/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:45:31 by pcampos-          #+#    #+#             */
/*   Updated: 2022/05/02 16:20:56 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_cmd_path(t_geral *vars)
{
	char	*tmp;
	char	*tmp2;
	int		i;
	int		j;

	j = -1;
	while (vars->path[++j])
	{
		tmp = ft_strjoin(vars->path[j], vars->cmd_path);
		tmp2 = ft_strdup(tmp);
		free (tmp);
		i = access(tmp2, F_OK);
		if (i < 0)
		{
			free (tmp2);
			continue ;
		}
		else
		{
			vars->cmd_path = ft_strdup(tmp2);
			free (tmp2);
			return ;
		}
	}
	error_handler(vars, 2);
}

char	*check_cmd_path(char *tmp)
{
	int		i;
	char	*str;

	i = -1;
	while (tmp[++i])
		if (tmp[i] == ' ')
			break ;
	str = ft_substr(tmp, 0, i);
	return (str);
}

void	good_path(t_geral *vars)
{
	int	a;

	a = access(vars->cmd_path, F_OK | X_OK);
	if (a < 0)
		error_handler(vars, 0);
}

void	get_cmd(t_geral *vars, int id)
{
	char	*tmp;
	int		i;

	i = -1;
	if (vars->args[id][0] == '/')
	{
		vars->cmd = ft_split(ft_strrchr(vars->args[id], '/') + 1, ' ');
		while (vars->args[id][++i])
			if (vars->args[id][i] == ' ')
				break ;
		vars->cmd_path = ft_substr(vars->args[id], 0, i);
		good_path(vars);
	}
	else
	{
		vars->cmd = ft_split(vars->args[id], ' ');
		vars->cmd_path = check_cmd_path(vars->args[id]);
		tmp = ft_strjoin("/", vars->cmd_path);
		free(vars->cmd_path);
		vars->cmd_path = ft_strdup(tmp);
		free(tmp);
		tmp = NULL;
		get_cmd_path(vars);
	}
}
