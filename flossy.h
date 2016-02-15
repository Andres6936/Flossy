#pragma once

namespace flossy {

template<typename OutputIterator, typename InputIterator, typename... ElementTypes>
void log(OutputIterator out, InputIterator start, InputIterator end, ElementTypes... elements) {
  while(start != end) {
    if(*start == '{') {
      
    }
  }
}

}
