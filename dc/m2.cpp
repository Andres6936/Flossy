#include "fast-dtoa.cc"
#include <cstdio>


void foo() {
  char buf[100];
  int len, dec;
  fast_dtoa(543.213f, fast_dtoa_mode::shortest_single, 0, buffer<char>(buf, sizeof(buf)), &len, &dec);
  printf("%se%d\n", buf, dec-1);
}
