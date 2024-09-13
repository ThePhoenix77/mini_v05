#include "../includes/minishell.h"

void free_tab(char **tab)
{
    int i;
    
    i = 0;
    if (!tab)
        return;
    while (tab[i])
        free(tab[i++]);
    free(tab);
}

char *find_path(char **split, char *cmd)
{
    int i;
    char *path;
    char *tmp;

    i = 0;
    while (split[i])
    {
        tmp = ft_strjoin(split[i], "/");
        path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (path && access(path, F_OK | X_OK) == 0)
            return (path);
        free(path);
        i++;
    }
    return (NULL);
}

char *get_the_path(char *cmd, t_global *global)
{
    t_env_list    *env_path;
    char        *path;
    int            len_skip;

    env_path = get_var_env(global, "PATH=");
    if (!env_path)
        return (NULL);
    path = ft_strdup(env_path->content);
    if (!path)
        malloc_failed(global);
    len_skip = ft_strlen_un_char(path, '=');
    if (len_skip == -2)
    {
        free(path);
        return (NULL);
    }
    update_line(&path, len_skip + 1, global);
    return (path);
}

char *get_path(char *cmd, t_global *global)
{
    int i;
    char **split;
    char *path;
    char *path_env;

    i = 0;
    if (ft_strchr(cmd, '/')) 
        return ft_strdup(cmd);
    path_env = get_the_path(cmd,  global);
    if (!path_env)
        return (NULL);
    split = ft_split(path_env, ':');
    free(path_env);
    path = find_path(split, cmd);
    free_tab(split);
    if (path)
        return (path);
    return (NULL);
    // while (envp[i])
    // {
    //     if (!ft_strncmp(envp[i], "PATH=", 5))
    //     {
    //         path_env = ft_strdup(envp[i] + 5);
    //         split = ft_split(path_env, ':');
    //         free(path_env);
    //         path = find_path(split, cmd);
    //         free_tab(split);
    //         if (path)
    //             return (path);
    //         else
    //             return (NULL);
    //     }
    //     i++;
    // }
}


// char *get_path(char *cmd, t_global *global)
// {
//     printf("Getting path for command: %s\n", cmd);
//     int i;
//     char **split;
//     char *path;
//     char *path_env;
//     char **envp=global->myenv;

//     i = 0;
//     if (ft_strchr(cmd, '/')) 
//         return ft_strdup(cmd);
//     while (envp[i])
//     {
//         if (!ft_strncmp(envp[i], "PATH=", 5))
//         {
//             path_env = ft_strdup(envp[i] + 5);
//             split = ft_split(path_env, ':');
//             free(path_env);
//             path = find_path(split, cmd);
//             free_tab(split);
//             if (path)
//             {
//                 printf("Getting path for command: %s\n", cmd);
//                 return (path);
//             }
//             else
//             {
//                 fprintf(stderr, "Error: Path not found for command: %s\n", cmd);
//                 return (NULL);
//             }
//         }
//         i++;
//     }
//     return (NULL);
// }