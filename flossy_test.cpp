#include <typeinfo>
#include <string>
#include <iterator>
#include "flossy.h"

int testcount = 0;
int failed = 0;

// This just truncates wider character types, but that's okay for these tests, because w
// only use the ASCII range. We just want to know if it works for all character types
template<typename CharT1, typename CharT2>
std::basic_string<CharT1> cheaty_cast_string(std::basic_string<CharT2> str) {
  return std::basic_string<CharT1>(str.begin(), str.end());
}


template<typename CharT1, typename CharT2>
std::basic_string<CharT1> cheaty_cast_string(CharT2 const* str) {
  return cheaty_cast_string<CharT1>(std::basic_string<CharT2>(str));
}


// Use char-based strings for expect and format, we'll widen them appropriately.
// This allows writing the test cases in a simpler way.
template<typename CharT, typename... Args>
void test_format_it(std::string expect, std::string format, Args... args) {
  auto conv_expect = cheaty_cast_string<CharT>(expect);
  auto conv_format = cheaty_cast_string<CharT>(format);

  std::basic_string<CharT> output;
  flossy::format_it(std::back_inserter(output), conv_format.begin(), conv_format.end(), args...);

  ++testcount;

  if(output != conv_expect) {
    std::cout << "Test failed (" << typeid(CharT).name() << "): " << format << "\": \"" << cheaty_cast_string<char>(output) << "\" != \"" << expect << "\")\n";
    ++failed;
  }
}


template<typename CharType>
void test_fixed_float_alignment() {
  // Alignment of negative floats (fixed)
  test_format_it<CharType>("     -42.133724", "{15f}",   -42.133724f);
  test_format_it<CharType>("     -42.133724", "{>15f}",  -42.133724f);
  test_format_it<CharType>("-     42.133724", "{_15f}",  -42.133724f);
  test_format_it<CharType>("-42.133724     ", "{<15f}",  -42.133724f);

  // Alignment of negative floats with 0 fill (fixed)
  test_format_it<CharType>("     -42.133724", "{015f}",   -42.133724f);
  test_format_it<CharType>("     -42.133724", "{>015f}",  -42.133724f);
  test_format_it<CharType>("-0000042.133724", "{_015f}",  -42.133724f);
  test_format_it<CharType>("-42.133724     ", "{<015f}",  -42.133724f);

  // Alignment of positive floats with plus sign (fixed)
  test_format_it<CharType>("     +42.133724", "{+15f}",   42.133724f);
  test_format_it<CharType>("     +42.133724", "{>+15f}",  42.133724f);
  test_format_it<CharType>("+     42.133724", "{_+15f}",  42.133724f);
  test_format_it<CharType>("+42.133724     ", "{<+15f}",  42.133724f);

  // Alignment of negative floats with 0 fill and plus sign (fixed)
  test_format_it<CharType>("     +42.133724", "{+015f}",   42.133724f);
  test_format_it<CharType>("     +42.133724", "{>+015f}",  42.133724f);
  test_format_it<CharType>("+0000042.133724", "{_+015f}",  42.133724f);
  test_format_it<CharType>("+42.133724     ", "{<+015f}",  42.133724f);

  // Alignment of positive floats with space (fixed)
  test_format_it<CharType>("      42.133724", "{ 15f}",   42.133724f);
  test_format_it<CharType>("      42.133724", "{> 15f}",  42.133724f);
  test_format_it<CharType>("      42.133724", "{_ 15f}",  42.133724f);
  test_format_it<CharType>(" 42.133724     ", "{< 15f}",  42.133724f);

  // Alignment of negative floats with 0 fill and space (fixed)
  test_format_it<CharType>("      42.133724", "{ 015f}",   42.133724f);
  test_format_it<CharType>("      42.133724", "{> 015f}",  42.133724f);
  test_format_it<CharType>(" 0000042.133724", "{_ 015f}",  42.133724f);
  test_format_it<CharType>(" 42.133724     ", "{< 015f}",  42.133724f);
}


