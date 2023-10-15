#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>
#define t 29		//tamaño del mapa
#define t_in 4
#define max 30
#define tiempo 0	//delay (inversamente proporcional a la velocidad)

// estructura del cuerpo y cabeza
struct cuerpo{
	int x,y;
};

// estructura de la fruta
struct fruta{
	int x, y;
};

void imprimir(char espacio[t][t], int *puntaje);
void generar(char espacio[t][t]);
void spawn(char espacio[t][t], struct cuerpo *snake);
char direccion(char espacio[t][t], struct cuerpo *snake, char letra, int *muerto, char ult, int tam);
void guardar_puntaje(char nombre[20], int puntaje);

int main(int argc, char *argv[]) {
	srand(time(NULL));

	struct cuerpo snake[max];
	char letra='w', ult='w', espacio[t][t], nombre[20];
	int muerto=0, puntaje=0, dif=0, cambio=0, auxx2=0, auxy2=0;
	int auxx=0, auxy=0;		//para modificar el tamaño de la snake
	int tam = t_in;			//tamaño inicial de la matriz
	
    // genero la matriz del mapa con los bordes
	generar(espacio);	
    // creo la vivorita
	spawn(espacio, snake);
	
    // genera la primera manzana
	struct fruta manzana;
	manzana.x = 1 + rand() % (t - 2);
	manzana.y = 1 + rand() % (t - 2);
	espacio[manzana.x][manzana.y] = '#';
				
	while (kbhit() != 1)
	{
        // imprime el menu
		printf("\n\n                         ....              ...::...                                                 \n                     ..::.......       ..:,::,,,,,::.                                               \n                ....::c;,::::,,;,::::,;;,,,:odxdlc:;::....                                          \n            ..::::::,:..::.....::..:;;,.,d00k0XKOkdd:.,;:.:::..                                     \n            :::;,,,,,;;;;:c;:......:;..:ONO;.c0XXK0Ol..,...::,:....                                 \n           .,cl:,;:.......::::,.......,dKXl..:OXXXX0l:..........:,,:.....                           \n           .,cc:;,.......,;;;,,.......,o0d...dKX0kl::..............:,,:::...                       \n              .::::,......,;,;..::.......:o:::xko;....::.::::........::..,;,:..                     \n                .,lc;;;,:.,;;;....... ............::::,;;;,:..:........:....,;:..                   \n                 .lc...:cll;;c;,,:............:;;:c::;::....::...............:,;:.                  \n                 .:l.   ;xl:,;.:,,,,,;;;;;;;:ll:,,,,:....,,:::..................;,.                 \n                  :l.   ,xc:;:.....;ccccllc::;........,;;::cll:::,..............:::.                \n                  .:,   ,o,:;...::lodool:;:.....,,,,,:oddxkkkddxkxol,............;;.                \n                  .:;   :;.;;.::odollc;......:,,,:....:ldxxxkkkkOOkOx;...........,;.                \n                 ..,.. .:.::;:oolll:,...:;,:::..  .    .,xOkkkkkkxxkkd;....:.....:,.                \n                 ...   ::.:llocllc,..,,,,...   .         :lxkkkxxxxxddd;.........;;.                \n                      .:.cdolccc;,,:::.                   .lOOOOOkdooodc:.......::,.                \n   ...              .:,,;clllc:,::..                       :dkxddddoodxo,.......;:.                 \n   ..:.         ...:;;,:. .....                            .:xxxxxxdoooc........:.                  \n    ..:.......:,;:;,:..                                    .:kxdddddddo,.......;;.                  \n      ..:,,;;,,::...                                       .lxdddooloo:.......;;.                   \n                                                          .;kxdoooooo:.......;,.                    \n                                                         .;okkxddool,......,;,..                    \n                                                       .,lxxxdoolc;.......,;..;. .                  \n                                                   ..::ldxxdoooc;........,,. .;;:..     .           \n                                              ..,;:coddoodocc;.........:,:. . :lc,:....  .          \n                                        ..:,;:lllllllllc;;;:.........:,:.     ..cc:,::.....         \n                                   ..:,;cloooolc::::;:............,,,:.         ..;ll;...:::..      \n                              ..:;;;:loollcc:;,:................;:,..              .cd;....:;,.     \n                  .........:;::cllc::cccc:,..........:.......:cc:,..::::::.:::::::::,,......;l,.    \n               ....:......:;,::,,,,;:;;,:............:::..::,;,:::::...........:...........::oc.    \n             ..,:............  .........  ...............  .............................,,;c:c;.    \n            .:,.................... .........   .. ................................:;;,:d.:;oc.     \n           .,cc;,;::,:,:..:::.........................................::........;:;;lo:,col:;.      \n           .cdo:lxxc:dxl,;llc;:::;:,c:;:.,::;;,,;::;,.:,,,::;,:,,,,:,:cc;:;cc:,,coc,cdl:cc,..       \n           .cdc:dxocokkl;ldo:cxdoc;oxoc,:doll:,cdool;::lcc;,cc;:llc;:lll:,:olc;::ol:loc,..          \n            .ccldxdcokxl:ddlcokdl::ddoc;lxdoo;;ddool,,lolc;:lc;cooc,;lllc,;oooc;ldl:,..             \n             ..:;:c:lxxolxkxodkxdcckkxocoxxxd:cxxdxo:cdddc:lol:looc:ldddo:cllc;::..                 \n                       :::,;:;:ccc:;ccc:;:lllc::llcc:;;cc:;,;:;,,,,::,,,::                          \n");
		if(cambio==0){
			printf("\n\n				PRESIONE CUALQUIER TECLA PARA COMENZAR");
		}
        // invierte el valor de cambio
		cambio=~cambio;
        // espera un cierto tiempo y refresca la pantalla
		sleep(1);
		system("cls");
	}	
	system("cls");
    
    // mientras el jugador no haya perdido puede jugar
	while(muerto==0){
		if(kbhit()){
            // lo almaceno
			letra=getch();
            // asigno el movimiento que voy a hacer dependiendo de la direccion que ya tenia
			if(letra=='w' && ult=='s'){
				letra='s';
			}
			if(letra=='a' && ult=='d'){
				letra='d';
			}
			if(letra=='s' && ult=='w'){
				letra='w';
			}
			if(letra=='d' && ult=='a'){
				letra='a';
			}
		}
		
		for(int i=0;i<(tam-1);i++){
			auxx=snake[i+1].x;
			auxy=snake[i+1].y;
            
			if(i!=0){
				snake[i+1].x=auxx2;
				snake[i+1].y=auxy2;
			}
			if(i==0){
				snake[i+1].x=snake[i].x;
				snake[i+1].y=snake[i].y;
				
				ult=direccion(espacio,&snake[0],letra,&muerto,ult,tam);

                // si la posicion de la cabeza es la misma que la de la manzana
				if (manzana.x == snake[0].x && manzana.y == snake[0].y)
				{
					tam++;
                    puntaje=puntaje+100;
                    // muevo la vivorita si toca una tecla adecuada
                    switch (letra){
                    case 'w':
                        snake[tam-1].x=snake[tam-2].x+1;
						snake[tam-1].y=snake[tam-2].y;
                        break;
                    case 'a':
                        snake[tam-1].x=snake[tam-2].x;
						snake[tam-1].y=snake[tam-2].y+1;
                        break;
                    case 's':
                        snake[tam-1].x=snake[tam-2].x-1;
						snake[tam-1].y=snake[tam-2].y;
                        break;
                    case 'd':
                        snake[tam-1].x=snake[tam-2].x;
						snake[tam-1].y=snake[tam-2].y-1;
                        break;
                    default:
                        break;
                    }

                    // agrega una manzana en una posicion libre dentro de los margenes
					while(dif==0){
						dif=1;
						manzana.x = 1 + rand() % (t - 2);
						manzana.y = 1 + rand() % (t - 2);
						for(int j=0;j<(tam-1);j++){
							if(manzana.x == snake[j].x && manzana.y == snake[j].y){
								dif=0;
								break;
							}
						}
					}
					dif=0;
					
                    // asigna la manzana en la posicion adecuada
					espacio[manzana.x][manzana.y] = '#';
				}
			}
			espacio[snake[i+1].x][snake[i+1].y]='x';
			espacio[auxx][auxy]=' ';
			auxx2=auxx;
			auxy2=auxy;
		}

        // muestra el frame
		imprimir(espacio, &puntaje);
	}

	printf("\n\n\n			GAME OVER\n\n\n\n");
    printf("  Ingrese su nombre: ");
    scanf("%s", &nombre);
    printf("  Su puntaje fue: %d", puntaje);
	
	guardar_puntaje(nombre, puntaje);
	
	return 0;
}

