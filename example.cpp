#include "flossy.h"
#include <iostream>
#include <string>
#include <iterator>

int main() {

  std::string result = flossy::format("foobar{>+09.5f}narf{+5}", "hallo", "jaja");

  std::cout << result << std::endl;
}
