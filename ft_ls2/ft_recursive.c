/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_recursive.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/07 17:21:16 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/03/19 20:03:37 by ftreand     ###    #+. /#+    ###.fr     */
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
//	t_ls	*padd;

	printf("lol d_name = %s\n", (*begin)->d_name); 
	while ((fill.dirent = readdir(dir)) != NULL)
	{
		if (!recu)
		{
			recu = (t_ls*)malloc(sizeof(t_ls));
			*begin = recu;
			recu->prev = NULL;
			recu->next = NULL;
			ft_recup_recu_path(recu->path, (*ls)->path, fill.dirent->d_name);
			printf("full path first  =%s\n", recu->path);
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
			printf("full path new  =%s\n", recu->path);
			ft_fill_struct(&(*recu), &fill);
			fg->total += fill.stats.st_blocks;
			ft_sort_list(&(*begin), recu, (*fg));
		}
	}

}

void	ft_recup_recu_path(char *ret, char *path, char *name)
{
	ft_strcpy(ret, path);
	ft_strcat(ret, "/");
	ft_strcat(ret, name);
}

void	ft_recursive(t_ls **ls, t_flags fg, char *path)
{
	t_ls	*begin;
	t_pad	*pad;
	t_ls	*padd;
	DIR *dir;

	begin = NULL;
	printf("ls d_name = %s\n", (*ls)->d_name);
	while (ls)
	{
		printf("ls type = %d\n", (*ls)->type);
		printf("ls name = %s\n", (*ls)->d_name);
		if ((*ls)->type == 4 && (*ls)->d_name[0] != '.')
		{
			fg.total = 0;
			dir = opendir((*ls)->d_name);
			ft_recup_recu_path((*ls)->path, path, (*ls)->d_name);
			printf("full path = %s\n", (*ls)->path);
			ft_fill_recursive_stats(&begin, &(*ls), dir, &fg);
			begin = begin->next;
			printf("begin d_name = %s\n", begin->d_name);
			padd = begin;
			pad = ft_padding(&padd, ft_strlen);
			ft_display(begin, &fg, pad);
			printf("fucking d_name = %s\n", begin->d_name);
//			begin = NULL;
			closedir(dir);
//			ft_recursive(&begin, fg, (*ls)->d_name);
		}
		(*ls) = (*ls)->next;
	}
}
