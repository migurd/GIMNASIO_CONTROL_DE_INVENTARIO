/* 
Hecho por:
Gonzalez Ramirez Jose Manuel
Qui Mora Angel Ernesto
Tirado Romero Juan Jose
*/

#include <stdio.h>
#include <windows.h>
#include <conio.h>

void gotoxy(int x,int y);
void menu();
void menuEntrenador();
void menuServicios();
void menuRegistro();
void menuCliente();

void leerArchivoEntrenador();
void guardarArchivoEntrenador(struct entrenador ent[]);

void leerArchivoCliente();
void guardarArchivoCliente(struct cliente cli[]);

void addEntrenador();
void consultarEntrenador();
void consultarEntrenadorGeneral();
void consultarEntrenadorEspecifico();
void modificarEntrenador();
void eliminarEntrenador();
void displayEntrenador(int p, int y);
int idPosition(struct entrenador ent[], int idWanted);
int idRepetida(struct entrenador ent[], int idWanted);

void addCliente();
void consultarCliente();
void consultarClienteGeneral();
void consultarClienteEspecifico();
void modificarCliente();
void eliminarCliente();
void displayCliente(int p, int y);
int idPositionCli(struct cliente cli[], int idWanted);
int idRepetidaCli(struct cliente cli[], int idWanted);

void addServicios(int idEntrenador);

char yesOrNo(int length);
long nument(int lon);
void valitext(int lon,char *pnom);
void valifec(char *pfecha);
void valiNum(char *pnom, int length);

struct entrenador {
	int id;
	char especialidad[13];
	char primerNombre[11];
	char segundoNombre[11];
	char apellidoMaterno[11];
	char apellidoPaterno[11];
	char telefono[11];
	char turno[11];
	int estado;
} ent[10]; // Usaremos las 3 primeras letras para todas las estructuras

struct servicios {
	int id;
	char idInstructor;
	char servicio[20];
	char rutina[20];
} ser[10];

struct registro {
	int id;
	char fechaRegistro[11];
	char vigenciaRegistro[11];
} reg[10];

struct cliente {
	int id;
	char primerNombre[11];
	char segundoNombre[11];
	char apellidoMaterno[11];
	char apellidoPaterno[11];
	char telefono[11];
	char direccion[16];
	char turno[11];
//	int idRegistro;
	int estado;
//	int idServicios;
} cli[10];

int main() {
//	system("COLOR C1");
	menu();
	return 0;
}

void menu() {
	int option = 0;
	
	do {
		system("cls");
		gotoxy(40, 5);
		printf("<====     Men%c principal     ====>", 163);
		gotoxy(40, 8);
		printf("1. Men%c entrenador\n", 163);
		gotoxy(40, 9);
		printf("2. Men%c cliente\n", 163);
		gotoxy(40, 10);
		printf("3. Men%c registro\n", 163);
		gotoxy(40, 11);
		printf("4. Men%c servicios\n", 163);
		gotoxy(40, 12);
		printf("5. Salir\n\n\n", 163);
		
		gotoxy(44, 15);
		printf("> > Elige una opci%cn: ", 162);
		option = nument(1);
		
		switch (option) {
			case 1:
				menuEntrenador();
				break;
			case 2:
				menuCliente();
				break;
			case 3:
				menuRegistro();
				break;
			case 4:
				menuServicios();
				break;
			case 5:
				system("cls");
				gotoxy(46,8);
				printf("Cerrando...\n\n\n");
				Sleep(1000);
				break;
			default:
				system("cls");
				gotoxy(40,8);
				printf("Opci%cn inv%clida. Elige de nuevo.", 162, 160);
				Sleep(1000);
				break;
		}
	} while (option != 5);
}

void menuEntrenador() {
	int option = 0;
	
	do {
		system("cls");
		gotoxy(40, 5);
		printf("======   Men%c entrenador   ======", 163);
		gotoxy(40, 8);
		printf("1. Agregar", 163);
		gotoxy(40, 9);
		printf("2. Consultar", 163);
		gotoxy(40, 10);
		printf("3. Modificar", 163);
		gotoxy(40, 11);
		printf("4. Eliminar", 163);
		gotoxy(40, 12);
		printf("5. Regresar", 163);
		
		gotoxy(44, 15);
		printf("> > Elige una opci%cn: ", 162);
		option = nument(1);
		leerArchivoEntrenador();
		switch (option) {
			case 1:
				addEntrenador();
				break;
			case 2:
				consultarEntrenador();
				break;
			case 3:
				modificarEntrenador();
				break;
			case 4:
				eliminarEntrenador();
				break;
			case 5:
				break;
			default:
				system("cls");
				printf("Opci%cn inv%clida. Elige de nuevo.", 162, 160);
				Sleep(300);
				break;
		}
		guardarArchivoEntrenador(ent);
	} while (option != 5);
}

void menuServicios() {
	system("cls");
	printf("No hay nada aqui we salte alv");
	getch();
}

void menuRegistro() {
	system("cls");
	printf("No hay nada aqui we salte alv");
	getch();
}

void menuCliente() {
	int option = 0;
	
	do {
		system("cls");
		gotoxy(40, 5);
		printf("<====     Men%c Cliente     ====>", 163);
		gotoxy(40, 8);
		printf("1. Agregar", 163);
		gotoxy(40, 9);
		printf("2. Consultar", 163);
		gotoxy(40, 10);
		printf("3. Modificar", 163);
		gotoxy(40, 11);
		printf("4. Eliminar", 163);
		gotoxy(40, 12);
		printf("5. Regresar", 163);
		
		gotoxy(44, 15);
		printf("> > Elige una opci%cn: ", 162);
		option = nument(1);
		leerArchivoCliente();
		switch (option) {
			case 1:
				addCliente();
				break;
			case 2:
				consultarCliente();
				break;
			case 3:
				modificarCliente();
				break;
			case 4:
				eliminarCliente();
				break;
			case 5:
				break;
			default:
				system("cls");
				printf("Opci%cn inv%clida. Elige de nuevo.", 162, 160);
				Sleep(300);
				break;
		}
		guardarArchivoCliente(cli);
	} while (option != 5);
}

