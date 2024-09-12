#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*current;

	size = 0;
	current = lst;
	if (!lst)
		return (0);
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}
