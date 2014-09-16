#include "mychecksum.h"

unsigned long long reverseChecksum(int file, int length)
{
	// Can't read from a nonexistant FD
	if(file > 0)
	{
		unsigned long long sum = 0;
		unsigned char buffer[2];
		int c = 1;
		
		int count = 0;
		
		// Reading 1 byte at a time, so as long as we've read at least 1
		// we keep reading and incrementing until we've read all but the last 8 bytes
		while(c != 0 && count < (length-8))
		{
			buffer[0] = 0;
			buffer[1] = 0;
			c = read(file, buffer, 1);
			if(c != 0)
			{
				sum += (unsigned long long)buffer[0];
				count++;
			}
		}
		
		
		return sum;
		
	}
	
	return 0;
	
}
