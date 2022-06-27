/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:52:01 by acolin            #+#    #+#             */
/*   Updated: 2022/02/01 14:46:31 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_char(char *cmd, size_t start, size_t end)
{
	size_t	i;
	size_t	j;
	char	*deb;

	if (end < start)
		return (NULL);
	deb = ft_calloc(1, end - start + 1);
	if (!deb)
		return (NULL);
	i = start;
	j = 0;
	while (i < end)
		deb[j++] = cmd[i++];
	deb[j] = '\0';
	return (deb);
}

void	insert_code(char **cmd, size_t *start)
{
	char	*debut;
	char	*fin;
	char	*tmp;
	char	*num;

	debut = get_char(*cmd, 0, *start);
	fin = get_char(*cmd, *start + 2, ft_strlen(*cmd));
	num = ft_itoa(g_env.status);
	free(*cmd);
	if (fin)
	{
		tmp = ft_strjoin(debut, num);
		*cmd = ft_strjoin(tmp, fin);
		free(tmp);
		free(fin);
	}
	else
		*cmd = ft_strjoin(debut, num);
	free(debut);
	free(num);
}

void	insert(char **cmd, char *var, size_t *start, size_t end)
{
	char	*debut;
	char	*fin;
	char	*tmp;

	if (!var)
		var = "";
	debut = get_char(*cmd, 0, *start);
	fin = get_char(*cmd, end, ft_strlen(*cmd));
	free(*cmd);
	if (fin)
	{
		tmp = ft_strjoin(debut, var);
		*cmd = ft_strjoin(tmp, fin);
		free(tmp);
		free(fin);
	}
	else
		*cmd = ft_strjoin(debut, var);
	free(debut);
	*start += ft_strlen(var) - 1;
}

void	expend_var_quote(char **cmd, size_t *i, char quote)
{
	size_t	k;
	char	*kw;

	(*i)++;
	while (cmd[0][*i] != quote)
	{
		if (cmd[0][*i] == '$' && cmd[0][*i + 1] == '?')
			insert_code(cmd, i);
		else if (cmd[0][*i] == '$' && ft_isalnum(cmd[0][*i + 1]))
		{
			k = *i + 1;
			while (ft_isalnum(cmd[0][k]))
				k++;
			kw = get_char(*cmd, *i + 1, k);
			insert(cmd, get_var_env(kw),
				i, k);
			free(kw);
		}
		if (cmd[0][*i] == '\\')
			(*i)++;
		(*i)++;
	}
}

void	expend_var(char **cmd, size_t index)
{
	size_t	j;
	size_t	k;
	char	*kw;

	j = index;
	while (cmd[0][j] && cmd[0][j] != ' ')
	{
		if (cmd[0][j] == '$' && cmd[0][j + 1] == '?')
			insert_code(cmd, &j);
		else if (cmd[0][j] == '$' && ft_isalnum(cmd[0][j + 1]))
		{
			k = j + 1;
			while (ft_isalnum(cmd[0][k]))
				k++;
			kw = get_char(*cmd, j + 1, k);
			insert(cmd, get_var_env(kw),
				&j, k);
			free(kw);
		}
		j++;
	}
}
