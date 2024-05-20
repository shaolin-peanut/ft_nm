/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:53:57 by sbars             #+#    #+#             */
/*   Updated: 2024/05/13 19:10:58 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# include "stddef.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

// dummy functions
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
void	ft_bzero(void *s, size_t n);
int		ft_toupper(int c);
// memory stuff
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
// str stuff
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strlen(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
// malloc func
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
//char	*ft_strnstr(const char *haystack, const char *needle, int len);
// additional functions
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s1, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
// lil funcs
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

typedef struct s_info
{
	va_list	args;
	int		tlen;
}	t_info;

// printf
int		ft_printf(const char *string, ...);
// CHECK FLAG AND CALL REQUIRED FUNCTION
int		check_flag(t_info *tab, char *string, int i);
// PRINTING
int		print_int(t_info *tab, char flag);
int		print_char(t_info *tab);
int		print_string(t_info *tab);
int		print_pointer(t_info *tab);
int		print_hex(t_info *tab);
int		print_lower_hex(t_info *tab);
// UTILS
int		int_len(int num);
int		ft_putuint(unsigned int n);
int		uint_len(unsigned int num);
int		rev_print(char *string);

#endif
