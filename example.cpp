#include "flossy.h"
#include <iostream>
#include <string>
#include <iterator>

int main() {
  std::string format = "{<+05.3f}";
  flossy::format(std::ostream_iterator<char>(std::cout), format.begin(), format.end(), 10.0);
}
