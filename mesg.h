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
	long type;
	char data[MAXMESSAGEDATA];
	int length;
} Message;



int read_message(int qid, long type, Message* buf);
int send_message(int qid, Message* buf);

key_t get_server_key(const char*);

int Msgget(key_t, int);

int Msgctl(int, int, struct msqid_ds*);

void server(int, int);
void client(int, int);
