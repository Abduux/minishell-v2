/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 01:14:33 by ali               #+#    #+#             */
/*   Updated: 2024/01/19 01:36:08 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	display_prompt(t_data *data)
{
	char	*input;
	t_input	*input_list;
	//char* prompt = "╭─" ANSI_COLOR" Minishell v2.0$\n" ANSI_COLOR_RESET"╰────> ";
	char* prompt = ANSI_COLOR" Minishell v2.0$" ANSI_COLOR_RESET" ─> ";
	
	input = readline(prompt);
	while (input != NULL)
	{
		data->syntax_error = 0;
		input_list = parser(input, data);
		add_history(input);
		free(input);
		if (input_list)
			execution (input_list, data);
		parse_free(input_list);
		input = readline(prompt);
	}
    free_env_list(data->env_list);
	free_env_list(data->export_list);
	//should free the input list 
	printf("EOF should clean everything here because propably\n");
	//should clearn everything here because propably 
}