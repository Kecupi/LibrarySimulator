/*
 * @file libsim.c
 * @author Stepan Horenek
 * @date 20-01-2026
 * @desc Simple library simulator
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFF_LEN 52

/*
 * @desc Function for clearing buffer
*/
void clear_buffer(){
	int c = 0;
	while((c = getchar()) != '\n' && c != EOF);
}

/*
 * @desc Function for checking whether input isn't bigger than buffer
 * @param input pointer to buffer to check
*/

int check_input_size(char* input){
	char* tmp = strrchr(input, '\n');
	if (tmp == NULL){
		clear_buffer();
		return 1;
	} else {
		return 0;
	}

}

/*
 * @desc Function for loading data about books from stdin and then saving them into file
 * @return 0 if successful, 1 if error occurs
*/

int add_book(){
	char* tmp_author = malloc(sizeof(char)*BUFF_LEN);
	if (tmp_author == NULL){
		fprintf(stderr, "Error: Couldn't allocate memory for new book\n");
		return 1;
	}
	char* tmp_book = malloc(sizeof(char)*BUFF_LEN);
	if (tmp_book == NULL){
		fprintf(stderr, "Error: Couldn't allocate memory for new book\n");
		free(tmp_author);
		return 1;
	}
	int tmp_year = 1900;
	clear_buffer();
	printf("\nType name of author:\n\n");
	fgets(tmp_author, BUFF_LEN, stdin);
	if ((check_input_size(tmp_author)) != 0){
		fprintf(stderr, "Error: Too many characters on input (limit %d)\n", BUFF_LEN);
		free(tmp_author);
		free(tmp_book);
		return 1;
	}
	printf("\nType name of book:\n\n");
	fgets(tmp_book, BUFF_LEN, stdin);
	if ((check_input_size(tmp_book)) != 0){
		fprintf(stderr, "Error: Too many characters on input (limit %d)\n", BUFF_LEN);
		free(tmp_author);
		free(tmp_book);
		return 1;
	}
	printf("\nType year of publishing:\n\n");
	scanf("%d", &tmp_year);
	tmp_author[strcspn(tmp_author, "\n")] = '\0';
	tmp_book[strcspn(tmp_book, "\n")] = '\0';
	printf("%s %s %d\n", tmp_author, tmp_book, tmp_year);
	FILE* soubor = fopen("catalog.txt", "a"); // opens book database or creates new one if not present
	fprintf(soubor, "%s, %s, %d\n", tmp_author, tmp_book, tmp_year);
	fclose(soubor);
	free(tmp_author);
	free(tmp_book);
	return 0;
}

int browse_catalog(){
	FILE* soubor = fopen("catalog.txt", "r");
	if (soubor == NULL){
		fprintf(stderr, "\nThe library is unfortunately empty right now >:(\n\n");
		return 1;
	} else {
		char* tmp_author = malloc(sizeof(char)*BUFF_LEN);
		if (tmp_author == NULL){
			fprintf(stderr, "\nError: Couldn't allocate memory for new book\n\n");
			return 1;
		}	
		char* tmp_book = malloc(sizeof(char)*BUFF_LEN);
		if (tmp_book == NULL){
			fprintf(stderr, "\nError: Couldn't allocate memory for new book\n\n");
			free(tmp_author);
			return 1;
		}
		int tmp_year;
		int status = 0;
		while ((status = fscanf(soubor, "%51[^,], %51[^,], %d\n", tmp_author, tmp_book, &tmp_year)) != EOF){
			if (status != 3){
				fprintf(stderr, "\nError: Invalid book database string\n\n");
				free(tmp_author);
				free(tmp_book);
				fclose(soubor);
				return 1;
			}
			printf("\n%s, %s, %d\n", tmp_author, tmp_book, tmp_year);
		}
		free(tmp_author);
		free(tmp_book);
		fclose(soubor);
		return 0;
	}
}

/*
 * @desc Function for operating Bookworm role
 * @param available status whether library is open or not
 */

void bookworm_mode(bool* available){
	if (*available == false){
		printf("\nYou try to open the door with all your strenght, but the door won't budge... Maybe another time\n\n");
		return;
	} else {
		int bw_state = 0;
		printf("\nOne of the few that still bother reading nowadays... Here are you choices:\n");
		while (true){
			printf("\n\t1. Lend book\n\n"
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
					browse_catalog();
					break;
				case 4:
					return;
				default:
					printf("\nInvalid input, please try again\n\n");
					break;	
			}
		}
	}
}

/*
 * @desc Function for operating Librarian role
 * @param available status whether library is open or not
 */
void librarian_mode(bool* available){
	int lb_state = 0;
	printf("\nGood to see someone still operates this place... Here are your possibilities:\n");
	while (true){
		printf("\n\t1. Add book\n\n"
			"\t2. Remove book\n\n"
			"\t3. Browse catalog\n\n"
			"\t4. Shush\n\n"
			"\t5. Open library\n\n"
			"\t6. Close library\n\n"
			"\t7. Return to main menu\n\n");
		scanf("%d", &lb_state);
		switch (lb_state){
			case 1:
				add_book();
				break;
			case 2:
				return;
			case 3:
				browse_catalog();
				break;
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
 * @desc Finite-state automaton operating based on input
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
