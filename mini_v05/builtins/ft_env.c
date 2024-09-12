#include "minishell.h"

void ft_env(t_global *global)
{
    t_env_list *current = global->env_list;
    
    while (current)
    {
        if (ft_strchr(current->content, '='))
        {
            ft_putstr_fd(current->content, STDOUT_FILENO);
            ft_putstr_fd("\n", STDOUT_FILENO);
        }
        current = current->next;
    }
}

// void ft_env(t_global *global)
// {
//     t_env_list *current;
    
//     current = global->env_list;
//     while (current)
//     {
//         if (current->type != SHOW)
//         {
//             ft_putstr_fd(current->content, STDOUT_FILENO);
//             ft_putstr_fd("\n", STDOUT_FILENO);
//         }
//         current = current->next;
//     }
// }


/*t_lst *new_lst_node(const char *content, t_type type)
{
    t_lst *node = malloc(sizeof(t_lst));
    if (!node)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->content = ft_strdup(content);
    node->next = NULL;
    node->prev = NULL;
    node->state = GENERAL;
    node->type = type;
    node->len = ft_strlen(content);
    return node;
}
int main()
{

}*/