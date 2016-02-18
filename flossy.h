#pragma once

#include <iostream>
#include <iterator>
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
    conversion_alignment     alignment = conversion_alignment::left;
    conversion_positive_sign sign      = conversion_positive_sign::none;
    bool                     zero_fill = false;
    int                      width     = 0;
    int                      precision = 0;
    conversion_format        format    = conversion_format::normal;
  };

  template<typename InputIterator>
  inline void ensure_not_equal(InputIterator const& a, InputIterator const& b) {
    if(a == b) {
      throw format_error("unterminated {");
    }
  }

  /* Helper class to parse the conversion options */
  template<typename InputIterator>
  class option_reader {
    typedef typename std::iterator_traits<InputIterator>::value_type char_type;

    const std::initializer_list<std::pair<char_type, conversion_alignment>> alignment_types {
      {'_', conversion_alignment::center},
      {'<', conversion_alignment::left},
      {'>', conversion_alignment::right}
    };

    const std::initializer_list<std::pair<char_type, conversion_positive_sign>> sign_types {
      {' ', conversion_positive_sign::space},
      {'+', conversion_positive_sign::plus},
      {'-', conversion_positive_sign::none}
    };

    const std::initializer_list<std::pair<char_type, conversion_format>> format_types {
      {'d', conversion_format::decimal},
      {'o', conversion_format::octal},
      {'b', conversion_format::binary},
      {'x', conversion_format::hex},
      {'f', conversion_format::normal_float},
      {'e', conversion_format::scientific_float}
    };

    InputIterator &it;
    InputIterator const end;
  public:
    inline option_reader(InputIterator &start, InputIterator const end)
      : it(start)
      , end(end) {
      read_options();  
    }

    conversion_options options;

    inline void check_it() const {
      ensure_not_equal(it, end);
    }

    template<typename ValueT>
    inline void map_char(std::initializer_list<std::pair<char_type, ValueT>> const& values, ValueT &out) {
      check_it();
      auto const c = *it;
      auto v = std::find_if(values.begin(), values.end(), [=](auto const& a){return a.first == c;});
      if(v != values.end()) {
        out = v->second;
        ++it;
      }
    }

    inline void read_align() {
      map_char(alignment_types, options.alignment);
    }

    inline void read_sign() {
      map_char(sign_types, options.sign);
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
      map_char(format_types, options.format);
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
        throw format_error("Invalid character in format string");
      }
      ++it;
    }
  };

  template<typename OutputIterator, typename ValueType>
  void format_element(OutputIterator &out, conversion_options const& options, ValueType value) {
    std::cout << int(options.alignment) << "\n"
      << int(options.sign) << "\n"
      << options.zero_fill << "\n"
      << options.width << "\n"
      << options.precision << "\n"
      << int(options.format) << std::endl;
  }

}

template<typename OutputIterator, typename InputIterator>
void format_it(OutputIterator out, InputIterator start, InputIterator const end) {
  // If there are not value left to convert, just copy the rest of the input.
  // Ignore further conversion specifiers.

  std::copy(start, end, out);
}

/* Generic formatting function using interators */
template<typename OutputIterator, typename InputIterator, typename FirstElement, typename... ElementTypes>
void format_it(OutputIterator out, InputIterator start, InputIterator const end, FirstElement const& first, ElementTypes... elements) {
  // Copy everything from start to the beginning of the first "real" (i.e. not '{{') conversion
  // specifier to out, transforming {{ into { appropriately.
  // Read conversion specifier, convert one element and recurse to format the rest.

  for(;start != end; ++start) {
    auto c = *start;

    if(c == '{') {
      ensure_not_equal(++start, end);

      if(*start != '{') {
        auto const options = option_reader<InputIterator>(start, end).options;
        format_element(out, options, first);
        return format_it(out, start, end, elements...);
      }

      c = '{';
    } 

    *out++ = c;
  }
}


/* Returns the formatted string */
template<typename CharT, typename... ElementTypes>
std::basic_string<CharT> format(std::basic_string<CharT> const & format_str, ElementTypes... elements) {
  std::basic_string<CharT> result;
  format_it(std::back_inserter(result), format_str.begin(), format_str.end(), elements...);
  return result;
}

template<typename CharT, typename... ElementTypes>
std::basic_string<CharT> format(CharT const* format_str, ElementTypes... elements) {
  return format(std::basic_string<CharT>(format_str), elements...);
}

/* Allows output formatting string directly to ostream, without extra buffering */
template<typename CharT, typename Traits, typename... ElementTypes>
void format(std::basic_ostream<CharT, Traits> &ostream, std::basic_string<CharT> const& format_str, ElementTypes... elements) {
  format_it(std::ostream_iterator<CharT>(ostream), format_str.begin(), format_str.end(), elements...);
}

template<typename CharT, typename Traits, typename... ElementTypes>
void format(std::basic_ostream<CharT, Traits> &ostream, CharT const* format_str, ElementTypes... elements) {
  format(ostream, std::basic_string<CharT>(format_str), elements...);
}

}
