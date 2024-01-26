/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 05:09:21 by ali               #+#    #+#             */
/*   Updated: 2024/01/26 05:21:56 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int set_exit_status(t_env **head, int exit_status)
{
    char *value ;

    value = ft_itoa(exit_status);
    add_env(head, "?", value);
    free(value);
    return (exit_status);
}