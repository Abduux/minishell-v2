/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 07:39:54 by ahraich           #+#    #+#             */
/*   Updated: 2024/01/21 02:05:02 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	change_dir(const char* path_name, t_data *data)
{
	char	olddir[PATH_MAX];

	getcwd(olddir, PATH_MAX);
	if (access(path_name , F_OK) != 0)
		printf("minishell: cd: %s: No such file or directory\n", path_name);
	else if (access(path_name, X_OK) != 0)
		printf("minishell: cd: %s: Permission denied\n", path_name);
	else
	{
		if(chdir(path_name) != 0)
			return (printf("Could not change to the  given path ! \n"));
		add_env(&data->env_list, "OLDPWD", olddir);
		add_export(&data->export_list, "OLDPWD", olddir);
		getcwd(olddir, PATH_MAX);
		add_env(&data->env_list, "PWD", olddir);
		add_export(&data->export_list, "PWD", olddir);
	}
	return (1);
}


int	cd(t_input cmd, t_data *data)
{
	char	*newdir;

	if (arg_count(cmd.args) == 1)
	{
		newdir =  get_value_from_env("HOME" , data->env_list); // get the home value to navigate to it 
		if(!newdir)
			printf("minishell: cd: HOME not set\n"); // if the HOME variable not set
		else
			change_dir(newdir, data); // if it set
	}
	else if (arg_count(cmd.args) > 2)
		printf("minishell: cd: too many arguments\n");
	else
		change_dir(cmd.args[1], data);
	return (0);
}
