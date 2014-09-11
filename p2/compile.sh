make clean

DEBUG="-U"
if [ $# -gt 0 ]
then
	DEBUG="-D"
fi

make all EXECUTABLE=mychecksum1 DEBUG="$DEBUG Debug"
make all EXECUTABLE=mychecksum2 DEBUG="$DEBUG Debug"
