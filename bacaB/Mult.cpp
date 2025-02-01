// Karolina Kulas
#include <cstdarg>
#include <string>
using namespace std;
int ss1(string a, string b) {
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
  return ss1(a.substr(1), b.substr(1));
}
string duSum(string &a, string &b, int idxA, int idxB, int carry) {
  if (idxA < 0 && idxB < 0) {
    if (carry == 1)
      return "1";
    return "";
  }
  int lastDigitA = (idxA >= 0) ? (a[idxA] - '0') : 0;
  int lastDigitB = (idxB >= 0) ? (b[idxB] - '0') : 0;
  int sum = lastDigitA + lastDigitB + carry;
  carry = sum / 10;
  string result = duSum(a, b, idxA - 1, idxB - 1, carry) + char(sum % 10 + '0');
  return result;
}
string doMult(string a, char b, int carry) {
  if (b == '0')
    return "0";
  if (a.empty()) {
    if (carry == 0)
      return "";
    int sum = carry;
    carry = sum / 10;
    sum %= 10;
    char summ = sum + '0';
    string result = doMult(a, b, carry) + summ;
    return result;
  }
  char xx = a[a.size() - 1];
  int x = xx - '0';
  int y = b - '0';
  int sum = x * y + carry;
  carry = sum / 10;
  sum %= 10;
  a = a.substr(0, a.size() - 1);
  char summ = sum + '0';
  string result = doMult(a, b, carry) + summ;
  return result;
}
void q(string a, string b, int n, int idx, string *array) {
  if (idx == n)
    return;
  array[idx] = doMult(a, b[n - idx - 1], 0) + string(idx, '0');
  q(a, b, n, idx + 1, array);
}
string doNormall(string s) {
  if (s.size() == 0)
    return "0";
  if (s[0] == '0' || s[0] == '-' || s[0] == '+')
    return doNormall(s.substr(1));
  return s;
}
string pp(string a, string b) {
  if (a.empty())
    return b;
  if (b.empty())
    return a;

  if (ss1(a, b) == -1) {
    return duSum(b, a, b.size() - 1, a.size() - 1, 0);
  }
  return duSum(a, b, a.size() - 1, b.size() - 1, 0);
}
string SomNext(int n, const string *s, string x) {
  if (n == 0)
    return x;
  string y = *s;
  y = doNormall(y);
  x = doNormall(x);
  x = pp(x, y);
  return SomNext(n - 1, (s + 1), x);
}
string Som(int n, const string *s) {
  if (n == 0)
    return "";
  string a = *s;
  string x = SomNext(n - 1, (s + 1), a);
  x = doNormall(x);
  return x;
}
string *makeArrr(int n, va_list arg) {
  string *arr = new string[n];
  for (int i = 0; i < n; ++i) {
    arr[i] = va_arg(arg, const char *);
  }
  return arr;
}
string MultNext(int n, int &sign, const string *s, string x) {
  if (n == 0)
    return x;
  string y = *s;
  if (y[0] == '-')
    sign++;
  sign %= 2;
  x = doNormall(x);
  y = doNormall(y);
  if (x == "0" || y == "0")
    return "0";
  string *arr = new string[y.size()];
  int tab_size = y.size();
  q(x, y, y.size(), 0, arr);
  x = Som(tab_size, arr);
  delete[] arr;
  return MultNext(n - 1, sign, (s + 1), x);
}

string Mult(int n, const string *s) {
  string a = *s;
  int sign = 0;
  if (a[0] == '-')
    sign++;
  string x = MultNext(n - 1, sign, (s + 1), a);
  x = doNormall(x);
  if (x[0] == '0')
    return x;
  return ((sign % 2 == 1) ? "-" : "") + x;
}
string Mult(int n, ...) {
  va_list arguments;
  va_start(arguments, n);
  string *arr = makeArrr(n, arguments);
  va_end(arguments);
  string result = Mult(n, arr);
  delete[] arr;
  return result;
}
void Mult(string *x, int n, const string *s) {
  *x = Mult(n, s);
  return;
}
void Mult(string *x, int n, ...) {
  va_list arguments;
  va_start(arguments, n);
  string *arr = makeArrr(n, arguments);
  va_end(arguments);
  *x = Mult(n, arr);
  delete[] arr;
}
void Mult(string &x, int n, const string *s) {
  x = Mult(n, s);
  return;
}
void Mult(string &x, int n, ...) {
  va_list arguments;
  va_start(arguments, n);
  string *arr = makeArrr(n, arguments);
  va_end(arguments);
  x = Mult(n, arr);
  delete[] arr;
}