template<typename CharType>
void test_scientific_float_alignment() {
  // Alignment of negative floats (scientific)
  test_format_it<CharType>("  -4.213372e+01", "{15e}",   -42.133724f);
  test_format_it<CharType>("  -4.213372e+01", "{>15e}",  -42.133724f);
  test_format_it<CharType>("-  4.213372e+01", "{_15e}",  -42.133724f);
  test_format_it<CharType>("-4.213372e+01  ", "{<15e}",  -42.133724f);

  // Alignment of negative floats with 0 fill (scientific)
  test_format_it<CharType>("  -4.213372e+01", "{015e}",   -42.133724f);
  test_format_it<CharType>("  -4.213372e+01", "{>015e}",  -42.133724f);
  test_format_it<CharType>("-004.213372e+01", "{_015e}",  -42.133724f);
  test_format_it<CharType>("-4.213372e+01  ", "{<015e}",  -42.133724f);

  // Alignment of positive floats with plus sign (scientific)
  test_format_it<CharType>("  +4.213372e+01", "{+15e}",   42.133724f);
  test_format_it<CharType>("  +4.213372e+01", "{>+15e}",  42.133724f);
  test_format_it<CharType>("+  4.213372e+01", "{_+15e}",  42.133724f);
  test_format_it<CharType>("+4.213372e+01  ", "{<+15e}",  42.133724f);

  // Alignment of negative floats with 0 fill and plus sign (scientific)
  test_format_it<CharType>("  +4.213372e+01", "{+015e}",   42.133724f);
  test_format_it<CharType>("  +4.213372e+01", "{>+015e}",  42.133724f);
  test_format_it<CharType>("+004.213372e+01", "{_+015e}",  42.133724f);
  test_format_it<CharType>("+4.213372e+01  ", "{<+015e}",  42.133724f);

  // Alignment of positive floats with space (scientific)
  test_format_it<CharType>("   4.213372e+01", "{ 15e}",   42.133724f);
  test_format_it<CharType>("   4.213372e+01", "{> 15e}",  42.133724f);
  test_format_it<CharType>("   4.213372e+01", "{_ 15e}",  42.133724f);
  test_format_it<CharType>(" 4.213372e+01  ", "{< 15e}",  42.133724f);

  // Alignment of negative floats with 0 fill and space (scientific)
  test_format_it<CharType>("   4.213372e+01", "{ 015e}",   42.133724f);
  test_format_it<CharType>("   4.213372e+01", "{> 015e}",  42.133724f);
  test_format_it<CharType>(" 004.213372e+01", "{_ 015e}",  42.133724f);
  test_format_it<CharType>(" 4.213372e+01  ", "{< 015e}",  42.133724f);
}


template<typename CharType>
void test_fixed_float_precision() {
  test_format_it<CharType>("1.2345678900000", "{.13f}", 1.234567890);
  test_format_it<CharType>("1.234567890000",  "{.12f}", 1.234567890);
  test_format_it<CharType>("1.23456789000",   "{.11f}", 1.234567890);
  test_format_it<CharType>("1.2345678900",    "{.10f}", 1.234567890);
  test_format_it<CharType>("1.234567890",     "{.9f}",  1.234567890);
  test_format_it<CharType>("1.23456789",      "{.8f}",  1.234567890);
  test_format_it<CharType>("1.2345679",       "{.7f}",  1.234567890); // rounding!
  test_format_it<CharType>("1.234568",        "{.6f}",  1.234567890); // rounding!
  test_format_it<CharType>("1.23457",         "{.5f}",  1.234567890); // rounding!
  test_format_it<CharType>("1.2346",          "{.4f}",  1.234567890); // rounding!
  test_format_it<CharType>("1.235",           "{.3f}",  1.234567890); // rounding!
  test_format_it<CharType>("1.23",            "{.2f}",  1.234567890);
  test_format_it<CharType>("1.2",             "{.1f}",  1.234567890);
  test_format_it<CharType>("1",               "{.0f}",  1.234567890);
}


template<typename CharType>
void test_scientific_float_precision() {
  test_format_it<CharType>("1.2345678900000e+00", "{.13e}", 1.234567890);
  test_format_it<CharType>("1.234567890000e+00",  "{.12e}", 1.234567890);
  test_format_it<CharType>("1.23456789000e+00",   "{.11e}", 1.234567890);
  test_format_it<CharType>("1.2345678900e+00",    "{.10e}", 1.234567890);
  test_format_it<CharType>("1.234567890e+00",     "{.9e}",  1.234567890);
  test_format_it<CharType>("1.23456789e+00",      "{.8e}",  1.234567890);
  test_format_it<CharType>("1.2345679e+00",       "{.7e}",  1.234567890); // rounding!
  test_format_it<CharType>("1.234568e+00",        "{.6e}",  1.234567890); // rounding!
  test_format_it<CharType>("1.23457e+00",         "{.5e}",  1.234567890); // rounding!
  test_format_it<CharType>("1.2346e+00",          "{.4e}",  1.234567890); // rounding!
  test_format_it<CharType>("1.235e+00",           "{.3e}",  1.234567890); // rounding!
  test_format_it<CharType>("1.23e+00",            "{.2e}",  1.234567890);
  test_format_it<CharType>("1.2e+00",             "{.1e}",  1.234567890);
  test_format_it<CharType>("1e+00",               "{.0e}",  1.234567890);
}


