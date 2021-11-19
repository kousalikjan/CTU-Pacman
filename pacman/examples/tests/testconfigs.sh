#!/bin/bash

./kousaja1 < ./examples/tests/input_test.txt

if [ $? -eq 1 ]
then

	./kousaja1 < ./examples/tests/input_config.txt	

	if [ $? -eq 0 ]
	then
		echo "SUCCESS!"
		echo "The config files are corrupted!"
	else
		echo "FAILURE!"
		echo "The config files are not corrupted!"
	fi

else
	echo "ERROR: Map 0 and config 0 must not be corrupted for this test to work!"
fi
