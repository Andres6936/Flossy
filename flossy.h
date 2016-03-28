/*
    flossy

    Copyright (C) 2016 Florian Kesseler

    This project is free software; you can redistribute it and/or modify it
    under the terms of the MIT license. See LICENSE.md for details.
*/





/*
  Format strings cosist of any character sequence containing any number of
  conversion specifiers.

  Conversion specifiers are delimited by curly braces containing the format
  specification:

  format: [align][sign][0][width][.precision][type]
  align: '>' | '_' | '<'
  sign: '+' | ' ' | '-'
  width: integer
  precision: integer
  type: 'd', 'o', 'x', 'f', 'e', 's', 'b'

  'align' specifies where in the resulting field the value will be aligned, as
  described in the following table:

  Option   Description
       >   Align the value to the right of the field (i.e. put spaces left of
           the resulting value). If this option is used, the zero flag is
           ignored. This is the default option.
       <   Align the value to the left of the field (i.e put spaces right of
           the resulting value.  If this option is used, the zero flag is
           ignored.
       _   Let the value fill the whole field by putting spaces or zeroes
           between the digits and the sign.  This is the only option that
           respects the zero flag.


  'sign' specifies how positive numbers should be displayed, as described in
  the following table:

  Option   Description
       -   Only display the sign of negative numbers. This is the default
           option.
       +   Positive numbers will be displayed with a plus sign ('+') in front
           of them.
 <space>   Positive numbers will be displayed with a space in front of them to
           align them with negative numbers.

 
  The 'zero' flag ('0'), if present, makes numbers displayed with internal
  alignment (the '_' align option) use a zero ('0') character instead of spaces
  to fill the gap between numbers and sign.

  'width' specifies the minimum width of the field. If this is larger than the
  width of the converted value, the value will be aligned and padded according
  to the 'align' and 'zero' flags.

  'precision' specifies the number of digits in the fractional part of floating
  point numbers.

  'type' specifies the formatting method used. This is basically used to change
  the display type of numbers, like the number base or float representation
  (scientific vs. fixed width) and is ignored if it doesn't make sense for the
  field currently converted.

*/


#ifndef FLOSSY_H_INCLUDED
#define FLOSSY_H_INCLUDED


#ifndef FLOSSY_FLOAT_METHOD
# define FLOSSY_FLOAT_METHOD FLOSSY_FLOAT_METHOD_SSTREAM
#endif

#define FLOSSY_FLOAT_METHOD_SSTREAM 0
#define FLOSSY_FLOAT_METHOD_FAST    1 // not implemented, yet
#define FLOSSY_FLOAT_METHOD_GRISU   2 // not implemented, yet

#include <array>
#include <iterator>
#include <exception>
#include <algorithm>
#include <sstream>
#include <cassert>
#include <cstdint>
#include <limits>


namespace flossy {

struct version_number {
  int major;
  int minor;
};


constexpr version_number version()
{
  return {1, 0};
}


class format_error: public std::invalid_argument {
public:
  using std::invalid_argument::invalid_argument;
};


// Used only for types that allow different representations, i.e. not for
// strings.
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


// Where to put zeroes and spaces when filling up a field to width.
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

  conversion_options(
      conversion_format format = conversion_format::normal, int width = 0, int precision = 6,
      fill_alignment align = fill_alignment::left, pos_sign_type pos_sign = pos_sign_type::none, bool zero_fill = false)
    : format(format)
    , width(width)
    , precision(precision)
    , alignment(align)
    , pos_sign(pos_sign)
    , zero_fill(zero_fill) {}
};


namespace {
  template<typename InputIterator>
  inline void ensure_not_equal(InputIterator const& a, InputIterator const& b)
  {
    if(a == b) {
      throw format_error("unterminated {");
    }
  }

  // Helper class to parse the conversion options
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
      {' ', pos_sign_type::space},
      {'-', pos_sign_type::none}
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
    conversion_options options;

    inline option_reader(InputIterator &start, InputIterator const end)
      : it(start)
      , end(end)
    {
      read_options();  
    }


