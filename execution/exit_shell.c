/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:28:42 by ahraich           #+#    #+#             */
/*   Updated: 2023/12/30 16:57:35 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_exit(unsigned char status, t_data *data, t_input *input)
{
    (void)input;
    free_env_list(data->env_list);
	free_env_list(data->export_list);
    exit(status);
}

int    exit_shell(t_data *data, t_input *input)
{
    printf("exit\n");
    free_exit(atoi(input->args[1]), data , input);
    return (0);
}
