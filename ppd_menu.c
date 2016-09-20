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

#include "ppd_menu.h"
/**
 * @file ppd_menu.c handles the initialised and management of the menu 
 * array
 **/

/**
 * @param menu the menu item array to initialise
 **/
void init_menu( struct menu_item* menu)
{
	
	struct menu_item tempMenu[MENU_SIZE] ={
		{"Display Items",display_items},
		{"Purchase Items",purchase_item},
		{"Save and exit",save_system},
		{"Add Item",add_item},
		{"Remove Item",remove_item},
		{"Display Coins",display_coins},
		{"Reset Stock",reset_stock},
		{"Reset Coins",reset_coins},
		{"Abort Program",system_free}
	};
	int i;
	for(i =0 ; i < MENU_SIZE ; i++){
		menu[i]=tempMenu[i];
	}
	/* No longer using as causing memory issues
	memcpy(menu,tempMenu,sizeof(tempMenu));*/
}
