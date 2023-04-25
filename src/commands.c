/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:13:37 by evallee-          #+#    #+#             */
/*   Updated: 2023/04/25 19:25:13 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*cmd_path;

	while (*paths)
	{
		cmd_path = ft_strjoin(*paths++, cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

static void	free_cmd(char	**cmds)
{
	char	**arr;

	arr = cmds;
	while (*arr)
		free(*arr++);
	free(cmds);
}

void	exec_cmd(t_pipex *pipex, int std, char *arg, char **env)
{
	char	**cmd;
	char	*cmd_path;
	int		status;

	cmd = ft_split(arg, ' ');
	dup2(pipex->fd[std], std);
	close(pipex->fd[1 - std]);
	dup2(pipex->files[1 - std], 1 - std);
	cmd_path = get_cmd(pipex->paths, cmd[0]);
	status = EXIT_SUCCESS;
	if (cmd_path)
	{
		if (execve(cmd_path, cmd, env) == -1)
			status = EXIT_FAILURE;
		free(cmd_path);
	}
	else
		status = 127;
	if (status == EXIT_FAILURE)
		perror("pipex");
	else if (status == 127)
		ft_putstr_fd("pipex: command not found\n", 2);
	free_cmd(cmd);
	exit(status);
}
