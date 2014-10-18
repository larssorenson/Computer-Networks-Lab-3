void* mallocAndCheck(size_t size);
int checkArgc(int argc, int count, char* message);
int parseAndCheckPort(char* port);
int numberFromString(char* str);
int bindUDPSocket();
int dedicatedForwarding(struct sockaddr_in serveraddr, struct sockaddr_in clientaddr, struct sockaddr_in vpnaddr, int port);
char* timeToString(int time);
