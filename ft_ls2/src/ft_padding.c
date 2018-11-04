/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_padding.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/21 15:03:58 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 14:49:48 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <stdio.h>

void	ft_padding_1(t_pad *pad)
{
	pad->lk = 1;
	pad->pw = 1;
	pad->gr = 1;
	pad->size = 1;
	pad->name = 1;
}

void	ft_fill_pad(t_pad *pad, t_ls **ls, size_t (len)(const char *s))
{
	pad->lk = ft_num_len((*ls)->link) > pad->lk ? ft_num_len((*ls)->link)
		: pad->lk;
	pad->pw = (len)((*ls)->pw_name) > pad->pw ? (len)((*ls)->pw_name)
		: pad->pw;
	pad->gr = (len)((*ls)->gr_name) > pad->gr ? (len)((*ls)->gr_name)
		: pad->gr;
	pad->size = ft_num_len((*ls)->size) > pad->size ?
		ft_num_len((*ls)->size) : pad->size;
	pad->name = (len)((*ls)->d_name) > pad->name ? (len)((*ls)->d_name)
		: pad->name;
	pad->in = ft_num_len((*ls)->node) > pad->in ? ft_num_len((*ls)->node) :
		pad->in;
	pad->blk = ft_num_len((*ls)->block) > pad->blk ? ft_num_len((*ls)->block) :
		pad->blk;
}

int		ft_num_len(int lk)
{
	int i;

	i = 0;
	if (!lk)
		return (1);
	while (lk)
	{
		lk /= 10;
		i++;
	}
	return (i);
}

t_pad	ft_padding(t_ls **ls)
{
	t_pad pad;

	pad.lk = 0;
	pad.pw = 0;
	pad.gr = 0;
	pad.in = 0;
	pad.size = 0;
	pad.name = 0;
	pad.blk = 0;
	while (*ls != NULL)
	{
		ft_fill_pad(&pad, ls, ft_strlen);
		*ls = (*ls)->next;
	}
	return (pad);
}
