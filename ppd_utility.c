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

#include "ppd_utility.h"
#include "ppd_menu.h"
/**
 * @file ppd_utility.c contains implementations of important functions for
 * the system. If you are not sure where to implement a new function, 
 * here is probably a good spot.
 **/

BOOLEAN getString(char* input, size_t size ){

	if(fgets(input,size + 2,stdin) != NULL){
		
	
		int len = strlen(input);
		if(strcmp(&input[0],"\n") == 0)
		{
			return FALSE;
		}
        if (len > 0 && input[len-1] == '\n'){
            input[len-1] = '\0';
			}else{
				read_rest_of_line();
			}
		
	}else
	{
		return FALSE;
	}
return TRUE;
}
int getInt(char* input){
char *ptr;
int ret;
ret = strtol(input,&ptr,10);
return ret;
}
 
void read_rest_of_line(void)
{
    int ch;
    /* keep retrieving characters from stdin until we
     * are at the end of the buffer
     */
    while(ch = getc(stdin), ch!='\n' && ch != EOF)
        ;
    /* reset error flags on stdin */
    clearerr(stdin);
}

/**
 * @param system a pointer to a @ref ppd_system struct that contains
 * all the data in the system we are manipulating
 * @param coins_name the name of the coins file
 * @param stock name the name of the stock file
 **/
BOOLEAN load_data(struct ppd_system * system , const char * coins_name, const char * stock_name)
{
	char lineBuff[256];
	char *token;
	FILE *stockFile;
	FILE *coinFile;
	struct ppd_node * current,* prev;
	int iter =0;
	printf("Loading\n");
	/*system = (struct ppd_system *)malloc(sizeof(struct ppd_system));*/
	/*load the file names*/
	system->coin_file_name = coins_name;
	system->stock_file_name = stock_name;
	/*load the files*/
	
	coinFile = fopen(system->coin_file_name,"r");
	stockFile = fopen(system->stock_file_name,"r");
	if(!stockFile || !coinFile){
		printf("%s", system->stock_file_name);
		printf("Files Failed to load");
		return FALSE;
	}
	/*STRTOK to read and break up file	
	load the stock*/
	while(fgets(lineBuff,sizeof(lineBuff),stockFile) != NULL){
		struct ppd_node * temp;
		token = strtok(lineBuff,"|");
		temp = malloc(sizeof(struct ppd_node));
		temp->data = malloc(sizeof(struct ppd_stock));
		
		while(token != NULL){
			/*at this point i need to insert into the linked list*/
			strcpy(temp->data->id , token);
			token = strtok(NULL,"|");
			strcpy(temp->data->name, token);
			token = strtok(NULL,"|");
			strcpy(temp->data->desc , token);
			/*token = strtok(NULL,"|");
			printf("%s \n",strtok(token,"."));
			printf("%s \n",strtok(NULL,"."));*/
			temp->data->price.dollars = atoi(strtok(NULL,"."));/*current*/
			temp->data->price.cents = atoi(strtok(NULL,"|"));
			/*strcpy(temp->data->price , token);*/
			
			token = strtok(NULL,"|");
			temp->data->on_hand = atoi(token);
			token = strtok(NULL,"|");
			/*Updated insert to sort by name*/
			if(system->item_list->head == NULL)
			{
				system->item_list->head = temp;
				system->item_list->head->next=NULL;
				system->item_list->count++;
			}else
			{
				prev = NULL;
				current = system->item_list->head;
				
				while(current!=NULL)
				{
					if(strcmp(current->data->name, temp->data->name) > 0)
					{
						if(prev == NULL)
						{
							 temp->next = system->item_list->head;
							 system->item_list->head = temp;
							 system->item_list->count++;
							  break;
						}
						else
						{
							prev->next = temp;
							temp->next = current;
							system->item_list->count++;
							 break;
						}
						
					}
					prev = current;
					current = current->next;
					if(current == NULL){
						prev->next = temp;
							temp->next = current;
							system->item_list->count++;
							 break;
						
						
					}
					printf(".");
				}
			}
			
			/*if(system->item_list->head == NULL){
				system->item_list->head = temp;
				system->item_list->count++;
				system->item_list->head->next=NULL;
	
			}else{
				current = system->item_list->head;
				while(current->next!= NULL)
				{	if(strcmp(temp->data->name,current->data->name) > 0){
					printf("LELELELELELELE");
					break;
				}
					current = current->next;
				}
				system->item_list->count++;
				temp->next = current->next;
				current->next = temp;			
			}*/
		}
		
	}

	fclose(stockFile);
	
	
	
	/*load the coins*/
	while(fgets(lineBuff,sizeof(lineBuff),coinFile) != NULL){
		token = strtok(lineBuff,",");
		
		while(token != NULL){
			system->cash_register[iter].denom = atoi(token);
			token = strtok(NULL,",");
			system->cash_register[iter].count = atoi(token);
			token = strtok(NULL,",");
		}
		printf(".");
		/*printf("%i : ",system->cash_register[iter].denom);
		printf("%i \n",system->cash_register[iter].count);*/
		iter++;
		
	}
	
	fclose(coinFile);
	printf(".\n");
	
    return TRUE;
}
/**
 * @param system a pointer to a @ref ppd_system struct that holds all 
 * the data for the system we are creating
 **/
BOOLEAN system_init(struct ppd_system * system)
{	/*struct ppd_list* item_list;
	item_list = (struct ppd_list*)malloc(sizeof(struct ppd_list ));*/
	system->item_list = (struct ppd_list*)malloc(sizeof(struct ppd_list ));
	system->item_list->head = NULL;
	system->item_list->count = 0;
	system->coin_file_name = NULL;
	system->stock_file_name = NULL;
    /*
     * Please delete this default return value once this function has 
     * been implemented. Please note that it is convention that until
     * a function has been implemented it should return FALSE
     */
    return FALSE;
}

/**
 * @param system a pointer to a @ref ppd_system struct that holds all 
 * the data for the system we are creating
 **/
BOOLEAN system_free(struct ppd_system * system)
{
	struct ppd_node *current, *next;
	current = system->item_list->head;
	while (current != NULL){
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	free(system->item_list);
	return TRUE;
}
