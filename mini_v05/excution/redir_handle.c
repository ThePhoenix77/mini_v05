#include "../includes/minishell.h"

void handle_redir_out(t_redir *redir)
{
    int fd;
    
    fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        handle_error("open");
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

void handle_redir_in(t_redir *redir)
{
    int fd;
    
    fd = open(redir->file_name, O_RDONLY);
    if (fd < 0)
        handle_error("open");
    dup2(fd, STDIN_FILENO);
    close(fd);
}

void handle_dredir_out(t_redir *redir)
{
    int fd;
    
    fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
        handle_error("open");
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

void handle_redirection(t_redir *redir_list)
{
    t_redir *redir = redir_list;
    while (redir)
    {
        if (redir->type == REDIR_OUT)
            handle_redir_out(redir);
        else if (redir->type == REDIR_IN)
            handle_redir_in(redir);
        else if (redir->type == DREDIR_OUT)
            handle_dredir_out(redir);
        redir = redir->next;
    }
}

