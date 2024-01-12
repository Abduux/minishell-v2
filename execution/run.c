/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:16:41 by ali               #+#    #+#             */
/*   Updated: 2024/01/09 22:08:20 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char* get_cmd_path(char *cmd, t_data *data)
{
    //should check if the file start with ./ or / 
    char **paths;
    int i;

    paths = ft_split(get_value_from_env("PATH", data->env_list), ':');
    i = 0;
    while (paths && paths[i])
    {
        char *path = ft_strjoin(paths[i], "/");
        char *full_path = ft_strjoin(path,cmd);
        free(path);
        if(access(full_path, F_OK | X_OK) == 0)
        {
            free_strs(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    free_strs(paths);
    return (NULL);
}

int run_cmd(t_input *input, t_data *data)
{
    int status;

    char *cmd_path = get_cmd_path(input->args[0], data);
    if (!cmd_path)
    {
        printf("%s: command not found\n", *(input->args));
        return (1);
    }
    int pid = fork();
    if(pid == 0)
    {
        // execve(cmd_path, input->args, env_to_array(data->env_list));
        // execve(cmd_path, input->args, data->env);
        execve(cmd_path, input->args, from_list_to_array(data->env_list));
        printf(" ");
        free_exit(0, data, input);
    }
    free(cmd_path);
    waitpid(pid, &status, 0); // should check the exit status and save it 
    return (0);
}
