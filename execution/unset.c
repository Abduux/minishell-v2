/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 09:46:25 by ahraich           #+#    #+#             */
/*   Updated: 2024/01/05 07:35:52 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int unset(t_data *data, t_input *input)//takes varaible names and removes them from the environment varaibles 
{
    int index;

    index = 1;
    while (input->args[index])
    {
        if(valid_var_name(input->args[index]))
        {
            delete_env(&data->env_list, input->args[index]);
            delete_export(&data->export_list, input->args[index]);
        }
        else
            ft_printf("minishell: unset: `%s': not a valid identifier\n", input->args[index]);
        index++;
    }
    return (0);
}