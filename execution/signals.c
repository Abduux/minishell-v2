/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:47:53 by ali               #+#    #+#             */
/*   Updated: 2024/01/28 06:39:52 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// "╭─" ANSI_COLOR" Minishell v2.0$\n" ANSI_COLOR_RESET"╰────> "

void    dont_quit(pid_t pid)
{
    (void) pid;
}

void    ctrl_c_handler()
{
    printf("\n");
    // printf("╭─"ANSI_COLOR"Minishell v2.0$\n");
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