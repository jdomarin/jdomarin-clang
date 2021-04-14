#include <stdio.h> //printf
#include <stdlib.h> //atol

long faultyfact(long n)
{
	return n == 0 ? 1 : n * faultyfact(n - 1);//error! but done on purpose
}

int main(int argc, char *argv[])
{
	if(argc != 2)
		printf("Usage: %s number\n", argv[0]);
	printf("%d\n", faultyfact(atol(argv[1])));
	
	return 0; 
}
