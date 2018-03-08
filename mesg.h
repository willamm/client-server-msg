/*
 * =====================================================================================
 *
 *       Filename:  mesg.h
 *
 *    Description:  Header file that contains the definitions for the message 
 *    		queue functions.
 *
 *        Version:  1.0
 *        Created:  2018-03-07 08:17:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Will Murphy (wm), 
 *   Organization:  
 *
 * =====================================================================================
 */
#pragma once


#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXMESSAGEDATA ((4096 - 16))
#define MESGHDRSIZE ((sizeof(Message) - MAXMESSAGEDATA))
#define MQ_KEY 76L

typedef struct msg_t 
{
	long length;
	long type;
	char data[MAXMESSAGEDATA];
} Message;

int mesg_send(int, Message*);
void Mesg_send(int, Message*);

int mesg_recv(int, Message*);
int Mesg_rect(int, Message*);

int Msgget(key_t, int);
int Msgctl(int, int, struct msqid_ds*);

void server(int, int);
void client(int, int, int);
