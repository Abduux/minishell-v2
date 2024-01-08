/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:33:20 by ali               #+#    #+#             */
/*   Updated: 2024/01/06 19:42:35 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>

void change_stdio(int newfd, int to_change)
{
    dup2(newfd, to_change);
    close(newfd);
}

void    redir(t_redirection *redirections)
{
    t_redirection   *redir;
    int             redirect_fd;

    redir = redirections;
    redirect_fd = -1;
    while (redir)
    {
        if(redir->type == REDIR_OUTPUT)
        {
            redirect_fd = open(redir->file_name , O_CREAT  | O_WRONLY | O_TRUNC, 0644);
            if(redirect_fd != -1)
                change_stdio(redirect_fd, STDOUT_FILENO);
        }
        else if (redir->type == REDIR_INPUT)
        {
            redirect_fd = open(redir->file_name , O_CREAT | O_RDONLY , 0644);
            if(redirect_fd != -1)
                change_stdio(redirect_fd, STDIN_FILENO);
        }
        redir = redir->next;
    }
}
