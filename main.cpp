#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "mtrand.h"

using namespace std;
const int SIZENUMS= 100000000;

clock_t start, endt;
double msecs;

void Start_record()
{
    start = clock();
}

void Stop_record()
{
    endt = clock();
}

void Calculate_dif()
{
    msecs = ((double) (endt - start)) / CLOCKS_PER_SEC;
    cout << msecs  << " ms"<< endl;
}

int main()
{
    cout << "Generating 100,000,000 random number by each method:"<<endl;

    MTRand random_rand;
    cout << "MTRand [0, 1):\n" << endl;
    float numner;
    Start_record();
    for (int i = 0; i < SIZENUMS; ++i)
    {
        numner= random_rand.Next(0.0f, 100.0f);
    }
    Stop_record();
    Calculate_dif();

    MTRand_closed random_closed;
    cout << endl;
    cout << "MTRand_closed  [0, 1]:\n" << endl;
    Start_record();
    for (int i = 0; i < SIZENUMS; ++i)
    {
        numner= random_closed.Next(0.0f, 100.0f);
    }
    Stop_record();
    Calculate_dif();

    MTRand_open random_opend;
    cout << endl;
    cout << "MTRand_open (0, 1):\n" << endl;
    Start_record();
    for (int i = 0; i < SIZENUMS; ++i)
    {
        numner= random_opend.Next(0.0f, 100.0f);
    }
    Stop_record();
    Calculate_dif();

    MTRand53 random_rand53;
    cout << endl;
    cout << "MTRand53 53 bits [0, 1):\n" << endl;
    Start_record();
    for (int i = 0; i < SIZENUMS; ++i)
    {
        numner= random_rand53.Next(0.0f, 100.0f);
    }
    Stop_record();
    Calculate_dif();



    return 0;
}
