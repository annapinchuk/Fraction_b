#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <limits>

#pragma once
// about const and initialization list: can be use to initialize const variables in the constructor :)
using namespace std;
namespace ariel
{
    class Fraction
    {
        // numerator/denominator
    private:
        int numeator;
        int denominator;
        // if the fraction addition is overflowing the float we need to throw an exception
        int max = std::numeric_limits<int>::max();
        int min = std::numeric_limits<int>::min();

        int gcd(int first, int second); // greatest common divisor for reduce function source:https://clubztutoring.com/ed-resources/math/how-to-reduce-a-fraction/
    public:
        void reduce(); // reduce the fraction after operations
        // constructor
        Fraction() : numeator(0), denominator(1) {}
        Fraction(int numeator, int denominator); // float contains int and float
        Fraction(float numeator);
        // distractor
        ~Fraction() {}
        // copy constructor
        Fraction(const Fraction &other) : numeator(other.numeator), denominator(other.denominator) {}
        // getters
        int getNumerator() const { return numeator; }
        int getDenominator() const { return denominator; }
        // & is more efficient than * (pointer) because it doesn't need to allocate memory source:https://www.programiz.com/cpp-programming/operator-overloading
        // arithmetic operators
        Fraction operator+(const Fraction &num); // we dont change the fraction so we dont need to pass by reference
        Fraction operator+(float num);
        Fraction operator-(const Fraction &num);
        Fraction operator-(float num);
        Fraction operator*(const Fraction &num);
        Fraction operator*(float num);
        Fraction operator/(const Fraction &num);
        Fraction operator/(float num);
        // increment and decrement operators
        Fraction &operator++();
        Fraction operator++(int);
        Fraction &operator--();
        Fraction operator--(int);
        // comparison operators
        bool operator==(const Fraction &num) const;
        bool operator==(float num) const;
        bool operator!=(const Fraction &num) const;
        bool operator!=(float num) const;
        bool operator>(const Fraction &num) const;
        bool operator<(float num) const;
        bool operator<(const Fraction &num) const;
        bool operator>(float num) const;
        bool operator>=(const Fraction &num) const;
        bool operator>=(float num) const;
        bool operator<=(const Fraction &num) const;
        bool operator<=(float num) const;
        // friend function <<
        friend ostream &operator<<(ostream &output, const Fraction &fraction);
        // friend function >>
        friend istream &operator>>(istream &input, Fraction &fraction);
        // friend function float
        friend Fraction operator+(float num, const Fraction &fraction);
        friend Fraction operator-(float num, const Fraction &fraction);
        friend Fraction operator*(float num, const Fraction &fraction);
        friend Fraction operator/(float num, const Fraction &fraction);
        friend bool operator==(float num, const Fraction &fraction);
        friend bool operator!=(float num, const Fraction &fraction);
        friend bool operator>(float num, const Fraction &fraction);
        friend bool operator<(float num, const Fraction &fraction);
        friend bool operator>=(float num, const Fraction &fraction);
        friend bool operator<=(float num, const Fraction &fraction);
    };
}