/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sort_list.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/23 12:29:22 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/03/21 14:25:42 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include <stdio.h>

void	ft_add_before(t_ls *ls, t_ls *now)
{
	t_ls *tmp;

	//	printf("now d_name add before = %s\n", now->d_name);
	if (now->prev != NULL)
	{
		tmp = now->prev;
		now->prev = ls;
		tmp->next = ls;
		ls->prev = tmp;
		ls->next = now;

		//		printf("tmp name = %s\n", tmp->d_name);

	}
	else
	{
		now->prev = ls;
		ls->prev = NULL;
		ls->next = now;
	}
}

void	ft_add_after(t_ls *ls, t_ls *now)
{
	now->next = ls;
	ls->prev = now;
	ls->next = NULL;
}

void	ft_manage_begin(t_ls *now, t_ls **begin)
{
	while (now->prev)
		now = now->prev;
	begin = &now;
}

void	ft_sort_list(t_ls **begin, t_ls *ls, t_flags fg)
{
	t_ls *now;

	(void)fg;
	now = (*begin);
	if (!fg.t)
	{
		while (ft_strcmp(now->d_name, ls->d_name) < 0 && now->next)
			now = now->next;
		//	printf("now d_name after = %s\n", now->d_name);
		//	printf("ls d_name = %s\n", ls->d_name);
		//	printf("strcmp = %i\n", ft_strcmp(now->d_name, ls->d_name));
		ft_strcmp(now->d_name, ls->d_name) > 0 ? ft_add_before(ls, now) :
			ft_add_after(ls, &(*now));
	}
	else
	{
		while ((now->time - ls->time >= 0) && now->next)
			now = now->next;
//		printf("ls->d_name = %s\n", ls->d_name);
//		printf("now->d_name = %s\n", now->d_name);
//		printf("ls->time = %ld\n", ls->time);
//		printf("now->time = %ld\n", now->time);
//		printf("diff = %ld\n", now->time - ls->time);
		(now->time - ls->time >= 0) ? ft_add_after(ls, now) : ft_add_before(ls, now);
		//	ft_manage_begin(now, &(*begin));
		//	printf("begin d_name = %s\n", (*begin)->d_name);
	}
}

