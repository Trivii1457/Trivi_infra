#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"

using namespace std;


void fillVector(vector<long long> &v, int n)
{
    for (int i = 0; i < n; i++)
    {
        v.push_back(i);
    }
}

long long elevateP(vector<long long> &v, int p)
{
    tbb::parallel_for(tbb::blocked_range<int>(0, v.size()), [&](tbb::blocked_range<int> r){
        for (int i = r.begin(); i != r.end(); i++)
        {
            v[i] = static_cast<long long>(pow(v[i], p));
        }
    });
    return 0;
}

long long pSquare (long long n, int p)
{
    return static_cast<long long>(pow(n, 1/p));
}

long long sumP(vector<long long> &v)
{
    long long sum = 0;
    tbb::parallel_for(tbb::blocked_range<int>(0, v.size()), [&](tbb::blocked_range<int> r){
        for (int i = r.begin(); i != r.end(); i++)
        {
            sum += v[i];
        }
    });
    return sum;
}



int main(int argc, char const *argv[])
{
    tbb::task_scheduler_init init;
    vector<long long> v;
    fillVector(v, 1000000);
    vector <long long> a = elevateP(v, 2);
    pSquare(a, 2);
    cout << "Suma de los cuadrados: " << sumP(v) << endl;
    return 0;
}
