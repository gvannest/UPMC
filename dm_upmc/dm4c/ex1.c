#include <stdio.h>
#include <stdlib.h>

int	inverseRec(int n,int acc)
{
	if (n == 0)
		return (acc);
	return(inverseRec(n / 10, acc * 10 + n % 10));
}

int	main(int argc, char **argv)
{
	if (argc == 3)
		printf("%d\n", inverseRec(atoi(argv[1]), atoi(argv[2])));
	return (0);
}
