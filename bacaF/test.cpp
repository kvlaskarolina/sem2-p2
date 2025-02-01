#include <cstdarg>
#include <iostream>
using namespace std;
class FACTOR {
public:
  int value;
  FACTOR *prev;
  FACTOR *next;

  FACTOR(int thisValue) {
    value = thisValue;
    prev = NULL;
    next = NULL;
  }
  FACTOR() {
    value = 0;
    prev = NULL;
    next = NULL;
  }
  ~FACTOR() {
    value = 0;
    prev = NULL;
    next = NULL;
  }
};

class POLYNOMIAL {
public:
  unsigned int degree;
  FACTOR *first;
  FACTOR *last;
  static int overloaded;
  POLYNOMIAL(int degree, ...) {
    this->degree = degree;
    va_list factors;
    va_start(factors, degree);
    first = NULL;
    last = NULL;
    for (int i = 0; i <= degree; ++i) {
      int value = va_arg(factors, int);
      FACTOR *a = new FACTOR(value);
      if (first == NULL) {
        first = a;
        last = a;
      } else {
        a->prev = last;
        last->next = a;
        last = a;
      }
    }
    va_end(factors);
    overloaded++;
  }
  friend ostream &operator<<(ostream &os, const POLYNOMIAL &p) {
    FACTOR *curr = p.first;
    os << "( ";
    while (curr != NULL) {
      os << curr->value;
      if (curr->next != NULL) {
        os << ", ";
      } else {
        os << " ";
      }
      curr = curr->next;
    }
    os << ")";
    return os;
  }
};

int POLYNOMIAL::overloaded = 0;
int main() {
  POLYNOMIAL p(0, 0);
  cout << p;
}

POLYNOMIAL(int degree, int values[]) {
  this->degree = degree;
  first = NULL;
  last = NULL;
  for (int i = 0; i <= degree; ++i) {
    FACTOR *a = new FACTOR(values[i]);
    if (first == NULL) {
      first = a;
      last = a;
    } else {
      a->prev = last;
      last->next = a;
      last = a;
    }
  }
  fixPolynomial();
  simplification();
  overloaded++;
}

POLYNOMIAL(int degree, int values[]) {
  this->degree = degree;
  first = NULL;
  last = NULL;
  for (int i = 0; i <= degree; ++i) {
    FACTOR *a = new FACTOR(values[i]);
    if (first == NULL) {
      first = a;
      last = a;
    } else {
      a->prev = last;
      last->next = a;
      last = a;
    }
  }
  fixPolynomial();
  simplification();
  overloaded++;
}

POLYNOMIAL(int degree, int values[]) {
  this->degree = degree;
  first = NULL;
  last = NULL;
  for (int i = 0; i <= degree; ++i) {
    FACTOR *a = new FACTOR(values[i]);
    if (first == NULL) {
      first = a;
      last = a;
    } else {
      a->prev = last;
      last->next = a;
      last = a;
    }
  }
  fixPolynomial();
  simplification();
  overloaded++;
}