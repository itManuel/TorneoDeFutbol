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
void MenuSimulacion(Equipo equipos [], int &cantEquipos, Nodo *&partidos); 
void MenuPrincipal (Equipo equipos [], int &cantEquipos, Nodo *&partidos); 
void Simular (Equipo equipos [], int &cantEquipos, Nodo *&partidos);
bool ListaEstaVacia(Nodo *partidos);
void PonerEnLista(Equipo equipos [],Nodo *&partidos, int fecha, int partido, int local, int visitante, int golesLocal, int golesVisitante);
void SacarDeLista(Nodo *&partidos);
void PartidosPorEquipo (Equipo equipos [],int cantEquipos,Nodo *partidos);
void EquipoEstaRegistrado(Equipo equipos[],int cantEquipos,Nodo *partidos,int &posLocal,int &posVisitante);
void TablaDePosiciones (Equipo equipos [],int cantEquipos,Nodo *partidos);
void PartidosPorFecha(Equipo equipos [],int cantEquipos,Nodo *partidos);
void generarPartido (int equipos, int fecha, int partido, short &local, short &visitante);
void MezclarEquipos(Equipo equipos [], int cantEquipos);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main (){ 
	int cantEquipos = 0;
	Equipo equipos [100];
	Nodo *partidos = NULL;
	CargarEquipos(equipos, cantEquipos);
    MenuPrincipal (equipos, cantEquipos, partidos);
	return 0;
}


