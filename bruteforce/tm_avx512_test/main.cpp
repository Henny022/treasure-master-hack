#include "tm_avx512_test.h"
#include "tester.h"

int main()
{
    tm_avx512_intrinsics_test tester;
    run_validity_tests<tm_avx512_intrinsics_test>(tester);

    run_speed_tests<tm_avx512_intrinsics_test>(tester, 10000000);
}