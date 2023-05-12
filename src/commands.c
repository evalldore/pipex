/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:13:37 by evallee-          #+#    #+#             */
/*   Updated: 2023/05/12 13:34:11 by evallee-         ###   ########.fr       */
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
	print_error("command not found", cmd);
	return (NULL);
}

static void	dup_fds(t_pipex *pipex, int fd, int std)
{
	dup2(pipex->fd[std], std);
	dup2(fd, 1 - std);
	close_fds(pipex);
	close(fd);
}

void	exec_cmd(t_pipex *pipex, int fd, int std, char *arg)
{
	char	**cmd;
	char	*cmd_path;

	cmd = ft_split(arg, ' ');
	if (!cmd)
		return ;
	cmd_path = get_cmd(pipex->paths, cmd[0]);
	if (cmd_path)
	{
		dup_fds(pipex, fd, std);
		execve(cmd_path, cmd, pipex->env);
		perror("pipex");
		free(cmd_path);
	}
	close_fds(pipex);
	close(fd);
	free_array(cmd);
	free_array(pipex->paths);
	exit(0);
}