void addEntrenador() {
	FILE *fp;
    char option = 'Y';
    int i = 0, j = 0, p = 0;
    while(option == 'Y')
    {
    	i = 0, j = 0;
    	fp = fopen("src/entrenadores.txt", "a+");
	    if(fp == NULL){
	    	system("cls");
	        gotoxy(10,5);
	        printf("Error abriendo el archivo");
	        exit(1);
	    }
    	system("cls");
	    while(fread(&ent[j], sizeof(struct entrenador), 1, fp) == 1){
	    	if (ent[j].estado == 1) { // Solo se imprimen los activos
	    		i++;
	    	}
	    	j++;
		}
		
		/*printf("%i", i); // Cantidad de activos
		getch();
		printf("\n%i", j); // Cantidad de activos
		getch();*/
    	if (i < 10)
    	{
	    	gotoxy(15,3);
	        printf("====    A%cadir entrenador    ====", 164);
	        gotoxy(15,5);
	        printf("Inserta los detalles del entrenador");
	        gotoxy(15,7);
	        printf("ID: ");
	        ent[j].id = nument(3);
	        if (idRepetida(ent, ent[j].id) == 1) { // Si la ID es repetida, devuelve 1
	        	system("cls");
	        	gotoxy(10, 5);
	        	p = idPosition(ent, ent[j].id);
				printf("La id `%i` es repetida: ", ent[p].id);
				displayEntrenador(p, 8);
				gotoxy(10, 15);
		        printf("%cDesea intentar con otra ID? (Y / N): ", 168, 164);
		        option = yesOrNo(1);
		        fclose(fp);
		        if (option == 'Y') {
		        	addEntrenador();
		        	return;
				}
				return;
			}
	        gotoxy(15,8);
	        printf("Especialidad: ");
	        valitext(12, ent[j].especialidad);
	        gotoxy(15,9);
	        printf("Primer nombre: ");
	        valitext(10, ent[j].primerNombre);
			gotoxy(15,10);
	        printf("Segundo nombre: ");
	        valitext(10, ent[j].segundoNombre);
	        gotoxy(15,11);
	        printf("Apellido Paterno: ");
	        valitext(10, ent[j].apellidoPaterno);
	        gotoxy(15,12);
	        printf("Apellido Materno: ");
	        valitext(10, ent[j].apellidoMaterno);
			gotoxy(15,13);
			printf("Tel%cfono: ", 130);
	        valiNum(ent[j].telefono, 10);
			gotoxy(15,14);
			printf("Turno: ", 130);
	        valitext(10, ent[j].turno);
	        ent[j].estado = 1;
	        fwrite(&ent[j], sizeof(struct entrenador), 1, fp);
	        gotoxy(15,16);
			printf("%cEntrenador a%cadido exitosamente!", 173, 164);
	        getch();
			gotoxy(15,18);
	        printf("%cDesea a%cadir otro entrenador? (Y / N): ", 168, 164);
	        option = yesOrNo(1);
	        fclose(fp);
		}
		else {
			gotoxy(10, 5);
			printf("No hay espacio de almacentamiento para m%cs entrenadores. :(", 160);
			fclose(fp);
			getch();
			return;
		}
    }
    fclose(fp);
}

void consultarEntrenador() {
	int option = 0;
	
	do {
		system("cls");
		gotoxy(40, 5);
		printf("====    Consulta Entrenador    ====");
		gotoxy(40, 8);
		printf("1. General");
		gotoxy(40, 9);
		printf("2. Espec%cfico", 161);
		gotoxy(40, 10);
		printf("3. Regresar");
		
		gotoxy(44, 15);
		printf("> > Elige una opci%cn: ", 162);
		option = nument(1);
		
		switch (option) {
			case 1:
				consultarEntrenadorGeneral();
				break;
			case 2:
				consultarEntrenadorEspecifico();
				break;
			case 3:
				break;
			default:
				system("cls");
				gotoxy(40, 10);
				printf("Opci%cn inv%clida. Elige de nuevo.", 162, 160);
				Sleep(300);
				break;
		}
	} while (option != 3);
	
}

void consultarEntrenadorGeneral() {
	FILE *fp;
    int i = 0, j;
    system("cls");
    gotoxy(36,2);
    printf("====    Consulta General Entrenador    ====");
    gotoxy(10,5);
    printf("ID  Especialidad    P. Nombre   S. Nombre   Apellido P.  Apellido M.  Tel%cfono     Turno       Estado", 130, 162);
    gotoxy(10,6);
    printf("_______________________________________________________________________________________________________");
    fp = fopen("src/entrenadores.txt","r+");
    if(fp == NULL){
        gotoxy(10,8);
        printf("Error abriendo el archivo");
        exit(1);
    }
    j=8;
    while(fread(&ent[i], sizeof(struct entrenador), 1, fp) == 1){
    	if (ent[i].estado == 1) { // Solo se imprimen los activos
    		gotoxy(10, j);
	        printf("%-4d%-16s%-12s%-12s%-13s%-13s%-13s%-12s%d", ent[i].id, ent[i].especialidad, ent[i].primerNombre, ent[i].segundoNombre, ent[i].apellidoPaterno, ent[i].apellidoMaterno, ent[i].telefono, ent[i].turno, ent[i].estado);
	        i++;
	        j++;
		}
        
    }
    fclose(fp);
    gotoxy(10, j+3);
    printf("Presiona cualquier tecla para salir");
    getch();
    
}

