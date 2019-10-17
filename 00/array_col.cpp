#include <iostream>
#include "timer.h"

using namespace std;

int main()
{
  int const m = 1e3, n = 1e5;
  int** matrix;
  volatile long long sum = 0;
  matrix = new int*[m];
  for( int i = 0; i<m; i++)
    matrix[i] = new int[n];

  for( int i = 0; i<m; i++)
    for( int j = 0 ; j<n; j++)
      matrix[i][j] = 1;

  for(int k = 0; k<100; k++)
  {
    static Timer t;
    sum = 0;
    for( int j = 0; j<n; j++)
      for( int i = 0 ; i<m; i++)
        sum += matrix[i][j];
  }

  for( int i = 0; i<m; i++)
    delete [] matrix[i];

  delete [] matrix;


  return 0;

}
