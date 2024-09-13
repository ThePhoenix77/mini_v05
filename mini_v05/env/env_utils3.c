#include "minishell.h"

int        env_list_size(t_global *global)
{
    int    list_size;
    t_env_list    *tmp;

    list_size = 0;
    tmp = global->env_list;
    while (tmp)
    {
        list_size++;
        tmp = tmp->next;
    }
    return (list_size);
}

void env_list_2d_array(t_global *global)
{
    int list_size;
    t_env_list *tmp;
    int i;

    list_size = env_list_size(global);
    // printf("%d list size\n", list_size);
    tmp = global->env_list;
    i = 0;
    global->myenv = (char **)malloc(sizeof(char) * (list_size + 1));
    if (!global->myenv)
        malloc_failed(global);
    while (tmp)
    {
        global->myenv[i] = ft_strdup(tmp->content);
        if (!global->myenv[i])
            malloc_failed(global);
        i++;
        tmp = tmp->next;
    }
    global->myenv[list_size] = NULL;
}