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
#include <time.h>
#include <pthread.h>

#include "mesg.h"

static const unsigned long base_wait = 10000000L;
static clock_t timer;
static pthread_mutex_t timerLock = PTHREAD_MUTEX_INITIALIZER;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  timer
 *  Description:  Causes the client to terminate after around 10 seconds
 * =====================================================================================
 */
static void* timeout(void* arg)
{
	(void) arg;
	clock_t diff;
	while(true)
	{
		pthread_mutex_lock(&timerLock);
		diff = clock() - timer;
		pthread_mutex_unlock(&timerLock);
		unsigned ms = diff * 1000 / CLOCKS_PER_SEC;
		if (ms > 10000)
		{
			break;
		}

	}
	printf("\nClient timed out.\n");
	exit(EXIT_SUCCESS);
	return NULL;
}/* -----  end of function timer  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  client
 *  Description: The main client function. Reads a file name from stdin and sends it 
 *  		as a message to the server.
 * =====================================================================================
 */
void client(int readFd, int writeFd, int priority)
{
	Message mesg;
	char* buffer;
	size_t currentLength;
	
	// Start the timer
	timer = clock();

	// Create the timer thread
	pthread_t timerThread;
	pthread_create(&timerThread, NULL, timeout, &priority);
	pthread_detach(timerThread);
	// Forever loop so that the client program doesn't need to be run multiple times
	while (true)
	{	
		snprintf(mesg.data, MAXMESSAGEDATA, "%ld ", (long) getpid());
		currentLength = strlen(mesg.data);

		printf("Enter a file that the server will open: ");
		
		buffer = mesg.data + currentLength;

		if (fgets(buffer, MAXMESSAGEDATA - currentLength, stdin) == NULL)
		{
			perror("fgets");
			continue;
		}
		// Update the current length of the message
		// currentLength = strlen(mesg.data);
		// Strips newline character from filename
		currentLength = strcspn(mesg.data, "\n");
		buffer[currentLength] = '\0';

		// Set the message members before the message is sent
		mesg.length = currentLength;
		mesg.type = 1;

		if (mesg_send(writeFd, &mesg) == -1)
		{
			perror("msgsnd");
			continue;
		}

		mesg.type = getpid();
		
		// Because we check that the length of the received message is > 0,
		// we send a 0 length message from the server to signify that
		// the server is done with the client request
		//
		// Should use a thread for a non blocking message receive
		// so the client program can quit if no messages ready
		int n;
		pthread_mutex_lock(&timerLock);
		while ((n = mesg_recv(readFd, &mesg)) > 0)
		{
			// Write n characters from the received message to stdout
			// with a delay that depends upon the client priority
			write(1, mesg.data, n);
			if (priority > 1)
			{
				nanosleep((const struct timespec[]){{0, base_wait * (priority - 1)}}, NULL);
			}	
		}
		// Update timer
		timer = clock();
		pthread_mutex_unlock(&timerLock);
	}
}/* -----  end of function client  ----- */
