/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 07:40:03 by ahraich           #+#    #+#             */
/*   Updated: 2024/01/08 13:22:54 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arg_count(char **args)
{
	char	**tmp;
	int		i;

	tmp = args;
	i = 0;
	while (*tmp)
	{
		i++;
		tmp++;
	}
	return(i);
}
int	valid_var_name(char *name)
{
	int i;

	i = 0;
	if(!name || (!ft_isalpha(name[i]) && name[i] != '_'))
		return (0); // should start with alpha and under score only
	while (name[i])
	{
		if(!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	to_join_values(char *key, int equal_index)
{
	if(equal_index == (int)ft_strlen(key) - 1)
		return(0);
	return (1);
}

void join_env(char* key, char* newvalue, t_data *data , int to_join)
{
	char* joined_value;

	if(!to_join)
	{
		if(newvalue)
			add_env(&data->env_list, key, newvalue);
		add_export(&data->export_list, key , newvalue);
		return;
	}
	joined_value = ft_strjoin(get_value_from_env(key, data->env_list), newvalue);
	if(newvalue)
		add_env(&data->env_list, key, joined_value);
	add_export(&data->export_list, key, joined_value);
	free(joined_value);
}
