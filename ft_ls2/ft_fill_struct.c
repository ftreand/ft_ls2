/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fill_struct.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/08 16:38:38 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 17:35:28 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include <stdio.h>


void	ft_fill_gr(t_fill *fill, t_ls *ls)
{
	char *name;

	name = ft_itoa(fill->stats.st_uid);
	ls->pw_name = ft_strdup(name);
	free(name);
}

void	ft_fill_pw(t_fill *fill, t_ls *ls)
{
	char *name;

	name = ft_itoa(fill->stats.st_uid);
	ls->pw_name = ft_strdup(name);
	free(name);
}

void	ft_recup_link(t_ls *ls, char *s)
{
	readlink(ls->path, ls->lk, 4096);
	ft_strcpy(ls->d_name, s);

}

void	ft_fill_struct(t_ls *ls, t_fill *fill)
{
	lstat(ls->path, &(fill->stats));
	if ((fill->group = getgrgid(fill->stats.st_gid)) == NULL)
		ft_fill_gr(fill, ls);
	else
		ls->gr_name = ft_strdup(fill->group->gr_name);
	if ((fill->passwd = getpwuid(fill->stats.st_uid)) == NULL)
		ft_fill_pw(fill, ls);
	else
		ls->pw_name = ft_strdup(fill->passwd->pw_name);
	ls->type = fill->dirent->d_type;
	ls->node = fill->stats.st_ino;
	ls->block = (int)fill->stats.st_blocks;
	ls->mode = ft_recup_mode(fill->stats.st_mode);
	ls->link = fill->stats.st_nlink;
	ls->size = fill->stats.st_size;
	ls->time = fill->stats.st_mtime;
	ls->mode[0] == 'l' ? ft_recup_link(ls, fill->dirent->d_name) :
			ft_strcpy(ls->d_name, fill->dirent->d_name);
}
