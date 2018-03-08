/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    Description: Source file for the main server function. Contains only the server
 *    			function.
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
		// The message type for message from the client to the server is 1
		mesg.type = 1;
		if ((messageSize = mesg_recv(read, &mesg)) == 0)
		{
			fprintf(stderr, "Pathname missing\n");
			continue;
		}
		mesg.data[messageSize] = '\0';
		if ((fileName = strchr(mesg.data, ' ')) == NULL)
		{
			fprintf(stderr, "Bad request: %s\n", mesg.data);
			continue;
		}
		// Null terminate the filename
		*fileName++ = '\0';
		clientPid = atol(mesg.data);
		printf("Received message from client with PID = %ld\n", (long) clientPid);
		// Fork child process to service client request
		if (fork() == 0)
		{
			mesg.type = (long) clientPid;
			if ((fileToSend = fopen(fileName, "r")) == NULL)
			{
				// Tell the client that the file was unable to be opened
				size_t numToWrite = sizeof(mesg.data);
				snprintf(mesg.data + messageSize, numToWrite, ": can't open the file. %s. \n", strerror(errno)); 
				mesg.length = strlen(fileName);
				// We do this to avoid the message sent to the client from being overwritten
				memmove(mesg.data, fileName, mesg.length);
				if (mesg_send(write, &mesg) == -1)
				{
					perror("msgsnd");
					continue;
				}
			}
			else 
			{
				while (fgets(mesg.data, MAXMESSAGEDATA, fileToSend) != NULL)
				{
					mesg.length = strlen(mesg.data);
					mesg_send(write, &mesg);
				}
				if (fclose(fileToSend) == EOF)
				{
					perror("fclose");
					continue;
				}
			}
			// Send 0 length message to client to signal that the server is done sending
			mesg.length = 0;
			mesg_send(write, &mesg);
			exit(EXIT_SUCCESS);
		}
	}
}/* -----  end of function server  ----- */
