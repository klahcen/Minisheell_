/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next1_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:07:18 by lkazaz            #+#    #+#             */
/*   Updated: 2024/04/03 23:36:55 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_next_exit(char **args)
{
	int	i;

	i = 0;
	while (args[0][i])
	{
		if (!ft_isdigit(args[0][i]))
		{
			ft_putstr_fd("exit\n", 2);
			printf("minishell: exit: %s: numeric argument required\n", args[0]);
			exit(2);
		}
		i++;
	}
}

int	ft_exit(t_cmd *cmd)
{
	if (!cmd->args[0])
		exit(0);
	else
	{
		ft_next_exit(cmd->args);
		if (cmd->args[1])
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			g_all.status = 1;
			return (0);
		}
		else
		{
			ft_putstr_fd("exit\n", 2);
			exit(ft_atoi(cmd->args[0]));
		}
	}
	return (0);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*p;
	t_env	*tmp;
	t_env	*t;

	p = *lst;
	t = *lst;
	while (t)
	{
		if (!ft_strcmp(t->name, new->name))
		{
			if (new->value || !ft_strcmp(new->value, ""))
				t->value = ft_strdup(new->value);
			return ;
		}
		t = t->next;
	}
	while (p->next->next)
		p = p->next;
	tmp = p->next;
	p->next = new;
	p->next->next = tmp;
}

int	ft_affichenv(t_env *envir)
{
	char	**env;

	if (!envir)
		return (1);
	env = ft_env(envir);
	while (env && *env)
	{
		if (ft_strchr(*env, '='))
			printf("%s\n", *env);
		env++;
	}
	return (0);
}

int	ft_echo(t_cmd *tmp)
{
	int		i;
	char	*str;
	int		j;

	i = 0;
	j = 1;
	str = NULL;
	if (tmp->args[0])
	{
		str = ft_malloc(ft_strlen(tmp->args[0]) + 1);
		if (!str)
			return (0);
		while (tmp->args[0][j])
		{
			if (tmp->args[0][0] != '-' || tmp->args[0][j] != 'n')
				break ;
			str[0] = '-';
			str[j] = tmp->args[0][j];
			j++;
		}
		str[j] = '\0';
	}
	ft_next_echo(tmp, str, i);
	return (0);
}
