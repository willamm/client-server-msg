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
 *         Name:  get_server_key
 *  Description:  
 * =====================================================================================
 */
key_t get_server_key(const char* fileName)
{	
	key_t server_key;
	if ((server_key = ftok(fileName, 'a')) == -1)
	{
		perror("ftok");
		exit(EXIT_FAILURE);
	}
	return server_key;
} /* -----  end of function get_server_key  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Msgget
 *  Description:  
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
 *  Description:  
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
 *  Description:  
 * =====================================================================================
 */
int mesg_send (int id, Message* buffer)
{
	return msgsnd(id, &buffer->type, buffer->length, 0);
}/* -----  end of function mesg_send  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  mesg_recv
 *  Description:  
 * =====================================================================================
 */
int mesg_recv(int id, Message* buffer)
{
	int n = msgrcv(id, &buffer->type, MAXMESSAGEDATA, buffer->type, 0);
	buffer->length = n;
	return n;
}		/* -----  end of function mesg_recv  ----- */
