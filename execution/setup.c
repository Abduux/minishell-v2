/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 03:19:06 by ali               #+#    #+#             */
/*   Updated: 2024/01/17 03:20:36 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_data(char **env, t_data *data)
{
	char **export;

	data->env = env;
	export = ft_strsdup(env);
	data->env_list = get_env_list(env);
	data->export_list = get_export_list(export);
	free_strs(export);
	increase_shlvl(data->env_list);
	increase_shlvl(data->export_list);
}

void	silent(char **av, int ac)
{
	(void)av;
	(void)ac;
}

void set_sigaction(struct sigaction *sa)
{
	sa->sa_handler = handle_signals;
	sa->sa_flags = 0;
	sigaction(SIGINT, sa, NULL);
}