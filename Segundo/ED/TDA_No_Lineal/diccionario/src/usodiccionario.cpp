#include <iostream>
#include <fstream>
#include "diccionario.h"



/**
 * @brief Operator<<.
 * @note Obsérvese el uso de 2 tipos diferentes de iteradores.
 * Uno sobre listas de listas y otro sobre listas.
 */
ostream & operator<<(ostream & os, const Diccionario<string,string> & D){
	  
	  Diccionario<string,string>::const_iterator it;
	  
	  for (it=D.cbegin(); it!=D.cend(); ++it){
	  
		    list<string>::const_iterator it_s;
		    
		    os<<endl<<(*it).clave<<endl<<"\tInformacion asociada:"<<endl;
		    for (it_s=(*it).info_asoci.begin();it_s!=(*it).info_asoci.end();++it_s){
			      os<<(*it_s)<<endl;
		    }
		    os<<"**************************************"<<endl;
	  }
	  
	  return os;
}

/**
 * @brief Operador >>.
 * El formato de la entrada es:
 * numero de claves en la primera linea
 * clave-iésima
 * numero de informaciones asociadas en la siguiente linea
 * y en cada linea obviamente la informacion asociada
 */
istream & operator >>(istream & is,Diccionario<string,string> &D){
	  int np;
	  is>>np;
	  is.ignore();//quitamos \n
	  Diccionario<string,string> Daux;
	  for (int i=0;i<np; i++){
		    string clave;

		    getline(is,clave); 
		    
		    int ns;
		    is>>ns; 
		    is.ignore();//quitamos \n
		    list<string>laux;
		    for (int j=0;j<ns; j++){
			      string s;
			      getline(is,s);
			      
			      //	cout<<"Significado leido "<<s<<endl;
			      laux.insert(laux.end(),s);
		    }
		    Daux.Insertar(clave,laux);		      
		    
	  }
	  D=Daux;
	  return is;
}

/**
 * @ brief Recorre la lista de información asociada a una clave y la imprime
 */
void EscribeSigni(const list<string>&l){		 
	  list<string>::const_iterator it_s;
	  
	  for (it_s=l.begin();it_s!=l.end();++it_s){
		    cout<<*it_s<<endl;
	  }
}

/**
 * @brief Muestra por pantalla una lista de data<string,string>
 * 
 * @param os Flujo de salida
 * @param lista Lista a mostrar por pantalla
 * @return Devuelve un flujo de salida con los datos a mostrar
 */
ostream & operator<<(ostream &os, list<data<string,string>> &lista) {

	list<data<string,string>>::const_iterator it;

	for(it = lista.begin(); it != lista.end(); ++it) {

		list<string>::const_iterator it_s;

		os<<endl<<(*it).clave<<endl<<"\tInformacion asociada:"<<endl;
		for (it_s=(*it).info_asoci.begin();it_s!=(*it).info_asoci.end();++it_s){
		      os<<(*it_s)<<endl;
		}
		os<<"**************************************"<<endl;
	
	}

	return os;
}


/**
 * 
 * @brief Lee un diccioario e imprime datos asociados a una clave. 
 * Hay un fichero ejemplo de prueba: data.txt.Para lanzar el programa con ese fichero se escribe: 
 * ./usodiccionario < data.txt 
 */
int main(){
	Diccionario<string,string> D;
	ifstream d1, d2;
	d1.open("../data/data.txt");
	if (d1.good()) {
		d1 >> D;
		d1.close();
	} else {
		cerr << "\nNo se ha podido abrir el archivo\n\n";
		exit(1);
	}
	cout << "\t\tDiccionario 1:\n"<< D;
	string c1 = "Compilador", c2 = "Programa";
	list<data<string,string>> lista = D.rango(c1, c2);

	cout << "\n\n\t\tElementos entre " << c1 << " y " << c2 << ":\n" << lista;

	string s = "Sentencia";
	D.del(s);

	cout << "\n\n\t\tDiccionario una vez borrado 'Sentencia':\n" << D;

	Diccionario<string,string> D2;
	d2.open("../data/data2.txt");
	if (d2.good()) {
		d2 >> D2;
		d2.close();
	} else {
		cerr << "\nNo se ha podido abrir el archivo\n\n";
		exit(1);
	}
	cout << "\n\n\t\tDiccionario 2:\n" << D2;

	Diccionario<string,string> dif = D.diferencia(D2);
	cout << "\n\n\t\tDiferencia entre los diccionarios:\n" << dif << endl;

	Diccionario<string,string> un = D.unir(D2);
	cout << "\n\n\t\tUnión entre los diccionarios:\n" << un << endl;

}

