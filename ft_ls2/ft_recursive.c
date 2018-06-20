/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_recursive.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/07 17:21:16 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/20 15:35:14 by ftreand     ###    #+. /#+    ###.fr     */
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
//	printf("name = %s\n", name);
//	printf("ret = %s\n", ret);
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

//	printf("(*ls) dname = %s\n", (*ls)->d_name);
//	while (!ft_strcmp((*ls)->d_name, ".") || !ft_strcmp((*ls)->d_name, ".."))
//	{
//		(*ls) = (*ls)->prev;
//		if (!ft_strcmp((*ls)->d_name, ".."))
//		{
//		if ((*ls)->next)
//			(*ls) = (*ls)->next;
//			break ;
//		}
//	}
//	printf("d_name = %s\n", (*ls)->d_name);
//	printf("ls path = %s\n", (*ls)->path);
//	printf("d_name next= %s\n", (*ls)->next->d_name);
	tmp = *ls;
	while (fg.r && (*ls)->next)
		(*ls) = (*ls)->next;
	while (ls)
	{
//		printf("ls->d_name = %s\n", (*ls)->d_name);
		if ((!fg.a && (*ls)->d_name[0] == '.') || (fg.a && (!ft_strcmp((*ls)->d_name, ".") || !ft_strcmp((*ls)->d_name, ".."))))
		{
			if ((*ls)->next)
			{
				(*ls) = (*ls)->next;
				printf("ls d_name = %s\n", (*ls)->d_name);
				continue ;
			}
			else
				break ;
		}
		i = 1;
		if ((*ls)->type == 4)
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
				if ((!fg.r && (*ls)->next) || (fg.r && (*ls)->prev))
				{
					!fg.r ? (*ls) = (*ls)->next : ((*ls) = (*ls)->prev);
					continue ;
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
