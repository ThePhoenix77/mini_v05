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
char **get_args_arr(t_cmd_args *cmd_args)
{
    int i;
    int arg_count;
    char **args_arr;

    i = 0;
    arg_count = args_arr_size(cmd_args);
    args_arr = malloc((arg_count + 1) * sizeof(char *));
    if (!args_arr)
        return (NULL);
    while (cmd_args)
    {
        args_arr[i++] = ft_strdup(cmd_args->content);
        cmd_args = cmd_args->next;
    }
    args_arr[i] = (NULL);
    // printf("Getting arguments for command\n");
    return (args_arr);
}

void handle_error(char *msg)
{
    perror(msg);
}
