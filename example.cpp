#include "flossy.h"
#include <iostream>
#include <string>
#include <iterator>

int main() {

  flossy::format(std::cout, "A={}{20s}",
    u'c', "hallo"
    );
}
