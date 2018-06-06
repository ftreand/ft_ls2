/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_recup_stats.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/14 15:27:10 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/06 17:35:14 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include <stdio.h>

char	*ft_recup_mode(mode_t st_mode)
{
	char str[11];
	char *res;

	str[0] = (st_mode & S_IFMT) == S_IFIFO ? 'p' : str[0];
	str[0] = (st_mode & S_IFMT) == S_IFCHR ? 'c' : str[0];
	str[0] = (st_mode & S_IFMT) == S_IFDIR ? 'd' : str[0];
	str[0] = (st_mode & S_IFMT) == S_IFBLK ? 'b' : str[0];
	str[0] = (st_mode & S_IFMT) == S_IFREG ? '-' : str[0];
	str[0] = (st_mode & S_IFMT) == S_IFLNK ? 'l' : str[0];
	str[0] = (st_mode & S_IFMT) == S_IFSOCK ? 's' : str[0];
	str[1] = st_mode & S_IRUSR ? 'r' : '-';
	str[2] = st_mode & S_IWUSR ? 'w' : '-';
	str[3] = st_mode & S_IXUSR ? 'x' : '-';
	str[4] = st_mode & S_IRGRP ? 'r' : '-';
	str[5] = st_mode & S_IWGRP ? 'w' : '-';
	str[6] = st_mode & S_IXGRP ? 'x' : '-';
	str[7] = st_mode & S_IROTH ? 'r' : '-';
	str[8] = st_mode & S_IWOTH ? 'w' : '-';
	str[9] = st_mode & S_IXOTH ? 'x' : '-';
	str[10] = '\0';
	res = ft_strdup(str);
	return (res);
}

void	ft_recup_full_path(char *path, char *av, struct dirent *dirent)
{
	if (!av || !ft_strcmp(av, dirent->d_name))
	{
		ft_strcpy(path, ".");
		ft_strcat(path, "/");
		ft_strcat(path, dirent->d_name);
	}
	else
	{
		ft_strcpy(path, av);
		ft_strcat(path, "/");
		ft_strcat(path, dirent->d_name);
	}
}

void	ft_fill_stats(DIR *dir, char *av, t_ls **begin, t_flags *fg)
{
	t_fill	fill;
	t_ls	*ls;
	t_ls	*now;

	fg->total = 0;
	while ((fill.dirent = readdir(dir)) != NULL)
	{
		if (!ls)
		{
			ls = (t_ls*)malloc(sizeof(t_ls));
			(*begin) = ls;
			ls->prev = NULL;
			ls->next = NULL;
			ft_recup_full_path(ls->path, av, fill.dirent);
			ft_fill_struct(&(*ls), &fill);
			(!fg->a) && ls->d_name[0] == '.' ? fg->total :
				(fg->total = fill.stats.st_blocks);
		}
		else
		{
			now = (t_ls*)malloc(sizeof(t_ls));;
			ls = now;
			ls->next = NULL;
			ls->prev = NULL;
			ft_recup_full_path(ls->path, av, fill.dirent);
			ft_fill_struct(&(*ls), &fill);
			(!fg->a) && ls->d_name[0] == '.' ? (fg->total += 0) :
				(fg->total += fill.stats.st_blocks);
			ft_sort_list(&(*begin), ls, (*fg));
		}
	}
}

void	ft_pad(int i)
{
	while (i)
	{
		ft_putchar(' ');
		i--;
	}
}

void	ft_recup_stats(char **av, t_flags fg)
{
	t_ls	*ls;
	DIR		*dir;
//	int i = 0;
	int nb_arg;
	t_pad	*pad;
	t_ls	*padd;

	printf("l = %i\n", fg.l);
	printf("R = %i\n", fg.ur);
	printf("a = %i\n", fg.a);
	printf("r = %i\n", fg.r);
	printf("t = %i\n", fg.t);
	ls = NULL;
	nb_arg = 0;
	fg.total = 0;
	ft_sort_av(av, ft_strdup, &nb_arg, fg);
	printf("start = %d\n", fg.start);
	ft_display_wrong_dir(av, fg);
	if (nb_arg == 0)
	{
		dir = opendir(".");
		ft_fill_stats(dir, av[fg.start], &ls, &fg);
		padd = ls;
		pad = ft_padding(&padd);
		ft_display(ls, &fg, pad);
		if (fg.ur)
			ft_recursive(&ls, fg, ".");
		closedir(dir);
	}
	if (nb_arg >= 1)
	{
		while (fg.start < ft_tablen(av))
		{
			while (!(dir = opendir(av[fg.start])) && fg.start < ft_tablen(av))
				fg.start++;
			if (!av[fg.start])
				break ;
			if (dir)
			{
				ft_fill_stats(dir, av[fg.start], &ls, &fg);
				padd = ls;
				if (!fg.a)
				{
					while (padd->d_name[0] == '.' && padd->next)
						padd = padd->next;
				}
				pad = ft_padding(&padd);
				if (nb_arg > 1)
				{
					ft_putchar('\n');
					ft_putstr(av[fg.start]);
					ft_putendl(": ");
				}
				ft_display(ls, &fg, pad);
				if (fg.ur)
					ft_recursive(&ls, fg, av[fg.start]);
//				if (++i != nb_arg && nb_arg != 1)
//					ft_putchar('\n');
				closedir(dir);
				fg.start++;
			}
		}
		fg.start = ft_recup_start(av);
		ft_errno_13(av, fg.start);
	}
}
