/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:08:58 by ali               #+#    #+#             */
/*   Updated: 2024/01/26 22:13:22 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>

int ft_pipe(int *pipe_fd, int *piped, t_input *current_cmd)
{
    if (*piped == 1) // if already piped , switch the input to be the pipe read , should already close the write end
    {
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        pipe_fd[0] = -1;
        *piped = 0;
    }
    if (current_cmd->next != NULL ) // if there is a next cmd --> switch the output to the pipe and pass it as input to it
    {
        pipe(pipe_fd);
        //fcntl(pipe_fd[1], F_SETFL, O_NONBLOCK);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        pipe_fd[1] = -1;
        *piped = 1;
    }
    return (0);
}
