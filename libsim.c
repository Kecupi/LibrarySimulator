#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void mode_switch(int* input){
	while (true){
		scanf("%d", input);
		switch(*input){
			case 1:
				printf("Welcome User:\n");
				return;
			case 2:
				printf("Welcome Librarian:\n");
				return;
			default:
				printf("Invalid input, please try again\n");
				break;
		}
	}
}

int main (){
	int input = 0;
	printf("Welcome to LibSim, choose one of the following to proceed:\n");
	printf("\t1. User interface\n\t2. Librarian interface\n");
	mode_switch(&input);
	return 0;
}
