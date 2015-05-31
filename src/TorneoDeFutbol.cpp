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
	// muestra el menú y devuelve la opción seleccionada
	//
	// Manuel

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

bool YaEstaEquipo(char id[4]){
	// devuelve TRUE si el equipo ya se encuentra en el archivo, FALSE si no se encuentra
	// TODO: errores en determinar por ID, como si leyera y escribiera en distintos formatos
	// ASIGNED TO: Manuel
	Equipo equipo;
	bool devuelvo=false;
	FILE* archivo = fopen(FILENAME, "rb");
	while(!feof(archivo)){
		fread(&equipo,sizeof(equipo),1,archivo);
		cout << "comparando: |" << id << "| con |" << equipo.id << "|" << endl;
		if ( equipo.id == id ){
			cout << "ENTRE!!" << endl;
			devuelvo=true;
		}
	}
	fclose(archivo);
	return devuelvo;
}

void ModificarEquipo(char id[4]){
	// este metodo busca el equipo por el id que recibe, y permite modificarlo
	// TODO: hay que desarrollarlo
	// ASIGNED TO:
}

bool GuardarEquipo(Equipo equipo){
	// este metodo devuelve TRUE si pudo guardar el equipo, FALSE si no pudo
	// TODO:
	// ASIGNED TO: Manuel

	FILE* archivo = fopen(FILENAME, "a");

	fwrite(&equipo, sizeof(equipo), 1, archivo);
	fclose(archivo);
	return true;
}



void VerEquipos(){
	// muestra los equipos del archivo
	//
	// Manuel
	Equipo equipo;
	FILE* archivo = fopen(FILENAME, "rb");
	cout << "Lista de equipos:" << endl;
	fread(&equipo,sizeof(equipo),1,archivo);
	while(!feof(archivo)){
		cout << equipo.id << " " << equipo.nombre << " (" << equipo.potenciaAtaque << " - " << equipo.potenciaDefensa << ")" << endl;
		fread(&equipo,sizeof(equipo),1,archivo);
	}
	fclose(archivo);
	return;
}




void AgregarEquipo(){
	// función para agregar equipo. Si encuentra que el equipo ya existe, pregunta para modificarlo.

	Equipo equipo;
	char modificar[1];

	cout << "Ingrese el identificador (3 caracteres): ";

	cin >> equipo.id;

	if(YaEstaEquipo(equipo.id)){
		cout << " ## Este equipo ya se encuentra cargado, desea modificarlo? (S/N):";
		cin >> modificar;
		if(modificar=="y"|| modificar=="Y"){
			ModificarEquipo(equipo.id);
		}
	} else {
		cout << "Ingrese el nombre (31 caracteres): ";
/* por alguna razón, esta línea de abajo sólo toma la primer palabra, hasta el espacio. */
		cin >> equipo.nombre;

		cout << "Ingrese potencia de ataque (0-100): ";
		cin >> equipo.potenciaAtaque;
		cout << "Ingrese potencia de defensa (0-100): ";
		cin >> equipo.potenciaDefensa;
		if(GuardarEquipo(equipo)){
			cout << "        equipo guardado satisfactoriamente" << endl;
		} else {
			cout << "        ERROR - el equipo no se pudo guardar." << endl;
		}
	}
	return;
}


int main() {
	// funcion Main.
	// Manuel

	int opcion=1;
	while(opcion!=0){
		opcion=MostrarMenu();
		switch (opcion){
			case 1:
				AgregarEquipo();
				break;
			case 2:
				cout << "Esto hara� que entres en el menu de eliminar equipo Y LO VA A HACER IAN" << endl;
				break;
			case 3:
				VerEquipos();
				break;
			case 0:
				cout << "SALIR" << endl;;
				break;
			default:
				cout << opcion << " no es una opcion valida, intente nuevamente" << endl;
		}
	}
	cout << "Gracias por usar nuestro programa!" << endl;

	return 0;
}
