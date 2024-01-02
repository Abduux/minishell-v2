/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:16:41 by ali               #+#    #+#             */
/*   Updated: 2024/01/02 12:59:44 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char* get_cmd_path(char *cmd, t_data *data)
{
    char **paths = ft_split(get_value_from_env("PATH", data->env_list), ':');
    int i = 0;
    while (paths[i])
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
    //should check if the file start with ./ or / 
}

int run_cmd(t_input *input, t_data *data)
{
    int status;

    char *cmd_path = get_cmd_path(input->args[0], data);
    if (!cmd_path)
    {
        printf("%s not found\n", *(input->args));
        return (8);
    }
    int pid = fork();
    if(pid == 0)
    {
        //printf("running %s \n", cmd_path);
        execve(cmd_path, input->args, env_to_array(data->env_list));
        printf("Error with execve\n");
        exit(0);
    }
    free(cmd_path);
    waitpid(pid, &status, 0);
    //write(1 , "------------\n", 14);
    return (0);
}
