#include "ft_printf.h"

char	*ft_itoa(int nbr, t_variable *var, int length, int sign)
{
	char	*str;

	sign = nbr;
	var->num += 1;
	if (nbr == 0 && var->p)
		return ("");
	while (sign /= 10)
		length++;
	sign = nbr < 0 ? 1 : 0;
	length = nbr < 0 ? length += 1 : length;
	str = (char*)malloc(sizeof(char) * length + 1);
	if (nbr == -2147483648)
		return (str = ft_strdup("-2147483648", -1));
	if (!str)
		return (NULL);
	(sign) ? str[0] = '-' : 0;
	nbr = nbr < 0 ? nbr *= -1 : nbr;
	while (--length >= sign)
	{
		str[length] = (nbr >= 10) ? (nbr % 10) + 48 : nbr + 48;
		nbr /= 10;
	}
	str[ft_strlen(str)] = '\0';
	return (str);
}

int		get_unumlen(size_t num, int base, int i)
{
	while (num /= base)
		i++;
	return (i);
}

char	*ft_itoabase_umax(size_t num, int base, t_variable *var)
{
	char			*str;
	int				len;
	char			*basestr;

	basestr = ft_strdup("0123456789abcdef", -1);
	var->num += 1;
	len = get_unumlen(num, base, 1);
	num == 0 ? var->pound = 0 : 0;
	if (num == 0 && var->p)
		return ("");
	if (!(str = (char *)malloc(sizeof(*str) * len + 1)))
		return (NULL);
	str[len] = '\0';
	str[--len] = basestr[num % base];
	while (num /= base)
		str[--len] = basestr[num % base];
	len = -1;
	if (var->conv == 'X')
		while (str[++len])
			(str[len] >= 'a' && str[len] <= 'z') ? str[len] -= 32 : 0;
	free(basestr);
	return (str);
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
	uintmax_t	tmp;

	len = get_snumlen(num, 1);
	tmp = num;
	if (num < 0)
	{
		tmp = -num;
		len++;
	}
	if (!(str = (char *)malloc(sizeof(*str) * len)))
		return (NULL);
	str[len] = '\0';
	str[--len] = tmp % 10 + '0';
	while (tmp /= 10)
		str[--len] = tmp % 10 + '0';
	(num < 0) ? str[0] = '-' : 0;
	return (str);
}

