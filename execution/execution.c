/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 07:40:08 by ahraich           #+#    #+#             */
/*   Updated: 2024/01/13 16:28:02 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_builtin(t_input *input, t_data *data)
{
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
    return (-1);
}

void    run_herdocs(t_input *inputs)
{
    t_input *tmp;

    tmp = inputs;
    while (tmp)
    {
        open_herdocs(tmp);
        tmp = tmp->next;
    }
}
void    reset_fds(t_data *data);
void    save_fds(t_data *data);

void execution(t_input *input_list, t_data *data)
{
    t_input *tmp = input_list;
    int command_status;
    int pipe_fd[2];
    int piped;

    run_herdocs(tmp);
    save_fds(data);
    piped = 0;
    while (tmp)
    {
        if((*tmp->args))
        {
            ft_pipe(pipe_fd, &piped, tmp); // pipe if there is a next cmd 
            redir(tmp->redirect); // creat all files and change the FDs
            command_status = is_builtin(tmp, data);
            if (command_status == -1) // run the comand but all pipes are closed 
                run_cmd(tmp, data);
            reset_fds(data);
        }
        tmp = tmp->next;
    }
}

void    reset_fds(t_data *data)
{
    ft_printf("RESET ALL FDs to Default\n");
    dup2(data->stdin, STDIN_FILENO);
    dup2(data->stdout, STDOUT_FILENO);
    dup2(data->stderr, STDERR_FILENO);
}

void    save_fds(t_data *data)
{
    data->stderr = dup(STDERR_FILENO);
    data->stdin = dup(STDIN_FILENO);
    data->stdout = dup(STDOUT_FILENO);
}


// int run_cmd(t_input *input, t_data *data)
// {

//     t_input *tmp = input_list;
//     int command_status;
//     int pipe_fd[2];
//     int piped;

//     run_herdocs(tmp);
//     save_fds(data);
//     piped = 0;
//     while (tmp)
//     {
//         if((*tmp->args))
//         {
//             redir(input_list->redirect); // creat all files and change the FDs
//             ft_pipe(pipe_fd, &piped, tmp); // pipe if there is a next cmd 
//             command_status = is_builtin(tmp, data);
//             if (command_status == -1) // run the comand but all pipes are closed 
//                 run_cmd(tmp, data);
//             reset_fds(data);
//         }
//         tmp = tmp->next;
//     }
// }