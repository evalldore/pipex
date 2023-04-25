/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:13:37 by evallee-          #+#    #+#             */
/*   Updated: 2023/04/24 19:30:07 by evallee-         ###   ########.fr       */
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

static void	free_cmds(char	**cmds)
{
	char	**arr;

	arr = cmds;
	while (*arr)
		free(*arr++);
	free(cmds);
}

int	exec_cmd(t_pipex *pipex, int std, char *arg, char **env)
{
	char	**cmd;
	char	*cmd_path;
	int		status;

	cmd = ft_split(arg, ' ');
	dup2(pipex->fd[std], std);
	close(pipex->fd[1 - std]);
	dup2(pipex->files[1 - std], 1 - std);
	status = -1;
	cmd_path = get_cmd(pipex->paths, cmd[0]);
	if (cmd_path)
	{
		status = execve(cmd_path, cmd, env);
		free(cmd_path);
	}
	free_cmds(cmd);
	if (status == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	return (status);
}
