/* 
Hecho por:
González Ramírez José Manuel
Qui Mora Ángel Ernesto
Tirado Romero Juan José
*/

#include <stdio.h>
#include <windows.h>
#include <conio.h>

struct entrenador {
	id[10];
	especialidad[15];
	primerNombre[15];
	segundoNombre[15];
	apellidoMaterno[15];
	apellidoPaterno[15];
	telefono[10];
	correo[20];
	direccion[20];
	turno[10];
} ent[10]; // Usaremos las 3 primeras letras para todas las estructuras

struct servicios {
	id[10];
	servicio[20];
	idInstructor[10];
	rutina[20];
} ser[10];

struct registro {
	id[10];
	fechaRegistro[11];
	vigenciaRegistro[11];
} reg[10];

struct cliente {
	id[10];
	primerNombre[15];
	segundoNombre[15];
	apellidoMaterno[15];
	apellidoPaterno[15];
	telefono[10];
	correo[20];
	direccion[20];
	turno[10];
	idRegistro[10];
	idServicios[10];
} cli[10];



int main() {
	return 0;
	int x;
	do{
		printf("holaaaaaaa");
		x++;
		printf("ayuda dios");
	}while(x<10);
}
