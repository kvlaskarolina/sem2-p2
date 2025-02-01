
#include "POLYNOMIAL.cpp"
#include <cstdarg>
#include <iostream>
using namespace std;
int POLYNOMIAL::overloaded = 0;
int main() {
  POLYNOMIAL p1(4, 3, 2, 1, 2, 7);
  POLYNOMIAL p2(1, 4, 7);
  cout << ++p1 << p1-- << p1;
}
int POLYNOMIAL::overloaded = 0;
int main() {
  POLYNOMIAL p1(4, 3, 2, 1, 2, 7);
  POLYNOMIAL p2(1, 4, 7);
  cout << p1 * p2;
}
