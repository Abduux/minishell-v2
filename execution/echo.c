/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 07:40:00 by ahraich           #+#    #+#             */
/*   Updated: 2024/01/28 11:29:06 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    n_option(char *arg) 
{
	int	i;
	
	i = 0;
    if (!arg || arg[i] != '-')
		return (0);
	while (arg[++i])
    {
        if(arg[i] != 'n')
            return (0);
	}
	if(i == 1)
		return (0);
    return (1);
}

int	echo(char **args)
{
	int	new_line;
	int	i;

    new_line = 1;
	i = 1;
    while (n_option(args[i]))
    {
        new_line = 0;
        i++;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if(ft_strlen(args[i]) > 0 && args[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if(new_line == 1)
    {
        write(STDOUT_FILENO, "\n", 1);
    }
	return (0);
}
