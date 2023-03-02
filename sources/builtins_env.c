/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:37:40 by zrebhi            #+#    #+#             */
/*   Updated: 2023/03/02 15:36:31 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_built_in_env(t_env **head)
{
	t_env	*temp;

	temp = *head;
	printf("mon env:\n");
	while (temp)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

void ft_print_env_sorted(t_env *env)
{
	env = env->next;
	printf("%s", env->value);
}

void    ft_built_in_export(t_env **head, char **full_cmd)
{
	size_t  i;
	char	*equal;
	char	*key;
	char	*value;

	i = 1;
	if (!full_cmd[1])
		ft_print_env_sorted(*head);
	while (full_cmd[i])
	{
		equal = ft_strchr(full_cmd[i], '=');
		key = ft_strndup(full_cmd[i], equal - full_cmd[i]);
		if (ft_get_env(head, key) == NULL || !(equal + 1))
		{
			value = ft_strdup(equal + 1);
			*head = add_node(*head, key, value);
			free(key);
		}
		else
			free(key);
		i++;
	}
}


static void	remove_env_node(t_env **head, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	if (current != NULL && ft_strcmp(current->key, key) == 0)
	{
		*head = current->next;
		free(current->key);
		free(current->value);
		free(current);
		return ;
	}
	while (current != NULL && ft_strcmp(current->key, key) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	prev->next = current->next;
	return (free(current->key), free(current->value), free(current));
}

void	ft_built_in_unset(t_env **head, char **key)
{
	size_t	i;
	t_env	*temp;

	i = 1;
	while (key[i])
	{
		temp = *head;
		while (temp)
		{
			if (ft_strcmp(temp->key, key[i]) == 0)
				remove_env_node(head, key[i]);
			temp = temp->next;
		}
		i++;
	}
}
