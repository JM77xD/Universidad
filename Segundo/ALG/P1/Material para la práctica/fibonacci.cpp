/**
   @file C�lculo de la sucesi�n de Fibonacci
*/

   
#include <iostream>
#include <chrono>
using namespace std;


/**
   @brief Calcula el t�rmino n-�simo de la sucesi�n de Fibonacci.

   @param n: n�mero de orden del t�rmino buscado. n >= 1.

   @return: t�rmino n-�simo de la sucesi�n de Fibonacci.
*/
int fibo(int n)
{
  if (n < 2)
    return 1;
  else
    return fibo(n-1) + fibo(n-2);
}


int main(int argc, char** argv)
{

  int n;
  int f;

  chrono::high_resolution_clock::time_point tantes, tdespues;
  chrono::duration<double> tiempo; 

  n = atoi(argv[1]);

  tantes = chrono::high_resolution_clock::now();

  f = fibo(n);

  tdespues = chrono::high_resolution_clock::now();

  tiempo = chrono::duration_cast<chrono::duration<double>> (tdespues - tantes);

  cout << n << " " << tiempo.count() << endl;

  return 0;
}
