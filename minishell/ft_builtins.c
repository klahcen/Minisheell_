/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:21:16 by lkazaz            #+#    #+#             */
/*   Updated: 2024/04/04 01:26:38 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_cmd *cmd, t_env **head_ref)
{
	int		i;
	t_env	*temp;

	i = 0;
	while (cmd->args[i])
	{
		temp = *head_ref;
		if (temp != NULL && !ft_strcmp(temp->name, cmd->args[i]))
		{
			(*head_ref) = temp->next;
			return (0);
		}
		if (!ft_strcmp(cmd->args[i], "_"))
		{
			if (cmd->args[i + 1])
				i++;
			else
				return (0);
		}
		if (!ft_next_unset(cmd->args, temp, i, head_ref))
			return (0);
		i++;
	}
	return (0);
}

int	ft_strnchr(const char *str, int a)
{
	char			*c;
	unsigned char	l;
	int				i;

	c = (char *)str;
	i = 0;
	l = (unsigned char)a;
	while (*c)
	{
		if (*c == l)
			return (i);
		c++;
		i++;
	}
	if (l != 0)
		return (i);
	return (i);
}

void	ft_next_export(char **str, t_env **envir)
{
	int		i;
	int		len;
	t_env	*new;

	i = 0;
	while (str[i])
	{
		new = ft_malloc(sizeof(t_env));
		if (new == NULL)
			return ;
		len = 0;
		while (str[i][len])
			len++;
		new->name = ft_substr(str[i], 0, ft_strnchr(str[i], '='));
		new->value = ft_substr(str[i], ft_strnchr(str[i], '=') + 1, len);
		if (!new->value && ft_strchr(str[i], '='))
			new->value = ft_strdup(" ");
		new->next = NULL;
		if (ft_isalpha(new->name[0]))
			ft_lstadd_back(envir, new);
		else if (new->name[0] != '#')
			printf("minishell: export: `%s': not a valid identifier\n",
				new->name);
		i++;
	}
}

int	ft_export(t_cmd *cmd, t_env **envir)
{
	t_norrr	nor;

	nor.index = 0;
	ft_next_export(cmd->args, envir);
	if (!cmd->args[0] || !ft_strcmp(cmd->args[0], "#"))
	{
		nor.str = ft_env(*envir);
		ft_sorte(nor.str);
		while (nor.str[nor.index])
		{
			printf("declare -x %s", ft_substr(nor.str[nor.index], 0,
					ft_strnchr(nor.str[nor.index], '=')));
			nor.src = ft_substr(nor.str[nor.index],
					ft_strnchr(nor.str[nor.index], '=') + 1,
					ft_strlen(nor.str[nor.index]));
			if (nor.src && ft_strcmp(nor.src, " "))
				printf("=\"%s\"\n", nor.src);
			else if (!ft_strcmp(nor.src, " "))
				printf("=\"\"\n");
			else
				printf("\n");
			nor.index++;
		}
	}
	return (0);
}

int	ft_builtins(t_cmd *tmp, t_env **envir)
{
	char	*command;

	if (tmp && tmp->cmd)
	{
		command = ft_last_world(tmp->cmd);
		if (command)
		{
			if (ft_strcmp(command, "echo") == 0)
				return (ft_echo(tmp));
			else if (ft_strcmp(command, "cd") == 0)
				return (ft_cd(tmp, *envir));
			else if (ft_strcmp(command, "pwd") == 0)
				return (ft_pwd());
			else if ((ft_strcmp(command, "env") == 0))
				return (ft_affichenv(*envir));
			else if ((ft_strcmp(command, "unset") == 0))
				return (ft_unset(tmp, envir));
			else if (ft_strcmp(command, "export") == 0)
				return (ft_export(tmp, envir));
			else if (ft_strcmp(command, "exit") == 0)
				return (ft_exit(tmp));
		}
	}
	return (-1);
}
