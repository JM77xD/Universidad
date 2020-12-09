#include "guiatlf.h"
#include <fstream>
using namespace std;

int main(){
	Guia_Tlf g;
	string g1, g2;
	ifstream guia1,guia2;
	cout<<"Introduce el nombre de una guia"<<endl;
	cin >> g1;
	guia1.open("../data/" + g1 + ".txt");
	if (guia1.good()) {
		guia1>>g;
		guia1.close();
	} else {
		cerr << "\n\nNo se pudo abrir la guía, asegurese de estar ejecutando el programa desde el directorio bin de la carpeta.\n\n";
		exit(1);
	}
 	cout<<"La guia insertada\n"<<g<<endl;
	cin.ignore(1000000, '\n');
	cout<<"Dime un nombre sobre el que quieres obtener el telefono (-1 para acabar)"<<endl;
	string n;
	getline(cin,n);
	while (n != "-1" ){
		cout<<"Buscando "<<n<<"...."<<endl;
		string tlf = g.gettelefono(n);
		if (tlf==""){
		    cout<<"No existe ese nombre en la guia"<<endl;
		}
		else 
		 cout<<"El telefono es "<<tlf<<endl;
		cout<<"Dime un nombre sobre el que quieres obtener el telefono (-1 para acabar)"<<endl;
		getline(cin,n);
	}

	cout << "\nDime un nombre para modificar su número de teléfono: ";
	string modificar;
	getline(cin, modificar);
	cout << "\nDime el nuevo número de teléfono: ";
	string telefono;
	getline(cin, telefono);
	g.modificar(modificar, telefono);

	cout << "\nDime una letra para mostrar los teléfonos que empiecen por ese nombre ";
	char letra;
	cin >> letra;
	cout << g.gettelefonos(letra) << endl;
	cin.ignore(1000000, '\n');

	cout << "\nDime 2 nombres para mostrar los teléfonos en es rango (separados por espacios)\n";
	string n1, n2;
	cin >> n1 >> n2;
	cin.ignore(1000000, '\n');
	Guia_Tlf rango = g.rango(n1, n2);
	cout << "\nLos teléfonos en ese rango son\n" << rango << endl;
	
	cout<<"Dime el nombre que quieres borrar (-1 para acabar)"<<endl;
	getline(cin,n);
	while (n != "-1"){
		g.borrar(n);
		cout<<"Ahora la guia es:"<<endl;
		cout<<g<<endl;
		cout<<"Dime el nombre que quieres borrar (-1 para acabar)"<<endl;
		getline(cin,n);
	}
	
	Guia_Tlf otraguia;
	cout<<"Introduce el nombre de otra guia"<<endl;
	cin >> g2;
	guia2.open("../data/" + g2 + ".txt");
	if (guia2.good()) {
		guia2>>otraguia;
		guia2.close();
	} else {
		cerr << "\n\nNo se pudo abrir la guía, asegurese de estar ejecutando el programa desde el directorio bin de la carpeta.\n\n";
		exit(1);
	}
	cout<<"La guia insertada\n"<<otraguia<<endl;
	cin.clear();
	Guia_Tlf un = g+otraguia;
	Guia_Tlf dif = g-otraguia;
	Guia_Tlf inter = g.interseccion(otraguia);

	cout<<"La union de las dos guias: "<<endl <<un<<endl;

	cout<<"La diferencia de las dos guias:"<<endl <<dif<<endl;

	cout << "La intersección de las dos guías:\n" << inter << endl;
}
