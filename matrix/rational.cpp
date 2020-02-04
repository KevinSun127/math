#include <stdexcept>
#include "rational.h"

Rational::Rational()
{
    n = 0;
    d = 1;
}

Rational::Rational(int num, int denom):
  n(num), d(denom)
{
    if (denom == 0) throw std::invalid_argument("Can't have denom = 0");
    // Continue your implementation below.
    // You should likely call this->reduce() and this->normalize0()

    this->reduce();

    if(d < 0)
    {
        n *= -1;
        d *= -1;
    }

    this->normalize0();

}

void Rational::normalize0()
{
  if (n == 0 && d != 1)
    d = 1;
}



std::ostream& operator<<(std::ostream& ostr, const Rational& r)
{
  //prints the numerator then a slash then the denominator
  std::string print = std::to_string(r.n) + '/' + std::to_string(r.d);
  ostr << print;
  return ostr;
}


std::istream& operator>>(std::istream& istr, Rational& r)
{
  //extracts from the stream
  //numerator -> then slash -> then denominator
  char slash;
  istr >> r.n >> slash >> r.d;

  //if the stream fails, set the rational = 0/1
  if(istr.fail())
  {
    r.n = 0;
    r.d = 1;
    return istr;
  }

  //standardizes the rational number
    //1. reduces the fraction
    //2. denominator > 0
    //3. 0/(not 1) -> 0/1

  r.reduce();
  if(r.d < 0)
  {
      r.n *= -1;
      r.d *= -1;
  }
  r.normalize0();

  return istr;
}


void Rational::reduce()
{
  //divides top and bottom by the greatest common factor
  int div = gcd(n, d);

  //reverses sign if factor is negative
  if(div < 0)
    div = -div;

  n/=div;
  d/=div;
}


//https://en.wikipedia.org/wiki/Euclidean_algorithm#Procedure
int Rational::gcd(int a, int b)
{
  if(!(a%b))
    return b;
  return gcd(b, a%b);
}


int Rational::lcm(int a, int b)
{
  //takes the GCD out of each
  //then multiplies both by the GCD
  int fact = gcd(a, b);
  return fact*(a/fact)*(b/fact);
}

//Addition

Rational operator+(const Rational& r1, const Rational& r2)
{
  //cross-multiply (+multiply the two denom. together)
  //then add -> then return the sum
  Rational newR(r1.n*r2.d + r2.n*r1.d, r1.d*r2.d);
  return newR;
}

Rational operator+(const int num, const Rational& r)
{
  //cross-multiply -> add -> return the sum
  Rational newR(num*r.d + r.n, r.d);
  return newR;
}

Rational operator+(const Rational& r, const int num)
{
  //cross-multiply -> add -> return the sum
  Rational newR(num*r.d + r.n, r.d);
  return newR;
}

//Subtraction

Rational operator-(const Rational& r1, const Rational& r2)
{
  //cross-multiply (+multiply the two denom. together)
  //then add -> then return the sum
  Rational newR(r1.n*r2.d - r2.n*r1.d, r1.d*r2.d);
  return newR;
}

Rational operator-(const int num, const Rational& r)
{
  //cross-multiply -> add -> return the sum
  Rational newR(num*r.d - r.n, r.d);
  return newR;
}

Rational operator-(const Rational& r, const int num)
{
  //cross-multiply -> add -> return the sum
  Rational newR(num*r.d - r.n, r.d);
  return newR;
}



//Multiplication

Rational operator*(const Rational& r1, const Rational& r2)
{
  //multiplies the numerators and denominators
  //returns the product
  Rational newR(r1.n*r2.n, r1.d*r2.d);
  return newR;
}

Rational operator*(const int num, const Rational& r)
{
  Rational newR(num*r.n, r.d);
  return newR;
}

Rational operator*(const Rational& r, const int num)
{
  Rational newR(num*r.n, r.d);
  return newR;
}

//Exponentiation

Rational operator^(const Rational& r, int const num)
{
  //creates a copy of
    //1. numerator (newN)
    //2. denominator (newD)
    //3. power (power)
  int newN, newD, power = num;

  //power of anything to zero is 1
  if(num == 0)
  {
    newN = 1, newD = 1;
  }

  //assign copies of the numerator and denominator
  else if(num > 0)
  {
    newN = r.n, newD = r.d;
  }

  //if the power is negative, switch the num. and denom.
  else
  {
    newN = r.d, newD = r.n;
    power = -num;
  }

  //final numerator and denominator
  int finN = newN, finD = newD;

  //multiply by initial num and denom (power-1) times
  for(int i = 1; i < power; i++)
  {
    finN*=newN;
    finD*=newD;
  }

  //return a rational number with this data
  Rational newR(finN, finD);
  return newR;
}

//Equal
bool operator==(const Rational& r1, const Rational& r2)
{
  //check if the num. and denom. are equal
  return (r1.n == r2.n) && (r1.d == r2.d);
}

//Not Equal
bool operator!=(const Rational& r1, const Rational& r2)
{
  ///check if the num. and denom. are not equal
  return (r1.n != r2.n) || (r1.d != r2.d);
}

//Less than
bool operator<(const Rational& r1, const Rational& r2)
{
  //cross-multiply and see which side is greater
  return (r1.n*r2.d < r2.n*r1.d);
}

//Assignment Addition
Rational Rational::operator+=(const Rational& r2)
{
  //cross-multiply (+multiply the two denom. together)
  //then add -> then assign
  n = n*r2.d + r2.n*d;
  d = d*r2.d;

  //reduce the fraction to lowest terms
  this->reduce();

  return *this;
}

Rational Rational::operator+=(const int num)
{
  //cross-multiply -> add -> assign
  n+=(num*d);

  //reduce fraction
  this->reduce();

  return *this;
}

//Assignment Subtraction
Rational Rational::operator-=(const Rational& r2)
{
  //cross-multiply (+multiply the two denom. together)
  //then add -> then assign
  n = n*r2.d - r2.n*d;
  d = d*r2.d;

  //reduce the fraction to lowest terms
  this->reduce();

  return *this;
}

Rational Rational::operator-=(const int num)
{
  //cross-multiply -> add -> assign
  n-=(num*d);

  //reduce fraction
  this->reduce();

  return *this;
}


//Assignment Multiplication
Rational Rational::operator*=(const Rational& r2)
{
  //multiply corresponding num. and denom.
  n*=r2.n;
  d*=r2.d;

  //reduce the fraction
  this->reduce();

  return *this;
}

Rational Rational::operator*=(const int num)
{
  //multiply numerator by the integer
  n*=num;

  //reduce fraction
  this->reduce();

  return *this;
}

Rational Rational::operator=(int num)
{
  n = num;
  d = 1;
  return *this;
}
