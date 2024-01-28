/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:33:20 by ali               #+#    #+#             */
/*   Updated: 2024/01/28 11:29:23 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>

void change_stdio(int newfd, int to_change)
{
    dup2(newfd, to_change);
    close(newfd);
}

int    redir(t_redirection *redirections)
{
    t_redirection   *redir;
    int             redirect_fd;

    redir = redirections;
    redirect_fd = -1;
    while (redir)
    {
        if (redir->type == REDIR_HEREDOC)
        {
            change_stdio(redir->pipe[0], STDIN_FILENO);
        }
        else if(redir->type == REDIR_OUTPUT)
        {
            redirect_fd = open(redir->file_name , O_CREAT  | O_WRONLY | O_TRUNC, 0644);
            if(redirect_fd != -1)
                change_stdio(redirect_fd, STDOUT_FILENO);
        }
        else if (redir->type == REDIR_INPUT)
        {
            if (access(redir->file_name , F_OK) != 0){
                ft_printf("Minishell: %s: No such file or directory\n", redir->file_name);
            }
            redirect_fd = open(redir->file_name , O_RDONLY);
            if(redirect_fd != -1)
                change_stdio(redirect_fd, STDIN_FILENO);
        }
        else if(redir->type == REDIR_APPEND)
        {
            redirect_fd = open(redir->file_name , O_APPEND | O_CREAT | O_WRONLY, 0644);
            if (redirect_fd != -1)
                change_stdio(redirect_fd, STDOUT_FILENO);
        }
        redir = redir->next;
    }
    return (0);
}
