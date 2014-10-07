make clean

DEBUG="-U"
if [ $# -gt 0 ]
then
	DEBUG="-D"
fi

make all EXECUTABLE=vpntunnel DEBUG="$DEBUG Debug"
make all EXECUTABLE=vpntunneld DEBUG="$DEBUG Debug"
