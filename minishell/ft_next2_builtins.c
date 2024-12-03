/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next2_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:10:52 by lkazaz            #+#    #+#             */
/*   Updated: 2024/03/30 12:59:37 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_next_cd(t_cmd *tmp, t_env *envir, char *newpath, char *oldpwd)
{
	if (chdir(tmp->files) == -1)
	{
		perror("cd");
		return (0);
	}
	else
	{
		getcwd(newpath, 256);
		ft_modifenv(envir, "PWD", newpath);
		ft_modifenv(envir, "OLDPWD", oldpwd);
	}
	return (1);
}

int	ft_cd(t_cmd *tmp, t_env *envir)
{
	char	*home;
	char	oldpwd[256];
	char	newpath[256];

	getcwd(oldpwd, 256);
	home = t_getdata(envir, "HOME");
	if (tmp->args[0])
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(tmp->args[0]);
		return (0);
	}
	if (!tmp->files)
	{
		if (!home)
		{
			ft_putstr_fd("bash: cd: HOME not set\n", 2);
			return (0);
		}
		else
			tmp->files = ft_strdup(home);
	}
	if (!ft_next_cd(tmp, envir, newpath, oldpwd))
		return (0);
	return (0);
}

void	ft_sorte(char **str)
{
	int		i;
	char	*s;
	int		j;

	i = 0;
	while (str[i])
	{
		j = i;
		while (str[j])
		{
			if (strcmp(str[i], str[j]) > 0)
			{
				s = ft_strdup(str[j]);
				str[j] = ft_strdup(str[i]);
				str[i] = ft_strdup(s);
			}
			j++;
		}
		i++;
	}
}

int	ft_next_unset(char **str, t_env *temp, int i, t_env **head_ref)
{
	t_env	*temp1;

	temp1 = NULL;
	while (temp != NULL && ft_strcmp(temp->name, str[i]))
	{
		temp1 = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return (0);
	if (temp1 == NULL)
		(*head_ref) = temp->next;
	else
		temp1->next = temp->next;
	return (1);
}
