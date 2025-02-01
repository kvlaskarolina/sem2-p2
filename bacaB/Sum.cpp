// Karolina Kulas
#include <cstdarg>
//#include <iostream>
#include <string>
using namespace std;
int ss(string a, string b) {
  if (a.empty() && b.empty())
    return 0;
  if (a.size() > b.size())
    return 1;
  if (a.size() < b.size())
    return -1;
  if (a[0] > b[0])
    return 1;
  if (a[0] < b[0])
    return -1;
  return ss(a.substr(1), b.substr(1));
}
string doNormal(string s) {
  if (s.size() == 0)
    return "0";
  if (s[0] == '0' || s[0] == '-' || s[0] == '+')
    return doNormal(s.substr(1));
  return s;
}
string doSum(string a, string b, int carry) {
  if (a.empty()) {
    char m = (carry + '0');
    return string(1, m);
  }
  if (b.empty()) {
    char lastCharA = a[a.size() - 1];
    int lastDigitA = lastCharA - '0';
    int sum = lastDigitA + carry;
    if (sum > 10) {
      sum %= 10;
      carry = 1;
    } else
      carry = 0;
    a = a.substr(0, a.size() - 1);
    char summ = sum + '0';
    return doSum(a, b, carry) + summ;
  }
  char lastCharA = a[a.size() - 1];
  char lastCharB = b[b.size() - 1];
  int lastDigitA = lastCharA - '0';
  int lastDigitB = lastCharB - '0';
  int sum = lastDigitA + lastDigitB + carry;
  carry = sum / 10;
  sum %= 10;
  a = a.substr(0, a.size() - 1);
  b = b.substr(0, b.size() - 1);
  char summ = sum + '0';
  return doSum(a, b, carry) + summ;
}
string doSubtract(string a, string b, int carry) {
  if (a.empty()) {
    return "";
  }
  if (b.empty()) {
    char lastCharA = a[a.size() - 1];
    int lastDigitA = lastCharA - '0';
    int diff = lastDigitA - carry;
    if (diff < 0) {
      diff += 10;
      carry = 1;
    } else
      carry = 0;
    a = a.substr(0, a.size() - 1);
    string x = "";
    x = (diff + '0');
    return doSubtract(a, b, carry) + x;
  }
  char lastCharA = a[a.size() - 1];
  char lastCharB = b[b.size() - 1];
  int lastDigitA = lastCharA - '0';
  int lastDigitB = lastCharB - '0';
  int diff = lastDigitA - lastDigitB - carry;
  if (diff < 0) {
    diff += 10;
    carry = 1;
  } else {
    carry = 0;
  }
  a = a.substr(0, a.size() - 1);
  b = b.substr(0, b.size() - 1);
  string x = "";
  x = (diff + '0');
  return doSubtract(a, b, carry) + x;
}
string p(string a, string b, bool a_neg, bool b_neg) {
  if (a.empty())
    return (b_neg ? "-" : "") + b;
  if (b.empty())
    return (a_neg ? "-" : "") + a;
  if (a_neg && !b_neg) {
    switch (ss(a, b)) {
    case 1:
      return '-' + doSubtract(a, b, 0);
    case 0:
      return "0";
    case -1:
      return doSubtract(b, a, 0);
    default:
      return "";
    }
  }
  if (!a_neg && b_neg) {
    switch (ss(a, b)) {
    case 1:
      return doSubtract(a, b, 0);
    case 0:
      return "0";
    case -1:
      return '-' + doSubtract(b, a, 0);
    default:
      return "";
    }
  }
  if (ss(a, b) == -1) {
    string temp = a;
    a = b;
    b = temp;
  }
  if (a_neg && b_neg) {
    return "-" + doSum(a, b, 0);
  }
  if (!a_neg && !b_neg)
    return doSum(a, b, 0);
}
string SumNext(int n, const string *s, string x) {
  if (n == 0)
    return x;
  string y = *s;
  bool x_neg = (x[0] == '-'), y_neg = (y[0] == '-');
  y = doNormal(y);
  x = doNormal(x);
  x = p(x, y, x_neg, y_neg);
  return SumNext(n - 1, (s + 1), x);
}
void makeArr(string *arr, int n, va_list arg) {
  if (n == 0)
    return;
  arr[0] = va_arg(arg, const char *);
  makeArr(arr + 1, n - 1, arg);
}
string Sum(int n, const string *s) {
  string a = *s;
  string x = SumNext(n - 1, (s + 1), a);
  bool x_neg = (x[0] == '-');
  x = doNormal(x);
  if (x[0] == '0')
    return x;
  return (x_neg ? "-" : "") + x;
}
string Sum(int n, ...) {
  string arr[n];
  va_list arguments;
  va_start(arguments, n);
  makeArr(arr, n, arguments);
  va_end(arguments);
  return Sum(n, arr);
}
void Sum(string *x, int n, const string *s) { *x = Sum(n, s); }
void Sum(string *x, int n, ...) {
  string arr[n];
  va_list arguments;
  va_start(arguments, n);
  makeArr(arr, n, arguments);
  va_end(arguments);
  *x = Sum(n, arr);
}
void Sum(string &x, int n, const string *s) { x = Sum(n, s); }
void Sum(string &x, int n, ...) {
  string arr[n];
  va_list arguments;
  va_start(arguments, n);
  makeArr(arr, n, arguments);
  va_end(arguments);
  x = Sum(n, arr);
}
/**
int main() {
  std::string term1;
  std::string term2;
  int i = 0;
  int num = 0;

  std::cin >> num;
  while (i < num) {
    std::cin >> term1;
    std::cin >> term2;
    std::cout << Sum(2, term1.c_str(), term2.c_str()) << '\n';
    i++;
  }

  return 0;
}
*/