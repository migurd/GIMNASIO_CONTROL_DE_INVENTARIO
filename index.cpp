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
	char telefono[11];
	char direccion[20];
	char turno[11];
} ent[10]; // Usaremos las 3 primeras letras para todas las estructuras

struct servicios {
	int id;
	char servicio[20];
	char* idInstructor;
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
	char telefono[11];
	char direccion[20];
	char turno[11];
	int idRegistro;
	int idServicios;
} cli[10];

void gotoxy(int x,int y);

void menu();
void menuEntrenador();
void menuServicios();
void menuRegistro();
void menuCliente();

void addEntrenador();
void addServicios(int idEntrenador);
void addCliente(int idEntrenador, int idServicio);

void consultarEntrenador();
void consultarEntrenadorGeneral();

int nument(int lon);
void valitext(int lon,char *pnom);
void valifec(char *pfecha);

int main() {
	menu();
	return 0;
}

void menu() {
	int option = 0;
	
	do {
		system("cls");
		gotoxy(40, 5);
		printf("======\tMen%c principal\t======\n\n", 163);
		gotoxy(40, 8);
		printf("1. Men%c entrenador\n", 163);
		gotoxy(40, 9);
		printf("2. Men%c servicios\n", 163);
		gotoxy(40, 10);
		printf("3. Men%c registro\n", 163);
		gotoxy(40, 11);
		printf("4. Men%c cliente\n", 163);
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
		gotoxy(40, 5);
		printf("======\tMen%c entrenador\t======\n\n", 163);
		gotoxy(40, 8);
		printf("1. Agregar\n", 163);
		gotoxy(40, 9);
		printf("2. Consultar\n", 163);
		gotoxy(40, 10);
		printf("3. Modificar\n", 163);
		gotoxy(40, 11);
		printf("4. Eliminar\n", 163);
		gotoxy(40, 12);
		printf("5. Regresar\n\n\n", 163);
		
		gotoxy(44, 15);
		printf("> > Elige una opci%cn: ", 162);
		option = nument(1);
		
		switch (option) {
			case 1:
				addEntrenador();
				break;
			case 2:
				consultarEntrenadorGeneral();
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
				printf("Opci%cn inv%clida. Elige de nuevo.", 162, 160);
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
		
		printf("> > Elige una opci%cn: ", 162);
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
				printf("Opci%cn inv%clida. Elige de nuevo.", 162, 160);
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
		printf("======\tMen%c cliente\t======\n\n", 163);
		printf("1. Agregar\n", 163);
		printf("2. Consultar\n", 163);
		printf("3. Modificar\n", 163);
		printf("4. Eliminar\n", 163);
		printf("5. Regresar\n\n\n", 163);
		
		printf("> > Elige una opci%cn: ", 162);
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
				printf("Opci%cn inv%clida. Elige de nuevo.", 162, 160);
				Sleep(300);
				break;
		}
	} while (option != 5);
}

void addEntrenador() {
	FILE *fp;
	char condition;
	int i;
		for (i = 0; i < 10; i++)
		if (ent[i].id==NULL)
			break;
	if (fp == NULL) {
		gotoxy(10, 5);
		printf("No se pudo abrir el archivo");
		exit(1);
	}
//		do {
		system("cls");
		fp = fopen("./src/entrenadores.txt", "ab+");
		gotoxy(40, 5);
		printf("========\tA%cadir entrenador\t========", 164);
		gotoxy(40, 8);
		printf("ID: ");
		scanf("%i", &ent[i].id);
		fflush(stdin); // Para eliminar el output bugeado cuando se mezcla scanf y gets
		gotoxy(40, 9);
		printf("Especialidad: ");
		gets(ent[i].especialidad);
		gotoxy(40, 10);
		printf("Primer nombre: ");
		gets(ent[i].primerNombre);
		gotoxy(40, 11);
		printf("Segundo nombre: ");
		gets(ent[i].primerNombre);
		gotoxy(40, 12);
		printf("Apellido paterno: ");
		gets(ent[i].apellidoPaterno);
		gotoxy(40, 13);
		printf("Apellido materno: ");
		gets(ent[i].apellidoMaterno);
		gotoxy(40, 14);
		printf("Tel%cfono: ", 130);
		gets(ent[i].telefono);
		gotoxy(40, 15);
		printf("Direcci%cn: ", 162);
		gets(ent[i].direccion);
		gotoxy(40, 16);
		printf("Turno: ");
		gets(ent[i].turno);
		
		fwrite(&ent, sizeof(ent), 1, fp);
		fclose(fp);
}

void consultarEntrenador() {
	
}

void consultarEntrenadorGeneral() {
	system("cls");
	int i;
	gotoxy(40, 1);
	printf("==== Datos generales de entrenadores ====");
	gotoxy(5, 8);
	printf("ID  | Especialidad | Primer nombre | Segundo nombre | Apellido Paterno | Apellido Materno | Telefono | Direccion |  Turno | ");
	gotoxy(5,10);
	for (i = 0; ent[i].id != NULL; i++)
	{
		
	}
	getch();
}

void addCliente(int idEntrenador, int idServicio) {
	
}
void addservicios() {
	FILE *fp;
	char cd;
	int i;
	if (fp == NULL) {
		gotoxy(10, 5);
		printf("No se pudo abrir el archivo");
		exit(1);
	}
	for (i = 0; i < 10; i++)
		if (ser[i].id==NULL)
			break;
	if (i < 10) {
		do {
			system("cls");
			fp = fopen("./src/Servicios.txt", "a");
			printf("\t\t\t\t\t======\tA%cadir otro servicio\t======\n\n", 164);
			printf("\t\t\t\t\tID: %i", i);
			ser[i].id = i;
			getch();
			printf("\n\t\t\t\t\tServicios: ");
			valitext(15, ser[i].servicio);
			printf("\n\t\t\t\t\tId del Instructor: ");
			valitext(15, ser[i].idInstructor);
			printf("\n\t\t\t\t\tRutina: ");
			valitext(15, ser[i].rutina);
			
			fwrite(&ser, sizeof(struct servicios), 10, fp);
			fclose(fp);
			
			printf("\t\t\t\t\t%cA%cadir otro servicio? (y/n) ", 168, 164);
			scanf("%s", &cd);
		} while(cd == 'y' || cd == 'Y');
	}
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

void valitext(int lon,char *pnom){
	int c=0, x=0;
    do{
		c=getch();
        if(c>=65 && c<=90 || c>=97 && c<=122 || c==32 || c==164 || c==165){
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
    *(pnom+x)='\n';
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

void gotoxy(int x,int y) {
        COORD c;
        c.X=x;
        c.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
