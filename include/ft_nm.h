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

typedef	struct s_row {
	void	*value;
	char	type;
	char	*name;
	bool	print;
}	t_row;

// typedef struct s_symbol {
// 	char				*name;
// 	void				*value;
// 	long unsigned int	size;
// 	unsigned int		type;
// 	unsigned int		binding;
// 	unsigned int		visibility;
// 	void				*section;
// 	char				*section_name;
// 	int					section_flags;
// 	bool				small	;
	
// }	t_symbol;

typedef struct	s_info {
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
}	t_info;

// utils
void	exit_err(char *msg, int exit_code);
bool	check_elf_validity(char *mapped_elf);
void	free_all(t_info	*info);
void	swap_ptr(void *a, void *b);

// sort
void	sort(t_row *array, int low, int high);
int		partition(t_row *array, int low, int high);

// parse_elf.c
void	parse_elf(t_info	*info);

// process_symbols.c
void	process_symbols(t_info  *info);

#endif