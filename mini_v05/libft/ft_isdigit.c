#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace2(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_issign(int c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}
