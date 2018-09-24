/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sort_list.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/23 12:29:22 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/24 12:50:57 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include "includes/ft_ls.h"

void	ft_add_before(t_ls *ls, t_ls *now)
{
	t_ls *tmp;

	if (now->prev != NULL)
	{
		tmp = now->prev;
		now->prev = ls;
		tmp->next = ls;
		ls->prev = tmp;
		ls->next = now;
	}
	else
	{
		now->prev = ls;
		ls->next = now;
		ls->prev = NULL;
	}
}

void	ft_add_after(t_ls *ls, t_ls *now)
{
	now->next = ls;
	ls->prev = now;
	ls->next = NULL;
}

void	ft_sort_list(t_ls **begin, t_ls *ls, t_flags fg)
{
	t_ls *now;

	now = (*begin);
	if (!fg.t)
	{
		while (ft_strcmp(now->d_name, ls->d_name) < 0 && now->next)
			now = now->next;
		ft_strcmp(now->d_name, ls->d_name) > 0 ?
			ft_add_before(ls, now) : ft_add_after(ls, now);
	}
	else
	{
		while ((now->time - ls->time >= 0) && now->next)
			now = now->next;
		if (now->time - ls->time == 0)
			ft_strcmp(now->d_name, ls->d_name) > 0 ? ft_add_before(ls, now) :
				ft_add_after(ls, now);
		else
			(now->time - ls->time > 0) ? ft_add_after(ls, now) :
			ft_add_before(ls, now);
	}
	while (now->prev)
		now = now->prev;
	(*begin) = now;
}
