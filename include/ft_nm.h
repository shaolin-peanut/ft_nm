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

# include "../libft/libft.h"

typedef	struct s_row {
	uint16_t	value;
	char		type;
	char		*name;
	bool		print;
}	t_row;

typedef struct	s_einfo {
	char		*m_elf;
	int			elf_size;
	void		*sym_tab;
	int			symsize;
	int			symcount;
	void		*sh_str_tab;
	void		*sym_str_tab;
	bool		is32;
	int			type;
	void		*symbols;
	t_row		*output_tab;
}	t_data;

// utils
int		ft_nbrlen_base(uint16_t n, int base);
int		ft_strcasecmp(const char *s1, const char *s2);
void	exit_err(char *msg, char *extra, int exit_code);
bool	check_elf_validity(char *mapped_elf);
void	free_all(t_data	*info);
void	swap_ptr(void *a, void *b);

// sort
void	sort(t_row *array, int low, int high);
int		partition(t_row *array, int low, int high);

// parse_elf.c
void	parse_elf(t_data	*info);

// process_symbols.c
void	process_symbols(t_data  *info);

#endif
