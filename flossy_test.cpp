#include <string>
#include <iterator>
#include "flossy.h"


template<typename CharT, typename... Args>
void test_format_it(std::basic_string<CharT> expect, std::basic_string<CharT> format, Args... args) {
  std::basic_string<CharT> output;
  flossy::format_it(std::back_inserter(output), format.begin(), format.end(), args...);

  if(output == expect) {
    std::cout << "Test passed\n";
  } else {
    std::cout << "Test failed (\"" << format << "\": \"" << output << "\" != \"" << expect << "\")\n";
  }
}



int main() {
  // basic formatters (char)
  test_format_it<char>("12.345600",    "{f}",   12.3456f);
  test_format_it<char>("1.234560e+03", "{e}", 1.23456e3f);
  test_format_it<char>("12.345600",    "{f}",    12.3456);
  test_format_it<char>("1.234560e+03", "{e}",  1.23456e3);

  // Characters
  test_format_it<char>("f", "{c}", 'f');

  // Strings
  test_format_it<char>("yyy",        "{s}",    "yyy");
  test_format_it<char>("       yyy", "{10s}",  "yyy");
  test_format_it<char>("       yyy", "{>10s}", "yyy");
  test_format_it<char>("yyy       ", "{<10s}", "yyy");

  // Lowest possible negative integers
  test_format_it<char>("-128",                 "{d}", std::numeric_limits<int8_t>::min());
  test_format_it<char>("-32768",               "{d}", std::numeric_limits<int16_t>::min());
  test_format_it<char>("-2147483648",          "{d}", std::numeric_limits<int32_t>::min());
  test_format_it<char>("-9223372036854775808", "{d}", std::numeric_limits<int64_t>::min());

  // Alignment of negative integers
  test_format_it<char>("  -42", "{5d}",   -42);
  test_format_it<char>("  -42", "{>5d}",  -42);
  test_format_it<char>("-  42", "{_5d}",  -42);
  test_format_it<char>("-42  ", "{<5d}",  -42);

  // Alignment of negative integers with 0 fill
  test_format_it<char>("  -42", "{05d}",   -42);
  test_format_it<char>("  -42", "{>05d}",  -42);
  test_format_it<char>("-0042", "{_05d}",  -42);
  test_format_it<char>("-42  ", "{<05d}",  -42);

  // Alignment of positive integers with plus sign
  test_format_it<char>("  +42", "{+5d}",   42);
  test_format_it<char>("  +42", "{>+5d}",  42);
  test_format_it<char>("+  42", "{_+5d}",  42);
  test_format_it<char>("+42  ", "{<+5d}",  42);

  // Alignment of negative integers with 0 fill and plus sign
  test_format_it<char>("  +42", "{+05d}",   42);
  test_format_it<char>("  +42", "{>+05d}",  42);
  test_format_it<char>("+0042", "{_+05d}",  42);
  test_format_it<char>("+42  ", "{<+05d}",  42);

  // Alignment of positive integers with plus sign (unsigned type)
  test_format_it<char>("  +42", "{+5d}",   42U);
  test_format_it<char>("  +42", "{>+5d}",  42U);
  test_format_it<char>("+  42", "{_+5d}",  42U);
  test_format_it<char>("+42  ", "{<+5d}",  42U);

  // Alignment of negative integers with 0 fill and plus sign (unsigned type)
  test_format_it<char>("  +42", "{+05d}",   42U);
  test_format_it<char>("  +42", "{>+05d}",  42U);
  test_format_it<char>("+0042", "{_+05d}",  42U);
  test_format_it<char>("+42  ", "{<+05d}",  42U);

  // Alignment of positive integers with space
  test_format_it<char>("   42", "{ 5d}",   42);
  test_format_it<char>("   42", "{> 5d}",  42);
  test_format_it<char>("   42", "{_ 5d}",  42);
  test_format_it<char>(" 42  ", "{< 5d}",  42);

  // Alignment of negative integers with 0 fill and space
  test_format_it<char>("   42", "{ 05d}",   42);
  test_format_it<char>("   42", "{> 05d}",  42);
  test_format_it<char>(" 0042", "{_ 05d}",  42);
  test_format_it<char>(" 42  ", "{< 05d}",  42);

  // Alignment of positive integers with space (unsigned type)
  test_format_it<char>("   42", "{ 5d}",   42U);
  test_format_it<char>("   42", "{> 5d}",  42U);
  test_format_it<char>("   42", "{_ 5d}",  42U);
  test_format_it<char>(" 42  ", "{< 5d}",  42U);

  // Alignment of negative integers with 0 fill and space (unsigned type)
  test_format_it<char>("   42", "{ 05d}",   42U);
  test_format_it<char>("   42", "{> 05d}",  42U);
  test_format_it<char>(" 0042", "{_ 05d}",  42U);
  test_format_it<char>(" 42  ", "{< 05d}",  42U);

  // Different integer bases
  test_format_it<char>("1",               "{x}", uint8_t(0x01));
  test_format_it<char>("123",             "{x}", uint16_t(0x0123));
  test_format_it<char>("1234567",         "{x}", uint32_t(0x01234567));
  test_format_it<char>("123456789abcdef", "{x}", uint64_t(0x0123456789abcdef));

  test_format_it<char>("d6",               "{x}", int8_t(-42));
  test_format_it<char>("ffd6",             "{x}", int16_t(-42));
  test_format_it<char>("ffffffd6",         "{x}", int32_t(-42));
  test_format_it<char>("ffffffffffffffd6", "{x}", int64_t(-42));

  test_format_it<char>("20",                    "{o}", uint8_t(020));
  test_format_it<char>("10000",                 "{o}", uint16_t(010000));
  test_format_it<char>("2000000000",            "{o}", uint32_t(02000000000));
  test_format_it<char>("100000000000000000000", "{o}", uint64_t(0100000000000000000000));

  test_format_it<char>("326",                    "{o}", int8_t(-42));
  test_format_it<char>("177726",                 "{o}", int16_t(-42));
  test_format_it<char>("37777777726",            "{o}", int32_t(-42));
  test_format_it<char>("1777777777777777777726", "{o}", int64_t(-42));

  test_format_it<char>("1",                                                         "{b}", uint8_t(0x01));
  test_format_it<char>("100100011",                                                 "{b}", uint16_t(0x0123));
  test_format_it<char>("1001000110100010101100111",                                 "{b}", uint32_t(0x01234567));
  test_format_it<char>("100100011010001010110011110001001101010111100110111101111", "{b}", uint64_t(0x0123456789abcdef));

  test_format_it<char>("11010110",                                                         "{b}", int8_t(-42));
  test_format_it<char>("1111111111010110",                                                 "{b}", int16_t(-42));
  test_format_it<char>("11111111111111111111111111010110",                                 "{b}", int32_t(-42));
  test_format_it<char>("1111111111111111111111111111111111111111111111111111111111010110", "{b}", int64_t(-42));

}
