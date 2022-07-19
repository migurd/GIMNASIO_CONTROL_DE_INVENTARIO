/* 
Hecho por:
Gonzalez Ramirez Jose Manuel
Qui Mora Angel Ernesto
Tirado Romero Juan Jose
*/

#include <stdio.h>
#include <windows.h>
#include <conio.h>

struct entrenador {
	int id;
	char especialidad[15];
	char primerNombre[15];
	char segundoNombre[15];
	char apellidoMaterno[15];
	char apellidoPaterno[15];
	long telefono;
	char correo[20];
	char direccion[20];
	char turno[10];
} ent[10]; // Usaremos las 3 primeras letras para todas las estructuras

struct servicios {
	int id;
	char servicio[20];
	int idInstructor;
	char rutina[20];
} ser[10];

struct registro {
	int id;
	char fechaRegistro[11];
	char vigenciaRegistro[11];
} reg[10];

struct cliente {
	int id;
	char primerNombre[15];
	char segundoNombre[15];
	char apellidoMaterno[15];
	char apellidoPaterno[15];
	long telefono;
	char correo[20];
	char direccion[20];
	char turno[10];
	int idRegistro;
	int idServicios;
} cli[10];

void menu();
void menuEntrenador();
void menuServicios();
void menuRegistro();
void menuCliente();

void addEntrenador();
void addServicios(int idEntrenador);
void addCliente(int idEntrenador, int idCliente);

void consultarEntrenador();

int nument(int lon);

int main() {
	menu();
	return 0;
}

void menu() {
	int option = 0;
	
	do {
		system("cls");
		printf("\t\t\t\t\t======\tMen%c principal\t======\n\n", 163);
		printf("\t\t\t\t\t1. Men%c entrenador\n", 163);
		printf("\t\t\t\t\t2. Men%c servicios\n", 163);
		printf("\t\t\t\t\t3. Men%c registro\n", 163);
		printf("\t\t\t\t\t4. Men%c cliente\n", 163);
		printf("\t\t\t\t\t5. Salir\n\n\n", 163);
		
		printf("\t\t\t\t\t> > Elige una opci%cn: ", 162);
		option = nument(1);
		
		switch (option) {
			case 1:
				menuEntrenador();
				break;
			case 2:
				menuServicios();
				break;
			case 3:
				menuRegistro();
				break;
			case 4:
				menuCliente();
				break;
			case 5:
				system("cls");
				printf("\n\n\n\n\n\t\t\t\t\t\tCerrando...");
				Sleep(1000);
				break;
			default:
				system("cls");
				printf("\n\n\n\n\n\t\t\t\t\tOpci%cn inv%clida. Elige de nuevo.", 162, 160);
				Sleep(1000);
				break;
		}
	} while (option != 5);
}

void menuEntrenador() {
	int option = 0;
	
	do {
		system("cls");
		printf("\t\t\t\t\t======\tMen%c entrenador\t======\n\n", 163);
		printf("\t\t\t\t\t1. Agregar\n", 163);
		printf("\t\t\t\t\t2. Consultar\n", 163);
		printf("\t\t\t\t\t3. Modificar\n", 163);
		printf("\t\t\t\t\t4. Eliminar\n", 163);
		printf("\t\t\t\t\t5. Regresar\n\n\n", 163);
		
		printf("\t\t\t\t\t> > Elige una opci%cn: ", 162);
		option = nument(1);
		
		switch (option) {
			case 1:
				menuEntrenador();
				break;
			case 2:
				menuServicios();
				break;
			case 3:
				menuRegistro();
				break;
			case 4:
				menuCliente();
				break;
			case 5:
				break;
			default:
				system("cls");
				printf("\n\n\n\n\n\t\t\t\t\tOpci%cn inv%clida. Elige de nuevo.", 162, 160);
				Sleep(300);
				break;
		}
	} while (option != 5);
}

void menuServicios() {
	int option = 0;
	
	do {
		system("cls");
		printf("\t\t\t\t\t======\tMen%c servicios\t======\n\n", 163);
		printf("\t\t\t\t\t1. Agregar\n", 163);
		
		printf("\t\t\t\t\t2. Consultar\n", 163);
		
		printf("\t\t\t\t\t3. Modificar\n", 163);
		printf("\t\t\t\t\t4. Eliminar\n", 163);
		printf("\t\t\t\t\t5. Regresar\n\n\n", 163);
		
		printf("\t\t\t\t\t> > Elige una opci%cn: ", 162);
		option = nument(1);
		
		switch (option) {
			case 1:
				menuEntrenador();
				break;
			case 2:
				menuServicios();
				break;
			case 3:
				menuRegistro();
				break;
			case 4:
				menuCliente();
				break;
			case 5:
				break;
			default:
				system("cls");
				printf("\n\n\n\n\n\t\t\t\t\tOpci%cn inv%clida. Elige de nuevo.", 162, 160);
				Sleep(300);
				break;
		}
	} while (option != 5);
}

void menuRegistro() {
	
}

void menuCliente() {
	int option = 0;
	
	do {
		system("cls");
		printf("\t\t\t\t\t======\tMen%c cliente\t======\n\n", 163);
		printf("\t\t\t\t\t1. Agregar\n", 163);
		printf("\t\t\t\t\t2. Consultar\n", 163);
		printf("\t\t\t\t\t3. Modificar\n", 163);
		printf("\t\t\t\t\t4. Eliminar\n", 163);
		printf("\t\t\t\t\t5. Regresar\n\n\n", 163);
		
		printf("\t\t\t\t\t> > Elige una opci%cn: ", 162);
		option = nument(1);
		
		switch (option) {
			case 1:
				menuEntrenador();
				break;
			case 2:
				menuServicios();
				break;
			case 3:
				menuRegistro();
				break;
			case 4:
				menuCliente();
				break;
			case 5:
				break;
			default:
				system("cls");
				printf("\n\n\n\n\n\t\t\t\t\tOpci%cn inv%clida. Elige de nuevo.", 162, 160);
				Sleep(300);
				break;
		}
	} while (option != 5);
}



int nument(int lon) {
	char car, cadena[lon+1]={' '};
	int x=0;
	do{
		car = getch();
		if(car >= 48 && car <= 57){
			printf("%c", car);
			cadena[x]=car;
			x++;
		}
		if(car==8 && x>0){
			printf("\b \b");
			x--;
			cadena[x]=' ';
		}
	}while(car != 13 && x < lon);
	cadena[x]='\n';
	return atoi(cadena);
}
