/*
Nombre del programa: Batalla naval
Fecha: 
Programado por: Raúl Alberto Kumul Várguez y Luis Fernando Kumul Várguez
*/
#include <stdio.h>
#include <time.h>
#include <conio.h>     //Para funcion getch
#include <windows.h>   //Para la funcion gotoXY
#include <stdbool.h>   //Para funciones booleana s
//Flechas del teclado
#define tecla_arriba 72 
#define tecla_abajo 80
#define tecla_izquierda 75
#define tecla_derecha 77
#define enter 13
#define space 32
//Formato de colores
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define WHITE "\033[1;37m"
#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define RESET "\033[1;0m"
//fondo
#define FONDCYAN "\033[46;1m"
#define FONDGREEN "\033[42;1m"
#define FONDRESET "\033[0m"
//Centrado del juego
#define Xc 0 //columna
#define Yc 0 //fila
//funciones
void main_menu();
void game1();
void WriteResult();
void board();
void bannerGetName();
void bannerDisplayName();
void bannerStarGame();
void bannerComingSoon();
void Saveresult();

int gotoXY(int columna, int fila){
	COORD coord; 
	coord.X=columna;
	coord.Y=fila;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
	return 0;
}

int main() {
	unsigned int opc=1;
	do{
		bool repeat=true;
		system("CLS");
		main_menu(Xc,Yc);
		do{
			gotoXY(6+Xc,11+Yc+opc);//flechita 
			printf(RED"==>"RESET);
			//movimiento de la flechita
			int tecla=getch();
			gotoXY(6+Xc,11+Yc+opc);
			printf(RED"   "RESET);
			switch(tecla){
			case tecla_arriba:
				opc--;
				if(opc<1)
					opc=4;
				break;
			case tecla_abajo:
				opc++;
				if(opc>4)
					opc=1;
				break;
			case enter:
				repeat=false;
			}
			
		}while(repeat);
		switch(opc){
		case 1:
			system("CLS");
			game1(6+Xc,0+Yc);
			break;
		case 2:
			system("CLS");
			// game2(0+Xc,0+Yc);
			bannerComingSoon(5,3);
			system("PAUSE");
			break;
		case 3:
			system("CLS");
			WriteResult();
			printf("\n");
			system("PAUSE");
			break;
		case 4:
			system("CLS");
			break;
		}
	} while(opc!=4);
	return 0;
}
///Sistema
void game1(int x, int y){
	char player1[10], player2[10];
	int p1b[10][10]={0}, p2b[10][10]={0};
	int hit1[10][10]={0}, hit2[10][10]={0};
	///Jugador 1 acomoda
	system("CLS");//get name
	bannerGetName(x,y+5,1);
	gotoXY(x+28,y+7);
	scanf("%s", player1);
	system("CLS");//empieza el acomodo
	bannerDisplayName(x,y,1,player1);
	board(x+1, y+5);
	int pz=7;
	for (int i = 0; i < 21; i+=3)//7 barcos
	{
		gotoXY(x+30,y+2);printf(RED"%i"RESET, pz);
		bool repeat=true;
		int p=6+x, o=7+y;
		int m=p,n=o,a=p,b=o+2,c=p,d=o+4;
		do{
			gotoXY(m-1,n);printf(RED"[");
			gotoXY(m+1,n);printf(RED"]");
			gotoXY(a-1,b);printf(RED"[");
			gotoXY(a+1,b);printf(RED"]");
			gotoXY(c-1,d);printf(RED"[");
			gotoXY(c+1,d);printf(RED"]"RESET);
			//
			int tecla=getch();
			gotoXY(m-1,n);printf(RED" ");
			gotoXY(m+1,n);printf(RED" ");
			gotoXY(a-1,b);printf(RED" ");
			gotoXY(a+1,b);printf(RED" ");
			gotoXY(c-1,d);printf(RED" ");
			gotoXY(c+1,d);printf(RED" "RESET);

			if(tecla==tecla_arriba && n>=o+2 && b>=o+2 && d>=o+2){
				n-=2;b-=2;d-=2;
			}
			else if(tecla==tecla_abajo && n<=o+16 && b<=o+16 && d<=o+16){
				n+=2;b+=2;d+=2;
			}
			else if(tecla==tecla_derecha && m<=p+32 && a<=p+32 && c<=p+32){
				m+=4;a+=4;c+=4;
			}
			else if(tecla==tecla_izquierda && m>=p+3 && a>=p+3 && c>=p+3){
				m-=4;a-=4;c-=4;
			}
			else if(tecla==enter){	
				if (p1b[(n-o)/2][(m-p)/4]==0 && p1b[(b-o)/2][(a-p)/4]==0 && p1b[(d-o)/2][(c-p)/4]==0)
				{
					gotoXY(m,n);
					printf(RED"x"RESET);
					gotoXY(a,b);
					printf(RED"x"RESET);
					gotoXY(c,d);
					printf(RED"x"RESET);
					p1b[(n-o)/2][(m-p)/4]=1;
					p1b[(b-o)/2][(a-p)/4]=1;
					p1b[(d-o)/2][(c-p)/4]=1;
					repeat=false;
				}
			}
		}while(repeat);
		pz--;
	}
	///Jugador 2 acomoda
	system("CLS");//get name
	bannerGetName(x,y+5,2);
	gotoXY(x+28,y+7);
	scanf("%s", player2);
	system("CLS");//empieza el acomodo
	bannerDisplayName(x,y,2,player2);
	board(x+1, y+5);
	pz=7;
	for (int i = 0; i < 21; i+=3)//7 barcos
	{
		gotoXY(x+30,y+2);printf(RED"%i"RESET, pz);
		bool repeat=true;
		int p=6+x, o=7+y;
		int m=p,n=o,a=p,b=o+2,c=p,d=o+4;
		do{
			gotoXY(m-1,n);printf(RED"[");
			gotoXY(m+1,n);printf(RED"]");
			gotoXY(a-1,b);printf(RED"[");
			gotoXY(a+1,b);printf(RED"]");
			gotoXY(c-1,d);printf(RED"[");
			gotoXY(c+1,d);printf(RED"]"RESET);
			//
			int tecla=getch();
			gotoXY(m-1,n);printf(RED" ");
			gotoXY(m+1,n);printf(RED" ");
			gotoXY(a-1,b);printf(RED" ");
			gotoXY(a+1,b);printf(RED" ");
			gotoXY(c-1,d);printf(RED" ");
			gotoXY(c+1,d);printf(RED" "RESET);

			if(tecla==tecla_arriba && n>=o+2 && b>=o+2 && d>=o+2){
				n-=2;b-=2;d-=2;
			}
			else if(tecla==tecla_abajo && n<=o+16 && b<=o+16 && d<=o+16){
				n+=2;b+=2;d+=2;
			}
			else if(tecla==tecla_derecha && m<=p+32 && a<=p+32 && c<=p+32){
				m+=4;a+=4;c+=4;
			}
			else if(tecla==tecla_izquierda && m>=p+3 && a>=p+3 && c>=p+3){
				m-=4;a-=4;c-=4;
			}
			else if(tecla==enter){
				if (p2b[(n-o)/2][(m-p)/4]==0 && p2b[(b-o)/2][(a-p)/4]==0 && p2b[(d-o)/2][(c-p)/4]==0)
				{
					gotoXY(m,n);
					printf(RED"x"RESET);
					gotoXY(a,b);
					printf(RED"x"RESET);
					gotoXY(c,d);
					printf(RED"x"RESET);
					p2b[(n-o)/2][(m-p)/4]=1;
					p2b[(b-o)/2][(a-p)/4]=1;
					p2b[(d-o)/2][(c-p)/4]=1;
					repeat=false;
				}
	
			}
		}while(repeat);
		pz--;
	}
	///Inicia el combate
	system("CLS");//Comienza juego
	bannerStarGame(x,y+5);
	system("PAUSE");
	system("CLS");
	gotoXY(17+x,0+y);printf(RED"Jugador Uno"RESET);
	gotoXY(11+x,1+y);printf(RED"Ataca mapa de jugador 2"RESET);
	board(1+x,2+y);
	gotoXY(65+x,0+y);printf(RED"Jugador Dos"RESET);
	gotoXY(59+x,1+y);printf(RED"Ataca mapa de jugador 1"RESET);
	board(49+x,2+y);
	int lmx=x, lmy=y+4;
	int turn=1;
	int c1=21,c2=21;
	gotoXY(59+23+x,1+y);
	printf("%i",c2);
	gotoXY(11+23+x,1+y);
	printf("%i",c2);
	bool win=true;
	while(win){
		if(turn%2==0)
				lmx=x+54;
			else
				lmx=x+6;
		bool repeat=true;
		int m=lmx,n=lmy;
		do{
			gotoXY(m-1,n);printf(RED"[");
			gotoXY(m+1,n);printf(RED"]"RESET);
			;
			//
			int tecla=getch();
			gotoXY(m-1,n);printf(RED" ");
			gotoXY(m+1,n);printf(RED" "RESET);

			if(tecla==tecla_arriba && n>=lmy+2)
				n-=2;
			else if(tecla==tecla_abajo && n<=lmy+16)
				n+=2;
			else if(tecla==tecla_derecha && m<=lmx+32)
				m+=4;
			else if(tecla==tecla_izquierda && m>=lmx+3)
				m-=4;
			else if(tecla==enter){	
				if(turn%2==0){
					if(p1b[(n-lmy)/2][(m-lmx)/4]==1 && hit1[(n-lmy)/2][(m-lmx)/4]!=1){
						gotoXY(m,n);
						printf(RED"X"RESET);
						hit1[(n-lmy)/2][(m-lmx)/4]=1;
						c1--;
						if(c1==0)
							win=false;
						// gotoXY(59+23+x,1+y);
						// printf("%i",c1);
					}
					else if(p1b[(n-lmy)/2][(m-lmx)/4]==0 && hit1[(n-lmy)/2][(m-lmx)/4]!=1){
						gotoXY(m,n);
						printf(BLUE"o"RESET);
					}
				}
				else{
					if(p2b[(n-lmy)/2][(m-lmx)/4]==1 && hit2[(n-lmy)/2][(m-lmx)/4]!=1){
						gotoXY(m,n);
						printf(RED"X"RESET);
						hit2[(n-lmy)/2][(m-lmx)/4]=1;
						c2--;
						if(c2==0)
							win=false;
						// gotoXY(11+23+x,1+y);
						// printf("%i",c2);
					}
					else if(p2b[(n-lmy)/2][(m-lmx)/4]==0 && hit2[(n-lmy)/2][(m-lmx)/4]!=1){
						gotoXY(m,n);
						printf(BLUE"o"RESET);
					}
				}
				repeat=false;
			}
		}while(repeat);
		turn++;
	}	
	if(c2==0){

		gotoXY(x,y+25);printf(GREEN" _____________________________________________\n");
		gotoXY(x,y+26);printf(GREEN"|                                             |\n");
		gotoXY(x,y+27);printf(GREEN"|"YELLOW"           ¡Ha terminado el juego!           "GREEN"|\n");
		gotoXY(x,y+28);printf(GREEN"|           Jugador uno ha ganado             |\n"RESET);
		gotoXY(x,y+29);printf(GREEN"|_____________________________________________|\n"RESET);
		time_t t = time(NULL);
		struct tm tiempoLocal = *localtime(&t);
		char date[70];
		char *formato = "%Y/%m/%d--%H:%M:%S";
		int byteswrite = strftime(date, sizeof date, formato, &tiempoLocal);
		///Llamado de la funcion
		Saveresult(player1,player2,40-(27-c1),40-(27-c2),player1,date);
		/*
		nombre del archivo: "results.txt"
		Datos que debe contener el archivo:
		-Jugador uno y puntos
		-jugador dos y puntos
		-ganador y fecha
		*/
	}
	else if(c1==0){
		gotoXY(x,y+25);printf(GREEN" _____________________________________________\n");
		gotoXY(x,y+26);printf(GREEN"|                                             |\n");
		gotoXY(x,y+27);printf(GREEN"|"YELLOW"           ¡Ha terminado el juego!           "GREEN"|\n");
		gotoXY(x,y+28);printf(GREEN"|           Jugador dos ha ganado             |\n"RESET);
		gotoXY(x,y+29);printf(GREEN"|_____________________________________________|\n"RESET);
		time_t t = time(NULL);
		struct tm tiempoLocal = *localtime(&t);
		char date[70];
		char *formato = "%Y/%m/%d--%H:%M:%S";
		int byteswrite = strftime(date, sizeof date, formato, &tiempoLocal);
		///Llamado de la funcion
		Saveresult(player1,player2,40-(27-c1),40-(27-c2),player2,date);
	}
}
void WriteResult(){
	char player1[10];
	char player2[10];
	int pts1,pts2;
	char winner[10];
	char date[70];
	int i=0;
	
	FILE *cfPtr;
	
	if ((cfPtr=fopen("results.txt","r")) == NULL ) {
		puts( "Error. Imposible abrir archivo.");
	}
	else {
		
		printf(GREEN"||   Jugador 1   ||Puntución 1||   Jugador 2   ||Puntución 2||   Ganador   ||        Fecha        ||\n");
		printf(RED"=========================================================================================================n"GREEN);
		fscanf(cfPtr,"%s %d %s %d %s %s",player1,&pts1,player2,&pts2,winner,date);
		while (!feof(cfPtr)) {
			//printf(" %s %d %s %d %s %s\n",player1,pts1,player2,pts2,winner,date);
			gotoXY(0,2+i);
			printf("||     %s",player1);
			gotoXY(17,2+i);
			printf("||");
			gotoXY(22,2+i);
			printf("%d",pts1);
			gotoXY(30,2+i);
			printf("||");
			gotoXY(37,2+i);
			printf("%s",player2);
			gotoXY(47,2+i);
			printf("||");
			gotoXY(53,2+i);
			printf("%d",pts2);
			gotoXY(60,2+i);
			printf("||");
			gotoXY(66,2+i);
			printf("%s",winner);
			gotoXY(75,2+i);
			printf("||");
			gotoXY(77,2+i);
			printf("%s",date);
			gotoXY(98,2+i);
			printf("||");
			i++;
			fscanf(cfPtr,"%s %d %s %d %s %s",player1,&pts1,player2,&pts2,winner,date);
		}
		fclose(cfPtr);
	}
	
}
///Modulos-CARTELES
void main_menu(int x, int y){
	system("CLS");
	//BANNER
	gotoXY(x,y);printf(RED"      ____	"RESET);
	gotoXY(x,y+1);printf(RED"     |  _ \\"YELLOW"  _       _   _   _           _     _      ");
	gotoXY(x,y+2);printf(RED"     | |_) )"YELLOW"| | __ _| |_| |_| | ___  ___| |__ (_)____   ");
	gotoXY(x,y+3);printf(RED"     |  _ /"YELLOW" | |/ _` | __| __| |/ _ \\/ __|  _ \\| |  _ \\      ");
	gotoXY(x,y+4);printf(RED"     | |_)\\"YELLOW" | | (_| | |_| |_| |  __/\\__ \\ | | | | |_) |       ");
	gotoXY(x,y+5);printf(RED"     |____/"YELLOW" |_|\\__,_|\\__|\\__|_|\\___||___/_| |_|_|  __/      "RESET);
	gotoXY(x,y+6);printf(YELLOW"                                                |_|"RESET);
	gotoXY(x,y+8);printf(WHITE"   }"RED"----------------------------------------------------"WHITE"{");
	gotoXY(x,y+9);printf(WHITE"}"RED"--------------------------"GREEN" MENU "RED"--------------------------"WHITE"{");
	gotoXY(x,y+10);printf(WHITE"   }"RED"----------------------------------------------------"WHITE"{");
	//Opciones
	gotoXY(x+10,y+12);printf(GREEN"["WHITE" 1 "GREEN"]"YELLOW" Jugador contra Jugador");
	gotoXY(x+10,y+13);printf(GREEN"["WHITE" 2 "GREEN"]"YELLOW" Jugador contra Máquina (Próximamente)");
	gotoXY(x+10,y+14);printf(GREEN"["WHITE" 3 "GREEN"]"YELLOW" Resultados");
	gotoXY(x+10,y+15);printf(GREEN"["WHITE" 4 "GREEN"]"YELLOW" Salir del juego"RESET);
}
void board(int x, int y){
	gotoXY(x,y);printf(FONDGREEN"     A   B   C   D   E   F   G   H   I   J   \n"FONDRESET);
	gotoXY(x,y+1);printf(FONDGREEN"  "FONDRESET YELLOW"===========================================\n");
	gotoXY(x,y+2);printf(RESET FONDGREEN"1 "FONDRESET YELLOW"||   |   |   |   |   |   |   |   |   |   ||\n");
	gotoXY(x,y+3);printf(FONDGREEN"  "FONDRESET YELLOW"||---------------------------------------||\n");
	gotoXY(x,y+4);printf(RESET FONDGREEN"2 "FONDRESET YELLOW"||   |   |   |   |   |   |   |   |   |   ||\n");
	gotoXY(x,y+5);printf(FONDGREEN"  "FONDRESET YELLOW"||---------------------------------------||\n");
	gotoXY(x,y+6);printf(RESET FONDGREEN"3 "FONDRESET YELLOW"||   |   |   |   |   |   |   |   |   |   ||\n");
	gotoXY(x,y+7);printf(FONDGREEN"  "FONDRESET YELLOW"||---------------------------------------||\n");
	gotoXY(x,y+8);printf(RESET FONDGREEN"4 "FONDRESET YELLOW"||   |   |   |   |   |   |   |   |   |   ||\n");
	gotoXY(x,y+9);printf(FONDGREEN"  "FONDRESET YELLOW"||---------------------------------------||\n");
	gotoXY(x,y+10);printf(RESET FONDGREEN"5 "FONDRESET YELLOW"||   |   |   |   |   |   |   |   |   |   ||\n");
	gotoXY(x,y+11);printf(FONDGREEN"  "FONDRESET YELLOW"||---------------------------------------||\n");
	gotoXY(x,y+12);printf(RESET FONDGREEN"6 "FONDRESET YELLOW"||   |   |   |   |   |   |   |   |   |   ||\n");
	gotoXY(x,y+13);printf(FONDGREEN"  "FONDRESET YELLOW"||---------------------------------------||\n");
	gotoXY(x,y+14);printf(RESET FONDGREEN"7 "FONDRESET YELLOW"||   |   |   |   |   |   |   |   |   |   ||\n");
	gotoXY(x,y+15);printf(FONDGREEN"  "FONDRESET YELLOW"||---------------------------------------||\n");
	gotoXY(x,y+16);printf(RESET FONDGREEN"8 "FONDRESET YELLOW"||   |   |   |   |   |   |   |   |   |   ||\n");
	gotoXY(x,y+17);printf(FONDGREEN"  "FONDRESET YELLOW"||---------------------------------------||\n");
	gotoXY(x,y+18);printf(RESET FONDGREEN"9 "FONDRESET YELLOW"||   |   |   |   |   |   |   |   |   |   ||\n");
	gotoXY(x,y+19);printf(FONDGREEN"  "FONDRESET YELLOW"||---------------------------------------||\n");
	gotoXY(x,y+20);printf(RESET FONDGREEN"10"FONDRESET YELLOW"||   |   |   |   |   |   |   |   |   |   ||\n");
	gotoXY(x,y+21);printf(FONDGREEN"  "FONDRESET YELLOW"===========================================\n"RESET);
}
void bannerGetName(int x,int y, int player){
	gotoXY(x,y);printf(GREEN" ______________________________________________\n");
	gotoXY(x,y+1);printf(GREEN"|"YELLOW"Turno del jugador %i de acomodar sus piezas    "GREEN"|\n", player);
	gotoXY(x,y+2);printf(GREEN"|"YELLOW"Ingrese nombre del jugador:"RED"xxxxxxxxxx"GREEN"         |\n");
	gotoXY(x,y+3);printf(GREEN"|______________________________________________|\n");
}
void bannerDisplayName(int x,int y, int player, char name[10]){
	gotoXY(x,y);printf(GREEN" _____________________________________________\n");
	gotoXY(x,y+1);printf(GREEN"|"YELLOW"Turno del jugador %i de acomodar sus piezas   "GREEN"|\n", player);
	gotoXY(x,y+2);printf(GREEN"|"YELLOW"Jugador:              Quedan:"GREEN"                |\n");
	gotoXY(x,y+3);printf(GREEN"|_____________________________________________|\n");
	gotoXY(x+10,y+2);printf(RED"%s"RESET, name);//nombre del jugador
}
void bannerStarGame(int x, int y){
	gotoXY(x,y);printf(GREEN" _____________________________________________\n");
	gotoXY(x,y+1);printf(GREEN"|                                             |\n");
	gotoXY(x,y+2);printf(GREEN"|"YELLOW"           ¡Qué comience el juego!           "GREEN"|\n");
	gotoXY(x,y+3);printf(GREEN"|_____________________________________________|\n"RESET);
}
void bannerComingSoon(int x,int y){
	//system("CLS");
	gotoXY(x,y);printf(GREEN" _____________________________________________\n");
	gotoXY(x,y+1);printf(GREEN"|"YELLOW"     Este modo de juego está en desarrollo"GREEN"   |\n");
	gotoXY(x,y+2);printf(GREEN"|"YELLOW"     > > > Disponible el proximo mes < < <"GREEN"   |\n");
	gotoXY(x,y+3);printf(GREEN"|_____________________________________________|\n"RESET);
}
void Saveresult (char player1[10],char player2[10],int pts1,int pts2,char winner[10],char date[70]){
	FILE *fapt;
	if ((fapt = fopen("results.txt", "a")) != NULL) {
		fprintf(fapt,"%s %d %s %d %s %s\n",player1,pts1,player2,pts2,winner,date);
		
		fclose(fapt);
	}
	printf("Archivo guardado\n");
	system("PAUSE");
}
