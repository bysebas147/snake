#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define t 29		//tamaño del mapa
#define t_in 4
#define max 30
#define tiempo 0	//delay (inversamente proporcional a la velocidad)

struct cuerpo{		//estructura del cuerpo y cabeza
	int x,y;
};

struct fruta
{
	int x, y;
};

void imprimir(char espacio[t][t]);
void generar(char espacio[t][t]);
void spawn(char espacio[t][t], struct cuerpo *snake);
char direccion(char espacio[t][t], struct cuerpo *snake,char letra,int *muerto, char ult, int tam);

int main(int argc, char *argv[]) {
	
	srand(time(NULL));
	struct cuerpo snake[max];
	char letra='w', ult='w', espacio[t][t];
	int muerto=0;
	int auxx=0, auxy=0;		//para modificar el tamaño de la snake
	int auxx2=0, auxy2=0;
	int tam = t_in;			//tamaÃ±o inicial de la matriz
	int dif=0, cambio=0;
	
	generar(espacio);	
	spawn(espacio, snake);
	
	struct fruta manzana;
	manzana.x = 1 + rand() % (t - 2);
	manzana.y = 1 + rand() % (t - 2);
	espacio[manzana.x][manzana.y] = '#';
				
	while (kbhit() != 1)
	{
		printf("\n\n                         ....              ...::...                                                 \n                     ..::.......       ..:,::,,,,,::.                                               \n                ....::c;,::::,,;,::::,;;,,,:odxdlc:;::....                                          \n            ..::::::,:..::.....::..:;;,.,d00k0XKOkdd:.,;:.:::..                                     \n            :::;,,,,,;;;;:c;:......:;..:ONO;.c0XXK0Ol..,...::,:....                                 \n           .,cl:,;:.......::::,.......,dKXl..:OXXXX0l:..........:,,:.....                           \n           .,cc:;,.......,;;;,,.......,o0d...dKX0kl::..............:,,:::...                       \n              .::::,......,;,;..::.......:o:::xko;....::.::::........::..,;,:..                     \n                .,lc;;;,:.,;;;....... ............::::,;;;,:..:........:....,;:..                   \n                 .lc...:cll;;c;,,:............:;;:c::;::....::...............:,;:.                  \n                 .:l.   ;xl:,;.:,,,,,;;;;;;;:ll:,,,,:....,,:::..................;,.                 \n                  :l.   ,xc:;:.....;ccccllc::;........,;;::cll:::,..............:::.                \n                  .:,   ,o,:;...::lodool:;:.....,,,,,:oddxkkkddxkxol,............;;.                \n                  .:;   :;.;;.::odollc;......:,,,:....:ldxxxkkkkOOkOx;...........,;.                \n                 ..,.. .:.::;:oolll:,...:;,:::..  .    .,xOkkkkkkxxkkd;....:.....:,.                \n                 ...   ::.:llocllc,..,,,,...   .         :lxkkkxxxxxddd;.........;;.                \n                      .:.cdolccc;,,:::.                   .lOOOOOkdooodc:.......::,.                \n   ...              .:,,;clllc:,::..                       :dkxddddoodxo,.......;:.                 \n   ..:.         ...:;;,:. .....                            .:xxxxxxdoooc........:.                  \n    ..:.......:,;:;,:..                                    .:kxdddddddo,.......;;.                  \n      ..:,,;;,,::...                                       .lxdddooloo:.......;;.                   \n                                                          .;kxdoooooo:.......;,.                    \n                                                         .;okkxddool,......,;,..                    \n                                                       .,lxxxdoolc;.......,;..;. .                  \n                                                   ..::ldxxdoooc;........,,. .;;:..     .           \n                                              ..,;:coddoodocc;.........:,:. . :lc,:....  .          \n                                        ..:,;:lllllllllc;;;:.........:,:.     ..cc:,::.....         \n                                   ..:,;cloooolc::::;:............,,,:.         ..;ll;...:::..      \n                              ..:;;;:loollcc:;,:................;:,..              .cd;....:;,.     \n                  .........:;::cllc::cccc:,..........:.......:cc:,..::::::.:::::::::,,......;l,.    \n               ....:......:;,::,,,,;:;;,:............:::..::,;,:::::...........:...........::oc.    \n             ..,:............  .........  ...............  .............................,,;c:c;.    \n            .:,.................... .........   .. ................................:;;,:d.:;oc.     \n           .,cc;,;::,:,:..:::.........................................::........;:;;lo:,col:;.      \n           .cdo:lxxc:dxl,;llc;:::;:,c:;:.,::;;,,;::;,.:,,,::;,:,,,,:,:cc;:;cc:,,coc,cdl:cc,..       \n           .cdc:dxocokkl;ldo:cxdoc;oxoc,:doll:,cdool;::lcc;,cc;:llc;:lll:,:olc;::ol:loc,..          \n            .ccldxdcokxl:ddlcokdl::ddoc;lxdoo;;ddool,,lolc;:lc;cooc,;lllc,;oooc;ldl:,..             \n             ..:;:c:lxxolxkxodkxdcckkxocoxxxd:cxxdxo:cdddc:lol:looc:ldddo:cllc;::..                 \n                       :::,;:;:ccc:;ccc:;:lllc::llcc:;;cc:;,;:;,,,,::,,,::                          \n");
		if(cambio==0){
			printf("\n\n				PRESIONE CUALQUIER TECLA PARA COMENZAR");
		}
		cambio=~cambio;
		sleep(1);
		system("cls");
	}	
	system("cls");
	while(muerto==0){
		
		if(kbhit()){
			letra=getch();
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
				if (manzana.x == snake[0].x && manzana.y == snake[0].y)
				{
					tam++;
					if(letra=='w'){
						snake[tam-1].x=snake[tam-2].x+1;
						snake[tam-1].y=snake[tam-2].y;
					}
					if(letra=='a'){
						snake[tam-1].x=snake[tam-2].x;
						snake[tam-1].y=snake[tam-2].y+1;
					}
					if(letra=='s'){
						snake[tam-1].x=snake[tam-2].x-1;
						snake[tam-1].y=snake[tam-2].y;
					}
					if(letra=='d'){
						snake[tam-1].x=snake[tam-2].x;
						snake[tam-1].y=snake[tam-2].y-1;
					}
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
					
					espacio[manzana.x][manzana.y] = '#';
				}
			}
			espacio[snake[i+1].x][snake[i+1].y]='x';
			espacio[auxx][auxy]=' ';
			auxx2=auxx;
			auxy2=auxy;
		}

		imprimir(espacio);
	}

	printf("\n\n\n\n\n\n\n\n			GAME OVER\n\n\n\n\n\n\n");
	
	return 0;
}

