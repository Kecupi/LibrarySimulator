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
 * @param available status whether library is open or not
 */

void bookworm_mode(bool* available){
	if (*available == false){
		printf("\nYou try to open the door with all your strenght, but the door won't budge... Maybe another time\n\n");
		return;
	} else {
		int bw_state = 0;
		printf("\nOne of the few that still bother reading nowadays... Here are you choices:\n\n");
		while (true){
			printf("\t1. Lend book\n\n"
			"\t2. Return book\n\n"
			"\t3. Browse catalog\n\n"
			"\t4. Return to main menu\n\n");
			scanf("%d", &bw_state);
			switch(bw_state){
				case 1:
					return;
				case 2:
					return;
				case 3:
					return;
				case 4:
					return;
			}
		}
	}
}

/*
 * Function for operating Librarian role
 * @param available status whether library is open or not
 */
void librarian_mode(bool* available){
	int lb_state = 0;
	printf("\nGood to see someone still operates this place... Here are your possibilities:\n\n");
	while (true){
		printf("\t1. Add book\n\n"
			"\t2. Remove book\n\n"
			"\t3. Browse catalog\n\n"
			"\t4. Shush\n\n"
			"\t5. Open library\n\n"
			"\t6. Close library\n\n"
			"\t7. Return to main menu\n\n");
		scanf("%d", &lb_state);
		switch (lb_state){
			case 1:
				return;
			case 2:
				return;
			case 3:
				return;
			case 4:
				printf("\nYou shush from top of your lungs... Noone is around so nothing happens\n\n");
				break;
			case 5:
				if (*available == false){
					*available = true;
					printf("\nAs you open the doors of library, sharp sun rays blind you for a second... Library is now open\n\n");
				} else {
					printf("\nYou feel weird wind whispering to you: The library is already open...\n\n");
				}
				break;
			case 6:
				if (*available == true){
					*available = false;
					printf("\nAs you close the door, a stray at runs outside the library and you just shrug... Library is now closed\n\n");
				} else {
					printf("\nYou feel weird wind whispering to you: The library is already open...\n\n");
				}	
				break;
			case 7:
				return;
			default:
				printf("\nInvalid input, please try again\n\n");
				break;
		}
	}
}

/*
 * Finite-state automaton operating based on input
 * @param input variable to store last user input
 */
void mode_switch(int* input, bool* available){
	while (true){
		scanf("%d", input);
		switch(*input){
			case 1:
				bookworm_mode(available);
				return;
			case 2:
				librarian_mode(available);
				return;
			case 3: 
				printf("\nLibrary exited successfully, see you next time!\n\n");
				return;
			default:
				printf("\nInvalid input, please try again\n\n");
				break;
		}
	}
}

int main (){
	int input = 0;
	bool available = false;
	while (true){
		printf("\nWelcome to LibSim, choose one of the following to proceed:\n");
		printf("\n\t1. Bookworm role\n\n\t2. Librarian role\n\n\t3. Exit library\n");
		mode_switch(&input, &available);
		if (input == 3){
			break;
		}
	}
	return 0;
}
