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
void grava_texto();
void remove_quebra();
int grava_bin(char *arqbin);
void imprime_tela(char *arqbin);

typedef struct velha{
    int partida;
    char JogVelha[3][3];
    char resultado;
} Partida;
Partida jogo;

FILE *arq;
char  jog1, jog2, jog, vez, contra[20], nome1[20], nome2[20];
int nvez=2, lin, col, resjogada,jogadas1[3][3],jogadas2[3][3],nivel,jogcomp;
//Possiveis combinações de vitória
int vitoria[8][3][2]={{{0,0},{0,1},{0,2}},{{1,0},{1,1},{1,2}},{{2,0},{2,1},{2,2}},{{0,0},{1,0},{2,0}},{{0,1},{1,1},{2,1}},{{0,2},{1,2},{2,2}},{{0,0},{1,1},{2,2}},{{0,2},{1,1},{2,0}}};

int main(){
    system("cls");
    printf("----------------------------JOGO DA VELHA!!------------------------\n");
    char opc, arqbin[20];
    jogo.partida=0;
    strcpy(arqbin,"campeonato.bin");
    printf("Jogador 1, digite seu nome: ");
    setbuf(stdin, NULL);
    fgets(nome1,sizeof(nome1),stdin);
    if(menu()==2){
        strcpy(contra,"Jogador 2");
        printf("Jogador 2, digite seu nome: ");
        setbuf(stdin, NULL);
        fgets(nome2,sizeof(nome1),stdin);
    } else {
        strcpy(contra,"Computador");
        strcpy(nome2,"Computador");
        jogcomp=1;
    }
    escolha_simb(&jog1,&jog2);
    remove_quebra();
    grava_texto();
    do{
        system("cls");
        inicializa_velha();
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
                jogo.resultado=vez;
            } else if(verifica_ganhador(vez)==1 && !strcmp(contra,"Computador")){
                if(vez==jog1){
                    printf("Jogador %d ganhou!",nvez);
                    jogo.resultado=vez;
                }else{
                    printf("Computador ganhou!");
                    jogo.resultado=vez;
                }
            }else {
                printf("Velha!");
                jogo.resultado='v';
            }
            jogo.partida++;
            if(!grava_bin(arqbin)){
                printf("Erro ao criar arquivo binario!");
            }
            printf("\nDeseja continuar?[S/N]: ");
            setbuf(stdin,NULL);
            scanf("%c",&opc);
    }while(tolower(opc)=='s');
    imprime_tela(arqbin);
    printf("\nPress ENTER key to Continue\n");  
    getchar();
    getchar(); 
    return 0;
    }

