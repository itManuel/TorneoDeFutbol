//============================================================================
// Name        : TorneoDeFutbol.cpp
// Author      : Manuel Fernando Aller
// Version     :
// Copyright   : (c) grupo 114
// Description : Simulación de torneo de Fútbol
//============================================================================

#include <iostream>
using namespace std;

struct Equipo {
	char id[3];
	char nombre[31];
	int potenciaAtaque;
	int potenciaDefensa;
};

int MostrarMenu(){
	int opcion;
	cout << "____________________________________________________________________________" << endl;
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
	cout << " Ingrese su opción (y presione 'enter'): ";
	cin >> opcion;
	return opcion;
}

bool YaEstaEquipo(char id[3]){
	// devuelve TRUE si el equipo ya se encuentra en el archivo, FALSE si no se encuentra
	// TODO: hay que desarrollarlo
	// ASIGNED TO:
	return false;
}

void ModificarEquipo(char id[3]){
	// este metodo busca el equipo por el id que recibe, y permite modificarlo
	// TODO: hay que desarrollarlo
	// ASIGNED TO:
}

bool GuardarEquipo(Equipo equipo){
	// este metodo devuelve TRUE si pudo guardar el equipo, FALSE si no pudo
	// TODO: hay que hacerlo
	// ASIGNED TO:
	return false;
}

void AgregarEquipo(){
	Equipo equipo;
	char modificar[1];
	cout << "____________________________________________________________________________" << endl;
	cout << "|                                                                          |\\" << endl;
	cout << "|                         Nunca Viste Un Torneo Así (TM)                   ||" << endl;
	cout << "|                                                                          ||" << endl;
	cout << "|   Ingrese el identificador (3 caracteres):                               ||" << endl;
	cin >> equipo.id;
	cin >> modificar;
	if(YaEstaEquipo(equipo.id)){
		cout << "| Este equipo ya se encuentra cargado, desea modificarlo? (S/N)            ||" << endl;
		cin >> modificar;
		if(modificar=="y"|| modificar=="Y"){
			ModificarEquipo(equipo.id);
		}
	} else {
		cout << "|   Ingrese el nombre (31 caracteres):                                     ||" << endl;
		cin >> equipo.nombre;
		cout << "|   Ingrese potencia de ataque:                                            ||" << endl;
		cin >> equipo.potenciaAtaque;
		cout << "|   Ingrese potencia de defensa:                                           ||" << endl;
		cin >> equipo.potenciaDefensa;
		cout << "|                                                                          ||" << endl;
		cout << "|                          procesando...                                   ||" << endl;
		cout << "|                                                                          ||" << endl;
		if(GuardarEquipo(equipo)){
			cout << "|        equipo guardado satisfactoriamente                                ||" << endl;

		} else {
			cout << "|        ERROR                                                             ||" << endl;

		}
		cout << "|__________________________________________________________________________||" << endl;
		cout << " \\_________________________________________________________________________\\|" << endl;
	}
}


int main() {

	int opcion=1;
	while(opcion!=0){
		opcion=MostrarMenu();
		switch (opcion){
			case 1:
				AgregarEquipo();
				break;
			case 2:
				cout << "Esto hará que entres en el menú de eliminar equipo" << endl;
				break;
			case 3:
				cout << "Esto hará que entres en el menú de ver equipos" << endl;
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
