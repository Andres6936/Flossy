#include "flossy.h"
#include <iostream>
#include <string>
#include <iterator>

int main() {

  flossy::format(std::cout, "Hallo{>+08.2f}blu{<+08.3f}blub\n", 
  
  0.1, 20.0, 30.0);
}
