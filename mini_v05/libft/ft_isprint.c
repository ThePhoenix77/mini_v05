#include "libft.h"

int	ft_isprint(int c)
{
	return ((c >= 32) && (c <= 126));
}

int	ft_is_valid_expnd(char c)
{
	if (ft_isalnum(c) || c  == '_' || c == '?')
		return (1);
	return (0);
}