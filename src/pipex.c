/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 08:52:06 by evallee-          #+#    #+#             */
/*   Updated: 2023/04/21 00:15:50 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
	int	fd[2];
	int	pid[2];

	(void)argc;
	(void)argv;
	if (pipe(fd) == -1)
		return (EXIT_FAILURE);
	pid[0] = fork();
	if (pid[0] < 0)
		return (2);
	if (pid[0] == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	pid[1] = fork();
	if (pid[1] < 0)
		return (3);
	if (pid[1] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "rtt", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
*/

/*void	pipex(const char *in, char **cmd1, char **cmd2, const char *out)
{
	
}*/

void	exec_cmd(t_pipex *pipex, int std, char *arg)
{
	char	**cmd;
	char	**arr;

	cmd = ft_split(arg, ' ');
	dup2(pipex->fd[std], std);
	close(pipex->fd[1 - std]);
	dup2(pipex->paths[1 - std], 1 - std);
	execve(cmd[0], &cmd[1], NULL);
	arr = cmd;
	while (*arr)
		free(*arr++);
	free(cmd);
}

int	open_inout(t_pipex *pipex, char	*in, char *out)
{
	pipex->paths[0] = open(in, O_RDONLY);
	if (pipex->paths[0] < 0)
		return (EXIT_FAILURE);
	pipex->paths[1] = open(out, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex->paths[1] < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	close_pipe(t_pipex *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	waitpid(pipex->pid[0], NULL, 0);
	waitpid(pipex->pid[1], NULL, 0);
}

int	main(int argc, char	**argv, char **env)
{
	t_pipex	pipex;

	(void)env;
	if (argc != 5)
		return (EXIT_FAILURE);
	if (open_inout(&pipex, argv[1], argv[argc - 1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pipe(pipex.fd) == -1)
		return (EXIT_FAILURE);
	pipex.pid[0] = fork();
	if (pipex.pid[0] < 0)
		return (2);
	if (pipex.pid[0] == 0)
		exec_cmd(&pipex, 1, argv[2]);
	pipex.pid[1] = fork();
	if (pipex.pid[1] < 0)
		return (3);
	if (pipex.pid[1] == 0)
		exec_cmd(&pipex, 0, argv[3]);
	close_pipe(&pipex);
	return (EXIT_SUCCESS);
}
