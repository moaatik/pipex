/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:33:12 by moaatik           #+#    #+#             */
/*   Updated: 2025/02/21 23:18:35 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	free_strs(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

int	ft_strncmp(const char *s1, const char *s2, int size)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < size)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return (1);
		i++;
	}
	return (0);
}

void	handle_command_error(char *command, int fd)
{
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n", 20);
	close(fd);
	exit(127);
}

void	handle_file_error(char *file)
{
	write(2, "pipex: ", 7);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	perror("");
	exit(1);
}
