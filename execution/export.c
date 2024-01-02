/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:11:51 by ahraich           #+#    #+#             */
/*   Updated: 2024/01/02 05:19:21 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *cutvalue(char *str, int value_index)
{
    int i;

    i = 0;
    char *value;
    if(!str[value_index])
        return (NULL);
    value = ft_calloc(sizeof(char), ft_strlen(str) - value_index);
    if(str[value_index] == '=')
        value_index++;
    while (str[i + value_index])
    {
        value[i] = str[i + value_index];
        i++;
    }
    return (value);
}

char* cut_name(char *str , int *value_index)
{
    int     len;
    char*   name;
    int     i;

    len = 0;
    i = 0;
    while(str[len] == '=' || str[len] == '+')
        len++;
    while (str[len] && str[len] != '=')
        len++;
    *value_index = len;
    if(str[len] == '=' && len > 0 && str[len - 1] == '+')
        len--;
    name = (char *)ft_calloc(sizeof(char), len + 1);
    if(!name)
        return(NULL);
    while (str[i] && i < len)
    {
        name[i] = str[i];
        i++;
    }
    return (name);
}

void add_variable(char *str , t_data *data)
{
    int     value_index;
    char    *name;
    char    *value;

    name = cut_name(str, &value_index);
    value = cutvalue(str , value_index);
    if (!valid_var_name(name))
        printf("minishell: export: `%s': not a valid identifier\n", str);
    else
        join_env(name, value, data, to_join_values(name, value_index));
    free(name);
    free(value);
}

void    display_export(t_env *env)
{
    t_env   *tmp;

    tmp = env;
    while (tmp)
    {
        printf("declare -x %s", tmp->name);
        if(tmp->value)
            printf("=\"%s\"", tmp->value);
        printf("\n");
        tmp = tmp->next;
    }
}

int export(t_input *input, t_data *data)
{
    int i;

    i = 1;
    if(arg_count(input->args) == 1)
        display_export(data->export_list);
    else 
    {
        while (input->args[i])
        {
            add_variable(input->args[i], data);
            i++;
        }
    }
    return (0);
}
