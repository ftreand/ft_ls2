/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_recursive.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/07 17:21:16 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/02 16:58:44 by ftreand     ###    #+. /#+    ###.fr     */
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
}

void	ft_recup_recu_path(char *ret, char *path, char *name)
{
	ft_strcpy(ret, path);
	if (ft_strcmp(ret, "/") != 0)
		ft_strcat(ret, "/");
	ft_strcat(ret, name);
}

void	ft_recursive(t_ls **ls, t_flags fg, char *path)
{
	t_ls	*begin;
	t_pad	*pad;
	t_ls	*padd;
	DIR		*dir;
	int		i;
	t_ls *tmp;

	while ((*ls)->prev)
		(*ls) = (*ls)->prev;
	tmp = *ls;
	while (fg.r && (*ls)->next)
		(*ls) = (*ls)->next;
	while (ls)
	{
		i = 1;
		if ((*ls)->type == 4 && (*ls)->d_name[0] != '.')
		{
			fg.total = 0;
			errno = 0;
			dir = opendir((*ls)->path);
			if (errno)
			{
				ft_putchar('\n');
				ft_putstr((*ls)->path);
				ft_putendl(":");
				ft_putstr("ls : ");
				perror((*ls)->d_name);
				break ;
			}
			else
			{
				ft_recup_recu_path((*ls)->path, path, (*ls)->d_name);
				ft_fill_recursive_stats(&begin, &(*ls), dir, &fg);
				padd = begin;
			}
			if (!fg.a)
			{
				while (padd->d_name[0] == '.' && padd->next)
					padd = padd->next;
				padd->d_name[0] == '.' ? i = 0 : i;
			}
			pad = ft_padding(&padd);
			ft_putchar('\n');
			ft_putstr((*ls)->path);
			ft_putendl(":");
			if (i)
				ft_display(begin, &fg, pad);
			closedir(dir);
			ft_recursive(&begin, fg, (*ls)->path);
		}
		if (((*ls)->next && !fg.r) || ((*ls)->prev && fg.r))
			fg.r ? (*ls) = (*ls)->prev : ((*ls) = (*ls)->next);
		else
			break ;
	}
	*ls = tmp;
	ft_free_list(*ls);
}
