/* 
Hecho por:
Gonzalez Ramirez Jose Manuel
Qui Mora Angel Ernesto
Tirado Romero Juan Jose
*/

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

void gotoxy(int x,int y);
void menu();
void menuServicio();
void menuEntrenador();
void menuCliente();
void menuRegistro();

void addServicio();
void consultarServicio();
void consultarServicioGeneral();
void consultarServicioEspecifico();
void modificarServicio();
void altaBajaServicio();
void altaServicio(int id, int y);
void bajaServicio(int id, int y); // Eliminar, pero en baja
void displayServicio(int p, int y);
int idPositionSer(struct servicio ser[], int idWanted);
int idRepetidaSer(struct servicio ser[], int idWanted);
int idSiguienteSer(struct servicio ser[], int i);
void leerArchivoServicio();
void guardarArchivoServicio(struct servicio ser[]);

void addEntrenador();
void consultarEntrenador();
void consultarEntrenadorGeneral();
void consultarEntrenadorEspecifico();
void modificarEntrenador();
void altaBajaEntrenador();
void altaEntrenador(int id, int y);
void bajaEntrenador(int id, int y); // Eliminar, pero en baja
void displayEntrenador(int p, int y);
int idPositionEnt(struct entrenador ent[], int idWanted);
int idRepetidaEnt(struct entrenador ent[], int idWanted);
int idSiguienteEnt(struct entrenador ent[], int i);
void leerArchivoEntrenador();
void guardarArchivoEntrenador(struct entrenador ent[]);

void addCliente();
void consultarCliente();
void consultarClienteGeneral();
void consultarClienteEspecifico();
void modificarCliente();
void altaBajaCliente();
void altaCliente(int id, int y);
void bajaCliente(int id, int y);
void displayCliente(int p, int y);
int idPositionCli(struct cliente cli[], int idWanted);
int idRepetidaCli(struct cliente cli[], int idWanted);
int idSiguienteCli(struct cliente ent[], int i);
void leerArchivoCliente();
void guardarArchivoCliente(struct cliente cli[]);

void addRegistro(int idCliente);
void consultarRegistro();
void consultarRegistroGeneral();
void consultarRegistroEspecifico();
void modificarRegistro();
void altaBajaRegistro();
void altaRegistro(int id, int y);
void bajaRegistro(int id, int y);
void displayRegistro(int p, int y);
int idPositionReg(struct registro reg[], int idWanted);
int idRepetidaReg(struct registro reg[], int idWanted);
int idSiguienteReg(struct registro reg[], int i);
void leerArchivoRegistro();
void guardarArchivoRegistro(struct entrenador ent[]);

void desactivadorSerEnt(int idDesactivada, int y);
int desactivadorEntCli(int idDesactivada, int y);
int desactivadorEntReg(int idDesactivada, int y);
int desactivadorCliReg(int idDesactivada, int y);

char yesOrNo(int length);
char autoOrManual(int length);
long nument(int lon);
void valitext(int lon,char *pnom);
void valiDireccion(int lon, char *pnom);
void valiDescripcion(int lon, char *pnom);
void valiTurno(int lon, char *pnom);
void valifec(char *pfecha);
void valiTelefono(char *pnom, int length);

// Un negocio primero necesita algo que ofrecer (SERVICIOS), en segundo lugar, empleados (ENTRENADORES),
// y finalmentem, un negocio necesita clientes para mantenerse a flote, y los CLIENTES necesitan
// un tipo de registro o suscripción para estar activos o estar inactivos temporalmente (REGISTRO). FIN
// ---------------------------------------------------------------------------------------------------------

// Nota importante con el estado:
// if estado de servicio conectado a entrenador es inactivo, entonces, los entrenadores relacionados serán inactivos también,
// pero si se reactiva, se activarán los entrenadores relacionados. FIN
// if estado de entrenadores es inactivo, entonces, los clientes relacionados buscarán a uno con sus mismas capacidades, de otro modo,
// se mantendrán inactivos hasta que se les asigne uno nuevo. FIN

// Otra nota: Tiene que existir servicios para haber entrenadores
// Si no hay servicios, entonces, te pedirá añadirlos. FIN

struct servicio {
	int id;
	char nombre[16];
	char especialidadReq[13]; // Especialidad requerida para llevar a cabo el servicio
	char descripcion[51]; // Descripción del servicio
	char estado[9]; // Activo e inactivo
} ser[10];

// Cuando se añada un entrenador o cliente estos estarán por defecto en inactivo,
// pero te preguntará si los quieres dar de alta y llamará a su respectiva función si option = 'Y'

struct entrenador {
	int id;
	char primerNombre[11];
	char segundoNombre[11];
	char apellidoMaterno[11];
	char apellidoPaterno[11];
	char telefono[11];
	
	// <--- Estas se rellenarán una vez que se dé de alta, antes de serán NULL --->
	char especialidad[13]; // Si no coincide con una especialidad de servicios pregunta para reiniciar el addEntrenador y display de especialidades disponibles
	char turno[11]; // if mixto, lo cuenta como valido para matutino, vespertino y nocturno
	int idServicio; // new || 
	// <----   ----------   ----> Esto primero es más relevante en un entrenador
	
	char estado[9];		// 'Inactivo' por defecto, pero te pedirá darlo de alta
} ent[10]; // Usaremos las 3 primeras letras para todas las estructuras

// Cuando se añada un entrenador o cliente estos estarán por defecto en inactivo,
// pero te preguntará si los quieres dar de alta y llamará a su respectiva función si option = 'Y'

struct cliente {
	int id;
	char primerNombre[11];
	char segundoNombre[11];
	char apellidoMaterno[11];
	char apellidoPaterno[11];
	char telefono[11];
	char direccion[21];
	
	// <--- Estas se rellenarán una vez que se dé de alta, antes de serán NULL --->
	char especialidadBus[13]; // Especialidad buscada || Si no coincide con una especialidad, te mostrará los servicios disponibles y te preguntará si quieres estar con otro servicio
	char turno[11]; // ---------------------- Turno	|| Modificable solamente en registro 	|| NULL por defecto
	int idEntrenador;	// new || Sugiere iDs de entrenadores que coincidan con tanto turno como especialidad, si no hay, te dice que no hay entrenadores con
						// lo solicitado, pero sugiere registrarse, pero con su estado inactivo para tenerlo guardado en un futuro que se necesite. FIN
	// <----   ----------   ----> Esto primero es más relevante en un entrenador
	
	char estado[9]; // Activo e inactivo 	|| 'Inactivo' por defecto, pero te pedirá darlo de alta
} cli[10];

// Registro es donde se dará de alta el cliente  || En este solamente se podrán modificar 

struct registro {
	int id; // Va a tomar la misma ID que la de cliente o de entrenador
	char fechaRegistro[11];
	char ultimoRegistro[11]; // Cuando se dé se podrá asignar una fecha de última suscripción a actividad
	// Mientras turno 
} entReg[10], cliReg[10]; // registro_ent.txt || registro_cli.txt

int main() {
//	system("COLOR C1");
	menu();
	return 0;
}

// <=== MENÚS ===>