void consultarEntrenadorEspecifico() {
	int cod;
	int p; // p = position
	int i = 0;
	int condition = 1;
	char option='Y';
	FILE *fp;
	p = idPosition(ent, cod); 
	while(option == 'Y'){
		system("cls");
		gotoxy(38,2);
	    printf("<====     Consulta Espec%cfica Entrenador     ====>",161);
	    gotoxy(38,5);
		printf("ID del Entrenador: ");
		cod = nument(3);
		fp = fopen("src/entrenadores.txt","r+");
		while(!feof(fp)){ 
			fread(&ent[i],sizeof(ent[i]),1,fp);
			if(cod == ent[i].id){ // Lo imprime aunque est� inactivo
				system("cls");
				gotoxy(38,2);
			    printf("<====     Consulta Espec%cfica Entrenador     ====>",161);
			    gotoxy(10,5);
			    printf("ID  Especialidad    P. Nombre   S. Nombre   Apellido P.  Apellido M.  Tel%cfono     Turno       Estado", 130, 162);
			    gotoxy(10,6);
			    printf("_______________________________________________________________________________________________________");
				gotoxy(10, 8);
	        	printf("%-4d%-16s%-12s%-12s%-13s%-13s%-13s%-12s%d", ent[i].id, ent[i].especialidad, ent[i].primerNombre, ent[i].segundoNombre, ent[i].apellidoPaterno, ent[i].apellidoMaterno, ent[i].telefono, ent[i].turno, ent[i].estado);
				gotoxy(10,12);
				getch();
		        printf("%cDesea buscar otro entrenador? (Y / N): ", 168, 164);
		        option = yesOrNo(1);
		        condition = 0;
		        fclose(fp); // ALGO CLAVE ERA QUE CERRARAN ESTOS
				break;
			}
		}
		if (p == NULL && condition == 1) {
			system("cls");
			gotoxy(10,4);
			printf("La ID `%i` no se encuentra registrada.", cod);
			gotoxy(10,5);
			printf("%cDesea buscar otro entrenador para consultar? (Y / N): ", 168, 164);
			fflush(stdin);
			option = yesOrNo(1);
			fclose(fp); // ALGO CLAVE ERA QUE CERRARAN ESTOS
			if (option == 'N')
				break;
		}
		condition = 1;
	}
	fclose(fp);
	
}

void modificarEntrenador() {
    FILE *fp, *temp;
    char option = 'Y';
	int idEntrenador; // Esto era char antes, daba 89 en vez de 344 LMAO
	int i = 0, p = 0;
	do {
		system("cls");
		gotoxy(10,3);
	    printf("====    Modificar Entrenador    ====");
	    gotoxy(10,5);
	    printf("Inserta la ID de entrenador a modificar: ");
	    idEntrenador = nument(3);
	    p = idPosition(ent, idEntrenador);
	    if (ent[p].id == idEntrenador && ent[p].estado == 1)
	    {
	    	displayEntrenador(p, 7);
		    gotoxy(10,14);
			printf("%cEst%c seguro que quiere editar el usuario con la ID `%i`? (Y / N): ", 168, 160, idEntrenador);
		    option = yesOrNo(1);
		}
		while(idEntrenador == ent[p].id && ent[p].estado == 1) // Puedes modificar mientras la ID coincida y el entrenador se encuentre activo
	    {
	    	system("cls");
	    	if (option == 'N')
				return;
		    fp = fopen("src/entrenadores.txt","r+");
		    if(fp == NULL) {
		        gotoxy(10,6);
		        printf("Error abriendo el archivo");
		        exit(1);
		    }
		    temp = fopen("src/temporal.txt","w+");
		    if(fp == NULL) {
		        gotoxy(10,6);
		        printf("Error abriendo el archivo");
		        exit(1);
		    }
        	displayEntrenador(p, 2);
            gotoxy(10,8);
	        printf("Especialidad: ");
	        valitext(12, ent[p].especialidad);
	        gotoxy(10,9);
	        printf("Primer nombre: ");
	        valitext(10, ent[p].primerNombre);
			gotoxy(10,10);
	        printf("Segundo nombre: ");
	        valitext(10, ent[p].segundoNombre);
	        gotoxy(10,11);
	        printf("Apellido Paterno: ");
	        valitext(10, ent[p].apellidoPaterno);
	        gotoxy(10,12);
	        printf("Apellido Materno: ");
	        valitext(10, ent[p].apellidoMaterno);
			gotoxy(10,13);
			printf("Tel%cfono: ", 130);
	        valiNum(ent[p].telefono, 10);
			gotoxy(10,14);
			printf("Turno: ", 130);
	        valitext(10, ent[p].turno);
	        gotoxy(10,16);
	        printf("%cDesea guardar los cambios? (Y / N): ", 168);
	        option = yesOrNo(1);
			gotoxy(10,18);
			// Primero guarda la variable cambiada y la mueve al principio,
			// entonces, anota el resto menos la cambiada.
			if(option == 'Y')
				fwrite(&ent[p], sizeof(ent[p]), 1, temp); // Primero se anota la reci�n guardada
			while (fread(&ent[i], sizeof(struct entrenador), 1, fp) == 1) {
				if (ent[i].id != ent[p].id) { // Condici�n para que no se repita la misma id despu�s del cambio
	    			fwrite(&ent[i], sizeof(ent[i]), 1, temp);
				}
				i++;
			}
	    	fclose(fp);
			fclose(temp);
			if(option == 'Y')
			{
				remove("src/entrenadores.txt");
			    rename("src/temporal.txt", "src/entrenadores.txt");
		    	printf("%cEntrenador modificado exitosamente!", 173);
			}
			else {
				printf("No se hizo ning%cn cambio", 163);
				remove("src/temporal.txt");
			}
	        getch();
            return;
	    }
	    
    	if (option == 'Y')
    	{
    		system("cls");
			gotoxy(10,4);
			printf("La ID `%i` no se encuentra registrada o ya ha sido eliminada.", idEntrenador);
			gotoxy(10,7);
			printf("%cDesea buscar otro entrenador para modificar? (Y / N): ", 168, 164);
			option = yesOrNo(1);
			if (option == 'N')
				return;
		}
	}while (option == 'Y');
    
}

