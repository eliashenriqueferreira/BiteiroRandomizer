#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#if defined BITEIRO_RAND_C
#define EXTERN
#elif defined CPP_CODE
#define EXTERN extern "C"
#else
#define EXTERN extern
#endif

typedef struct st_bitRandom {
	__int64 modulus;
	__int64 alfa;
	__int64 seed;
	__int64 max;
} BIT_RAND;


EXTERN int biteiroRand(int argc, char ** argv);
EXTERN BIT_RAND *bitRandInit(__int64 p_alfa, __int64 p_seed, __int64 p_max_mod);
EXTERN void bitRandFinish(BIT_RAND *prand);
EXTERN __int64 bitRand(BIT_RAND *prand);


#undef EXTERN