#include <stdio.h>
#include <gmp.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	mpz_t n, i, mode_val, mode_num, idx; /*declare gmp variables*/
	mpz_inits(n, i, mode_val, mode_num, idx, NULL);
	FILE *file;
	char *line = NULL;
	size_t len = 0;

	if (argc != 2)
	{
		printf("Usage: %s file\n", argv[0]);
		free(line);
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");/*open file to read numbers from*/
	if (file == NULL) 
	{
		perror("fopen");
		free(line);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, file) != -1)
	{
		line[strlen(line) - 1] = '\0'; /*add terminating zero in plave of newline for string */
		mpz_set_str(n, line, 10);
		mpz_sqrt(idx, n);

		for (mpz_set_ui(i, 2); mpz_cmp(i, idx) <= 0; mpz_add_ui(i, i, 1))
		{
			mpz_mod(mode_val, n, i);
			if (mpz_cmp_ui(mode_val, 0) == 0)
			{
				mpz_div(mode_num, n, i);
				gmp_printf("%Zd=%Zd*%Zd\n", n, mode_num, i);
				break;
			}
		}
	}

	fclose(file);/*close opened file*/
	free(line);/*free pointer memory*/
	mpz_clears(n, i, mode_val, mode_num, idx, NULL);/*clear gmp variables*/

	return (0);
}
