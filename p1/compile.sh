make clean

DEBUG="-U"
if [ $# -gt 0 ]
then
	DEBUG="-D"
fi

make all DEBUG="$DEBUG Debug"
