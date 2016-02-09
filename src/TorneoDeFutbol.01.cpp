//============================================================================
// Name        : TorneoDeFutbol.cpp
// Author      : Manuel Fernando Aller, Ian Alexis Bassi, Lucas Manuel Blanco y Mateo Tozzini.
// Version     :
// Copyright   : (c) grupo 114
// Description : Simulacion de torneo de Futbol
//============================================================================

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include <time.h>

struct Equipo {
	char id[4];
	char nombre[32];
	int potenciaAtaque;
	int potenciaDefensa;
};

namespace {

const char* FILENAME = "EQUIPOS.BIN";
const int MAX_EQUIPOS = 100;

}

using namespace std;

void MuestroEncabezado() {
	cout << " __________________________________________________________________________" << endl;
	cout << "|                                                                          |\\" << endl;
	cout << "|                         Torneo master race locura (TM)                   ||" << endl;
	cout << "|                                                                          ||" << endl;
}

void MuestroPie() {
	cout << "|                                                                          ||" << endl;
	cout << "|                                                            grupo114      ||" << endl;
	cout << "|__________________________________________________________________________||" << endl;
	cout << " \\_________________________________________________________________________\\|" << endl;
}

void VerEquipos(Equipo equipos[],int cantEquipos){
	// muestra los equipos del array
	//
	// Manuel
	int i,j,espacios,aux;
	for(i=0;i<cantEquipos;i++){
		cout << "| " << equipos[i].id << " " << equipos[i].nombre << " (" << equipos[i].potenciaAtaque << " - " << equipos[i].potenciaDefensa << ")";
		if(equipos[i].potenciaAtaque<10){
			aux=1;
		} else {
			aux=2;
		}
		if(equipos[i].potenciaDefensa<10){
			aux=aux+1;
		} else {
			aux=aux+2;
		}
		espacios=66-(strlen(equipos[i].id)+strlen(equipos[i].nombre)+aux);
		for(j=0;j<espacios;j++){
			cout << " ";
		}
		cout << "||" << endl;
	}
	return;
}

int PosicionEquipo(Equipo equipos[], int cantEquipos, char id[4]){
	int posEquipo=0,i;
	bool entre=false;
	for(i=0;i<cantEquipos;i++){
		if(strcmp(equipos[i].id, id)==0){
			posEquipo=i;
			entre=true;
		}
	}
	if(!entre){
		posEquipo=cantEquipos;
	}
	return posEquipo;
}

void AgregarEquipo(Equipo equipos[],int &cantEquipos){
	Equipo nuevoEquipo;
	string nombre; // variable auxiliar para leer una línea completa
	char modificar[2];
	cout << "Ingrese el identificador (3 caracteres): ";
	cin >> nuevoEquipo.id;
	int posEquipo = PosicionEquipo(equipos, cantEquipos, nuevoEquipo.id);
	if (posEquipo == cantEquipos) { // equipo nuevo
	    // agregar equipo nuevo
		cout << "Ingrese el nombre (31 caracteres): ";

		getline(cin, nombre); // lee una línea vacía que quedó pendiente del último ingreso.
		getline(cin, nombre); // lee una línea desde el teclado
		strncpy(nuevoEquipo.nombre, nombre.c_str(), sizeof(nuevoEquipo.nombre)); // copia los caracteres al registro
		nuevoEquipo.nombre[sizeof(nuevoEquipo.nombre) - 1] = '\0'; // fuerza a que tenga a lo sumo 31 caracteres

		cout << "Ingrese potencia de ataque (0-100): ";
		cin >> nuevoEquipo.potenciaAtaque;
		cout << "Ingrese potencia de defensa (0-100): ";
		cin >> nuevoEquipo.potenciaDefensa;
		equipos[cantEquipos]=nuevoEquipo;
		cantEquipos++;
	}
	else { // equipo existente
	    // preguntar si quiere modificar y modificarlo si dice que sí
		cout << "El equipo ya existe, desea modificarlo? (S/N)" << endl;
		cin >> modificar;
		if(strcmp(modificar,"s")==0||strcmp(modificar,"S")==0){
			cout << "Nombre actual: " << equipos[posEquipo].nombre << endl;
			cout << "Ingrese nuevo nombre (31 caracteres): ";
			getline(cin, nombre); // lee una línea vacía que quedó pendiente del último ingreso.
			getline(cin, nombre); // lee una línea desde el teclado
			strncpy(nuevoEquipo.nombre, nombre.c_str(), sizeof(nuevoEquipo.nombre)); // copia los caracteres al registro
			nuevoEquipo.nombre[sizeof(nuevoEquipo.nombre) - 1] = '\0'; // fuerza a que tenga a lo sumo 31 caracteres

			cout << "Potencia de ataque actual: " << equipos[posEquipo].potenciaAtaque << endl;
			cout << "Ingrese nueva potencia de ataque (0-100): ";
			cin >> nuevoEquipo.potenciaAtaque;
			cout << "Potencia de defensa actual: " << equipos[posEquipo].potenciaDefensa << endl;
			cout << "Ingrese nueva potencia de defensa (0-100): ";
			cin >> nuevoEquipo.potenciaDefensa;
			equipos[posEquipo]=nuevoEquipo;
		}
	}
	return;
}

