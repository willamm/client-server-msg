#!/bin/bash

server_key=9
start_server="./server-debug $server_key"

start_client="./client-debug $server_key"

gnome-terminal -e $start_server

for i in `seq 1 3`;
do
	gnome-terminal -e $start_client
done

