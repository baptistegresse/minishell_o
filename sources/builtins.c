/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:24:08 by bgresse           #+#    #+#             */
/*   Updated: 2023/03/02 15:22:20 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_set_env(t_env **head, char *key, char *value)
{
	t_env	*temp;

	temp = *head;
	while (temp)
	{
		if (!ft_strcmp(temp->key, key))
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			return ;
		}
		temp = temp->next;
	}
	add_node(*head, key, value);
}

void	ft_built_in_cd(t_env **head, char **full_cmd)
{
	char	cwd[PATH_MAX];

	if (chdir(full_cmd[1]) == -1)
		perror("chdir()");
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (ft_get_env(head, "PWD"))
			ft_set_env(head, "OLDPWD", ft_get_env(head, "PWD"));
		ft_set_env(head, "PWD", cwd);
	}
	else
		perror("getcwd()");
}

void	ft_built_in_exit(void)
{
	exit(0);
}

void	ft_built_in_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd()");
}

int	ft_builtins(t_minishell *data)
{
	if (!ft_strcmp(data->cmds->full_cmd[0], "pwd"))
		return (ft_built_in_pwd(), 1);
	if (!ft_strcmp(data->cmds->full_cmd[0], "env"))
		return (ft_built_in_env(&data->head_env), 1);
	if (!ft_strcmp(data->cmds->full_cmd[0], "export"))
		return (ft_built_in_export(&data->head_env, data->cmds->full_cmd), 1);
	if (!ft_strcmp(data->cmds->full_cmd[0], "cd"))
		return (1);
	if (!ft_strcmp(data->cmds->full_cmd[0], "unset"))
		return (1);
	return (0);
}

void	ft_special_builtins(t_minishell *data)
{
	if (!data->cmds->next && data->cmds->full_cmd[0])
	{
		if (!ft_strcmp(data->cmds->full_cmd[0], "cd"))
			return (ft_built_in_cd(&data->head_env, data->cmds->full_cmd));
		if (!ft_strcmp(data->cmds->full_cmd[0], "exit"))
			return (ft_built_in_exit());
		if (!ft_strcmp(data->cmds->full_cmd[0], "export") \
			&& data->cmds->full_cmd[1])
			return (ft_built_in_export(&data->head_env, \
			data->cmds->full_cmd));
		if (!ft_strcmp(data->cmds->full_cmd[0], "unset"))
			return (ft_built_in_unset(&data->head_env, \
			data->cmds->full_cmd));
	}
}
