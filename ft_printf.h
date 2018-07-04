/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 20:04:47 by lmartine          #+#    #+#             */
/*   Updated: 2018/07/03 20:27:59 by lmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <wchar.h>

typedef struct	s_variable
{
	int			num;
	int			space;
	int			minus;
	int			pound;
	int			plus;
	int			zero;
	int			width;
	int			prec;
	char		conv;
	char		*mod;
	int		bytes;
	int		p;
}				t_variable;

char			*ft_zeros(char *s, t_variable *var);
char			*ft_strcat(char *dest, const char *src);
char			*ft_spaces(char *s, t_variable *var);
char			*ft_chop(char *s, t_variable *var, int i);
void			ft_apply_flags(char *s, t_variable *var);
void			ft_handle_it(t_variable *var, va_list args);
void			ft_init_var(t_variable *var);
char			*ft_mod_cast(va_list args, t_variable *var, int base);
char			*ft_hex_cast(va_list args, t_variable *var, int base);
void			ft_putwstr(wchar_t *ws, t_variable *var, int i);
wchar_t			*ft_wchrtostr(wchar_t wchar);
char			*ft_itoa(int nbr, t_variable *var, int length, int sign);
int				get_unumlen(size_t num, int base, int i);
char			*ft_itoabase_umax(size_t num, int base, t_variable *var);
int				get_snumlen(intmax_t num, int i);
char			*ft_itoa_smax(intmax_t num);
int				ft_atoi(char *str, int i, int nb, int sign);
char			*ft_otoa(unsigned long int number, t_variable *var);
char			*ft_ptoa(unsigned long int number, t_variable *var);
int				ft_printf(const char *format, ...);
int				ft_conv_check(int i, char *s, char c, t_variable *var);
void			ft_mod_check(char *s, int *i, t_variable *var);
void			ft_flag_save(char *s, t_variable *var, int *i);
void			ft_prec_width_parse(char *s, int *i, t_variable *var, va_list args);
int				ft_parse(char *s, int *i, t_variable *var, va_list args);
void			ft_putchar(char c, t_variable *var);
void			ft_putstr(char *s, t_variable *var, int i);
char			*ft_strrev(char *str, int i, int length);
int				ft_strlen(char *s);
char			*ft_strcpy(char *dest, const char *src, size_t i);
int				ft_nbrlen(int n, int i);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(char *s1, int i);
int				ft_wstrlen(const wchar_t *s);
int				ft_strcmp(const char *s1, const char *s2);

#endif
