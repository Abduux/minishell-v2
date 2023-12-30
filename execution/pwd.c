/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahraich <ahraich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 07:39:34 by ahraich           #+#    #+#             */
/*   Updated: 2023/12/25 12:59:55 by ahraich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pwd(void)
{
	char	cwdir[PATH_MAX];

	if(!getcwd(cwdir, PATH_MAX)){
		write(2 , "Error accured !\n", 17);
		return (1);
	}
	else
		printf("%s\n", cwdir);
	return (0);
}