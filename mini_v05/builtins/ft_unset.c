#include "minishell.h"

void remove_env_node(t_global *global, t_env_list *node)
{
    if (node->prev)
        node->prev->next = node->next;
    else
        global->env_list = node->next;
    if (node->next)
        node->next->prev = node->prev;
    free(node->content);
    free(node);
}


void ft_unset(t_global *global, t_cmd_args *cmd_args)
{
    t_env_list *env_var;
    
    while (cmd_args)
    {
        env_var = find_var(global->env_list, cmd_args->content);
        if (env_var)
        {
            remove_env_node(global, env_var);
            break ;
        }
        cmd_args = cmd_args->next;
    }
}

// void print_env_list(t_env_list *head)
// {
//     t_env_list *current = head;
//     while (current != NULL)
//     {
//         printf("Content: %s\n", current->content);
//         current = current->next;
//     }
// }

// void ft_unset(t_global *global, t_cmd_args *cmd_args)
// {
//     t_env_list *env_var;
//     char *key;
//     char *equal_sign;
//     size_t key_length;
    
//     while (cmd_args)
//     {
//         equal_sign = ft_strchr(cmd_args->content, '=');
//         if (equal_sign)
//         {
//             key_length = equal_sign - cmd_args->content;
//             key = ft_strndup(cmd_args->content, key_length);
//             if (key)
//             {
//                 env_var = find_var(global->env_list, key);
//                 if (env_var)
//                     remove_env_node(global, env_var);
//                 free(key);
//             }
//         }
//         else
//             printf("unset: Invalid format. Use VAR.\n");
//         cmd_args = cmd_args->next;
//     }
// }

