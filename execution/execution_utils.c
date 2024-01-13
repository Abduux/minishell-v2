/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 07:40:03 by ahraich           #+#    #+#             */
/*   Updated: 2024/01/12 18:19:23 by ali              ###   ########.fr       */
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

int	to_join_values(char *str, int equal_index)
{
	if(equal_index > 0 && str[equal_index - 1] == '+')
		return 1;
	return (0);
}

void join_env(const char* key,const char* value, t_data *data , int to_join)
{
	char* joined_value;

	if(!to_join)
	{
		if(value)
			add_env(&data->env_list, key, value);
		add_export(&data->export_list, key , value);
		return;
	}
	printf("joined the value\n");
	joined_value = ft_strjoin(get_value_from_env(key, data->env_list), value);
	if(value)
		add_env(&data->env_list, key, joined_value);
	add_export(&data->export_list, key, joined_value);
	free(joined_value);
}
