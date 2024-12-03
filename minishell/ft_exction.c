/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:55:51 by lkazaz            #+#    #+#             */
/*   Updated: 2024/04/01 05:24:06 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_cmd *cmd, t_env **envir, t_exe exe, t_cmd *cmd1)
{
	if (!ft_buil(cmd, envir, exe.pip))
		return ;
	if (exe.status != 0 || !cmd->cmd)
		return ;
	exe.pid[exe.i] = fork();
	if (exe.pid[exe.i] == -1)
		(perror("fork"), exit(1));
	if (exe.pid[exe.i] == 0)
	{
		signal(SIGQUIT, handle2);
		if (exe.pip > 0)
		{
			if (exe.i == 0)
				(dup2(cmd->fd[0][1], 1), ft_close(cmd, exe.pip), ft_exec(cmd,
						exe.env, envir, cmd1));
			if (exe.i != exe.pip)
				(dup2(cmd->fd[exe.i - 1][0], 0), dup2(cmd->fd[exe.i][1], 1),
					ft_close(cmd, exe.pip), ft_exec(cmd, exe.env, envir, cmd1));
			if (exe.i == exe.pip)
				(dup2(cmd->fd[exe.i - 1][0], 0), ft_close(cmd, exe.pip),
					ft_exec(cmd, exe.env, envir, cmd1));
		}
		else
			ft_exec(cmd, exe.env, envir, cmd1);
	}
}

void	ft_next_exc(t_cmd *temp)
{
	t_redirect	*red;

	signal(SIGINT, SIG_DFL);
	while (temp)
	{
		red = temp->redirect;
		while (red)
		{
			if (red->type == 4 && red->status != 1)
			{
				ft_red_doc(red);
				close(red->pip[1]);
				close(red->pip[0]);
			}
			red = red->next;
		}
		temp = temp->next;
	}
	exit(0);
}

void	ft_execute(t_cmd *cmd, t_env **envir)
{
	t_exea	nor;

	if (!cmd)
		return ;
	nor.exe.env = ft_env(*envir);
	nor.exe.pip = 0;
	nor.exe.tmp = cmd;
	while (nor.exe.tmp->next)
	{
		nor.exe.pip++;
		nor.exe.tmp = nor.exe.tmp->next;
	}
	nor.exe.cmd1 = cmd;
	nor.exe.cmd2 = cmd;
	nor.tmp = cmd;
	nor.tmp1 = cmd;
	nor.nbr_her = 0;
	new_pipe(nor.exe.cmd1);
	nor.exe.i = 0;
	nor.exe.pid = ft_malloc((nor.exe.pip + 1) * sizeof(int));
	ft_exit_her_doc(nor);
	ft_norm_next(cmd, envir, nor);
}

void	ft_exit_her_doc(t_exea nor)
{
	while (nor.tmp)
	{
		nor.nbr_her += ft_nbr_her(nor.tmp);
		nor.tmp = nor.tmp->next;
	}
	if (nor.nbr_her > 16)
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
		exit(2);
	}
}

void	ft_norm_next(t_cmd *cmd, t_env **envir, t_exea nor)
{
	g_all.nbr_herdoc = nor.nbr_her;
	nor.temp = cmd;
	nor.pid = fork();
	if (!nor.pid)
		ft_next_exc(nor.temp);
	waitpid(nor.pid, &nor.exe.status, 0);
	if (nor.exe.status != 0)
	{
		g_all.status = 1;
		return ;
	}
	while (cmd)
	{
		execute_command(cmd, envir, nor.exe, nor.tmp1);
		cmd = cmd->next;
		nor.exe.i++;
	}
	ft_closered(nor.tmp1);
	ft_closered(nor.tmp1);
	ft_close(nor.exe.cmd2, nor.exe.pip);
	nor.exe.k = 0;
	while (nor.exe.k < nor.exe.i)
		waitpid(nor.exe.pid[nor.exe.k++], &nor.exe.status, 0);
	g_all.status = WEXITSTATUS(nor.exe.status);
}
