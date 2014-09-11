#include "mychecksum.h"

int main(int argc, char** argv)
{
	// Need at least 2 arguments
	if(argc < 3)
	{
		write(2, "Please provide a targe file for checking the checksum and another for outputting\r\n", 63);
		return 1;
	}
	
	// Open file to read from
	int fd = open(argv[1], O_RDONLY);
	if(fd <= 0)
	{
		write(2, "Could not open target file!\r\n", 28);
		return 1;
	}
	
	// Get the file length
	int length = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	
	// Generate checksum of the file, minus the appended checksum
	unsigned long long sum = reverseChecksum(fd, length);
	
	// Read the checksum at the end of the file
	// and store it in check
	unsigned long long check = 0;
	unsigned char buffer[2];
	unsigned char* k = (unsigned char*)&check;
	int x;
	int c;
	for(x = 0; x < 8; x++)
	{
		buffer[0] = 0;
		buffer[1] = 0;
		c = read(fd, buffer, 1);
		if(c != 0)
		{
			k[x] = (unsigned long long)buffer[0];
			#ifdef Debug
				printf("Read: %02x\t%0d\r\n", buffer[0], buffer[0]);
			#endif
		}
	}
	
	#ifdef Debug	
		unsigned char* p = (unsigned char*)&check;
		for(int q = 0; q < sizeof(unsigned long long); q++)
			printf("%02x ", p[q]);
		printf("%lld\r\n", check);
	#endif
	
	// We read it in the opposite endian order of our system, so we have to reverse it
	check = reverseLong(check);
	
	#ifdef Debug
		for(int q = 0; q < sizeof(unsigned long long); q++)
			printf("%02x ", p[q]);
		printf("%lld\r\n", check);
	#endif
	
	write(2, "Read Checksum: ", 15);
	
	printUnsignedLongLong(sum);
	
	write(2, "\tCalculated Checksum: ", 22);
	
	printUnsignedLongLong(check);
	
	write(2, "\r\n", 2);
	
	// Checksum check
	if(sum != check)
	{
		write(2, "Checksums do not match!\r\n", 25);
	}
	
	else
	{
		write(2, "Checksums match!\r\n", 18);
	}
	
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
	c = 1;
	buffer[0] = 0;
	buffer[1] = 0;
	
	// Read the bytes from one file and write to the other
	while(c != 0 && sum != 0)
	{
		c = read(fd, buffer, 1);
		#ifdef Debug
			printf("Read: %c ", buffer[0]);
		#endif
		if(c != 0)
		{
			write(out, buffer, 1);
			sum -= buffer[0];
			#ifdef Debug
				printf("Sum: %lld\r\n", sum);
			#endif
		}
		
	}
	
	close(fd);
	close(out);
	
	return 0;
	
}