void CargarEquipos(Equipo equipos[], int &cantEquipos){
	/* abro el archivo al principio, cargo los equipos en un array y cierro el archivo. Trabajamos con los datos en memoria. */

	FILE* archivo = fopen(FILENAME, "rb");
	fread(&equipos[cantEquipos],sizeof(Equipo),1,archivo);
	while(!feof(archivo)){
		cantEquipos++;
		fread(&equipos[cantEquipos],sizeof(Equipo),1,archivo);
	}
	fclose(archivo);

	return;
}

void BorrarEquipo(Equipo equipos[], int &cantEquipos, char idEquipoBorrar[4]){
	int i;
	int nuevocantEquipos=0;
	Equipo nuevoEquipos[100];
	for(i=0;i<cantEquipos;i++){
		if(strcmp(equipos[i].id,idEquipoBorrar)!=0){
			nuevoEquipos[nuevocantEquipos]=equipos[i];
			nuevocantEquipos++;
		}
	}
	for(i=0;i<cantEquipos;i++){
		equipos[i]=nuevoEquipos[i];
	}
//	equipos=nuevoEquipos;
	cantEquipos=nuevocantEquipos;
	return;
}

void EliminarEquipo(Equipo equipos[], int &cantEquipos){
	char idEquipoBorrar[4];
	char resp[2];
	MuestroEncabezado();
	cout << "|              Menu para eliminar equipos                                  ||" << endl;
	cout << "|                                                                          ||" << endl;
	VerEquipos(equipos,cantEquipos);
	MuestroPie();
	cout << endl;
	cout << " Ingrese el identificador del equipo que desea eliminar: ";
	cin >> idEquipoBorrar;
	cout << " Esta seguro que desea eliminar al equipo "<<equipos[PosicionEquipo(equipos,cantEquipos,idEquipoBorrar)].nombre<<" de la lista? (S/N)" << endl;
		cin >> resp;
		if(strcmp(resp,"s")==0||strcmp(resp,"S")==0){
	BorrarEquipo(equipos, cantEquipos, idEquipoBorrar);
	cout<<" Equipo eliminado"<<endl;
		}
	else
	return;
}

void GuardarEquipos(Equipo equipos[], int cantEquipos){
	int i;

	FILE* archivo = fopen(FILENAME, "wb");
	/* ahora guardo equipos en el archivo: */

	for(i=0;i<cantEquipos;i++){
		fwrite(&equipos[i], sizeof(Equipo), 1, archivo);
	}
	fclose(archivo);
	return;
}

void MenuEdicion(Equipo equipos[MAX_EQUIPOS], int &cantEquipos){
	// muestra el menu y devuelve la opcion seleccionada
	// Manuel

	int opcion=9;
	while(opcion!=0){
		MuestroEncabezado();
		cout << "|              Menu Edicion                                                ||" << endl;
		cout << "|              1. Agregar Equipo                                           ||" << endl;
		cout << "|              2. Eliminar Equipo                                          ||" << endl;
		cout << "|              3. Ver Equipos                                              ||" << endl;
		cout << "|              0. Volver                                                   ||" << endl;
		MuestroPie();
		cout << endl;
		cout << " Ingrese su opcion (y presione 'enter'): ";
		cin >> opcion;
		switch (opcion){
			case 1:
				AgregarEquipo(equipos,cantEquipos);
				break;
			case 2:
				//cout << "Esto hara que entres en el menu de eliminar equipo Y LO VA A HACER IAN" << endl;
				EliminarEquipo(equipos,cantEquipos);
				break;
			case 3:
				MuestroEncabezado();
				cout << "|    Lista de equipos:                                                     ||" << endl;
				VerEquipos(equipos,cantEquipos);
				MuestroPie();
				break;
			case 0:
				cout << "SALIR" << endl;;
				break;
			default:
				cout << opcion << " no es una opción valida, intente nuevamente" << endl;
		}
	}
	return;
}

int TorneoDeFutbol01() {
	// funcion Main.
	// Manuel
	Equipo equipos[MAX_EQUIPOS];
	int cantEquipos=0;
	CargarEquipos(equipos, cantEquipos);
	MenuEdicion(equipos, cantEquipos);
	GuardarEquipos(equipos, cantEquipos);

	return 0;
}
