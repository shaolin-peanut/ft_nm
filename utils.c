#ifndef _GNU_SOURCE
#define _GNU_SOURCE

#include "include/ft_nm.h"

void	exit_err(char *msg, int exit_code)
{
	printf("nm: %s\n", msg);
	exit(exit_code);
}

bool check_elf_validity(char *mapped_elf) {
	return (
		mapped_elf[0] == ELFMAG0
		&& mapped_elf[1] == 'E'
		&& mapped_elf[2] == 'L'
		&& mapped_elf[3] == 'F'
		);
}


#endif