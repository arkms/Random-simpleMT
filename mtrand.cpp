// mtrand.cpp, see include file mtrand.h for information

#include "mtrand.h"
#include <math.h>
// non-inline function definitions and static member definitions cannot
// reside in header file because of the risk of multiple declarations

// initialization of static private members
unsigned long MTRand_int32::state[n] = {0x0UL};
int MTRand_int32::p = 0;
bool MTRand_int32::init = false;

void MTRand_int32::gen_state() { // generate new state vector
  for (int i = 0; i < (n - m); ++i)
    state[i] = state[i + m] ^ twiddle(state[i], state[i + 1]);
  for (int i = n - m; i < (n - 1); ++i)
    state[i] = state[i + m - n] ^ twiddle(state[i], state[i + 1]);
  state[n - 1] = state[m - 1] ^ twiddle(state[n - 1], state[0]);
  p = 0; // reset position
}

void MTRand_int32::seed(unsigned long s) {  // init by 32 bit seed
  state[0] = s & 0xFFFFFFFFUL; // for > 32 bit machines
  for (int i = 1; i < n; ++i) {
    state[i] = 1812433253UL * (state[i - 1] ^ (state[i - 1] >> 30)) + i;
// see Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier
// in the previous versions, MSBs of the seed affect only MSBs of the array state
// 2002/01/09 modified by Makoto Matsumoto
    state[i] &= 0xFFFFFFFFUL; // for > 32 bit machines
  }
  p = n; // force gen_state() to be called for next random number
}

void MTRand_int32::seed(const unsigned long* array, int size) { // init by array
  seed(19650218UL);
  int i = 1, j = 0;
  for (int k = ((n > size) ? n : size); k; --k) {
    state[i] = (state[i] ^ ((state[i - 1] ^ (state[i - 1] >> 30)) * 1664525UL))
      + array[j] + j; // non linear
    state[i] &= 0xFFFFFFFFUL; // for > 32 bit machines
    ++j; j %= size;
    if ((++i) == n) { state[0] = state[n - 1]; i = 1; }
  }
  for (int k = n - 1; k; --k) {
    state[i] = (state[i] ^ ((state[i - 1] ^ (state[i - 1] >> 30)) * 1566083941UL)) - i;
    state[i] &= 0xFFFFFFFFUL; // for > 32 bit machines
    if ((++i) == n) { state[0] = state[n - 1]; i = 1; }
  }
  state[0] = 0x80000000UL; // MSB is 1; assuring non-zero initial array
  p = n; // force gen_state() to be called for next random number
}

const float CONST_for_Rand = 1. / 4294967296.;

int MTRand::Next_int(int _min, int _max)
{
    return (int)( floor((_max-_min)*(static_cast<double>(rand_int32()) * CONST_for_Rand) + _min));
}

float MTRand::Next(float _min, float _max)
{
    return (_max-_min)*(static_cast<double>(rand_int32()) * CONST_for_Rand) + _min;
}

const float CONST_for_closed= 1. / 4294967295.;

int MTRand_closed::Next_int(int _min, int _max)
{
    return (int)( floor((_max-_min+1)*(rand_int32() * CONST_for_closed) + _min));
}

float MTRand_closed::Next(float _min, float _max)
{
    return (_max-_min)*(rand_int32() * CONST_for_closed) + _min;
}

int MTRand_open::Next_int(int _min, int _max)
{
    --_max;
    ++_min;
    return (int)( round((_max-_min)*((static_cast<double>(rand_int32()) + .5) * CONST_for_Rand) + _min));
}

float MTRand_open::Next(float _min, float _max)
{
    return (_max-_min)*((static_cast<double>(rand_int32()) + .5) * CONST_for_Rand) + _min;
}

const float CONST_for_Rand53 = 1. / 9007199254740992.;

int MTRand53::Next_int(int _min, int _max)
{
    return (int)( ceil((_max-_min)*((static_cast<double>(rand_int32() >> 5) * 67108864. +
      static_cast<double>(rand_int32() >> 6)) * CONST_for_Rand53) + _min));
}

float MTRand53::Next(float _min, float _max)
{
    return (_max-_min)*((static_cast<double>(rand_int32() >> 5) * 67108864. +
      static_cast<double>(rand_int32() >> 6)) * CONST_for_Rand53) + _min;
}
