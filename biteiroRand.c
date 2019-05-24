#define BITEIRO_RAND_C

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <biteiroRand.h>

// #define TEST_C_RAND


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BIT_RAND *bitRandInit(__int64 p_alfa, __int64 p_seed, __int64 p_max_mod)
{
	BIT_RAND *prand = malloc(sizeof(struct st_bitRandom));

	if (p_alfa > 0)
	{
		prand->alfa = p_alfa;
	}
	else
	{
		prand->alfa = 25417;
	}

	if (p_seed > 0)
	{
		prand->seed = p_seed;
	}
	else
	{
		prand->seed = prand->alfa;
	}

	prand->max = 0;
	if (p_max_mod > 0)
	{
		prand->max = p_max_mod;
	}

#ifdef TEST_C_RAND
	srand((unsigned int)prand->seed);
	return prand;
#endif

	prand->modulus = LLONG_MAX / prand->alfa;

	while (prand->seed < prand->modulus)
	{
		prand->seed = prand->alfa * prand->seed;
	}

	prand->seed = prand->seed % prand->modulus;

	return prand;
}

void bitRandFinish(BIT_RAND *prand)
{
	assert(prand != NULL);
	free(prand);
}

__int64 bitRand(BIT_RAND *prand)
{
	assert(prand != NULL);

#ifdef TEST_C_RAND
	return((__int64)(rand() % prand->max));
#endif

	prand->seed = (prand->alfa * prand->seed) % prand->modulus;

	return ((prand->seed / 100) % prand->max);
}

//////////////////////////////////// Main entry point for tests  ///////////////////////////////////////////////

//int main(int argc, char ** argv)
int biteiroRand(int argc, char ** argv)
{
	size_t count = 0;
	int statistics[100];
	char ind[1000];
	int val = 0;
	int first_pattern[5];
	int match_ct = 0;
	char pattern_message[1000];
	BIT_RAND *randomizer = bitRandInit(0, 25423, 60);

	printf("\n====================================== Biteiro Randomizer Tests ================================================\n");

	memset(statistics, 0, sizeof(statistics));

	pattern_message[0] = 0;

	// Seaches for a randomic entry point.
	for (int i = 0; i < 6596; ++i)
	{
		bitRand(randomizer);
	}


	while (1)
	{

		val = (int)bitRand(randomizer);

		statistics[val]++;

		if ((count && count % 5000 == 0) || match_ct == 5)
		{
			system("cls");

			for (int i = 0; i < 60; i++)
			{
				int t = statistics[i];
				memset(ind, 0, sizeof(ind));
				memset(ind, '=', t);
				ind[t] = '>';
				printf("\n%.2d-%s", i, ind);
			}
			printf("\n Results for %zd numbers ...  %s", count, pattern_message);

			if (match_ct == 5) break;		// The first occurence of five numbers pattern.
			if (count >= 1500000) break;	// Reach ansi C generator. 

			if (strlen(pattern_message) > 0) 
			{
				_sleep(15000);
				pattern_message[0] = 0;
			}
			_sleep(500);
					   
			memset(statistics, 0, sizeof(statistics));
		}

		if (count < 5)
		{
			first_pattern[count] = val;		// Saves the first pattern
		}
		else
		{
			if (first_pattern[match_ct] == val)
			{
				match_ct++;
				switch (match_ct) {
				//case 2: sprintf(pattern_message, "The pattern of %.2d, %.2d values where found in %zd randomic generation!", first_pattern[0], first_pattern[1], count); break;
				case 3: sprintf(pattern_message, "The pattern of %.2d, %.2d, %.2d values where found in %zd randomic generation!", first_pattern[0], first_pattern[1], first_pattern[2], count); break;
				case 4: sprintf(pattern_message, "The pattern of %.2d, %.2d, %.2d, %.2d values where found in %zd randomic generation!", first_pattern[0], first_pattern[1], first_pattern[2], first_pattern[3], count); break;
				case 5: sprintf(pattern_message, "The pattern of %.2d, %.2d, %.2d, %.2d, %.2d values where found in %zd randomic generation!", first_pattern[0], first_pattern[1], first_pattern[2], first_pattern[3], first_pattern[4], count); break;
				}
			}
			else
			{
				match_ct = 0;
			}
		}

		count++;
	}

	return 0;
}

