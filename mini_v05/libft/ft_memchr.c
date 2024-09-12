#include "libft.h"

void	*ft_memchr(const void *buf, int c, size_t n)
{
	const unsigned char	*p;

	p = (unsigned char *)buf;
	while (n-- > 0)
	{
		if (*p == (unsigned char)c)
			return ((void *)p);
		p++;
	}
	return (NULL);
}
