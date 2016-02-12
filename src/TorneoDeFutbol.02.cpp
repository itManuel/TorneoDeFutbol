#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include "torneo.h"
#include "torneo.cpp"
#include "TorneoDeFutbol.01.cpp"
#define NULO 105
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Nodo{
	int fecha;
	int partido;
	int local;
	int visitante;
	int golesLocal;
	int golesVisitante;
	Nodo *sgte;
};

struct Posiciones{
	int PJ;
	int PG;
	int PP;
	int PE;
	int GF;
	int GC;
	int DG;
	int puntos;
	int posicion;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuSimulacion(Equipo equipos [], int &cantEquipos, Nodo *&puntero); 
void MenuPrincipal (Equipo equipos [], int &cantEquipos, Nodo *&puntero); 
void Simular (Equipo equipos [], int &cantEquipos, Nodo *&puntero);
bool ListaEstaVacia(Nodo *puntero);
void PonerEnLista(Equipo equipos [],Nodo *&puntero, int fecha, int partido, int local, int visitante, int golesLocal, int golesVisitante);
void SacarDeLista(Nodo *&puntero);
void PartidosPorEquipo (Equipo equipos [],int cantEquipos,Nodo *puntero);
void EquipoEstaRegistrado(Equipo equipos[],int cantEquipos,Nodo *puntero,int &posLocal,int &posVisitante);
void TablaDePosiciones (Equipo equipos [],int cantEquipos,Nodo *puntero);
void PartidosPorFecha(Equipo equipos [],int cantEquipos,Nodo *puntero);
void generarPartido (int equipos, int fecha, int partido, short &local, short &visitante);


void MezclarEquipos(Equipo equipos [], int cantEquipos);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main (){ 
	int cantEquipos = 0;
	Equipo equipos [MAX_EQUIPOS];
	Nodo *puntero = NULL;
	CargarEquipos(equipos, cantEquipos);
    MenuPrincipal (equipos, cantEquipos, puntero);
	return 0;
}


void MenuPrincipal(Equipo equipos[MAX_EQUIPOS], int &cantEquipos,Nodo *&puntero){
	
	// muestra el menu y devuelve la opcion seleccionada
	// Manuel

	int opcion=9;
	while(opcion!=0){
		MuestroEncabezado();
		cout << "|              Menu Principal                                              ||" << endl;
		cout << "|              1. Editar Equipos                                           ||" << endl;
		cout << "|              2. Simular                                                  ||" << endl;
		cout << "|              0. Salir                                                    ||" << endl;
		cout << "|                                                                          ||" << endl;
		MuestroPie();
		cout << endl;
		cout << " Ingrese su opcion (y presione 'enter'): ";
		cin >> opcion;
		switch (opcion){
			case 1:
				TorneoDeFutbol01(equipos, cantEquipos);
		
				break;
			case 2:
				cout<<endl<<endl;
				if (cantEquipos<2){
					cout<<endl<<endl<<"No hay equipos suficientes para realizar la simulacion"<<endl<<endl;
				}
				else{
					Simular (equipos, cantEquipos, puntero);
					MenuSimulacion(equipos, cantEquipos, puntero);
					while(!ListaEstaVacia(puntero)){
						SacarDeLista(puntero);
					}
				}
				break;
	
			case 0:
				cout << "SALIR" << endl;;
				break;
			default:
				cout << opcion << " no es una opcion valida, intente nuevamente" << endl;
		}
	}
	return;
}


void MenuSimulacion(Equipo equipos[],int &cantEquipos,Nodo *&puntero){
// muestra el menu de Simulacion y devuelve la opcion seleccionada
	// Manuel

	int opcion=9;
	while(opcion!=0){
		MuestroEncabezado();
		cout << "|              Menu Simulacion                                             ||" << endl;
		cout << "|              1. Ver Tabla de Posiciones                                  ||" << endl;
		cout << "|              2. Ver Partidos por equipo                                  ||" << endl;
		cout << "|              3. Ver Partidos por fecha                                   ||" << endl;
		cout << "|              0. Volver                                                   ||" << endl;
		MuestroPie();
		cout << endl;
		cout << " Ingrese su opcion (y presione 'enter'): ";
		cin >> opcion;
		switch (opcion){
			case 1:
				TablaDePosiciones (equipos,cantEquipos,puntero);
				break;
			case 2:
				PartidosPorEquipo(equipos,cantEquipos,puntero);
				break;
			case 3:
				PartidosPorFecha(equipos,cantEquipos,puntero);
				break;
			case 0:
				cout << "SALIR" << endl;;
				break;
			default:		
			cout << opcion << " no es una opcion valida, intente nuevamente" << endl;
		}
	}
	return;
}


bool ListaEstaVacia(Nodo *partidos){
	return(partidos==NULL);
}


void PonerEnLista(Equipo equipos[], Nodo *&puntero, int fecha, int partido, int local, int visitante, int golesLocal, int golesVisitante){
	
	Nodo *nodo=new Nodo;
	nodo->fecha=fecha;
	nodo->partido=partido;
	nodo->local=local;
	nodo->visitante=visitante;
	nodo->golesLocal=golesLocal;
	nodo->golesVisitante=golesVisitante;
	nodo->sgte=puntero;
	puntero=nodo;
}


void SacarDeLista(Nodo *&puntero){
	Nodo *viejo;
	viejo=puntero;
	puntero=puntero->sgte;
}


void Simular (Equipo equipos[], int &cantEquipos, Nodo *&puntero){
	
    int local=0;
	int visitante=0;
	int golesLocal=0;
	int golesVisitante=0;
	int totalFechas=0;
	int totalPartidos=0;
	int i;
	
	if (cantEquipos / 2 == 0){
		totalFechas=cantEquipos-1;
	}
	else {
		totalFechas=cantEquipos;
	}
	
	totalPartidos=cantEquipos/2;

	MezclarEquipos(equipos, cantEquipos);

	for (int fecha=totalFechas; fecha>0 && fecha < 100 ; fecha--){
		for(int partido=totalPartidos; partido>0 ; partido--){
			generarPartido (cantEquipos,fecha,partido,local,visitante);
			simularPartido (equipos[local].potenciaAtaque,equipos[local].potenciaDefensa,equipos[visitante].potenciaAtaque,equipos[visitante].potenciaDefensa,golesLocal,golesVisitante);	
			PonerEnLista(equipos, puntero,fecha, partido,local,visitante,golesLocal,golesVisitante);
			
		}		
	}
	
}


void MezclarEquipos(Equipo equipos[], int cantEquipos){

bool existe;
int i=0, v[100], num;
Equipo equiposaux[100];

  srand(time(NULL)); // A la semilla le asigno la hora del sistema
 
  for(i=0;i<cantEquipos;i++){ //inicializo el vector
  	v[i]=NULO;
  }

   
 while(v[cantEquipos-1]==NULO){			//Se realiza el loop hasta que el ultimo elemento del vector tenga un numero random 
 existe=false;
 	
  	num=rand()%(cantEquipos);	// Genero numeros random 
  	
	for(i=0;i<cantEquipos;i++){		//Verifica que el numero random sea distinto a todos los del vector. 
	 	if(num==v[i]){
	 		existe=true;
	 	}
		}
 
 	if(existe==false){		
 		i=0;
 		while(v[i]!=NULO){
 			i=i+1;
			 }
	 	   v[i]=num;
	 	
		}
	    
    }

for(i=0;i<cantEquipos;i++){
	equiposaux[i]=equipos[v[i]];	
	}
	
for(i=0;i<cantEquipos;i++){
	equipos[i]=equiposaux[i];
		
	}		
}


void PartidosPorEquipo (Equipo equipos[],int cantEquipos, Nodo *puntero){
	
	Equipo equipo;
	bool existe;
	int pos;
	cout<<endl<<endl<<"Ingrese el id del equipo a consultar: ";
	cin>>equipo.id;
	pos=PosicionEquipo(equipos,cantEquipos,equipo.id);
	equipo=equipos[pos];
	MuestroEncabezado();
	cout << "|              "<<"Partidos de "<<equipos[pos].nombre<<endl<<endl;
	
	while(!ListaEstaVacia(puntero)){
		if(strcmp(equipo.id,equipos[puntero->local].id)==0){
			cout << "|              "<<equipos[puntero->local].id<<"  "<<equipos[puntero->local].nombre<<"          "<<puntero->golesLocal<<" - "<<puntero->golesVisitante<<"          "<<equipos[puntero->visitante].nombre<<"  "<<equipos[puntero->visitante].id<<endl;
		}
		else if (strcmp(equipo.id,equipos[puntero->visitante].id)==0){
			cout << "|              "<<equipos[puntero->local].id<<"  "<<equipos[puntero->local].nombre<<"          "<<puntero->golesLocal<<" - "<<puntero->golesVisitante<<"          "<<equipos[puntero->visitante].nombre<<"  "<<equipos[puntero->visitante].id<<endl;
		}
		SacarDeLista(puntero);
	}
	MuestroPie();
}


void PartidosPorFecha(Equipo equipos[],int cantEquipos,Nodo *puntero){
	
	int fecha=0;
	int totalFechas=0,x=0;
	
	if (cantEquipos / 2 == 0){
		totalFechas=cantEquipos-1;
	}
	else {
		totalFechas=cantEquipos;
	}

	cout<<endl<<endl<<"Ingrese una fecha (entre 1 y "<<totalFechas<<"): ";
	cin>>fecha;
	MuestroEncabezado();
	cout << "|              "<<"puntero de la fecha "<<fecha<<endl<<endl;
	
	while(!ListaEstaVacia(puntero)){
		
		if(puntero->fecha==fecha){
			cout << "|              "<<equipos[puntero->local].id<<"  "<<equipos[puntero->local].nombre<<"          "<<puntero->golesLocal<<" - "<<puntero->golesVisitante<<"          "<<equipos[puntero->visitante].nombre<<"  "<<equipos[puntero->visitante].id<<endl;
		
		}
	
			SacarDeLista(puntero);
		
	}	
	MuestroPie();
}


void EquipoEstaRegistrado(Posiciones array[],Nodo *puntero, int cantEquipos,int &posLocal,int &posVisitante){
	int i=0;
	bool existeLocal=false,existeVisitante=false;

	
	for(i=0;i<cantEquipos;i++){
	  if(array[i].posicion==puntero->local){
		existeLocal=true;
		posLocal=i;
		}
	  if(array[i].posicion==puntero->visitante){
		existeVisitante=true;
		posVisitante=i;
		}	
		}
		if(existeLocal==false){
		posLocal=cantEquipos;
	}
		if(existeVisitante==false){
		posVisitante=cantEquipos;
	}
	
}


void TablaDePosiciones(Equipo equipos[],int cantEquipos,Nodo *puntero){

int fecha=0, totalFechas=0,i=0, posLocal,posVisitante;
Posiciones array[100];
	
	if (cantEquipos / 2 == 0){
		totalFechas=cantEquipos-1;
	}
	else {
		totalFechas=cantEquipos;
	}

	cout<<endl<<endl<<"Ingrese una fecha (entre 1 y "<<totalFechas<<"): ";
	cin>>fecha;

for(i=0;i<cantEquipos;i++){
array[i].DG=0;
array[i].GF=0;
array[i].GC=0;
array[i].PE=0;
array[i].PG=0;
array[i].PP=0;
array[i].PJ=0;
array[i].puntos=0;
array[i].posicion=NULO;
}

int local=0, visitante=1,local1,visitante1;
while(!ListaEstaVacia(puntero)){
	
		if(puntero->fecha <= fecha){
			EquipoEstaRegistrado(array, puntero, cantEquipos,posLocal,posVisitante);
			
			if (posLocal == cantEquipos) { // equipo nuevo	
			array[local].PJ=array[local].PJ+1;
			array[local].GF=array[local].GF+puntero->golesLocal;
			array[local].GC=array[local].GC+puntero->golesVisitante;
			array[local].posicion=puntero->local;
			local1=local;
			local=local+2;
			}
			else{//equipo ya guardado
			array[posLocal].PJ=array[posLocal].PJ+1;
			array[posLocal].GF=array[posLocal].GF+puntero->golesLocal;
			array[posLocal].GC=array[posLocal].GC+puntero->golesVisitante;
			array[posLocal].posicion=puntero->local;
			local1=posLocal;		
			}
			
			if (posVisitante == cantEquipos) { // equipo nuevo	
			array[visitante].PJ=array[visitante].PJ+1;
			array[visitante].GF=array[visitante].GF+puntero->golesVisitante;
			array[visitante].GC=array[visitante].GC+puntero->golesLocal;
			array[visitante].posicion=puntero->visitante;
			visitante1=visitante;
			visitante= visitante+2;
			}
			else{//equipo ya guardado
			array[posVisitante].PJ=array[posVisitante].PJ+1;
			array[posVisitante].GF=array[posVisitante].GF+puntero->golesVisitante;
			array[posVisitante].GC=array[posVisitante].GC+puntero->golesLocal;
			array[posVisitante].posicion=puntero->visitante;
			visitante1=posVisitante;	
			}
			
			if(puntero->golesLocal>puntero->golesVisitante){
				array[local1].PG=array[local1].PG+1;
				array[visitante1].PP=array[visitante1].PP+1;
				array[local1].puntos=array[local1].puntos+3;
						
			}
			else if(puntero->golesLocal<puntero->golesVisitante){
				array[local1].PP=array[local1].PP+1;
				array[visitante1].PG=array[visitante1].PG+1;
				array[visitante1].puntos=array[visitante1].puntos+3;
			}
			else{
			
				array[local1].PE=array[local1].PE+1;
				array[visitante1].PE=array[visitante1].PE+1;
				array[local1].puntos=array[local1].puntos+1;
				array[visitante1].puntos=array[visitante1].puntos+1;
			}	
		}
			SacarDeLista(puntero);
}

for(i=0;i<cantEquipos;i++) {// Si DG es negativo se lo hace positivo
	array[i].DG=array[i].GF-array[i].GC;
	if(array[i].DG<0){
	array[i].DG=array[i].DG*(-1);
	}
}


Posiciones temp;
for(i=0;i<cantEquipos;i++) {
                for(int j=0;j<100-1;j++) {
				
                    if(array[j].puntos<array[j+1].puntos){
                        temp=array[j]; 
                        array[j]=array[j+1]; 
                        array[j+1]=temp;
						} 
}
}

		
cout<<"Equipo			Puntos PJ PG PE	PP GF  GC DG "<<endl;
for(i=0;i<cantEquipos;i++){
	if(array[i].PJ>0){
	cout<<equipos[array[i].posicion].id<<" "<<equipos[array[i].posicion].nombre<<"		"<<array[i].puntos<<" 	"<<array[i].PJ<<" "<<array[i].PG<<"  "<<array[i].PE<<"	"<<array[i].PP<<"  "<<array[i].GF<<"   "<<array[i].GC<<" "<<array[i].DG<<endl;		
	}
}

}






	
	


		