void menu() {
	int option = 0;
	
	do {
		system("cls");
		gotoxy(40, 5);
		printf("<====     Men%c principal     ====>", 163);
		gotoxy(40, 8);
		printf("1. Men%c Servicios", 163);
		gotoxy(40, 9);
		printf("2. Men%c Entrenadores", 163);
		gotoxy(40, 10);
		printf("3. Men%c Clientes", 163);
		gotoxy(40, 11);
		printf("4. Men%c Registro", 163);
		gotoxy(40, 12);
		printf("5. Salir");
		
		gotoxy(44, 15);
		printf("> > Elige una opci%cn: ", 162);
		option = nument(1);
		
		switch (option) {
			case 1:
				menuServicio();
				break;
			case 2:
				menuEntrenador();
				break;
			case 3:
				menuCliente();
				break;
			case 4:
				menuRegistro();
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

void menuServicio() {
	int option = 0;
	
	do {
		system("cls");
		gotoxy(40, 5);
		printf("======   Men%c Servicio   ======", 163);
		gotoxy(40, 8);
		printf("1. Agregar");
		gotoxy(40, 9);
		printf("2. Consultar");
		gotoxy(40, 10);
		printf("3. Modificar");
		gotoxy(40, 11);
		printf("4. Alta / Baja");
		gotoxy(40, 12);
		printf("5. Regresar");
		
		gotoxy(44, 15);
		printf("> > Elige una opci%cn: ", 162);
		option = nument(1);
		leerArchivoServicio();
		switch (option) {
			case 1:
				addServicio();
				break;
			case 2:
				consultarServicio();
				break;
			case 3:
				modificarServicio();
				break;
			case 4:
				altaBajaServicio();
				break;
			case 5:
				break;
			default:
				system("cls");
				printf("Opci%cn inv%clida. Elige de nuevo.", 162, 160);
				Sleep(300);
				break;
		}
		guardarArchivoServicio(ser);
	} while (option != 5);
}

void menuEntrenador() {
	int option = 0;
	
	do {
		system("cls");
		gotoxy(40, 5);
		printf("======   Men%c Entrenador   ======", 163);
		gotoxy(40, 8);
		printf("1. Agregar");
		gotoxy(40, 9);
		printf("2. Consultar");
		gotoxy(40, 10);
		printf("3. Modificar");
		gotoxy(40, 11);
		printf("4. Alta / Baja");
		gotoxy(40, 12);
		printf("5. Regresar");
		
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
				altaBajaEntrenador();
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

void menuCliente() {
	int option = 0;
	
	do {
		system("cls");
		gotoxy(40, 5);
		printf("<====     Men%c Cliente     ====>", 163);
		gotoxy(40, 8);
		printf("1. Agregar");
		gotoxy(40, 9);
		printf("2. Consultar");
		gotoxy(40, 10);
		printf("3. Modificar");
		gotoxy(40, 11);
		printf("4. Alta / Baja");
		gotoxy(40, 12);
		printf("5. Regresar");
		
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
				altaBajaCliente();
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

void menuRegistro() {
	
}


// <=== SERVICIOS ===>
// <=== SERVICIOS ===>
// <=== SERVICIOS ===>


void addServicio() {
	FILE *fp;
    char option = 'Y', option2;
    int i = 0, j = 0, p = 0;
    while(option == 'Y')
    {
    	i = 0, j = 0;
    	fp = fopen("src/servicios.txt", "a+");
	    if(fp == NULL){
	    	system("cls");
	        gotoxy(10,5);
	        printf("Error abriendo el archivo");
	        exit(1);
	    }
    	system("cls");
	    while(fread(&ser[j], sizeof(struct servicio), 1, fp) == 1){
	    	if (strcmp(ser[j].estado, "Activo") == 0) { // Solo se imprimen los activos
	    		i++;
	    	}
	    	j++;
		}
    	if (i < 10)
    	{
	    	gotoxy(15,2);
	        printf("<====    A%cadir Servicio    ====>", 164);
	        gotoxy(15,4);
	        printf("Inserta los detalles del servicio");
	        gotoxy(15,6);
	        printf("%cDesea a%cdir la ID autom%cticamente o manualmente? (A / M): ", 168, 164, 160);
	        option2 = autoOrManual(1);
	        gotoxy(15,8);
	        if (option2 == 'A') {
	        	printf("ID: %i", idSiguienteSer(ser, 0));
				ser[j].id = idSiguienteSer(ser, 0);
			}
			if (option2 == 'M') {	
		        printf("ID: ");
		        ser[j].id = nument(3);
			}
	        if (idRepetidaSer(ser, ser[j].id) == 1) { // Si la ID es repetida, devuelve 1
	        	system("cls");
	        	gotoxy(10, 5);
	        	p = idPositionSer(ser, ser[j].id);
				printf("La id `%i` es repetida: ", ser[p].id);
				displayServicio(p, 8);
				gotoxy(10, 15);
		        printf("%cDesea intentar con otra ID? (Y / N): ", 168, 164);
		        option = yesOrNo(1);
		        fclose(fp);
		        if (option == 'N')
		        	return;
				guardarArchivoServicio(ser); // Para ordenar las IDs
		        gotoxy(10, 17);
		        printf("Recomendaci%cn: La id `%i` es la pr%cxima ID disponible", 162, idSiguienteSer(ser, 0), 162);
		        getch();
		        if (option == 'Y') {
		        	addServicio();
		        	return;
				}
				return;
			}
			option = 'N';
			while (1) {
				system("cls");
				gotoxy(15,3);
		        printf("<====    A%cadir Servicio    ====>", 164);
		        gotoxy(15,5);
		        printf("Inserta los detalles del servicio");
		        gotoxy(15,7);
		        printf("ID: %i", ser[j].id);
				gotoxy(15,8);
		        printf("Nombre del servicio: ");
		        valitext(15, ser[j].nombre);
				gotoxy(15,9);
		        printf("Descripci%cn del servicio: ", 162);
		        valitext(50, ser[j].descripcion);
		        gotoxy(15,12);
	        	printf("%cEst%cn bien los datos? (Y / N): ", 168, 160);
	        	option = yesOrNo(1);
	        	if (option == 'Y')
	        		break;
			}
	        
	        strcpy(ser[j].estado, "Inactivo"); // Son por defecto de baja
	        strcpy(ser[j].especialidadReq, "S/N");
	        fwrite(&ser[j], sizeof(struct servicio), 1, fp);
	        gotoxy(15,15);
			printf("%cServicio a%cadido exitosamente!", 173, 164);
	        getch();
	        gotoxy(15,15);
	        printf("%cDesea darlo de alta? (Y / N): ", 168);
	        option = yesOrNo(1);
	        if (option == 'Y') {
	        	fclose(fp);
	        	altaServicio(ser[j].id, 0);
			}
			gotoxy(15,15);
			if(option == 'Y') {
				system("cls");
				gotoxy(10, 5);
			}
	        printf("%cDesea a%cadir otro servicio? (Y / N): ", 168, 164);
	        option = yesOrNo(1);
	        fclose(fp);
		}
		else {
			gotoxy(10, 5);
			printf("No hay espacio de almacentamiento para m%cs servicios. :(", 160);
			fclose(fp);
			getch();
			return;
		}
    }
    fclose(fp);
}

void consultarServicio() {
	int option = 0;
	
	do {
		system("cls");
		gotoxy(40, 5);
		printf("<====    Consulta Servicio    ====>");
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
				consultarServicioGeneral();
				break;
			case 2:
				consultarServicioEspecifico();
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

void consultarServicioGeneral() {
	FILE *fp;
    int i = 0, j;
    char option;
    system("cls");
    gotoxy(36,2);
    printf("<====    Consulta General Servicios    ====>");
    gotoxy(10,5);
	printf("ID   Nombre de Servicio  Especialidad   Estado    Descripci%cn                            ", 162);
    gotoxy(10,6);
	printf("____________________________________________________________________________________________________");
    fp = fopen("src/servicios.txt","r+");
    if(fp == NULL){
        gotoxy(10,8);
        printf("Error abriendo el archivo");
        exit(1);
    }
    j=8;
    while(fread(&ser[i], sizeof(struct servicio), 1, fp) == 1){
    	if (strcmp(ser[i].estado, "Activo") == 0) { // Solo se imprimen los activos
    		gotoxy(10, j);
	        printf("%-5d%-20s%-15s%-10s%s", ser[i].id, ser[i].nombre, ser[i].especialidadReq, ser[i].estado, ser[i].descripcion);
	        i++;
	        j++;
		}
    }
    fclose(fp);
    getch();
    gotoxy (10, j+1);
    printf("%cDesea ver los servicios inactivos tambi%cn? (Y / N): ", 168, 130);
	option = yesOrNo(1);
	if (option == 'Y') {
		fp = fopen("src/servicios.txt","r+");
	    if(fp == NULL){
	        gotoxy(10,8);
	        printf("Error abriendo el archivo");
	        exit(1);
	    }
		i = 0, j = 8;
		system("cls");
	    gotoxy(36,2);
	    printf("<====    Consulta General Servicios    ====>");
	    gotoxy(10,5);
	    printf("ID   Nombre de Servicio  Especialidad   Estado    Descripci%cn                            ", 162);
	    gotoxy(10,6);
	    printf("____________________________________________________________________________________________________");
		while(fread(&ser[i], sizeof(struct servicio), 1, fp) == 1){
	    	if (strcmp(ser[i].estado, "Inactivo") == 0) { // Solo se imprimen los activos
	    		gotoxy(10, j);
	        	printf("%-5d%-20s%-15s%-10s%s", ser[i].id, ser[i].nombre, ser[i].especialidadReq, ser[i].estado, ser[i].descripcion);
		        i++;
		        j++;
			}
    	}
	}
    fclose(fp);
    gotoxy(10, j+3);
    printf("Presiona cualquier tecla para salir");
    getch();
    
}

void consultarServicioEspecifico() {
	int cod;
	int p; // p = position
	int i = 0;
	int condition = 1;
	char option='Y';
	FILE *fp;
	p = idPositionSer(ser, cod); 
	while(option == 'Y'){
		system("cls");
		gotoxy(38,2);
	    printf("<====     Consulta Espec%cfica de Servicio     ====>", 161);
	    gotoxy(38,5);
		printf("ID del Servicio: ");
		cod = nument(3);
		fp = fopen("src/servicios.txt","r+");
		while(!feof(fp)){ 
			fread(&ser[i], sizeof(struct servicio), 1, fp);
			if(cod == ser[i].id){ // Lo imprime aunque estï¿½ inactivo
				system("cls");
				gotoxy(38,2);
			    printf("<====     Consulta Espec%cfica Servicio     ====>", 161);
			    displayServicio(i, 5);
				getch();
		        gotoxy(10, 12);
				printf("%cDesea buscar otro servicio? (Y / N): ", 168, 164);
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
			printf("%cDesea buscar otro servicio para consultar? (Y / N): ", 168, 164);
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

void modificarServicio() {
	FILE *fp, *temp;
    char option = 'Y';
	int idServicio; // Esto era char antes, daba 89 en vez de 344 LMAO
	int i = 0, p = 0;
	do {
		system("cls");
		gotoxy(10,3);
	    printf("<====    Modificar Servicio    ====>");
	    gotoxy(10,5);
	    printf("Inserta la ID de servicio a modificar: ");
	    idServicio = nument(3);
	    p = idPositionSer(ser, idServicio);
	    if (ser[p].id == idServicio && strcmp(ser[p].estado, "Activo") == 0)
	    {
	    	displayServicio(p, 8);
		    gotoxy(10,14);
			printf("%cEst%c seguro que quiere editar el servicio con la ID `%i`? (Y / N): ", 168, 160, idServicio);
		    option = yesOrNo(1);
		}
		while(idServicio == ser[p].id && strcmp(ser[p].estado, "Activo") == 0) // Puedes modificar mientras la ID coincida y el servicio se encuentre activo
	    {
	    	system("cls");
	    	if (option == 'N')
				return;
		    fp = fopen("src/servicios.txt","r+");
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
        	displayServicio(p, 4);
            gotoxy(10,10);
	        printf("Nombre del servicio: ");
	        valitext(15, ser[p].nombre);
	        gotoxy(10,11);
	        printf("Descripci%cn del servicio: ", 162);
	        valitext(50, ser[p].descripcion);
	        option = yesOrNo(1);
			gotoxy(10,19);
			// Primero guarda la variable cambiada y la mueve al principio,
			// entonces, anota el resto menos la cambiada.
			if(option == 'Y')
				fwrite(&ser[p], sizeof(struct servicio), 1, temp); // Primero se anota la reciï¿½n guardada
			while (fread(&ser[i], sizeof(struct servicio), 1, fp) == 1) {
				if (ser[i].id != ser[p].id) { // Condiciï¿½n para que no se repita la misma id despuï¿½s del cambio
	    			fwrite(&ser[i], sizeof(struct servicio), 1, temp);
				}
				i++;
			}
	    	fclose(fp);
			fclose(temp);
			if(option == 'Y')
			{
				remove("src/servicios.txt");
			    rename("src/temporal.txt", "src/servicios.txt");
		    	printf("%cServicio modificado exitosamente!", 173);
			}
			else {
				printf("No se hizo ning%cn cambio.", 163);
				remove("src/temporal.txt");
			}
	        getch();
            return;
	    }
	    
    	if (option == 'Y')
    	{
    		
			system("cls");
			gotoxy(10,4);
			printf("%i", p);
    		if (strcmp(ser[p].estado, "Inactivo") == 0)
				printf("La ID `%i` necesita estar dada de alta para ser modificada.", idServicio);
			else
				printf("La ID `%i` no est%c registrada.", idServicio, 160);
			gotoxy(10,7);
			printf("%cDesea buscar otro servicio para modificar? (Y / N): ", 168, 164);
			option = yesOrNo(1);
			if (option == 'N')
				return;
		}
	}while (option == 'Y');
}

void altaBajaServicio() {
	int option = 0;
	
	do {
		system("cls");
		gotoxy(40, 5);
		printf("<====    Alta / Baja Servicio    ====>");
		gotoxy(40, 8);
		printf("1. Alta");
		gotoxy(40, 9);
		printf("2. Baja", 161);
		gotoxy(40, 10);
		printf("3. Regresar");
		gotoxy(44, 15);
		printf("> > Elige una opci%cn: ", 162);
		option = nument(1);
		leerArchivoServicio();
		switch (option) {
			case 1:
				altaServicio(0, 0);
				break;
			case 2:
				bajaServicio(0, 0);
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
		guardarArchivoServicio(ser);
	} while (option != 3);	
}

void altaServicio(int id, int y) {
	FILE *fp,*temp;
    int i = 0, j = 0, p = 0;
	char option = 'Y';
    while(option == 'Y')
    {
    	i = 0, j = 0;
    	fp = fopen("src/servicios.txt", "r+");
	    if(fp == NULL){
	    	system("cls");
	        gotoxy(10,5);
	        printf("Error abriendo el archivo");
	        exit(1);
	    }
	    while(fread(&ser[j], sizeof(struct servicio), 1, fp) == 1){
	    	if (strcmp(ser[j].estado, "Activo") == 0) { // Solo se imprimen los activos
	    		i++;
	    	}
	    	j++;
		}
		fclose(fp);
	    system("cls");
	    if (i < 10)
	    {
			gotoxy(10,y+3);
		    printf("<====    Dar de Alta Servicio    ====>");
		    gotoxy(10,y+5);
		    if (id == 0) {	
			    printf("Insertar la ID a dar de alta: ");
			    id = nument(3);
			}
		    p = idPositionSer(ser, id);
		    
		    while (id == ser[p].id && option == 'Y' && strcmp(ser[p].estado, "Inactivo") == 0)
		    {
		    	fp = fopen("src/servicios.txt", "r+");
			    if(fp == NULL){
			    	system("cls");
			        gotoxy(10,5);
			        printf("Error abriendo el archivo");
			        exit(1);
			    }
			    temp = fopen("src/temporal.txt","w+");
			    if(temp == NULL) {
			        gotoxy(10,y+6);
			        printf("Error al abrir el archivo");
			        exit(1);
		    	}
				displayServicio(p, y+8);
		    	strcpy(ser[p].estado, "Activo"); // El estado queda desactivo y ya no se mostrarï¿½ o tomarï¿½ en cuenta
				gotoxy(10,y+14);
				printf("Especialidad: ");
		        valitext(12, ser[p].especialidadReq);
				gotoxy(10,y+16);
				printf("%cGuardar los cambios y dar de alta el servicio con la ID `%i`? (Y / N): ", 168, id);
			    option = yesOrNo(1);
			    i = 0; // Se pone para resetear el conteo donde se añaden los servicios
			 	if(option == 'Y')
					fwrite(&ser[p], sizeof(struct servicio), 1, temp); // Primero se anota la reciï¿½n guardada
				while (fread(&ser[i], sizeof(struct servicio), 1, fp) == 1) {
					if (ser[i].id != ser[p].id) { // Condiciï¿½n para que no se repita la misma id despuï¿½s del cambio
		    			fwrite(&ser[i], sizeof(struct servicio), 1, temp);
		    		}
		    		i++;
		    	}
		    	fclose(fp);
				fclose(temp);
				gotoxy(10,y+19);
				if(option == 'Y')
				{
					remove("src/servicios.txt");
				    rename("src/temporal.txt", "src/servicios.txt");
			    	printf("%cServicio dado de alta exitosamente!", 173);
				}
				else {
					printf("No se dio de alta el servicio con la ID `%i`.", id);
					remove("src/temporal.txt");
				}
		        getch();
	            return;
			}
			system("cls");
			gotoxy(10,4);
			printf("La ID `%i` no est%ca registrado o ya se dio de alta.", id, 160);
			gotoxy(10,5);
			printf("%cDesea buscar otro servicio para dar de alta? (Y / N): ", 168, 164);
			option = yesOrNo(1);
			if (option == 'N')
				return;	
		}
		else {
			system("cls");
			gotoxy(10, 5);
			printf("No hay espacio de almacentamiento para dar m%cs servicios de alta. :(", 160);
			getch();
			return;
		}
		
	}
}

void bajaServicio(int id, int y) {	// Eliminar, pero en baja
	int i, p; // P = position
	char option = 'Y';
    FILE *fp,*temp, *pEnt;
    do {
	    system("cls");
		gotoxy(10,y+3);
		
	    printf("<====    Dar de Baja Servicio    ====>");
	    gotoxy(10,y+5);
	    if (id == NULL) {	
		    printf("Insertar la ID a dar de baja: ");
		    id = nument(3);
		}
	    p = idPositionSer(ser, id);
	    
	    while (id == ser[p].id && option == 'Y' && strcmp(ser[p].estado, "Activo") == 0)
	    {
		    fp = fopen("src/servicios.txt","r+");
		    if(fp == NULL){
		        gotoxy(10,y+6);
		        printf("Error al abrir el archivo");
		        exit(1);
		    }
		    temp = fopen("src/temporal.txt","w+");
		    if(temp == NULL) {
		        gotoxy(10,y+6);
		        printf("Error al abrir el archivo");
		        exit(1);
	    	}
			displayServicio(p, y+8);
			strcpy(ser[p].especialidadReq, "S/N");
	    	strcpy(ser[p].estado, "Inactivo"); // El estado queda desactivo y ya no se mostrarï¿½ o tomarï¿½ en cuenta
	    	gotoxy(10,y+14);
	    	printf("Advertencia: Si se da de baja el servicio, se dar%c de baja a los entrenadores relacionados al servicio.", 160);
	    	getch();
			gotoxy(10,y+16);
			printf("%cEst%cs seguro que quiere dar de baja el servicio con la ID `%i`? (Y / N): ", 168, 160, id);
		    option = yesOrNo(1);
		 	if(option == 'Y')
				fwrite(&ser[p], sizeof(struct servicio), 1, temp); // Primero se anota la reciï¿½n guardada
			while (fread(&ser[i], sizeof(struct servicio), 1, fp) == 1) {
				if (ser[i].id != ser[p].id) { // Condiciï¿½n para que no se repita la misma id despuï¿½s del cambio
	    			fwrite(&ser[i], sizeof(struct servicio), 1, temp);
	    		}
	    		i++;
	    	}
	    	fclose(fp);
			fclose(temp);
			gotoxy(10,y+19);
			if(option == 'Y')
			{
				remove("src/servicios.txt");
			    rename("src/temporal.txt", "src/servicios.txt");
		    	printf("%cServicio `%i` dado de baja exitosamente!", 173, id);
		    	getch();
		    	desactivadorSerEnt(ser[p].id, y+20);
			}
			else {
				printf("No se dio de baja el servicio con la ID `%i`.", id);
				remove("src/temporal.txt");
	        	getch();
			}
            return;
		}
		system("cls");
		gotoxy(10,4);
		printf("La ID `%i` no se encuentra registrada o ya ha sido dado de baja.", id);
		gotoxy(10,5);
		printf("%cDesea buscar otro servicio para dar de baja? (Y / N): ", 168, 164);
		option = yesOrNo(1);
		if (option == 'N')
			return;
	} while (option == 'Y');
}

void displayServicio(int p, int y) {
	// y representa la parte de Gotoxy para que baje
	gotoxy(10,y);
	printf("ID   Nombre de Servicio  Especialidad   Estado    Descripci%cn                            ", 162);
	gotoxy(10,y+1);
	printf("____________________________________________________________________________________________________");
	gotoxy(10, y+3);
	printf("%-5d%-20s%-15s%-10s%s", ser[p].id, ser[p].nombre, ser[p].especialidadReq, ser[p].estado, ser[p].descripcion);
}

int idPositionSer(struct servicio ser[], int idWanted) {
	FILE *fp;
    fp = fopen("src/servicios.txt","r+");
    if(fp == NULL){
        printf("ARCHIVO NO CREADO/ABIERTO");
        exit(1);
    }
	int top = 0, i = 0;
	while(fread(&ser[top], sizeof(struct servicio), 1, fp) == 1) {
    	top++; // para sacar la longitud de servicios
	}
	for (i = 0; i < top; i++) {
		if (ser[i].id == idWanted) {
			fclose(fp);
			return i;
		}
	}
	fclose(fp);
	return NULL;
}

int idRepetidaSer(struct servicio ser[], int idWanted) {
	// Devolverï¿½ un 1 si la ID es repetida
	FILE *pSer;
	int i = 0, j = 0, k = 0;
    pSer = fopen("src/servicios.txt","r+");
    if(pSer == NULL){
        printf("ARCHIVO NO CREADO/ABIERTO");
        getch();
    }
    while(fread(&ser[i], sizeof(struct servicio), 1, pSer) == 1){
        i++;
    }
    // `i` Cantidad de IDs existentes
    for (j = 0; j < i; j++) {	
		if (idWanted == ser[j].id) {
			fclose(pSer);
			return 1;
		}
	}
	fclose(pSer);
	return 0;
}

int idSiguienteSer(struct servicio ser[], int i) {
	if ((ser[i].id)+1 != (ser[i+1].id))  // Se actualiza por si se añadió un nuevo valor
		leerArchivoServicio(); // Sin esto repite el mismo núemero dos veces seguidas el mismo n
	if ((ser[i].id)+1 == (ser[i+1].id))
		return idSiguienteSer(ser, i+1);
	return ser[i].id + 1;
}

void leerArchivoServicio() {
	FILE *pSer;
    int i = 0;
    pSer = fopen("src/servicios.txt","r+");
    if(pSer == NULL){
        printf("ARCHIVO NO CREADO/ABIERTO");
        exit(1);
    }
    else {
        while(fread(&ser[i], sizeof(struct servicio), 1, pSer) == 1){
        	// Leer
        	i++;
        }
    }
    fclose(pSer);
}

void guardarArchivoServicio(struct servicio ser[]) {
	FILE *fp; // En vez de guardar el archivo en sï¿½, acomodarï¿½ las ID por orden numï¿½rico
	FILE *temp;
	int i = 0, j = 0, k = 0, izq = 0, der = 0, temporal = 0;
    fp = fopen("src/servicios.txt","r+");
    if(fp == NULL){
        printf("ARCHIVO NO CREADO/ABIERTO");
        exit(1);
    }
    temp = fopen("src/temporal.txt","w+");
	if(temp == NULL) {
		printf("ARCHIVO NO CREADO/ABIERTO");
		getch();
	}
	while(fread(&ser[i], sizeof(struct servicio), 1, fp) == 1){
    	i++; // para sacar la longitud de servicios
	}
	
	int arr[i];
	
	for (j = 0; i > j; j++) { // Asignar los valores desordenados a un arreglo
    	arr[j] = ser[j].id;
    	/*printf("%i", arr[j]);
    	getch();*/
	}
	// Aquï¿½ se acomodan los nï¿½meros del arreglo de manera numï¿½rica
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
	
	// Aquï¿½ ya se imprimen las variables en orden numï¿½rico en un archivo temporal
	// que se termina reenombrando como servicios
	
	for (j = 0; j < i; j++) {
		for (k = 0; k < i; k++) {	
			if (arr[j] == ser[k].id) {
				fwrite(&ser[k], sizeof(struct servicio), 1, temp);
				break;
			}
		}
	}
	fclose(fp);
	fclose(temp);
	remove("src/servicios.txt");
	rename("src/temporal.txt", "src/servicios.txt");
}


// <=== ENTRENADORES ===>
// <=== ENTRENADORES ===>
// <=== ENTRENADORES ===>


void addEntrenador() {
	FILE *fp;
    char option = 'Y', option2;
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
	    	if (strcmp(ent[j].estado, "Activo") == 0) { // Solo se imprimen los activos
	    		i++;
	    	}
	    	j++;
		}
    	if (i < 10)
    	{
	    	gotoxy(15,2);
	        printf("<====    A%cadir Entrenador    ====>", 164);
	        gotoxy(15,4);
	        printf("Inserta los detalles del entrenador");
	        gotoxy(15,6);
	        printf("%cDesea a%cdir la ID autom%cticamente o manualmente? (A / M): ", 168, 164, 160);
	        option2 = autoOrManual(1);
	        gotoxy(15,8);
	        if (option2 == 'A') {
	        	printf("ID: %i", idSiguienteEnt(ent, 0));
				ent[j].id = idSiguienteEnt(ent, 0);
			}
			if (option2 == 'M') {	
		        printf("ID: ");
		        ent[j].id = nument(3);
			}
	        if (idRepetidaEnt(ent, ent[j].id) == 1) { // Si la ID es repetida, devuelve 1
	        	system("cls");
	        	gotoxy(10, 5);
	        	p = idPositionEnt(ent, ent[j].id);
				printf("La id `%i` es repetida: ", ent[p].id);
				displayEntrenador(p, 8);
				gotoxy(10, 15);
		        printf("%cDesea intentar con otra ID? (Y / N): ", 168, 164);
		        option = yesOrNo(1);
		        fclose(fp);
		        if (option == 'N')
		        	return;
				guardarArchivoEntrenador(ent); // Para ordenar las IDs
		        gotoxy(10, 17);
		        printf("Recomendaci%cn: La id `%i` es la pr%cxima ID disponible", 162, idSiguienteEnt(ent, 0), 162);
		        getch();
		        if (option == 'Y') {
		        	addEntrenador();
		        	return;
				}
				return;
			}
			option = 'N';
			while (1) {
				system("cls");
				gotoxy(15,3);
		        printf("<====    A%cadir Entrenador    ====>", 164);
		        gotoxy(15,5);
		        printf("Inserta los detalles del entrenador");
		        gotoxy(15,7);
		        printf("ID: %i", ent[j].id);
				gotoxy(15,8);
		        printf("Primer nombre: ");
		        valitext(10, ent[j].primerNombre);
				gotoxy(15,9);
		        printf("Segundo nombre: ");
		        valitext(10, ent[j].segundoNombre);
		        gotoxy(15,10);
		        printf("Apellido Paterno: ");
		        valitext(10, ent[j].apellidoPaterno);
		        gotoxy(15,11);
		        printf("Apellido Materno: ");
		        valitext(10, ent[j].apellidoMaterno);
				gotoxy(15,12);
				printf("Tel%cfono: ", 130);
		        valiTelefono(ent[j].telefono, 10);
		        gotoxy(15,15);
	        	printf("%cEst%cn bien los datos? (Y / N): ", 168, 160);
	        	option = yesOrNo(1);
	        	if (option == 'Y')
	        		break;
			}
	        strcpy(ent[j].estado, "Inactivo"); // Son por defecto de baja
	        strcpy(ent[j].especialidad, "S/N");
	    	strcpy(ent[j].turno, "S/N");
	    	ent[j].idServicio = 0; // 0 means null
	        fwrite(&ent[j], sizeof(struct entrenador), 1, fp);
	        gotoxy(15,15);
			printf("%cEntrenador a%cadido exitosamente!", 173, 164);
	        getch();
	        gotoxy(15,18);
	        printf("%cDesea darlo de alta? (Y / N): ", 168);
	        option = yesOrNo(1);
	        if (option == 'Y') {
	        	fclose(fp);
	        	altaEntrenador(ent[j].id, 0);
			}
			gotoxy(15,18);
			if(option == 'Y') {
				system("cls");
				gotoxy(10, 5);
			}
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
		printf("<====    Consulta Entrenador    ====>");
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
    char option;
    system("cls");
    gotoxy(36,2);
    printf("<====    Consulta General Entrenador    ====>");
    gotoxy(10,5);
    printf("ID   ID Ser.  P. Nombre   S. Nombre   Apellido P.  Apellido M.  Tel%cfono     Especialidad    Turno       Estado", 130);
    gotoxy(10,6);
    printf("___________________________________________________________________________________________________________________");
    fp = fopen("src/entrenadores.txt","r+");
    if(fp == NULL){
        gotoxy(10,8);
        printf("Error abriendo el archivo");
        exit(1);
    }
    j=8;
    while(fread(&ent[i], sizeof(struct entrenador), 1, fp) == 1){
    	if (strcmp(ent[i].estado, "Activo") == 0) { // Solo se imprimen los activos
    		gotoxy(10, j);
	        printf("%-5d%-9d%-12s%-12s%-13s%-13s%-13s%-16s%-12s%s", ent[i].id, ent[i].idServicio, ent[i].primerNombre, ent[i].segundoNombre, ent[i].apellidoPaterno, ent[i].apellidoMaterno, ent[i].telefono, ent[i].especialidad, ent[i].turno, ent[i].estado);
	        i++;
	        j++;
		}
    }
    fclose(fp);
    getch();
    gotoxy (10, j+3);
    printf("%cDesea ver los entrenadores inactivos tambi%cn? (Y / N): ", 168, 130);
	option = yesOrNo(1);
	if (option == 'Y') {
		fp = fopen("src/entrenadores.txt","r+");
	    if(fp == NULL){
	        gotoxy(10,8);
	        printf("Error abriendo el archivo");
	        exit(1);
	    }
		i = 0, j = 8;
		system("cls");
	    gotoxy(36,2);
	    printf("<====    Consulta General Entrenador    ====>");
	    gotoxy(10,5);
    	printf("ID   ID Ser.  P. Nombre   S. Nombre   Apellido P.  Apellido M.  Tel%cfono     Especialidad    Turno       Estado", 130);
	    gotoxy(10,6);
	    printf("___________________________________________________________________________________________________________________");
		while(fread(&ent[i], sizeof(struct entrenador), 1, fp) == 1){
	    	if (strcmp(ent[i].estado, "Inactivo") == 0) { // Solo se imprimen los activos
	    		gotoxy(10, j);
	        	printf("%-5d%-9d%-12s%-12s%-13s%-13s%-13s%-16s%-12s%s", ent[i].id, ent[i].idServicio, ent[i].primerNombre, ent[i].segundoNombre, ent[i].apellidoPaterno, ent[i].apellidoMaterno, ent[i].telefono, ent[i].especialidad, ent[i].turno, ent[i].estado);
		        i++;
		        j++;
			}
    	}
	}
    fclose(fp);
    gotoxy(10, j+5);
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
	p = idPositionEnt(ent, cod); 
	while(option == 'Y'){
		system("cls");
		gotoxy(38,2);
	    printf("<====     Consulta Espec%cfica de Entrenador     ====>", 161);
	    gotoxy(38,5);
		printf("ID del Entrenador: ");
		cod = nument(3);
		fp = fopen("src/entrenadores.txt","r+");
		while(!feof(fp)){ 
			fread(&ent[i], sizeof(struct entrenador), 1, fp);
			if(cod == ent[i].id){ // Lo imprime aunque estï¿½ inactivo
				system("cls");
				gotoxy(38,2);
			    printf("<====     Consulta Espec%cfica Entrenador     ====>", 161);
			    displayEntrenador(i, 5);
				getch();
		        gotoxy(10, 12);
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
	    printf("<====    Modificar Entrenador    ====>");
	    gotoxy(10,5);
	    printf("Inserta la ID de entrenador a modificar: ");
	    idEntrenador = nument(3);
	    p = idPositionEnt(ent, idEntrenador);
	    if (ent[p].id == idEntrenador && strcmp(ent[p].estado, "Activo") == 0)
	    {
	    	displayEntrenador(p, 8);
		    gotoxy(10,14);
			printf("%cEst%c seguro que quiere editar el entrenador con la ID `%i`? (Y / N): ", 168, 160, idEntrenador);
		    option = yesOrNo(1);
		}
		while(idEntrenador == ent[p].id && strcmp(ent[p].estado, "Activo") == 0) // Puedes modificar mientras la ID coincida y el entrenador se encuentre activo
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
        	displayEntrenador(p, 4);
            gotoxy(10,10);
	        printf("Primer nombre: ");
	        valitext(10, ent[p].primerNombre);
	        gotoxy(10,11);
	        printf("Segundo nombre: ");
	        valitext(10, ent[p].segundoNombre);
			gotoxy(10,12);
	        printf("Apellido Paterno: ");
	        valitext(10, ent[p].apellidoPaterno);
	        gotoxy(10,13);
	        printf("Apellido Materno: ");
	        valitext(10, ent[p].apellidoMaterno);
	        gotoxy(10,14);
			printf("Tel%cfono: ", 130);
	        valiTelefono(ent[p].telefono, 10);
	        gotoxy(10,16);
	        printf("%cDesea guardar los cambios? (Y / N): ", 168);
	        option = yesOrNo(1);
			gotoxy(10,19);
			// Primero guarda la variable cambiada y la mueve al principio,
			// entonces, anota el resto menos la cambiada.
			if(option == 'Y')
				fwrite(&ent[p], sizeof(struct entrenador), 1, temp); // Primero se anota la reciï¿½n guardada
			while (fread(&ent[i], sizeof(struct entrenador), 1, fp) == 1) {
				if (ent[i].id != ent[p].id) { // Condiciï¿½n para que no se repita la misma id despuï¿½s del cambio
	    			fwrite(&ent[i], sizeof(struct entrenador), 1, temp);
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
				printf("No se hizo ning%cn cambio.", 163);
				remove("src/temporal.txt");
			}
	        getch();
            return;
	    }
	    
    	if (option == 'Y')
    	{
    		
			system("cls");
			gotoxy(10,4);
			printf("%i", p);
    		if (strcmp(ent[p].estado, "Inactivo") == 0)
				printf("La ID `%i` necesita estar dada de alta para ser modificada.", idEntrenador);
			else
				printf("La ID `%i` no est%c registrada.", idEntrenador, 160);
			gotoxy(10,7);
			printf("%cDesea buscar otro entrenador para modificar? (Y / N): ", 168, 164);
			option = yesOrNo(1);
			if (option == 'N')
				return;
		}
	} while (option == 'Y');
}

void altaBajaEntrenador() {
	int option = 0;
	
	do {
		system("cls");
		gotoxy(40, 5);
		printf("<====    Alta / Baja Entrenador    ====>");
		gotoxy(40, 8);
		printf("1. Alta");
		gotoxy(40, 9);
		printf("2. Baja", 161);
		gotoxy(40, 10);
		printf("3. Regresar");
		
		gotoxy(44, 15);
		printf("> > Elige una opci%cn: ", 162);
		option = nument(1);
		leerArchivoEntrenador();
		switch (option) {
			case 1:
				altaEntrenador(0, 0);
				break;
			case 2:
				bajaEntrenador(0, 0);
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
		guardarArchivoEntrenador(ent);
	} while (option != 3);	
}

void altaEntrenador(int id, int y) {
	FILE *fp,*temp;
    int i = 0, j = 0, p = 0;
	char option = 'Y';
    while(option == 'Y')
    {
    	i = 0, j = 0;
    	fp = fopen("src/entrenadores.txt", "r+");
	    if(fp == NULL){
	    	system("cls");
	        gotoxy(10,5);
	        printf("Error abriendo el archivo");
	        exit(1);
	    }
	    while(fread(&ent[j], sizeof(struct entrenador), 1, fp) == 1){
	    	if (strcmp(ent[j].estado, "Activo") == 0) { // Solo se imprimen los activos
	    		i++;
	    	}
	    	j++;
		}
		fclose(fp);
	    system("cls");
	    if (i < 10)
	    {
			gotoxy(10,y+3);
		    printf("<====    Dar de Alta Entrenador    ====>");
		    gotoxy(10,y+5);
		    if (id == 0) {	
			    printf("ID entrenador: ");
			    id = nument(3);
			}
			else {
				printf("Insertar la ID a dar de alta: %i", id);
			}
		    p = idPositionEnt(ent, id);
		    
		    while (id == ent[p].id && option == 'Y' && strcmp(ent[p].estado, "Inactivo") == 0)
		    {
		    	fp = fopen("src/entrenadores.txt", "r+");
			    if(fp == NULL){
			    	system("cls");
			        gotoxy(10,5);
			        printf("Error abriendo el archivo");
			        exit(1);
			    }
			    temp = fopen("src/temporal.txt","w+");
			    if(temp == NULL) {
			        gotoxy(10,y+6);
			        printf("Error al abrir el archivo");
			        exit(1);
		    	}
				displayEntrenador(p, y+8);
		    	strcpy(ent[p].estado, "Activo"); // El estado queda desactivo y ya no se mostrarï¿½ o tomarï¿½ en cuenta
		        while (1) {
		        	int condition = 0, condition2 = 0;
		        	system("cls");
		        	gotoxy(10,y+3);
		    		printf("<====    Dar de Alta Entrenador    ====>");
		    		gotoxy(10,y+5);
		    		printf("ID entrenador: %i", id);
					displayEntrenador(p, y+8);
					gotoxy(10,y+14);
					printf("Especialidad: ");
			        valitext(12, ent[p].especialidad);
		        	FILE *pSer;
		        	pSer = fopen("src/servicios.txt","r+");
				    if(pSer == NULL) {
				        gotoxy(10,y+16);
				        printf("Error al abrir el archivo");
				        exit(1);    
		    		}
		    		y = 2;
		    		system("cls");
					gotoxy(10,y);
					printf("Servicios compatibles: ");
					gotoxy(10,y+2);
					printf("ID   Nombre de Servicio  Especialidad   Estado    Descripci%cn                            ", 162);
					gotoxy(10,y+3);
					printf("____________________________________________________________________________________________________");
		    		while(fread(&ser[i], sizeof(struct servicio), 1, pSer) == 1){
						if (strcmp(ser[i].estado, "Activo") == 0 && strcmp(ent[p].especialidad, ser[i].especialidadReq) == 0) {
							gotoxy(10, y+5);
							printf("%-5d%-20s%-15s%-10s%s", ser[i].id, ser[i].nombre, ser[i].especialidadReq, ser[i].estado, ser[i].descripcion);
							y++;
							condition = 1;
						}
			        	i++;
			        }
			        if (i == 0) {
			        	system("cls");
			        	gotoxy(10,10);
			        	printf("No puedes dar de alta ning%cn entrenador si no hay servicios registraods.", 163);
			        	fclose(fp);
						fclose(temp);
						fclose(pSer);
			        	getch();
						return;
					}
					if (condition == 0) {
			        	system("cls");
						gotoxy(10,10);
						printf("No hay ning%cn servicio que requiera la especialidad del entrenador `%i` ahora mismo.", 163, ent[p].id);
						fclose(fp);
						fclose(temp);
						fclose(pSer);
			        	getch();
						return;
					}
					if (condition == 1) {
						fclose(pSer);
						gotoxy(10, y+7);
						printf("ID entrenador: %i", id);
						y++;
						while (1) {
							gotoxy(10, y+7);
							printf("ID del servicio: ");
							ent[p].idServicio = nument(3);
							pSer = fopen("src/servicios.txt","r+");
							if(pSer == NULL) {
						        gotoxy(10,y+8);
						        printf("Error al abrir el archivo");
						        exit(1);    
				    		}
				    		i = 0;
				    		while(fread(&ser[i], sizeof(struct servicio), 1, pSer) == 1) {
								if (strcmp(ser[i].estado, "Activo") == 0 && strcmp(ent[p].especialidad, ser[i].especialidadReq) == 0  && ser[i].id == ent[p].idServicio) {
									condition2 = 1;
								}
					        	i++;
					        }
							fclose(pSer);
							if (condition2 == 1) {
								break;
							}
							else {
								int len = 1;
								if (ent[p].idServicio >= 10)
									len = 2;
								if (ent[p].idServicio >= 100)
									len = 3;
								for (int x = 0; x < len; x++) {
									printf("\b \b");
								}
							}
						} break;
					}
				}
		        gotoxy(10,y+8);
		        printf("Turno: ");
		        valiTurno(10, ent[p].turno);
				gotoxy(10,y+10);
				printf("%cGuardar los cambios y dar de alta el entrenador con la ID `%i`? (Y / N): ", 168, id);
			    option = yesOrNo(1);
			    i = 0; // Se pone para resetear el conteo donde se añaden los entrenadores
			 	if(option == 'Y')
					fwrite(&ent[p], sizeof(struct entrenador), 1, temp); // Primero se anota la reciï¿½n guardada
				while (fread(&ent[i], sizeof(struct entrenador), 1, fp) == 1) {
					if (ent[i].id != ent[p].id) { // Condiciï¿½n para que no se repita la misma id despuï¿½s del cambio
		    			fwrite(&ent[i], sizeof(struct entrenador), 1, temp);
		    		}
		    		i++;
		    	}
		    	fclose(fp);
				fclose(temp);
				gotoxy(10,y+13);
				if(option == 'Y')
				{
					remove("src/entrenadores.txt");
				    rename("src/temporal.txt", "src/entrenadores.txt");
			    	printf("%cEntrenador dado de alta exitosamente!", 173);
				}
				else {
					printf("No se dio de alta el entrenador con la ID `%i`.", id);
					remove("src/temporal.txt");
				}
		        getch();
	            return;
			}
			system("cls");
			gotoxy(10,4);
			printf("La ID `%i` no se encuentra registrada o ya se dio de alta.", id);
			gotoxy(10,5);
			printf("%cDesea buscar otro entrenador para dar de alta? (Y / N): ", 168, 164);
			option = yesOrNo(1);
			if (option == 'N')
				return;	
		}
		else {
			system("cls");
			gotoxy(10, 5);
			printf("No hay espacio de almacentamiento para dar m%cs entrenadores de alta. :(", 160);
			getch();
			return;
		}
		
	}
}

void bajaEntrenador(int id, int y) {
	int i, p; // P = position
	char option = 'Y';
    FILE *fp,*temp;
    do {
	    system("cls");
		gotoxy(10,y+3);
		
	    printf("<====    Dar de Baja Entrenador    ====>");
	    gotoxy(10,y+5);
	    if (id == NULL) {	
		    printf("Insertar la ID a dar de baja: ");
		    id = nument(3);
		}
	    p = idPositionEnt(ent, id);
	    
	    while (id == ent[p].id && option == 'Y' && strcmp(ent[p].estado, "Activo") == 0)
	    {
		    fp = fopen("src/entrenadores.txt","r+");
		    if(fp == NULL){
		        gotoxy(10,y+6);
		        printf("Error al abrir el archivo");
		        exit(1);
		    }
		    temp = fopen("src/temporal.txt","w+");
		    if(temp == NULL) {
		        gotoxy(10,y+6);
		        printf("Error al abrir el archivo");
		        exit(1);
	    	}
			displayEntrenador(p, y+8);
	    	strcpy(ent[p].estado, "Inactivo"); // El estado queda desactivo y ya no se mostrarï¿½ o tomarï¿½ en cuenta
	    	strcpy(ent[p].especialidad, "S/N");
    		strcpy(ent[p].turno, "S/N");
			gotoxy(10,y+14);
			printf("Advertencia: Si se da de baja el usuario perder%c su especialidad y turno.", 160, 160);
			gotoxy(10,y+16);
			printf("%cEst%cs seguro que quiere dar de baja el entrenador con la ID `%i`? (Y / N): ", 168, 160, id);
		    option = yesOrNo(1);
		 	if(option == 'Y')
				fwrite(&ent[p], sizeof(struct entrenador), 1, temp); // Primero se anota la reciï¿½n guardada
			while (fread(&ent[i], sizeof(struct entrenador), 1, fp) == 1) {
				if (ent[i].id != ent[p].id) { // Condiciï¿½n para que no se repita la misma id despuï¿½s del cambio
	    			fwrite(&ent[i], sizeof(struct entrenador), 1, temp);
	    		}
	    		i++;
	    	}
	    	fclose(fp);
			fclose(temp);
			gotoxy(10,y+19);
			if(option == 'Y')
			{
				remove("src/entrenadores.txt");
			    rename("src/temporal.txt", "src/entrenadores.txt");
		    	printf("%cEntrenador `%i` dado de baja exitosamente!", 173, id);
		    	getch();
		    	desactivadorEntCli(id, y+20);
			}
			else {
				printf("No se dio de baja el entrenador con la ID `%i`.", id);
				remove("src/temporal.txt");
	        	getch();
			}
            return;
		}
		system("cls");
		gotoxy(10,4);
		printf("La ID `%i` no se encuentra registrada o ya ha sido dado de baja.", id);
		gotoxy(10,5);
		printf("%cDesea buscar otro entrenador para dar de baja? (Y / N): ", 168, 164);
		option = yesOrNo(1);
		if (option == 'N')
			return;
	} while (option == 'Y');
}

void displayEntrenador(int p, int y) {
	// y representa la parte de Gotoxy para que baje
	gotoxy(10,y);
    printf("ID   ID Ser.  P. Nombre   S. Nombre   Apellido P.  Apellido M.  Tel%cfono     Especialidad    Turno       Estado", 130);
	gotoxy(10,y+1);
	printf("___________________________________________________________________________________________________________________");
	gotoxy(10, y+3);
	printf("%-5d%-9d%-12s%-12s%-13s%-13s%-13s%-16s%-12s%s", ent[p].id, ent[p].idServicio, ent[p].primerNombre, ent[p].segundoNombre, ent[p].apellidoPaterno, ent[p].apellidoMaterno, ent[p].telefono, ent[p].especialidad, ent[p].turno, ent[p].estado);
}

void leerArchivoEntrenador(){
    FILE *pEnt;
    int i = 0;
    pEnt = fopen("src/entrenadores.txt","r+");
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

void guardarArchivoEntrenador(struct entrenador ent[]) { // AKA la poderosa acomoda numeros
	FILE *fp; // En vez de guardar el archivo en sï¿½, acomodarï¿½ las ID por orden numï¿½rico
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
	// Aquï¿½ se acomodan los nï¿½meros del arreglo de manera numï¿½rica
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
	
	// Aquï¿½ ya se imprimen las variables en orden numï¿½rico en un archivo temporal
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

int idRepetidaEnt(struct entrenador ent[], int idWanted) { 
	// Devolverï¿½ un 1 si la ID es repetida
	FILE *pEnt;
	int i = 0, j = 0, k = 0;
    pEnt = fopen("src/entrenadores.txt","r+");
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

int idSiguienteEnt(struct entrenador ent[], int i) {
	if ((ent[i].id)+1 != (ent[i+1].id))  // Se actualiza por si se añadió un nuevo valor
		leerArchivoEntrenador(); // Sin esto repite el mismo núemero dos veces seguidas el mismo n
	if ((ent[i].id)+1 == (ent[i+1].id))
		return idSiguienteEnt(ent, i+1);
	return ent[i].id + 1;
}

int idPositionEnt(struct entrenador ent[], int idWanted) {
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


// <=== CLIENTES ===>
// <=== CLIENTES ===>
// <=== CLIENTES ===>


void addCliente() {
	FILE *fp;
    char option = 'Y', option2;
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
	    	if (strcmp(cli[j].estado, "Activo") == 0) { // Solo se imprimen los activos
	    		i++;
	    	}
	    	j++;
		}
    	if (i < 10)
    	{
	    	gotoxy(15,2);
	        printf("<====    A%cadir Cliente    ====>", 164);
	        gotoxy(15,4);
	        printf("Inserta los detalles del cliente");
	        gotoxy(15,6);
	        printf("%cDesea a%cdir la ID autom%cticamente o manualmente? (A / M): ", 168, 164, 160);
	        option2 = autoOrManual(1);
	        gotoxy(15,8);
	        if (option2 == 'A') {
	        	printf("ID: %i", idSiguienteCli(cli, 0));
				cli[j].id = idSiguienteCli(cli, 0);
			}
			if (option2 == 'M') {	
		        printf("ID: ");
		        cli[j].id = nument(3);
			}
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
		        if (option == 'N')
		        	return;
				guardarArchivoCliente(cli); // Para ordenar las IDs
		        gotoxy(10, 17);
		        printf("Recomendaci%cn: La id `%i` es la pr%cxima ID disponible", 162, idSiguienteCli(cli, 0), 162);
		        getch();
		        if (option == 'Y') {
		        	addCliente();
		        	return;
				}
				return;
			}
			option = 'N';
			while (1) {
				system("cls");
				gotoxy(15,3);
		        printf("<====    A%cadir Cliente    ====>", 164);
		        gotoxy(15,5);
		        printf("Inserta los detalles del cliente");
		        gotoxy(15,7);
		        printf("ID: %i", cli[j].id);
				gotoxy(15,8);
		        printf("Primer nombre: ");
		        valitext(10, cli[j].primerNombre);
				gotoxy(15,9);
		        printf("Segundo nombre: ");
		        valitext(10, cli[j].segundoNombre);
		        gotoxy(15,10);
		        printf("Apellido Paterno: ");
		        valitext(10, cli[j].apellidoPaterno);
		        gotoxy(15,11);
		        printf("Apellido Materno: ");
		        valitext(10, cli[j].apellidoMaterno);
				gotoxy(15,12);
				printf("Tel%cfono: ", 130);
		        valiTelefono(cli[j].telefono, 10);
		        gotoxy(15,13);
		        printf("Direcci%cn: ", 162);
		        valiDireccion(20, cli[j].direccion);
		        gotoxy(15,16);
	        	printf("%cEst%cn bien los datos? (Y / N): ", 168, 160);
	        	option = yesOrNo(1);
	        	if (option == 'Y')
	        		break;
			}
	        strcpy(cli[j].estado, "Inactivo"); // Son por defecto de baja
	    	strcpy(cli[j].especialidadBus, "S/N");
	    	strcpy(cli[j].turno, "S/N");
	    	cli[j].idEntrenador = 0; // 0 means null
	        fwrite(&cli[j], sizeof(struct cliente), 1, fp);
	        gotoxy(15,16);
			printf("%cEl Cliente ha a%cadido exitosamente!", 173, 164);
	        getch();
	        gotoxy(15,19);
	        printf("%cDesea darlo de alta? (Y / N): ", 168);
	        option = yesOrNo(1);
	        if (option == 'Y') {
	        	fclose(fp);
	        	altaCliente(cli[j].id, 0);
			}
			gotoxy(15,19);
			if(option == 'Y') {
				system("cls");
				gotoxy(10, 5);
			}
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
    char option;
    system("cls");
    gotoxy(36,2);
    printf("<====    Consulta General Cliente    ====>");
    gotoxy(10,5);
    printf("ID   ID Ent.  P. Nombre   S. Nombre   Apellido P.  Apellido M.  Tel%cfono    Direcci%cn            Especialidad Req.  Turno       Estado", 130);
    gotoxy(10,6);
    printf("__________________________________________________________________________________________________________________________________________");
    fp = fopen("src/clientes.txt","r+");
    if(fp == NULL){
        gotoxy(10,8);
        printf("Error abriendo el archivo");
        exit(1);
    }
    j=8;
    while(fread(&cli[i], sizeof(struct cliente), 1, fp) == 1){
    	if (strcmp(cli[i].estado, "Activo") == 0) { // Solo se imprimen los activos
    		gotoxy(10, j);
	        printf("%-5d%-9d%-12s%-12s%-13s%-13s%-12s%-21s%-19s%-12s%s", cli[i].id, cli[i].idEntrenador, cli[i].primerNombre, cli[i].segundoNombre, cli[i].apellidoPaterno, cli[i].apellidoMaterno, cli[i].telefono, cli[i].direccion, cli[i].especialidadBus, cli[i].turno, cli[i].estado);
	        i++;
	        j++;
		}
    }
    fclose(fp);
    getch();
    gotoxy (10, j+3);
    printf("%cDesea ver los clientes inactivos tambi%cn? (Y / N): ", 168, 130);
	option = yesOrNo(1);
	if (option == 'Y') {
		fp = fopen("src/clientes.txt","r+");
	    if(fp == NULL){
	        gotoxy(10,8);
	        printf("Error abriendo el archivo");
	        exit(1);
	    }
		i = 0, j = 8;
		system("cls");
	    gotoxy(36,2);
	    printf("<====    Consulta General Cliente    ====>");
	    gotoxy(10,5);
    	printf("ID   ID Ent.  P. Nombre   S. Nombre   Apellido P.  Apellido M.  Tel%cfono    Direcci%cn            Especialidad Req.  Turno       Estado", 130, 162);
	    gotoxy(10,6);
		printf("__________________________________________________________________________________________________________________________________________");
		while(fread(&cli[i], sizeof(struct cliente), 1, fp) == 1){
	    	if (strcmp(cli[i].estado, "Inactivo") == 0) { // Solo se imprimen los activos
	    		gotoxy(10, j);
	        	printf("%-5d%-9d%-12s%-12s%-13s%-13s%-12s%-21s%-19s%-12s%s", cli[i].id, cli[i].idEntrenador, cli[i].primerNombre, cli[i].segundoNombre, cli[i].apellidoPaterno, cli[i].apellidoMaterno, cli[i].telefono, cli[i].direccion, cli[i].especialidadBus, cli[i].turno, cli[i].estado);
		        i++;
		        j++;
			}
    	}
	}
    fclose(fp);
    gotoxy(10, j+5);
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
	    printf("<====     Consulta Espec%cfica de Cliente     ====>", 161);
	    gotoxy(38,5);
		printf("ID del Cliente: ");
		cod = nument(3);
		fp = fopen("src/clientes.txt","r+");
		while(!feof(fp)){ 
			fread(&cli[i], sizeof(struct cliente), 1, fp);
			if(cod == cli[i].id){ // Lo imprime aunque estï¿½ inactivo
				system("cls");
				gotoxy(38,2);
			    printf("<====     Consulta Espec%cfica Entrenador     ====>", 161);
			    displayEntrenador(i, 5);
				getch();
		        gotoxy(10, 12);
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

void modificarCliente(){
	FILE *fp, *temp;
    char option = 'Y';
	int idCliente; // Esto era char antes, daba 89 en vez de 344 LMAO
	int i = 0, p = 0;
	do {
		system("cls");
		gotoxy(10,3);
	    printf("<====    Modificar Cliente    ====>");
	    gotoxy(10,5);
	    printf("Inserta la ID de cliente a modificar: ");
	    idCliente = nument(3);
	    p = idPositionCli(cli, idCliente);
	    if (cli[p].id == idCliente && strcmp(cli[p].estado, "Activo") == 0)
	    {
	    	displayCliente(p, 8);
		    gotoxy(10,14);
			printf("%cEst%c seguro que quiere editar el cliente con la ID `%i`? (Y / N): ", 168, 160, idCliente);
		    option = yesOrNo(1);
		}
		while(idCliente == cli[p].id && strcmp(cli[p].estado, "Activo") == 0) // Puedes modificar mientras la ID coincida y el cliente se encuentre activo
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
        	displayCliente(p, 4);
            gotoxy(10,10);
	        printf("Primer nombre: ");
	        valitext(10, cli[p].primerNombre);
			gotoxy(10,11);
	        printf("Segundo nombre: ");
	        valitext(10, cli[p].segundoNombre);
	        gotoxy(10,12);
	        printf("Apellido Paterno: ");
	        valitext(10, cli[p].apellidoPaterno);
	        gotoxy(10,13);
	        printf("Apellido Materno: ");
	        valitext(10, cli[p].apellidoMaterno);
			gotoxy(10,14);
			printf("Tel%cfono: ", 130);
	        valiTelefono(cli[p].telefono, 10);
	        gotoxy(10,15);
	        printf("Direcci%cn: ", 162);
	        valiDireccion(20, cli[p].direccion);
	        gotoxy(10,17);
	        printf("%cDesea guardar los cambios? (Y / N): ", 168);
	        option = yesOrNo(1);
			gotoxy(10,20);
			// Primero guarda la variable cambiada y la mueve al principio,
			// entonces, anota el resto menos la cambiada.
			if(option == 'Y')
				fwrite(&cli[p], sizeof(struct cliente), 1, temp); // Primero se anota la reciï¿½n guardada
			while (fread(&cli[i], sizeof(struct cliente), 1, fp) == 1) {
				if (cli[i].id != cli[p].id) { // Condiciï¿½n para que no se repita la misma id despuï¿½s del cambio
	    			fwrite(&cli[i], sizeof(struct cliente), 1, temp);
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
				printf("No se hizo ning%cn cambio.", 163);
				remove("src/temporal.txt");
			}
	        getch();
            return;
	    }
	    
    	if (option == 'Y')
    	{
    		
			system("cls");
			gotoxy(10,4);
			printf("%i", p);
    		if (strcmp(cli[p].estado, "Inactivo") == 0)
				printf("La ID `%i` necesita estar dada de alta para ser modificada.", idCliente);
			else
				printf("La ID `%i` no est%c registrada.", idCliente, 160);
			gotoxy(10,7);
			printf("%cDesea buscar otro cliente para modificar? (Y / N): ", 168, 164);
			option = yesOrNo(1);
			if (option == 'N')
				return;
		}
	} while (option == 'Y');
}

void altaBajaCliente() {
	int option = 0;
	
	do {
		system("cls");
		gotoxy(40, 5);
		printf("<====    Alta / Baja Cliente    ====>");
		gotoxy(40, 8);
		printf("1. Alta");
		gotoxy(40, 9);
		printf("2. Baja", 161);
		gotoxy(40, 10);
		printf("3. Regresar");
		
		gotoxy(44, 15);
		printf("> > Elige una opci%cn: ", 162);
		option = nument(1);
		leerArchivoCliente();
		switch (option) {
			case 1:
				altaCliente(0, 0);
				break;
			case 2:
				bajaCliente(0, 0);
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
		guardarArchivoCliente(cli);
	} while (option != 3);	
}

void altaCliente(int id, int y) {
	FILE *fp,*temp;
    int i = 0, j = 0, p = 0;
	char option = 'Y';
    while(option == 'Y')
    {
    	i = 0, j = 0;
    	fp = fopen("src/clientes.txt", "r+");
	    if(fp == NULL){
	    	system("cls");
	        gotoxy(10,5);
	        printf("Error abriendo el archivo");
	        exit(1);
	    }
	    while(fread(&cli[j], sizeof(struct cliente), 1, fp) == 1){
	    	if (strcmp(cli[j].estado, "Activo") == 0) { // Solo se imprimen los activos
	    		i++;
	    	}
	    	j++;
		}
		fclose(fp);
	    system("cls");
	    if (i < 10)
	    {
			gotoxy(10,y+3);
		    printf("<====    Dar de Alta Cliente    ====>");
		    gotoxy(10,y+5);
		    if (id == 0) {	
			    printf("ID cliente: ");
			    id = nument(3);
			}
			else {
				printf("Insertar la ID a dar de alta: %i", id);
			}
		    p = idPositionCli(cli, id);
		    
		    while (id == cli[p].id && option == 'Y' && strcmp(cli[p].estado, "Inactivo") == 0)
		    {
		    	fp = fopen("src/clientes.txt", "r+");
			    if(fp == NULL){
			    	system("cls");
			        gotoxy(10,5);
			        printf("Error abriendo el archivo");
			        exit(1);
			    }
			    temp = fopen("src/temporal.txt","w+");
			    if(temp == NULL) {
			        gotoxy(10,y+6);
			        printf("Error al abrir el archivo");
			        exit(1);
		    	}
				displayCliente(p, y+8);
		    	strcpy(cli[p].estado, "Activo"); // El estado queda desactivo y ya no se mostrarï¿½ o tomarï¿½ en cuenta
		        while (1) {
		        	int condition = 0, condition2 = 0;
		        	system("cls");
		        	gotoxy(10,y+3);
		    		printf("<====    Dar de Alta Cliente    ====>");
		    		gotoxy(10,y+5);
		    		printf("ID cliente: %i", id);
					displayCliente(p, y+8);
					gotoxy(10,y+14);
					printf("Especialidad buscada: ");
			        valitext(12, cli[p].especialidadBus);
			        gotoxy(10,y+15);
		        	printf("Turno: ");
		        	valiTurno(10, cli[p].turno);
		        	FILE *pEnt;
		        	pEnt = fopen("src/entrenadores.txt","r+");
				    if(pEnt == NULL) {
				        gotoxy(10,y+16);
				        printf("Error al abrir el archivo");
				        exit(1);    
		    		}
		    		y = 2;
		    		system("cls");
					gotoxy(10,y);
					printf("Entrenadores compatibles: ");
					gotoxy(10,y+2);
					printf("ID   ID Ser.  P. Nombre   S. Nombre   Apellido P.  Apellido M.  Tel%cfono     Especialidad    Turno       Estado", 130);
					gotoxy(10,y+3);
					printf("___________________________________________________________________________________________________________________");
		    		while(fread(&ent[i], sizeof(struct entrenador), 1, pEnt) == 1){
						if (strcmp(ent[i].estado, "Activo") == 0 && strcmp(cli[p].especialidadBus, ent[i].especialidad) == 0 && (strcmp(cli[p].turno, ent[i].turno) == 0 || strcmp(ent[i].turno, "Mixto") == 0 || strcmp(cli[p].turno, "Mixto") == 0)) {
							gotoxy(10, y+5);
							printf("%-5d%-9d%-12s%-12s%-13s%-13s%-13s%-16s%-12s%s", ent[i].id, ent[i].idServicio, ent[i].primerNombre, ent[i].segundoNombre, ent[i].apellidoPaterno, ent[i].apellidoMaterno, ent[i].telefono, ent[i].especialidad, ent[i].turno, ent[i].estado);
							y++;
							condition = 1;
						}
			        	i++;
			        }
			        if (i == 0) {
			        	system("cls");
			        	gotoxy(10,10);
			        	printf("No puedes dar de alta ning%cn cliente si no hay entrenadores registrados.", 163);
			        	fclose(fp);
						fclose(temp);
						fclose(pEnt);
			        	getch();
						return;
					}
					if (condition == 0) {
			        	system("cls");
						gotoxy(10,10);
						printf("No hay ning%cn entrenador que se adapte a las necesidades del cliente `%i` ahora mismo.", 163, ent[p].id);
						fclose(fp);
						fclose(temp);
						fclose(pEnt);
			        	getch();
						return;
					}
					if (condition == 1) {
						fclose(pEnt);
						gotoxy(10, y+7);
						printf("ID del cliente: %i", id);
						y++;
						while (1) {
							gotoxy(10, y+7);
							printf("ID del entrenador: ");
							cli[p].idEntrenador = nument(3);
							pEnt = fopen("src/entrenadores.txt","r+");
							if(pEnt == NULL) {
						        gotoxy(10,y+8);
						        printf("Error al abrir el archivo");
						        exit(1);    
				    		}
				    		i = 0;
				    		while(fread(&ent[i], sizeof(struct entrenador), 1, pEnt) == 1) {
								if (strcmp(ent[i].estado, "Activo") == 0 && strcmp(cli[p].especialidadBus, ent[i].especialidad) == 0 && ent[i].id == cli[p].idEntrenador) {
									condition2 = 1;
								}
					        	i++;
					        }
							fclose(pEnt);
							if (condition2 == 1) {
								break;
							}
							else {
								int len = 1;
								if (cli[p].idEntrenador >= 10)
									len = 2;
								if (cli[p].idEntrenador >= 100)
									len = 3;
								for (int x = 0; x < len; x++) {
									printf("\b \b");
								}
							}
						} break;
					}
				}
				gotoxy(10,y+10);
				printf("%cGuardar los cambios y dar de alta el cliente con la ID `%i`? (Y / N): ", 168, id);
			    option = yesOrNo(1);
			    i = 0; // Se pone para resetear el conteo donde se añaden los clientes
			 	if(option == 'Y')
					fwrite(&cli[p], sizeof(struct cliente), 1, temp); // Primero se anota la reciï¿½n guardada
				while (fread(&cli[i], sizeof(struct cliente), 1, fp) == 1) {
					if (cli[i].id != cli[p].id) { // Condiciï¿½n para que no se repita la misma id despuï¿½s del cambio
		    			fwrite(&cli[i], sizeof(struct cliente), 1, temp);
		    		}
		    		i++;
		    	}
		    	fclose(fp);
				fclose(temp);
				gotoxy(10,y+13);
				if(option == 'Y')
				{
					remove("src/clientes.txt");
				    rename("src/temporal.txt", "src/clientes.txt");
			    	printf("%cCliente dado de alta exitosamente!", 173);
				}
				else {
					printf("No se dio de alta el cliente con la ID `%i`.", id);
					remove("src/temporal.txt");
				}
		        getch();
	            return;
			}
			system("cls");
			gotoxy(10,4);
			printf("La ID `%i` no se encuentra registrada o ya se dio de alta.", id);
			gotoxy(10,5);
			printf("%cDesea buscar otro cliente para dar de alta? (Y / N): ", 168, 164);
			option = yesOrNo(1);
			if (option == 'N')
				return;	
		}
		else {
			system("cls");
			gotoxy(10, 5);
			printf("No hay espacio de almacentamiento para dar m%cs clientes de alta. :(", 160);
			getch();
			return;
		}
		
	}
}

void bajaCliente(int id, int y) {
	int i, p; // P = position
	char option = 'Y';
    FILE *fp,*temp;
    do {
	    system("cls");
		gotoxy(10,y+3);
		
	    printf("<====    Dar de Baja Cliente    ====>");
	    gotoxy(10,y+5);
	    if (id == NULL) {	
		    printf("Insertar la ID a dar de baja: ");
		    id = nument(3);
		}
	    p = idPositionCli(cli, id);
	    
	    while (id == cli[p].id && option == 'Y' && strcmp(cli[p].estado, "Activo") == 0)
	    {
		    fp = fopen("src/clientes.txt","r+");
		    if(fp == NULL){
		        gotoxy(10,y+6);
		        printf("Error al abrir el archivo");
		        exit(1);
		    }
		    temp = fopen("src/temporal.txt","w+");
		    if(temp == NULL) {
		        gotoxy(10,y+6);
		        printf("Error al abrir el archivo");
		        exit(1);
	    	}
			displayCliente(p, y+8);
	    	strcpy(cli[p].estado, "Inactivo"); // Son por defecto de baja
	    	strcpy(cli[p].especialidadBus, "S/N");
	    	strcpy(cli[p].turno, "S/N");
	    	cli[p].idEntrenador = 0; // 0 means null
			gotoxy(10,y+14);
			printf("Advertencia: Si se da de baja el usuario perder%c su especialidad y turno.", 160, 160);
			gotoxy(10,y+16);
			printf("%cEst%cs seguro que quiere dar de baja el cliente con la ID `%i`? (Y / N): ", 168, 160, id);
		    option = yesOrNo(1);
		 	if(option == 'Y')
				fwrite(&cli[p], sizeof(struct cliente), 1, temp); // Primero se anota la reciï¿½n guardada
			while (fread(&cli[i], sizeof(struct cliente), 1, fp) == 1) {
				if (cli[i].id != cli[p].id) { // Condiciï¿½n para que no se repita la misma id despuï¿½s del cambio
	    			fwrite(&cli[i], sizeof(struct cliente), 1, temp);
	    		}
	    		i++;
	    	}
	    	fclose(fp);
			fclose(temp);
			gotoxy(10,y+19);
			if(option == 'Y')
			{
				remove("src/clientes.txt");
			    rename("src/temporal.txt", "src/clientes.txt");
		    	printf("%cCliente dado de baja exitosamente!", 173);
			}
			else {
				printf("No se dio de baja el cliente con la ID `%i`.", id);
				remove("src/temporal.txt");
			}
	        getch();
            return;
		}
		system("cls");
		gotoxy(10,4);
		printf("La ID `%i` no se encuentra registrada o ya ha sido dado de baja.", id);
		gotoxy(10,5);
		printf("%cDesea buscar otro cliente para dar de baja? (Y / N): ", 168, 164);
		option = yesOrNo(1);
		if (option == 'N')
			return;
	} while (option == 'Y');
}

void displayCliente(int p, int y){
	// y representa la parte de Gotoxy para que baje
	gotoxy(10,y);
    printf("ID   ID Ent.  P. Nombre   S. Nombre   Apellido P.  Apellido M.  Tel%cfono    Direcci%cn            Especialidad Req.  Turno       Estado", 130, 162);
	gotoxy(10,y+1);
	printf("__________________________________________________________________________________________________________________________________________");
	gotoxy(10, y+3);
	printf("%-5d%-9d%-12s%-12s%-13s%-13s%-12s%-21s%-19s%-12s%s", cli[p].id, cli[p].idEntrenador, cli[p].primerNombre, cli[p].segundoNombre, cli[p].apellidoPaterno, cli[p].apellidoMaterno, cli[p].telefono, cli[p].direccion, cli[p].especialidadBus, cli[p].turno, cli[p].estado);
}

void leerArchivoCliente(){
	FILE *pCli;
    int i = 0;
    pCli = fopen("src/clientes.txt","r+");
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
	FILE *fp; // En vez de guardar el archivo en sï¿½, acomodarï¿½ las ID por orden numï¿½rico
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
	// Aquï¿½ se acomodan los nï¿½meros del arreglo de manera numï¿½rica
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
	
	// Aquï¿½ ya se imprimen las variables en orden numï¿½rico en un archivo temporal
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

int idRepetidaCli(struct cliente cli[], int idWanted){
	// Devolverï¿½ un 1 si la ID es repetida
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

int idSiguienteCli(struct cliente cli[], int i) {
	if ((cli[i].id)+1 != (cli[i+1].id)) // Sin esto repite el mismo núemero dos veces seguidas
		leerArchivoCliente();
	if ((cli[i].id)+1 == (cli[i+1].id))
		return idSiguienteCli(cli, i+1);
	return cli[i].id + 1;
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


// <=== REGISTROS ===>
// <=== REGISTROS ===>
// <=== REGISTROS ===>


void addRegistro(int idCliente) {
	
}

void consultarRegistro() {
	
}

void consultarRegistroGeneral() {
	
}

void consultarRegistroEspecifico() {
	
}

void modificarRegistro() {
	
}

void displayRegistro(int p, int y) {
	
}

void leerArchivoRegistro() {
	
}

void guardarArchivoRegistro(struct entrenador ent[]) {
	
}


// <=== DESACTIVADORES EN CADENA ===>
// Cuando un servicio se desactive se tendrán que desactivar los entrenadores relacionados. 
// Una vez que se desactiven los entrenadores se desactivarán los clientes, consecutivamente, sus registros
// <=== DESACTIVADORES EN CADENA ===>

void desactivadorSerEnt(int idDesactivada, int y) {
	// servicio --> entrenadores
    int i, j;
    FILE *fp,*temp;
    fp = fopen("src/entrenadores.txt","r+");
    if(fp == NULL){
        gotoxy(10,y);
        printf("Error al abrir el archivo");
        exit(1);
    }
    i = 0;
    while (fread(&ent[i], sizeof(struct entrenador), 1, fp) == 1) {
		i++;
	}
	fclose(fp);
	
	for (int p = 0; p < i; p++) {
	    fp = fopen("src/entrenadores.txt","r+");
	    if(fp == NULL){
	        gotoxy(10,y+6);
	        printf("Error al abrir el archivo");
	        exit(1);
	    }
	    temp = fopen("src/temporal.txt","w+");
	    if(temp == NULL) {
	        gotoxy(10,y+6);
	        printf("Error al abrir el archivo");
	        exit(1);
    	}
	    while (idDesactivada == ent[p].idServicio)
	    {
			ent[p].idServicio = 0;
	    	strcpy(ent[p].especialidad, "S/N");
			strcpy(ent[p].turno, "S/N");
	    	strcpy(ent[p].estado, "Inactivo"); // El estado queda desactivo y ya no se mostrarï¿½ o tomarï¿½ en cuenta
			fwrite(&ent[p], sizeof(struct entrenador), 1, temp); // Primero se anota la reciï¿½n guardada
			j = 0;
			while (fread(&ent[j], sizeof(struct entrenador), 1, fp) == 1) {
				if (ent[j].id != ent[p].id) { // Condiciï¿½n para que no se repita la misma id despuï¿½s del cambio
	    			fwrite(&ent[j], sizeof(struct entrenador), 1, temp);
	    		}
	    		j++;
	    	}
	    	fclose(fp);
			fclose(temp);
			gotoxy(10,y);
			y++;
			remove("src/entrenadores.txt");
		    rename("src/temporal.txt", "src/entrenadores.txt");
	    	printf("%cEntrenador `%i` dado de baja exitosamente!", 173, ent[p].id);
	    	getch();
	    	y = desactivadorEntCli(ent[p].id, y);
	    	break;
		}
		fclose(fp);
		fclose(temp);
	}
	guardarArchivoEntrenador(ent);
}

int desactivadorEntCli(int idDesactivada, int y) {
	// entrenador --> clientes
	int i, j;
    FILE *fp,*temp;
    fp = fopen("src/clientes.txt","r+");
    if(fp == NULL){
        gotoxy(10,y);
        printf("Error al abrir el archivo");
        exit(1);
    }
    i = 0;
    while (fread(&cli[i], sizeof(struct cliente), 1, fp) == 1) {
		i++;
	}
	fclose(fp);
	
	for (int p = 0; p < i; p++) {
	    fp = fopen("src/clientes.txt","r+");
	    if(fp == NULL){
	        gotoxy(10,y+6);
	        printf("Error al abrir el archivo");
	        exit(1);
	    }
	    temp = fopen("src/temporal.txt","w+");
	    if(temp == NULL) {
	        gotoxy(10,y+6);
	        printf("Error al abrir el archivo");
	        exit(1);
    	}
	    while (idDesactivada == cli[p].idEntrenador)
	    {
			cli[p].idEntrenador = 0;
	    	strcpy(cli[p].especialidadBus, "S/N");
			strcpy(cli[p].turno, "S/N");
	    	strcpy(cli[p].estado, "Inactivo"); // El estado queda desactivo y ya no se mostrarï¿½ o tomarï¿½ en cuenta
			fwrite(&cli[p], sizeof(struct cliente), 1, temp); // Primero se anota la reciï¿½n guardada
			j = 0;
			while (fread(&cli[j], sizeof(struct cliente), 1, fp) == 1) {
				if (cli[j].id != cli[p].id) { // Condiciï¿½n para que no se repita la misma id despuï¿½s del cambio
	    			fwrite(&cli[j], sizeof(struct cliente), 1, temp);
	    		}
	    		j++;
	    	}
	    	fclose(fp);
			fclose(temp);
			gotoxy(10,y);
			y++;
			remove("src/clientes.txt");
		    rename("src/temporal.txt", "src/clientes.txt");
	    	printf("%cCliente `%i` dado de baja exitosamente!", 173, cli[p].id);
	    	getch();
	    	break;
		}
		fclose(fp);
		fclose(temp);
	}
	guardarArchivoCliente(cli);
	return y;
}

int desactivadorEntReg(int idDesactivada, int y) {
	
}

int desactivadorCliReg(int idDesactivada, int y) {
	
}


// <=== VALIDADORES ===>
// <=== VALIDADORES ===>
// <=== VALIDADORES ===>


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

void valitext(int lon, char *pnom){
	int c=0, x=0;
    do{
		c=getch();
        if((x == 0) && c>=65 && c<=90 || c>=97 && c<=122 || c==32 || c == 130 || c >= 160 && c <= 165 || c == 181 || c == 144 || c == 214 || c == 224 || c == 233) {
			if (x == 0 && (c == 130 || c >= 160 &&  c <= 164)) {
				switch (c) {
					case 160:
						c = 181;
						break;
					case 130:
						c = 144;
						break;
					case 161:
						c = 214;
						break;
					case 162:
						c = 224;
						break;
					case 163:
						c = 233;
						break;
					case 164:
						c = 165;
						break;
				}
			}
			if (x == 0) {
				c = toupper(c);
				printf("%c",c);
            	*(pnom+x)=c;
         		x++;
        	}
        	else {
        		c = tolower(c);
				printf("%c",c);
            	*(pnom+x)=c;
         		x++;
			}
		}	
        if(c==8 && x>0){
			x--;
		    printf("\b \b");
	        *(pnom+x)=' ';
        }
    }while(c!=13 && x<lon);
    /* *(pnom+0) = toupper(*(pnom+0));
    for (x = 1; x < lon; x++)
    	*(pnom+x) = tolower(*(pnom+x));*/
    *(pnom+x)= NULL;
}

void valiDireccion(int lon, char *pnom){
	int c=0, x=0;
    do{
		c=getch();
        if(c>=65 && c<=90 || c>=97 && c<=122 || c==32 || c == 130 || c >= 160 && c <= 165 || c == 181 || c == 144 || c == 214 || c == 224 || c == 233 || c == 35){
			if (x == 0 && (c == 130 || c >= 160 &&  c <= 164)) {
				switch (c) {
					case 160:
						c = 181;
						break;
					case 130:
						c = 144;
						break;
					case 161:
						c = 214;
						break;
					case 162:
						c = 224;
						break;
					case 163:
						c = 233;
						break;
					case 164:
						c = 165;
						break;
				}
			}
			if (x == 0) {
				c = toupper(c);
				printf("%c",c);
            	*(pnom+x)=c;
         		x++;
        	}
        	else {
        		c = tolower(c);
				printf("%c",c);
            	*(pnom+x)=c;
         		x++;
			}
		}
		if ((x == 0 || x == 1) && c == 35) {
			x--;
		    printf("\b \b");
	        *(pnom+x)=' ';
		}
        if(c==8 && x>0){
			x--;
		    printf("\b \b");
	        *(pnom+x)=' ';
        }
    }while(c!=13 && x<lon);
    *(pnom+x)= NULL;
}

void valiDescripcion(int lon, char *pnom){
	int c=0, x=0;
    do{
		c=getch();
        if(c>=32 && c<=126 || c == 130 || c >= 160 && c <= 165 || c == 181 || c == 144 || c == 214 || c == 224 || c == 233){
			if (x == 0 && (c == 130 || c >= 160 &&  c <= 164)) {
				switch (c) {
					case 160:
						c = 181;
						break;
					case 130:
						c = 144;
						break;
					case 161:
						c = 214;
						break;
					case 162:
						c = 224;
						break;
					case 163:
						c = 233;
						break;
					case 164:
						c = 165;
						break;
				}
			}
			if (x == 0) {
				c = toupper(c);
				printf("%c",c);
            	*(pnom+x)=c;
         		x++;
        	}
        	else {
        		c = tolower(c);
				printf("%c",c);
            	*(pnom+x)=c;
         		x++;
			}
		}	
        if(c==8 && x>0){
			x--;
		    printf("\b \b");
	        *(pnom+x)=' ';
        }
    }while(c!=13 && x<lon);
    *(pnom+x)= NULL;
}

void valiTurno(int lon, char *pnom) {
	int condition = 0;
	do {
		valitext(lon, pnom);
		int length = strlen(pnom);
		if(strcmp(pnom, "Mixto") == 0 || strcmp(pnom, "Matutino") == 0 || strcmp(pnom, "Vespertino") == 0 || strcmp(pnom, "Nocturno") == 0)
			condition = 1;
		if (condition == 0) {
			for (int x = 0; x < length; x++) {
				printf("\b \b");
				*(pnom+x) = ' ';
			}	
		}
	} while (condition == 0);
}

void valiTelefono(char *pnom, int length) {
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

char autoOrManual(int length) {
	char car, option;
	do {
		car = getch();
		option = toupper(car);
		switch (option) {
			case 65:
				printf("%c", option);
				return 'A';
				break;
			case 77:
				printf("%c", option);
				return 'M';
				break;
			default:
				break;
		} 
	} while(option != 65 || option != 77);
}

// <=== EXTRAS ===>

void gotoxy(int x,int y) {
        COORD c;
        c.X=x;
        c.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
