/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:09:05 by lkazaz            #+#    #+#             */
/*   Updated: 2024/04/01 05:24:14 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_next1(t_cmd *tmp)
{
	if (!tmp->cmd)
	{
		if (access(tmp->files, F_OK) != -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tmp->files, 2);
			ft_putstr_fd(" Is a directory\n", 2);
			exit(126);
		}
	}
}

void	ft_exec(t_cmd *tmp, char **env, t_env **envir, t_cmd *cmd1)
{
	char		**cmdd;
	t_redirect	*red;
	char		*str;
	int			i;

	i = 0;
	ft_next1(tmp);
	red = tmp->redirect;
	if (red)
		ft_redirect(red);
	if (!ft_builtins(tmp, envir))
		exit(0);
	i = ft_strrch(tmp->cmd, '/');
	str = ft_substrr(tmp->cmd, i);
	i = 0;
	while (tmp->args[i])
		str = ft_strjoin2(str, " ", tmp->args[i++]);
	str = ft_strjoin2(str, " ", tmp->files);
	str = ft_strjoin(str, " ");
	cmdd = ft_split(str, ' ');
	if (!tmp->cmd && !tmp->args[0])
		exit(0);
	(ft_closered(cmd1), ft_closered1(cmd1));
	if (execve(tmp->cmd, cmdd, env) == -1)
		ft_error(tmp->cmd);
}

void	create_pipe(t_cmd *data, t_exe exe)
{
	exe.i = 0;
	while (exe.i < exe.ac)
	{
		if (pipe(data->fd[exe.i]) == -1)
		{
			perror("pipe");
			exit(1);
		}
		exe.i++;
	}
}

void	new_pipe(t_cmd *data)
{
	t_exe	exe;

	exe.ac = 0;
	exe.tmp = data;
	while (exe.tmp->next)
	{
		exe.ac++;
		exe.tmp = exe.tmp->next;
	}
	data->fd = ft_malloc((exe.ac) * sizeof(int *));
	if (!data->fd)
		return ;
	exe.i = 0;
	while (exe.i < exe.ac)
		data->fd[exe.i++] = ft_malloc(2 * sizeof(int));
	exe.i = 0;
	create_pipe(data, exe);
	exe.f = data->fd;
	exe.tmp = data;
	while (exe.tmp)
	{
		exe.tmp->fd = exe.f;
		exe.tmp = exe.tmp->next;
	}
}

void	ft_close(t_cmd *data, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		close(data->fd[j][1]);
		close(data->fd[j][0]);
		j++;
	}
}
