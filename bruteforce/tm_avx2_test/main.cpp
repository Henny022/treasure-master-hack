#include "tm_avx2_test.h"
#include "tester.h"

int main(int argc, char*argv[])
{
    if (argc <= 1)
    {
        printf("usage: test <iterations>\n");
        exit(1);
    }
	tm_avx2_intrinsics_test tester;
	run_validity_tests<tm_avx2_intrinsics_test>(tester);

    int n = std::strtol(argv[0], nullptr, 10);
	run_speed_tests<tm_avx2_intrinsics_test>(tester, n);
}