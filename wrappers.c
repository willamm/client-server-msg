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
 *         Name:  read_message
 *  Description:  
 * =====================================================================================
 */
int read_message(int qid, long type, Message* buf)
{
	int result = msgrcv(qid, buf, MAXMESSAGEDATA, type, 0);
	if (result == -1) 
	{
		perror("msgrcv");
		exit(EXIT_FAILURE);
	}
	buf->length = result;
	printf("Buf length: %d\n", buf->length);
	return result;
}/* -----  end of function read_message  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  send_message
 *  Description:  
 * =====================================================================================
 */
int send_message(int qid, Message* buf)
{	
	int length = sizeof(Message) - sizeof(long) - sizeof(int);
	int result = msgsnd(qid, buf, length, 0);
	return result;
}/* -----  end of function send_message  ----- */


