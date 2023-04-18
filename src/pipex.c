/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 08:52:06 by evallee-          #+#    #+#             */
/*   Updated: 2023/04/18 17:41:37 by evallee-         ###   ########.fr       */
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

void	free_cmd(char	**cmd)
{
	char	**arr;

	arr = cmd;
	while (*arr)
		free(*arr++);
	free(cmd);
}

void	exec_cmd(char	**cmd)
{
	uint32_t	i;

	i = 0;
	while (cmd[i])
		ft_printf("%s\n", cmd[i++]);
	free_cmd(cmd);
}

int	main(int argc, char	**argv)
{
	char	*in_path;
	char	*out_path;
	char	*cmd1;
	char	*cmd2;

	if (argc == 5)
	{
		in_path = argv[1];
		ft_printf("in: %s\n", in_path);
		cmd1 = argv[2];
		exec_cmd(ft_split(cmd1, ' '));
		cmd2 = argv[3];
		exec_cmd(ft_split(cmd2, ' '));
		out_path = argv[4];
		ft_printf("out: %s\n", out_path);
	}
	return (EXIT_SUCCESS);
}
