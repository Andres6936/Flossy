#pragma once

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
  align: [>_]
  sign: [+ ]
  width: [0-9]+
  precision: [0-9]+
  type: [doxfes]
*/


namespace flossy {

class format_error: public std::invalid_argument {
public:
  using std::invalid_argument::invalid_argument;
};

namespace {
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
    int                width     = 0;
    int                precision = 6;
    fill_alignment     alignment = fill_alignment::left;
    conversion_format  format    = conversion_format::normal;
    pos_sign_type      pos_sign  = pos_sign_type::none;
    bool               prec_expl = false;
    bool               zero_fill = false;
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

    inline void read_fill() {
      check_it();
      if(*it == '0') {
        ++it;
        options.zero_fill = true;
      }
    }

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
        options.prec_expl = true;
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

  template<typename CharT, typename OutputIterator, typename InputIterator>
  void format_string(OutputIterator &out, conversion_options const& options, InputIterator start, InputIterator end) {
    int fill_count = options.width - (end - start);
    if(fill_count < 0) {
      fill_count = 0;
    }

    if(options.alignment == fill_alignment::left) {
      out = std::fill_n(out, fill_count, CharT(' '));
      out = std::copy(start, end, out);
    } else {
      out = std::copy(start, end, out);
      out = std::fill_n(out, fill_count, CharT(' '));
    }
  }

  template<typename CharT, typename OutputIterator>
  void format_element(OutputIterator &out, conversion_options const& options, CharT const* value) {
    CharT const* end = value;
    while(*end != CharT('\0')) {
      ++end;
    }

    format_string<CharT>(out, options, value, end);
  }

  template<typename CharT, typename OutputIterator>
  void format_element(OutputIterator &out, conversion_options const& options, std::basic_string<CharT> const& value) {
    format_string<CharT>(out, options, value.begin(), value.end());
  }

  template<typename CharT>
  constexpr CharT digit_chars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', 
                                     '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};


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

  // This should be enough space for all integer types supported by the compiler, in binary representation
  template<typename CharT>
  struct Digits {
    std::array<CharT, std::numeric_limits<uintmax_t>::digits> digits;
    int count = 0;

    void insert(CharT c) {
      digits[count++] = c;
    }

    template<typename OutputIterator>
    OutputIterator output(OutputIterator out) const {
      for(int i = count; i > 0; --i) {
        *out++ = digits[i-1];
      }
      return out;
    }
  };
  

  template<typename CharT, typename ValueType>
  Digits<CharT> generate_digits(ValueType value, conversion_format const& format) {
    Digits<CharT> digits;

    const ValueType radix = int_format_radix<ValueType>(format);

    do {
      digits.insert(digit_chars<CharT>[value % radix]);
      value /= radix;
    } while(value);

    return digits;
  }


  enum class Sign {
    none,
    space,
    plus,
    minus
  };

  template<typename CharT, typename OutputIterator>
  OutputIterator output_sign(OutputIterator out, Sign sign) {
    if(sign == Sign::space) {
      *out++ = CharT(' ');
    } else if(sign == Sign::plus) {
      *out++ = CharT('+');
    } else if(sign == Sign::minus) {
      *out++ = CharT('-');
    }

    return out;
  }

