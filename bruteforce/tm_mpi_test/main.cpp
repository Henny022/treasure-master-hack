#include "../common/tester.h"
#include "tm_mpi_test.h"

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("usage: test <iterations>\n");
        exit(1);
    }
    tm_mpi_test tester;
    run_validity_tests<tm_mpi_test>(tester);

    int n = std::strtol(argv[1], nullptr, 10);
    run_speed_tests<tm_mpi_test>(tester, n);
}
