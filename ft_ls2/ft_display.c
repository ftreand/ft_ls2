/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_display.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/06 15:43:15 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/03/06 17:29:56 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	ft_display_reverse(t_ls *ls, t_flags fg, t_pad *pad)
{
	(void)pad;
	(void)fg;
	while (ls->prev != NULL)
	{
		if (!fg.a)
		{
		while (ls->d_name[0] == '.')
			ls = ls->prev;
		}
		ft_putendl(ls->d_name);
		ls = ls->prev;
	}
	if (fg.a && ls->d_name[0] == '.')
		ft_putendl(ls->d_name);
}


void	ft_display(t_ls *ls, t_flags fg, t_pad *pad)
{
	if (fg.r)
	{
		while (ls->next)
			ls = ls->next;
		ft_display_reverse(ls, fg, pad);
	}
}
