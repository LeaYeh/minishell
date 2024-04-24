#include <stdio.h>
#include <unistd.h>

void	create_files(void)
{
	for (int i = 0; i <= 255; i++)
	{
		unsigned char	filename[2] = {i, '\0'};
		FILE			*file = fopen((char *)filename, "w");
		if (file == NULL)
		{
			printf("Failed to open file: |%s| (%d)\n", filename, i);
			continue;
		}
		fclose(file);
	}
}

int	main(void)
{
	// create_files();
	write (1, "äöü\n", 7);
	return (0);
}
