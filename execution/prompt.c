/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 01:14:33 by ali               #+#    #+#             */
/*   Updated: 2024/01/28 02:44:27 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_prompt(t_data *data)
{
	char	*input;
	t_input	*input_list;
	
	input = readline(PROMPT);
	while (input != NULL)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &data->term_attr);
		data->syntax_error = 0;
		input_list = parser(input, data);
		if(input[0])
			add_history(input);
		free(input);
		if (input_list)
			execution(input_list, data);
		parse_free(input_list);
		input = readline(PROMPT);
	}
	clear_history();
    free_env_list(data->env_list);
	free_env_list(data->export_list);
	//printf("EOF should clean everything here\n");
}
