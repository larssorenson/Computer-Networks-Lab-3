#!/bin/bash

for i in `seq 1 10`
do
	./myping 128.10.25.101 50505 >> test.txt
done
