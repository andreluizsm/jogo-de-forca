#include <stdio.h>
#include <string.h>

int main() {
	
	char palavraSecreta[20],chutes[26];
	
	sprintf(palavraSecreta,"melancia");
	
	int acertou = 0,enforcou = 0,tentativas = 0;
	
	do {
		int i;
		for(i = 0; i < strlen(palavraSecreta); i++) {
			
			int achou = 0,j;
			
			for(j = 0; j < tentativas; j++){
				if(chutes[j] == palavraSecreta[i]){
					achou = 1;
					break;
				}
			} 
				
			if(achou == 1){
				printf(" %c ",palavraSecreta[i]);
			}else{
				printf("_ ");
			}
		}
		
		printf("\n\n");
		
		char chute;
		printf("Escreta seu chute:");
		scanf(" %c",&chute);
	
		chutes[tentativas] = chute;
		tentativas++;
	} while(!acertou && !enforcou);
	
	return 0;
}




























