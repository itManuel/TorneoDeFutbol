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
	int id;
	char nombre[31];
	int potenciaAtaque;
	int potenciaDefensa;
};

int main() {

	Equipo equipo;
	int opcion=1;
	while(opcion!=0){
		cout << "============================================================================" << endl;
		cout << "#                         Nunca Viste Un Torneo Así                        #" << endl;
		cout << "#                                                                          #" << endl;
		cout << "#              Menu                                                        #" << endl;
		cout << "#              1. Agregar Equipo                                           #" << endl;
		cout << "#              2. Eliminar Equipo                                          #" << endl;
		cout << "#              3. Ver Equipos                                              #" << endl;
		cout << "#              0. Salir                                                    #" << endl;
		cout << "#                                                                          #" << endl;
		cout << "#                                                            grupo114      #" << endl;
		cout << "============================================================================" << endl;
		cout << endl;
		cout << " Ingrese su opción (y presione 'enter'): ";
		cin >> opcion;
		switch (opcion){
			case 1:
				cout << "Esto hará que entres en el menú de agregar equipo" << endl;
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
