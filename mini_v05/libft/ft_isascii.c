#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

int ft_is_sp_tb(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}