void imprimir(char espacio[t][t]){
	for (int i = 0; i < t; i++) {
		for (int j = 0; j < t; j++) {
			printf("%c ", espacio[i][j]);
		} printf("\n");
	}
	sleep(tiempo);
	system("cls");
}
	
void generar(char espacio[t][t]){
	for(int i = 0; i < t; i++){
		espacio[0][i] = '-';
		espacio[t-1][i] = '-';
	}
	
	// Pongo los caracteres para el medio
	for(int i = 1; i < t - 1; i++){
		// Pongo el caracter para los bordes verticales
		espacio[i][0] = '|';
		espacio[i][t-1] = '|';
		
		for(int j = 1; j < t - 1; j++){
			espacio[i][j] = ' ';
		}
	}
}
	
void spawn(char espacio[t][t], struct cuerpo *snake){

   // establece la posicion de toda la vivorita

	for(int i=0;i<t_in;i++){
		snake[i].x=(t/2)+i;
		snake[i].y=t/2;
	}
	
   for(int i=0;i<t_in;i++){
	   if(i==0){
		   espacio[snake[i].x][snake[i].y]='0';
	   }else{
		   espacio[snake[i].x][snake[i].y]='x';
	   }
   }
}

char direccion(char espacio[t][t],struct cuerpo *snake, char letra,int *muerto, char ult, int tam){
   //espacio[cabeza1[0].x][cabeza1[0].y]=' ';
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

	espacio[snake[0].x][snake[0].y]='0';
	for(int i=1;i<tam;i++){
		if(snake[0].x==snake[i].x && snake[0].y==snake[i].y){
			*muerto=1;
			break;
		}
	}
	if(snake[0].x==0||snake[0].x==t-1||snake[0].y==0||snake[0].y==t-1){
	   *muerto=1;
	}
   
   return ult;
}