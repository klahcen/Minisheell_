/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:07:37 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/02 14:46:17 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_redirect_type(t_mini *mini, char **args)
{
	mini->new_redirect->type = 4;
	if (args[mini->j] != NULL)
	{
		mini->new_redirect->lim = args[mini->j];
	}
}

static t_redirect	*print_syntax_error(char **args, t_mini *mini)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(args[mini->j], 2);
	ft_putstr_fd("'\n", 2);
	return (NULL);
}

static t_redirect	*process_redirect(t_mini *mini, char **args)
{
	if (ft_strcmp(args[mini->i], ">") == 0)
		mini->new_redirect->type = 1;
	else if (ft_strcmp(args[mini->i], ">>") == 0)
		mini->new_redirect->type = 3;
	if (ft_strcmp(args[mini->i], "<<") == 0)
		set_redirect_type(mini, args);
	else if (ft_strcmp(args[mini->i], "<") == 0)
		mini->new_redirect->type = 2;
	if (args[mini->j][0] != '>' && args[mini->j][0] != '<'
		&& args[mini->j][0] != '|' && args[mini->j][0] != '\0')
		mini->new_redirect->file = args[mini->j];
	else
		return (print_syntax_error(args, mini));
	mini->new_redirect->next = NULL;
	if (mini->redirect == NULL)
	{
		mini->redirect = mini->new_redirect;
		mini->current_redirect = mini->new_redirect;
	}
	else
	{
		mini->current_redirect->next = mini->new_redirect;
		mini->current_redirect = mini->new_redirect;
	}
	return (mini->redirect);
}

static int	handle_redirection(t_mini *mini, char **args)
{
	mini->new_redirect = ft_malloc(sizeof(t_redirect));
	mini->j = mini->i + 1;
	while (args[mini->j] && ft_strcmp(args[mini->j], "") == 0)
		mini->j++;
	if (args[mini->j] != NULL)
	{
		mini->redirect = process_redirect(mini, args);
		if (mini->redirect == NULL)
			return (-1);
	}
	mini->i = mini->j;
	return (0);
}

t_redirect	*ft_redirection(char **args)
{
	t_mini	mini;

	mini.redirect = NULL;
	mini.current_redirect = NULL;
	mini.i = 0;
	while (args[mini.i])
	{
		if (ft_strcmp(args[mini.i], ">") == 0 || ft_strcmp(args[mini.i],
				">>") == 0 || ft_strcmp(args[mini.i], "<") == 0
			|| ft_strcmp(args[mini.i], "<<") == 0)
		{
			if (handle_redirection(&mini, args) == -1)
			{
				return (NULL);
			}
		}
		else
			mini.i++;
	}
	return (mini.redirect);
}