void imprimir(char espacio[t][t], int *puntaje){
    // recorre la matriz e imprime el caracter
	for (int i = 0; i < t; i++) {
		for (int j = 0; j < t; j++) {
			printf("%c ", espacio[i][j]);
		} printf("\n");
	}
    // imprime el puntaje actual
    printf("Puntaje: %d", *puntaje);
    // deja una espera antes de refrescar
	sleep(tiempo);
	system("cls");
}
	
void generar(char espacio[t][t]){
	// Pongo el caracter para los bordes horizontales
    for(int i = 0; i < t; i++){
		espacio[0][i] = '-';
		espacio[t-1][i] = '-';
	}
	
	for(int i = 1; i < t - 1; i++){
		// Pongo el caracter para los bordes verticales
		espacio[i][0] = '|';
		espacio[i][t-1] = '|';
		
        // pongo el caracter vacio para todo el resto
		for(int j = 1; j < t - 1; j++){
			espacio[i][j] = ' ';
		}
	}
}
	
void spawn(char espacio[t][t], struct cuerpo *snake){
    // establece la posicion de toda la vivorita
	for(int i=0; i<t_in; i++){
		snake[i].x = (t/2)+i;
		snake[i].y = t/2;
	}
	
    // posiciona las partes en la matriz
    for(int i=0; i<t_in; i++){
	    if(i==0){
	 	    espacio[snake[i].x][snake[i].y]='0';
	    }else{
 		    espacio[snake[i].x][snake[i].y]='x';
 	    }
    }
}

