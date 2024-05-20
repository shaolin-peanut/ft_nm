#ifndef FTNM_H
#define FTNM_H

#include <stdbool.h>

typedef struct	s_info {
	char	*m_elf;
	void	*sym_tab;
	void	*str_tab;
	bool	is32;
}	t_info;

void	parse_elf(t_info	*info);

#endif