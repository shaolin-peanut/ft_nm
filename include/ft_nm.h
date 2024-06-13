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
	char		*path;
	char		*m_elf;
	int			elf_size;
	void		*sym_tab;
	int			symsize;
	int			symcount;
	void		*sh_str_tab;
	void		*sym_str_tab;
	bool		is32;
	void		*symbols;
	t_row		*output_tab;
}	t_data;

extern t_data			info;

// utils
void    print_n_z(char c, int n);
void	*ptr_add(void *ptr, size_t offset);
int		ft_nbrlen_base(uint16_t n, int base);
int		ft_strcasecmp(const char *s1, const char *s2);
int		err(char *msg, char *extra);
bool	check_elf_validity(char *mapped_elf);
void	swap_ptr(void *a, void *b);

// sort
void	sort(t_row *array, int low, int high);
int		partition(t_row *array, int low, int high);

// process_symbols.c
void	process_symbols();

#endif
