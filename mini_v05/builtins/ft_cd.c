#include "minishell.h"

void checker(void *ptr, char *msg)
{
    if (!ptr)
    {
        printf("%s", msg);
        return ;
    }
}

void update_pwd(t_global *global)
{
    char *cwd;
    char *old_pwd;
    t_env_list *tmp;
    
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("getcwd");
        return;
    }
    tmp = find_var(global->env_list, "PWD");
    old_pwd = tmp->content + 5;
    if (old_pwd)
        add_or_update_env_var(global, "OLDPWD", old_pwd, DEFINED);
    add_or_update_env_var(global, "PWD", cwd, DEFINED);
    free(cwd);
}

void ft_cd(t_global *global, t_cmd_args *cmd_args)
{
    char *old_p;
    char *new_p;
    char *home_p;
    t_env_list *home;

    old_p = NULL;
    new_p = NULL;
    if (cmd_args->next)
        new_p = cmd_args->next->content;
    else
    {
        home = find_var(global->env_list, "HOME");
        checker(&home, "cd: HOME not set\n");
        home_p = home->content + 5;
        new_p = home_p;
    }
    old_p = getcwd(NULL, 0);
    checker(&old_p, "getcwd has failed !\n");
    if (chdir(new_p) != 0)
    {
        printf("cd has failed !\n");
        free(old_p);
        return ;
    }
    else
    {
        free(old_p);
        return ;
    }
    update_pwd(global);
    free(old_p);
}
