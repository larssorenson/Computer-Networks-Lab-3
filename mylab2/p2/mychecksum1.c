#include "mychecksum.h"

int main(int argc, char** argv)
{
	// Need at least 2 arguments
	if(argc < 3)
	{
		write(2, "Please provide a target file for the checksum and writing out\r\n", 63);
		return 1;
	}
	
	// Open file to read from
	int fd = open(argv[1], O_RDONLY);
	
	// Generate checksum of the file
	unsigned long long sum = checksum(fd);
	
	// reset the read position
	lseek(fd, 0, SEEK_SET);
	
	if(fd <= 0)
	{
		write(2, "The read file failed to open!\r\n", 31);
		return 1;
	}
	
	// Open the file we're going to write to
	int out = open(argv[2], O_WRONLY|O_CREAT);
	
	if(out <= 0)
	{
		write(2, "The write file failed to open!\r\n", 32);
		return 1;
	}
	
	// Byte read count (c)
	int c = 1;
	char buffer[2];
	
	// Read the bytes from one file and write to the other
	while(c != 0)
	{
		c = read(fd, buffer, 1);
		if(c != 0)
		{
			write(out, buffer, 1);
		}
		
	}
	
	close(fd);
	
	// Now we append the checksum, in big endian order.
	unsigned char* p = (unsigned char*)&sum;
	#ifdef Debug
		for(int q = 0; q < sizeof(unsigned long long); q++)
			printf("%02x ", p[q]);
		printf("%lld\r\n", sum);
	#endif
	sum = reverseLong(sum);
	#ifdef Debug
		for(int q = 0; q < sizeof(unsigned long long); q++)
			printf("%02x ", p[q]);
		printf("%lld\r\n", sum);
	#endif
	for(int q = 0; q < sizeof(unsigned long long); q++)
		write(out, &(p[q]), 1);
	close(out);
	
	return 0;
	
}
