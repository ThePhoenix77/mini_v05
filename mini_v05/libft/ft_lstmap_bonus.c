#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*tmp;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	res = NULL;
	while (lst != NULL)
	{
		tmp = ft_lstnew(NULL);
		if (tmp == NULL)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		tmp->content = f(lst->content);
		ft_lstadd_back(&res, tmp);
		lst = lst->next;
	}
	return (res);
}
