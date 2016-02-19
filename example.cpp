#include "flossy.h"
#include <iostream>
#include <string>
#include <iterator>

int main() {

  flossy::format(std::cout, "Hallo{>+020.2f}blu{<+08.3f}blub\n", 1.5e2, 20, 30);
}
