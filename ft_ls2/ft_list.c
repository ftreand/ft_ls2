/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_list.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 15:36:40 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/29 16:21:03 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include <stdio.h>

void	ft_list_first(t_ls **ls, t_ls ***begin)
{
	ls = (t_ls**)malloc(sizeof(t_ls));
	(*begin) = ls;
	(*ls)->prev = NULL;
	(*ls)->next = NULL;
}

void	ft_list_next(t_ls *now, t_ls *ls)
{
	now = (t_ls*)malloc(sizeof(t_ls));
	ls = now;
	ls->next = NULL;
	ls->prev = NULL;
}

