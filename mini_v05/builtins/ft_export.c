#include "minishell.h"

char *ft_strcpy(char *dest, const char *src)
{
    char *dest_ptr = dest;

    while (*src)
    {
        *dest_ptr++ = *src++;
    }
    *dest_ptr = '\0';
    return dest;
}

void export_without_args(t_global *global)
{
    t_env_list *tmp = global->env_list;
    while (tmp)
    {
        ft_putstr_fd("declare -x ", 2);
        ft_putstr_fd(tmp->content, 2);
        ft_putstr_fd("\n", 2);
        tmp = tmp->next;
    }
}

int is_valid_name_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}

int name_checker(char *s)
{
    int i;

    i = 0;
    if (!ft_isalpha(s[0]) && s[0] != '_')
        return (-1);
    while (s[i])
    {
        if (!is_valid_name_char(s[i]))
            return (-1);
        i++;
    }
    return (0);
}

t_env_list *find_var(t_env_list *env_list, char *key)
{
    size_t key_len;
    
    key_len = ft_strlen(key);
    while (env_list)
    {
        if (ft_strncmp(env_list->content, key, key_len) == 0 &&
            (env_list->content[key_len] == '=' || env_list->content[key_len] == '\0'))
            return (env_list);
        env_list = env_list->next;
    }
    return (NULL);
}

char *create_new_content(char *key, char *value)
{
    size_t total_len;
    char *new_content;

    if (value)
        total_len = ft_strlen(key) + ft_strlen(value) + 2;
    else
        total_len = ft_strlen(key) + 1;
    
    new_content = malloc(total_len);
    if (!new_content)
    {
        perror("malloc");
        return (NULL);
    }
    
    ft_strcpy(new_content, key);
    if (value)
    {
        new_content[ft_strlen(key)] = '=';
        ft_strcpy(new_content + ft_strlen(key) + 1, value);
    }
    return (new_content);
}

void update_env_var(t_env_list *env_var, char *new_content)
{
    free(env_var->content);
    env_var->content = new_content;
}

t_env_list *create_new_node(char *new_content, int type)
{
    t_env_list *new_node;

    new_node = malloc(sizeof(t_env_list));
    if (!new_node)
    {
        perror("malloc");
        free(new_content);
        return (NULL);
    }
    new_node->content = new_content;
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->type = type;
    return (new_node);
}

void add_export_node(t_env_list **head, t_env_list *new)
{
    t_env_list *last;

    if (!head || !new)
        return;
    if (*head == NULL)
        *head = new;
    else
    {
        last = *head;
        while (last->next != NULL)
            last = last->next;
        last->next = new;
        new->prev = last;
    }
}

void add_or_update_env_var(t_global *global, char *key, char *value, int type)
{
    t_env_list *env_var;
    char *new_content;

    env_var = find_var(global->env_list, key);
    new_content = create_new_content(key, value);
    if (!new_content)
        return;

    if (env_var)
    {
        update_env_var(env_var, new_content);
        env_var->type = type;
    }
    else
    {
        t_env_list *new_node = create_new_node(new_content, type);
        if (new_node)
            add_export_node(&global->env_list, new_node);
    }
}

void handle_key_value(t_global *global, char *content)
{
    char *equal_sign;
    char *key;
    char *value;
    size_t key_length;

    equal_sign = ft_strchr(content, '=');
    if (equal_sign)
    {
        key_length = equal_sign - content;
        key = ft_strndup(content, key_length);
        value = ft_strdup(equal_sign + 1);
        if (key && value)
        {
            add_or_update_env_var(global, key, value, DEFINED);
            free(key);
            free(value);
        }
    }
    else
    {
        key = ft_strdup(content);
        if (key)
        {
            add_or_update_env_var(global, key, NULL, SHOW);
            free(key);
        }
    }
}

void process_export_cmd(t_global *global, t_cmd_args *cmd_args)
{
    while (cmd_args)
    {
        handle_key_value(global, cmd_args->content);
        cmd_args = cmd_args->next;
    }
}

void ft_export(t_global *global, t_cmd_args *cmd_args)
{
    if (!cmd_args->next)
        export_without_args(global);
    else if (name_checker(cmd_args->content) == -1)
        ft_putstr_fd("export: Invalid variable name.\n", 2);
    else
        process_export_cmd(global, cmd_args);
}
