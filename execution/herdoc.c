/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 06:06:17 by ali               #+#    #+#             */
/*   Updated: 2024/01/17 01:06:19 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void    open_herdocs(t_input *input)
{
    t_redirection   *tmp_red;
    char            *line;

    tmp_red = input->redirect;
    while (tmp_red)
    {
        if(tmp_red->type == REDIR_HEREDOC) // IF THE IS A HERDOC OPNED
        {
            line = readline("> "); // READ INPUT AND SAVE IT
            while (ft_strncmp(line, tmp_red->file_name, INT_MAX) != 0) // IF THE INPUT != DELIMTER (FILE NAME) READ AGAIN
            {
                free(line);
                line = readline("> ");
            }
            free(line);
        }
        tmp_red = tmp_red->next;
    }
}

void    run_herdocs(t_input *inputs)
{
    t_input *tmp;

    tmp = inputs;
    while (tmp)
    {
        open_herdocs(tmp);
        tmp = tmp->next;
    }
}