void eliminarEntrenador() {
	int id, i, p; // P = position
	char option = 'Y';
    FILE *fp,*temp;
    do {
	    system("cls");
		gotoxy(10,3);
	    printf("====    Eliminar entrenador    ====");
	    gotoxy(10,5);
	    printf("Insertar la ID a eliminar: ");
	    id = nument(3);
	    p = idPosition(ent, id);
	    
	    while (id == ent[p].id && option == 'Y' && ent[p].estado == 1)
	    {
		    fp = fopen("src/entrenadores.txt","r+");
		    if(fp == NULL){
		        gotoxy(10,6);
		        printf("Error al abrir el archivo");
		        exit(1);
		    }
		    temp = fopen("src/temporal.txt","w+");
		    if(temp == NULL) {
		        gotoxy(10,6);
		        printf("Error al abrir el archivo");
		        exit(1);
	    	}
			displayEntrenador(p, 5);
			gotoxy(10,12);
	    	ent[p].estado = 0; // El estado queda desactivo y ya no se mostrar� o tomar� en cuenta
			printf("%cEst%cs seguro que quiere eliminar el usuario con la ID `%i`? (Y / N): ", 168, 160, id);
		    option = yesOrNo(1);
		 	if(option == 'Y')
				fwrite(&ent[p], sizeof(struct entrenador), 1, temp); // Primero se anota la reci�n guardada
			while (fread(&ent[i], sizeof(struct entrenador), 1, fp) == 1) {
			    /*printf("\n%i", ent[i].id);
			    getch();
			    printf("\n%i", ent[p].id);
			    getch();*/
				if (ent[i].id != ent[p].id) { // Condici�n para que no se repita la misma id despu�s del cambio
	    			fwrite(&ent[i], sizeof(struct entrenador), 1, temp);
	    		}
	    		i++;
	    	}
	    	fclose(fp);
			fclose(temp);
			gotoxy(10,15);
			if(option == 'Y')
			{
				remove("src/entrenadores.txt");
			    rename("src/temporal.txt", "src/entrenadores.txt");
		    	printf("%cEntrenador eliminado exitosamente!", 173);
			}
			else {
				printf("No se hizo ning%cn cambio", 163);
				remove("src/temporal.txt");
			}
	        getch();
            return;
		}
		system("cls");
		gotoxy(10,4);
		printf("La ID `%i` no se encuentra registrada o ya ha sido eliminada.", id);
		gotoxy(10,5);
		printf("%cDesea buscar otro entrenador para eliminar? (Y / N): ", 168, 164);
		option = yesOrNo(1);
		if (option == 'N')
			return;
	} while (option == 'Y');
}
	
void displayEntrenador(int p, int y) {
	// y representa la parte de Gotoxy para que baje
	gotoxy(10,y);
	printf("ID  Especialidad    P. Nombre   S. Nombre   Apellido P.  Apellido M.  Tel%cfono     Turno       Estado", 130, 162);
	gotoxy(10,y+1);
	printf("_______________________________________________________________________________________________________");
	gotoxy(10, y+3);
	printf("%-4d%-16s%-12s%-12s%-13s%-13s%-13s%-12s%d", ent[p].id, ent[p].especialidad, ent[p].primerNombre, ent[p].segundoNombre, ent[p].apellidoPaterno, ent[p].apellidoMaterno, ent[p].telefono, ent[p].turno, ent[p].estado);
}

void addCliente() {    //Quite el int entrenadores y el int servicios por el momento
	FILE *fp;
    char option = 'Y';
    int i = 0, j = 0, p = 0;
    while(option == 'Y')
    {
    	i = 0, j = 0;
    	fp = fopen("src/clientes.txt", "a+");
	    if(fp == NULL){
	    	system("cls");
	        gotoxy(10,5);
	        printf("Error abriendo el archivo");
	        exit(1);
	    }
    	system("cls");
	    while(fread(&cli[j], sizeof(struct cliente), 1, fp) == 1){
	    	if (cli[j].estado == 1) { // Solo se imprimen los activos
	    		i++;
	    	}
	    	j++;
		}
		
		/*printf("%i", i); // Cantidad de activos
		getch();
		printf("\n%i", j); // Cantidad de activos
		getch();*/
    	if (i < 10)
    	{
	    	gotoxy(15,3);
	        printf("<====     A%cadir Cliente     ====>", 164);
	        gotoxy(15,5);
	        printf("Inserta los detalles del cliente");
	        gotoxy(15,7);
	        printf("ID: ");
	        cli[j].id = nument(3);
	        if (idRepetidaCli(cli, cli[j].id) == 1) { // Si la ID es repetida, devuelve 1
	        	system("cls");
	        	gotoxy(10, 5);
	        	p = idPositionCli(cli, cli[j].id);
				printf("La id `%i` es repetida: ", cli[p].id);
				displayCliente(p, 8);
				gotoxy(10, 15);
		        printf("%cDesea intentar con otra ID? (Y / N): ", 168, 164);
		        option = yesOrNo(1);
		        fclose(fp);
		        if (option == 'Y') {
		        	addCliente();
		        	return;
				}
				return;
			}
	        gotoxy(15,8);
			printf("Primer nombre: ");
			valitext(10, cli[j].primerNombre);
			gotoxy(15,9);
			printf("Segundo nombre: ");
			valitext(10, cli[j].segundoNombre);
			gotoxy(15,10);
			printf("Apellido paterno: ");
			valitext(10, cli[j].apellidoPaterno);
			gotoxy(15,11);
			printf("Apellido materno: ");
			valitext(10, cli[j].apellidoMaterno);
			gotoxy(15,12);
			printf("Tel%cfono: ",130);
			valiNum(cli[j].telefono, 10);
			gotoxy(15,13);
			printf("Direcci%cn: ", 162);
			valitext(15,cli[j].direccion);
			gotoxy(15,14);
			printf("Turno: ", 130);
			valitext(10, cli[j].turno);
			cli[j].estado = 1;
			fwrite(&cli[j], sizeof(struct cliente), 1, fp);
			gotoxy(15,16);
			printf("%cCliente a%cadido exitosamente!", 173, 164);
			getch();
			gotoxy(15,18);
			printf("%cDesea a%cadir otro cliente? (Y / N): ", 168, 164);
			option = yesOrNo(1);
			fclose(fp);
		}
		else {
			gotoxy(10, 5);
			printf("No hay espacio de almacentamiento para m%cs clientes. :(", 160);
			fclose(fp);
			getch();
			return;
		}
    }
    fclose(fp);
}

