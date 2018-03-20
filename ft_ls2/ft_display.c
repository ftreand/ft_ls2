/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_display.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/06 15:43:15 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/03/08 15:43:56 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include <stdio.h>

void	ft_display_l(t_ls *ls, t_pad *pad)
{
	ft_putstr(ls->mode);
	ft_putchar(' ');
	(ft_num_len(ls->link) < pad->lk) ? ft_pad(pad->lk - ft_num_len(ls->link) + 1) : ft_putchar(' ');
	ft_putnbr(ls->link);
	ft_putchar(' ');
	ft_putstr(ls->pw_name);
	ft_strlen(ls->pw_name) < pad->pw ? ft_pad(pad->pw - ft_strlen(ls->pw_name) + 2) : ft_putstr("  ");
	ft_putstr(ls->gr_name);
	ft_strlen(ls->gr_name) < pad->gr ? ft_pad(pad->gr - ft_strlen(ls->gr_name) + 1) : ft_putchar(' ');
	ft_num_len(ls->size) < pad->size ? ft_pad(pad->size - ft_num_len(ls->size) + 1) : ft_putchar(' ');
	ft_putnbr(ls->size);
	ft_putchar(' ');
	ft_display_time(ls->time);
	ft_putchar(' ');
}

void	ft_display_norm(t_ls *ls, t_flags *fg, t_pad *pad)
{
	if (fg->l)
	{
		ft_putstr("total ");
		ft_putendl(ft_itoa(fg->total));
	}
	while (ls != NULL)
	{
		if (!fg->a)
		{
			while (ls->d_name[0] == '.')
				ls = ls->next;
		}
		if (fg->l)
			ft_display_l(ls, pad);
		ft_putendl(ls->d_name);
		ls = ls->next;
	}
}

void	ft_display_reverse(t_ls *ls, t_flags *fg, t_pad *pad)
{
	if (fg->l)
	{
		ft_putstr("total ");
		ft_putendl(ft_itoa(fg->total));
	}
	while (ls)
	{
		if (!fg->a && ls->d_name[0] == '.')
			ls = ls->prev;
		else
		{
			if (fg->l)
				ft_display_l(ls, pad);
			ft_putendl(ls->d_name);
			ls = ls->prev;
		}
	}
}


void	ft_display(t_ls *ls, t_flags *fg, t_pad *pad)
{
	if (fg->r)
	{
		while (ls->next)
			ls = ls->next;
		ft_display_reverse(ls, fg, pad);
	}
	else
		ft_display_norm(ls, fg, pad);
}