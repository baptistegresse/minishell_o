/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:18:09 by bgresse           #+#    #+#             */
/*   Updated: 2023/03/01 17:33:02 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

char	**ft_expand_path(t_env **head, char **cmds)
{
	size_t	i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i][0] == '~' && !cmds[i][1])
		{
			cmds[i] = ft_get_env(head, "HOME");
			break ;
		}
		else if (cmds[i][0] == '~' && cmds[i][1] == '/')
		{
			cmds[i] = ft_strjoin(ft_get_env(head, "HOME"), cmds[i] + 1);
			break ;
		}
		i++;
	}
	return (cmds);
}

static char	*ft_expand_string(t_env **head, char *string,
	bool quote, bool dquote)
{
	size_t	i;
	char	*new_string;

	i = 0;
	new_string = ft_strdup("");
	while (string[i])
	{
		if (string[i] == '\'')
			quote = !quote;
		if (string[i] == '\"')
			dquote = !dquote;
		if (quote && !dquote && string[i + 1])
		{
			while (string[i] && string[i + 1] != '\'')
				new_string = ft_strjoin_char(new_string, string[i++]);
			quote = !quote;
		}
		if (string[i] == '$' && (dquote || (!dquote && !quote))
			&& string[i + 1] && ft_isalnum(string[i + 1]))
		{
			i++;
			new_string = ft_strjoin(new_string,
					ft_check_key(*head, string + i));
			while (string[i + 1] && (ft_isalnum(string[i + 1])
					|| string[i + 1] == '_'))
				i++;
		}
		else if (string[i] == '$' && (dquote || (!dquote && !quote))
			&& string[i + 1] == '?')
		{
			i++;
			new_string = ft_strjoin(new_string, ft_itoa(g_status));
		}
		else
			new_string = ft_strjoin_char(new_string, string[i]);
		i++;
	}
	return (new_string);
}

char	**ft_expand_var(t_env **head, char **cmds)
{
	size_t	i;

	i = 0;
	while (cmds[i])
	{
		if (ft_strchr(cmds[i], '$'))
			cmds[i] = ft_expand_string(head, cmds[i], false, false);
		i++;
	}
	return (cmds);
}

char	**ft_remove_quotes(char **cmds)
{
	size_t	i;

	i = 0;
	while (cmds[i])
	{
		if (ft_strchr(cmds[i], '\'') || ft_strchr(cmds[i], '\"'))
			cmds[i] = ft_remove_quote_in_string(cmds[i], false, false);
		i++;
	}
	return (cmds);
}
