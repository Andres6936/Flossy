#pragma once

#ifndef FLOSSY_FLOAT_METHOD
# define FLOSSY_FLOAT_METHOD FLOSSY_FLOAT_METHOD_SSTREAM
#endif

#define FLOSSY_FLOAT_METHOD_SSTREAM 0
#define FLOSSY_FLOAT_METHOD_FAST    1
#define FLOSSY_FLOAT_METHOD_GRISU   2

#include <iostream>
#include <iomanip>
#include <iterator>
#include <exception>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cstdint>
#include <cmath>
#include <limits>

/*
  format: {(align)(sign)(0)(width)(.precision)(type)}
  align: [>_<]
  sign: [+ ]
  width: [0-9]+
  precision: [0-9]+
  type: [doxfesb]
*/


namespace flossy {

class format_error: public std::invalid_argument {
public:
  using std::invalid_argument::invalid_argument;
};

// Used only for types that allow different representations, i.e. not for strings
enum class conversion_format {
  binary,
  decimal,
  octal,
  hex,
  normal_float,
  scientific_float,
  normal,
  string,
  character,
  fail
};

enum class fill_alignment {
  left,
  intern,
  right
};

enum class pos_sign_type {
  plus,
  space,
  none
};

struct conversion_options {
  conversion_format  format    = conversion_format::normal;
  int                width     = 0;
  int                precision = 6;
  fill_alignment     alignment = fill_alignment::left;
  pos_sign_type      pos_sign  = pos_sign_type::none;
  bool               zero_fill = false;

  conversion_options(conversion_format format = conversion_format::normal,
                     int width = 0, int precision = 6,
                     fill_alignment align = fill_alignment::left,
                     pos_sign_type pos_sign = pos_sign_type::none,
                     bool zero_fill = false)
    : format(format)
    , width(width)
    , precision(precision)
    , alignment(align)
    , pos_sign(pos_sign)
    , zero_fill(zero_fill) {}
};

namespace {

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

    const std::initializer_list<std::pair<char_type, fill_alignment>> alignment_types {
      {'>', fill_alignment::left},
      {'_', fill_alignment::intern},
      {'<', fill_alignment::right}
    };

    const std::initializer_list<std::pair<char_type, pos_sign_type>> sign_types {
      {'+', pos_sign_type::plus},
      {' ', pos_sign_type::space}
    };

