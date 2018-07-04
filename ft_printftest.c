/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 16:38:53 by lmartine          #+#    #+#             */
/*   Updated: 2018/07/03 19:04:20 by lmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <inttypes.h>

typedef struct	s_variable
{
	int		num;
	int		space;
	int		minus;
	int		pound;
	int		zero;
	int		width;
	int		prec;
	char	conv;
	char	*mod;
	int		data;
	int		bytes;
	int		p;
	int		plus;
}				t_variable;

void	variable_initial(t_variable *var)
{
	var->num = 0;
	var->space = 0;
	var->minus = 0;
	var->pound = 0;
	var->zero = 0;
	var->width = 0;
	var->prec = 0;
	var->conv = 0;
	var->mod = 0;
	var->data = 0;
	var->bytes = 0;
	var->p = 0;
	var->plus = 0;
}
//writes char and increments byte count
void	ft_putchar(char c, t_variable *var)
{
	write(1, &c, 1);
	var->bytes += 1;
}

void	ft_putstr(char *str, t_variable *var, int i)
{
	if (!str)
	{
		write(1, "(null)", 6);
		return ;
	}
	while (str[++i])
	{
		write(1, &str[i], 1);
		var->bytes += 1;
	}
}

int		ft_strlen(char *str)
{
	int i;
	
	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, const char *src, size_t i)
{
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strrev(char *str, int i, int length)
{
	char	buffer;

	while (str[length])
		length++;
	while (length - 1 > ++i)
	{
		buffer = str[i];
		str[i] = str[length - 1];
		str[length - 1] = buffer;
		length--;
	}
	return (str);
}

int		ft_nbrlen(int num, int i)
{
	while (num != 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;

	i = ft_strlen(dest);
	while (*src)
		dest[i++] = *src++;
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *str;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = (char*)malloc(ft_strlen((char*)s1) +
						ft_strlen((char*)s2))))
		return (NULL);
	str = ft_strcpy(str, s1, -1);
	str = ft_strcat(str, s2);
	return (str);
}

char	*ft_strdup(char *s1, int i)
{
	int		length;
	char	*filler;

	length = ft_strlen(s1);
	filler = malloc(sizeof(*filler) * (length + 1));
	if (filler)
	{
		while (s1[++i] != '\0')
			filler[i] = s1[i];
		filler[i] = '\0';
	}
	return (filler);
}



int		ft_wstrlen(const wchar_t *str)
{
	int length;

	length = 0;
	while (str[length] != L'\0')
		length++;
	return (length);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (-1);
	while (*s1 && *s2 && *s1 == *s2)
		s1++ && s2++;
	return (*(unsigned char*)s1) - *((unsigned char*)s2);
}

int		ft_atoi(char *str, int i, int num, int sign)
{
	if (!str)
		return (0);
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (sign & num);
}

int		get_unumlen(size_t num, int base, int i)
{
	while (num /= base)
		i++;
	return (i);
}

int		get_snumlen(intmax_t num, int i)
{
	while (num /= 10)
		i++;
	return (i);
}

char	*ft_itoa_smax(intmax_t num)
{
	char		*str;
	int			len;
	uintmax_t	temp;

	len = get_snumlen(num, 1);
	temp = num;
	if (num < 0)
	{
		temp = -num;
		len++;
	}
	if (!(str = (char *)malloc(sizeof(*str) * len)))
		return (NULL);
	str[len] = '\0';
	str[--len] = temp % 10 + '0';
	while (temp /= 10)
		str[--len] = temp % 10 + '0';
	(num < 0) ? str[0] = '-' : 0;
	return (str);
}

char	*ft_itoabase_umax(size_t num, int base, t_variable *var)
{
	char		*str;
	int			length;
	char		*basestr;

	basestr = ft_strdup("01234567890abcdef", -1);
	var->num += 1;
	length = get_unumlen(num, base, 1);
	num == 0 ? var->pound = 0: 0;
	if (num == 0 && var->pound)
		return ("");
	if (!(str = (char*)malloc(sizeof(*str) * length + 1)))
		return (NULL);
	str[length] = '\0';
	str[--length] = basestr[num % base];
	length = -1;
	if (var->conv == 'X')
		while (str[++length])
			(str[length] >= 'a' && str[length] <= 'z') ? str[length] -= 32 : 0;
	free(basestr);
	return (str);
}

char	*ft_itoa(int num, t_variable *var, int length, int sign)
{
	char	*str;

	sign = num;
	var->num += 1;
	if (num == 0 && var->p)
		return ("");
	while (sign /= 10)
		length++;
	sign = num < 0 ? 1 : 0;
	length = num < 0 ? length += 1 : length;
	str = (char*)malloc(sizeof(char) * length + 1);
	if (num == -2147483648)
		return (str = ft_strdup("-214783648", -1));
	if (!str)
		return (NULL);
	(sign) ? str[0] = '-' : 0;
	num = num < 0 ? num *= -1 : num;
	while (--length >= sign)
	{
		str[length] = (num >= 10) ? (num % 10) + 48 : num + 48;
		num /= 10;
	}
	str[ft_strlen(str)] = '\0';
	return (str);
}

char	*ft_otoa(unsigned long int number, t_variable *var)
{
	char			*print;
	unsigned int		i;
	unsigned long int	x;

	x = number;
	var->num += 1;
	i = 0;
	print = (char*)malloc(sizeof(char) * 24);
	if (number == 0 && !var->pound && var->p)
		return ("");
	if (number == 0)
	{
		print[i] = '0';
		i++;
	}
	while (number)
	{
		print[i] = (number % 8) + 48;
		number /= 8;
		i++;
	}
	print[i] = '\0';
	ft_strrev(print, -1, 0);
	(x != 0 && var->pound) ? print = ft_strjoin("0", print): 0;
	return (print);
}

char	*ft_ptoa(unsigned long int number, t_variable *var)
{
	char		*print;
	int			i;

	i = 0;
	print = (char*)malloc(sizeof(char) * 12);
	if (number == 0)
		print[i] = '0';
	while (number && var->conv == 'p')
	{
		print[i++] = "0123456789abcdef"[number % 16];
		number /= 16;
	}
	print = ft_strrev(print, -1, 0);
	print = ft_strjoin("0x", print);
	return (print);
}


void	check_flags(char *str, t_variable *var, int *i)
{
	while (str[*i] && (str[*i] == '#' || str[*i] == ' ' || 
				str[*i] == '0' || str[*i] == '+' || str[*i] == '-'))
	{
		(str[*i] == '0') ? var->zero += 1 : 0;
		(str[*i] == '-') ? var->minus += 1 : 0;
		(str[*i] == '+') ? var->plus += 1 : 0;
		(str[*i] == ' ') ? var->space += 1 : 0;
		(str[*i] == '#') ? var->pound += 1 : 0;
		*i += 1;
	}
}

void	check_mod(char *str, int *i, t_variable *var)
{
	if (str[*i] == 'h' && str[*i + 1] == 'h')
		var->mod = "hh";
	if (str[*i] == 'h' && str[*i + 1] != 'h')
		var->mod = "h";
	if (str[*i] == 'l' && str[*i + 1] != 'l')
		var->mod = "l";
	if (str[*i] == 'l' && str[*i + 1] == 'l')
		var->mod = "ll";
	if (str[*i] == 'j')
		var->mod = "j";
	if (str[*i] == 'z')
		var->mod = "z";
	if (var->mod)
		*i += ft_strlen(var->mod);
}

void	parse_width_prec(char *str, int *i, t_variable *var, va_list args)
{
	if (str[*i] && (((str[*i] > '0' && str[*i] <= '9'))
				|| (str[*i] == '*' && str[*i - 1] != '*')))
	{
		if (str[*i] == '*' && str[*i - 1] != '*')
		{
			var->width = va_arg(args, int);
			*i += 1;
		}
		else
		{
			var->width = (ft_atoi(&str[*i], 0, 0, 1));
			*i += ft_nbrlen(ft_atoi(&str[*i], 0, 0, 1), 0);
		}
	}
	if (str[*i] && (str[*i] == '.'))
	{
		*i += 1;
		var->p += 1;
		if (str[*i] == '*')
			var->prec = va_arg(args, int);
		else if (str[*i] && str[*i] >= '0' && str[*i] <= '9')
			var->prec = (ft_atoi(&str[*i], 0, 0, 1));
		while ((str[*i] >= '0' && str[*i] <= '9') || str[*i] == '*')
			*i += 1;
	}
}

int		conv_check(int i, char *str, char c, t_variable *var)
{
	while (str[++i])
	{
		if (c == str[i])
		{
			var->conv = c;
			return (1);
		}
	}
	return (0);
}

char	*mod_cast(va_list args, t_variable *var, int base)
{
	var->num += 1;
	if (!var->mod)
		return (ft_itoa((va_arg(args, ssize_t)), var, 1, 0));
	else if (ft_strcmp(var->mod, "z") == 0)
		return (ft_itoa_smax(va_arg(args, ssize_t)));
	else if (ft_strcmp(var->mod, "j") == 0)
		return (ft_itoa_smax(va_arg(args, intmax_t)));
	else if (ft_strcmp(var->mod, "ll") == 0)
		return (ft_itoa_smax(va_arg(args, long long)));
	else if (ft_strcmp(var->mod, "l") == 0)
		return (ft_itoa_smax(va_arg(args, long)));
	else if (ft_strcmp(var->mod, "hh") == 0)
		return (ft_itoa_smax((char)va_arg(args, int)));
	else if (ft_strcmp(var->mod, "h") == 0)
		return (ft_itoa((short)va_arg(args, int), var, 1, 0));
	else
		return (ft_itoabase_umax(va_arg(args, intmax_t), base, var));
}

char	*hex_cast(va_list args, t_variable *var, int base)
{
	var->num += 1;
	if (var->mod)
		return (ft_itoabase_umax((va_arg(args, unsigned int)), base, var));
	else if (ft_strcmp(var->mod, "z") == 0)
		return (ft_itoabase_umax(va_arg(args, ssize_t), base, var));
	else if (ft_strcmp(var->mod, "j") == 0)
		return (ft_itoabase_umax(va_arg(args, intmax_t), base, var));
	else if (ft_strcmp(var->mod, "ll") == 0)
		return (ft_itoabase_umax(va_arg(args, long long), base, var));
	else if (ft_strcmp(var->mod, "l") == 0)
		return (ft_itoabase_umax(va_arg(args, long), base, var));
	else if (ft_strcmp(var->mod, "hh") == 0)
		return (ft_itoabase_umax((char)va_arg(args, int), base, var));
	else if (ft_strcmp(var->mod, "h") == 0)
		return (ft_itoabase_umax((short)va_arg(args, int), base, var));
	else
		return (ft_itoabase_umax(va_arg(args, intmax_t), base, var));
}

void	ft_putwstr(wchar_t *wstr, t_variable *var, int i)
{
	var->width -= (ft_wstrlen(wstr) - var->prec);
	var->minus ? var->zero = 0 : 0;
	if (var->width > 0 && !var->minus)
		while (var->width)
		{
			var->zero ? write(1, "0", 1) : write(1, " ", 1);
			var->width -= 1;
		}
	while (wstr[++i])
	{
		if (var->prec && var->prec < ft_wstrlen(wstr))
		{
			while (var->prec--)
				ft_putchar(wstr[i], var);
			break ;
		}
		ft_putchar(wstr[i], var);
		var->bytes += 1;
	}
	if (var->width > 0 && var->minus)
		while (var->width)
		{
			var->zero ? write(1, "0", 1) : write(1, " ", 1);
			var->width -= 1;
		}
}

wchar_t	*ft_wchrtostr(wchar_t wchar)
{
	wchar_t	*wstr;

	wstr = (wchar_t *)malloc(sizeof(wchar) * 2);
	if (wstr)
	{
		wstr[0] = wchar;
		wstr[1] = L'\0';
	}
	return (wstr);
}

char	*ft_zeros(char *str, t_variable *var)
{
	char	block[var->prec + 1];
	int		i;

	i = -1;
	if (var->prec < 0)
		return (str);
	while (++i < var->prec)
		block[i] = '0';
	block[i] = '\0';
	if (str[0] == '-')
	{
		str = ft_strjoin(block, &str[1]);
		str = ft_strjoin("-", str);
	}
	else
		str = ft_strjoin(block, str);
	var->zero = 0;
	return (str);
}

char	*ft_spaces(char *str, t_variable *var)
{
	char	block[var->width + 1];
	int		i;
	char	edge[2];

	i = 0;
	edge[0] = str[0];
	edge[1] = '\0';
	if (var->width < 1)
		return (str);
	while (i < var->width)
	{
		block[i] = (var->zero) ? '0' : ' ';
		i++;
	}
	block[i] = '\0';
	if ((edge[0] == '-' || edge[0] == '+') && var->zero && var->num)
	{
		str = ft_strjoin(block, &str[1]);
		str = ft_strjoin(edge, str);
	}
	else
		str = (var->minus) ? ft_strjoin(str, block) : ft_strjoin(block, str);
	return (str);
}

char	*ft_chop(char *str, t_variable *var, int i)
{
	char 	*dest;

	dest = (char*)malloc(sizeof(char) * var->prec + 1);
	while (++i < var->prec)
		dest[i] = str[i];
	dest[i] = '\0';
	return (dest);
}

void	apply_flags(char *str, t_variable *var)
{
	if (!str)
	{
		ft_putstr("(null)", var, -1);
		return ;
	}
	(str[0] == '-') ? var->prec += 1 : 0;
	if (!var->num)
		str = (var->prec) ? ft_chop(str, var, -1) : str;
	str = (var->pound && var->conv == 'x' && !var->zero)
		? ft_strjoin("0x", str) : str;
	str = (var->pound && var->conv == 'X' && !var->zero)
		? ft_strjoin("0X", str) : str;
	(var->space && str[0] != '-') ? var->width -= 1 : 0;
	var->prec -= ft_strlen(str);
	(var->plus && str[0] != '-') ? var->width -= 1 : 0;
	str = (var->num) ? ft_zeros(str, var) : str;
	var->width -= ft_strlen(str);
	str = (var->plus && str[0] != '-') ? ft_strjoin("+", str) : str;
	str = ft_spaces(str, var);
	str = (var->pound && var->conv == 'x' && var->zero) ? ft_strjoin("0x", str) : str;
	str = (var->pound && var->conv == 'X' && var->zero) ? ft_strjoin("0X", str) : str;
	str = (var->space && str[0] != '-') ? ft_strjoin(" ", str) : str;
	ft_putstr(str, var, -1);
}

void 	handle_it(t_variable *var, va_list args)
{
	(var->plus) ? var->space = 0 : 0;
	(var->conv == 'u' || var->conv == 'U') ? var->plus = 0 : 0;
	(var->conv == 'u' || var->conv == 'U') ? var->space = 0 : 0;
	(var->zero && var->minus) ? var->zero = 0 : 0;
	if (var->conv == 's' && !var->mod)
		apply_flags(va_arg(args, char*), var);
	else if (var->conv == 'D')
		apply_flags(ft_itoabase_umax(va_arg(args, long), 10, var), var);
	else if (var->conv == 'S' ||
			(var->conv == 's' && ft_strcmp("l", var->mod) == 0))
		ft_putwstr(va_arg(args, wchar_t*), var, -1);
	else if (var->conv == 'C')
		ft_putwstr((ft_wchrtostr(va_arg(args, wchar_t))), var, -1);
	else if (var->conv == 'c')
		ft_putchar(va_arg(args, int), var);
	else if (var->conv == 'o' || var->conv == 'O')
		apply_flags(ft_otoa(va_arg(args, unsigned int), var), var);
	else if (var->conv == 'p')
		apply_flags(ft_ptoa(va_arg(args, unsigned long int), var), var);
	else if (var->conv == 'd' || var->conv == 'i')
		apply_flags(mod_cast(args, var, 10), var);
	else if (var->conv == 'x' || var->conv == 'X')
		apply_flags(hex_cast(args, var, 16), var);
	else if (var->conv == 'u' || var->conv == 'U')
		apply_flags(ft_itoabase_umax(va_arg(args, intmax_t), 10, var), var);
}

int		parse_format(char *str, int *i, t_variable *var, va_list args)
{
	*i += 1;
	check_flags(str, var, i);
	parse_width_prec(str, i, var, args);
	check_mod(str, i, var);
	if (conv_check(-1, "sSpdDioOuUxXcC", str[*i], var))
		return (1);
	if (var->zero)
		ft_putstr(ft_zeros("", var), var, -1);
	if (var->width)
	{
		var->width -= 1;
		(var->minus) ? ft_putchar(str[*i], var) : 0;
		(var->minus) ? *i += 1 : 0;
		ft_putstr(ft_spaces("", var), var, -1);
	}
	return (0);
}

void	ft_sonic_heroes(const char *format, va_list args, int i, int *byte_count)
{
	t_variable	var;
	int		j;
	
	j = ft_strlen((char*)format);
	while (format[++i])
	{
		variable_initial(&var);
		if (format[i] == '%' && format[i + 1] == '%')
		{
			ft_putchar('%', &var);
			i += 1;
		}
		else if (format[i] == '%')
		{
			if (parse_format((char*)format, &i, &var, args))
				handle_it(&var, args);
			else if (format[i])
				ft_putchar(format[i], &var);
		}
		else if (i < j)
			ft_putchar(format[i], &var);
		*byte_count += var.bytes;
	}
}

int		ft_printf(const char *format, ...)
{
	va_list		args;
	int			byte_count;

	va_start(args, format);
	ft_sonic_heroes(format, args, -1, &byte_count);
	va_end(args);
	return(byte_count);
}
