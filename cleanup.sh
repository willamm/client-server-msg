#!/bin/bash

function cleanup
{
	ipcs -q | 		\
	while read c1 c2 c3;	\
	do 			\
		echo $c2;	\
				\
		ipcrm -q $c2;	\
	done
	echo "done"
}

cleanup