void consultarCliente(){
	int option = 0;
	
	do {
		system("cls");
		gotoxy(40, 5);
		printf("<====     Men%c Consulta Cliente     ====>", 163);
		gotoxy(40, 8);
		printf("1. General");
		gotoxy(40, 9);
		printf("2. Espec%cfico", 161);
		gotoxy(40, 10);
		printf("3. Regresar");
		
		gotoxy(44, 15);
		printf("> > Elige una opci%cn: ", 162);
		option = nument(1);
		
		switch (option) {
			case 1:
				consultarClienteGeneral();
				break;
			case 2:
				consultarClienteEspecifico();
				break;
			case 3:
				break;
			default:
				system("cls");
				gotoxy(40, 10);
				printf("Opci%cn inv%clida. Elige de nuevo.", 162, 160);
				Sleep(300);
				break;
		}
	} while (option != 3);
}

void consultarClienteGeneral(){
	FILE *fp;
    int i = 0, j;
    system("cls");
    gotoxy(36,2);
    printf("<====     Consulta General Cliente     ====>");
    gotoxy(10,5);
    printf("ID   P. Nombre    S. Nombre   Apellido P.   Apellido M.  Tel%cfono     Direcci%cn        Turno       Estado", 130, 162);
    gotoxy(10,6);
    printf("_____________________________________________________________________________________________________________");
    fp = fopen("src/clientes.txt","r+");
    if(fp == NULL){
        gotoxy(10,8);
        printf("Error abriendo el archivo");
        exit(1);
    }
    j=8;
    while(fread(&cli[i], sizeof(struct cliente), 1, fp) == 1){
    	if (cli[i].estado == 1){
    		gotoxy(10, j);
			printf("%-5d%-13s%-12s%-14s%-13s%-13s%-17s%-12s%d", cli[i].id, cli[i].primerNombre, cli[i].segundoNombre, cli[i].apellidoPaterno, cli[i].apellidoMaterno, cli[i].telefono, cli[i].direccion, cli[i].turno, cli[i].estado);
     		i++;
        	j++;
		}
    }
    fclose(fp);
    gotoxy(10, j+3);
    printf("Presiona cualquier tecla para salir");
    getch();
}

void consultarClienteEspecifico(){
	int cod;
	int p; // p = position
	int i = 0;
	int condition = 1;
	char option='Y';
	FILE *fp;
	p = idPositionCli(cli, cod);
	while(option == 'Y'){
		system("cls");
		gotoxy(38,2);
	    printf("<====     Consulta Espec%cfica Cliente     ====>",161);
	    gotoxy(38,5);
		printf("ID del Cliente: ");
		cod = nument(3);
		fp = fopen("src/clientes.txt","r+");
		while(!feof(fp)){ // Avanza al siguiente cli[i] si el anterior no est� presente
			fread(&cli[i],sizeof(cli[i]),1,fp);
			if(cod==cli[i].id){
				system("cls");
				gotoxy(38,2);
			    printf("<====     Consulta Espec%cfica Cliente     ====>",161);
			    gotoxy(10,5);
			    printf("ID   P. Nombre    S. Nombre   Apellido P.   Apellido M.  Tel%cfono     Direcci%cn        Turno       Estado", 130, 162);
			    gotoxy(10,6);
			    printf("_____________________________________________________________________________________________________________");
				gotoxy(10, 8);
	        	printf("%-5d%-13s%-12s%-14s%-13s%-13s%-17s%-12s%d", cli[i].id, cli[i].primerNombre, cli[i].segundoNombre, cli[i].apellidoPaterno, cli[i].apellidoMaterno, cli[i].telefono, cli[i].direccion, cli[i].turno, cli[i].estado);
				getch();
				gotoxy(10,12);
		        printf("%cDesea buscar otro cliente? (Y / N): ", 168, 164);
		        option = yesOrNo(1);
		        condition = 0;
		        fclose(fp); // ALGO CLAVE ERA QUE CERRARAN ESTOS
				break;
			}
		}
		if (p == NULL && condition == 1) {
			system("cls");
			gotoxy(10,4);
			printf("La ID `%i` no se encuentra registrada.", cod);
			gotoxy(10,5);
			printf("%cDesea buscar otro cliente para consultar? (Y / N): ", 168, 164);
			fflush(stdin);
			option = yesOrNo(1);
			fclose(fp); // ALGO CLAVE ERA QUE CERRARAN ESTOS
			if (option == 'N')
				break;
		}
		condition = 1;
	}
	fclose(fp);
}

