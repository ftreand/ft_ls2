/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fill_struct.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/08 16:38:38 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/17 19:05:31 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include <stdio.h>

void	ft_fill_struct(t_ls *ls, t_fill *fill)
{
	char *name;

	printf("ls->path = %s\n", ls->path);
	lstat(ls->path, &fill->stats);
	if ((fill->group = getgrgid(fill->stats.st_gid)) == NULL)
	{
		name = ft_itoa(fill->stats.st_gid);
		ls->gr_name = ft_strdup(name);
		free(name);
	}
	else
		ls->gr_name = ft_strdup(fill->group->gr_name);
	if ((fill->passwd = getpwuid(fill->stats.st_uid)) == NULL)
	{
		name = ft_itoa(fill->stats.st_uid);
		ls->pw_name = ft_strdup(name);
		free(name);
	}
	else
		ls->pw_name = ft_strdup(fill->passwd->pw_name);
	ls->type = fill->dirent->d_type;
	ls->mode = ft_recup_mode(fill->stats.st_mode);
	ls->link = fill->stats.st_nlink;
	ls->size = fill->stats.st_size;
	ls->time = fill->stats.st_mtime;
	ft_strcpy(ls->d_name, fill->dirent->d_name);
}
