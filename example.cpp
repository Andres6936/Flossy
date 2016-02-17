#include "flossy.h"
#include <iostream>
#include <string>
#include <iterator>

int main() {

  std::string result = flossy::format("foobar{>+09.3f}narf", "hallo");

  std::cout << result << std::endl;
}
