#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "tm_8_test.h"

struct TestCase
{
    uint8_t algorithm;
    uint8_t rng[2];
    uint8_t code[128];
    uint8_t target_rng[2];
    uint8_t target_code[128];
};

int main()
{
    tm_8_test tester;

    FILE *pFile;
    pFile = fopen("../common/TM_test_cases_OUT.txt", "w");
    if (pFile == nullptr)
    {
        printf("File error\n");
        return 1;
    }


    for (int i = 0; i < 10000; ++i)
    {
        for (int alg = 0; alg < 8; ++alg)
        {
            TestCase testCase{};
            testCase.algorithm = alg;
            testCase.rng[0] = rand();
            testCase.rng[1] = rand();
            for (int j = 0; j < 128; ++j)
            {
                testCase.code[j] = testCase.target_code[j] = rand();
            }
            uint16_t rng_seed = (testCase.rng[0] << 8) | testCase.rng[1];
            tester.process_test_case(testCase.target_code, &rng_seed, alg);
            testCase.target_rng[0] = rng_seed >> 8;
            testCase.target_rng[1] = rng_seed & 0xff;
            auto *raw = reinterpret_cast<uint8_t *>(&testCase);
            for (int j = 0; j < sizeof(TestCase); ++j)
            {
                fprintf(pFile, "%i,", raw[j]);
            }
        }
    }
}

