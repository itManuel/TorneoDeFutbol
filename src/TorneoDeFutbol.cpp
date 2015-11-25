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

void CuentoEspacios(char impreso, char formato){
	int i;
	for(i=impreso;i<formato;i++){
		cout << " ";
	}
}

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

void VerEquipos(Equipo equipos[],int lineas){
	// muestra los equipos del array
	//
	// Manuel
	int i,j,espacios,aux;
	for(i=0;i<lineas;i++){
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
//		cout << "i: " << i << " -> " << equipos[i].id << " " << equipos[i].nombre << " (" << equipos[i].potenciaAtaque << " - " << equipos[i].potenciaDefensa << ")" << endl;
	}
	return;
}

int PosicionEquipo(Equipo equipos[], int lineas, char id[4]){
	int posEquipo=0,i;
	bool entre=false;
	for(i=0;i<lineas;i++){
		if(strcmp(equipos[i].id, id)==0){
			posEquipo=i;
			entre=true;
		}
	}
	if(!entre){
		posEquipo=lineas;
	}
	return posEquipo;
}

void AgregarEquipo(Equipo equipos[],int &lineas){
	Equipo nuevoEquipo;
	string nombre; // variable auxiliar para leer una línea completa
	char modificar[2];
	cout << "Ingrese el identificador (3 caracteres): ";
	cin >> nuevoEquipo.id;
	int posEquipo = PosicionEquipo(equipos, lineas, nuevoEquipo.id);
	if (posEquipo == lineas) { // equipo nuevo
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
		equipos[lineas]=nuevoEquipo;
		lineas++;
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

void CargarEquipos(Equipo equipos[], int &lineas){
	/* abro el archivo al principio, cargo los equipos en un array y cierro el archivo. Trabajamos con los datos en memoria. */

	FILE* archivo = fopen(FILENAME, "rb");
	fread(&equipos[lineas],sizeof(Equipo),1,archivo);
	while(!feof(archivo)){
		lineas++;
		fread(&equipos[lineas],sizeof(Equipo),1,archivo);
	}
	fclose(archivo);

	return;
}

void BorrarEquipo(Equipo equipos[], int &lineas, char idEquipoBorrar[4]){
	int i;
	int nuevoLineas=0;
	Equipo nuevoEquipos[100];
	for(i=0;i<lineas;i++){
		if(strcmp(equipos[i].id,idEquipoBorrar)!=0){
			cout << "entre porque " << equipos[i].id << " es distinto que " << idEquipoBorrar << endl;
			nuevoEquipos[nuevoLineas]=equipos[i];
			nuevoLineas++;
		}
	}
	for(i=0;i<lineas;i++){
		equipos[i]=nuevoEquipos[i];
	}
//	equipos=nuevoEquipos;
	lineas=nuevoLineas;
	return;
}

void EliminarEquipo(Equipo equipos[], int &lineas){
	char idEquipoBorrar[4];
	MuestroEncabezado();
	cout << "|              Menu para eliminar equipos                                  ||" << endl;
	cout << "|                                                                          ||" << endl;
	VerEquipos(equipos,lineas);
	MuestroPie();
	cout << endl;
	cout << " Ingrese el identificador del equipo que desea eliminar: ";
	cin >> idEquipoBorrar;
	BorrarEquipo(equipos, lineas, idEquipoBorrar);

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

void Simular(){
	
	cout<<"Este procedimiento simulara los partidos y mostrara otro menu"<<endl;
	
}

void MenuSecundario(Equipo equipos[MAX_EQUIPOS], int &lineas){
	// muestra el menu secundario y devuelve la opcion seleccionada
	// Manuel

	int opcion=9;
	while(opcion!=0){
		MuestroEncabezado();
		cout << "|              Menu 2                                                      ||" << endl;
		cout << "|              1. Agregar Equipo                                           ||" << endl;
		cout << "|              2. Eliminar Equipo                                          ||" << endl;
		cout << "|              3. Ver Equipos                                              ||" << endl;
		cout << "|              0. Ir al Menu 1                                             ||" << endl;
		MuestroPie();
		cout << endl;
		cout << " Ingrese su opcion (y presione 'enter'): ";
		cin >> opcion;
		switch (opcion){
			case 1:
				AgregarEquipo(equipos,lineas);
				break;
			case 2:
				//cout << "Esto hara que entres en el menu de eliminar equipo Y LO VA A HACER IAN" << endl;
				EliminarEquipo(equipos,lineas);
				break;
			case 3:
				MuestroEncabezado();
				cout << "|    Lista de equipos:                                                     ||" << endl;
				VerEquipos(equipos,lineas);
				MuestroPie();
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

void MenuPrimario(Equipo equipos[MAX_EQUIPOS], int &lineas){
	// muestra el menu primario y devuelve la opcion seleccionada
	// Manuel

	int opcion=9;
	while(opcion!=0){
		MuestroEncabezado();
		cout << "|              Menu 1                                                      ||" << endl;
		cout << "|              1. Editar Equipo                                            ||" << endl;
		cout << "|              2. Simular                                                  ||" << endl;
		cout << "|              0. Salir                                                    ||" << endl;
		cout << "|                                                                          ||" << endl;
		MuestroPie();
		cout << endl;
		cout << " Ingrese su opcion (y presione 'enter'): ";
		cin >> opcion;
		switch (opcion){
			case 1:
				MenuSecundario(equipos,lineas);
				break;
			case 2:
				Simular();
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
	


int main() {
	// funcion Main.
	// Manuel
	Equipo equipos[MAX_EQUIPOS];
	int lineas=0;
	CargarEquipos(equipos, lineas);
	MenuPrimario(equipos, lineas);
	GuardarEquipos(equipos, lineas);

	cout << "Gracias por usar nuestro programa!" << endl;

	return 0;
}
