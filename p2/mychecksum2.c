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
	unsigned char* check_ptr = (unsigned char*)&check;
	int c;
	
	// Read 8 bytes total
	for(int i = 0; i < 8; i++)
	{
		// Zero buffer to make sure we don't add any residual data
		buffer[0] = 0;
		buffer[1] = 0;
		
		// Read a byte
		c = read(fd, buffer, 1);
		if(c != 0)
		{
			// Pointer "magic" to put the bytes into the memory positions
			// of the long long
			check_ptr[i] = (unsigned long long)buffer[0];
			#ifdef Debug
				printf("Read: %02x\t%0d\r\n", buffer[0], buffer[0]);
			#endif
		}
		
	}
	
	
	// Pointer to the read in checksum
	unsigned char* sum_ptr = (unsigned char*)&sum;
	
	// Print read checksum
	write(2, "Read Checksum: ", 15);
	printUnsignedLongLong(sum);
	write(2, "\r\n\t", 3);
	
	// Print hex of read checksum
	for(int i = 0; i < sizeof(unsigned long long); i++)
		printf("%02x ", sum_ptr[i]);
	printf("\r\n\r\n\t");
	
	#ifdef Debug	
		for(int i = 0; i < sizeof(unsigned long long); i++)
			printf("%02x ", check_ptr[i]);
		printf("%lld\r\n", check);
	#endif
	
	// We read it in the opposite endian order of our system, so we have to reverse it
	check = reverseLong(check);
	
	// Output our calculated checksum
	write(2, "Calculated Checksum: ", 22);
	printUnsignedLongLong(check);
	write(2, "\r\n", 2);

	// print hex form of the calculated checksum
	for(int i = 0; i < sizeof(unsigned long long); i++)
		printf("%02x ", check_ptr[i]);
	printf("\r\n\r\n");
	#ifdef Debug
		printf("%lld\r\n", check);
	#endif
	
	
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
	
	// Open the file we're going to write to
	int out = open(argv[2], O_WRONLY|O_CREAT);
	if(out <= 0)
	{
		write(2, "The write file failed to open!\r\n", 32);
		return 1;
	}
	
	// Byte read count (c), should be 1 as long as we're reading the file
	c = 1;
	buffer[0] = 0;
	buffer[1] = 0;
	int written = 0;
	
	// Read the bytes from one file and write to the other
	while(c != 0 && written < (length-8))
	{
		c = read(fd, buffer, 1);
		#ifdef Debug
			printf("Read: %c ", buffer[0]);
		#endif
		if(c != 0)
		{
			write(out, buffer, 1);
			written++;
			#ifdef Debug
				printf("Sum: %lld\r\n", sum);
			#endif
		}
		
	}
	
	close(fd);
	close(out);
	
	return 0;
	
}