void modificarCliente(){
	FILE *fp, *temp;
    char option = 'Y';
	int idCliente; // Esto era char antes, daba 89 en vez de 344 LMAO
	int i = 0, p = 0;
	do {
		system("cls");
		gotoxy(10,3);
	    printf("<====     Modificar Cliente     ====>");
	    gotoxy(10,5);
	    printf("Inserta la ID del cliente a modificar: ");
	    idCliente = nument(3);
	    p = idPositionCli(cli, idCliente);
	    if (cli[p].id == idCliente && cli[p].estado == 1)
	    {
	    	displayCliente(p, 7);
		    gotoxy(10,14);
			printf("%cEst%c seguro que quiere editar el cliente con la ID `%i`? (Y / N): ", 168, 160, idCliente);
		    option = yesOrNo(1);
		}
		while(idCliente == cli[p].id && cli[p].estado == 1) // Puedes modificar mientras la ID coincida y el entrenador se encuentre activo
	    {
	    	system("cls");
	    	if (option == 'N')
				return;
		    fp = fopen("src/clientes.txt","r+");
		    if(fp == NULL) {
		        gotoxy(10,6);
		        printf("Error abriendo el archivo");
		        exit(1);
		    }
		    temp = fopen("src/temporal.txt","w+");
		    if(fp == NULL) {
		        gotoxy(10,6);
		        printf("Error abriendo el archivo");
		        exit(1);
		    }
        	displayCliente(p, 2);
            gotoxy(10,8);
			printf("Primer Nombre: ");
			valitext(10, cli[p].primerNombre);
			gotoxy(10,9);
			printf("Segundo nombre: ");
			valitext(10, cli[p].segundoNombre);
			gotoxy(10,10);
			printf("Apellido paterno: ");
			valitext(10, cli[p].apellidoPaterno);
			gotoxy(10,11);
			printf("Apellido Materno: ");
			valitext(10, cli[p].apellidoMaterno);
			gotoxy(10,12);
			printf("Tel%cfono: ",130);
			valiNum(cli[p].telefono, 10);
			gotoxy(10,13);
			printf("Direcci%cn: ", 162);
			valitext(15, cli[p].direccion);
			fflush(stdin);
			gotoxy(10,14);
			printf("Turno: ", 130);
			valitext(10, cli[p].turno);
			gotoxy(10,16);
			printf("%cDesea guardar los cambios? (Y / N): ", 168);
			option = yesOrNo(1);
			gotoxy(10,18);
			// Primero guarda la variable cambiada y la mueve al principio,
			// entonces, anota el resto menos la cambiada.
			if(option == 'Y')
				fwrite(&cli[p], sizeof(cli[p]), 1, temp); // Primero se anota la reci�n guardada
			while (fread(&cli[i], sizeof(struct cliente), 1, fp) == 1){
				if (cli[i].id != cli[p].id){  // Condici�n para que no se repita la misma id despu�s del cambio
	    			fwrite(&cli[i], sizeof(cli[i]), 1, temp);
	    		}
	    		i++;
			}
	    	fclose(fp);
			fclose(temp);
			if(option == 'Y')
			{
				remove("src/clientes.txt");
			    rename("src/temporal.txt", "src/clientes.txt");
		    	printf("%cCliente modificado exitosamente!", 173);
			}
			else {
				printf("No se hizo ning%cn cambio", 163);
				remove("src/temporal.txt");
			}
	        getch();
            return;
	    }
	    
    	if (option == 'Y')
    	{
    		system("cls");
			gotoxy(10,4);
			printf("La ID `%i` no se encuentra registrada o ya ha sido eliminada.", idCliente);
			gotoxy(10,7);
			printf("%cDesea buscar otro cliente para modificar? (Y / N): ", 168, 164);
			option = yesOrNo(1);
			if (option == 'N')
				return;
		}
	}while (option == 'Y');
}

void eliminarCliente(){
	int id, i, p; // P = position
	char option = 'Y';
    FILE *fp,*temp;
    do {
	    system("cls");
		gotoxy(10,3);
	    printf("<====     Eliminar cliente     ====>");
	    gotoxy(10,5);
	    printf("Insertar la ID a eliminar: ");
	    id = nument(3);
	    p = idPositionCli(cli, id);
	    
	    while (id == cli[p].id && option == 'Y' && cli[p].estado == 1)
	    {
		    fp = fopen("src/clientes.txt","r+");
		    if(fp == NULL){
		        gotoxy(10,6);
		        printf("Error al abrir el archivo");
		        exit(1);
		    }
		    temp = fopen("src/temporal.txt","w+");
		    if(temp == NULL) {
		        gotoxy(10,6);
		        printf("Error al abrir el archivo");
		        exit(1);
	    	}
			displayCliente(p, 5);
			gotoxy(10,12);
	    	cli[p].estado = 0; // El estado queda desactivo y ya no se mostrar� o tomar� en cuenta
			printf("%cEst%cs seguro que quiere eliminar el cliente con la ID `%i`? (Y / N): ", 168, 160, id);
		    option = yesOrNo(1);
		 	if(option == 'Y')
				fwrite(&cli[p], sizeof(struct cliente), 1, temp); // Primero se anota la reci�n guardada
			while (fread(&cli[i], sizeof(struct cliente), 1, fp) == 1) {
			    /*printf("\n%i", ent[i].id);
			    getch();
			    printf("\n%i", ent[p].id);
			    getch();*/
				if (cli[i].id != cli[p].id) { // Condici�n para que no se repita la misma id despu�s del cambio
	    			fwrite(&cli[i], sizeof(struct cliente), 1, temp);
	    		}
	    		i++;
	    	}
	    	fclose(fp);
			fclose(temp);
			gotoxy(10,15);
			if(option == 'Y')
			{
				remove("src/clientes.txt");
			    rename("src/temporal.txt", "src/clientes.txt");
		    	printf("%cCliente eliminado exitosamente!", 173);
			}
			else {
				printf("No se hizo ning%cn cambio", 163);
				remove("src/temporal.txt");
			}
	        getch();
            return;
		}
		system("cls");
		gotoxy(10,4);
		printf("La ID `%i` no se encuentra registrada o ya ha sido eliminada.", id);
		gotoxy(10,5);
		printf("%cDesea buscar otro cliente para eliminar? (Y / N): ", 168, 164);
		option = yesOrNo(1);
		if (option == 'N')
			return;
	} while (option == 'Y');
}

void displayCliente(int p, int y){
	// y representa la parte de Gotoxy para que baje
	gotoxy(10,y);
	printf("ID   P. Nombre    S. Nombre   Apellido P.   Apellido M.  Tel%cfono     Direcci%cn        Turno       Estado", 130, 162);
	gotoxy(10,y+1);
	printf("_____________________________________________________________________________________________________________");
	gotoxy(10, y+3);
	printf("%-5d%-13s%-12s%-14s%-13s%-13s%-17s%-12s%d", cli[p].id, cli[p].primerNombre, cli[p].segundoNombre, cli[p].apellidoPaterno, cli[p].apellidoMaterno, cli[p].telefono, cli[p].direccion, cli[p].turno, cli[p].estado);
}

