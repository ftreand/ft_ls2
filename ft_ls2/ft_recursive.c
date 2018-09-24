/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_recursive.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/07 17:21:16 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/24 18:33:35 by ftreand     ###    #+. /#+    ###.fr     */
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
/*
void	ft_recursive(t_ls **ls, t_flags fg, char *path)
{
	t_ls	*begin;
	t_ls	*padd;
	DIR		*dir;
	t_ls *tmp;

	tmp = *ls;
	while (fg.r && (*ls)->next)
		(*ls) = (*ls)->next;
	while (ls)
	{
		if ((!fg.a && (*ls)->d_name[0] == '.'))
		{
			if (((*ls)->next && !fg.r) || ((*ls)->prev && fg.r))
			{
				(*ls) = fg.r ? (*ls)->prev : (*ls)->next;
				continue ;
			}
			else
				break ;
		}
		fg.i = 1;
		if ((*ls)->type == 4 && ((*ls)->d_name[0] != '.' || (((*ls)->d_name[1]
							&& (*ls)->d_name[1] != '.'))))
		{
			fg.total = 0;
//			errno = 0;
			ft_opti_recu_error(&(*ls), fg);
//			dir = opendir((*ls)->path);
///			if (errno)
//			{
//				ft_print_base((*ls)->path);
//				ft_putstr("ls : ");
//				perror((*ls)->d_name);
//				if ((!fg.r && (*ls)->next) || (fg.r && (*ls)->prev))
//				{
//					!fg.r ? (*ls) = (*ls)->next : ((*ls) = (*ls)->prev);
//					continue ;
				}
				else
					break ;
			}
			else
			{
				ft_recup_recu_path((*ls)->path, path, (*ls)->d_name);
				ft_fill_recursive_stats(&begin, &(*ls), dir, &fg);
				padd = begin;
			}
			ft_opti_recu0(fg, ls, padd, begin);
			closedir(dir);
			ft_recursive(&begin, fg, (*ls)->path);
		}
		if ((((*ls)->next) && !fg.r) || ((*ls)->prev && fg.r))
			(*ls) = fg.r ? (*ls)->prev : ((*ls)->next);
		else
			break ;
	}
	*ls = tmp;
	ft_free_list(*ls);
}*/
