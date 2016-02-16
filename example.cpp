#include "flossy.h"
#include <iostream>
#include <string>
#include <iterator>

int main() {
  std::string format = "xxxxx{>+05.3f}yyyyy";
  flossy::format(std::ostream_iterator<char>(std::cout), format.begin(), format.end(), 10.0);


  std::string result = flossy::format("foobar{}narf", "hallo");

  std::cout << result << std::endl;
}
