/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:16:40 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/26 05:12:05 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

int	main(int ac, char **av, char **env)
{
	t_data data;

	(void)av;
	(void)ac;
	init_data(env, &data);
	add_env(&data.env_list , "?", "0");
	display_prompt(&data);
	return (0);
}