void addServicios(int idEntrenador) {
	
}

void leerArchivoEntrenador(){
    FILE *pEnt;
    int i = 0;
    pEnt = fopen("src/entrenadores.txt","a+");
    if(pEnt == NULL){
        printf("ARCHIVO NO CREADO/ABIERTO");
        exit(1);
    }
    else {
        while(fread(&ent[i], sizeof(struct entrenador), 1, pEnt) == 1){
        	// Leer
        	i++;
        }
    }
    fclose(pEnt);
}

void guardarArchivoEntrenador(struct entrenador ent[]) { // AKA la poderosa acomoda n�meros
	FILE *fp; // En vez de guardar el archivo en s�, acomodar� las ID por orden num�rico
	FILE *temp;
	int i = 0, j = 0, k = 0, izq = 0, der = 0, temporal = 0;
    fp = fopen("src/entrenadores.txt","r+");
    if(fp == NULL){
        printf("ARCHIVO NO CREADO/ABIERTO");
        exit(1);
    }
    temp = fopen("src/temporal.txt","w+");
	if(temp == NULL) {
		printf("ARCHIVO NO CREADO/ABIERTO");
		getch();
	}
	while(fread(&ent[i], sizeof(struct entrenador), 1, fp) == 1){
    	i++; // para sacar la longitud de entrenadores
	}
	
	int arr[i];
	
	for (j = 0; i > j; j++) { // Asignar los valores desordenados a un arreglo
    	arr[j] = ent[j].id;
    	/*printf("%i", arr[j]);
    	getch();*/
	}
	// Aqu� se acomodan los n�meros del arreglo de manera num�rica
    for (k = 0; k < i; k++) { // i representa el tope
    	for (izq = 0, der = 1; der < i; izq++, der++) {
    		if (arr[izq] > arr[der]) {
    			temporal = arr[der];
    			arr[der] = arr[izq];
    			arr[izq] = temporal;
			}
		}
	}
	/*printf("%i", arr[11]);
	getch();*/
	
	// Aqu� ya se imprimen las variables en orden num�rico en un archivo temporal
	// que se termina reenombrando como entrenador
	
	for (j = 0; j < i; j++) {
		for (k = 0; k < i; k++) {	
			if (arr[j] == ent[k].id) {
				fwrite(&ent[k], sizeof(struct entrenador), 1, temp);
				break;
			}
		}
	}
	fclose(fp);
	fclose(temp);
	remove("src/entrenadores.txt");
	rename("src/temporal.txt", "src/entrenadores.txt");
}

int idRepetida(struct entrenador ent[], int idWanted) { 
	// Devolver� un 1 si la ID es repetida
	FILE *pEnt;
	int i = 0, j = 0, k = 0;
    pEnt = fopen("src/entrenadores.txt","a+");
    if(pEnt == NULL){
        printf("ARCHIVO NO CREADO/ABIERTO");
        getch();
    }
    while(fread(&ent[i], sizeof(struct entrenador), 1, pEnt) == 1){
        i++;
    }
    // `i` Cantidad de IDs existentes
    for (j = 0; j < i; j++) {	
		if (idWanted == ent[j].id) {
			fclose(pEnt);
			return 1;
		}
	}
	fclose(pEnt);
	return 0;
}

int idRepetidaCli(struct cliente cli[], int idWanted){
	// Devolver� un 1 si la ID es repetida
	FILE *pCli;
	int i = 0, j = 0, k = 0;
    pCli = fopen("src/clientes.txt","a+");
    if(pCli == NULL){
        printf("ARCHIVO NO CREADO/ABIERTO");
        getch();
    }
    while(fread(&cli[i], sizeof(struct cliente), 1, pCli) == 1){
        i++;
    }
    // `i` Cantidad de IDs existentes
    for (j = 0; j < i; j++) {	
		if (idWanted == cli[j].id) {
			fclose(pCli);
			return 1;
		}	
	}
	fclose(pCli);
	return 0;
}

void leerArchivoCliente(){
	FILE *pCli;
    int i = 0;
    pCli = fopen("src/clientes.txt","a+");
    if(pCli == NULL){
        printf("ARCHIVO NO CREADO/ABIERTO");
        exit(1);
    }
    else {
        while(fread(&cli[i], sizeof(struct cliente), 1, pCli) == 1){
        	// Leer
        	i++;
        }
    }
    fclose(pCli);
}

void guardarArchivoCliente(struct cliente cli[]){
	FILE *fp; // En vez de guardar el archivo en s�, acomodar� las ID por orden num�rico
	FILE *temp;
	int i = 0, j = 0, k = 0, izq = 0, der = 0, temporal = 0;
    fp = fopen("src/clientes.txt","r+");
    if(fp == NULL){
        printf("ARCHIVO NO CREADO/ABIERTO");
        exit(1);
    }
    temp = fopen("src/temporal.txt","w+");
	if(temp == NULL) {
		printf("ARCHIVO NO CREADO/ABIERTO");
		getch();
	}
	while(fread(&cli[i], sizeof(struct cliente), 1, fp) == 1){
    	i++; // para sacar la longitud de entrenadores
	}
	
	int arr[i];
	
	for (j = 0; i > j; j++) { // Asignar los valores desordenados a un arreglo
    	arr[j] = cli[j].id;
    	/*printf("%i", arr[j]);
    	getch();*/
	}
	// Aqu� se acomodan los n�meros del arreglo de manera num�rica
    for (k = 0; k < i; k++) { // i representa el tope
    	for (izq = 0, der = 1; der < i; izq++, der++) {
    		if (arr[izq] > arr[der]) {
    			temporal = arr[der];
    			arr[der] = arr[izq];
    			arr[izq] = temporal;
			}
		}
	}
	/*printf("%i", arr[11]);
	getch();*/
	
	// Aqu� ya se imprimen las variables en orden num�rico en un archivo temporal
	// que se termina reenombrando como entrenador
	
	for (j = 0; j < i; j++) {
		for (k = 0; k < i; k++) {	
			if (arr[j] == cli[k].id) {
				fwrite(&cli[k], sizeof(struct cliente), 1, temp);
				break;
			}
		}
	}
	fclose(fp);
	fclose(temp);
	remove("src/clientes.txt");
	rename("src/temporal.txt", "src/clientes.txt");
}

