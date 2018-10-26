#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

int jogada_usuario(int lin, int col, char jog);
void jogada_computador(char jog, int nivel);
int menu();
void escolha_simb(char *jog1, char *jog2);
void inicializa_velha();
int verifica_ganhador(char jog);
void mostra_matriz();

char matriz[3][3], jog1, jog2, jog, vez, contra[20];
int nvez=2, lin, col, resjogada,jogadas1[3][3],jogadas2[3][3],nivel,jogcomp;
//Possiveis combinações de vitória
int vitoria[8][3][2]={{{0,0},{0,1},{0,2}},{{1,0},{1,1},{1,2}},{{2,0},{2,1},{2,2}},{{0,0},{1,0},{2,0}},{{0,1},{1,1},{2,1}},{{0,2},{1,2},{2,2}},{{0,0},{1,1},{2,2}},{{0,2},{1,1},{2,0}}};

int main(){
    system("cls");
    printf("----------------------------JOGO DA VELHA!!------------------------\n");
    inicializa_velha();
    if(menu()==2){
        strcpy(contra,"Jogador 2");
    } else {
        strcpy(contra,"Computador");
        jogcomp=1;
    }
    escolha_simb(&jog1,&jog2);
    vez=jog2;
    printf("---------------------VALENDO!-------------------");
    mostra_matriz();
    if(nivel==3){
        vez=jog1;
    }
    do{
        if(vez==jog2){
            vez=jog1;
            nvez=1;
        } else {
            vez=jog2;
            nvez=2;
        }
        if(!strcmp(contra,"Jogador 2")){
            do{
                printf("Jogador %d escolha a posicao para jogar, linha e coluna: ",nvez);
                scanf("%d %d",&lin,&col);
                lin--;
                col--;
                resjogada=jogada_usuario(lin,col,vez);
            }while(resjogada!=0);
            mostra_matriz();
        } else {
            if(nvez==1){
                    do{
                        printf("Jogador %d escolha a posicao para jogar, linha e coluna: ",nvez);
                        scanf("%d %d",&lin,&col);
                        lin--;
                        col--;
                        resjogada=jogada_usuario(lin,col,vez);
                }while(resjogada!=0);
            } else {
                //computador joga
                printf("PC jogando...\n");
                jogada_computador(jog2,nivel);
            }
        mostra_matriz();
        }
    }while(verifica_ganhador(vez)==0);
        if(verifica_ganhador(vez)==1 && !strcmp(contra,"Jogador 2")){
            printf("Jogador %d ganhou!",nvez);
        } else if(verifica_ganhador(vez)==1 && !strcmp(contra,"Computador")){
            if(vez==jog1){
                printf("Jogador %d ganhou!",nvez);
            }else{
                printf("Computador ganhou!");
            }
        }else {
            printf("Velha!");
        }
    printf("\nPress ENTER key to Continue\n");  
    getchar();
    getchar(); 
    return 0;
    }

int jogada_usuario(int lin, int col, char jog){
    if(lin<0 || lin>4 || col<0 || col>4){
        return 1;
    } else if(matriz[lin][col]!=' '){
        return 2;
    }
    matriz[lin][col]=jog;
    return 0;
}

