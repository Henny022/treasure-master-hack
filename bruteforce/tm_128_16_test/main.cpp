#include "tester.h"
#include "tm_128_16_test.h"

int main()
{
    tm_128_16_test tester;
    run_validity_tests<tm_128_16_test>(tester);

    run_speed_tests<tm_128_16_test>(tester, 10000000);
}