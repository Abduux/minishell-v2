/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:16:40 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/17 00:43:48 by ali              ###   ########.fr       */
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
	printf("EOF\n");
	//should clearn everything here because propably 
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	**export;
	struct sigaction sa;

	sa.sa_handler = handle_signals;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	(void)av;
	(void)ac;
	// lets handle signals here 
	
	data.env = env;
	export = ft_strsdup(env);
	data.env_list = get_env_list(env);
	data.export_list = get_export_list(export);
	free_strs(export);
	increase_shlvl(data.env_list);
	increase_shlvl(data.export_list);
	display_prompt(&data);
	free_env_list(data.env_list);
	free_env_list(data.export_list);
	return (0);
}

// first pass go read all herdocs and save the input into a pipe in the input 
// every cmd should save the last herdoc input to the pipe
