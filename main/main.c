/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:16:40 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/20 01:21:36 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_main_data
{
	t_data data;
	struct sigaction sa;
}	t_main_data;

int	main(int ac, char **av, char **env)
{
	t_main_data data;

	silent(av, ac);
	set_sigaction(&data.sa);
	set_data(env , &data.data);
	display_prompt(&data.data);
	return (0);
}
