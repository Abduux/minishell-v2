/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 20:20:13 by ali               #+#    #+#             */
/*   Updated: 2024/01/02 05:08:28 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int list_count(t_env *env_list)
{
    t_env   *tmp;
    int     len;

    tmp = env_list;
    len = 0;
    while (tmp)
    {
        len++;
        tmp = tmp->next;
    }
    return (len + 1);
}

void    copy(char *dest, t_env *env_index)
{
    int i = 0;
    int j = 0;
    
    while (env_index->name[i])
    {
        dest[j] = env_index->name[i]; 
        i++;
        j++;
    }
    i = 0;
    dest[j++] = '=';
    while (env_index->value && env_index->value[i])
    {
        dest[j] = env_index->value[i];
        i++;
        j++;
    }
    dest[i] = '\0';
}

char**  env_to_array(t_env *env)
{
    int     len = list_count(env);
    char**  env_array = (char **)malloc(sizeof(char *) * (len + 1));
    int     i = 0;
    t_env   *tmp = env;
    
    while (i < len && tmp)
    {
        env_array[i] = (char *)malloc(ft_strlen(tmp->name) + ft_strlen(tmp->value) + 2); // allocate space for the
        copy(env_array[i], tmp);
        i++;
        tmp = tmp->next;
    }
    env_array[i] = NULL;
    return (env_array);
}
