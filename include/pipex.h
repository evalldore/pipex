/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 08:52:18 by evallee-          #+#    #+#             */
/*   Updated: 2023/04/21 19:23:29 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft.h"
# define ERR_CMD "Command doesnt exist!"

typedef struct pipex
{
	int		fd[2];
	int		pid[2];
	int		files[2];
	char	**paths;
	char	**cmds[2];
}	t_pipex;

void	exec_cmd(t_pipex *pipex, int std, char *arg, char **env);

#endif