long nument(int lon) {
	char car, cadena[lon+1]={' '};
	int x=0;
	do{
		car = getch();
		if(car >= 48 && car <= 57){
			printf("%c", car);
			cadena[x]=car;
			x++;
		}
		if (car == 48 && x == 1) {
			printf("\b \b");
			x--;
			cadena[x]=' ';
		}
		if(car==8 && x>0){
			printf("\b \b");
			x--;
			cadena[x]=' ';
		}
	}while((car != 13 || x == 0) && x < lon);
//	cadena[x]='\n';
	
	return atoi(cadena);
}

void valitext(int lon,char *pnom){
	int c=0, x=0;
    do{
		c=getch();
        if(c>=65 && c<=90 || c>=97 && c<=122 || c==32 || c == 130 || c >= 160 && c <= 165 || c == 181 || c == 144 || c == 214 || c == 224 || c == 233){
			printf("%c",c);
            *(pnom+x)=c;
            x++;
        }
        if(c==8 && x>0){
			x--;
		    printf("\b \b");
	        *(pnom+x)=' ';
        }
    }while(c!=13 && x<lon);
    *(pnom+x)= NULL;
}

void valiNum(char *pnom, int length){
	int c=0, x=0;
    do{
		c=getch();
        if(c>=48 && c<=57){
			printf("%c",c);
            *(pnom+x)=c;
            x++;
        }
        if(c==8 && x>0){
			x--;
		    printf("\b \b");
	        *(pnom+x)=' ';
        }
    }while(x<length);
    *(pnom+x)= NULL;
}

void valifec(char *pfecha){
	int dia=0, mes=0, anio=0, x=0, c=0, d=0, m=0, a=0, fec=0, bi=0;
	char diac[2], mesc[2], anioc[4];
	do{
		x=d=m=a=0;
		strcpy(diac,"  ");
		strcpy(mesc,"  ");
		strcpy(anioc,"    ");
		do{
			c=getch();
	    	if(c>=48 && c<=57){
				printf("%c",c);
    			if(x<2){
					diac[d]=c;
        			d++;
        		}
				else if (x<5){
					mesc[m]=c;
					m++;
				}
				else{
					anioc[a]=c;
					a++;
				}
				*(pfecha+x)=c;
    	    	x++;
	    	}
	    	if(x==2 || x==5){
				printf("/");
    	    	*(pfecha+x)='/';
        		x++;        
        	} 
			if(c==8 && x>0){
				x--;
	    		if(x==2){
					printf("\b\b  \b\b");
	    			*(pfecha+x)=' ';
	    			x--;
	    			*(pfecha+x)=' ';
	    			d--;
	    		}
	    		else if(x<2){
					printf("\b \b");
					*(pfecha+x)=' ';
					d--;
				}
	    		else if(x==5){
					printf("\b\b  \b\b");
	    			*(pfecha+x)=' ';
	    			x--;
					*(pfecha+x)=' ';
					m--;
	    		}
	    		else if(x<5){
					printf("\b \b");
					*(pfecha+x)=' ';
					m--;
				}
	    		else if(x>5){
					printf("\b \b");
	    			*(pfecha+x)=' ';
	    			a--;
	    		}
    		}
		}while(x<10);
		dia=atoi(diac);
		mes=atoi(mesc);
		anio=atoi(anioc);
		bi=0;
		if(anio%4==0 && (anio%100!=0 || anio%400==0))
			bi++;
		if(dia<=31 && (mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12) && anio>=1900 && anio<=2050)
			fec=1;
		else if(dia<=30 && (mes==4 || mes==6 || mes==9 || mes==11) && anio>=1900 && anio<=2050)
			fec=1;
		else if(dia<=28 && mes==2 && anio>=1900 && anio<=2050)
			fec=1;
		else if(dia==29 && mes==2 && anio>=1900 && anio<=2050 && bi==1)
			fec=1;
		else
			for(int y=1;y<=10;y++)
				printf("\b \b");
	}while(fec!=1);
}

char yesOrNo(int length) {
	char car, option;
	do {
		car = getch();
		option = toupper(car);
		switch (option) {
			case 89:
				printf("%c", option);
				return 'Y';
				break;
			case 78:
				printf("%c", option);
				return 'N';
				break;
			default:
				break;
		} 
	} while(option != 89 || option != 78);
}

int idPosition(struct entrenador ent[], int idWanted) {
	FILE *fp;
    fp = fopen("src/entrenadores.txt","r+");
    if(fp == NULL){
        printf("ARCHIVO NO CREADO/ABIERTO");
        exit(1);
    }
	int top = 0, i = 0;
	while(fread(&ent[top], sizeof(struct entrenador), 1, fp) == 1){
    	top++; // para sacar la longitud de entrenadores
	}
	for (i = 0; i < top; i++) {
		if (ent[i].id == idWanted) {
			fclose(fp);
			return i;
		}
	}
	fclose(fp);
	return NULL;
}

int idPositionCli(struct cliente cli[], int idWanted){
	FILE *fp;
    fp = fopen("src/clientes.txt","r+");
    if(fp == NULL){
        printf("ARCHIVO NO CREADO/ABIERTO");
        exit(1);
    }
	int top = 0, i = 0;
	while(fread(&cli[top], sizeof(struct cliente), 1, fp) == 1){
    	top++; // para sacar la longitud de entrenadores
	}
	for (i = 0; i < top; i++) {
		if (cli[i].id == idWanted) {
			fclose(fp);
			return i;
		}
	}
	fclose(fp);
	return NULL;
}

void gotoxy(int x,int y) {
        COORD c;
        c.X=x;
        c.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
