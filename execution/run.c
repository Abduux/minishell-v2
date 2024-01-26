/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:16:41 by ali               #+#    #+#             */
/*   Updated: 2024/01/26 21:21:31 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char* get_cmd_path(const char *cmd, t_data *data)
{
    char**  paths;
    int     i;
    char*   path;
    char*   full_path;

    if (access(cmd, F_OK) == 0)
        return(ft_strdup(cmd));
    paths = ft_split(get_value_from_env("PATH", data->env_list), ':');
    i = -1;
    while (paths && paths[++i])
    {
        path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(path, cmd);
        free(path);
        if(access(full_path, F_OK) == 0)
        {
            free_strs(paths);
            return (full_path);
        }
        free(full_path);
    }
    free_strs(paths);
    return (NULL);
}

int run_cmd(t_input *input, t_data *data, int *pipe_fd)
{
    int     status;
    char*   cmd_path;
    int     pid;

    cmd_path = get_cmd_path(input->args[0], data);
    if (!cmd_path)
    {
        ft_printf("%s: command not found\n", *(input->args));
        return (1);
    }
    pid = fork();
    if(pid == -1)
        return(ft_printf("minishell : could not fork\n"));
    if(pid == 0)
    {
        close(pipe_fd[0]);
        //ft_printf("Excuting : '%s'", cmd_path);
        execve(cmd_path, input->args, from_list_to_array(data->env_list));
        ft_printf("Error Excuting : '%s'", cmd_path);
        free_exit(0, data, input);
    }
    free(cmd_path);
    waitpid(pid, &status, 0);
    // wait(&status); // should check the exit status and save it 
    
    //ft_printf("waited ...\n");
    return (set_exit_status(&data->env_list, WTERMSIG(status))); // Ark :: Added by me, just in case
    
}

