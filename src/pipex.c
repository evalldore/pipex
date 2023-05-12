/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 08:52:06 by evallee-          #+#    #+#             */
/*   Updated: 2023/05/12 13:36:21 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	open_pipe(t_pipex *pipex, int argc, char **env)
{
	char	**paths;

	if (argc != 5)
	{
		ft_putstr_fd("pipex: Not enough arguments\n", 2);
		return (false);
	}
	paths = get_env_paths(env);
	if (!paths)
		return (false);
	if (pipe(pipex->fd) < 0)
		return (false);
	pipex->paths = paths;
	pipex->env = env;
	return (true);
}

static int	close_pipe(t_pipex *pipex)
{
	int		status;

	close_fds(pipex);
	waitpid(pipex->pid[0], &status, 0);
	waitpid(pipex->pid[1], &status, 0);
	free_array(pipex->paths);
	pipex->paths = NULL;
	return (WEXITSTATUS(status));
}

static void	end_fork(t_pipex pipex, int pid, int fd)
{
	if (pipex.pid[pid] < 0 || fd < 0)
		perror("pipex");
	if (fd >= 0)
		close(fd);
}

int	main(int argc, char	**argv, char **env)
{
	t_pipex	pipex;
	int		fd;

	pipex.pid[0] = 0;
	pipex.pid[1] = 0;
	if (!open_pipe(&pipex, argc, env))
		return (EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY, 0777);
	if (fd > -1)
	{
		pipex.pid[0] = fork();
		if (pipex.pid[0] == 0)
			exec_cmd(&pipex, fd, 1, argv[2]);
	}
	end_fork(pipex, 0, fd);
	fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (fd > -1)
	{
		pipex.pid[1] = fork();
		if (pipex.pid[1] == 0)
			exec_cmd(&pipex, fd, 0, argv[3]);
	}
	end_fork(pipex, 1, fd);
	return (close_pipe(&pipex));
}
