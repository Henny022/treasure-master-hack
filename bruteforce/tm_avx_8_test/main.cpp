#include "tester.h"
#include "tm_avx_8_test.h"

int main()
{
    tm_avx_8_test tester;
    run_validity_tests<tm_avx_8_test>(tester);

    run_speed_tests<tm_avx_8_test>(tester, 10000000);
}