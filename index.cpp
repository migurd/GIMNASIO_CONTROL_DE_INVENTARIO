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
	char correo[20];
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
	char correo[20];
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
				addEntrenador();
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

void addEntrenador() {
	FILE *fp;
	char condition;
	int i;
	if (fp == NULL) {
		gotoxy(10, 5);
		printf("No se pudo abrir el archivo");
		exit(1);
	}
	for (i = 0; i < 10; i++)
		if (ent[i].id==NULL)
			break;
	if (i < 10) {
		do {
			system("cls");
			fp = fopen("./src/entrenadores.txt", "a");
			printf("\t\t\t\t\t======\tA%cadir entrenador\t======\n\n", 164);
			printf("\t\t\t\t\tID: %i", i);
			ent[i].id = i;
			getch();
			printf("\n\t\t\t\t\tEspecialidad: ");
			valitext(15, ent[i].especialidad);
			printf("\n\t\t\t\t\tPrimer nombre: ");
			valitext(15, ent[i].primerNombre);
			printf("\n\t\t\t\t\tSegundo nombre: ");
			valitext(15, ent[i].segundoNombre);
			printf("\n\t\t\t\t\tApellido paterno: ");
			valitext(15, ent[i].apellidoPaterno);
			printf("\n\t\t\t\t\tApellido materno: ");
			valitext(15, ent[i].apellidoMaterno);
			printf("\n\t\t\t\t\tTel%cfono: ", 130);
			nument(10);
			printf("\n\t\t\t\t\tCorreo: ");
			scanf("%s", &ent[i].correo);
			printf("\t\t\t\t\tDirecci%cn: ", 162);
			valitext(20, ent[i].direccion);
			printf("\n\t\t\t\t\tTurno: ");
			valitext(11, ent[i].turno);
			
			fwrite(&ent, sizeof(struct entrenador), 10, fp);
			fclose(fp);
			
			printf("\t\t\t\t\t%cA%cadir otro entrenador? (y/n) ", 168, 164);
			scanf("%s", &condition);
		} while(condition == 'y' || condition == 'Y');
	}
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
		exit(2);
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