template<typename CharType>
void test_float_formatters() {
  test_fixed_float_alignment<CharType>();
  test_scientific_float_alignment<CharType>();
  test_fixed_float_precision<CharType>();
  test_scientific_float_precision<CharType>();
}


template<typename CharType>
void test_int_alignment() {
  // Lowest possible negative integers
  test_format_it<CharType>("-128",                 "{d}", std::numeric_limits<int8_t>::min());
  test_format_it<CharType>("-32768",               "{d}", std::numeric_limits<int16_t>::min());
  test_format_it<CharType>("-2147483648",          "{d}", std::numeric_limits<int32_t>::min());
  test_format_it<CharType>("-9223372036854775808", "{d}", std::numeric_limits<int64_t>::min());

  // Alignment of negative integers
  test_format_it<CharType>("  -42", "{5d}",   -42);
  test_format_it<CharType>("  -42", "{>5d}",  -42);
  test_format_it<CharType>("-  42", "{_5d}",  -42);
  test_format_it<CharType>("-42  ", "{<5d}",  -42);

  // Alignment of negative integers with 0 fill
  test_format_it<CharType>("  -42", "{05d}",   -42);
  test_format_it<CharType>("  -42", "{>05d}",  -42);
  test_format_it<CharType>("-0042", "{_05d}",  -42);
  test_format_it<CharType>("-42  ", "{<05d}",  -42);

  // Alignment of positive integers with plus sign
  test_format_it<CharType>("  +42", "{+5d}",   42);
  test_format_it<CharType>("  +42", "{>+5d}",  42);
  test_format_it<CharType>("+  42", "{_+5d}",  42);
  test_format_it<CharType>("+42  ", "{<+5d}",  42);

  // Alignment of negative integers with 0 fill and plus sign
  test_format_it<CharType>("  +42", "{+05d}",   42);
  test_format_it<CharType>("  +42", "{>+05d}",  42);
  test_format_it<CharType>("+0042", "{_+05d}",  42);
  test_format_it<CharType>("+42  ", "{<+05d}",  42);

  // Alignment of positive integers with plus sign (unsigned type)
  test_format_it<CharType>("  +42", "{+5d}",   42U);
  test_format_it<CharType>("  +42", "{>+5d}",  42U);
  test_format_it<CharType>("+  42", "{_+5d}",  42U);
  test_format_it<CharType>("+42  ", "{<+5d}",  42U);

  // Alignment of negative integers with 0 fill and plus sign (unsigned type)
  test_format_it<CharType>("  +42", "{+05d}",   42U);
  test_format_it<CharType>("  +42", "{>+05d}",  42U);
  test_format_it<CharType>("+0042", "{_+05d}",  42U);
  test_format_it<CharType>("+42  ", "{<+05d}",  42U);

  // Alignment of positive integers with space
  test_format_it<CharType>("   42", "{ 5d}",   42);
  test_format_it<CharType>("   42", "{> 5d}",  42);
  test_format_it<CharType>("   42", "{_ 5d}",  42);
  test_format_it<CharType>(" 42  ", "{< 5d}",  42);

  // Alignment of negative integers with 0 fill and space
  test_format_it<CharType>("   42", "{ 05d}",   42);
  test_format_it<CharType>("   42", "{> 05d}",  42);
  test_format_it<CharType>(" 0042", "{_ 05d}",  42);
  test_format_it<CharType>(" 42  ", "{< 05d}",  42);

  // Alignment of positive integers with space (unsigned type)
  test_format_it<CharType>("   42", "{ 5d}",   42U);
  test_format_it<CharType>("   42", "{> 5d}",  42U);
  test_format_it<CharType>("   42", "{_ 5d}",  42U);
  test_format_it<CharType>(" 42  ", "{< 5d}",  42U);

  // Alignment of negative integers with 0 fill and space (unsigned type)
  test_format_it<CharType>("   42", "{ 05d}",   42U);
  test_format_it<CharType>("   42", "{> 05d}",  42U);
  test_format_it<CharType>(" 0042", "{_ 05d}",  42U);
  test_format_it<CharType>(" 42  ", "{< 05d}",  42U);
}


