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

#include <stdio.h>
#include <string.h>
#include "ppd_main.h"
#ifndef PPD_UTILITY
#define PPD_UTILITY
/**
 * @file ppd_utility.h defines some helper functions for the rest of your
 * program. In particular, it declares three of the most important 
 * functions for your application: @ref load_data which loads the data
 * in from files, @ref system_init which initialises the system to a 
 * known safe state and @ref system_free which frees all memory when you
 * are going to quit the application.
 **/
BOOLEAN getString(char*, size_t);
int getInt(char*);
/**
 * the function to call for buffer clearing. This was discussed extensively
 * for assignment 1
 **/
void read_rest_of_line(void);

/**
 * function which is called to load the coin and stock data into the 
 * system. You should ideally break this function up into smaller parts
 * to load the stock and the coins. You will also need to assign the 
 * char pointers to the stock and coin file names here so that the same
 * names will be used for save. A key part of this function is input
 * validation. A substantial number of marks are allocated to this function
 * - half are allocated to getting this function working and the other
 * half for rejecting invalid files. Please don't see file validation
 * as an optional extra but it is a central component of this assignment.
 **/
BOOLEAN load_data(struct ppd_system * , const char * , const char * );

/**
 * Initialise the system to a known safe state. Before you post on the
 * discussion board about this, have a look at the structures as defined
 * in ppd_stock.h, ppd_coin.h and ppd_main.h. Given that nothing is 
 * initialized by the system if it
 * is a local variable, what would be good starting values for each of 
 * these. You already have some experience with this from assignment 
 * 1 to help you.
 **/
BOOLEAN system_init(struct ppd_system *);

/**
 * free all memory that has been allocated. If you are struggling to
 * find all your memory leaks, compile your program with the -g flag
 * and run it through valgrind. An important thing to think about here:
 * as malloc() returns a memory address to the first byte allocated, you
 * must pass each of these memory addresses to free, and no other 
 * memory addresses.
 **/
BOOLEAN system_free(struct ppd_system *);
#endif