char direccion(char espacio[t][t],struct cuerpo *snake, char letra,int *muerto, char ult, int tam){
    // ve que tecla se toco
	switch(letra){
	case 'w':
		snake[0].x--;
		ult='w';
	    break;
	case 'a':
		snake[0].y--;
		ult='a';
	    break;
	case 's':
		snake[0].x++;
		ult='s';
	    break;
	case 'd':
		snake[0].y++;
		ult='d';
	    break;
    // si toca cualquier tecla no definida mueve la vivorita en la direccion anterior
	default:
		if(ult=='w'){
			snake[0].x--;
		}
		if(ult=='a'){
			snake[0].y--;
		}
		if(ult=='s'){
			snake[0].x++;
		}
		if(ult=='d'){
			snake[0].y++;
		}
	    break;
	}

    // pone la posicion de las partes en el mapa
	espacio[snake[0].x][snake[0].y]='0';
    // analiza las colisiones entre la cabeza y el cuerpo
	for(int i=1;i<tam;i++){
		if(snake[0].x==snake[i].x && snake[0].y==snake[i].y){
			*muerto=1;
			break;
		}
	}
    // analiza las colisiones entre la cabeza y los bordes
	if(snake[0].x==0||snake[0].x==t-1||snake[0].y==0||snake[0].y==t-1){
	   *muerto=1;
	}
   
   return ult;
}

void guardar_puntaje(char nombre[20], int puntaje){
	// crea el tipo de dato archivo y lo abre en modo append
	FILE *fpuntaje;
	fpuntaje=fopen("./data.txt", "a");
	// si no lo encuentra intenta crearlo
	if(NULL == fpuntaje){
		printf("No se encontro el archivo de puntajes, creandolo...\n");
		fpuntaje=fopen("./data.txt", "w");

		// si no puede sale del programa
		if(NULL == fpuntaje){
			printf("No se pudo crear el archivo...");
			exit(1);
		}
	}

	// agrega la informacion y cierra el archivo
	fprintf(fpuntaje, "%s %d\n", nombre, puntaje);
	fclose(fpuntaje);
}