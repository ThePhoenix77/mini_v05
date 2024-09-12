#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*res;

	res = NULL;
	while (*s)
	{
		if (*s == (char)c)
		{
			res = s;
		}
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return ((char *)res);
}
