/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:47:53 by ali               #+#    #+#             */
/*   Updated: 2024/01/26 01:57:12 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ctrl_c_handler()
{
    g_signal = SIGINT;
    write(STDIN_FILENO, "\n", 1);
    printf("working !\n");
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