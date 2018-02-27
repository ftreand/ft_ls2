/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_recup_stats.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/14 15:27:10 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/02/27 16:32:34 by ftreand     ###    #+. /#+    ###.fr     */
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

char	*ft_recup_full_path(char **av, struct dirent *dirent, int start)
{
	char	*tmp;
	char	*tmp1;

	if (!av[start])
		return (dirent->d_name);
	tmp = av[start];
	tmp1 = ft_strjoin(ft_strjoin(tmp, "/"), dirent->d_name);
	return (tmp1);
}

void	ft_fill_stats(DIR *dir, int start, char **av, t_ls **begin, t_flags fg)
{
	t_fill	fill;
	t_ls	*ls;
	t_ls	*now;
	t_ls	*padd;

	//	pad = NULL;
	(void)fg;
	while ((fill.dirent = readdir(dir)) != NULL)
	{
		if (!ls)
		{
			ls = (t_ls*)malloc(sizeof(t_ls));
			(*begin) = ls;
			ls->prev = NULL;
			ls->next = NULL;
		}
		else
		{
			now = (t_ls*)malloc(sizeof(t_ls));;
			ls->next = now;
			now->prev = ls;
			now->next = NULL;
			ls = now;
		}
		ls->path = ft_recup_full_path(av, fill.dirent, start);
		lstat(ls->path, &fill.stats);
		fill.group = getgrgid(fill.stats.st_gid);
		fill.passwd = getpwuid(fill.stats.st_uid);
		ls->mode = ft_recup_mode(fill.stats.st_mode);
		ls->link = fill.stats.st_nlink;
		ls->pw_name= ft_strdup(fill.passwd->pw_name);
		ls->gr_name = ft_strdup(fill.group->gr_name);
		ls->size = fill.stats.st_size;
		ls->time = ft_strsub(ctime(&fill.stats.st_mtime), 4, 12);
		ft_strcpy(ls->d_name, fill.dirent->d_name);
		//		printf("d_name = %s\n", ls->d_name);
		ls->total += fill.stats.st_blocks;
		//		(*pad) = ft_padding(ls, (*pad));
		//		ls->next = NULL;
		//		begin = !begin ? ls : begin;
		//		ls = ls->next;
		ft_sort_list(&begin, ls, fg); // a faire
	}
	padd = *begin;
	//	while ((*begin)->next)
	//		{
	//			printf("name begin = %s\n", (*begin)->d_name);
	//			*begin = (*begin)->next;
	//			OK;
	//		}
	//	while (padd != NULL)
	//		{
	//			printf("name padd = %s\n", padd->d_name);
	//			padd = padd->next;
	//			OK;
	//		}

//	(*pad) = ft_padding(&padd, ft_strlen);
//	printf("lk = %d\n", (*pad)->lk);
//	printf("pw = %zu\n", (*pad)->pw);
//	printf("gr = %zu\n", (*pad)->gr);
//	printf("size = %d\n", (*pad)->size);
	OK;
	OK;
}

void	ft_pad(int i)
{
	while (i)
	{
		ft_putchar(' ');
		i--;
	}
}

void	ft_display(t_ls *ls, t_flags fg, t_pad *pad)
{
	if (!fg.a)
	{
		while (ls->d_name[0] == '.')
			ls = ls->next;
	}
	while (ls != NULL)
	{

		if (fg.l)
		{
			ft_putstr(ls->mode);
			ft_num_len(ls->link) < pad->lk ?
				ft_pad(pad->lk - (ft_num_len(ls->link)) + 1) : ft_putchar(' ');
			ft_putnbr(ls->link);
			ft_putchar(' ');
			ft_putstr(ls->pw_name);
			ft_strlen(ls->pw_name) < pad->pw ? ft_pad(pad->pw - ft_strlen(ls->pw_name) + 1) : ft_putchar(' ');
			ft_putstr(ls->gr_name);
			ft_strlen(ls->gr_name) < pad->gr ? ft_pad(pad->gr - ft_strlen(ls->gr_name) + 1) : ft_putchar(' ');
			ft_num_len(ls->size) < pad->size ? ft_pad(pad->size - ft_num_len(ls->size) + 1): ft_putchar(' ');
			ft_putnbr(ls->size);
			SP;
			ft_putstr(ls->time);
			SP;
		}
		ft_putstr(ls->d_name);
		SP;
		NL;
		ls = ls->next;
	}
}

void	ft_recup_stats(char **av, t_flags fg, int start)
{
	t_ls	*ls;
	DIR		*dir;
	int i = 0;
	//	int start;
	int nb_arg;
	t_pad	*pad;
	t_ls	*padd;

	ls = NULL;
	nb_arg = 0;
	//	start = ft_recup_start(av);
	ft_sort_av(av, ft_strdup, start, &nb_arg);
	printf("start = %d\n", start);
	while (av[i])
	{
		printf("av = %s\n", av[i]);
		i++;
	}
	ft_display_wrong_dir(av, start);
	printf("nb_arg = %d\n", nb_arg);
	if (nb_arg == 0)
	{
		dir = opendir(".");
		ft_fill_stats(dir, start, av, &ls, fg);
		padd = ls;
		pad = ft_padding(&padd, ft_strlen);
		printf("lk = %d\n", pad->lk);
		printf("pw = %zu\n", pad->pw);
		printf("gr = %zu\n", pad->gr);
		printf("size = %d\n", pad->size);
		OK;
//		ft_sort_list(&ls, fg);
//		while (ls->next)
//		{
//			printf("d_name = %s\n", ls->d_name);
//			ls = ls->next;
//		}
		closedir(dir);
		//	printf("lk = %d\n", pad->lk);
		//	printf("pw = %zu\n", pad->pw);
		//	printf("gr = %zu\n", pad->gr);
		//	printf("size = %d\n", pad->size);
		OK;
		ft_display(ls, fg, pad);
	}
	printf("start = %d\n", start);
	if (nb_arg >= 1)
	{
		while (start < ft_tablen(av))
		{
			while (!(dir = opendir(av[start])) && start < ft_tablen(av))
				start++;
			if (!av[start])
				break ;
			if (dir)
			{
				ft_fill_stats(dir, start, av, &ls, fg);
//				ft_sort_list(&ls, fg);
				ft_putstr(av[start]);
				NL;
				ft_display(ls, fg, pad);
				closedir(dir);
				start++;
			}
		}
	}
}
