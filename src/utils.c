#ifndef _GNU_SOURCE
#define _GNU_SOURCE

#include "../include/ft_nm.h"

void    print_n_z(char c, int n)
{
    for (int i = 0; i < n; i++)
        write(1, &c, 1);
}

void	*ptr_add(void *ptr, size_t offset)
{
	if (offset > (size_t)info.elf_size)
		exit_err("Invalid file", 0, 42);
	return (ptr + offset);
}

int ft_nbrlen_base(uint16_t n, int base)
{
    int len = 0;

    if (n == 0) {
        return 1;
	}

	for (uint16_t tmp = n; tmp > 0; tmp /= base)
		len++;
    return len;
}

int	to_lower(char	c)
{
	if ((c >= 64 && c <= 90))
			return (c + 32);
	return (c);
}

int	ft_strcasecmp(const char *s1, const char *s2)
{
	unsigned char	*string1;
	unsigned char	*string2;
	char		c1;
	char		c2;
	int				i;

	i = 0;
	string1 = (unsigned char *) s1;
	string2 = (unsigned char *) s2;
	while ((string1[i] || string2[i]))
	{
		c1 = to_lower(string1[i]);
		c2 = to_lower(string2[i]);
		if (c1 > c2) // && c1 != '_'
			return (1);
		else if (c1 < c2)
			return (-1);
		i++;
	}
	return (0);
}

void	exit_err(char *msg, char *extra, int exit_code)
{
	ft_putstr_fd("nm: ", 1);
	if (extra)
		ft_putstr_fd(extra, 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
	if (exit_code == 0)
		return ;
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
