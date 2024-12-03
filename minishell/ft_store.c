/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:47:26 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/01 05:22:08 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_store_environment(char *env)
{
	t_env	*environment;
	int		i;

	i = 0;
	while (env[i] != '=')
		i++;
	environment = (t_env *)ft_malloc(sizeof(t_env));
	environment->name = ft_substr(env, 0, i);
	environment->value = ft_substr(env, i + 1, ft_strlen(env) - i);
	environment->next = NULL;
	return (environment);
}

t_env	*ft_add_env(t_env *env, char *name, char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = env;
	new = ft_create_env(name, value);
	if (!env)
		return (new);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (env);
}

t_env	*ft_create_default_env(void)
{
	t_env	*environment;
	t_env	*head;

	environment = ft_create_env("PWD", getcwd(NULL, 0));
	head = environment;
	environment->next = ft_create_env("SHLVL", "1");
	environment = environment->next;
	environment->next = ft_create_env("OLDPWD", getcwd(NULL, 0));
	environment = environment->next;
	environment->next = ft_create_env("_", "minishell");
	environment = environment->next;
	environment->next = NULL;
	return (head);
}

t_env	*ft_get_env(char **env)
{
	t_env	*environment;
	t_env	*head;
	int		i;

	if (!env || !*env)
	{
		return (ft_create_default_env());
	}
	i = 0;
	while (env[i])
	{
		if (i == 0)
		{
			environment = ft_store_environment(env[i]);
			head = environment;
		}
		else
		{
			environment->next = ft_store_environment(env[i]);
			environment = environment->next;
		}
		i++;
	}
	return (head);
}
