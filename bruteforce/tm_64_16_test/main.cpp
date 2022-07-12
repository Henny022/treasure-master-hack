#include "tester.h"
#include "tm_64_16_test.h"

int main()
{
    tm_64_16_test tester;
    run_validity_tests<tm_64_16_test>(tester);

    run_speed_tests<tm_64_16_test>(tester, 10000000);
}