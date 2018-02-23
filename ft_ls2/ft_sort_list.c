/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sort_list.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/23 12:29:22 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/02/23 14:56:00 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	ft_sort_list(t_ls **ls, t_flags fg)
{
	t_ls *tmp;
	t_ls *tmp1;

//	while(tmp)
//	{
//		printf("d_name tmp = %s\n", tmp->d_name);
//		tmp = tmp->next;
//	}
//	while (ls)
//	{
//		printf("d_name ls = %s\n", ls->d_name);
//		ls = ls->next;
//	}
	(void)fg;
//	if (fg.t)
//		ft_sort_time_list(ls);
//	else if (fg.r && !fg.t)
//		ft_sort_reverse_list(ls);
//	else
//	{
		while ((*ls)->next != NULL)
		{
			tmp = (*ls)->next;
			while (tmp->next != NULL)
			{
				if (ft_strcmp((*ls)->d_name, tmp->d_name ) > 0)
				{
					tmp1 = *ls;
					(*ls)->prev = tmp;
					(*ls)->prev->next = tmp1;
				}
				tmp =tmp->next;
			}
			tmp = tmp->next;
		}
//	}
}
