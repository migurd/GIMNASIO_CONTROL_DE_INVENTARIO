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

int main() {
	for (int i = 0; i <= 10; i++)
	{
		printf("dsff\n");
	}
}