template<typename CharType>
void test_int_bases() {
  // Different integer bases
  test_format_it<CharType>("1",               "{x}", uint8_t(0x01));
  test_format_it<CharType>("123",             "{x}", uint16_t(0x0123));
  test_format_it<CharType>("1234567",         "{x}", uint32_t(0x01234567));
  test_format_it<CharType>("123456789abcdef", "{x}", uint64_t(0x0123456789abcdef));

  test_format_it<CharType>("d6",               "{x}", int8_t(-42));
  test_format_it<CharType>("ffd6",             "{x}", int16_t(-42));
  test_format_it<CharType>("ffffffd6",         "{x}", int32_t(-42));
  test_format_it<CharType>("ffffffffffffffd6", "{x}", int64_t(-42));

  test_format_it<CharType>("20",                    "{o}", uint8_t(020));
  test_format_it<CharType>("10000",                 "{o}", uint16_t(010000));
  test_format_it<CharType>("2000000000",            "{o}", uint32_t(02000000000));
  test_format_it<CharType>("100000000000000000000", "{o}", uint64_t(0100000000000000000000));

  test_format_it<CharType>("326",                    "{o}", int8_t(-42));
  test_format_it<CharType>("177726",                 "{o}", int16_t(-42));
  test_format_it<CharType>("37777777726",            "{o}", int32_t(-42));
  test_format_it<CharType>("1777777777777777777726", "{o}", int64_t(-42));

  test_format_it<CharType>("1",                                                         "{b}", uint8_t(0x01));
  test_format_it<CharType>("100100011",                                                 "{b}", uint16_t(0x0123));
  test_format_it<CharType>("1001000110100010101100111",                                 "{b}", uint32_t(0x01234567));
  test_format_it<CharType>("100100011010001010110011110001001101010111100110111101111", "{b}", uint64_t(0x0123456789abcdef));

  test_format_it<CharType>("11010110",                                                         "{b}", int8_t(-42));
  test_format_it<CharType>("1111111111010110",                                                 "{b}", int16_t(-42));
  test_format_it<CharType>("11111111111111111111111111010110",                                 "{b}", int32_t(-42));
  test_format_it<CharType>("1111111111111111111111111111111111111111111111111111111111010110", "{b}", int64_t(-42));
}


template<typename CharType>
void test_int_formatters() {
  test_int_alignment<CharType>();
  test_int_bases<CharType>();
}


template<typename CharType>
void test_basic_formatters() {
  test_float_formatters<CharType>();
  test_int_formatters<CharType>();

  // Characters
  test_format_it<CharType>("f", "{c}", 'f');

  // Strings
  test_format_it<CharType>("yyy",        "{s}",    cheaty_cast_string<CharType>("yyy"));
  test_format_it<CharType>("       yyy", "{10s}",  cheaty_cast_string<CharType>("yyy"));
  test_format_it<CharType>("       yyy", "{>10s}", cheaty_cast_string<CharType>("yyy"));
  test_format_it<CharType>("yyy       ", "{<10s}", cheaty_cast_string<CharType>("yyy"));

  // C-Strings
  auto tmp_str = cheaty_cast_string<CharType>("yyy");
  test_format_it<CharType>("yyy",        "{s}",    tmp_str.c_str());
  test_format_it<CharType>("       yyy", "{10s}",  tmp_str.c_str());
  test_format_it<CharType>("       yyy", "{>10s}", tmp_str.c_str());
  test_format_it<CharType>("yyy       ", "{<10s}", tmp_str.c_str());
}


template<typename CharType>
void test_multiple_formatters() {
  test_format_it<CharType>("AAfooXX42YYbarBB", "AA{}XX{}YY{}BB", cheaty_cast_string<CharType>("foo"), 42, cheaty_cast_string<CharType>("bar"));
}


template<typename CharType>
void run_tests() {
  test_basic_formatters<CharType>();
  test_multiple_formatters<CharType>();
}


int main() {
  run_tests<char>();
  run_tests<wchar_t>();
  run_tests<char32_t>();
  std::cout << "Performed " << testcount << " tests, " << (testcount - failed) << " passed, " << failed << " failed." << std::endl;
}
