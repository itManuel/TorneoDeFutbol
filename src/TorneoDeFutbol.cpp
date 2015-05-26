//============================================================================
// Name        : TorneoDeFutbol.cpp
// Author      : Manuel Fernando Aller
// Version     :
// Copyright   : (c) grupo 114
// Description : Simulación de torneo de Fútbol
//============================================================================


#include <iostream>
#include <fstream>

struct Equipo {
	char id[3];
	char nombre[31];
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
	cout << "|                         Nunca Viste Un Torneo Así (TM)                   ||" << endl;
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

bool YaEstaEquipo(char id[3]){
	// devuelve TRUE si el equipo ya se encuentra en el archivo, FALSE si no se encuentra
	// TODO: errores en determinar por ID, como si leyera y escribiera en distintos formatos
	// ASIGNED TO: Manuel
	Equipo equipo;
	bool devuelvo=false;
	FILE* archivo = fopen(FILENAME, "rb");
	while(!feof(archivo)){

		fread(&equipo,sizeof(equipo),1,archivo);
		if(equipo.id==id){
			devuelvo=true;
		}

	}
	fclose(archivo);
	return devuelvo;
}

void ModificarEquipo(char id[3]){
	// este metodo busca el equipo por el id que recibe, y permite modificarlo
	// TODO: hay que desarrollarlo
	// ASIGNED TO:
}

bool GuardarEquipo(Equipo equipo){
	// este metodo devuelve TRUE si pudo guardar el equipo, FALSE si no pudo
	// TODO: hay que hacerlo
	// ASIGNED TO: Manuel


	FILE* archivo = fopen(FILENAME, "wb");

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
	while(!feof(archivo)){

		fread(&equipo,sizeof(equipo),1,archivo);
		if(equipo.id!=""){
			cout << equipo.id << " " << equipo.nombre << " (" << equipo.potenciaAtaque << " - " << equipo.potenciaDefensa << ")" << endl;
		}

	}
	fclose(archivo);
	return;
}




void AgregarEquipo(){
	// función para agregar equipo. Si encuentra que el equipo ya existe, pregunta para modificarlo.
	//
	// Manuel

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
	// función Main.
	// Manuel

	int opcion=1;
	while(opcion!=0){
		opcion=MostrarMenu();
		switch (opcion){
			case 1:
				AgregarEquipo();
				break;
			case 2:
				cout << "Esto hará que entres en el menú de eliminar equipo Y LO VA A HACER IAN" << endl;
				break;
			case 3:
				VerEquipos();
				break;
			case 0:
				cout << "SALIR" << endl;;
				break;
			default:
				cout << opcion << " no es una opción válida, intente nuevamente" << endl;
		}
	}
	cout << "Gracias por usar nuestro programa!" << endl;

	return 0;
}
