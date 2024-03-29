/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 07:40:08 by ahraich           #+#    #+#             */
/*   Updated: 2024/01/28 16:56:34 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int excute_builtin(t_input *input, t_data *data);
int exit_status(int status);

int   is_builtin(t_input *input) // returns 1 if the cmd is a built in 
{
    if (ft_strncmp(*input->args , "echo", CMD_LEN) == 0 
		|| ft_strncmp(*input->args, "cd", CMD_LEN) == 0
		|| ft_strncmp(*input->args, "pwd", CMD_LEN) == 0
		|| ft_strncmp(*input->args, "env", CMD_LEN) == 0
		|| ft_strncmp(*input->args, "unset", CMD_LEN) == 0
		|| ft_strncmp(*input->args, "export", CMD_LEN) == 0
		|| ft_strncmp(*input->args, "exit", CMD_LEN) == 0)
		return (1);
    return (0);
}

int	run_a_builtin(t_input *input, t_data *data) // forks the minishell and excute the 
{
    if(!is_builtin(input))
    {
        return(-1);
    }
	int status = excute_builtin(input, data);
	return(status);
}

int   excute_builtin(t_input *input, t_data *data)
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
        return(exit_(data, input, 0));
    return (-1);
}

void execution(t_input *input_list, t_data *data)
{
	if (ft_strncmp(*input_list->args, "exit", CMD_LEN) == 0 && !input_list->next)
        exit_(data, input_list, EXIT_MINISHELL);
    t_input *tmp = input_list;
    int pipe_fd[2];
    int piped;
    pid_t cmds_pids[10];
    int index = 0;
    int status;

    piped = 0;
    if(run_herdocs(tmp, data) != 0)
        return;
    while (tmp)
    {
        if((*tmp->args))
        {
			ft_pipe(pipe_fd, &piped, tmp);
            redir(tmp->redirect);
			status = run_a_builtin(tmp, data);
            if(status == -1)
				cmds_pids[index++] = run_cmd(tmp, data);
            else
                set_exit_status(&data->env_list, status);
			reset_fds(data);
        }
        tmp = tmp->next;
    }
    for(int i = 0; i < index; i++)
	{
		waitpid(cmds_pids[i], &status, 0);
		set_exit_status(&data->env_list, exit_status(status));
	}
    handle_signals();
}

// int	run_a_builtin(t_input *input, t_data *data) // forks the minishell and excute the 
// {
// 	pid_t child_pid;
// 	int status ;

// 	redir(input->redirect);
    
// 	child_pid = fork();
// 	if(child_pid == -1)
// 		return (-1);
// 	if(child_pid == 0)
// 	{
//         status = excute_builtin(input, data);
// 		exit(status);
// 	}
// 	return(child_pid);
// }


void    reset_fds(t_data *data)
{
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

int exit_status(int status)
{
    if(WIFSIGNALED(status))
    {
        return(128 + WIFSIGNALED(status));
    }
    else
    {
        return (WEXITSTATUS(status));
    }
}
