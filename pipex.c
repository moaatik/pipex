/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 04:12:15 by moaatik           #+#    #+#             */
/*   Updated: 2025/02/21 23:37:41 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *command, char **env)
{
	char	**paths;
	char	*path;
	int		i;

	paths = ft_split(get_paths(env), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = fix_path(paths[i], command);
		if (!access(path, X_OK))
			return (free_strs(paths), path);
		free(path);
		i++;
	}
	return (free_strs(paths), NULL);
}

void	first_child(char **argv, char **env, int *pipe_fd)
{
	int		fd;
	char	**args;
	char	*path;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		handle_file_error(argv[1]);
	dup2(fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	args = ft_split(argv[2], ' ');
	path = find_path(args[0], env);
	if (!path)
		handle_command_error(args[0], fd);
	if (execve(path, args, env) == -1)
	{
		free_strs(args);
		free(path);
		exit(1);
	}
}

void	second_child(char **argv, char **env, int *pipe_fd)
{
	int		fd;
	char	**args;
	char	*path;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		handle_file_error(argv[4]);
	dup2(fd, STDOUT_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	args = ft_split(argv[3], ' ');
	path = find_path(args[0], env);
	if (!path)
		handle_command_error(args[0], fd);
	if (execve(path, args, env) == -1)
	{
		free_strs(args);
		free(path);
		exit(1);
	}
}

int	main(int argc, char **argv, char **env)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		return (write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40), 1);
	if (pipe(pipe_fd) < 0)
		return (perror("pipe"), 1);
	pid1 = fork();
	if (pid1 < 0)
		return (write(2, "fork failed\n", 13), 1);
	if (pid1 == 0)
		first_child(argv, env, pipe_fd);
	pid2 = fork();
	if (pid2 < 0)
		return (write(2, "fork failed\n", 13), 1);
	if (pid2 == 0)
		second_child(argv, env, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
