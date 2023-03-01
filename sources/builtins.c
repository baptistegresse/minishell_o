/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:24:08 by bgresse           #+#    #+#             */
/*   Updated: 2023/03/01 15:23:29 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_built_in_cd(char **full_cmd)
{
	if (chdir(full_cmd[1]) == -1)
		perror("chdir()");
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
	if (!strcmp(data->cmds->full_cmd[0], "pwd"))
		return (ft_built_in_pwd(), 1);
	if (!strcmp(data->cmds->full_cmd[0], "env"))
		return (ft_built_in_env(&data->head_env), 1);
	if (!strcmp(data->cmds->full_cmd[0], "export"))
		return (ft_built_in_export(&data->head_env, data->cmds->full_cmd), 1);
	if (!strcmp(data->cmds->full_cmd[0], "cd"))
		return (1);
	if (!strcmp(data->cmds->full_cmd[0], "unset"))
		return (1);
	return (0);
}

void	ft_special_builtins(t_minishell *data)
{
	if (!data->cmds->next && data->cmds->full_cmd[0])
	{
		if (!ft_strcmp(data->cmds->full_cmd[0], "cd"))
			return (ft_built_in_cd(data->cmds->full_cmd));
		if (!ft_strcmp(data->cmds->full_cmd[0], "exit"))
			return (ft_built_in_exit());
		if (!ft_strcmp(data->cmds->full_cmd[0], "export") \
			&& data->cmds->full_cmd[1])
			return (ft_built_in_export(&data->head_env, \
			data->cmds->full_cmd));
		if (!ft_strcmp(data->cmds->full_cmd[0], "unset"))
			return (ft_built_in_unset(&data->head_env, \
			data->cmds->full_cmd[1]));
	}
}
