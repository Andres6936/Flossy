#include "fast-dtoa.cc"
#include <cstdio>


void foo() {
  char buf[100];
  int len, dec;
  FastDtoa(543.213f, FAST_DTOA_SHORTEST_SINGLE, 0, Vector<char>(buf, sizeof(buf)), &len, &dec);
  printf("%se%d\n", buf, dec-1);
}
