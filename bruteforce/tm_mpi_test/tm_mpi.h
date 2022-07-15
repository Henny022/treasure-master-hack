#ifndef BRUTEFORCE_TM_MPI_H
#define BRUTEFORCE_TM_MPI_H

#include <cstdint>
#include <immintrin.h>
#include "../tm_mpi/rng.h"

void run_alg(int alg_id, int iterations, uint8_t *working_code,
             rng_tables_t* rng_tables,
             uint16_t *rng_seed);

#endif // BRUTEFORCE_TM_MPI_H
