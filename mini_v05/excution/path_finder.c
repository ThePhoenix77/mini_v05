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

char *get_path(char *cmd, char **envp)
{
    int i;
    char **split;
    char *path;
    char *path_env;

    i = 0;
    if (ft_strchr(cmd, '/')) 
        return ft_strdup(cmd);
    while (envp[i])
    {
        if (!ft_strncmp(envp[i], "PATH=", 5))
        {
            path_env = ft_strdup(envp[i] + 5);
            split = ft_split(path_env, ':');
            free(path_env);
            path = find_path(split, cmd);
            free_tab(split);
            if (path)
                return (path);
            else
                return (NULL);
        }
        i++;
    }
    return (NULL);
}
