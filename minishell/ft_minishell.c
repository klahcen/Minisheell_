/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 01:48:35 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/02 14:53:21 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_minishell(t_node *node, t_env **envir)
{
	t_mini	mini;
	t_cmd	*cmd;

	mini.tmp1 = node;
	mini.new_cmd = NULL;
	mini.cmd = ft_malloc(sizeof(t_cmd));
	if (node->args == NULL)
		return ;
	mini.current_cmd = mini.cmd;
	mini.first_redirect = NULL;
	mini.current_redirect = NULL;
	cmd = ft_process_commands(&mini, envir);
	if (cmd == NULL)
		return ;
	mini.cmd_path = ft_get_path(cmd, *envir);
	ft_execute(mini.cmd_path, envir);
}

static t_cmd	*allocate_next_command(t_cmd *current_cmd)
{
	current_cmd->next = ft_malloc(sizeof(t_cmd));
	return (current_cmd->next);
}

int	ft_gha_syntax_error(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0
			|| ft_strcmp(args[i], "<") == 0 || ft_strcmp(args[i], "<<") == 0)
		{
			if (args[i + 1] == NULL)
			{
				ft_putstr_fd("minishell:", 2);
				ft_putstr_fd("syntax error near unexpected token `\n", 2);
				return (1);
			}
			if (args[i + 1][0] == '>' || args[i + 1][0] == '<' || args[i
				+ 1][0] == '|' || args[i + 1][0] == '\0')
			{
				return (gha_error(args[i + 1]));
			}
		}
		i++;
	}
	return (0);
}

t_cmd	*ft_process_commands(t_mini *mini, t_env **envir)
{
	while (mini->tmp1)
	{
		mini->strtrim = ft_strtrim(mini->tmp1->args, " ");
		mini->args = ft_split2(mini->strtrim, " \t\n\r\v\f");
		if (!mini->args[0] || ft_gha_syntax_error(mini->args) == 1)
			return (NULL);
		mini->expanded = 0;
		mini->i = 0;
		mini->args = ft_process_args(mini->args, envir);
		mini->new_redirect = ft_redirection(mini->args);
		ft_process_redirect(mini, envir);
		mini->new_cmd = ft_set_arguments(mini->args, mini->current_cmd,
				mini->first_redirect);
		if (mini->new_cmd == NULL)
			return (NULL);
		mini->current_cmd = mini->new_cmd;
		mini->current_cmd->redirect = mini->first_redirect;
		mini->first_redirect = NULL;
		if (mini->tmp1->next)
			mini->current_cmd = allocate_next_command(mini->current_cmd);
		else
			mini->current_cmd->next = NULL;
		mini->tmp1 = mini->tmp1->next;
	}
	return (mini->cmd);
}

void	ft_process_redirect(t_mini *mini, t_env **envir)
{
	if (mini->new_redirect != NULL)
	{
		mini->new_redirect->envir = *envir;
		if (mini->first_redirect == NULL)
		{
			mini->first_redirect = mini->new_redirect;
			mini->current_redirect = mini->new_redirect;
		}
		else
		{
			mini->current_redirect->next = mini->new_redirect;
			mini->current_redirect = mini->new_redirect;
		}
	}
}
