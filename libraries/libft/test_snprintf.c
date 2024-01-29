#include <stdio.h>
#include <string.h>
#include "ft_printf.h"

/*
 * Notes:
 * - [x] If size is 0, nothing is written, but the return value (number of bytes that would have been written) is still calculated and returned.
 *
 * - [x] If size is 1, the null terminator is written, but nothing else.
 *       It means, the null terminator is included in size.
 *
 * - [x] The return value does not include the null terminator.
 *
 * - [x] An empty format string still writes the null terminator.
 *
 * - [x] NULL as the format string returns -1, but still writes one null terminator.
 *
 * - [x] NULL as the buffer string segfaults if size is bigger than 0.
 *       If size is 0, no segfault, but the return value (number of bytes that would have been written) is still calculated and returned.
 *       If the format string is also NULL and size is 0, no segfault, but the return value is still -1. If size is bigger, segfault.
*/

int main(int argc, char *argv[])
{
	int			buffersize;
	const char	*format;
	const char	*arg;
	size_t		size;
	int			ret = 0;

	if (argc < 4)
		return (printf("Give arguments!\n"), 1);
	size = atoi(argv[1]);
	buffersize = atoi(argv[2]);
	format = argv[3];
	if (argc > 4)
		arg = argv[4];
	else
		arg = NULL;
	printf("arg:       %s\n", argv[4]);
	printf("atoid arg: %d\n", atoi(arg));

	char buffer1[buffersize];
	char buffer2[buffersize];

	buffer1[0] = 'a';
	buffer2[0] = 'a';

	int ret1 = ft_snprintf(buffer1, size, format, 123);
	int ret2 =    snprintf(NULL, size, NULL, 123);

	printf("ft_snprintf: |%s|\n", buffer1);
	printf("snprintf:    |%s|\n", buffer2);
	if (strcmp(buffer1, buffer2) != 0)
	{
		printf("ft_snprintf output doesn't match snprintf output.\n");
		ret = 1;
	}

	printf("\n");
	printf("ft_snprintf: %d\n", ret1);
	printf("snprintf:    %d\n", ret2);
	if (ret1 != ret2)
	{
		printf("ft_snprintf return value doesn't match snprintf return value.\n");
		ret = 1;
	}

	if (ret == 0)
		printf("ft_snprintf matches snprintf.\n");
	return (ret);
}
