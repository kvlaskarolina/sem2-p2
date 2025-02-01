// Karolina Kulas
#include <cstdarg>
#include <string>
using namespace std;
void makeA(string *arr, int n, va_list arg) {
  if (n == 0)
    return;
  arr[0] = va_arg(arg, const char *);
  makeA(arr + 1, n - 1, arg);
}
string Operation(string (*ope)(int a, string const *b), int n,
                 const string *s) {
  return ope(n, s);
}
string Operation(string (*ope)(int a, string const *b), int n, ...) {
  string arr[n];
  va_list arguments;
  va_start(arguments, n);
  makeA(arr, n, arguments);
  va_end(arguments);
  return ope(n, arr);
}
void Operation(string *result, string (*ope)(int a, const string *b), int n,
               const string *s) {
  *result = ope(n, s);
}
void Operation(string *result, string (*ope)(int a, const string *b), int n,
               ...) {
  string arr[n];
  va_list arguments;
  va_start(arguments, n);
  makeA(arr, n, arguments);
  va_end(arguments);
  *result = ope(n, arr);
}
void Operation(string &result, void (*ope)(string *c, int a, const string *b),
               int n, const string *s) {
  ope(&result, n, s);
}
void Operation(string &result, void (*ope)(string *c, int a, const string *b),
               int n, ...) {
  string arr[n];
  va_list arguments;
  va_start(arguments, n);
  makeA(arr, n, arguments);
  va_end(arguments);
  ope(&result, n, arr);
}
