/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:42:52 by evallee-          #+#    #+#             */
/*   Updated: 2023/05/10 20:49:32 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *error, char *file)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putchar_fd('\n', 2);
}

void	free_array(char	**arr)
{
	char	**temp;

	temp = arr;
	while (*temp)
		free(*temp++);
	free(arr);
}

void	close_fds(t_pipex *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

static char	**split_paths(char	**env)
{
	while (*env)
	{
		if (ft_strnstr(*env, "PATH", ft_strlen(*env)))
			return (ft_split(*env + 5, ':'));
		env++;
	}
	return (NULL);
}

char	**get_env_paths(char	**env)
{
	char	**arr;
	char	*temp;
	size_t	index;

	arr = split_paths(env);
	if (!arr)
		return (NULL);
	index = 0;
	while (arr[index])
	{
		temp = arr[index];
		arr[index] = ft_strjoin(temp, "/");
		if (!arr[index])
		{
			free_array(arr);
			return (NULL);
		}
		free(temp);
		index++;
	}
	return (arr);
}