void jogada_computador(char jog, int nivel){

    time_t t;
    srand((unsigned) time(&t));
    int c,d;
    if(nivel==1){

    } else if(nivel==2){
        do{
            c=(rand()%3+1);
            d=(rand()%3+1);
        }while(matriz[c][d]!=' ');
        matriz[c][d]=jog;
    } else{
        if(jogcomp==1){
            if(matriz[0][0]==' '){
                matriz[0][0]=jog;
            }else{
                matriz[2][0]=jog;
            }
        } else if(jogcomp==2){
            if(matriz[0][0]==jog){
                if(matriz[0][2]==' '){
                    matriz[0][2]=jog;
                } else {
                    matriz[2][0]=jog;
                }
            } else {
                if(matriz[0][0]==' '){
                    matriz[0][0]=jog;
                } else {
                    matriz[2][2]=jog;
                }
            }
        } else if(jogcomp==3) {
            if(matriz[0][0]==jog && matriz[0][2]==jog){
                if(matriz[0][1]==' '){
                    matriz[0][1]=jog;
                } else if(matriz[1][1]!=' '){
                    matriz[2][1]=jog;
                } else if(matriz[2][1]!=' '){
                    matriz[1][1]=jog;
                }else if(matriz[2][0]!=' ' || matriz[2][2]!=' '){
                    matriz[2][1]=jog;
                } else{
                    int cont=0;
                    for(c=0;c<3;c++){
                        for(d=0;d<3;d++){
                            if(matriz[c][d]==' '){
                                matriz[c][d]=jog;
                                cont=1;
                                break;
                            }
                        }
                        if(cont==1){
                            break;
                        }
                    }
                }
            } else if(matriz[0][0]==jog && matriz[2][0]==jog){
                if(matriz[1][0]==' '){
                    matriz[1][0]=jog;
                } else if(matriz[1][1]!=' '){
                    matriz[1][2]=jog;
                } else if(matriz[1][2]!=' '){
                    matriz[1][1]=jog;
                }else if(matriz[0][2]!=' ' || matriz[2][2]!=' '){
                    matriz[1][2]=jog;
                }else {
                    int cont=0;
                    for(c=0;c<3;c++){
                        for(d=0;d<3;d++){
                            if(matriz[c][d]==' '){
                                matriz[c][d]=jog;
                                cont=1;
                                break;
                            }
                        }
                        if(cont==1){
                            break;
                        }
                    }
                }
            } else if(matriz[2][0]==jog && matriz[2][2]==jog){
                if(matriz[2][1]==' '){
                    matriz[2][1]=jog;
                }else if(matriz[1][1]!=' '){
                    matriz[0][1]=jog;
                }else if(matriz[0][1]!=' '){
                    matriz[1][1]=jog;
                }else if(matriz[0][0]!=' ' || matriz[0][2]!=' '){
                    matriz[0][1]=jog;
                }else{
                    int cont=0;
                    for(c=0;c<3;c++){
                        for(d=0;d<3;d++){
                            if(matriz[c][d]==' '){
                                matriz[c][d]=jog;
                                cont=1;
                                break;
                            }
                        }
                        if(cont==1){
                            break;
                        }
                    }
                }
            } 
        }else {
                int cont=0;
                    for(c=0;c<3;c++){
                        for(d=0;d<3;d++){
                            if(matriz[c][d]==' '){
                                matriz[c][d]=jog;
                                cont=1;
                                break;
                            }
                        }
                        if(cont==1){
                            break;
                        }
                    }
            }
    }
    jogcomp++;
}

//Criar jogadas b�sico, intermedi�rio e avan�ado

int menu(){
    int opc;
    do{
        printf("1-Computador\n2-Outro jogador\nCom quem deseja jogar?: ");
        scanf("%d",&opc);
        if(opc==1){
            do{
                printf("\n1-Basico\n2-Intermediario\n3-Avancado\nEscolha o nivel do jogo:");
                scanf("%d",&nivel);
            }while(nivel<1 || nivel>3);
        }
    }while(opc!=1 && opc!=2);
    return opc;
}

void escolha_simb(char *jog1, char *jog2){
    do{
        printf("\nJogador 1, escolha X ou O: ");
        setbuf(stdin,NULL);
        scanf("%c",jog1);
        *jog1=tolower(*jog1);
        vez=*jog2;
    }while(*jog1!='o' && *jog1!='x');
    if(*jog1=='x'){
        printf("%s sera O.\n",contra);
        *jog2='o';
    } else {
        printf("%s sera X.\n",contra);
        *jog2='x';
    }
}

void inicializa_velha(){
    printf("\n");
    for(int c=0;c<3;c++){
        for(int d=0;d<3;d++){
            matriz[c][d]=' ';
        }
    }
}

int verifica_ganhador(char jog){
    int cont, c, d;
    cont=3;
    for(c=0;c<3;c++){
        for(d=0;d<3;d++){
            if(matriz[c][d]==' '){
                cont=0;
                break;
            }
        }
        if(cont==0){
            break;
        }
    }
    if(cont==3){
        return cont;
    }
    for(c=0;c<8;c++){
        cont=1;
        //printf("--\n");
        for(d=0;d<3;d++){
            //printf("matriz[%d][%d] = %c\n",vitoria[c][d][0],vitoria[c][d][1],matriz[vitoria[c][d][0]][vitoria[c][d][1]]);
            if(matriz[vitoria[c][d][0]][vitoria[c][d][1]]!=jog){
                cont=0;
                break;
            }
        }
        if (cont==1){
            return cont;
        }
    }
    return cont;
}

//Grava em texto

//Grava em binario

//L� bin�rio

//Imprime na tela

void mostra_matriz(){
    printf("\n");
    printf("  1  2  3\n");
    for(int c=0;c<3;c++){
        printf("%d",c+1);
        for(int d=0;d<3;d++){
            printf("[%c]",matriz[c][d]);
        }
        printf("\n");
    }
    printf("\n");
}