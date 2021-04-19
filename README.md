soft_double\
[![Build Status](https://github.com/ckormanyos/soft_double/actions/workflows/soft_double.yml/badge.svg)](https://github.com/ckormanyos/soft_double/actions)
==================

soft_double is a C++ header-only library that implements
a 64-bit double-precision floating-point data type in software.
This data type is called `math::softfloat::soft_double`
and it can be used essentially like a regular
built-in 64-bit floating-point type (such as built-in `double`).

Some compilers do not support a built-in 64-bit floating-point type,
which might be commonly known as `double` or `long` `double`.
Consider, for instance, the `avr-gcc` tool chain popularly used on
8-bit embedded systems like Arduino or standalone _bare metal_ AVR.
Prior to version 10, this compiler does not support 64-bit `double`.
soft_double can be used on such systems to provide a software-emulated,
portable implementation of 64-bit `double`.

soft_double implements common algebraic operations,
comparison operations, simple functions like `sqrt`,
and also includes full support for `std::numeric_limits`.

soft_double is written in header-only C++11.
It is compatible through C++11, 14, 17, 20.

## Implementation goals

  - Clean header-only C++ design.
  - Seamless portability to any modern C++11, 14, 17, 20 compiler.
  - Efficiency suitable for _bare-metal_ embedded systems.
  - Particularly useful if 64-bit native `double` or a similar built-in type is unavailable.
  - Use refactored versions of trusted algorithms based on those found in [softfloat 3e](https://github.com/ucb-bar/berkeley-softfloat-3).

## Quick Start

Using `soft_double` is straightforward. Simply `#include <math/soft_double/soft_double.h>` and
the `soft_double` type can be used almost like familiar built-in 64-bit `double`.
The following example, for instance, computes and checks the value of
<img src="https://render.githubusercontent.com/render/math?math=\sqrt{\pi}\,\approx\,1.77245385090551602730">.

```
#include <cmath>
#include <iomanip>
#include <iostream>

#include <math/soft_double/soft_double.h>

int main()
{
  // Use a convenient alias for float64_t.
  using float64_t = ::math::softfloat::soft_double;

  // Use a cached value for pi.
  const float64_t my_pi = float64_t::my_value_pi();

  // Compute soft_double sqrt(pi).
  const float64_t s = sqrt(my_pi);

  using std::sqrt;

  // Compare with native double sqrt(pi).
  const double control = sqrt(3.1415926535897932384626433832795028841972);

  union
  {
    double   d;
    uint64_t u;
  } uZ;

  uZ.d = control;

  const bool result_is_ok = (s.crepresentation() == uZ.u);

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}
```

## Examples

Various interesting and algorithmically challenging
[examples](./examples) have been implemented.
It is hoped that the examples provide inspiration and guidance on
how to use soft_double.

  - ![`example001_roots_sqrt.cpp`](./examples/example001_roots_sqrt.cpp) computes a square root.
  - ![`example004_bessel_recur.cpp`](./examples/example004_bessel_recur.cpp) implements cylindrical Bessel functions of integral order via downward recursion with a Neumann sum.
  - ![`example007_catalan_series.cpp`](./examples/example007_catalan_series.cpp) computes <img src="https://render.githubusercontent.com/render/math?math=\approx\,15"> decimal digits of Catalan's constant using an accelerated series.
  - ![`example011_trig_trapezoid_integral.cpp`](./examples/example011_trig_trapezoid_integral.cpp) uses trapezoid integration with an integral representation involving locally-written trigonometric sine and cosine functions to compute several cylindrical Bessel function values.

## Testing and CI

Testing is a big issue and a growing test suite is in continued progress providing for tested,
efficient functionality on the PC and workstation. The GitHub code is delivered
with an affiliated MSVC project that uses easy-to-understand subroutines called
from `main()` that exercise various test cases. One of the tests uses
the [wide-decimal](https://github.com/ckormanyos/wide-decimal) project
in order to verify the functionality of `soft_double` with FFTs in a real-world application.

Continuous integration runs on push using GitHub Actions. Various compilers, operating systems,
and C++ standards ranging from C++11, 14, 17, 20 are included in CI.
