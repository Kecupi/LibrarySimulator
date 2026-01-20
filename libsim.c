/*
 * @file libsim.c
 * @author Stepan Horenek
 * @date 20-01-2026
 * @desc Simple library simulator
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Function for operating Bookworm role
 */

void bookworm_mode(){
	int bw_state = 0;
	while (true){
		printf("One of the few that still bother reading nowadays... Here are you choices:\n\t");
		printf("1. Lend book\n\t"
			"2. Return book\n\t"
			"3. Browse catalog\n\t"
			"4. Return to main menu");
		scanf("%d", &bw_state);
		printf("State chosen: %d\n", bw_state);
	}
}

/*
 * Function for operating Librarian role
 */
void librarian_mode(){
	int lb_state = 0;
	while (true){
		printf("Good to see someone still operates this place... Here are your possibilities:\n\t");
		printf("1. Add book\n\t"
			"2. Remove book\n\t"
			"3. Browse catalog\n\t"
			"5. Shush\n\t"
			"4. Open library\n\t"
			"5. Close library\n\t"
			"6. Return to main menu\n");
		scanf("%d", &lb_state);
		printf("State chosen: %d\n", lb_state);
	}
}

/*
 * Finite-state automaton operating based on input
 * @param input variable to store last user input
 */
void mode_switch(int* input){
	while (true){
		scanf("%d", input);
		switch(*input){
			case 1:
				bookworm_mode();
				return;
			case 2:
				librarian_mode();
				return;
			case 3: 
				printf("Library exited successfully, see you next time!\n");
				return;
			default:
				printf("Invalid input, please try again\n");
				break;
		}
	}
}

int main (){
	int input = 0;
	while (true){
		printf("Welcome to LibSim, choose one of the following to proceed:\n");
		printf("\t1. Bookworm role\n\t2. Librarian role\n\t3. Exit library\n");
		mode_switch(&input);
		if (input == 3){
			break;
		}
	}
	return 0;
}
