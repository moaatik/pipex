/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 04:12:12 by moaatik           #+#    #+#             */
/*   Updated: 2025/02/22 00:25:49 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>

void	free_strs(char **strs);
char	*get_paths(char **env);
int		ft_strlen(const char *s);
void	handle_file_error(char *file);
char	**ft_split(char const *s, char c);
char	*fix_path(char *str, char *command);
void	handle_command_error(char *command, int fd);
int		ft_strncmp(const char *s1, const char *s2, int size);

#endif
