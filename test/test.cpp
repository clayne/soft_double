// Build locally for test on MinGW or Strawberry via Git bash.
// cd C:\Users\User\Documents\Ks\PC_Software\NumericalPrograms\ExtendedNumberTypes\soft_double
// g++ -finline-functions -finline-limit=64 -march=native -mtune=native -O3 -Wall -Wextra -pedantic -Wno-strict-aliasing -std=c++14 -Imath/softfloat-3/source/include -I. math/softfloat-3/source/f64_add_sub_mul_div.cpp math/softfloat-3/source/f64_sqrt.cpp math/softfloat-3/source/f64_to_integral_types.cpp math/softfloat-3/source/round_to_integral_types.cpp math/softfloat-3/source/s_addMagsF64.cpp math/softfloat-3/source/s_approxRecipSqrt32_1.cpp math/softfloat-3/source/s_normRoundPackToF64.cpp math/softfloat-3/source/s_roundPackToF64.cpp math/softfloat-3/source/s_subMagsF64.cpp test/test.cpp test/test_soft_double.cpp test/test_soft_double_with_decwide_t_100k_digit_pi.cpp -o test_soft_double.exe

extern bool test_soft_double();
extern bool test_soft_double_with_decwide_t_100k_digit_pi();

int main()
{
  const bool result_is_ok_double = test_soft_double();
  const bool result_is_ok_pi     = test_soft_double_with_decwide_t_100k_digit_pi();

  const bool result_is_ok = (result_is_ok_double && result_is_ok_pi);

  return (result_is_ok ? 0 : -1);
}
