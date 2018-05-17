/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_error.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/03 17:15:58 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/17 19:28:14 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include "includes/libft.h"
#include <errno.h>
#include <stdio.h>

void	ft_display_l_file(char *file, t_flags fg, t_ls *ls)
{
	DIR		*dir;
	t_fill	fill;
	t_ls *now;
	t_ls *curr;

	(void)fg;
	(void)now;
	printf("file = %s\n", file);
	if (!ft_ocurences(file, '/'))
	{
		dir = opendir(".");
		while ((fill.dirent = readdir(dir)) != NULL)
		{
			if (!ft_strcmp(fill.dirent->d_name, file))
			{
				if (!ls)
				{
					curr = (t_ls*)malloc(sizeof(t_ls));
					curr->prev = NULL;
					curr->next = NULL;
					ft_recup_full_path(ls->path, file, fill.dirent);
					ft_fill_struct(ls, &fill);
				}
				else
				{
					
				}
			}
		}
	}
}

void	ft_errno_2(char **av, int start)
{
	DIR *dir;

	while (av[start])
	{
		errno = 0;
		dir = opendir(av[start]);
		if (errno == 2)
		{
			ft_putstr("ls: ");
			ft_putstr(av[start]);
			ft_putstr(": No such file or directory\n");
		}
		if (dir)
			closedir(dir);
		start++;
	}
}

void	ft_errno_20(char **av, int start, t_flags fg)
{
	DIR *dir;
	t_ls ls;

	while (av[start])
	{
		errno = 0;
		dir = opendir(av[start]);
		if (errno == 20 && !fg.l)
			ft_putendl(av[start]);
		else if (errno == 20 && fg.l)
			ft_display_l_file(av[start], fg, &ls);
		if (dir)
			closedir(dir);
		start++;
	}
}

void	ft_errno_13(char **av, int start)
{
	DIR *dir;

	while (av[start])
	{
		errno = 0;
		dir = opendir(av[start]);
		if (errno == 13)
		{
			ft_putchar('\n');
			ft_putstr(av[start]);
			ft_putstr(":\n");
			ft_putstr("ls: ");
			ft_putstr(av[start]);
			ft_putendl(" Permission denied");
		}
		if (dir)
			closedir(dir);
		start++;
	}
}
