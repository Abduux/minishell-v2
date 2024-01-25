/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:47:53 by ali               #+#    #+#             */
/*   Updated: 2024/01/23 02:38:05 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ctrl_c_handler()
{
    g_signal = SIGINT;
    printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void    handle_signals()
{
    signal(SIGINT , ctrl_c_handler);
    signal(SIGQUIT , SIG_IGN);
    return;
}