#ifndef FT_NM_H
# define FT_NM_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <errno.h>
# include <stdbool.h>
# include <stdint.h>
# include <inttypes.h>
# include <elf.h>

typedef struct s_output {
	long unsigned int	value;
	char				type;
	char				*name;
}	t_output;

typedef struct	s_info {
	char		*m_elf;
	void		*sym_tab;
	void		*sh_str_tab;
	void		*sym_str_tab;
	bool		is32;
	int			type;
	t_output	*output_tab;
}	t_info;


// utils
void	exit_err(char *msg, int exit_code);
bool	check_elf_validity(char *mapped_elf);

// parse_elf.c
void	parse_elf(t_info	*info);

// process_symbols.c
void	process_symbols(int symsize, int symcount, t_info  *info);

#endif