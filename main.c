#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <poll.h> 
#include <fcntl.h> 
#include <errno.h>



////////////////////////////////////////////////////////
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}
////////////////////////////////////////////////////////
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
///////////////////////////////////////////////////////
char Mapa[30][30] = {
	/*1*/	{'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x'},
	/*2*/	{'x','O',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x'},
	/*3*/ {'x',' ','x','x',' ','x','x','x','x','x','x','x','x','x',' ',' ','x','x','x','x','x','x','x','x','x',' ','x','x',' ','x'},
	/*4*/ {'x',' ','x','x',' ','x','x','x','x','x','x','x','x','x',' ',' ','x','x','x','x','x','x','x','x','x',' ','x','x',' ','x'},
	/*5*/{'x',' ','x','x',' ','x','x','x','x','x','x','x','x','x',' ',' ','x','x','x','x','x','x','x','x','x',' ','x','x',' ','x'},
	/*6*/ {'x',' ','x','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x','x',' ','x'},
	/*7*/	{'x',' ','x','x','x','x','x','x','x','x','x',' ','x','x','x','x','x','x',' ','x','x','x','x','x','x','x','x','x',' ','x'},
	/*8*/	{'x',' ','x','x','x','x','x','x','x','x','x',' ','x','x','x','x','x','x',' ','x','x','x','x','x','x','x','x','x',' ','x'},
	/*9*/ {'x',' ','x',' ',' ',' ',' ',' ',' ','x','x',' ','x','x','x','x','x','x',' ','x','x',' ',' ',' ',' ',' ',' ','x',' ','x'},
	/*10*/{'x',' ','x',' ','x','x','x','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x','x','x','x',' ','x',' ','x'},
	/*11*/{'x',' ',' ',' ','x','x','x','x','x','x','x',' ','x','x','x','x','x','x',' ','x','x','x','x','x','x','x',' ',' ',' ','x'},
	/*12*/{'x','x',' ','x','x','x','x','x','x','x','x',' ','x','x','x','x','x','x',' ','x','x','x','x','x','x','x','x',' ','x','x'},
	/*13*/	{'x','x',' ',' ','x','x','x','x','x','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x','x','x','x','x','x',' ',' ','x','x'},
	/*14*/{'x','x','x',' ',' ','x','x','x','x','x',' ','x','x','x',' ',' ','x','x','x',' ','x','x','x','x','x',' ',' ','x','x','x'},
	/*15*/{'x','x','x','x',' ','x','x','x','x','x',' ','x','x',' ',' ',' ',' ','x','x',' ','x','x','x','x','x',' ','x','x','x','x'},
	/*16*/{'x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x','x',' ',' ',' ',' ','x','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x'},
	/*17*/{'x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x','x',' ',' ',' ',' ','x','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x'},
	/*18*/{'x','x','x',' ','x','x','x','x','x','x',' ','x','x','x','x','x','x','x','x',' ','x','x','x','x','x','x',' ','x','x','x'},
	/*19*/{'x','x','x',' ','x','x','x','x','x','x',' ','x','x','x','x','x','x','x','x',' ','x','x','x','x','x','x',' ','x','x','x'},
	/*20*/{'x','x','x',' ','x','x','x','x','x','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x','x','x','x','x','x',' ','x','x','x'},
	/*21*/{'x',' ',' ',' ','x','x','x','x','x','x','x',' ','x','x','x','x','x','x',' ','x','x','x','x','x','x','x',' ',' ',' ','x'},
	/*22*/{'x',' ','x','x','x','x','x','x','x','x','x',' ','x','x','x','x','x','x',' ','x','x','x','x','x','x','x','x','x',' ','x'},
	/*23*/{'x',' ','x','x','x','x','x','x','x','x','x',' ','x','x','x','x','x','x',' ','x','x','x','x','x','x','x','x','x',' ','x'},
	/*24*/{'x',' ','x','x','x','x','x','x','x','x','x',' ','x','x','x','x','x','x',' ','x','x','x','x','x','x','x','x','x',' ','x'},
	/*25*/{'x',' ','x','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x','x',' ','x'},
	/*26*/{'x',' ','x','x',' ','x','x','x','x','x','x','x','x','x',' ',' ','x','x','x','x','x','x','x','x','x',' ','x','x',' ','x'},
	/*27*/{'x',' ','x','x',' ','x','x','x','x','x','x','x','x','x',' ',' ','x','x','x','x','x','x','x','x','x',' ','x','x',' ','x'},
	/*28*/{'x',' ','x','x',' ','x','x','x','x','x','x','x','x','x',' ',' ','x','x','x','x','x','x','x','x','x',' ','x','x',' ','x'},
	/*29*/{'x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x'},
	/*30*/{'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x'},
};
char resp;
int x,y;
int px = 1, py = 1;
int fy,fx, pontos=0;
int teste = 1;
int movimento_anterior = 0;
int fimdejogo = 1;
int ix1 = 15,iy1=16;
int moviop;
///////////////////////////////////////////////////
void finalizar(){
  system("clear");
  if(pontos >= 10){
    printf("Você deseja deseja continuar o jogo por 10 pontos?(s/n)\n");
    scanf(" %c",&resp);
    if (resp == 's'){
      pontos = pontos - 10;
    }
    else if (resp == 'n'){
      fimdejogo --;
    }  
  }
  else {
    fimdejogo --;
		
  }
}
///////////////////////////////////////////////////////
void printmapa(){
	for(x=0;x<30;x++){
		for(y=0;y<30;y++){
				printf("%c",Mapa[x][y]);
				printf(" ");
		}
		printf("\n");
	}
  printf("\nPONTOS: %d",pontos);
}
///////////////////////////////////////////////////////
void comer(){

	Mapa[py][px] = ' ';
	Mapa[fy][fx] = 'O';
	px = fx;
	py = fy; 
	pontos += 1;
}
///////////////////////////////////////////////////////
void andar(){
	switch(getch()){

	case 'w':
		if(Mapa[py - 1][px] == ' '){
			Mapa[py][px] = ' ';
			Mapa[py - 1][px] = 'O';
			py--;
		}
	else if(Mapa[py - 1][px] == '4'){
			comer();
		}
	break;
	case 'a':
	if(Mapa[py][px - 1] == ' '){
		Mapa[py][px] = ' ';
		Mapa[py][px - 1] = 'O';
		px--;
		}
  else if (Mapa[py][px - 1] == '4'){
      comer();
    }
	break;
	
	case 's':
  if(Mapa[py + 1][px] == ' '){
		Mapa[py][px] = ' ';
		Mapa[py + 1][px] = 'O';
		py++;
    }
  else if(Mapa[py+1][px] == '4'){
      comer();
  }
	break;
	
	case 'd':
  if(Mapa[py][px + 1] == ' '){
		Mapa[py][px] = ' ';
		Mapa[py][px + 1] = 'O';
    px++;
	}
  else if(Mapa[py][px + 1] == '4'){
    comer();
   }
	break;
  }


}
///////////////////////////////////////////////////////
void fruta(){
	srand(time(NULL));
	
	fy = rand()%30;
	fx = rand()%30;
	
	while(Mapa[fy][fx] !=' ' ){
			fy = rand()%30;
			fx = rand()%30;

	}
	Mapa[fy][fx] = '4'; 
}
///////////////////////////////////////////////////////
void prioridade(){
	int inim;
	if(inim == moviop){
			inim = movimento_anterior;	
	}
	if(inim != movimento_anterior){
		inim = rand()%4;
		if(inim != movimento_anterior){
			inim = rand()%4;
			if(inim != movimento_anterior){
				inim = rand()%4;	
				if(inim != movimento_anterior){
					inim = rand()%4;
					if(inim != movimento_anterior){
						inim = rand()%4;	
						if(inim != movimento_anterior){
							inim = rand()%4;	
						}
					}	
				}	
			}		
		}	
	}
	
}
///////////////////////////////////////////////////////
void inimigo(){
int inim;
srand(time(NULL));
	teste = 1;
  while(teste == 1){ 
		 
		inim = rand()%4;
		prioridade();
		switch(inim){
			case 0 :
				if(Mapa[iy1 - 1][ix1] != 'x'){
					Mapa[iy1][ix1] = ' ';
					Mapa[iy1 - 1][ix1] = 'M';
					iy1--;
					teste--;
					movimento_anterior = 0;
					moviop = 1;	
				}
				break;
			case 1 :
				if(Mapa[iy1 + 1][ix1] != 'x'){
					Mapa[iy1][ix1] = ' ';
					Mapa[iy1 + 1][ix1] = 'M';
					iy1++;
					teste--;
					movimento_anterior = 1;
					moviop = 0;	
				}
				break;
			case 2 :
				if(Mapa[iy1][ix1 - 1] != 'x'){
					Mapa[iy1][ix1] = ' ';
					Mapa[iy1][ix1-1] = 'M';
					ix1--;
					teste--;
					movimento_anterior = 2;
					moviop = 3;	
				}
				break;
			case 3 :
				if(Mapa[iy1][ix1+1] != 'x'){
					Mapa[iy1][ix1] = ' ';
					Mapa[iy1][ix1+1] = 'M';
					ix1++;
					teste --;
					movimento_anterior = 3;
					moviop = 2;	
				}
				break;
		} 
	}
}
///////////////////////////////////////////////////////
int main(void){
	system("clear");
	fruta();
	Mapa[16][15] ='M';
	
	while(fimdejogo ==1){
	if(Mapa[fy][fx] != '4'){
		fruta();	
	}
	if(Mapa[py][px]== Mapa[iy1][ix1]){
		finalizar();
		
	}
	printmapa();
	andar();
  inimigo();
	
	system("clear");
  
	}
	system("clear");
  printf("\n\n\nVOCÊ PERDEU O JOGO!!!!!!");
}







