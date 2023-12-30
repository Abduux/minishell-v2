/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahraich <ahraich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 07:40:08 by ahraich           #+#    #+#             */
/*   Updated: 2023/12/25 13:58:22 by ahraich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_builtin(t_input *input, t_data *data)
{
    if (!input->args || !(*input->args)){
        printf("no command");
        return (0);
    }
    if (ft_strncmp(*input->args , "echo", CMD_LEN) == 0)
        return (echo(input->args));
    else if (ft_strncmp(*input->args , "cd", CMD_LEN) == 0)
        return (cd(*input, data));
    else if (ft_strncmp(*input->args , "pwd", CMD_LEN) == 0)
        return (pwd());
    else if (ft_strncmp(*input->args, "env", CMD_LEN) == 0)
        return (env(data->env_list));
    else if (ft_strncmp(*input->args, "unset", CMD_LEN) == 0)
        return(unset(data, input));
    else if (ft_strncmp(*input->args, "export", CMD_LEN) == 0)
        return(export(input, data));
    else if (ft_strncmp(*input->args, "exit", CMD_LEN) == 0)
        return(exit_shell(data, input));
    return (0);
}

void execution(t_input *input_list, t_data *data)
{
    t_input *tmp = input_list;
    int command_status;

    while (tmp)
    {
        command_status = is_builtin(tmp, data);
        if (command_status == -1)
            printf("Try to run this command -> %s\n", tmp->args[0]);
        else if(command_status)
        {
            printf("A built in exited with error");
        }
        else {
            //do nothing !
        }
        tmp = tmp->next;
    }
    // printf("execution called \n");
}

// void update_exit_status(int status, char *command, t_data *data)
// {
//     // data->exit_status = status;
//     // add_env(data->env_list, );
// }

