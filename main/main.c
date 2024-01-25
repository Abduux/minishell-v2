/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:16:40 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/23 02:35:50 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

int	main(int ac, char **av, char **env)
{
	t_data data;

	(void)av;
	(void)ac;
	g_signal = -1;
	init_data(env, &data);
	display_prompt(&data);
	return (0);
}
