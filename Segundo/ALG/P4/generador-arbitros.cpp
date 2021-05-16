double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

void generapuntuaciones() {

 int puntos=10; //las puntuaciones serán números reales entre 1 y 10
 srand(time(0));
 for (int i = 0; i < n; i++) 
   for (int j = 0; j < m; j++)  {
            double u=uniforme();
            p[i][j]=1+u*(puntos-1); //uniforme entre 1 y m
        }  
}

void generapartidos() { //genera una permutacion aleatoria de los equipos de 0 a n-1 y los empareja
			// el i con el i+n/2 (n es par)

  int * T = new int[n];
  assert(T);
srand(time(0));

for (int i=0; i<n; i++) T[i]=i;


for (int i=0; i<n; i++) 
  cout<< T[i]<<" ";

//algoritmo de random shuffling the Knuth (permutación aleatoria)
for (int j=n-1; j>0; j--) {
   double u=uniforme();
   int k=(int)(j*u);
   int tmp=T[j];
   T[j]=T[k];
   T[k]=tmp;
}

//Ahora hay que asociar el equipo i con el equipo i+n/2 para formar los partidos de esa jornada

}
