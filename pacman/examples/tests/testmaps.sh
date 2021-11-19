#!/bin/bash

./kousaja1 < ./examples/tests/input_test.txt

if [ $? -eq 1 ]
then

	./kousaja1 < ./examples/tests/input_maps.txt	

	if [ $? -eq 0 ]
	then
		echo "SUCCESS!"
		echo "The map files are corrupted!"
	else
		echo "FAILURE!"
		echo "The map files are not corrupted!"
	fi

else
	echo "ERROR: Config 0 and map 0 must not be corrupted for this test to work!"
fi




