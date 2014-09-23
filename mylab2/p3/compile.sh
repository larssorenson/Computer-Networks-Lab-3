make clean

DEBUG="-U"
if [ $# -gt 0 ]
then
	DEBUG="-D"
fi

make all EXECUTABLE=myping DEBUG="$DEBUG Debug"
make all EXECUTABLE=mypingd DEBUG="$DEBUG Debug"
