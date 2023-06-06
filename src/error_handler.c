/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 10:42:24 by pcampos-          #+#    #+#             */
/*   Updated: 2022/05/02 17:05:03 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_path(t_geral *vars)
{
	int	i;

	i = -1;
	while (vars->path[++i])
		free (vars->path[i]);
	free (vars->path);
}

void	free_all(t_geral *vars)
{
	int	i;

	i = -1;
	while (vars->args[++i])
		free (vars->args[i]);
	free (vars->args);
	free_path(vars);
}

void	error_handler(t_geral *vars, int op)
{
	perror("ERROR");
	if (op == 1)
	{
		if (vars->heredoc)
			free_path(vars);
		else
			free_all(vars);
	}
	else if (op == 2)
		free_path(vars);
	else
		free_all(vars);
	exit(EXIT_FAILURE);
}
