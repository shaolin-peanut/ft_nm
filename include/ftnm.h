#ifndef FTNM_H
# define FTNM_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <assert.h>
# include <errno.h>
# include <stdbool.h>
# include <elf.h>

typedef struct	s_info {
	char	*m_elf;
	void	*sym_tab;
	void	*str_tab;
	bool	is32;
}	t_info;

// utils
void	exit_err(char *msg, int exit_code);
void	check_elf_validity(char *mapped_elf);

// parse_elf.c
void	parse_elf(t_info	*info);

#endif