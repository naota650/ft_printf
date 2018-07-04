#include "ft_printf.h"

int		ft_conv_check(int i, char *s, char c, t_variable *var)
{
	while (s[++i])
		if (c == s[i])
		{
			var->conv = c;
			return (1);
		}
	return (0);
}

void	ft_mod_check(char *s, int *i, t_variable *var)
{
	(s[*i] == 'h' && s[*i + 1] == 'h') ? var->mod = "hh" : 0;
	(s[*i] == 'h' && s[*i + 1] != 'h') ? var->mod = "h" : 0;
	(s[*i] == 'l' && s[*i + 1] != 'l') ? var->mod = "l" : 0;
	(s[*i] == 'l' && s[*i + 1] == 'l') ? var->mod = "ll" : 0;
	(s[*i] == 'j') ? var->mod = "j" : 0;
	(s[*i] == 'z') ? var->mod = "z" : 0;
	if (var->mod)
		*i += ft_strlen(var->mod);
}

void	ft_flag_save(char *s, t_variable *var, int *i)
{
	while (s[*i] && (s[*i] == '#' || s[*i] == '0' ||
				s[*i] == '-' || s[*i] == '+' || s[*i] == ' '))
	{
		(s[*i] == '0') ? var->zero += 1 : 0;
		(s[*i] == '-') ? var->minus += 1 : 0;
		(s[*i] == '+') ? var->plus += 1 : 0;
		(s[*i] == '#') ? var->pound += 1 : 0;
		(s[*i] == ' ') ? var->space += 1 : 0;
		*i += 1;
	}
}

void	ft_prec_width_parse(char *s, int *i, t_variable *var, va_list args)
{
	if (s[*i] && (((s[*i] > '0' && s[*i] <= '9'))
				|| (s[*i] == '*' && s[*i - 1] != '*')))
	{
		if (s[*i] == '*' && s[*i - 1] != '*')
		{
			var->width = va_arg(args, int);
			*i += 1;
		}
		else
		{
			var->width = (ft_atoi(&s[*i], 0, 0, 1));
			*i += ft_nbrlen(ft_atoi(&s[*i], 0, 0, 1), 0);
		}
	}
	if (s[*i] && (s[*i] == '.'))
	{
		*i += 1;
		var->p += 1;
		if (s[*i] == '*')
			var->prec = va_arg(args, int);
		else if (s[*i] && s[*i] >= '0' && s[*i] <= '9')
			var->prec = (ft_atoi(&s[*i], 0, 0, 1));
		while ((s[*i] >= '0' && s[*i] <= '9') || s[*i] == '*')
			*i += 1;
	}
}

int		ft_parse(char *s, int *i, t_variable *var, va_list args)
{
	*i += 1;
	ft_flag_save(s, var, i);
	ft_prec_width_parse(s, i, var, args);
	ft_mod_check(s, i, var);
	if (ft_conv_check(-1, "sSpdDioOuUxXcC", s[*i], var))
		return (1);
	if (var->zero)
		ft_putstr(ft_zeros("", var), var, -1);
	if (var->width)
	{
		var->width -= 1;
		(var->minus) ? ft_putchar(s[*i], var) : 0;
		(var->minus) ? *i += 1 : 0;
		ft_putstr(ft_spaces("", var), var, -1);
	}
	return (0);
}

