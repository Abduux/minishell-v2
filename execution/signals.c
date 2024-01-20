/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:47:53 by ali               #+#    #+#             */
/*   Updated: 2024/01/20 01:39:05 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ctrl_c_handler()
{
    rl_replace_line("", 0);
    printf("\n");
    rl_on_new_line();
    rl_redisplay();
}

void    ctrl_back_slash_handler()
{
    //do absulutly nothing ...
    //
}

void    handle_signals(int  the_signal)
{
    if(the_signal == SIGINT)
        ctrl_c_handler();
    // else if (the_signal == SIG_DFL)
    //     ctrl_d_handler();
    // else if(the_signal == SIGABRT)
    //     ctrl_back_slash_handler();
    return;
}