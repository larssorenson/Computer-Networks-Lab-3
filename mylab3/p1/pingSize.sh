#!/bin/sh

for i in `seq 0 500 3500`
do
	ping -c 10 indiana.edu -s $i > indiana_$i.txt
done
