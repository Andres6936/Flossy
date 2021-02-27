# Flossy

Flossy is an easy to use but very flexible library to format strings in C++17 in
a type safe way.

It is loosely inspired by string formatting in Python, but stripped down in many
places to allow making it type safe and faster.

## Usage

To use flossy, just include `flossy.h` in your C++ code:

```c++
#include
"Flossy/Flossy.hpp"
```

No linking or additional source files are needed. You will have to select C++17
mode on most compilers manually, though. This is done by passing
the `-std=c++17`
flag to your GCC or Clang compilers.

The easiest way to use flossy is to format a string directly:

```c++
auto result = flossy::format("The first value passed is {}, and the second is {}!", 42, "foo");
```

But often, you do not want to store the formatted string itself but rather want
to output it directly to a stream:

```c++
flossy::format(std::cout, "The first value passed is {}, and the second is {}!", 42, "foo");
```

These functions are just wrappers around a more generic function though, which
works on iterators of any kind:

```c++
std::string result;
std::string format("The first value passed is {}, and the second is {}!");
auto it = format_it(std::back_inserter(result), format_str.begin(), format_str.end(), 42, "foo");
```

Instead of `string` and  `back_inserter`, any kind of iterator will work.

`format` and `format_it` work with any character type you want, as long as
string arguments use the same character type:

```c++
auto result = flossy::format(L"The first value passed is {}, and the second is {}!", 42, L"foo");
```

## Format Specification Language

Inside the curly braces, a string format specification language inspired by
Python is used.

Format strings consist of any character sequence containing any number of
conversion specifiers.

Conversion specifiers are delimited by curly braces containing the format
specification:

```
  format: [align][sign][0][width][.precision][type]
  align: '>' | '_' | '<'
  sign: '+' | ' ' | '-'
  width: integer
  precision: integer
  type: 'd', 'o', 'x', 'f', 'e', 's', 'b'
```

`align` specifies where in the resulting field the value will be aligned, as
described in the following table:

|Option|Description|
|---|---|
|>|Align the value to the right of the field (i.e. put spaces left of the resulting value). If this option is used, the zero flag is ignored. This is the default option.|
|<|Align the value to the left of the field (i.e put spaces right of the resulting value.  If this option is used, the zero flag is ignored.|
|_|Let the value fill the whole field by putting spaces or zeroes between the digits and the sign.  This is the only option that respects the zero flag.|


`sign` specifies how positive numbers should be displayed, as described in
the following table:

|Option|Description|
|---|---|
|-|Only display the sign of negative numbers. This is the default option.|
|+|Positive numbers will be displayed with a plus sign ('+') in front of them.|
|&lt;space&gt;|Positive numbers will be displayed with a space in front of them to align them with negative numbers.|

 
  The `zero` flag ('0'), if present, makes numbers displayed with internal
  alignment (the '_' align option) use a zero ('0') character instead of spaces
  to fill the gap between numbers and sign.

  `width` specifies the minimum width of the field. If this is larger than the
  width of the converted value, the value will be aligned and padded according
  to the 'align' and 'zero' flags.

  `precision` specifies the number of digits in the fractional part of floating
  point numbers.

  `type` specifies the formatting method used. This is basically used to change
  the display type of numbers, like the number base or float representation
  (scientific vs. fixed width) and is ignored if it doesn't make sense for the
  field currently converted.
  
## Formatting Custom Types

Sometimes you may want to add a custom formatter for your own classes. Flossy is
easily extensible by providing an appropriate formatting function template for
your type.

To do that, you have to provide a templated function `format_element`, taking at
least two template parameters and exactly three function parameters:

```c++
template<typename CharT, typename OutIt>
OutIt format_element(OutIt out, conversion_options options, YourType value);
```

Mandatory template parameters:

|Parameter|Description|
|---|---|
|`CharT`|Character type to generate.|
|`OutIt`|Output iterator type used by the format function.|

You may add more template parameters if you wish, as long as they can
always be deduced from the type you want to convert.

Parameters:

|Parameter|Description|
|---|---|
|`out`|The output iterator your format function should write to|
|`options`|The options selected in the format specifier (see section flossy.h for details).|
|`value|The value you passed in the format or format_it function.|

Your function should always return the updated output iterator.

You may use existing `flossy::format_element` functions for integers, floats,
characters, and strings to built upon.

conversion_options is holds the format flags specified in the format string.
See definition of conversion_options for more information.

There is currently no way to add your own conversion flags or options, sorry.

## What's in the Repository?

* `flossy.h`: The full library. This is all you need to use flossy.
* `README.md`: You're reading it right now.
* `flossy_test.cpp`: A bunch of black box unit tests for Flossy.
* `CMakeLists.txt`: Simple CMake project file that only compiles the unit tests.


## Current State

Flossy is fully usable and tested (compile and run `flossy_test.cpp` to make
sure it works on your compiler).

At the moment, floats are formatted using an internal stringstream, which is
probably not the fastest solution out there (at the very least, stringstreams
use dynamic memory, which can cause unpredictable timing).

I plan to add two other implementations for floating point conversions, which
will then be configurable through an optional macro definition. This is not
done, yet, though. I plan to add an external
library ([https://github.com/google/double-conversion])
which you would have to compile and link into the rest of the program as one
options, and a cheaty, imprecise but fast method of rounding floats to an
integer of the required precision and outputting that one.

I had actually started stripping down the `double-conversion` library so it
could be placed completely inside the `flossy.h` header file, but even the
stripped-down version took around 1500 lines of code, more then the existing
Flossy code base _including_ documentation.

If you find and errors in Flossy, please let me know!

## Why "Flossy"?

Good question! I asked a few friends for a name for a string formatting library
and, [@martijnfrazer](https://twitter.com/martijnfrazer) suggested this name and
I immediately loved it for the following reasons:

1. (Dental) floss is some kind of string.
2. Flossy is FLOSS (Free/Libre Open Source Software)
3. My first name starts with "Flo", so even that matches.

I think it's the perfect name for this library.

## License

Flossy is licensed under the MIT software license. See the header of
`Flossy.hpp` for the full license text.
