#include "flossy.h"
#include <iostream>
#include <string>
#include <iterator>

int main() {

  flossy::format(std::cout, "Hallo{>+08.2f}blu{<+08.3f}blub\n", 
  
  +1.5e2, 20.0, 30.0);
}
