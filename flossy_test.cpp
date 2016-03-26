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
  test_format_it<char>("yyy",          "{s}",      "yyy");
  test_format_it<char>("42",           "{d}",         42U);
  test_format_it<char>("12abcdef",     "{x}", 0x12ABCDEF);
  test_format_it<char>("1234567",      "{o}",   01234567);
  test_format_it<char>("12.345600",    "{f}",   12.3456f);
  test_format_it<char>("1.234560e+03", "{e}", 1.23456e3f);
  test_format_it<char>("12.345600",    "{f}",    12.3456);
  test_format_it<char>("1.234560e+03", "{e}",  1.23456e3);
  test_format_it<char>("f",            "{c}",        'f');

  test_format_it<char>("-42",          "{d}",    -42);

  // Alignment of negative integers
  test_format_it<char>("  -42",        "{5d}",   -42);
  test_format_it<char>("  -42",        "{>5d}",  -42);
  test_format_it<char>("-  42",        "{_5d}",  -42);
  test_format_it<char>("-42  ",        "{<5d}",  -42);

  // Alignment of negative integers with 0 fill
  test_format_it<char>("  -42",        "{05d}",   -42);
  test_format_it<char>("  -42",        "{>05d}",  -42);
  test_format_it<char>("-0042",        "{_05d}",  -42);
  test_format_it<char>("-42  ",        "{<05d}",  -42);

  // Alignment of positive integers with plus sign
  test_format_it<char>("  +42",        "{+5d}",   42);
  test_format_it<char>("  +42",        "{>+5d}",  42);
  test_format_it<char>("+  42",        "{_+5d}",  42);
  test_format_it<char>("+42  ",        "{<+5d}",  42);

  // Alignment of negative integers with 0 fill and plus sign
  test_format_it<char>("  +42",        "{+05d}",   42);
  test_format_it<char>("  +42",        "{>+05d}",  42);
  test_format_it<char>("+0042",        "{_+05d}",  42);
  test_format_it<char>("+42  ",        "{<+05d}",  42);

  // Alignment of positive integers with plus sign (unsigned type)
  test_format_it<char>("  +42",        "{+5d}",   42U);
  test_format_it<char>("  +42",        "{>+5d}",  42U);
  test_format_it<char>("+  42",        "{_+5d}",  42U);
  test_format_it<char>("+42  ",        "{<+5d}",  42U);

  // Alignment of negative integers with 0 fill and plus sign (unsigned type)
  test_format_it<char>("  +42",        "{+05d}",   42U);
  test_format_it<char>("  +42",        "{>+05d}",  42U);
  test_format_it<char>("+0042",        "{_+05d}",  42U);
  test_format_it<char>("+42  ",        "{<+05d}",  42U);

  // Alignment of positive integers with space
  test_format_it<char>("   42",        "{ 5d}",   42);
  test_format_it<char>("   42",        "{> 5d}",  42);
  test_format_it<char>("   42",        "{_ 5d}",  42);
  test_format_it<char>(" 42  ",        "{< 5d}",  42);

  // Alignment of negative integers with 0 fill and space
  test_format_it<char>("   42",        "{ 05d}",   42);
  test_format_it<char>("   42",        "{> 05d}",  42);
  test_format_it<char>(" 0042",        "{_ 05d}",  42);
  test_format_it<char>(" 42  ",        "{< 05d}",  42);

  // Alignment of positive integers with space (unsigned type)
  test_format_it<char>("   42",        "{ 5d}",   42U);
  test_format_it<char>("   42",        "{> 5d}",  42U);
  test_format_it<char>("   42",        "{_ 5d}",  42U);
  test_format_it<char>(" 42  ",        "{< 5d}",  42U);

  // Alignment of negative integers with 0 fill and space (unsigned type)
  test_format_it<char>("   42",        "{ 05d}",   42U);
  test_format_it<char>("   42",        "{> 05d}",  42U);
  test_format_it<char>(" 0042",        "{_ 05d}",  42U);
  test_format_it<char>(" 42  ",        "{< 05d}",  42U);


  test_format_it<char>("-42",          "{x}",    -42);

#if 0
  // basic formatters (wchar_t)
  test_format_it<wchar_t>(L"yyy",          L"{s}",      L"yyy");
  test_format_it<wchar_t>(L"42",           L"{d}",         42);
  test_format_it<wchar_t>(L"12abcdef",     L"{x}", 0x12ABCDEF);
  test_format_it<wchar_t>(L"1234567",      L"{o}",   01234567);
  test_format_it<wchar_t>(L"12.345600",    L"{f}",   12.3456f);
  test_format_it<wchar_t>(L"1.234560e+03", L"{e}", 1.23456e3f);
  test_format_it<wchar_t>(L"12.345600",    L"{f}",    12.3456);
  test_format_it<wchar_t>(L"1.234560e+03", L"{e}",  1.23456e3);
  test_format_it<wchar_t>(L"f",            L"{c}",        L'f');
#endif
}
