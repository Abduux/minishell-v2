/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:28:42 by ahraich           #+#    #+#             */
/*   Updated: 2024/01/28 17:03:34 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_numric(char *str)
{
    int i;

    i = 0;
    if(!str || !ft_strlen(str))
        return (0);
    if(str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
        if(!ft_isdigit(str[i++]))
            return (0);
    return (1);
}

void    free_exit(unsigned char status, t_data *data , t_input *input)
{
    free_env_list(data->env_list);
	free_env_list(data->export_list);
    parse_free(input);
    clear_history();
    exit(status);
}

int    exit_shell(t_data *data, t_input *input)
{
    int count;
    int isdigit;
    int status;

    count = arg_count(input->args);
    isdigit = is_numric(input->args[1]);
    (void)status;
    printf("exit\n");
    if(count == 1)
    {
        status = atoi(get_value_from_env("?", data->env_list)); // should exit with the last exit status 
        return(0);
    }
    else
    {
        if((isdigit && count == 2)) // when used normally 1 number
            return(ft_atoi(input->args[1]));
        else if(!isdigit)
        {
            ft_printf("minishell: exit: %s: numeric argument required\n", input->args[1]);
            return(2); // should check the exit value of this 1
        }
        else
        {
            ft_printf("minishell: exit: too many arguments");
            return(1);
        }
    }
    return (44);
}

int exit_(t_data *data, t_input *input, int flag)
{
    int exit_status;
    exit_status = exit_shell(data, input);
    if(flag == EXIT_MINISHELL)
        free_exit(exit_status, data, input);
    set_exit_status(&data->env_list, exit_status);
    return(exit_status);
}

    //if the first argument is not a number 
    //check if there is more numbers 
    //if arguments are more print exit and numric only 
    //else exit and print numeric argument
    //if only 1 argument

// void    free_exit(unsigned char status, t_data *data, t_input *input)
// {
//     (void)input;
//     free_env_list(data->env_list);
// 	free_env_list(data->export_list);
//     exit(status);
// }

// int    exit_shell(t_data *data, t_input *input)
// {
//     printf("exit\n");
//     free_exit(0, data , input);
//     return (0);
// }
