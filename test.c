#include <stdlib.h>
#include <stdio.h>

char			*dtoa_doom(double n);

int main(int argc, char **argv)
{
	(void)argc;
	char *r;
	// printf("f = %f\n", atof(argv[1]));
	r = dtoa_doom(atof(argv[1]));
	printf("result = %s\n", r);
	// dtoa_doom(atof(argv[1]));
	free(r);
	// while (1);
	return (0);
}