int jogada_usuario(int lin, int col, char jog){
    if(lin<0 || lin>4 || col<0 || col>4){
        return 1;
    } else if(jogo.JogVelha[lin][col]!=' '){
        return 2;
    }
    jogo.JogVelha[lin][col]=jog;
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
        }while(jogo.JogVelha[c][d]!=' ');
        jogo.JogVelha[c][d]=jog;
    } else{
        if(jogcomp==1){
            if(jogo.JogVelha[0][0]==' '){
                jogo.JogVelha[0][0]=jog;
            }else{
                jogo.JogVelha[2][0]=jog;
            }
        } else if(jogcomp==2){
            if(jogo.JogVelha[0][0]==jog){
                if(jogo.JogVelha[0][2]==' '){
                    jogo.JogVelha[0][2]=jog;
                } else {
                    jogo.JogVelha[2][0]=jog;
                }
            } else {
                if(jogo.JogVelha[0][0]==' '){
                    jogo.JogVelha[0][0]=jog;
                } else {
                    jogo.JogVelha[2][2]=jog;
                }
            }
        } else if(jogcomp==3) {
            if(jogo.JogVelha[0][0]==jog && jogo.JogVelha[0][2]==jog){
                if(jogo.JogVelha[0][1]==' '){
                    jogo.JogVelha[0][1]=jog;
                } else if(jogo.JogVelha[1][1]!=' '){
                    jogo.JogVelha[2][1]=jog;
                } else if(jogo.JogVelha[2][1]!=' '){
                    jogo.JogVelha[1][1]=jog;
                }else if(jogo.JogVelha[2][0]!=' ' || jogo.JogVelha[2][2]!=' '){
                    jogo.JogVelha[2][1]=jog;
                } else{
                    int cont=0;
                    for(c=0;c<3;c++){
                        for(d=0;d<3;d++){
                            if(jogo.JogVelha[c][d]==' '){
                                jogo.JogVelha[c][d]=jog;
                                cont=1;
                                break;
                            }
                        }
                        if(cont==1){
                            break;
                        }
                    }
                }
            } else if(jogo.JogVelha[0][0]==jog && jogo.JogVelha[2][0]==jog){
                if(jogo.JogVelha[1][0]==' '){
                    jogo.JogVelha[1][0]=jog;
                } else if(jogo.JogVelha[1][1]!=' '){
                    jogo.JogVelha[1][2]=jog;
                } else if(jogo.JogVelha[1][2]!=' '){
                    jogo.JogVelha[1][1]=jog;
                }else if(jogo.JogVelha[0][2]!=' ' || jogo.JogVelha[2][2]!=' '){
                    jogo.JogVelha[1][2]=jog;
                }else {
                    int cont=0;
                    for(c=0;c<3;c++){
                        for(d=0;d<3;d++){
                            if(jogo.JogVelha[c][d]==' '){
                                jogo.JogVelha[c][d]=jog;
                                cont=1;
                                break;
                            }
                        }
                        if(cont==1){
                            break;
                        }
                    }
                }
            } else if(jogo.JogVelha[2][0]==jog && jogo.JogVelha[2][2]==jog){
                if(jogo.JogVelha[2][1]==' '){
                    jogo.JogVelha[2][1]=jog;
                }else if(jogo.JogVelha[1][1]!=' '){
                    jogo.JogVelha[0][1]=jog;
                }else if(jogo.JogVelha[0][1]!=' '){
                    jogo.JogVelha[1][1]=jog;
                }else if(jogo.JogVelha[0][0]!=' ' || jogo.JogVelha[0][2]!=' '){
                    jogo.JogVelha[0][1]=jog;
                }else{
                    int cont=0;
                    for(c=0;c<3;c++){
                        for(d=0;d<3;d++){
                            if(jogo.JogVelha[c][d]==' '){
                                jogo.JogVelha[c][d]=jog;
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
                            if(jogo.JogVelha[c][d]==' '){
                                jogo.JogVelha[c][d]=jog;
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
            jogo.JogVelha[c][d]=' ';
        }
    }
}

int verifica_ganhador(char jog){
    int cont, c, d;
    for(c=0;c<8;c++){
        cont=1;
        //printf("--\n");
        for(d=0;d<3;d++){
            //printf("jogo.JogVelha[%d][%d] = %c\n",vitoria[c][d][0],vitoria[c][d][1],jogo.JogVelha[vitoria[c][d][0]][vitoria[c][d][1]]);
            if(jogo.JogVelha[vitoria[c][d][0]][vitoria[c][d][1]]!=jog){
                cont=0;
                break;
            }
        }
        if (cont==1){
            return cont;
        }
    }
    for(c=0;c<3;c++){
        for(d=0;d<3;d++){
            if(jogo.JogVelha[c][d]==' '){
                return 0;
            }
        }
    }
    return 3;
}

void grava_texto(){
    if((arq=fopen("nomes.txt","a+"))==NULL){
        printf("Erro!");
        exit(0);
    }
    fprintf(arq, "%s; %c; %s; %c\n",nome1,jog1,nome2,jog2);
    fclose(arq);
}

int grava_bin(char *arqbin){
    if((arq=fopen(arqbin,"a+b"))==NULL){
        return 0;
    } else {
        fwrite(&jogo,1,sizeof(jogo),arq);
    }
    fclose(arq);
    return 1;
}

//L� bin�rio

//Imprime na tela

void imprime_tela(char arqbin[50]){
    char jog1, jog2, nomejog1[20], nomejog2[20], linha[48], vencedor[20];
    int v1,v2,c=0,d=0;
    FILE *arqtxt;
    if((arq=fopen(arqbin,"rb"))==NULL){
        printf("Erro!\n");
        //exit(0);
    }
    if((arqtxt=fopen("nomes.txt","r"))==NULL){
        printf("Erro!\n");
        //exit(0);
    }
    fgets(linha,sizeof(linha),arqtxt);
    while(linha[c]!=';'){
        nomejog1[d]=linha[c];
        c++;
        d++;
    }
    nomejog1[d]='\0';
    d=0;
    jog1=linha[c+2];    c+=5;
    while(linha[c]!=';'){
        nomejog2[d]=linha[c];
        c++;
        d++;
    }
    nomejog2[d]='\0';
    jog2=linha[c+2];
    printf("\n-------------------------RESULTADOS------------------------\n");
    do{
        fread(&jogo,1,sizeof(Partida),arq);
        printf("\n----------------------Partida %d---------------------\n\n",jogo.partida);
        for(int c=0;c<3;c++){
            for(int d=0;d<3;d++){
                printf("[%c]",jogo.JogVelha[c][d]);
            }
            printf("\n");
        }
        if(jogo.resultado==jog1){
            strcpy(vencedor,nomejog1);
        } else if(jogo.resultado==jog2){
            strcpy(vencedor,nomejog2);
        } else {
            strcpy(vencedor,"Velha");
        }
        printf("\nResultado: %s",vencedor);
    }while(!feof(arq));
    fclose(arq);
    fclose(arqtxt);
}

void mostra_matriz(){
    printf("\n");
    printf("  1  2  3\n");
    for(int c=0;c<3;c++){
        printf("%d",c+1);
        for(int d=0;d<3;d++){
            printf("[%c]",jogo.JogVelha[c][d]);
        }
        printf("\n");
    }
    printf("\n");
}

void remove_quebra(){
    for(int c=0;c<sizeof(nome1);c++){
        if(nome1[c]=='\n'){
            nome1[c]='\0';
            break;
        }
    }
    for(int c=0;c<sizeof(nome1);c++){
        if(nome2[c]=='\n'){
            nome2[c]='\0';
            break;
        }
    }
}
