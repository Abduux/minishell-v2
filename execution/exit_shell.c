/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:28:42 by ahraich           #+#    #+#             */
/*   Updated: 2024/01/08 12:45:19 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_numric(char *str)
{
    int i;

    i = 0;
    if(!str || !ft_strlen(str))
        return (0);
    while (str[i])
        if(!ft_isdigit(str[i++]))
            return (0);
    return (1);
}

void    free_exit(unsigned char status, t_data *data , t_input *input)
{
    free_env_list(data->env_list);
	free_env_list(data->export_list);
    free_strs(input->args);
    free(input->redirect);
    exit(status);
}

int    exit_shell(t_data *data, t_input *input)
{
    int count;
    int isdigit;

    count = arg_count(input->args);
    isdigit = is_numric(input->args[1]);
    printf("exit\n");
    if(count == 1)
        free_exit(0 , data, input); // should exit with the last exit status 
    else
    {
        if((isdigit && count == 2)) // when used normally 1 number
            free_exit(ft_atoi(input->args[1]), data, input);
        else if(!isdigit)
        {
            printf("minishell: exit: %s: numeric argument required\n", input->args[1]);
            free_exit(0 , data, input); // should check the exit value of this 1
        }
        else
            printf("minishell: exit: too many arguments");
    }
    return (0);
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