    const std::initializer_list<std::pair<char_type, conversion_format>> format_types {
      {'b', conversion_format::binary},
      {'d', conversion_format::decimal},
      {'o', conversion_format::octal},
      {'x', conversion_format::hex},
      {'e', conversion_format::scientific_float},
      {'f', conversion_format::normal_float},
      {'s', conversion_format::string},
      {'c', conversion_format::character}
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

    /* Ensure the input iterator is not at the end of input */
    inline void check_it() const {
      ensure_not_equal(it, end);
    }

    /* Read a character from the input iterator, map it to one of the given values. */
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

    /* Read alignment of field */
    inline void read_align() {
      map_char(alignment_types, options.alignment);
    }

    /* Read zero-fill field */
    inline void read_fill() {
      check_it();
      if(*it == '0') {
        ++it;
        options.zero_fill = true;
      }
    }

    /* Read positive sign flag (none, space or plus) */
    inline void read_sign() {
      map_char(sign_types, options.pos_sign);
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


  /* Output string with space padding on the appropriate side */
  template<typename CharType, typename OutputIterator, typename InputIterator>
  OutputIterator format_string(OutputIterator out, conversion_options const& options, InputIterator start, InputIterator end) {
    int fill_count = options.width - (end - start);
    if(fill_count < 0) {
      fill_count = 0;
    }

    if(options.alignment == fill_alignment::left) {
      out = std::fill_n(out, fill_count, CharType(' '));
      out = std::copy(start, end, out);
    } else {
      out = std::copy(start, end, out);
      out = std::fill_n(out, fill_count, CharType(' '));
    }

    return out;
  }



  /* digit_buffer for integer conversions */
  template<typename CharType>
  constexpr CharType digit_chars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', 
                                        '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

  /* Convert format flag to number system base */
  template<typename ValueType>
  constexpr ValueType int_format_radix(conversion_format format) {
    switch(format) {
      case conversion_format::hex:
        return ValueType(16);
      case conversion_format::octal:
        return ValueType(8);
      case conversion_format::binary:
        return ValueType(2);
      default:
        return ValueType(10);
    }
  }

  // Holds the characters of a string with the appropriate size for all numbers
  template<typename CharType>
  struct digit_buffer {
    // This should be enough space for all integer types supported by the compiler, in binary representation
    // and thus for all integer types in all bases.
    std::array<CharType, std::numeric_limits<uintmax_t>::digits> digits;
    int count = 0;

    void insert(CharType c) {
      digits[count++] = c;
    }

    // Copy the characters to the output iterator
    template<typename OutputIterator>
    OutputIterator output(OutputIterator out) const {
      for(int i = count; i > 0; --i) {
        *out++ = digits[i-1];
      }
      return out;
    }
  };
  
  // Generate the digit characters for the given value
  template<typename CharType, typename ValueType>
  digit_buffer<CharType> generate_digits(ValueType value, conversion_format const& format) {
    digit_buffer<CharType> digits;

    const ValueType radix = int_format_radix<ValueType>(format);

    do {
      digits.insert(digit_chars<CharType>[value % radix]);
      value /= radix;
    } while(value);

    return digits;
  }

  // The sign character to output when formatting a number
  enum class sign_character {
    none,
    space,
    plus,
    minus
  };

  // Output the given sign to the iterator
  template<typename CharType, typename OutputIterator>
  OutputIterator output_sign(OutputIterator out, sign_character sign) {
    if(sign == sign_character::space) {
      *out++ = CharType(' ');
    } else if(sign == sign_character::plus) {
      *out++ = CharType('+');
    } else if(sign == sign_character::minus) {
      *out++ = CharType('-');
    }

    return out;
  }

  template<typename CharType, typename OutputIterator, typename DigitOutFunc>
  OutputIterator output_padded_with_sign(OutputIterator out, DigitOutFunc out_func, int digit_count, conversion_options const& options, sign_character sign) {
    int fill_count = options.width - digit_count - (sign == sign_character::none ? 0 : 1);
    if(fill_count < 0) {
      fill_count = 0;
    }

    auto fill = options.zero_fill ? CharType('0') : CharType(' ');

    if(options.alignment == fill_alignment::left) {
      out = std::fill_n(out, fill_count, fill);
      out = output_sign<CharType>(out, sign);
      out = out_func();
    } else if(options.alignment == fill_alignment::intern) {
      out = output_sign<CharType>(out, sign);
      out = std::fill_n(out, fill_count, fill);
      out = out_func();
    } else if(options.alignment == fill_alignment::right) {
      out = output_sign<CharType>(out, sign);
      out = out_func();
      out = std::fill_n(out, fill_count, fill);
    }

    return out;
  }


  // Format a decomposed integer with fill characters and sign
  template<typename OutputIterator, typename CharType>
  OutputIterator output_integer(OutputIterator out, digit_buffer<CharType> const& digits, conversion_options const& options, sign_character sign) {
    auto out_func = [&]() {
      return digits.output(out);
    };

    return output_padded_with_sign<CharType>(out, out_func, digits.count, options, sign);
  }

  // Get the sign character required to display the given sign
  // with the given representation of positive numbers.
  constexpr sign_character sign_from_format(bool neg, pos_sign_type pos) {
    if(neg) {
      return sign_character::minus;
    } else {
      switch(pos) {
        case pos_sign_type::plus:
          return sign_character::plus;
        case pos_sign_type::space:
          return sign_character::space;
        default:
          return sign_character::none;
      }
    }
  }

  // Format an unsigned integer without validity checks for given flags with given sign and options.
  template<typename CharType, typename OutputIterator, typename ValueType>
  typename std::enable_if<std::is_integral<ValueType>::value && std::is_unsigned<ValueType>::value, OutputIterator>::type
  format_integer_unchecked(OutputIterator out, ValueType value, bool negative, conversion_options const& options) {
    // Special case: Conversion to character requested
    if(options.format == conversion_format::character) {
      *out++ = CharType(value);
    } else {
      digit_buffer<CharType> digits = generate_digits<CharType>(value, options.format);
      
      out = output_integer(out, digits, options, sign_from_format(negative, options.pos_sign));
                           
    }

    return out;
  }

  // Format unsigned integer with checks for flag validity with given sign and options.
  template<typename CharType, typename OutputIterator, typename ValueType>
  typename std::enable_if<std::is_integral<ValueType>::value && std::is_unsigned<ValueType>::value, OutputIterator>::type
  format_integer(OutputIterator out, ValueType value, bool negative, conversion_options options) {
    if(options.alignment != fill_alignment::intern) {
      options.zero_fill = false;
    }

    return format_integer_unchecked<CharType>(out, value, negative, options);
  }

  // Absolute value of given value as the unsigned type with same width as input type (this allows
  // getting the absolute value of the lowest integer without overflow).
  template<typename ValueType>
  typename std::make_unsigned<ValueType>::type make_positive(ValueType value) {
    if(value >= 0) {
      return static_cast<typename std::make_unsigned<ValueType>::type>(value);
    } else {
      return ~(static_cast<typename std::make_unsigned<ValueType>::type>(value) - 1U);
    }
  }
}


/* String formatter for C-Strings */
template<typename CharType, typename OutputIterator>
OutputIterator format_element(OutputIterator out, conversion_options const& options, CharType const* value) {
  CharType const* end = value;
  while(*end != CharType('\0')) {
    ++end;
  }

  return format_string<CharType>(out, options, value, end);
}


/* String formatter for C++ strings */
template<typename CharType, typename OutputIterator>
OutputIterator format_element(OutputIterator out, conversion_options const& options, std::basic_string<CharType> const& value) {
  return format_string<CharType>(out, options, value.begin(), value.end());
}

template<typename OutputIterator, typename InputIterator>
OutputIterator format_it(OutputIterator out, InputIterator start, InputIterator const end) {
  // If there are not value left to convert, just copy the rest of the input.
  // Ignore further conversion specifiers.

  return std::copy(start, end, out);
}


// Formatter function for unsigned integers
template<typename CharType, typename OutputIterator, typename ValueType>
typename std::enable_if<std::is_integral<ValueType>::value && std::is_unsigned<ValueType>::value, OutputIterator>::type
format_element(OutputIterator out, conversion_options options, ValueType value) {
  return format_integer<CharType>(out, value, false, options);
}

// Formatter function for a signed integer. Converts the given number bitwise to an unsigned value
// if the requested conversion is _not_ decimal. For decimal, it passes the absolute value and sign bit
// appropriately.
template<typename CharType, typename OutputIterator, typename ValueType>
typename std::enable_if<std::is_integral<ValueType>::value && std::is_signed<ValueType>::value, OutputIterator>::type
format_element(OutputIterator out, conversion_options options, ValueType value) {
  if(options.format != conversion_format::normal and options.format != conversion_format::decimal) {
    return format_integer<CharType>(out, static_cast<typename std::make_unsigned<ValueType>::type>(value), false, options);
  } else {
    return format_integer<CharType>(out, make_positive(value), value < 0, options);
  }
}


// Formatter function for floating point numbers.
#if FLOSSY_FLOAT_METHOD == FLOSSY_FLOAT_METHOD_SSTREAM
  template<typename CharType, typename OutputIterator, typename ValueType>
  typename std::enable_if<std::is_floating_point<ValueType>::value, OutputIterator>::type
  format_element(OutputIterator out, conversion_options options, ValueType value) {
    if(options.alignment != fill_alignment::intern) {
      options.zero_fill = false;
    }

    // Format as char string, convert to wider character types later (in std::copy).
    // This works with char32_t, while using a basic_ostringstream<char32_t> doesn't.
    // I did not investigate further :)
    std::stringstream sstr;
    sstr.flags(options.format != conversion_format::scientific_float ? 
                 std::ios::fixed : std::ios::scientific);
    sstr.precision(options.precision);

    bool const neg = std::signbit(value);
    sstr << std::abs(value);

    auto out_func = [&]() {
      return std::copy(std::istreambuf_iterator<char>(sstr.rdbuf()), std::istreambuf_iterator<char>(), out);
    };

    return output_padded_with_sign<CharType>(out, out_func, sstr.tellp(), options, sign_from_format(neg, options.pos_sign));
  }

#elif FLOSSY_FLOAT_METHOD == FLOSSY_FLOAT_METHOD_FAST
  #error "Fast (and imprecise) float conversion not implemented, yet."
#elif FLOSSY_FLOAT_METHOD == FLOSSY_FLOAT_METHOD_GRISU
  #error "Grisu float conversion not implemented, yet."
#else
  #error "FLOSSY_FLOAT_METHOD must be defined as FLOSSY_FLOAT_METHOD_SSTREAM, FLOSSY_FLOAT_METHOD_FAST or FLOSSY_FLOAT_METHOD_GRISU"
#endif

/* Generic formatting function using interators */
template<typename OutputIterator, typename InputIterator, typename FirstElement, typename... ElementTypes>
OutputIterator format_it(OutputIterator out, InputIterator start, InputIterator const end, FirstElement const& first, ElementTypes... elements) {
  // Copy everything from start to the beginning of the first "real" (i.e. not '{{') conversion
  // specifier to out, transforming {{ into { appropriately.
  // Read conversion specifier, convert one element and recurse to format the rest.

  for(;start != end; ++start) {
    auto c = *start;

    if(c == '{') {
      ensure_not_equal(++start, end);

      if(*start != '{') {
        auto const options = option_reader<InputIterator>(start, end).options;
        format_element<typename std::iterator_traits<InputIterator>::value_type>(out, options, first);
        return format_it(out, start, end, elements...);
      }

      c = '{';
    } 

    *out++ = c;
  }

  return out;
}


/* Returns the formatted string */
template<typename CharType, typename... ElementTypes>
std::basic_string<CharType> format(std::basic_string<CharType> const & format_str, ElementTypes... elements) {
  std::basic_string<CharType> result;
  format_it(std::back_inserter(result), format_str.begin(), format_str.end(), elements...);
  return result;
}

template<typename CharType, typename... ElementTypes>
std::basic_string<CharType> format(CharType const* format_str, ElementTypes... elements) {
  return format(std::basic_string<CharType>(format_str), elements...);
}

/* Allows output formatting string directly to ostream, without extra buffering */
template<typename CharType, typename Traits, typename... ElementTypes>
void format(std::basic_ostream<CharType, Traits> &ostream, std::basic_string<CharType> const& format_str, ElementTypes... elements) {
  format_it(std::ostream_iterator<CharType, CharType>(ostream), format_str.begin(), format_str.end(), elements...);
}

template<typename CharType, typename Traits, typename... ElementTypes>
void format(std::basic_ostream<CharType, Traits> &ostream, CharType const* format_str, ElementTypes... elements) {
  format(ostream, std::basic_string<CharType>(format_str), elements...);
}

}
