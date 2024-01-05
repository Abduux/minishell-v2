/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:16:40 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/05 05:17:35 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minishell(t_data *data)
{
	char	*input;
	t_input	*input_list;
	char* prompt = ANSI_COLOR_RED"Minishell: --> "ANSI_COLOR_RESET;
	// char	cwdir[PATH_MAX];

	// printf("%s :", getcwd(cwdir , PATH_MAX));
	input = readline(prompt);
	while (input != NULL)
	{
		data->syntax_error = 0;
		input_list = parser(input, data);
		add_history(input);
		free(input);
		execution (input_list, data);
		parse_free(input_list);
		// printf("%s :", getcwd(cwdir , PATH_MAX));
		input = readline(prompt);
	}
}

void	sigint_handler(int signo)
{
	(void)signo;
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	**export;

	(void)av;
	(void)ac;
	export = ft_strsdup(env);
	data.env_list = get_env_list(env);
	data.export_list = get_export_list(export);
	free_strs(export);
	increase_shlvl(data.env_list);
	increase_shlvl(data.export_list);
	minishell(&data);
	free_env_list(data.env_list);
	free_env_list(data.export_list);
	return (0);
}
