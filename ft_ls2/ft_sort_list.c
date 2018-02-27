/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sort_list.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/23 12:29:22 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/02/27 16:33:26 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	ft_sort_list(t_ls ***begin, t_ls *ls, t_flags fg)
{
	t_ls **new;
	t_ls *tmp;

	tmp = NULL;
	(void)fg;
	new = *begin;
	printf("begin d_name = %s\n", (**begin)->d_name);
	printf("ls d_name = %s\n", ls->d_name);
	while ((*new)->next)
	{
	printf("new d_name = %s\n", (*new)->d_name);
		if (ft_strcmp((*new)->d_name, ls->d_name) > 0)
		{
			OK;
			tmp = (*new)->prev;
			OK;
			(*new)->prev = ls->prev;
			ls->prev = tmp;
			OK;
		}
		(*new) = (*new)->next;
	}
	while ((*new)->prev)
	{
		(*new) = (*new)->prev;
	}
	begin = &new;
//	while (begin)
//	{
//	printf("begin d_name = %s\n", (**begin)->d_name);
//	(*begin) = (*begin)->next;
//	}
}
