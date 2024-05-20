#ifndef _GNU_SOURCE
#define _GNU_SOURCE

#include "include/ftnm.h"

void	exit_err(char *msg, int exit_code)
{
	printf("nm: %s\n", msg);
	exit(exit_code);
}

void	check_elf_validity(char	*mapped_elf)
{
	if (!(mapped_elf[0] == ELFMAG0
		&& mapped_elf[1] == 'E'
		&& mapped_elf[2] == 'L'
		&& mapped_elf[3] == 'F'))
		exit_err("Invalid binary file", 1);
}

#endif