#include "Fraction.hpp"
using namespace ariel;

Fraction::Fraction(int numeator, int denominator)
{
    if (denominator == 0)
    {
        throw invalid_argument("denominator can't be 0");
    }

    this->numeator = numeator;
    this->denominator = denominator;
    reduce();
}
Fraction::Fraction(float numeator)
{
    if (numeator < 0)
    {
        this->denominator = -1000;
    }
    else
    {
        this->denominator = 1000;
    }
    // abs is a function that return the absolute value of a number
    this->numeator = abs(numeator) * 1000; // casting numeator to int
    reduce();
}
int Fraction::gcd(int frist, int second)
{
    if (second == 0)
        return frist;
    return gcd(second, frist % second);
}
void Fraction::reduce()
{
    int gcd = this->gcd(this->numeator, this->denominator);
    this->numeator /= gcd;
    this->denominator /= gcd;
    if (this->denominator < 0 && this->numeator > 0)
    {
        this->numeator *= -1;
        this->denominator *= -1;
    }
}
// the furmula is (a/b) + (c/d) = (a*d + b*c)/(b*d)
Fraction Fraction::operator+(const Fraction &other)
{
    long newNumeator = (long)this->numeator * other.denominator + other.numeator * this->denominator;
    long newDenominator = (long)this->denominator * other.denominator;
    // check if the fraction is overflowing the float
    if (newNumeator > this->max || newNumeator < this->min || newDenominator > this->max || newDenominator < this->min)
    {
        throw overflow_error("overflow");
    }
    Fraction newFraction(newNumeator, newDenominator);
    return newFraction;
}
Fraction Fraction::operator+(float other)
{
    // float + fraction need to add float to the fraction
    Fraction newFraction(other);
    return *this + newFraction;
}
// the furmula is (a/b) - (c/d) = (a*d - b*c)/(b*d)
Fraction Fraction::operator-(const Fraction &other)
{
    long newNumeator = (long)this->numeator * other.denominator - other.numeator * this->denominator;
    long newDenominator = (long)this->denominator * other.denominator;
    // check if the fraction is overflowing the float
    if (newNumeator > this->max || newNumeator < this->min || newDenominator > this->max || newDenominator < this->min)
    {
        throw overflow_error("overflow");
    }
    Fraction newFraction(newNumeator, newDenominator);
    newFraction.reduce();
    return newFraction;
}
Fraction Fraction::operator-(float other)
{
    Fraction newFraction(other);
    return *this - newFraction;
}
// the furmula is (a/b) * (c/d) = (a*c)/(b*d)
Fraction Fraction::operator*(const Fraction &other)
{
    long newNumeator = (long)this->numeator * other.numeator;
    long newDenominator = (long)this->denominator * other.denominator;
    // check if the fraction is overflowing the float
    if (newNumeator > this->max || newNumeator < this->min || newDenominator > this->max || newDenominator < this->min)
    {
        throw overflow_error("overflow");
    }
    Fraction newFraction(newNumeator, newDenominator);
    newFraction.reduce();
    return newFraction;
}
Fraction Fraction::operator*(float other)
{
    Fraction newFraction(other);
    return *this * newFraction;
}
// the furmula is (a/b) / (c/d) = (a*d)/(b*c)
Fraction Fraction::operator/(const Fraction &other)
{
    long newNumeator = (long)this->numeator * other.denominator;
    long newDenominator = (long)this->denominator * other.numeator;
    // check if the fraction is overflowing the float
    if (newNumeator > this->max || newNumeator < this->min || newDenominator > this->max || newDenominator < this->min)
    {
        throw overflow_error("overflow");
    }
    // if 0 in the denominator
    if (other.numeator == 0) // the numenator is 0 when the fraction is 0
    {
        throw runtime_error("denominator can't be 0");
    }

    return Fraction(newNumeator, newDenominator); // include reduce
}
Fraction Fraction::operator/(float other)
{
    Fraction newFraction(other);
    return *this / newFraction;
}
Fraction &Fraction::operator++()
{
    this->numeator += this->denominator; // int
    return *this;
}
Fraction Fraction::operator++(int)
{
    // save the old fraction deep copy
    Fraction temp = *this;
    // add 1 to the fraction
    ++*this;
    // return the old fraction
    return temp;
}
Fraction &Fraction::operator--()
{
    this->numeator -= this->denominator;
    return *this;
}
Fraction Fraction::operator--(int)
{
    Fraction temp = *this;
    --*this;
    return temp;
}
bool Fraction::operator==(const Fraction &other) const
{
    return this->numeator == other.numeator && this->denominator == other.denominator;
}
bool Fraction::operator==(float other) const
{
    return this->numeator == other * this->denominator;
}
bool Fraction::operator!=(const Fraction &other) const
{
    return !(*this == other);
}
bool Fraction::operator!=(float other) const
{
    return !(*this == other);
}
bool Fraction::operator>(const Fraction &other) const
{
    return this->numeator * other.denominator > other.numeator * this->denominator;
}
bool Fraction::operator>(float other) const
{
    return this->numeator > other * this->denominator;
}
bool Fraction::operator<(const Fraction &other) const
{
    return this->numeator * other.denominator < other.numeator * this->denominator;
}
bool Fraction::operator<(float other) const
{
    return this->numeator < other * this->denominator;
}
bool Fraction::operator>=(const Fraction &other) const
{
    return *this > other || *this == other;
}
bool Fraction::operator>=(float other) const
{
    return *this > other || *this == other;
}
bool Fraction::operator<=(const Fraction &other) const
{
    return *this < other || *this == other;
}
bool Fraction::operator<=(float other) const
{
    return *this < other || *this == other;
}

ostream &ariel::operator<<(ostream &output, const Fraction &fraction) // not working without ariel::
{
    output << fraction.numeator << "/" << fraction.denominator;
    return output;
}
istream &ariel::operator>>(istream &input, Fraction &fraction) // not working without ariel::
{
    // check if the input is valid
    if (input >> fraction.numeator >> fraction.denominator)
    {
        if (fraction.denominator == 0)
        {
            throw runtime_error("denominator can't be 0");
        }
        fraction.reduce();
        return input;
    }
    else
    {
        throw runtime_error("invalid input");
    }
}

Fraction ariel::operator+(float other, const Fraction &fraction) // not working without ariel::
{
    return Fraction(other) + fraction;
}
Fraction ariel::operator-(float other, const Fraction &fraction) // not working without ariel::
{
    return Fraction(other) - fraction;
}
Fraction ariel::operator*(float other, const Fraction &fraction)
{
    return Fraction(other) * fraction;
}
Fraction ariel::operator/(float other, const Fraction &fraction)
{
    return Fraction(other) / fraction;
}
bool ariel::operator==(float other, const Fraction &fraction)
{

    return Fraction(other) == fraction;
}
bool ariel::operator!=(float other, const Fraction &fraction)
{
    return !(other == fraction);
}
bool ariel::operator>(float other, const Fraction &fraction)
{
    return !(other <= fraction);
}
bool ariel::operator<(float other, const Fraction &fraction)
{
    return !(other >= fraction);
}
bool ariel::operator>=(float other, const Fraction &fraction)
{
    return Fraction(other) >= fraction;
}
bool ariel::operator<=(float other, const Fraction &fraction)
{
    return Fraction(other) <= fraction;
}