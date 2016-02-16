#pragma once

/*
  format: {(align)(sign)(0)(width)(.precision)(type)}
  align: [>_]
  sign: [+ ]
  width: [0-9]+
  precision: [0-9]+
  type: [dobhfe]
*/

#include <algorithm>

namespace flossy {

// Used only for types that allow different representations, i.e. not for strings
enum class conversion_format {
  decimal,
  octal,
  binary,
  hex,
  normal_float,
  scientific_float,
  brace
};

enum class conversion_alignment {
  left,
  center,
  right
};

enum class conversion_positive_sign {
  none,
  plus,
  space
};

struct conversion_options {
  conversion_alignment alignment;
  conversion_positive_sign sign;
  bool zero_fill;
  int width;
  int precision;
  conversion_format format;
};

template<typename InputIterator>
conversion_alignment read_align(InputIterator *start, InputIterator end) {

}

template<typename InputIterator>
conversion_positive_sign read_sign(InputIterator *start, InputIterator end) {

}

template<typename InputIterator>
bool read_zero_fill(InputIterator *start, InputIterator end) {

}

template<typename InputIterator>
int read_width(InputIterator *start, InputIterator end) {

}

template<typename InputIterator>
int read_precision(InputIterator *start, InputIterator end) {

}

template<typename InputIterator>
conversion_format read_format(InputIterator *start, InputIterator end) {

}


template<typename InputIterator>
conversion_options read_conversion_options(InputIterator *start, InputIterator end) {
  return {
    read_align(start, end),
    read_sign(start, end),
    read_zero_fill(start, end),
    read_width(start, end),
    read_precision(start, end),
    read_format(start, end)
  };
}


template<typename OutputIterator, typename InputIterator>
void format(OutputIterator out, InputIterator start, InputIterator end) {
  std::copy(start, end, out);
}

template<typename OutputIterator, typename InputIterator, typename... ElementTypes>
void format(OutputIterator out, InputIterator start, InputIterator end, ElementTypes... elements) {
  while(start != end) {
    auto const c = *start;
    if(c == '{') {
      auto const options = read_conversion_options(&start, end);
    } else {
      *out = c;
    }
    ++start;
    ++out;
  }
}

}
