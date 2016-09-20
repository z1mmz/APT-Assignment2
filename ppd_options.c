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

#include "ppd_options.h"
#include <math.h>

/**
 * @file ppd_options.c this is where you need to implement the main 
 * options for your program. You may however have the actual work done
 * in functions defined elsewhere. 
 * @note if there is an error you should handle it within the function
 * and not simply return FALSE unless it is a fatal error for the 
 * task at hand. You want people to use your software, afterall, and
 * badly behaving software doesn't get used.
 **/

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true as this particular function should never fail.
 **/
BOOLEAN display_items(struct ppd_system * system)
{
	struct ppd_node* temp;

	temp = system->item_list->head;
	printf("Items Menu\n----------\n");
	printf("%-5s| %-20s| %-10s| %s\n","ID","Name","Available","Price");
	while(temp != NULL){
			printf("%-5s",temp->data->id);
			printf("| %-20s",temp->data->name);
			printf("| %-10i",temp->data->on_hand);
			printf("| $%i.%i\n",temp->data->price.dollars,temp->data->price.cents);
			temp = temp->next;
	}
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true when a purchase succeeds and false when it does not
 **/
BOOLEAN purchase_item(struct ppd_system * system)
{
	struct ppd_node* temp;
	BOOLEAN wasSold;
	int i;
	double price , origPrice;
	char itemID[IDLEN];
	int totalInput;
	int change;
	temp = system->item_list->head;
	wasSold = TRUE;
	printf("Purchase Item\n----------\n");
	printf("Please enter the id of the item you wish to purchase: ");
	/*if(fgets(itemID,IDLEN+2,stdin) != 0){
		int len = strlen(itemID);
        if (len > 0 && itemID[len-1] == '\n')
            itemID[len-1] = '\0';
	}*/
	if (getString(itemID,sizeof(itemID))== FALSE)
		{
			return FALSE;
		}
	for(i = system->item_list->count;i > 0; i--){
		if(strcmp(temp->data->id,itemID) == 0 ){
			break;
		}else{
			temp = temp->next;
		}

		
	}
	if(!temp){
		printf("Item is not valid\n");
		return FALSE;
	}

	price = temp->data->price.dollars * 100;
	price += temp->data->price.cents;
	origPrice = price;
	
	printf("You have selected \"%s - %s. This will cost you $%.2f\n ",temp->data->name,
	temp->data->desc,price/100);
	printf("Please hand over the money – type in the value of each note/coin in cents\n");
	printf("Press enter or ctrl­d on a new line to cancel this purchase: ");
	
	while(price > 0.0){
		
		BOOLEAN inputValid = FALSE;
		char input[6];
		
		printf("You still need to give us $%.2f : ",price/100);
		while(inputValid == FALSE){
			
			if(getString(input,sizeof(input)) == TRUE){
				int len = strlen(input);
					int inputValue;
					int i;
					BOOLEAN isInputValid = FALSE;
					input[len-1] = '\0';
					inputValid = TRUE;
					inputValue = atoi(input);
					
					for(i=0; i < NUM_DENOMS;i++){
						if (inputValue == system->cash_register[i].denom ){
							system->cash_register[i].count++; 
							price -=inputValue;
							totalInput += inputValue;
							isInputValid = TRUE;
							
						}
					}
					if(isInputValid==FALSE){
						printf("Error: $%.2f is not a valid denomination of money\n", (double)inputValue/100);
					}
				
			}else{
				printf("Exiting transaction and refunding\n");
				price =  price - origPrice;
				wasSold = FALSE;
				break;
				
			}
			/*if(fgets(input,6+2,stdin)!=NULL){
				int len = strlen(input);
				if(len > 0 && input[len-1]=='\n'){
					int inputValue;
					
					int i;
					BOOLEAN isInputValid = FALSE;
					input[len-1] = '\0';
					inputValid = TRUE;
					inputValue = atoi(input);
					
					for(i=0; i < NUM_DENOMS;i++){
						if (inputValue == system->cash_register[i].denom ){
							system->cash_register[i].count++; 
							price -=inputValue;
							totalInput += inputValue;
							isInputValid = TRUE;
						}
					}
					if(isInputValid==FALSE){
						printf("Error: $%.2f is not a valid denomination of money\n", (double)inputValue/100);
					}
					
					
				}else{
						read_rest_of_line();
						printf("Input is invalid please try again: ");
					}
			}else{
				read_rest_of_line();
				printf("Input is invalid please try again: ");
			}*/
			
		}
		
	}
	
	
	printf("Dispensing $%.2f Change: ",fabs(price/100));
	change = fabs(price);
	while(change > 0){
		int i;
		int found;
		found=0;
		for(i = 0; i < NUM_DENOMS;i++){
			
			if(system->cash_register[i].denom <= change && system->cash_register[i].count > 0){
				system->cash_register[i].count--;
				change -= system->cash_register[i].denom;
				printf(" $%.2f  ",(double)system->cash_register[i].denom /100);
				found++;
			}
			
		}
		if(found == 0){
			
			printf("Cannot give change");
		}
		printf("\n");
		
	}
	
	if(wasSold == TRUE){
	temp->data->on_hand--;
	}

    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true when a save succeeds and false when it does not
 **/
BOOLEAN save_system(struct ppd_system * system)
{
   FILE *stockFile;
   FILE *coinFile;
   int i;
   struct ppd_node * current;
   stockFile = fopen(system->stock_file_name,"w");
   coinFile = fopen(system->coin_file_name,"w");
   current = system->item_list->head;
  while(current != NULL)
	{
		fprintf(stockFile,"%s|%s|%s|%i.%i|%i\n",current->data->id,current->data->name,current->data->desc,current->data->price.dollars,current->data->price.cents,current->data->on_hand);
		current = current->next;
	}
	for(i = 0; i < NUM_DENOMS;i++)
	{
		fprintf(coinFile,"%i,%i\n",system->cash_register[i].denom,system->cash_register[i].count);
		
	}
	
   
   

   fclose(stockFile);
   fclose(coinFile);
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true when adding an item succeeds and false when it does not
 **/
BOOLEAN add_item(struct ppd_system * system)
{
	struct ppd_node *current,*prev;
	struct ppd_node *tempN;
	char name[NAMELEN];
	char itemCode[IDLEN];
	char desc[DESCLEN];
	char price[254];
	char* dollar;
	char* cents;
	char onhand[254];
	prev = NULL;
	current = system->item_list->head;
	tempN = malloc(sizeof(struct ppd_node));
	tempN->next = NULL;
	tempN->data = malloc(sizeof(struct ppd_stock));
	printf("Enter item code: ");
	/*if ctrl d or new line is entered free tempN*/
	if(getString(itemCode,sizeof(itemCode)) == FALSE)
	{
		free(tempN->data);
		free(tempN);
		return FALSE;
	}
	printf("Enter name: ");
	if(getString(name,sizeof(name))== FALSE)
	{
		free(tempN->data);
		free(tempN);
		return FALSE;
	}
	printf("Enter description: ");
	if(getString(desc,sizeof(desc))== FALSE)
	{		
		free(tempN->data);
		free(tempN);
		return FALSE;
	}
	printf("Enter Cost: ");
	if (getString(price,sizeof(price))== FALSE)
	{
		free(tempN->data);
		free(tempN);
		return FALSE;
	}
	dollar = strtok(price,".");
	cents = strtok(NULL,".");
	tempN->data->price.dollars = getInt(dollar);
	tempN->data->price.cents = getInt(cents);
	printf("Enter Amount on hand: ");
	getString(onhand,sizeof(onhand));
	tempN->data->on_hand = getInt(onhand);
	strcpy(tempN->data->id,itemCode);
	strcpy(tempN->data->name,name);
	strcpy(tempN->data->desc,desc);

	while(current!=NULL)
				{
					/*Sort by name*/
					if(strcmp(current->data->name, tempN->data->name) > 0)
					{
					
						if(prev == NULL)
						{
							 tempN->next = system->item_list->head;
							 system->item_list->head = tempN;
							 system->item_list->count++;
							 break;
						}
						else
						{
							prev->next = tempN;
							tempN->next = current;
							system->item_list->count++;
							 break;
						
						}
						
					}
					prev = current;
					current = current->next;
					if(current == NULL){
						prev->next = tempN;
							tempN->next = current;
							system->item_list->count++;
							 break;
						
						
					}
					
				}
	/*while(current != NULL){
		if(strcmp(current->data->name, tempN->data->name) > 0)
					{
							 printf("LOOPED\n");
					if(current->next == NULL){break;};
					prev = current;
					current = current->next;
					
						
					}else{
						break;
					}
				
	}
	if(prev == NULL)
			{
				 tempN->next = system->item_list->head;
				 system->item_list->head = tempN;
				 system->item_list->count++;
				 printf("added using head!");
		
			}else
			{
				prev->next = tempN;
							tempN->next = current;
							system->item_list->count++;
				printf("added!");
			
			
			}
	
	while(foundPlace == FALSE){
		
		while(current != NULL){
				if(atoi(current->data->id) < atoi(tempN->data->id)){
				printf("FOUND");
				}
			
			
		}
		current = current->next;
		
	}*/
    
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true when removing an item succeeds and false when it does not
 **/
BOOLEAN remove_item(struct ppd_system * system)
{
	struct ppd_node *current,*prev = NULL;
	char id[IDLEN];
	printf("Enter the item id of the item to remove from the menu: ");
	if(getString(id,sizeof(id))== FALSE){
		return FALSE;
	}
	current = system->item_list->head;
	while (current != NULL){
		if(strcmp(current->data->id,id) == 0){
			printf("\"%s - %s - %s\" \nhas been remove from the system",current->data->id,current->data->name,current->data->desc);
			/*If head*/
			if(prev == NULL){
				system->item_list->head = current->next;
				free(current->data);
				free(current);
				
				system->item_list->count--;
				break;
			}
			else{ /*If not head*/
				prev->next = current->next;
				free(current->data);
				free(current);
				system->item_list->count--;
				break;
			
			}
			
		
		}
		prev = current;
		current = current->next;
		
	}

        return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true as this function cannot fail.
 **/
BOOLEAN reset_stock(struct ppd_system * system)
{
	struct ppd_node *current;
	current = system->item_list->head;
	while (current != NULL){
		current->data->on_hand = DEFAULT_STOCK_LEVEL;
		current = current->next;
	}
	printf("“All stock has been reset to the default level of %i\n",DEFAULT_STOCK_LEVEL);
	
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true as this function cannot fail.
 **/
BOOLEAN reset_coins(struct ppd_system * system)
{
	int i;
	for(i = 0; i < NUM_DENOMS; i++)
	{
		system->cash_register[i].count = DEFAULT_COIN_COUNT;
	}
		printf("“All coins has been reset to the default level of %i\n",DEFAULT_COIN_COUNT);
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true as this function cannot fail
 **/
BOOLEAN display_coins(struct ppd_system * system)
{
	int i;
	printf("Coins Summary\n---------------------\n%10s | %5s\n---------------------\n","Denomination","Count");
	for(i =  NUM_DENOMS -1; i >= 0; i--)
	{
		printf("%-10.2f | %5i\n",(double)system->cash_register[i].denom /100,system->cash_register[i].count);
	}
	
    return TRUE;
}

