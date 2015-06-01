//============================================================================
// Name        : TorneoDeFutbol.cpp
// Author      : Manuel Fernando Aller, Ian Alexis Bassi, Lucas Manuel Blanco y Mateo Tozzini.
// Version     :
// Copyright   : (c) grupo 114
// Description : Simulacion de torneo de Futbol
//============================================================================


#include <iostream>
#include <fstream>

struct Equipo {
	char id[4];
	char nombre[32];
	int potenciaAtaque;
	int potenciaDefensa;
};

namespace {

const char* FILENAME = "EQUIPOS.BIN";

}

using namespace std;


int MostrarMenu(){
		int opcion;
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
	return opcion;
}

void ModificarEquipo(char id[4]){
	// este metodo busca el equipo por el id que recibe, y permite modificarlo
	// TODO: hay que desarrollarlo
	// ASIGNED TO:
}

void VerEquipos(int lineas,Equipo equipo[]){
	// muestra los equipos del archivo
	//
	// Manuel
	int i;
	cout << "Lista de equipos:" << endl;
	for(i=0;i<lineas;i++){
		cout << equipo[i].id << " " << equipo[i].nombre << " (" << equipo[i].potenciaAtaque << " - " << equipo[i].potenciaDefensa << ")" << endl;
	}
	return;
}

void AgregarEquipo(int &lineas, Equipo equipo[]){
	int i;
	bool agregar=true;
	Equipo nuevoEquipo;
	cout << "Ingrese el identificador (3 caracteres): ";
	cin >> nuevoEquipo.id;
	for(i=0;i<lineas;i++){
		if(equipo[i].id==nuevoEquipo.id){
			agregar=false;
		}
	}
	if(agregar){
		cout << "Ingrese el nombre (31 caracteres): ";
		cin >> nuevoEquipo.nombre;
		cout << "Ingrese potencia de ataque (0-100): ";
		cin >> nuevoEquipo.potenciaAtaque;
		cout << "Ingrese potencia de defensa (0-100): ";
		cin >> nuevoEquipo.potenciaDefensa;
		lineas++;
		equipo[lineas]=nuevoEquipo;
	} else {
		ModificarEquipo(nuevoEquipo.id);
	}
	return;
}

int main() {
	// funcion Main.
	// Manuel

	/* abro el archivo al principio, cargo los equipos en un array y cierro el archivo. Trabajamos con los datos en memoria. */
	Equipo equipo[100];
	int i;
	int lineas=0;

	FILE* archivo = fopen(FILENAME, "rb");
	fread(&equipo[lineas],sizeof(equipo),1,archivo);
	lineas++;
	while(!feof(archivo)){
		fread(&equipo[lineas],sizeof(equipo),1,archivo);
		lineas++;
	}
	fclose(archivo);
/* muestro lo que cargue del archivo */
	for(i=0;i<lineas;i++){
		cout << equipo[i].id << " " << equipo[i].nombre << " (" << equipo[i].potenciaAtaque << " - " << equipo[i].potenciaDefensa << ")" << endl;
	}


	int opcion=1;
	while(opcion!=0){
		opcion=MostrarMenu();
		switch (opcion){
			case 1:
				AgregarEquipo(lineas,equipo);
				break;
			case 2:
				cout << "Esto hara que entres en el menu de eliminar equipo Y LO VA A HACER IAN" << endl;
				break;
			case 3:
				VerEquipos(lineas,equipo);
				break;
			case 0:
				cout << "SALIR" << endl;;
				break;
			default:
				cout << opcion << " no es una opción valida, intente nuevamente" << endl;
		}
	}

	/* ahora guardo todo en el archivo: */
	archivo = fopen(FILENAME,"wb");
	for(i=0;i<lineas;i++){
		fwrite(&equipo[i], sizeof(equipo), 1, archivo);
	}
	fclose(archivo);

	cout << "Gracias por usar nuestro programa!" << endl;

	return 0;
}
