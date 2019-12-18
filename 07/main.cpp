#include "pthread.cpp"
#include <iostream>

using namespace std;

double sum(double a, double b)
{
    return a+b;
}

void print()
{
    cout<<"print"<<endl;
}

double dot(vector<double> &a, vector<double> &b)
{
    double dot = 0;
    for(int i=0; i<a.size(); i++)
        dot += a[i]*b[i];

    return dot;
}

int main()
{
    ThreadPool pool(10);
    auto task1 = pool.exec(sum, 1, 2);
    cout << task1.get()<< endl;

    auto task2 = pool.exec(print);

    vector<double> a, b;
    for(int i=1; i<100; i++)
    {
        a.push_back(i);
        b.push_back(1/i);
    }
    auto task3 = pool.exec(dot, a, b);
    cout << task3.get()<< endl;

    return 0;
}