  template<typename OutputIterator, typename CharT>
  OutputIterator output_integer(OutputIterator out, Digits<CharT> const& digits, CharT fill, Sign sign, fill_alignment fill_align, int width) {
    
    /*
      result         fill_align  fill  sign   valid
      "+000001234"   intern      '0'   plus   yes
      "-000001234"   intern      '0'   minus  yes
      " 000001234"   intern      '0'   space  yes
      "0000001234"   intern      '0'   none   yes
      "+     1234"   intern      ' '   plus   yes
      "-     1234"   intern      ' '   minus  yes
      "      1234"   intern      ' '   space  yes
      "      1234"   intern      ' '   none   yes

      "00000+1234"   left        '0'   plus   no
      "00000-1234"   left        '0'   minus  no
      "00000 1234"   left        '0'   space  no
      "0000001234"   left        '0'   none   yes
      "+     1234"   left        ' '   plus   yes
      "-     1234"   left        ' '   minus  yes
      "      1234"   left        ' '   space  yes
      "      1234"   left        ' '   none   yes

      "+123400000"   right       '0'   plus   no
      "-123400000"   right       '0'   minus  no
      " 123400000"   right       '0'   space  no
      "1234000000"   right       '0'   none   yes (for fraction part of float formatting)
      "+1234     "   right       ' '   plus   yes
      "-1234     "   right       ' '   minus  yes
      " 1234     "   right       ' '   space  yes
      "1234      "   right       ' '   none   yes
     */

    int fill_count = width - digits.count - (sign == Sign::none ? 0 : 1);
    if(fill_count < 0) {
      fill_count = 0;
    }

    if(fill_align == fill_alignment::left) {
      out = std::fill_n(out, fill_count, fill);
      out = output_sign<CharT>(out, sign);
      out = digits.output(out);
    } else if(fill_align == fill_alignment::intern) {
      out = output_sign<CharT>(out, sign);
      out = std::fill_n(out, fill_count, fill);
      out = digits.output(out);
    } else if(fill_align == fill_alignment::right) {
      out = output_sign<CharT>(out, sign);
      out = digits.output(out);
      out = std::fill_n(out, fill_count, fill);
    }

    return out;
  }


  constexpr Sign sign_from_format(bool neg, pos_sign_type pos) {
    if(neg) {
      return Sign::minus;
    } else {
      switch(pos) {
        case pos_sign_type::plus:
          return Sign::plus;
        case pos_sign_type::space:
          return Sign::space;
        case pos_sign_type::none:
          return Sign::none;
      }
    }
  }

  template<typename CharT, typename OutputIterator, typename ValueType>
  typename std::enable_if<std::is_integral<ValueType>::value && std::is_unsigned<ValueType>::value>::type
  format_integer_unchecked(OutputIterator &out, ValueType value, bool negative, conversion_options const& options) {
    if(options.format == conversion_format::character) {
      *out++ = CharT(value);
    } else {
      Digits<CharT> digits = generate_digits<CharT>(value, options.format);
      
      out = output_integer(out, digits, options.zero_fill ? CharT('0') : CharT(' '),
                           sign_from_format(negative, options.pos_sign),
                           options.alignment, options.width);
    }
  }

  template<typename CharT, typename OutputIterator, typename ValueType>
  typename std::enable_if<std::is_integral<ValueType>::value && std::is_unsigned<ValueType>::value>::type
  format_integer(OutputIterator &out, ValueType value, bool negative, conversion_options options) {
    if(options.alignment != fill_alignment::intern) {
      options.zero_fill = false;
    }

    format_integer_unchecked<CharT>(out, value, negative, options);
  }


  template<typename CharT, typename OutputIterator, typename ValueType>
  typename std::enable_if<std::is_integral<ValueType>::value && std::is_unsigned<ValueType>::value>::type
  format_element(OutputIterator &out, conversion_options options, ValueType value) {
    format_integer<CharT>(out, value, false, options);
  }

  template<typename ValueType>
  typename std::make_unsigned<ValueType>::type make_positive(ValueType value) {
    if(value >= 0) {
      return static_cast<typename std::make_unsigned<ValueType>::type>(value);
    } else {
      return ~(static_cast<typename std::make_unsigned<ValueType>::type>(value) - 1U);
    }
  }


  template<typename CharT, typename OutputIterator, typename ValueType>
  typename std::enable_if<std::is_integral<ValueType>::value && std::is_signed<ValueType>::value>::type
  format_element(OutputIterator &out, conversion_options options, ValueType value) {
    if(options.format != conversion_format::normal and options.format != conversion_format::decimal) {
      format_integer<CharT>(out, static_cast<typename std::make_unsigned<ValueType>::type>(value), false, options);
    } else {
      format_integer<CharT>(out, make_positive(value), value < 0, options);
    }
  }

  template<typename CharT, typename OutputIterator, typename ValueType>
  typename std::enable_if<std::is_floating_point<ValueType>::value>::type
  format_element(OutputIterator &out, conversion_options const& options, ValueType value) {
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
        format_element<typename std::iterator_traits<InputIterator>::value_type>(out, options, first);
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
