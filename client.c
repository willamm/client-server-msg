/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018-03-05 01:15:38 PM
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
 *         Name:  client
 *  Description:  
 * =====================================================================================
 */
void client(int readFd, int writeFd)
{
	// Forever loop so that the client program doesn't need to be run multiple times
	while (true)
	{	
		Message mesg;
		sprintf(mesg.data, "%ld", (long) getpid());
		strcat(mesg.data, " ");
		printf("Enter a file that the server will open: ");
		char buffer[1024];

		if (fgets(buffer, 1024, stdin) == NULL)
		{
			perror("fgets");
			continue;
		}
		char fileName[1024];
		if (sscanf(buffer, "%s", fileName) != 1)
		{
			perror("sscanf");
			continue;
		}
		// Strips newline character from filename 
		fileName[strcspn(fileName, "\n")] = '\0';
		size_t spaceLoc = strcspn(mesg.data, " ") + 1;
		if (sprintf(mesg.data + spaceLoc, "%s", fileName) < 0)
		{
			perror("sprintf");
			continue;
		}

		// Set the message members before the message is sent
		mesg.length = strlen(mesg.data);
		mesg.type = 1;

		send_message(writeFd, &mesg);

		mesg.type = getpid();
		
		// Because we check that the length of the received message is > 0,
		// we send a 0 length message from the server to signify that
		// the server is done with the client request
		//
		// Should use a thread for a non blocking message receive
		// so the client program can quit if no messages ready
		
		while (true)
		{
			// Determine priority here?
			if (read_message(readFd, getpid(), &mesg) == -1)
			{
				break;
			}
			printf("Message data: %s\n", mesg.data);
			printf("Message length: %d\n", mesg.length);
		}
		// Add a signal handler for exiting the client process
	}
}/* -----  end of function client  ----- */
