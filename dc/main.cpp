#include "fast-dtoa.cc"

int main() {
  char buf[100];
  int len, dec;
  FastDtoa(100.0, FAST_DTOA_SHORTEST, 0, Vector<char>(buf, sizeof(buf)), &len, &dec);
}