    // Ensure the input iterator is not at the end of input.
    inline void check_it() const
    {
      ensure_not_equal(it, end);
    }


    // Read a character from the input iterator, map it to one of the given values.
    template<typename ValueT>
    inline void map_char(std::initializer_list<std::pair<char_type, ValueT>> const& values, ValueT &out)
    {
      check_it();
      auto const c = *it;
      auto v = std::find_if(values.begin(), values.end(), [=](auto const& a){return a.first == c;});
      if(v != values.end()) {
        out = v->second;
        ++it;
      }
    }


    // Read alignment of field
    inline void read_align()
    {
      map_char(alignment_types, options.alignment);
    }


    // Read zero-fill field
    inline void read_fill()
    {
      check_it();
      if(*it == '0') {
        ++it;
        options.zero_fill = true;
      }
    }


    // Read positive sign flag (none, space or plus)
    inline void read_sign()
    {
      map_char(sign_types, options.pos_sign);
    }


    inline int read_number()
    {
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


    inline void read_width()
    {
      options.width = read_number();
    }


    inline void read_precision()
    {
      check_it();
      if(*it == '.') {
        ++it;
        options.precision = read_number();
      }
    }


    inline void read_format()
    {
      map_char(format_types, options.format);
    }


    inline void read_options()
    {
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


  // Output string with space padding on the appropriate side
  template<typename CharT, typename OutIt, typename InputIterator>
  OutIt format_string(OutIt out, conversion_options const& options, InputIterator start, InputIterator end)
  {
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

    return out;
  }


  // Digits for integer conversions
  template<typename CharT>
  constexpr CharT digit_chars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};


  // Convert format flag to number system base
  template<typename ValueT>
  constexpr ValueT int_format_radix(conversion_format format)
  {
    switch(format) {
      case conversion_format::hex:
        return ValueT(16);
      case conversion_format::octal:
        return ValueT(8);
      case conversion_format::binary:
        return ValueT(2);
      default:
        return ValueT(10);
    }
  }


  // Holds the characters of a string with the appropriate size for all numbers
  template<typename CharT>
  struct digit_buffer {
    // This should be enough space for all integer types supported by the
    // compiler, in binary representation and thus for all integer types in all
    // bases.
    std::array<CharT, std::numeric_limits<uintmax_t>::digits> digits;
    int count = 0;

    
    // Insert character into buffer.
    void insert(CharT c)
    {
      digits[count++] = c;
    }


    // Copy the accumulated characters to the output iterator
    template<typename OutIt>
    OutIt output(OutIt out) const
    {
      for(int i = count; i > 0; --i) {
        *out++ = digits[i-1];
      }
      return out;
    }
  };


  // Generate the digit characters for the given unsigned value
  template<typename CharT, typename ValueT>
  digit_buffer<CharT> generate_digits(ValueT value, conversion_format const& format)
  {
    static_assert(std::is_unsigned<ValueT>::value, "ValueT must be unsigned in generate_digits");

    digit_buffer<CharT> digits;

    const ValueT radix = int_format_radix<ValueT>(format);

    do {
      digits.insert(digit_chars<CharT>[value % radix]);
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
  template<typename CharT, typename OutIt>
  OutIt output_sign(OutIt out, sign_character sign)
  {
    if(sign == sign_character::space) {
      *out++ = CharT(' ');
    } else if(sign == sign_character::plus) {
      *out++ = CharT('+');
    } else if(sign == sign_character::minus) {
      *out++ = CharT('-');
    }

    return out;
  }


  // Output values given by out_func to the output iterator and add padding and
  // sign characters. 
  template<typename CharT, typename OutIt, typename DigitOutFunc>
  OutIt output_padded_with_sign(
      OutIt out, DigitOutFunc out_func, int digit_count, conversion_options const& options, sign_character sign)
  {
    int fill_count = options.width - digit_count - (sign == sign_character::none ? 0 : 1);

    if(fill_count < 0) {
      fill_count = 0;
    }

    auto fill = options.zero_fill ? CharT('0') : CharT(' ');

    if(options.alignment == fill_alignment::left) {
      out = std::fill_n(out, fill_count, fill);
      out = output_sign<CharT>(out, sign);
      out = out_func();
    } else if(options.alignment == fill_alignment::intern) {
      out = output_sign<CharT>(out, sign);
      out = std::fill_n(out, fill_count, fill);
      out = out_func();
    } else if(options.alignment == fill_alignment::right) {
      out = output_sign<CharT>(out, sign);
      out = out_func();
      out = std::fill_n(out, fill_count, fill);
    }

    return out;
  }


  // Format a decomposed integer with fill characters and sign
  template<typename OutIt, typename CharT>
  OutIt output_integer(
      OutIt out, digit_buffer<CharT> const& digits, conversion_options const& options, sign_character sign)
  {
    auto out_func = [&]() {
      return digits.output(out);
    };

    return output_padded_with_sign<CharT>(out, out_func, digits.count,
                                             options, sign);
  }


  // Get the sign character required to display the given sign with the given
  // representation of positive numbers
  constexpr sign_character sign_from_format(bool neg, pos_sign_type pos)
  {
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


  // Format an unsigned integer without validity checks for given flags with
  // given sign and options.
  template<typename CharT, typename OutIt, typename ValueT>
  typename std::enable_if<std::is_integral<ValueT>::value && std::is_unsigned<ValueT>::value, OutIt>::type
  format_integer_unchecked(OutIt out, ValueT value, bool negative, conversion_options const& options)
  {
    // Special case: Conversion to character requested
    if(options.format == conversion_format::character) {
      *out++ = CharT(value);
    } else {
      digit_buffer<CharT> digits = generate_digits<CharT>(value, options.format);
      
      out = output_integer(out, digits, options, sign_from_format(negative, options.pos_sign));
                           
    }

    return out;
  }


  // Format unsigned integer with checks for flag validity with given sign and options.
  template<typename CharT, typename OutIt, typename ValueT>
  typename std::enable_if<std::is_integral<ValueT>::value && std::is_unsigned<ValueT>::value, OutIt>::type
  format_integer(OutIt out, ValueT value, bool negative, conversion_options options)
  {
    if(options.alignment != fill_alignment::intern) {
      options.zero_fill = false;
    }

    return format_integer_unchecked<CharT>(out, value, negative, options);
  }


  // Absolute value of given value as the unsigned type with same width as
  // input type (this allows // getting the absolute value of the lowest integer
  // without overflow).
  template<typename ValueT>
  typename std::make_unsigned<ValueT>::type make_positive(ValueT value)
  {
    if(value >= 0) {
      return static_cast<typename std::make_unsigned<ValueT>::type>(value);
    } else {
      return ~(static_cast<typename std::make_unsigned<ValueT>::type>(value) - 1U);
    }
  }
}


// String formatter for C-Strings
template<typename CharT, typename OutIt>
OutIt format_element(OutIt out, conversion_options const& options, CharT const* value)
{
  CharT const* end = value;
  while(*end != CharT('\0')) {
    ++end;
  }

  return format_string<CharT>(out, options, value, end);
}


// String formatter for C++ strings
template<typename CharT, typename OutIt>
OutIt format_element(OutIt out, conversion_options const& options, std::basic_string<CharT> const& value)
{
  return format_string<CharT>(out, options, value.begin(), value.end());
}


// If there are not value left to convert, just copy the rest of the input.
// Ignore further conversion specifiers.
template<typename OutIt, typename InputIterator>
OutIt format_it(OutIt out, InputIterator start, InputIterator const end)
{
  return std::copy(start, end, out);
}


// Formatter function for unsigned integers
template<typename CharT, typename OutIt, typename ValueT>
typename std::enable_if<std::is_integral<ValueT>::value && std::is_unsigned<ValueT>::value, OutIt>::type
format_element(OutIt out, conversion_options options, ValueT value)
{
  return format_integer<CharT>(out, value, false, options);
}


// Formatter function for a signed integer. Converts the given number bitwise to
// an unsigned value if the requested conversion is _not_ decimal. For decimal,
// it passes the absolute value and sign bit appropriately
template<typename CharT, typename OutIt, typename ValueT>
typename std::enable_if<std::is_integral<ValueT>::value && std::is_signed<ValueT>::value, OutIt>::type
format_element(OutIt out, conversion_options options, ValueT value)
{
  if(options.format != conversion_format::normal and options.format != conversion_format::decimal) {
    return format_integer<CharT>(out, static_cast<typename std::make_unsigned<ValueT>::type>(value), false, options);
  } else {
    return format_integer<CharT>(out, make_positive(value), value < 0, options);
  }
}


// Formatter function for floating point numbers.

#if FLOSSY_FLOAT_METHOD == FLOSSY_FLOAT_METHOD_SSTREAM
  // This method used C++ string streams to convert float values. That means it
  // is precise and easy to implement. String streams use dynamic memory though,
  // so it may have unpredictable timing and be slower than other alternatives.

  template<typename CharT, typename OutIt, typename ValueT>
  typename std::enable_if<std::is_floating_point<ValueT>::value, OutIt>::type
  format_element(OutIt out, conversion_options options, ValueT value)
  {
    if(options.alignment != fill_alignment::intern || std::isinf(value)) {
      options.zero_fill = false;
    }

    if(std::isnan(value)) {
      options.zero_fill = false;
      if(options.pos_sign == pos_sign_type::plus) {
        options.pos_sign = pos_sign_type::space;
      }
    }


    // Format as char string, convert to wider character types later (in std::copy).
    // This works with char32_t, while using a basic_ostringstream<char32_t> doesn't.
    // I did not investigate further, why it doesn't work. :)
    std::stringstream sstr;
    sstr.precision(options.precision);
    sstr.flags(
      options.format != conversion_format::scientific_float 
        ? std::ios::fixed
        : std::ios::scientific
    );
    sstr << std::abs(value);

    auto out_func = [&]() {
      return std::copy(std::istreambuf_iterator<char>(sstr.rdbuf()), std::istreambuf_iterator<char>(), out);
    };

    bool const neg = std::signbit(value);
    return output_padded_with_sign<CharT>(out, out_func, sstr.tellp(), options,
                                          sign_from_format(neg, options.pos_sign));
  }

#elif FLOSSY_FLOAT_METHOD == FLOSSY_FLOAT_METHOD_FAST
  #error "Fast (and imprecise) float conversion not implemented, yet."
#elif FLOSSY_FLOAT_METHOD == FLOSSY_FLOAT_METHOD_GRISU
  #error "Grisu float conversion not implemented, yet."
#else
  #error "FLOSSY_FLOAT_METHOD undefined."
#endif


// Generic formatting function using interators
template<typename OutIt, typename InputIterator, typename FirstElement, typename... ElementTypes>
OutIt format_it(
  OutIt out, InputIterator start, InputIterator const end, FirstElement const& first,ElementTypes... elements)
{
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


// Returns the formatted string
template<typename CharT, typename... ElementTypes>
std::basic_string<CharT> format(std::basic_string<CharT> const & format_str, ElementTypes... elements)
{
  std::basic_string<CharT> result;
  format_it(std::back_inserter(result), format_str.begin(), format_str.end(), elements...);
  return result;
}


template<typename CharT, typename... ElementTypes>
std::basic_string<CharT> format(CharT const* format_str, ElementTypes... elements)
{
  return format(std::basic_string<CharT>(format_str), elements...);
}


// Allows output formatting string directly to ostream, without extra buffering
template<typename CharT, typename Traits, typename... ElementTypes>
void format(std::basic_ostream<CharT, Traits> &ostream, std::basic_string<CharT> const& format_str, ElementTypes... elements)
{
  format_it(std::ostream_iterator<CharT, CharT>(ostream), format_str.begin(), format_str.end(), elements...);
}


template<typename CharT, typename Traits, typename... ElementTypes>
void format(std::basic_ostream<CharT, Traits> &ostream, CharT const* format_str, ElementTypes... elements)
{
  format(ostream, std::basic_string<CharT>(format_str), elements...);
}

}

#endif
