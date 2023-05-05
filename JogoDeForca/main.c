#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

char palavraSecreta[TAMANHO_PALAVRA],chutes[26];
int chutesDados = 0;

void abertura(){
	printf("*+**+**+**+**+**+**+*\n");
	printf("*   Jogo de Forca   *\n");
	printf("*+**+**+**+**+**+**+*\n");
}

void adicionaPalavra(){
	char quer;
	
	printf("Deseja adicionar uma nova palavra (s/n)\n");
	scanf(" %c", &quer);

	if(quer == 's'){
		char novaPalavra[TAMANHO_PALAVRA];
		
		printf("Escreva a nova palavra:");
		scanf("%s", &novaPalavra);
		
		FILE* f;
		
		f = fopen("palavras.txt", "r+");
		if(f == 0){
			printf("Desculpe, banco de dados nao disponivel");
			exit(1);
		}
		
		int qnt;
		fscanf(f, "%d", &qnt);
		qnt++;
		
		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", qnt);
		fseek(f, 0, SEEK_END);
		
		fprintf(f, "\n%s", novaPalavra);
		
		fclose(f);
	}
}

void chuta(){
	char chute;
	
	printf("\n");
	scanf(" %c", &chute);

	chutes[chutesDados] = chute;
	chutesDados++;
}

void desenhaForca(){
	int erros = chutesErrados();

    printf("  _______      \n");
    printf(" |/      |     \n");
    printf(" |      %c%c%c    \n",(erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')': ' '));
    printf(" |      %c%c%c   \n",(erros >= 3 ? '\\' : ' '),(erros >= 2 ? '|' : ' '),(erros >= 4 ? '/' : ' '));
    printf(" |       %c     \n",(erros >= 2 ? '|': ' '));
    printf(" |      %c %c   \n",(erros >= 5 ? '/' : ' '),(erros >= 5 ? '\\' : ' '));
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n\n");


	int i = 0;
	
	for(i = 0; i < strlen(palavraSecreta); i++) {
		
		int achou = jachutou(palavraSecreta[i]);
			
		if(achou == 1){
			printf(" %c ", palavraSecreta[i]);
		}else{
			printf("_ ");
		}
	}
}

void escrevePalavra(){
	FILE* f;
	
	f = fopen("palavras.txt", "r");
	if(f == 0){
		printf("Desculpe, banco de dados nao disponivel");
		exit(1);
	}
	
	
	int qtdDePalavras; 
	fscanf(f, "%d", &qtdDePalavras);
	
	srand(time(0));
	int randomico = rand() % qtdDePalavras;
	
	int i = 0;
	for(i = 0; i <= randomico; i++){
		fscanf(f, "%s", palavraSecreta);
	}
	
	
	fclose(f);
}

int acertou(){
	int i = 0;
	
	for(i = 0; i< strlen(palavraSecreta); i++){
		if(!jachutou(palavraSecreta[i]))
			return 0;
	} 

	return 1;
}

int chutesErrados(){
	int erros = 0, i = 0;
	
	for(i = 0; i < chutesDados; i++){
		int existe = 0, j = 0;
		for(j = 0; j < strlen(palavraSecreta); j++){
			if(chutes[i] == palavraSecreta[j]){
				
				existe = 1;
				break;
			}	
		} 
		if(!existe)	 erros++;
	} 
	return erros;
}

int enforcou(){

	return chutesErrados() >= 6;	
}

int jachutou(char letra){
	int achou = 0, j;
			
	for(j = 0; j < chutesDados; j++){
		if(chutes[j] == letra){
			achou = 1; 
			break;
		}
	} 

	return achou;
}

void ganhouErrou(){
	if(acertou()){
		printf("\nParabéns, você ganhou!\n\n");
	
	    printf("       ___________      \n");
	    printf("      '._==_==_=_.'     \n");
	    printf("      .-\\:      /-.    \n");
	    printf("     | (|:.     |) |    \n");
	    printf("      '-|:.     |-'     \n");
	    printf("        \\::.    /      \n");
	    printf("         '::. .'        \n");
	    printf("           ) (          \n");
	    printf("         _.' '._        \n");
	    printf("        '-------'       \n\n");
	}else{
		printf("\nPuxa, você foi enforcado!\n");
	    printf("A palavra era **%s**\n\n", palavraSecreta);
	
	    printf("    _______________         \n");
	    printf("   /               \\       \n"); 
	    printf("  /                 \\      \n");
	    printf("//                   \\/\\  \n");
	    printf("\\|   XXXX     XXXX   | /   \n");
	    printf(" |   XXXX     XXXX   |/     \n");
	    printf(" |   XXX       XXX   |      \n");
	    printf(" |                   |      \n");
	    printf(" \\__      XXX      __/     \n");
	    printf("   |\\     XXX     /|       \n");
	    printf("   | |           | |        \n");
	    printf("   | I I I I I I I |        \n");
	    printf("   |  I I I I I I  |        \n");
	    printf("   \\_             _/       \n");
	    printf("     \\_         _/         \n");
	    printf("       \\_______/           \n");
	}	
}

int main() {

	escrevePalavra();
	abertura();
	
	do {
		desenhaForca();		
		chuta();
		
	} while(!acertou() && !enforcou());
	
	ganhouErrou();
	adicionaPalavra();
	return 0;
}




























