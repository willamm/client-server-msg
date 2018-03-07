/*
 * =====================================================================================
 *
 *       Filename:  client_main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018-03-05 12:58:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Will Murphy (wm), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "mesg.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main()
{
	int write = Msgget(MQ_KEY, 0);
	client(write, write);
	return EXIT_SUCCESS;
}/* ----------  end of function main  ---------- */

