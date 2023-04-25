/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 08:52:06 by evallee-          #+#    #+#             */
/*   Updated: 2023/04/25 19:26:15 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	close_pipe(t_pipex *pipex)
{
	char	**paths;
	int		status;

	close(pipex->fd[0]);
	close(pipex->fd[1]);
	waitpid(pipex->pid[0], &status, 0);
	waitpid(pipex->pid[1], &status, 0);
	paths = pipex->paths;
	while (*paths)
		free(*paths++);
	free(pipex->paths);
	pipex->paths = NULL;
	return (status);
}

static char	**env_paths(char	**env)
{
	char	**arr;
	char	*temp;
	size_t	index;

	while (*env)
	{
		if (ft_strnstr(*env, "PATH", ft_strlen(*env)))
		{
			arr = ft_split(*env + 5, ':');
			index = 0;
			while (arr[index])
			{
				temp = arr[index];
				arr[index] = ft_strjoin(temp, "/");
				free(temp);
				index++;
			}
			return (arr);
		}
		env++;
	}
	return (NULL);
}

static int	open_pipe(t_pipex *pipex, char	*in, char *out, char **env)
{
	pipex->files[0] = open(in, O_RDONLY);
	pipex->files[1] = open(out, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex->files[1] < 0)
		return (EXIT_FAILURE);
	if (pipe(pipex->fd) < 0)
		return (EXIT_FAILURE);
	pipex->paths = env_paths(env);
	if (!pipex->paths)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char	**argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
		return (EXIT_FAILURE);
	if (open_pipe(&pipex, argv[1], argv[argc - 1], env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pipex.pid[0] = fork();
	if (pipex.pid[0] < 0)
		return (EXIT_FAILURE);
	if (pipex.pid[0] == 0)
		exec_cmd(&pipex, 1, argv[2], env);
	pipex.pid[1] = fork();
	if (pipex.pid[1] < 0)
		return (EXIT_FAILURE);
	if (pipex.pid[1] == 0)
		exec_cmd(&pipex, 0, argv[3], env);
	return (close_pipe(&pipex));
}
