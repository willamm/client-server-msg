/*
 * =====================================================================================
 *
 *       Filename:  wrappers.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018-03-05 09:40:16 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Will Murphy 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "mesg.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Msgget
 *  Description: Wrapper function for msgget(). Exits the program if msgget() fails.  
 * =====================================================================================
 */
int Msgget(key_t key, int flags)
{
	int result;
	if ((result = msgget(key, flags)) == -1)
	{
		perror("msgget");
		exit(EXIT_FAILURE);
	}
	return result;
}/* -----  end of function Msgget  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Msgctl
 *  Description:  Wrapper function for msgctl(). Exits the program if msgctl() fails.
 * =====================================================================================
 */
int Msgctl(int msqid, int cmd, struct msqid_ds* queue_info)
{
	int result;
	if ((result = msgctl(msqid, cmd, queue_info) == -1)) 
	{
		perror("msgctl");
		exit(EXIT_FAILURE);
	}
	return result;
}/* -----  end of function Msgctl  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  mesg_send
 *  Description:  Wrapper function for msgsnd(). The address of the message type is passed
 *  		 to msgsnd's message buffer parameter because that is the memory address
 *  		 of the beginning of the message data.
 * =====================================================================================
 */
int mesg_send (int id, Message* buffer)
{
	return msgsnd(id, &buffer->type, buffer->length, 0);
}/* -----  end of function mesg_send  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  mesg_recv
 *  Description:  Wrapper function for msgrcv(). The address of the message type is passed
 *  		 to msgsnd's message buffer parameter because that is the memory address
 *  		 of the beginning of the message data.
 * =====================================================================================
 */
int mesg_recv(int id, Message* buffer)
{
	int n = msgrcv(id, &buffer->type, MAXMESSAGEDATA, buffer->type, 0);
	buffer->length = n;
	return n;
}		/* -----  end of function mesg_recv  ----- */