void MenuPrincipal(Equipo equipos[MAX_EQUIPOS], int &cantEquipos,Nodo *&partidos){
	
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
				TorneoDeFutbol01();
				break;
			case 2:
				cout<<endl<<endl;
				if (cantEquipos<2){
					cout<<endl<<endl<<"No hay equipos suficientes para realizar la simulacion"<<endl<<endl;
				}
				else{
					Simular (equipos, cantEquipos, partidos);
					MenuSimulacion(equipos, cantEquipos, partidos);
					while(!ListaEstaVacia(partidos)){
						SacarDeLista(partidos);
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


void MenuSimulacion(Equipo equipos[],int &cantEquipos,Nodo *&partidos){
// muestra el menu de Simulacion y devuelve la opcion seleccionada
	// Manuel

	int opcion=9;
	while(opcion!=0){
		MuestroEncabezado();
		cout << "|              Menu Simulacion                                             ||" << endl;
		cout << "|              1. Ver Tabla de Posiciones                                  ||" << endl;
		cout << "|              2. Ver partidos por equipo                                  ||" << endl;
		cout << "|              3. Ver partidos por fecha                                   ||" << endl;
		cout << "|              0. Volver                                                   ||" << endl;
		MuestroPie();
		cout << endl;
		cout << " Ingrese su opcion (y presione 'enter'): ";
		cin >> opcion;
		switch (opcion){
			case 1:
				TablaDePosiciones (equipos,cantEquipos,partidos);
				break;
			case 2:
				PartidosPorEquipo(equipos,cantEquipos,partidos);
				break;
			case 3:
				PartidosPorFecha(equipos,cantEquipos,partidos);
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
	if(partidos==NULL){
		return true;
	}else{
		return false;	
	}	
}


void PonerEnLista(Equipo equipos[], Nodo *&partidos, int fecha, int partido, int local, int visitante, int golesLocal, int golesVisitante){
	
	Nodo *nodo=new Nodo;
	nodo->fecha=fecha;
	nodo->partido=partido;
	nodo->local=local;
	nodo->visitante=visitante;
	nodo->golesLocal=golesLocal;
	nodo->golesVisitante=golesVisitante;
	nodo->sgte=partidos;
	partidos=nodo;
}


void SacarDeLista(Nodo *&partidos){
	Nodo *viejo;
	viejo=partidos;
	partidos=partidos->sgte;
}


void Simular (Equipo equipos[], int &cantEquipos, Nodo *&partidos){
	
    int local=0;
	int visitante=0;
	int golesLocal=0;
	int golesVisitante=0;
	int totalFechas=0;
	int totalPartidos=0;
	int i;
	
	if (cantEquipos % 2 == 0){
		totalFechas=cantEquipos-1;
	}
	else {
		totalFechas=cantEquipos;
	}
	
	totalPartidos=floor(double (cantEquipos/2));

	MezclarEquipos(equipos, cantEquipos);

	for (int fecha=totalFechas; fecha>0 && fecha < 100 ; fecha--){
		for(int partido=totalPartidos; partido>0 && partido < 50; partido--){
			generarPartido (cantEquipos,fecha,partido,local,visitante);
			simularPartido (equipos[local].potenciaAtaque,equipos[local].potenciaDefensa,equipos[visitante].potenciaAtaque,equipos[visitante].potenciaDefensa,golesLocal,golesVisitante);	
			PonerEnLista(equipos, partidos,fecha, partido,local,visitante,golesLocal,golesVisitante);
			
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


void PartidosPorEquipo (Equipo equipos[],int cantEquipos, Nodo *partidos){
	
	Equipo equipo;
	bool existe;
	int pos;
	cout<<endl<<endl<<"Ingrese el id del equipo a consultar: ";
	cin>>equipo.id;
	pos=PosicionEquipo(equipos,cantEquipos,equipo.id);
	equipo=equipos[pos];
	MuestroEncabezado();
	cout << "|              "<<"Partidos de "<<equipos[pos].nombre<<endl<<endl;
	
	while(!ListaEstaVacia(partidos)){
		if(strcmp(equipo.id,equipos[partidos->local].id)==0){
			cout << "|              "<<equipos[partidos->local].id<<"  "<<equipos[partidos->local].nombre<<"          "<<partidos->golesLocal<<" - "<<partidos->golesVisitante<<"          "<<equipos[partidos->visitante].nombre<<"  "<<equipos[partidos->visitante].id<<endl;
			SacarDeLista(partidos);
		}
		else if (strcmp(equipo.id,equipos[partidos->visitante].id)==0){
			cout << "|              "<<equipos[partidos->local].id<<"  "<<equipos[partidos->local].nombre<<"          "<<partidos->golesLocal<<" - "<<partidos->golesVisitante<<"          "<<equipos[partidos->visitante].nombre<<"  "<<equipos[partidos->visitante].id<<endl;
			SacarDeLista(partidos);
		}
		else{
			SacarDeLista(partidos);
		}
	}
	MuestroPie();
}


void PartidosPorFecha(Equipo equipos[],int cantEquipos,Nodo *partidos){
	
	int fecha=0;
	int totalFechas=0,x=0;
	
	if (cantEquipos % 2 == 0){
		totalFechas=cantEquipos-1;
	}
	else {
		totalFechas=cantEquipos;
	}

	cout<<endl<<endl<<"Ingrese una fecha (entre 1 y "<<totalFechas<<"): ";
	cin>>fecha;
	MuestroEncabezado();
	cout << "|              "<<"Partidos de la fecha "<<fecha<<endl<<endl;
	
	while(!ListaEstaVacia(partidos)){
		
		if(partidos->fecha==fecha){
			cout << "|              "<<equipos[partidos->local].id<<"  "<<equipos[partidos->local].nombre<<"          "<<partidos->golesLocal<<" - "<<partidos->golesVisitante<<"          "<<equipos[partidos->visitante].nombre<<"  "<<equipos[partidos->visitante].id<<endl;
			SacarDeLista(partidos);
		}
		else{
			SacarDeLista(partidos);
		}
	}	
	MuestroPie();
}


void EquipoEstaRegistrado(Posiciones v[],Nodo *partidos, int cantEquipos,int &posLocal,int &posVisitante){
	int i=0;
	bool existeLocal=false,existeVisitante=false;

	
	for(i=0;i<cantEquipos;i++){
	  if(v[i].posicion==partidos->local){
		existeLocal=true;
		posLocal=i;
		}
	  if(v[i].posicion==partidos->visitante){
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


void TablaDePosiciones(Equipo equipos[],int cantEquipos,Nodo *partidos){

int fecha=0, totalFechas=0,i=0, posLocal,posVisitante;
Posiciones v[100];
	
	if (cantEquipos % 2 == 0){
		totalFechas=cantEquipos-1;
	}
	else {
		totalFechas=cantEquipos;
	}

	cout<<endl<<endl<<"Ingrese una fecha (entre 1 y "<<totalFechas<<"): ";
	cin>>fecha;

for(i=0;i<cantEquipos;i++){
v[i].DG=0;
v[i].GF=0;
v[i].GC=0;
v[i].PE=0;
v[i].PG=0;
v[i].PP=0;
v[i].PJ=0;
v[i].puntos=0;
v[i].posicion=NULO;
}

int local=0, visitante=1,local1,visitante1;
while(!ListaEstaVacia(partidos)){
	
		if(partidos->fecha <= fecha){
			EquipoEstaRegistrado(v, partidos, cantEquipos,posLocal,posVisitante);
			
			if (posLocal == cantEquipos) { // equipo nuevo	
			v[local].PJ=v[local].PJ+1;
			v[local].GF=v[local].GF+partidos->golesLocal;
			v[local].GC=v[local].GC+partidos->golesVisitante;
			v[local].posicion=partidos->local;
			local1=local;
			local=local+2;
			}
			else{//equipo ya guardado
			v[posLocal].PJ=v[posLocal].PJ+1;
			v[posLocal].GF=v[posLocal].GF+partidos->golesLocal;
			v[posLocal].GC=v[posLocal].GC+partidos->golesVisitante;
			v[posLocal].posicion=partidos->local;
			local1=posLocal;		
			}
			
			if (posVisitante == cantEquipos) { // equipo nuevo	
			v[visitante].PJ=v[visitante].PJ+1;
			v[visitante].GF=v[visitante].GF+partidos->golesVisitante;
			v[visitante].GC=v[visitante].GC+partidos->golesLocal;
			v[visitante].posicion=partidos->visitante;
			visitante1=visitante;
			visitante= visitante+2;
			}
			else{//equipo ya guardado
			v[posVisitante].PJ=v[posVisitante].PJ+1;
			v[posVisitante].GF=v[posVisitante].GF+partidos->golesVisitante;
			v[posVisitante].GC=v[posVisitante].GC+partidos->golesLocal;
			v[posVisitante].posicion=partidos->visitante;
			visitante1=posVisitante;	
			}
			
			if(v[local1].GF>v[visitante1].GF){
				v[local1].PG=v[local1].PG+1;
				v[visitante1].PP=v[visitante1].PP+1;
				v[local1].puntos=v[local1].puntos+3;
						
			}
			else{
			
			if(v[local1].GF<v[visitante1].GF){
				v[local1].PP=v[local1].PP+1;
				v[visitante1].PG=v[visitante1].PG+1;
				v[visitante1].puntos=v[visitante1].puntos+3;
			}
			else{
			
				v[local1].PE==v[local1].PE+1;
				v[visitante1].PE=v[visitante1].PE+1;
				v[local1].puntos=v[local1].puntos+1;
				v[visitante1].puntos=v[visitante1].puntos+1;
			}	
		}
			SacarDeLista(partidos);
		}
		else{
			SacarDeLista(partidos);
		}
}

for(i=0;i<cantEquipos;i++) {// Si DG es negativo se lo hace positivo
	v[i].DG=v[i].GF-v[i].GC;
	if(v[i].DG<0){
	v[i].DG=v[i].DG*(-1);
	}
}


Posiciones temp;
for(i=0;i<cantEquipos;i++) {
                for(int j=0;j<100-1;j++) {
				
                    if(v[j].puntos<v[j+1].puntos){
                        temp=v[j]; 
                        v[j]=v[j+1]; 
                        v[j+1]=temp;
						} 
}
}

		
cout<<"Equipo			Puntos PJ PG PE	PP GF  GC DG "<<endl;
for(i=0;i<cantEquipos;i++){
	if(v[i].PJ>0){
	cout<<equipos[v[i].posicion].id<<" "<<equipos[v[i].posicion].nombre<<"		"<<v[i].puntos<<" 	"<<v[i].PJ<<" "<<v[i].PG<<"  "<<v[i].PE<<"	"<<v[i].PP<<"  "<<v[i].GF<<"   "<<v[i].GC<<" "<<v[i].DG<<endl;		
	}
}

}






	
	


		


