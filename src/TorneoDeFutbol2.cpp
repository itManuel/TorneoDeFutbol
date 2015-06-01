//============================================================================
// Name        : TorneoDeFutbol.cpp
// Author      : Manuel Fernando Aller, Blanco Lucas, Tozzini Mateo, Bassi Ian.
// Version     :
// Copyright   : (c) grupo 114
// Description : Simulacion de torneo de Futbol
//============================================================================


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <conio.h>


struct Equipo {
	char id[4];
	char nombre[32];
	int potenciaAtaque;
	int potenciaDefensa;
}equipo;

namespace {

const char* FILENAME = "EQUIPOS.BIN";
const char* FILEtemp = "EQUIPOStemp.BIN";
}

using namespace std;


int MostrarMenu(){
	// muestra el menu y devuelve la opcion seleccionada
	
	int opcion;
	cout << " __________________________________________________________________________" << endl;
	cout << "|                                                                          |\\" << endl;
	cout << "|                         Nunca Viste Un Torneo Asi (TM)                   ||" << endl;
	cout << "|                                                                          ||" << endl;
	cout << "|              Menu                                                        ||" << endl;
	cout << "|              1. Agregar Equipo\Editar Equipos                            ||" << endl;
	cout << "|              2. Eliminar Equipo                                          ||" << endl;
	cout << "|              3. Ver Equipos                                              ||" << endl;
	cout << "|              0. Salir                                                    ||" << endl;
	cout << "|                                                                          ||" << endl;
	cout << "|                                                            Grupo114      ||" << endl;
	cout << "|__________________________________________________________________________||" << endl;
	cout << " \\_________________________________________________________________________\\|" << endl;
	cout << endl;
	cout << " Ingrese su opcion (y presione 'enter'): ";
	cin >> opcion;
	return opcion;
}

bool YaEstaEquipo(char id[4]){
	// devuelve TRUE si el equipo ya se encuentra en el archivo, FALSE si no se encuentra

	Equipo equipo;
	bool devuelvo=false;

	FILE* archivo = fopen(FILENAME, "rb");
	if(archivo!=NULL){ //Si el archivo no existe la funcion fopen asigna NULL a archivo
		while(!feof(archivo)){
			fread(&equipo,sizeof(equipo),1,archivo);
		
			if ( strcmp(equipo.id,id)==0){ //strcmp compara ambos parametros y si son iguales devuelve un 0
			devuelvo=true;
			}
		}
}
	fclose(archivo);
	return devuelvo;
}

void ModificarEquipo(char id[4]){
	// este metodo busca el equipo por el id que recibe, y permite modificarlo

	
	Equipo equipo;

	FILE* archivo = fopen(FILENAME, "r+");
	fread(&equipo,sizeof(equipo),1,archivo);
	while(!feof(archivo)){
			if ( strcmp(equipo.id,id)==0){ //strcmp compara ambos parametros y si son iguales devuelve un 0
			cout << "Ingrese el nombre (31 caracteres): ";
			cin >> equipo.nombre;
			cout << "Ingrese potencia de ataque (0-100): ";
			cin >> equipo.potenciaAtaque;
			cout << "Ingrese potencia de defensa (0-100): ";
			cin >> equipo.potenciaDefensa;
			cout<<"Posicion "<<ftell(archivo)-44<<endl;
			getch();
			fseek(archivo,ftell(archivo)-44,SEEK_SET);
			fwrite(&equipo, sizeof(equipo), 1, archivo);
			goto final;
		}else
	
		fread(&equipo,sizeof(equipo),1,archivo);
	}
		final:	
		fclose(archivo);
	
}

bool GuardarEquipo(Equipo equipo){
	// este metodo devuelve TRUE si pudo guardar el equipo, FALSE si no pudo


	FILE* archivo = fopen(FILENAME, "a");

	fwrite(&equipo, sizeof(equipo), 1, archivo);

	fclose(archivo);
	return true;
}



void VerEquipos(){
	// muestra los equipos del archivo
	
	Equipo equipo;
	FILE* archivo = fopen(FILENAME, "rb");
	if(archivo==NULL){
	cout<<"El archivo esta vacio. Agregue un equipo para poder realizar la visualizacion";
	}else{
		cout << "Lista de equipos:" << endl;
		fread(&equipo,sizeof(equipo),1,archivo);
		while(!feof(archivo)){
			
			cout << equipo.id << " " << equipo.nombre << " (" << equipo.potenciaAtaque << " - " << equipo.potenciaDefensa << ")" << endl;
			fread(&equipo,sizeof(equipo),1,archivo);
		}
	}
	fclose(archivo);

}




void AgregarEquipo(){
	// funcion para agregar equipo. Si encuentra que el equipo ya existe, pregunta para modificarlo.

	Equipo equipo;
	char modificar[1];

	cout << "Ingrese el identificador (3 caracteres): ";

	cin >> equipo.id;
	

	if(YaEstaEquipo(equipo.id)){
		cout << " ## Este equipo ya se encuentra cargado, desea modificarlo? (S/N):";
		cin >> modificar;
		if(strcmp(modificar,"s")==0||strcmp(modificar,"S")==0){
			
		
			ModificarEquipo(equipo.id);
		}
	} else {
		cout << "Ingrese el nombre (31 caracteres): ";

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


void EliminarEquipo(){
//Funcion para eliminar equipos.	
char id[4];
char modificar[1];
int n;
Equipo equipo;

cout<<"Ingrese el identificador del equipo que desea borrar. ";
cin>>id;
FILE* archivo = fopen(FILENAME, "rb");
FILE* archivotemp = fopen(FILEtemp, "a");
 //A continuacion se copia los registros de EQUIPOS.BIN a EQUIPOStemp.BIN, descartando el registro que se quiere eliminar
	fread(&equipo,sizeof(equipo),1,archivo);
	while(!feof(archivo)){
		if (strcmp(equipo.id,id)!=0){
		fseek(archivotemp,ftell(archivotemp)-44,SEEK_SET);
		fwrite(&equipo, sizeof(equipo), 1, archivotemp);
		}
			
		fread(&equipo,sizeof(equipo),1,archivo); 
	}
	
	fclose(archivotemp);
	fclose(archivo);
	//Se borra EQUIPOS.BIN
	remove("EQUIPOS.BIN");
	rename("EQUIPOStemp.BIN", "EQUIPOS.BIN");
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
				system("cls"); //Borra la pantalla
				break;
			case 2:
				EliminarEquipo();
			
				system("cls");
				break;
			case 3:
				VerEquipos();
				getch(); 
			
				system("cls");
				break;
			case 0:
				cout << "SALIR" << endl;;
				break;
			default:
				cout << opcion << " no es una opcion valida, intente nuevamente" << endl;
				getch();
				system("cls");
		}
	}
	cout << "Gracias por usar nuestro programa!" << endl;

	return 0;
}
