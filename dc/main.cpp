#include <cstdio>
#include "fast-dtoa.cc"

void foo();
int main() {
  char buf[100];
  int len, dec;
  fast_dtoa(123.123443234875638475638745638745638746583745687, fast_dtoa_mode::shortest, 0, buffer<char>(buf, sizeof(buf)), &len, &dec);
  printf("%se%d\n", buf, dec-1);

  foo();
}
