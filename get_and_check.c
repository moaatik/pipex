/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 23:14:43 by moaatik           #+#    #+#             */
/*   Updated: 2025/02/21 23:15:06 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_paths(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*fix_path(char *str, char *command)
{
	char	*path;
	int		i;
	int		j;

	if (!str || !command)
		return (NULL);
	path = malloc(ft_strlen(str) + ft_strlen(command) + 2);
	if (!path)
		return (NULL);
	i = 0;
	while (str[i])
	{
		path[i] = str[i];
		i++;
	}
	path[i++] = '/';
	j = 0;
	while (command[j])
	{
		path[i] = command[j];
		i++;
		j++;
	}
	path[i] = 0;
	return (path);
}
