// Karolina Kulas
#include <cstdarg>
#include <iostream>
using namespace std;
int GCD(int a, int b) {
  if (a == 0)
    return b;
  if (b == 0)
    return a;
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}
int NWW(int a, int b) { return a * b / GCD(a, b); }
int ABS(int a) {
  if (a < 0)
    return a * (-1);
  return a;
}
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

  void simplification() {
    FACTOR *curr = first;
    int gcd = ABS(curr->value);
    while (curr != NULL) {
      gcd = GCD(ABS(curr->value), gcd);
      curr = curr->next;
    }
    curr = first;
    while (curr != NULL) {
      if (gcd != 0)
        curr->value /= gcd;
      curr = curr->next;
    }
  }
  void simplificationArray(int arr[], int len) {
    int gcd = ABS(arr[0]);
    for (int i = 1; i <= len; i++) {
      gcd = GCD(ABS(arr[i]), gcd);
    }
    for (int i = 0; i <= len; i++) {
      if (gcd != 0)
        arr[i] /= gcd;
    }
  }
  void fixPolynomial() {
    FACTOR *curr = last;
    while (curr != NULL && curr->value == 0 && curr != first) {
      FACTOR *toDelete = curr;
      curr = curr->prev;
      if (curr != NULL) {
        curr->next = NULL;
      }
      last = curr;
      degree--;
      delete toDelete;
    }
  }
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
    fixPolynomial();
    simplification();
    overloaded++;
  }

  POLYNOMIAL() {
    this->degree = 0;
    FACTOR *a = new FACTOR(0);
    first = a;
    last = a;
    overloaded++;
  }
  POLYNOMIAL(int degree, int v) {
    this->degree = 0;
    if (v != 0) {
      v = (v < 0) ? -1 : 1;
    }
    FACTOR *a = new FACTOR(v);
    first = a;
    last = a;
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
  POLYNOMIAL(const POLYNOMIAL &p) {
    this->degree = p.degree;
    first = NULL;
    last = NULL;
    FACTOR *curr = p.first;
    while (curr != NULL) {
      FACTOR *a = new FACTOR(curr->value);
      if (first == NULL) {
        first = a;
        last = a;
      } else {
        a->prev = last;
        last->next = a;
        last = a;
      }
      curr = curr->next;
    }
    fixPolynomial();
    simplification();
    overloaded++;
  }

  ~POLYNOMIAL() {
    FACTOR *current = first;
    while (current != NULL) {
      FACTOR *next = current->next;
      delete current;
      current = next;
    }
    first = NULL;
    last = NULL;
    degree = 0;
    overloaded--;
  }
  POLYNOMIAL operator<<(int shift) {
    int resultDegree = this->degree - shift;
    POLYNOMIAL result(*this);
    if (shift < 0 || resultDegree < 0) {
      POLYNOMIAL r(0, 0);
      return r;
    }
    FACTOR *curr = result.first;
    for (int i = 0; i < shift; ++i) {
      result.first = curr->next;
      curr = curr->next;
      curr->prev = NULL;
      result.degree--;
    }
    result.fixPolynomial();
    result.simplification();
    return result;
  }
  POLYNOMIAL operator>>(int shift) {
    POLYNOMIAL result(*this);
    FACTOR *curr = result.first;
    if (shift < 0) {
      POLYNOMIAL r(0, 0);
      return r;
    }
    for (int i = 0; i < shift; ++i) {
      FACTOR *New = new FACTOR(0);
      New->next = curr;
      curr->prev = New;
      result.first = New;
      curr = New;
    }

    result.degree = this->degree + shift;
    return result;
  }
  POLYNOMIAL operator++() {
    POLYNOMIAL result;
    result.degree = this->degree;
    result.first = NULL;
    result.last = NULL;
    FACTOR *curr1 = this->first;
    for (int i = 0; i <= result.degree; ++i) {
      int val1 = curr1->value;
      FACTOR *a = new FACTOR(val1 + 1);
      if (result.first == NULL) {
        result.first = a;
        result.last = a;
      } else {
        a->prev = result.last;
        result.last->next = a;
        result.last = a;
      }

      if (curr1 != NULL)
        curr1 = curr1->next;
    }

    result.fixPolynomial();
    result.simplification();

    *this = result;
    return *this;
  }
  POLYNOMIAL operator--() {
    POLYNOMIAL result;
    result.degree = this->degree;
    result.first = NULL;
    result.last = NULL;
    FACTOR *curr1 = this->first;
    for (int i = 0; i <= result.degree; ++i) {
      int val1 = curr1->value;
      FACTOR *a = new FACTOR(val1 - 1);
      if (result.first == NULL) {
        result.first = a;
        result.last = a;
      } else {
        a->prev = result.last;
        result.last->next = a;
        result.last = a;
      }

      if (curr1 != NULL)
        curr1 = curr1->next;
    }

    result.fixPolynomial();
    result.simplification();
    *this = result;
    return *this;
  }
  POLYNOMIAL operator++(int) {
    POLYNOMIAL result;
    result.degree = this->degree;
    result.first = NULL;
    result.last = NULL;
    FACTOR *curr1 = this->first;
    for (int i = 0; i <= result.degree; ++i) {
      int val1 = curr1->value;
      FACTOR *a = new FACTOR(val1 + 1);
      if (result.first == NULL) {
        result.first = a;
        result.last = a;
      } else {
        a->prev = result.last;
        result.last->next = a;
        result.last = a;
      }

      if (curr1 != NULL)
        curr1 = curr1->next;
    }

    result.fixPolynomial();
    result.simplification();
    POLYNOMIAL prevPoly(*this);
    *this = result;
    return prevPoly;
  }
  POLYNOMIAL operator--(int) {
    POLYNOMIAL result;
    result.degree = this->degree;
    result.first = NULL;
    result.last = NULL;
    FACTOR *curr1 = this->first;
    for (int i = 0; i <= result.degree; ++i) {
      int val1 = curr1->value;
      FACTOR *a = new FACTOR(val1 - 1);
      if (result.first == NULL) {
        result.first = a;
        result.last = a;
      } else {
        a->prev = result.last;
        result.last->next = a;
        result.last = a;
      }

      if (curr1 != NULL)
        curr1 = curr1->next;
    }

    result.fixPolynomial();
    result.simplification();

    POLYNOMIAL prevPoly(*this);
    *this = result;
    return prevPoly;
  }
  POLYNOMIAL operator+(const POLYNOMIAL &p2) const {
    int resultDegree = (p2.degree > this->degree) ? p2.degree : this->degree;
    FACTOR *curr1 = this->first;
    FACTOR *curr2 = p2.first;
    int arrayresult[resultDegree + 1];
    for (int i = 0; i <= resultDegree; ++i) {
      int val1 = (curr1 != NULL) ? curr1->value : 0;
      int val2 = (curr2 != NULL) ? curr2->value : 0;
      arrayresult[i] = val1 + val2;

      if (curr1 != NULL)
        curr1 = curr1->next;
      if (curr2 != NULL)
        curr2 = curr2->next;
    }
    POLYNOMIAL result(resultDegree, arrayresult);
    return result;
  }
  POLYNOMIAL operator-() {
    POLYNOMIAL result(*this);
    FACTOR *curr = result.first;
    while (curr != NULL) {
      curr->value = curr->value * (-1);
      curr = curr->next;
    }
    return result;
  }
  POLYNOMIAL operator-(POLYNOMIAL p2) {
    POLYNOMIAL temp(-p2);
    return *this + temp;
  }
  POLYNOMIAL operator*(const POLYNOMIAL &p2) const {
    int resultDegree = p2.degree + this->degree + 1;
    int mult[p2.degree + 4][resultDegree];
    for (int i = 0; i < p2.degree + 4; i++) {
      for (int j = 0; j < resultDegree; j++) {
        mult[i][j] = 0;
      }
    }
    FACTOR *curr1 = this->first;
    for (int i = 0; i <= this->degree; i++) {
      mult[0][i] = curr1->value;
      curr1 = curr1->next;
    }
    FACTOR *curr2 = p2.first;
    for (int i = 0; i <= p2.degree; i++) {
      mult[1][i] = curr2->value;
      curr2 = curr2->next;
    }
    for (int i = 0; i <= p2.degree; i++) {
      for (int j = 0; j <= this->degree; j++) {
        mult[i + 2][j + i] = mult[1][i] * mult[0][j];
      }
    }
    for (int i = 0; i <= resultDegree; i++) {
      for (int j = 2; j < p2.degree + 3; j++)
        mult[p2.degree + 3][i] += mult[j][i];
    }
    POLYNOMIAL result(resultDegree - 1, mult[p2.degree + 3]);
    return result;
  }
  POLYNOMIAL operator/(const POLYNOMIAL &p2) const {
    if (this->degree < p2.degree)
      return POLYNOMIAL(0, 0);
    if (p2.degree == 0 && p2.first->value > 0)
      return *this;
    if (p2.degree == 0 && p2.first->value < 0)
      return (*this) * POLYNOMIAL(0, -1);
    if (p2.degree == 0 && p2.first->value == 0)
      return POLYNOMIAL(0, 0);

    int *dividend = new int[this->degree + 1];
    int *divisor = new int[p2.degree + 1];
    for (int i = 0; i <= this->degree; i++)
      dividend[i] = 0;
    for (int i = 0; i <= p2.degree; i++)
      divisor[i] = 0;
    FACTOR *curr1 = this->last;
    for (int i = this->degree; i >= 0 && curr1 != NULL; --i) {
      dividend[i] = curr1->value;
      curr1 = curr1->prev;
    }

    FACTOR *curr2 = p2.last;
    for (int i = p2.degree; i >= 0 && curr2 != NULL; --i) {
      divisor[i] = curr2->value;
      curr2 = curr2->prev;
    }

    int resultDegree = this->degree - p2.degree;
    int *resultArray = new int[resultDegree + 1]();
    for (int i = 0; i <= resultDegree; i++)
      resultArray[i] = 0;
    for (int i = this->degree; i >= p2.degree; --i) {
      if (dividend[i] != 0) {
        int d = ABS(NWW(dividend[i], divisor[p2.degree])) / ABS(dividend[i]);
        for (int j = 0; j <= resultDegree; j++) {
          resultArray[j] *= d;
        }
        for (int j = 0; j <= this->degree; j++) {
          dividend[j] *= d;
        }
        resultArray[i - p2.degree] = dividend[i] / divisor[p2.degree];
        for (int j = p2.degree; j >= 0; --j) {
          dividend[i - (p2.degree - j)] -=
              resultArray[i - p2.degree] * divisor[j];
        }
      } else {
        resultArray[i - p2.degree] = 0;
      }
    }

    POLYNOMIAL result(resultDegree, resultArray);

    delete[] dividend;
    delete[] divisor;
    delete[] resultArray;

    return result;
  }

  POLYNOMIAL operator%(const POLYNOMIAL &p2) {
    if (this->degree < p2.degree)
      return *this;
    if (p2.degree == 0 && p2.first->value > 0)
      return POLYNOMIAL(0, 0);
    if (p2.degree == 0 && p2.first->value < 0)
      return POLYNOMIAL(0, 0);
    if (p2.degree == 0 && p2.first->value == 0)
      return *this;
    int *dividend = new int[this->degree + 1];
    int *divisor = new int[p2.degree + 1];
    for (int i = 0; i <= this->degree; i++)
      dividend[i] = 0;
    for (int i = 0; i <= p2.degree; i++)
      divisor[i] = 0;
    FACTOR *curr1 = this->last;
    for (int i = this->degree; i >= 0 && curr1 != NULL; --i) {
      dividend[i] = curr1->value;
      curr1 = curr1->prev;
    }

    FACTOR *curr2 = p2.last;
    for (int i = p2.degree; i >= 0 && curr2 != NULL; --i) {
      divisor[i] = curr2->value;
      curr2 = curr2->prev;
    }

    int resultDegree = this->degree - p2.degree;
    int *resultArray = new int[resultDegree + 1]();
    for (int i = 0; i <= resultDegree; i++)
      resultArray[i] = 0;
    for (int i = this->degree; i >= p2.degree; --i) {
      if (dividend[i] != 0) {
        int d = ABS(NWW(dividend[i], divisor[p2.degree])) / ABS(dividend[i]);
        for (int j = 0; j <= resultDegree; j++) {
          resultArray[j] *= d;
        }
        for (int j = 0; j <= this->degree; j++) {
          dividend[j] *= d;
        }
        resultArray[i - p2.degree] = dividend[i] / divisor[p2.degree];
        for (int j = p2.degree; j >= 0; --j) {
          dividend[i - (p2.degree - j)] -=
              resultArray[i - p2.degree] * divisor[j];
        }
      } else {
        resultArray[i - p2.degree] = 0;
      }
    }

    POLYNOMIAL result(this->degree, dividend);

    delete[] dividend;
    delete[] divisor;
    delete[] resultArray;

    return result;
  }
  friend istream &operator>>(istream &is, POLYNOMIAL &p) {
    int degree;
    is >> degree;
    int elements[degree + 1];
    for (int i = 0; i <= degree; ++i) {
      is >> elements[i];
    }
    p = POLYNOMIAL(degree, elements);
    return is;
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
  POLYNOMIAL &operator=(const POLYNOMIAL &p) {
    FACTOR *current = first;
    while (current != NULL) {
      FACTOR *next = current->next;
      delete current;
      current = next;
    }
    first = last = NULL;
    degree = 0;

    this->degree = p.degree;
    first = NULL;
    last = NULL;
    FACTOR *curr = p.first;
    while (curr != NULL) {
      FACTOR *a = new FACTOR(curr->value);
      if (first == NULL) {
        first = a;
        last = a;
      } else {
        a->prev = last;
        last->next = a;
        last = a;
      }
      curr = curr->next;
    }

    return *this;
  }

  POLYNOMIAL &operator+=(const POLYNOMIAL &p) {
    *this = *this + p;
    return *this;
  }
  POLYNOMIAL &operator-=(POLYNOMIAL &p) {
    *this = *this + (-p);
    return *this;
  }
  POLYNOMIAL &operator<<=(int a) {
    *this = *this << a;
    return *this;
  }
  POLYNOMIAL &operator>>=(int a) {
    *this = *this >> a;
    return *this;
  }
  POLYNOMIAL &operator*=(POLYNOMIAL &p) {
    *this = *this * p;
    return *this;
  }
  POLYNOMIAL &operator/=(POLYNOMIAL &p) {
    *this = *this / p;
    return *this;
  }
  POLYNOMIAL &operator%=(POLYNOMIAL &p) {
    *this = *this % p;
    return *this;
  }
};

bool operator<(const POLYNOMIAL &p1, const POLYNOMIAL &p2) {
  if (p1.degree != p2.degree)
    return p1.degree < p2.degree;

  FACTOR *curr1 = p1.last;
  FACTOR *curr2 = p2.last;
  while (curr1 != NULL && curr2 != NULL) {
    if (curr1->value < curr2->value) {
      return true;
    }
    if (curr1->value > curr2->value) {
      return false;
    }
    curr1 = curr1->prev;
    curr2 = curr2->prev;
  }
  return false;
}
bool operator==(const POLYNOMIAL &p1, const POLYNOMIAL &p2) {
  return !(p1 < p2 || p2 < p1);
}

bool operator!=(const POLYNOMIAL &p1, const POLYNOMIAL &p2) {
  return !(p1 == p2);
}
bool operator<=(const POLYNOMIAL &p1, const POLYNOMIAL &p2) {
  return (p1 < p2 || p1 == p2);
}

bool operator>(const POLYNOMIAL &p1, const POLYNOMIAL &p2) {
  return !(p1 <= p2);
}

bool operator>=(const POLYNOMIAL &p1, const POLYNOMIAL &p2) {
  return !(p1 < p2);
}
int POLYNOMIAL::overloaded = 0;
int main() {
  cout << POLYNOMIAL(9, 3, 1, 0, 6, 22, 1, -99, 1, 1, 1) /
              POLYNOMIAL(3, 1, 32, 3, 4)
       << endl;
}