#pragma once

#include <iterator>
#include <iostream>
#include <exception>
#include <algorithm>

/*
  format: {(align)(sign)(0)(width)(.precision)(type)}
  align: [>_]
  sign: [+ ]
  width: [0-9]+
  precision: [0-9]+
  type: [dobxfe]
*/


namespace flossy {

class format_error: public std::invalid_argument {
public:
  using std::invalid_argument::invalid_argument;
};

namespace {
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

  template<typename IteratorType, typename CharT, typename ValueT>
   inline void map_char(IteratorType &it, std::initializer_list<std::pair<CharT, ValueT>> const& values, ValueT &out) noexcept {
    auto const c = *it;
    auto v = std::find_if(values.begin(), values.end(), [=](auto const& a){return a.first == c;});
    if(v != values.end()) {
      out = v->second;
      ++it;
    }
  }

  template<typename CharT>
  const std::initializer_list<std::pair<CharT, conversion_alignment>> alignment_types 
  {
    {'_', conversion_alignment::center},
    {'<', conversion_alignment::left},
    {'>', conversion_alignment::right}
  };

  template<typename CharT>
  const std::initializer_list<std::pair<CharT, conversion_positive_sign>> sign_types {
    {' ', conversion_positive_sign::space},
    {'+', conversion_positive_sign::plus},
    {'-', conversion_positive_sign::none}
  };

  template<typename CharT>
  const std::initializer_list<std::pair<CharT, conversion_format>> format_types {
    {'d', conversion_format::decimal},
    {'o', conversion_format::octal},
    {'b', conversion_format::binary},
    {'x', conversion_format::hex},
    {'f', conversion_format::normal_float},
    {'e', conversion_format::scientific_float}
  };

  /* Helper class to parse the conversion options */
  template<typename InputIterator>
  class option_reader {
    typedef typename std::iterator_traits<InputIterator>::value_type char_type;
    InputIterator it;
    InputIterator end;
  public:
    inline option_reader(InputIterator start, InputIterator end)
      : it(start)
      , end(end) {
      read_options();  
    }

    conversion_options options;

    inline void check_it() const {
      if(it == end) {
        throw format_error("unterminated {");
      }
    }

    inline void read_align() {
      check_it();
      map_char(it, alignment_types<char_type>, options.alignment);
    }

    inline void read_sign() {
      check_it();
      map_char(it, sign_types<char_type>, options.sign);
    }

    inline void read_fill() {
      check_it();
      if(*it == '0') {
        ++it;
        options.zero_fill = true;
      }
    }

    inline int read_number() {
      int v = 0;
      for(;;) {
        check_it();
        auto const c = *it;
        if(c >= '0' && c <= '9') {
          v = v * 10 + (c - '0');
          ++it;
        } else {
          return v;
        }
      }
    }

    inline void read_width() {
      options.width = read_number();
    }

    inline void read_precision() {
      check_it();
      if(*it == '.') {
        ++it;
        options.precision = read_number();
      }
    }

    inline void read_format() {
      check_it();
      map_char(it, format_types<char_type>, options.format);
    }

    inline void read_options() {
      read_align();
      read_sign();
      read_fill();
      read_width();
      read_precision();
      read_format();

      check_it();
      if(*it != '}') {
        throw format_error(std::string("Invalid character in format string: '") + (*it) + "'");
      }
    }

  };

  template<typename InputIterator>
  inline conversion_options read_conversion_options(InputIterator &it, InputIterator end) {
    return option_reader<InputIterator>(it, end).options;
  }

  template<typename OutputIterator, typename ValueType>
  void format_element(OutputIterator *out, conversion_options options, ValueType value) {
    std::cout << int(options.alignment) << "\n"
      << int(options.sign) << "\n"
      << options.zero_fill << "\n"
      << options.width << "\n"
      << options.precision << "\n"
      << int(options.format) << std::endl;

  }
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
            throw format_error("Missing } in format string");
          }
          ++format_end;
          auto const options = option_reader<InputIterator>(start, format_end).options;
          start = format_end;
          format_element(&out, options, first);
          format(out, start, end, elements...);
          return;
        }
      } else {
        throw format_error("Missing } in format string");
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
