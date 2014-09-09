#include "mychecksum.h"

const int ENDCHECK = 1;
#define is_bigendian() ( (*(char*)&ENDCHECK) == 0 )

unsigned long long reverseLong (unsigned long long i) 
{
	// 8 bytes in a 64 bit long
	unsigned char c1, c2, c3, c4, c5, c6, c7, c8;

	// If we're already in big endian, nothing to be done
	if (is_bigendian()) 
	{
		return i;
	} 
	else 
	{
		// Else, we break the long long into 8 bytes
		// using right shifts
		c1 = i;
		c2 = (i >> 8);
		c3 = (i >> 16);
		c4 = (i >> 24);
		c5 = (i >> 32);
		c6 = (i >> 40);
		c7 = (i >> 48);
		c8 = (i >> 56);

		// Then we left shift in reverse order and add it all back to gether
        	return ((unsigned long long)c1 << 56) | ((unsigned long long)c2 << 48) | ((unsigned long long)c3 << 40) | ((unsigned long long)c4 << 32) | ((unsigned long long)c5 << 24) | ((unsigned long long)c6 << 16) | ((unsigned long long)c7 << 8) | c8;
        }
        
}