//////////////////////////////////// NORMAL C RAND FUNCTIONS ( seed() and rand() ) and TEST_C_RAND defined ////////////////////////////////////
// 
// Results for 45000 numbers ...  The pattern of 03, 43, 09 values where found in 41311 randomic generation!
// Results for 50000 numbers ...  The pattern of 03, 43, 09, 30 values where found in 48496 randomic generation!
// Results for 100000 numbers ...  The pattern of 03, 43, 09, 30 values where found in 48496 randomic generation!
//
///// Randomic entry point 
// Results for 145000 numbers ...  The pattern of 14, 04, 46 values where found in 143843 randomic generation!
// Results for 340000 numbers ...  The pattern of 14, 04, 46 values where found in 336713 randomic generation!
// Results for 660000 numbers ...  The pattern of 14, 04, 46 values where found in 655011 randomic generation!
// Results for 810000 numbers ...  The pattern of 14, 04, 46 values where found in 805735 randomic generation!
// Results for 890000 numbers ...  The pattern of 14, 04, 46 values where found in 885991 randomic generation!
// Results for 1185000 numbers ...  The pattern of 14, 04, 46 values where found in 1184496 randomic generation!


//////////////////////////////////// BITEIRO FUNCTIONS /// TEST_C_RAND undefined ////////////////////////////////////
//
// Results for 330000 numbers ...  The pattern of 51, 34, 40 values where found in 327505 randomic generation!
// Results for 360000 numbers ...  The pattern of 51, 34, 40 values where found in 327505 randomic generation!
// Results for 370000 numbers ...  The pattern of 51, 34, 40 values where found in 365689 randomic generation!
//
///// Randomic entry point 
// Results for 105000 numbers ...  The pattern of 41, 37, 14 values where found in 103476 randomic generation!
// Results for 300000 numbers ...  The pattern of 41, 37, 14 values where found in 295436 randomic generation!
// Results for 1000000 numbers ... And So on!
// Replay
// Results for 105000 numbers ...  The pattern of 41, 37, 14 values where found in 103476 randomic generation!
// Results for 300000 numbers ...  The pattern of 41, 37, 14 values where found in 295436 randomic generation!
// Results for 1135000 numbers ...  The pattern of 41, 37, 14 values where found in 1133964 randomic generation!
//00-================================================================================>
//01 -= ============================================================================================== >
//02 -= ========================================================================== >
//03 -= ====================================================================================== = >
//04 -= ============================================================================== = >
//05 -= ================================================================================ >
//06 -= ====================================================================================== = >
//07 -= ==================================================================================== = >
//08 -= ========================================================================== = >
//09 -= ========================================================================================== = >
//10 -= ================================================================================ = >
//11 -= ================================================================================ = >
//12 -= ================================================================================== >
//13 -= ======================================================================== = >
//14 -= ==================================================================== = >
//15 -= ======================================================================================== >
//16 -= ================================================================================ = >
//17 -= ========================================================================== = >
//18 -= ====================================================================== >
//19 -= ============================================================================================ = >
//20 -= ==================================================================== = >
//21 -= ============================================================================================== = >
//22 -= ====================================================================== = >
//23 -= ========================================================================== >
//24 -= ==================================================================== >
//25 -= ====================================================================================== >
//26 -= ====================================================================== >
//27 -= ======================================================================================================== >
//28 -= ================================================================================== = >
//29 -= ========================================================================================================================== >
//30 -= ================================================================== >
//31 -= ==================================================================================== = >
//32 -= ========================================================================================== = >
//33 -= ============================================================================================ >
//34 -= ====================================================== = >
//35 -= ====================================================================================== >
//36 -= ============================================================================== >
//37 -= ====================================================================================== >
//38 -= ========================================================================== >
//39 -= ================================================================================== = >
//40 -= ================================================================================== >
//41 -= ====================================================================================== >
//42 -= ==================================================================================== = >
//43 -= ====================================================================================== = >
//44 -= ======================================================================== = >
//45 -= ============================================================================== = >
//46 -= ====================================================================================== >
//47 -= ====================================================================================== >
//48 -= ====================================================================================== = >
//49 -= ======================================================================================================== >
//50 -= ================================================================================ = >
//51 -= ======================================================================================== = >
//52 -= ======================================================================== = >
//53 -= ============================================================================== >
//54 -= ========================================================================================== = >
//55 -= ================================================================================ = >
//56 -= ============================================================================ >
//57 -= ========================================================================================== >
//58 -= ================================================================================== >
//59 -= ================================================================================== >
//Results for 1500000 numbers ...
