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
  conversion_alignment alignment = conversion_alignment::left;
  conversion_positive_sign sign = conversion_positive_sign::none;
  bool zero_fill = false;
  int width = 0;
  int precision = 0;
  conversion_format format = conversion_format::normal;
};

template<typename CharT>
const std::basic_regex<CharT> conversion_regex;

class format_error: public std::invalid_argument {
public:
  using std::invalid_argument::invalid_argument;
};

/*
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
*/



template<typename InputIterator>
conversion_options read_conversion_options(InputIterator &it, InputIterator end) {
  conversion_options options;

  enum class step_name {
    align, sign, fill, width, precision_dot, precision_read, format, close
  };

  step_name step = step_name::align;
  while(it != end) {
    auto const c = *it;
    switch(step) {
    case step_name::align:
      switch(c) {
      case '_':
        options.alignment = conversion_alignment::center;
        ++it;
        break;
      case '>':
        options.alignment = conversion_alignment::right;
        ++it;
        break;
      case 'y':
        ++it;
      }
      step = step_name::sign;
      break;

    case step_name::sign:
      switch(c) {
      case ' ':
        options.sign = conversion_positive_sign::space;
        ++it;
        break;
      case '+':
        options.sign = conversion_positive_sign::plus;
        ++it;
        break;
      case '-':
        ++it;
      }
      step = step_name::fill;
      break;

    case step_name::fill:
      if(c == '0') {
        ++it;
        options.zero_fill = true;
      }
      step = step_name::width;
      break;

    case step_name::width:
      if(c >= '0' && c <= '9') {
        options.width = options.width * 10 + (c - '0');
        ++it;
      } else {
        step = step_name::precision_dot;
      }
      break;

    case step_name::precision_dot:
      if(c == '.') {
        step = step_name::precision_read;
        ++it;
      } else {
        // skip precision, recheck current char
        step = step_name::format;
      }
      break;

    case step_name::precision_read:
      if(c >= '0' && c <= '9') {
        options.precision = options.precision * 10 + (c - '0');
        ++it;
      } else {
        step = step_name::format;
      }
      break;

    case step_name::format:
      switch(c) {
      case 'd':
        options.format = conversion_format::decimal;
        ++it;
        break;
      case 'o':
        options.format = conversion_format::octal;
        ++it;
        break;
      case 'b':
        options.format = conversion_format::binary;
        ++it;
        break;
      case 'x':
        options.format = conversion_format::hex;
        ++it;
        break;
      case 'f':
        options.format = conversion_format::normal_float;
        ++it;
        break;
      case 'e':
        options.format = conversion_format::scientific_float;
        ++it;
        break;
      default:
        step = step_name::close;
      }
      break;

    case step_name::close:
      if(c == '}') {
        ++it;
        return options;
      } else {
        throw format_error(std::string("Invalid character in format string: '") + c + "'");
      }
      break;
    }
  }
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
          auto format_end = std::find(start, end, '}');
          if(format_end == end) {
            //throw format_error("Missing } in format string");
          }
          auto const options = read_conversion_options(start, format_end);
          start = format_end;
          ++start;
          format_element(&out, options, first);
          format(out, start, end, elements...);
          return;
        }
      } else {
        //throw format_error("Invalid format string");
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
