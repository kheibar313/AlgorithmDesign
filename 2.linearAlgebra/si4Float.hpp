#ifndef SI4FLOAT
#define SI4FLOAT

#include <iostream>
#include <numeric>
#include <stdexcept>

class si4Float
{
private:
    long long _numerator = 0;
    long long _denominator = 1;

    void simplify()
    {
        if (_denominator < 0)
        {
            _numerator *= -1;
            _denominator *= -1;
        }
        long long g = std::gcd(_numerator, _denominator);
        if (g != 0)
        {
            _numerator /= g;
            _denominator /= g;
        }
    }

public:
    si4Float() = default;

    si4Float(long long numerator, long long denominator = 1)
    {
        if (denominator == 0)
            throw std::invalid_argument("Division by zero is not defined!");
        _numerator = numerator;
        _denominator = denominator;
        simplify();
    }

    si4Float(int n) : _numerator(n), _denominator(1) {}
    
    template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
    si4Float(T val)
    {
        const long long scale = 1000000000;
        _numerator = static_cast<long long>(val * scale);
        _denominator = scale;
        simplify();
    }
    
    long long returnNumerator() const { return _numerator; }
    long long returnDenominator() const { return _denominator; }
    long double returnVal() const
    {
        return static_cast<long double>(_numerator) / _denominator;
    }

    si4Float operator*(const si4Float &second) const
    {
        return si4Float(_numerator * second._numerator, _denominator * second._denominator);
    }

    si4Float operator/(const si4Float &second) const
    {
        if (second._numerator == 0)
            throw std::invalid_argument("Division by zero fraction!");
        return si4Float(_numerator * second._denominator,
                        _denominator * second._numerator);
    }

    si4Float operator-(const si4Float &second) const
    {
        return si4Float(_numerator * second._denominator - second._numerator * _denominator, _denominator * second._denominator);
    }

    si4Float operator+(const si4Float &second) const
    {
        return si4Float(_numerator * second._denominator + second._numerator * _denominator, _denominator * second._denominator);
    }

    si4Float &operator*=(const si4Float &second)
    {
        _numerator *= second._numerator;
        _denominator *= second._denominator;
        simplify();
        return *this;
    }

    si4Float &operator/=(const si4Float &second)
    {
        if (second._numerator == 0)
            throw std::invalid_argument("Division by zero fraction!");
        _numerator *= second._denominator;
        _denominator *= second._numerator;
        simplify();
        return *this;
    }

    si4Float &operator-=(const si4Float &second)
    {
        _numerator = _numerator * second._denominator - second._numerator * _denominator;
        _denominator *= second._denominator;
        simplify();
        return *this;
    }

    si4Float &operator+=(const si4Float &second)
    {
        _numerator = _numerator * second._denominator + second._numerator * _denominator;
        _denominator *= second._denominator;
        simplify();
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const si4Float &f)
    {
        if (f._denominator == 1)
            os << f._numerator;
        else
            os << f._numerator << "/" << f._denominator;
        return os;
    }
};

#endif
