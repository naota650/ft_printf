#include "ft_printf.h"

void	ft_printf2(const char *format, va_list args, int i, int *bytes)
{
	t_ops		ops;
	int			x;

	x = ft_strlen((char*)format);
	while (format[++i])
	{
		ft_init_ops(&ops);
		if (format[i] == '%' && format[i + 1] == '%')
		{
			ft_putchar('%', &ops);
			i += 1;
		}
		else if (format[i] == '%')
		{
			if (ft_parse((char*)format, &i, &ops, args))
				ft_handle_it(&ops, args);
			else if (format[i])
				ft_putchar(format[i], &ops);
		}
		else if (i < x)
			ft_putchar(format[i], &ops);
		*bytes += ops.bytes;
	}
}

int		ft_printf(const char *format, ...)
{
	va_list		args;
	int			bytes;

	bytes = 0;
	va_start(args, format);
	ft_printf2(format, args, -1, &bytes);
	va_end(args);
	return (bytes);
}

