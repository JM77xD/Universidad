
double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

void generamatriz() {
 srand(time(0));
 for (int i = 0; i < n; i++)
  for (int j = 0; j < n; j++) {
     double u=uniforme();
     m[i][j]=1+(int)((n-1)*u); //entero entre 1 y n-1
  }
}
