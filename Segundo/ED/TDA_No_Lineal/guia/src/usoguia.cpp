#include "guiatlf.h"
#include <fstream>
using namespace std;

int main(){
	Guia_Tlf g;
	string g1, g2;
	ifstream guia1,guia2;
	cout<<"Introduce una guia"<<endl;
	cin >> g1;
	guia1.open("../data/" + g1 + ".txt");
	guia1>>g;
	guia1.close();
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
	cout<<"Introduce otra guia"<<endl;
	cin >> g2;
	guia2.open("../data/" + g2 + ".txt");
	guia2>>otraguia;
	guia2.close();
	cout<<"La guia insertada\n"<<otraguia<<endl;
	cin.clear();
	Guia_Tlf un = g+otraguia;
	Guia_Tlf dif = g-otraguia;

	cout<<"La union de las dos guias: "<<endl <<un<<endl;

	cout<<"La diferencia de las dos guias:"<<endl <<dif<<endl;
}
