/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018-03-05 12:55:03 PM
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
 *         Name:  server
 *  Description:  
 * =====================================================================================
 */
void server(int read, int write)
{
	FILE* fileToSend;
	char* fileName;
	pid_t clientPid;
	int messageSize;
	Message mesg;

	signal(SIGCHLD, SIG_IGN);
	
	while (true)
	{
		if ((messageSize = read_message(read, 1, &mesg)) == -1)
		{
			fprintf(stderr, "Pathname missing\n");
			continue;
		}
		// Determine the priority of the client. In this program, priority 
		// determines the speed at which the client will receive a message
		printf("Size of message: %d\n", messageSize);
		mesg.data[messageSize] = '\0';
		if ((fileName = strchr(mesg.data, ' ')) == NULL)
		{
			fprintf(stderr, "Bad request: %s\n", mesg.data);
			continue;
		}
		// Null terminate the filename
		*fileName++ = '\0';
		clientPid = atol(mesg.data);
		mesg.type = clientPid;
		printf("Received message from client with PID = %ld\n", (long) clientPid);
		// Fork child process to service client request
		if (fork() == 0)
		{
			if ((fileToSend = fopen(fileName, "r")) == NULL)
			{
				// Tell the client that the file was unable to be opened
				messageSize = strlen(mesg.data);
				snprintf(mesg.data + messageSize, MAXMESSAGEDATA, ": can't open file %s\nfopen: %s\n", fileName, strerror(errno)); 
				mesg.length = strlen(mesg.data);
				send_message(write, &mesg);
			}
			else 
			{
				while (fgets(mesg.data, MAXMESSAGEDATA, fileToSend) != NULL)
				{
					mesg.length = strlen(mesg.data);
					send_message(write, &mesg);
				}
				if (fclose(fileToSend) == EOF)
				{
					perror("fclose");
					exit(EXIT_FAILURE);
				}
			}
			// Send 0 length message to client to signal that the server is done sending
			mesg.length = 0;
			send_message(write, &mesg);
			exit(EXIT_SUCCESS);
		}
	}
}/* -----  end of function server  ----- */
