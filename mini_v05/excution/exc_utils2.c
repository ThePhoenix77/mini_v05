#include "minishell.h"

int args_arr_size(t_cmd_args *cmd_args)
{
    int arg_count;
    t_cmd_args *temp;
    
    arg_count = 0;
    temp = cmd_args;
    while (temp)
    {
        arg_count++;
        temp = temp->next;
    }
    return (arg_count);
}
// char **get_args_arr(t_cmd_args *cmd_args)
// {
//     int i;
//     int arg_count;
//     char **args_arr;

//     i = 0;
//     arg_count = args_arr_size(cmd_args);
//     args_arr = malloc((arg_count + 1) * sizeof(char *));
//     if (!args_arr)
//         return (NULL);
//     while (cmd_args)
//     {
//         args_arr[i++] = ft_strdup(cmd_args->content);
//         cmd_args = cmd_args->next;
//     }
//     args_arr[i] = (NULL);
//     return (args_arr);
// }

char **get_args_arr(t_cmd_args *cmd_args)
{
    // Assuming cmd_args is a linked list of strings
    int count = 0;
    t_cmd_args *current = cmd_args;
    
    while (current) {
        count++;
        current = current->next;
    }

    char **args = malloc((count + 1) * sizeof(char *));
    if (!args) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    current = cmd_args;
    for (int i = 0; i < count; i++) {
        args[i] = strdup(current->content); // Assuming content is a string
        current = current->next;
    }
    args[count] = NULL; // Null-terminate the array

    return args;
}
void handle_error(char *msg)
{
    perror(msg);
}
