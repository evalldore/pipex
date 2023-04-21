/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 08:52:06 by evallee-          #+#    #+#             */
/*   Updated: 2023/04/21 06:05:31 by niceguy          ###   ########.fr       */
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

static void	exec_cmd(t_pipex *pipex, int std, char *arg, char **env)
{
	char	**cmd;
	char	**arr;
	char	**paths;
	char	*cmd_path;

	cmd = ft_split(arg, ' ');
	dup2(pipex->fd[std], std);
	close(pipex->fd[1 - std]);
	dup2(pipex->files[1 - std], 1 - std);
	paths = pipex->paths;
	while (*paths)
	{
		cmd_path = ft_strjoin(*paths++, cmd[0]);
		if (execve(cmd_path, cmd, env) == 0)
		{
			free(cmd_path);
			break;
		}
		free(cmd_path);
	}
	arr = cmd;
	while (*arr)
		free(*arr++);
	free(cmd);
}

static int	open_inout(t_pipex *pipex, char	*in, char *out)
{
	pipex->files[0] = open(in, O_RDONLY);
	if (pipex->files[0] < 0)
		return (EXIT_FAILURE);
	pipex->files[1] = open(out, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex->files[1] < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	close_pipe(t_pipex *pipex)
{
	char	**paths;

	close(pipex->fd[0]);
	close(pipex->fd[1]);
	waitpid(pipex->pid[0], NULL, 0);
	waitpid(pipex->pid[1], NULL, 0);
	paths = pipex->paths;
	while (*paths)
		free(*paths++);
	free(pipex->paths);
	pipex->paths = NULL;
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

int	main(int argc, char	**argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
		return (EXIT_FAILURE);
	if (open_inout(&pipex, argv[1], argv[argc - 1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pipe(pipex.fd) < 0)
		return (EXIT_FAILURE);
	pipex.paths = env_paths(env);
	pipex.pid[0] = fork();
	if (pipex.pid[0] < 0)
		return (2);
	if (pipex.pid[0] == 0)
		exec_cmd(&pipex, 1, argv[2], env);
	pipex.pid[1] = fork();
	if (pipex.pid[1] < 0)
		return (3);
	if (pipex.pid[1] == 0)
		exec_cmd(&pipex, 0, argv[3], env);
	close_pipe(&pipex);
	return (EXIT_SUCCESS);
}
