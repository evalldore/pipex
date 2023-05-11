/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 08:52:18 by evallee-          #+#    #+#             */
/*   Updated: 2023/05/11 13:38:12 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"
# define ERR_CMD "Command doesnt exist!"

typedef struct pipex
{
	int		pid[2];
	int		fd[2];
	char	**paths;
	char	**env;
}	t_pipex;

void	exec_cmd(t_pipex *pipex, int fd, int std, char *arg);
void	print_error(char *error, char *file);
char	**get_env_paths(char	**env);
void	free_array(char	**arr);
void	close_fds(t_pipex *pipex);

#endif