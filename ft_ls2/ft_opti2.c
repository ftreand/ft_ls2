/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_opti2.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/24 15:09:04 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/24 19:29:51 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include <stdio.h>

void	ft_fill(t_ls *ls, char *av, t_fill fill, t_flags *fg)
{
	ft_recup_full_path(ls->path, av, fill.dirent);
	ft_fill_struct(&(*ls), &fill);
	(!fg->a) && ls->d_name[0] == '.' ? fg->total :
		(fg->total += fill.stats.st_blocks);
}

void	ft_manage_begin(t_ls **begin)
{
	while ((*begin)->prev)
		(*begin) = (*begin)->prev;
}

void	ft_no_arg(char *av, t_ls *ls, t_flags fg)
{
	DIR		*dir;
	t_ls	*padd;
	t_pad	*pad;

	dir = opendir(".");
	ft_fill_stats(dir, av, &ls, &fg);
	padd = ls;
	pad = ft_padding(&padd);
	ft_display(ls, &fg, pad);
	if (fg.r)
		ft_manage_reverse(&ls);
	if (fg.ur)
		ft_recursive(&ls, fg, ".");
	closedir(dir);
}

void	ft_with_arg(DIR *dir, char *av, t_ls *ls, t_flags *fg)
{
	t_ls	*padd;
	t_pad	*pad;

	ft_fill_stats(dir, av, &ls, &(*fg));
	padd = ls;
	if (!fg->a)
		while (padd->d_name[0] == '.' && padd->next)
			padd = padd->next;
	pad = ft_padding(&padd);
	if (fg->nb_arg > 1)
	{
		!fg->i ? fg->i = 1 : ft_putchar('\n');
		ft_putstr(av);
		ft_putendl(": ");
	}
	ft_display(ls, &(*fg), pad);
	if (fg->r)
		ft_manage_reverse(&ls);
	if (fg->ur)
		ft_recursive(&ls, (*fg), av);
	closedir(dir);
	fg->start++;
}