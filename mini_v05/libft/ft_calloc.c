#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	void	*memory;

	total = count * size;
	memory = malloc(total);

	if (memory == NULL)
		return (NULL);
	ft_bzero(memory, total);
	return (memory);
}
