#include <iostream>
#include <stdio.h>  
#include <string.h> 
#include <conio.h>
using namespace std;
const char *nombre_archivo = "archivo.txt";
const char *nombre_auxarchivo = "auxarchivo.txt";

struct Ptraductor{
	char palabra[50];
	char traduccion[50];
	char definicion[30000];

};
void crear();
void leer();
void buscar();
void actualizar();
void borrar();
void final();

int main (){
	int menu;
	
	do {
		system("cls");
		
		cout<<"\n\t\t\t\t\t\t\t MENU PRINCIPAL\n";
		cout<<"\n\t\t1. INGRESAR PALABRAS\n";
		cout<<"\n\t\t2. MOSTRAR LISTA DE PALABRAS\n";
		cout<<"\n\t\t3. BUSCAR POR PALABRAS\n";
		cout<<"\n\t\t4. MODIFICAR PALABRAS\n";
		cout<<"\n\t\t5. ELIMINAR PALABRAS\n";
		cout<<"\n\t\t6. TRADUCIR CODIGO C++\n";
		cout<<"\n\t\t7. TRABAJO REALIZADO C++\n";
		cout<<"\n\t\t8. SALIR\n";
		cout<<"\n\t\t\t INGRESE LO QUE DESEA EJECUTAR: ";
		cin>>menu;
		system("cls");
		
		switch(menu){
			case 1 : 
				 crear();
			break;
			case 2 : 
				 leer();
			break;
			case 3 : 
				 buscar();
			break;
			case 4 : 
				 actualizar();
			break;
			case 5 : 
				 borrar();
			break;
			
			case 7 : 
				 final();
			break;
		
		}
	}while(menu<=7);
	return 0;	
}
void crear(){
char continuar;
	FILE* archivo = fopen(nombre_archivo, "ab"); // ab
	
	
		Ptraductor ptraductor;
		 string palabra,definicion,traduccion;
		do{
			fflush(stdin);
			
        cout<<"\n\t\t\t\t\t\t INGRESO DE PALABRAS \n";
        
		cout<<"\n\t Ingrese Palabra: ";
		getline(cin,palabra);
    	strcpy(ptraductor.palabra, palabra.c_str()); 
			
		cout<<"\n\t Ingrese Traduccion: ";
		getline(cin,traduccion);
    	strcpy(ptraductor.traduccion, traduccion.c_str()); 
		
		cout<<"\n\t Ingrese Definicion: ";
		getline(cin,definicion);
		strcpy(ptraductor.definicion, definicion.c_str());
	
		fwrite( &ptraductor, sizeof(Ptraductor), 1, archivo );
		cout<<"\n\t\t Desea Agregar otra Palabra s/n : ";
		cin>>continuar;
		} while((continuar=='s') || (continuar=='S') );
	
	fclose(archivo);
	leer();
	system("PAUSE");

}

void leer(){
	system("cls");
	FILE* archivo = fopen(nombre_archivo, "rb");
	if(!archivo) {
		archivo = fopen(nombre_archivo, "w+b");
	}
	Ptraductor ptraductor;
	int nump=0;
	fread ( &ptraductor, sizeof(Ptraductor), 1, archivo );
		do{
	cout << "_______________________________________________"<<endl;
	cout << "\n No. de Palabra: "<<nump<<endl;
	cout << "\n Palabra: "<<ptraductor.palabra<<endl;
	cout << "\n Traduccion: "<<ptraductor.traduccion<<endl;
	cout << "\n Definicion: "<<ptraductor.definicion<<endl;
    cout << "________________________________________________"<<endl;   
		fread ( &ptraductor, sizeof(Ptraductor), 1, archivo );
		nump += 1;	
		} while (feof( archivo ) == 0);
    cout<<endl;
    
		fclose(archivo);
		system("PAUSE");
}
void buscar(){
	FILE* archivo = fopen(nombre_archivo, "rb");
	
	int nump;
	cout<<"\n\t\t\t Ingrese el numero de la palabra que desea ver: ";
	cin>>nump;
	
	fseek ( archivo,nump * sizeof(Ptraductor), SEEK_SET );
	
	Ptraductor ptraductor;
	
    fread ( &ptraductor, sizeof( Ptraductor ), 1, archivo );
    cout<<"\n\t\t\t\t\t\t LA PALABRA QUE USTED BUSCO \n";
		cout << "_________________________________________________"<<nump<<endl;
    	cout << "\n Palabra: " << ptraductor.palabra<< endl;
    	cout << "\n Traduccion: " << ptraductor.traduccion<< endl;
    	cout << "\n Definicion: " << ptraductor.definicion<< endl;
    	cout << "__________________________________________________"<<nump<<endl;
	fclose(archivo);
	system("PAUSE");
}
void actualizar(){
	
	FILE* archivo = fopen(nombre_archivo, "r+b");
	
		int nump;
		string palabra,traduccion,definicion;	
    	Ptraductor ptraductor;
    
		cout << "\n\t\t\t\t\t\t Ingrese el numero que desea modificar: ";
    		cin >> nump;
    	fseek ( archivo, nump * sizeof(Ptraductor), SEEK_SET );  // esto es lo que permite modificar en la pocision
		
		fflush(stdin);
	
		cout<<"\n\t\t Ingrese Palabra: ";
		getline(cin,palabra);
    	strcpy(ptraductor.palabra, palabra.c_str()); 
			
		cout<<"\n\t\t Ingrese Traduccion: ";
		getline(cin,traduccion);
    	strcpy(ptraductor.traduccion, traduccion.c_str()); 
		
		cout<<"\n\t\t Ingrese Definicion: ";
		getline(cin,definicion);
		strcpy(ptraductor.definicion, definicion.c_str());
		cin.ignore();
		fwrite( &ptraductor, sizeof(Ptraductor), 1, archivo );
		
	fclose(archivo);
	system("PAUSE");
}

void borrar(){
	FILE* archivo = fopen(nombre_archivo, "r+b");
	FILE* auxarchivo = fopen(nombre_auxarchivo, "a+b");
	
		int nump,cod;
	
    	Ptraductor ptraductor;
    
		cout << "\n\t\t Ingrese el numero que desea Eliminar: ";
    		cin >> cod;
    	fseek ( archivo, cod * sizeof(Ptraductor), SEEK_SET ); 
	
		do{
			
			if (nump == cod){
			cout<<"\n\t\t EL REGISTRO HA SIDO ELIMINADO";
			
			}
			else {
			fwrite( &ptraductor, sizeof(Ptraductor), 1, auxarchivo );
		}
		fread ( &ptraductor, sizeof(Ptraductor), 1, archivo );
		
		} while (feof( archivo ) == 0);
		
	    		
		fclose(archivo);
		fclose(auxarchivo);
	    
		remove("archivo.txt");
		rename("auxarchivo.txt","archivo.txt");
		cout<<"\n\n";
		system("pause");
}

void final(){
	
	cout<<"\n\t\t\t\t\t\t PROYECTO TRADUCTOR \n";
	cout<<"\n\t\t\t\t\t UNIVERSIDAD MARIANO GALVEZ DE GUATEMALA \n";
	cout<<"\n\t\t DENY CONINE LEON HERNANDEZ      3590-21-1172\n";
	cout<<"\n\t\t CLEIMI YANETH PINEDA GARCIA      3590-21-926\n"<<endl;
		
		system("pause");
		system("cls");
}
