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



void ModificarEquipo(char id[4]){
	// este metodo busca el equipo por el id que recibe, y permite modificarlo
	// TODO: hay que desarrollarlo
	// ASIGNED TO:
	return;
}

void VerEquipos(Equipo equipos[],int lineas){
	// muestra los equipos del array
	//
	// Manuel
	int i;
	cout << "Lista de equipos:" << endl;
	for(i=0;i<lineas;i++){
		cout << "i: " << i << " -> " << equipos[i].id << " " << equipos[i].nombre << " (" << equipos[i].potenciaAtaque << " - " << equipos[i].potenciaDefensa << ")" << endl;
	}
	return;
}

void AgregarEquipo(Equipo equipos[],int &lineas){
	Equipo nuevoEquipo;
	string nombre; // variable auxiliar para leer una línea completa

	cout << "Ingrese el identificador (3 caracteres): ";
	cin >> nuevoEquipo.id;
	cout << "Ingrese el nombre (31 caracteres): ";

	getline(cin, nombre); // lee una línea vacía que quedó pendiente del último ingreso.
	getline(cin, nombre); // lee una línea desde el teclado
	strncpy(nuevoEquipo.nombre, nombre.c_str(), sizeof(nuevoEquipo.nombre)); // copia los caracteres al registro
	nuevoEquipo.nombre[sizeof(nuevoEquipo.nombre) - 1] = '\0'; // fuerza a que tenga a lo sumo 31 caracteres

	cout << "Ingrese potencia de ataque (0-100): ";
	cin >> nuevoEquipo.potenciaAtaque;
	cout << "Ingrese potencia de defensa (0-100): ";
	cin >> nuevoEquipo.potenciaDefensa;
	equipos[lineas]=nuevoEquipo;
	lineas++;
	return;
}

void CargarEquipos(Equipo equipos[], int &lineas){
	/* abro el archivo al principio, cargo los equipos en un array y cierro el archivo. Trabajamos con los datos en memoria. */
	int i;

	FILE* archivo = fopen(FILENAME, "rb");
	fread(&equipos[lineas],sizeof(Equipo),1,archivo);
	while(!feof(archivo)){
		lineas++;
		fread(&equipos[lineas],sizeof(Equipo),1,archivo);
	}
	fclose(archivo);

	return;
}

void GuardarEquipos(Equipo equipos[], int lineas){
	int i;

	FILE* archivo = fopen(FILENAME, "wb");
	/* ahora guardo equipos en el archivo: */

	for(i=0;i<lineas;i++){
		fwrite(&equipos[i], sizeof(Equipo), 1, archivo);
	}
	fclose(archivo);
	return;
}


void MenuPrincipal(Equipo equipos[MAX_EQUIPOS], int &lineas){
	// muestra el menu y devuelve la opcion seleccionada
	// Manuel

	int opcion=9;
	while(opcion!=0){
		cout << " __________________________________________________________________________" << endl;
		cout << "|                                                                          |\\" << endl;
		cout << "|                         Torneo master race locura (TM)                   ||" << endl;
		cout << "|                                                                          ||" << endl;
		cout << "|              Menu                                                        ||" << endl;
		cout << "|              1. Agregar Equipo                                           ||" << endl;
		cout << "|              2. Eliminar Equipo                                          ||" << endl;
		cout << "|              3. Ver Equipos                                              ||" << endl;
		cout << "|              0. Salir                                                    ||" << endl;
		cout << "|                                                                          ||" << endl;
		cout << "|                                                            grupo114      ||" << endl;
		cout << "|__________________________________________________________________________||" << endl;
		cout << " \\_________________________________________________________________________\\|" << endl;
		cout << endl;
		cout << " Ingrese su opcion (y presione 'enter'): ";
		cin >> opcion;
		switch (opcion){
			case 1:
				AgregarEquipo(equipos,lineas);
				break;
			case 2:
				cout << "Esto hara que entres en el menu de eliminar equipo Y LO VA A HACER IAN" << endl;
				break;
			case 3:
				VerEquipos(equipos,lineas);
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

int main() {
	// funcion Main.
	// Manuel
	Equipo equipos[MAX_EQUIPOS];
	int lineas=0;
	CargarEquipos(equipos, lineas);
	MenuPrincipal(equipos, lineas);
	GuardarEquipos(equipos, lineas);

	cout << "Gracias por usar nuestro programa!" << endl;

	return 0;
}
