/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:13:37 by evallee-          #+#    #+#             */
/*   Updated: 2023/04/21 19:44:22 by evallee-         ###   ########.fr       */
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
	perror("get_cmd\n\t");
	return (NULL);
}

void	exec_cmd(t_pipex *pipex, int std, char *arg, char **env)
{
	char	**cmd;
	char	**arr;
	char	*cmd_path;

	cmd = ft_split(arg, ' ');
	dup2(pipex->fd[std], std);
	close(pipex->fd[1 - std]);
	dup2(pipex->files[1 - std], 1 - std);
	cmd_path = get_cmd(pipex->paths, cmd[0]);
	if (cmd_path)
	{
		if (execve(cmd_path, cmd, env) == -1)
			perror("exec_cmd\n\t");
		free(cmd_path);
	}
	arr = cmd;
	while (*arr)
		free(*arr++);
	free(cmd);
}
