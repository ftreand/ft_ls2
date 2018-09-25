/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_recursive.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/07 17:21:16 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 16:41:04 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include <stdio.h>

void	ft_fill_recursive_stats(t_ls **begin, t_ls **ls, DIR *dir, t_flags *fg)
{
	t_ls	*recu;
	t_ls	*now;
	t_fill	fill;

	recu = NULL;
	while ((fill.dirent = readdir(dir)) != NULL)
	{
		if (!recu)
		{
			recu = (t_ls*)malloc(sizeof(t_ls));
			*begin = recu;
			recu->prev = NULL;
			recu->next = NULL;
			ft_recup_recu_path(recu->path, (*ls)->path, fill.dirent->d_name);
			ft_fill_struct(&(*recu), &fill);
			fg->total = fill.stats.st_blocks;
		}
		else
		{
			now = (t_ls*)malloc(sizeof(t_ls));
			recu = now;
			recu->next = NULL;
			recu->prev = NULL;
			ft_recup_recu_path(recu->path, (*ls)->path, fill.dirent->d_name);
			ft_fill_struct(&(*recu), &fill);
			fg->total += fill.stats.st_blocks;
			ft_sort_list(&(*begin), recu, (*fg));
		}
	}
	while ((*begin)->prev)
		(*begin) = (*begin)->prev;
}

void	ft_recup_recu_path(char *ret, char *path, char *name)
{
	ft_strcpy(ret, path);
	if (ft_strcmp(ret, "/") != 0)
		ft_strcat(ret, "/");
	ft_strcat(ret, name);
}
