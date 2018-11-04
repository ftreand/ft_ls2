/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_display.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/06 15:43:15 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 14:50:51 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <stdio.h>

void	ft_display_time(long mtime)
{
	int	i;
	int	j;

	i = 4;
	j = 10;
	if (mtime <= time(NULL) - 15778800)
	{
		while (i < j)
			ft_putchar(ctime(&mtime)[i++]);
		ft_putstr("  ");
		i = 20;
		j = 24;
		while (i < j)
			ft_putchar(ctime(&mtime)[i++]);
	}
	else
	{
		j = 16;
		while (i < j)
			ft_putchar(ctime(&mtime)[i++]);
	}
}

void	ft_display_l(t_ls *ls, t_pad *pad)
{
	ft_putstr(ls->mode);
	(ft_num_len(ls->link) < pad->lk) ? ft_pad(pad->lk -
			ft_num_len(ls->link) + 1) : ft_putchar(' ');
	ft_putnbr(ls->link);
	ft_putchar(' ');
	ft_putstr(ls->pw_name);
	ft_strlen(ls->pw_name) < pad->pw ? ft_pad(pad->pw - ft_strlen(ls->pw_name)
			+ 2) : ft_putstr("  ");
	ft_putstr(ls->gr_name);
	ft_strlen(ls->gr_name) < pad->gr ? ft_pad(pad->gr - ft_strlen(ls->gr_name)
			+ 1) : ft_putchar(' ');
	if (ls->mode[0] == 'c' || ls->mode[0] == 'b' || ft_strstr(ls->path, "dev/"))
		ft_major_minor(ls);
	else
	{
		ft_num_len(ls->size) < pad->size ? ft_pad(pad->size -
				ft_num_len(ls->size) + 1) : ft_putchar(' ');
		ft_putnbr(ls->size);
	}
	ft_putchar(' ');
	ft_display_time(ls->time);
	ft_putchar(' ');
}

void	ft_display_norm(t_ls *ls, t_flags *fg, t_pad *pad)
{
	int i;

	i = 0;
	while (ls)
	{
		if (!fg->a && ls->d_name[0] == '.')
			ls = ls->next;
		else
		{
			if (!i && fg->l && !fg->one)
			{
				ft_putstr("total ");
				fg->k ? ft_putnbr(fg->total / 2) : ft_putnbr(fg->total);
				fg->total = 0;
				ft_putchar('\n');
				i = 1;
			}
			if (fg->in || fg->s)
				ft_print_node(ls->block, ls->node, pad, fg);
			if (fg->l && !fg->one)
				ft_display_l(ls, pad);
			ft_display_color(fg, ls->d_name, ls->mode, ls->lk);
			ls = ls->next;
		}
	}
}

void	ft_display_reverse(t_ls *ls, t_flags *fg, t_pad *pad)
{
	int i;

	i = 0;
	while (ls)
	{
		if (!fg->a && ls->d_name[0] == '.')
			ls = ls->prev;
		else
		{
			if (!i && fg->l && !fg->one)
			{
				ft_putstr("total ");
				fg->k ? ft_putnbr(fg->total / 2) : ft_putnbr(fg->total);
				fg->total = 0;
				ft_putchar('\n');
				i = 1;
			}
			if (fg->in)
				ft_print_node(ls->block, ls->node, pad, fg);
			if (fg->l && !fg->one)
				ft_display_l(ls, pad);
			ft_display_color(fg, ls->d_name, ls->mode, ls->lk);
			ls = ls->prev;
		}
	}
}

void	ft_display(t_ls *ls, t_flags *fg, t_pad *pad)
{
	t_ls *tmp;

	while (ls->prev)
		ls = ls->prev;
	tmp = ls;
	if (fg->r)
	{
		while (ls->next)
			ls = ls->next;
		ft_display_reverse(ls, fg, pad);
	}
	else
		ft_display_norm(ls, fg, pad);
	if (!fg->ur)
	{
		ls = tmp;
		ft_free_list(ls);
	}
}
