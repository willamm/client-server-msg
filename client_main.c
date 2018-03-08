/*
 * =====================================================================================
 *
 *       Filename:  client_main.c
 *
 *    Description:  Contains the main function of the client program.  
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
 *  Description:  Takes 1 command line parameter, which is the client's priority. 
 *  		It also gets the server's message queue file descriptor, and 
 *  		passes it to the client function, along with the client's priority.
 * =====================================================================================
 */
int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s priority\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int priority;
	if ((priority = atoi(argv[1])) == 0)
	{
		fprintf(stderr, "Invalid priority\n");
		exit(EXIT_FAILURE);
	}
	int write = Msgget(MQ_KEY, 0);
	client(write, write, priority);
	return EXIT_SUCCESS;
}/* ----------  end of function main  ---------- */

