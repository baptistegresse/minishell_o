/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:51:24 by zrebhi            #+#    #+#             */
/*   Updated: 2023/03/01 15:34:41 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_newnode(t_cmdlist **cmds);
void	ft_syntax_error(char **parsed_line, int i);
void	ft_print_error(char **parsed_line, int i);

/* The following functions handle redirections for each command. */

void	ft_redirect_pipe(t_cmdlist **cmds)
{
	ft_newnode(cmds);
	if ((*cmds)->outfile == 1)
		(*cmds)->outfile = 0;
	*cmds = (*cmds)->next;
}

void	ft_redirect_infile(char **parsed_line, t_cmdlist *cmds, int i)
{
	if (!ft_error(parsed_line, i))
	{
		cmds->infile = open(parsed_line[i + 1], O_RDONLY);
		if (cmds->infile == -1)
			perror("open infile");
	}
}

void	ft_redirect_outfile(char **parsed_line, t_cmdlist *cmds, int i)
{
	if (!ft_error(parsed_line, i))
	{
		cmds->outfile = open(parsed_line[i + 1], \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmds->outfile == -1)
			perror("open outfile");
	}	
}

void	ft_redirect_outfile_append(char **parsed_line, t_cmdlist *cmds, int i)
{
	if (!ft_error(parsed_line, i))
	{
		cmds->outfile = open(parsed_line[i + 1], O_WRONLY | O_CREAT | \
				O_APPEND, 0644);
		if (cmds->outfile == -1)
			perror("open outfile");
	}
}

int	ft_redirection(char **parsed_line, t_cmdlist *cmds)
{
	int	i;

	i = -1;
	while (parsed_line[++i])
	{
		if (!strcmp(parsed_line[i], "|"))
			ft_redirect_pipe(&cmds);
		else if (!strcmp(parsed_line[i], "<"))
			ft_redirect_infile(parsed_line, cmds, i);
		else if (!strcmp(parsed_line[i], ">>"))
			ft_redirect_outfile_append(parsed_line, cmds, i);
		else if (!strcmp(parsed_line[i], ">"))
			ft_redirect_outfile(parsed_line, cmds, i);
		if (ft_error(parsed_line, i))
		{
			ft_print_error(parsed_line, i);
			return (0);
		}
	}
	return (1);
}
