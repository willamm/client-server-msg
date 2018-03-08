#!/bin/bash

function cleanup
{
	ipcrm -Q 76
	echo "done cleanup"
}

cleanup

