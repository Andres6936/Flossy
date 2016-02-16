#pragma once

#include <regex>
#include <iterator>
#include <iostream>
#include <exception>

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
  brace,
  normal,
  fail
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
  conversion_format format;
  conversion_alignment alignment;
  conversion_positive_sign sign;
  bool zero_fill;
  int width;
  int precision;
};

template<typename CharT>
const std::basic_regex<CharT> conversion_regex;

class format_error: public std::invalid_argument {
public:
  using std::invalid_argument::invalid_argument;
};

template<typename InputIterator>
conversion_options read_conversion_options(InputIterator *start, InputIterator end) {
  typedef typename std::iterator_traits<InputIterator>::value_type char_type;

  static const std::basic_regex<char_type> conversion_regex("^([>_<]?)([-+ ]?)(0?)([0-9]*)(\\.([0-9]+))?([dobxfe]?)(?=\\})");

  std::match_results<InputIterator> match;
  bool matched = std::regex_search(*start, end, match, conversion_regex);

  if(!matched) {
    throw format_error("Invalid format string");
  }

  *start = match.suffix().first;
}

template<typename OutputIterator, typename ValueType>
void format_element(OutputIterator *out, conversion_options options, ValueType value) {
  **out = '<';
  ++(*out);
  **out = '>';
  ++(*out);
}


template<typename OutputIterator, typename InputIterator>
void format(OutputIterator out, InputIterator start, InputIterator end) {
  std::copy(start, end, out);
}

template<typename OutputIterator, typename InputIterator, typename FirstElement, typename... ElementTypes>
void format(OutputIterator out, InputIterator start, InputIterator end, FirstElement first, ElementTypes... elements) {
  while(start != end) {
    auto const c = *start;
    if(c == '{') {
      ++start;
      if(start != end) {
        if(*start == '{') {
          *out = '{';
          ++out;
        } else {
          auto const options = read_conversion_options(&start, end);
          ++start;
          format_element(&out, options, first);
          format(out, start, end, elements...);
          return;
        }
      } else {
        throw format_error("Invalid format string");
      }
    } else {
      *out = c;
      ++(*out);
    }

    ++start;
  }
}

template<typename... ElementTypes>
std::string format(std::string format_str, ElementTypes... elements) {
  std::string result;
  format(std::back_inserter(result), format_str.begin(), format_str.end(), elements...);
  return result;
}

}
