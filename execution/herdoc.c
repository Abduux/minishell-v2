/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 06:06:17 by ali               #+#    #+#             */
/*   Updated: 2024/01/26 01:53:23 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    open_herdocs(t_input *input , t_data *data)
{
    t_redirection   *tmp_red;
    char            *line;

    (void)data;

    tmp_red = input->redirect;
    while (tmp_red)
    {
        if(tmp_red->type == REDIR_HEREDOC) // IF THE IS A HERDOC OPNED
        {
            pipe(tmp_red->pipe);
            line = readline("> "); // READ INPUT AND SAVE IT
            while (ft_strncmp(line, tmp_red->file_name, INT_MAX) != 0) // IF THE INPUT != DELIMTER (FILE NAME) READ AGAIN
            {
                //expand line 
                // write line 
                //write to the file
                printf("line saved = %s\n", line);
                free(line);
                line = readline("> ");
                printf("----------\n");
                if(g_signal == SIGINT)
                {
                    g_signal = -1;
                    exit(0);
                }
            }
            free(line);
        }
        tmp_red = tmp_red->next;
    }
}

void    run_herdocs(t_input *inputs, t_data *data)
{
    t_input *tmp;

    tmp = inputs;
    while (tmp) // for every cmd should save last herdoc opned 
    {
        open_herdocs(tmp, data);
        tmp = tmp->next;
    }
}
