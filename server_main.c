/*
 * =====================================================================================
 *
 *       Filename:  server_main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018-03-05 12:41:31 PM
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
	// The server needs to create the message queue
	int read = Msgget(MQ_KEY, IPC_CREAT | 0660);

	server(read, read);

	return EXIT_SUCCESS;
}/* ----------  end of function main  ---------- */
