/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:08:58 by ali               #+#    #+#             */
/*   Updated: 2024/01/13 15:44:46 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int ft_pipe(int *pipe_fd, int *piped, t_input *current_cmd)
{
    if (*piped == 1) // if piped means we need to change the fd for reading 
    {
        dup2(pipe_fd[0], STDIN_FILENO);
        if(current_cmd->next)
            ft_printf("%s STDIN = PIPE[0]\n", current_cmd->next->args[0]);
        close(pipe_fd[0]);
        *piped = 0;
    }
    if (current_cmd->next && *piped == 0) // if there is a next cmd --> means we need to pipe --> and change the output file descritor 
    {
        if(pipe(pipe_fd) == -1)
        {
            ft_printf("pipe : could not pipe \n");
            return (1);
        }
        dup2(pipe_fd[1], STDOUT_FILENO);
        ft_printf("STDOUT = PIPE[1]\n");
        close(pipe_fd[1]);
        *piped = 1;
    }
    return (0);
}
//echo text here is about to get piped to the next comand | grep is > output.txt
/*

cmd --> cmd2 --> cmd3 ---> output.txt

cmd output = pipe[write]

cmd2 output = pipe[write] && input = pipe[read]

cmd3 output = output.txt && input = pipe[read]

*/
