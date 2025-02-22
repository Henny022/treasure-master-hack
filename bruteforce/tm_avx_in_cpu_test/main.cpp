#include <chrono>
#include <cstdint>
#include <iostream>
#include <stdio.h>
#include "tm_avx_in_cpu_test.h"

int main()
{
    using std::chrono::duration_cast;
    using std::chrono::microseconds;
    typedef std::chrono::high_resolution_clock clock;

    uint8_t test_case[128 + 128 + 3 + 2];

    FILE *pFile;

    pFile = fopen("../common/TM_test_cases_OUT.txt", "r+");
    if (pFile == NULL)
    {
        printf("File error\n");
        return 0;
    }

    tm_avx_intrinsics2_test tester;
    bool all_tests_passed = true;
    for (int j = 0; j < 80000; j++)
    {
        for (int i = 0; i < 128 + 128 + 1 + 2 + 2; i++)
        {
            int val;
            fscanf(pFile, "%i,", &val);
            test_case[i] = val;
        }

        uint16_t rng_seed = (test_case[1] << 8) | test_case[2];
        uint16_t output_rng_seed =
            (test_case[3 + 128] << 8) | test_case[3 + 128 + 1];

        uint8_t test_data[128];
        for (int i = 0; i < 128; i++)
        {
            test_data[i] = test_case[3 + i];
        }

        if (test_case[0] == 8)
        {
            for (int i = 0; i < 128; i++)
            {

                printf("%i,", test_data[i]);
            }
            printf("\n");
        }

        tester.process_test_case(test_data, &rng_seed, test_case[0]);

        if (test_case[0] == 8)
        {
            for (int i = 0; i < 128; i++)
            {

                printf("%i,", test_data[i]);
            }
            printf("\n");

            for (int i = 0; i < 128; i++)
            {

                printf("%i,", test_case[3 + 128 + 2 + i]);
            }
            printf("\n");
        }

        int matching = 1;
        for (int i = 0; i < 128; i++)
        {
            if (test_data[i] != test_case[3 + 128 + 2 + i])
            {
                matching = 0;
                break;
            }
        }

        if (rng_seed != output_rng_seed)
        {
            matching = 0;
        }

        if (matching == 0)
        {
            printf("Test %i (alg %i): --FAIL--\n", j, test_case[0]);
            all_tests_passed = false;
        }
        /*
        else
        {
                printf("Test %i: Pass\n",j);
        }
        */
    }
    fclose(pFile);

    if (all_tests_passed)
    {
        printf("All tests passed!\n");
    }

    for (int i = 0; i < 8; i++)
    {
        uint16_t rng_seed = (test_case[1] << 8) | test_case[2];
        uint16_t output_rng_seed =
            (test_case[3 + 128] << 8) | test_case[3 + 128 + 1];

        uint8_t test_data[128];
        for (int j = 0; j < 128; j++)
        {
            test_data[j] = test_case[3 + j];
        }

        auto start = clock::now();
        tester.run_iterations(test_data, &rng_seed, i, 10000000);
        auto end = clock::now();
        std::cout << i << " "
                  << duration_cast<microseconds>(end - start).count() << "us\n";
    }
}