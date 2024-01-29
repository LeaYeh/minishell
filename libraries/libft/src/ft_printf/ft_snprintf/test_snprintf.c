#include <stdio.h>

/*
 * Notes:
 * - [ ] If size is 0, nothing is written, but the return value (number of bytes that would have been written) is still calculated and returned.
 *
 * - [ ] If size is 1, the null terminator is written, but nothing else.
 *       It means, the null terminator is included in size.
 *
 * - [ ] The return value does not include the null terminator.
 *
 * - [ ] An empty format string still writes the null terminator.
 *
 * - [ ] NULL as the format string returns -1, but still writes one null terminator.
 *
 * - [ ] NULL as the buffer string segfaults if size is bigger than 0.
 *       If size is 0, no segfault, but the return value (number of bytes that would have been written) is still calculated and returned.
 *       If the format string is also NULL and size is 0, no segfault, but the return value is still -1. If size is bigger, segfault.
*/

// int	main(void)
// {
// 	char	str[10];
// 	size_t	size = 10;
// 	int		ret;

// 	str[0] = 'a';
// 	str[1] = 'b';
// 	str[2] = 'c';
// 	ret = snprintf(str, size, "%05d", 42);
// 	printf("str: |%s|\n", str);
// 	printf("%c\n", str[0]);
// 	printf("%c\n", str[1]);
// 	printf("%c\n", str[2]);
// 	printf("ret:  %d\n", ret);
// 	return (0);
// }