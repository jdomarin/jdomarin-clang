#include <stdio.h>

int main(int argc, char *argv[])
{
	char* tweet;
	char text[] = "Ce tweet possède une longueur exacte de cent quarante et un caractères."
	"Ce tweet possède une longueur exacte de cent quarante et un caractères.";

	printf("%s\n", tweet);

	tweet = text;

	return 0;
}
