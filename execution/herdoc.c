/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 06:06:17 by ali               #+#    #+#             */
/*   Updated: 2024/01/26 03:52:54 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    the_mega_handler(pid_t signal)
{
    printf("\n");
    (void)signal;
    exit(1);
}

int save_herdoc_data(t_redirection *herdoc, t_data *data, t_input *input);

int    open_herdocs(t_input *input , t_data *data)
{
    t_redirection   *tmp_red;

    tmp_red = input->redirect;
    while (tmp_red)
    {
        if(tmp_red->type == REDIR_HEREDOC) // IF its a HERDOC OPNED
        {
            if(save_herdoc_data(tmp_red, data, input) != 0)
                return (-1);
        }
        tmp_red = tmp_red->next;
    }
    return (0);
}

void    dont_quit(pid_t pid)
{
    (void) pid;
    //printf("\n");
}

int    run_herdocs(t_input *inputs, t_data *data)
{
    t_input *tmp;

    tmp = inputs;
    signal(SIGINT, dont_quit);
    while (tmp) // for every cmd should save last herdoc opned 
    {
        if(open_herdocs(tmp, data) != 0)
        {
            handle_signals();
            return (-1);
        }
        tmp = tmp->next;
    }
    handle_signals();
    return (0);
}

int save_herdoc_data(t_redirection *herdoc, t_data *data, t_input *input)
{
    pid_t   pid;
    int     status;

    if(pipe(herdoc->pipe) != 0)
        return (-1);
    pid = fork();
    if(pid == -1)
        return(-1);
    if(pid == 0) // child -----------------------------------------
    {
        close(herdoc->pipe[0]); // close read end
        signal(SIGINT, the_mega_handler); // reset signal behavior
        char *line = readline("> ");
        while (ft_strncmp(line, herdoc->file_name, INT_MAX) != 0)
        {
            write(herdoc->pipe[1], line, ft_strlen(line));
            write(herdoc->pipe[1], "\n", 2);
            free(line);
            line = readline("> ");
        }
        free(line);
        close(herdoc->pipe[1]); // close write end after writing is complete 
        free_exit(0, data, input);
    }
    else // parent -----------------------------------------
    {
        close(herdoc->pipe[1]); // close write end of the pipe;
        // parent should wait for child 
        if(waitpid(pid, &status, 0) == -1)// if an Error accured with (waitpid) return -1
        {
            close(herdoc->pipe[0]);
            perror("waitpid");
            return (-1);
        }
        if(WEXITSTATUS(status) != 0) //if program exited wiht an error  should return -1 to cancel THE Prompt
            return (-1);
    }
    return (0); // if exit normaly continue and return 0
}


    // mypipe[0]; read end
    // mypipe[1]; write end

