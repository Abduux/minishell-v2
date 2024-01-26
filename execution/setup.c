/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 03:19:06 by ali               #+#    #+#             */
/*   Updated: 2024/01/26 06:08:49 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_data(char **env, t_data *data)
{
	char **export;

	save_fds(data);
	tcgetattr(STDIN_FILENO , &data->term_attr);
	data->env = env;
	export = ft_strsdup(env);
	data->env_list = get_env_list(env);
	data->export_list = get_export_list(export);
	free_strs(export);
	increase_shlvl(data->env_list);
	increase_shlvl(data->export_list);
	handle_signals();
}
