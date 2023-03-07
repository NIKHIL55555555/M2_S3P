#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <thread>
#include <time.h>
#include <unistd.h>
#include <string>
#include <omp.h>

using namespace std;

#define NUM_THREADS 8
#define MAX 1000000

int data[MAX];
long global_sum = 0;

int main(int argc, char *argv[])
{
    int cores = std::thread::hardware_concurrency();
    cout << "The number of cores on this machine = " << cores << endl;

    for (int i = 0; i < MAX; i++)
    {
        data[i] = rand() % 20;
    }

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int tid = omp_get_thread_num();
        long sum = 0;
        int range = MAX / NUM_THREADS;
        int start = tid * range;
        int end = start + range;

        for (int i = start; i < end; i++)
        {
            sum += data[i];
        }

        #pragma omp critical
        {
            global_sum += sum;
        }
    }

    cout << "The final sum = " << global_sum << endl;

    return 0;
}
