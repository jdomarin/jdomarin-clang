#include <stdio.h>

#define BUFSIZE 10000

int main(int argc, char **argv)
{
    if(argc != 2)
    {
	printf("Usage: count <filename>");
	return 1;
    }

    FILE *opened;
    char buf[BUFSIZE];
    int linecount = 0;
    opened = fopen(argv[1], "r");
    while( fgets(buf, BUFSIZE, opened) != NULL )
    {
        linecount++;
    }
    printf("%d\n", linecount);
    return 0;
}

