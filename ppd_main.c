/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2015 Assignment #2 
 * Full Name        : Wolf Zimmermann
 * Student Number   : S3495671
 * Course Code      : COSC1076
 * Program Code     : BP094
 * Start up code provided by Paul Miller
 * Some codes are adopted here with permission by an anonymous author
 ***********************************************************************/

#include "ppd_main.h"
#include "ppd_menu.h"
#include "ppd_options.h"
#include "ppd_utility.h"

/**
 * @file ppd_main.c contains the main function implementation and any 
 * helper functions for main such as a display_usage() function.
 **/

/**
 * manages the running of the program, initialises data structures, loads
 * data and handles the processing of options. The bulk of this function
 * should simply be calling other functions to get the job done.
 **/
int main(int argc, char** argv)
{
	/* represents the data structures to manage the system */
	BOOLEAN isQuit = FALSE;
    struct ppd_system system;
	struct menu_item menu[MENU_SIZE];
	
    /* validate command line arguments */
	if(argc != 3){
		printf("Incorrect args passed!");
	
		return EXIT_FAILURE;
	}
	

    /* init the system */
	system_init(&system);
	/* load file names*/
	/* load data */
	 load_data(&system , argv[2], argv[1]);
	 	
    /* test if everything has been initialised correctly */
    /* initialise the menu system */
	
	init_menu(menu);
	

		
   
	while(isQuit == FALSE){
	 /* loop, asking for options from the menu */
	int i;
	char choice[3];
	int selector;
	BOOLEAN readSucess=FALSE;
		for(i = 0; i < MENU_SIZE; i++){
			if(i == 0){
				printf("\nMain Menu\n");
			}
			  
			if(i == 3){
				printf("Admin Menu\n");
			}
			printf("   %i. %s \n",i+1,menu[i].name);
		}
		printf("Select you option (1-9): ");
			
		/* run each option selected */
		
		choice[2] =0;
		while(readSucess == FALSE){
			if(getString(choice,sizeof(choice))== TRUE){
			selector=atoi(choice);
			readSucess = TRUE;
			}else{
				printf("Input is invalid please try again: ");
			}
			/*if(fgets(choice,2+1,stdin) != 0){
				int len = strlen(choice);
				if (len > 0 && choice[len-1] == '\n'){
					choice[len-1] = '\0';
					readSucess=TRUE;
					selector=atoi(choice);
				}else{
					read_rest_of_line();
				
				}
			}else{
				read_rest_of_line();
				printf("Input is invalid please try again: ");
			}*/
		
			
		}
		
		if(selector == 9){
			menu[selector-1].function(&system);
			isQuit = TRUE;
		}else{
			menu[selector-1].function(&system);
		}
	}
    /* until the user quits */


    /* make sure you always free all memory and close all files 
     * before you exit the program
     */
    return EXIT_SUCCESS;
}
