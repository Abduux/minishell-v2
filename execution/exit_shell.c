/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahraich <ahraich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:28:42 by ahraich           #+#    #+#             */
/*   Updated: 2023/12/25 18:07:47 by ahraich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

free_exit(unsigned char status, t_data *data, t_input *input)
{
    free_env_list(data->env_list);
	free_env_list(data->export_list);
    exit(status);
}

int    exit_shell(t_data *data, t_input *input)
{
    printf("exit\n");
    //if the first argument is not a number 
    //check if there is more numbers 
    //if arguments are more print exit and numric only 
    //else exit and print numeric argument
    //if only 1 argument

    if(arg_count(input->args) == 2)
    {
        //if numeric and under long max 
        //
        free_exit(atoi(input->args[1]), data , input);
        // printf("minishell: exit: too many arguments\n");
    }
}
