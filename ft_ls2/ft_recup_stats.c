/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_recup_stats.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/14 15:27:10 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/03/19 18:34:36 by ftreand     ###    #+. /#+    ###.fr     */
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

void	ft_recup_full_path(char *path, char **av, struct dirent *dirent, int start)
{
	if (!av[start])
	{
		ft_strcpy(path, ".");
		ft_strcat(path, "/");
		ft_strcat(path, dirent->d_name);
	}
	else
	{
		ft_strcpy(path, av[start]);
		ft_strcat(path, "/");
		ft_strcat(path, dirent->d_name);
	}
}

void	ft_fill_stats(DIR *dir, int start, char **av, t_ls **begin, t_flags *fg)
{
	t_fill	fill;
	t_ls	*ls;
	t_ls	*now;
//	t_ls	*padd;

	//	pad = NULL;
	while ((fill.dirent = readdir(dir)) != NULL)
	{
		if (!ls)
		{
			ls = (t_ls*)malloc(sizeof(t_ls));
			(*begin) = ls;
			ls->prev = NULL;
			ls->next = NULL;
			ft_recup_full_path(ls->path, av, fill.dirent, start);
			ft_fill_struct(&(*ls), &fill);
			//		lstat(ls->path, &fill.stats);
			//		fill.group = getgrgid(fill.stats.st_gid);
			//		fill.passwd = getpwuid(fill.stats.st_uid);
			//		ls->type = fill.dirent->d_type;
			//		ls->mode = ft_recup_mode(fill.stats.st_mode);
			//		ls->link = fill.stats.st_nlink;
			//		ls->pw_name= ft_strdup(fill.passwd->pw_name);
			//		ls->gr_name = ft_strdup(fill.group->gr_name);
			//		ls->size = fill.stats.st_size;
			//		ls->time =fill.stats.st_mtime;
			//		ft_strcpy(ls->d_name, fill.dirent->d_name);
			//		printf("d_name = %s\n", ls->d_name);
			fg->total = fill.stats.st_blocks;
		}
		else
		{
			now = (t_ls*)malloc(sizeof(t_ls));;
			//		ls->next = now;
			//		now->prev = NULL;
			//		now->next = NULL;
			ls = now;
			ls->next = NULL;
			ls->prev = NULL;
			ft_recup_full_path(ls->path, av, fill.dirent, start);
			ft_fill_struct(&(*ls), &fill);
			//		lstat(ls->path, &fill.stats);
			//		fill.group = getgrgid(fill.stats.st_gid);
			//		fill.passwd = getpwuid(fill.stats.st_uid);
			//		ls->type = fill.dirent->d_type;
			//		ls->mode = ft_recup_mode(fill.stats.st_mode);
			//		ls->link = fill.stats.st_nlink;
			//		ls->pw_name= ft_strdup(fill.passwd->pw_name);
			//		ls->gr_name = ft_strdup(fill.group->gr_name);
			//		ls->size = fill.stats.st_size;
			//		ls->time = fill.stats.st_mtime;
			//		ft_strcpy(ls->d_name, fill.dirent->d_name);
			//		printf("d_name = %s\n", ls->d_name);
			fg->total += fill.stats.st_blocks;
			//(*pad) = ft_padding(ls, (*pad));
			//		ls->next = NULL;
			//		begin = !begin ? ls : begin;
			//		ls = ls->next;
			ft_sort_list(&(*begin), ls, (*fg)); // a faire
		}
	}
//	padd = *begin;
	//		while ((*begin)->next != NULL)
	//			{
	//				printf("name begin = %s\n", (*begin)->d_name);
	//				*begin = (*begin)->next;
	//				OK;
	//			}
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
}

void	ft_pad(int i)
{
	while (i)
	{
		ft_putchar(' ');
		i--;
	}
}

void	ft_display_time(long mtime)
{
	int i;
	int j;

	i = 4;
	j = 10;
	if (mtime <= time(NULL) - 15778800)
	{
		while (i < j)
			ft_putchar(ctime(&mtime)[i++]);
		ft_putstr("  ");
		i = 20;
		j = 24;
		while (i < j)
			ft_putchar(ctime(&mtime)[i++]);
	}
	else
	{
		j = 16;
		while (i < j)
		{
			ft_putchar(ctime(&mtime)[i++]);
		}
	}
}
/*
   void	ft_display(t_ls *ls, t_flags fg, t_pad *pad)
   {
//	t_ls	*reverse;

if (fg.r)
{
while (ls->next)
ls = ls->next;
}
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
SP;
ft_putstr(ls->gr_name);
ft_strlen(ls->gr_name) < pad->gr ? ft_pad(pad->gr - ft_strlen(ls->gr_name) + 1) : ft_putchar(' ');
ft_num_len(ls->size) < pad->size ? ft_pad(pad->size - ft_num_len(ls->size) + 1): ft_putchar(' ');
ft_putnbr(ls->size);
SP;
ft_display_time(ls->time);
SP;
}
ft_putstr(ls->d_name);
SP;
NL;
ls = ls->next;
}
free(ls);
free(pad);
}*/

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
	//	while (av[i])
	//	{
	//		printf("av = %s\n", av[i]);
	//		i++;
	//	}
	ft_display_wrong_dir(av, start);
	if (nb_arg == 0)
	{
		dir = opendir(".");
		ft_fill_stats(dir, start, av, &ls, &fg);
		padd = ls;
		pad = ft_padding(&padd, ft_strlen);

		//		ft_sort_list(&ls, fg);
		//		while (ls->next)
		//		{
		//			printf("d_name = %s\n", ls->d_name);
		//			ls = ls->next;
		//		}
		//	printf("lk = %d\n", pad->lk);
		//	printf("pw = %zu\n", pad->pw);
		//	printf("gr = %zu\n", pad->gr);
		//	printf("size = %d\n", pad->size);
		ft_display(ls, &fg, pad);
		if (fg.ur)
			ft_recursive(&ls, fg, ".");
		closedir(dir);

	}
	//	printf("start = %d\n", start);
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
				ft_fill_stats(dir, start, av, &ls, &fg);
				padd = ls;
				if (!fg.a)
				{
					while (padd->d_name[0] == '.')
						padd = padd->next;
				}
				pad = ft_padding(&padd, ft_strlen);
				if (nb_arg > 1)
				{
					ft_putstr(av[start]);
					ft_putendl(": ");
				}
				//				printf("lk = %d\n", pad->lk);
				//				printf("pw = %zu\n", pad->pw);
				//				printf("gr = %zu\n", pad->gr);
				//				printf("size = %d\n", pad->size);
				ft_display(ls, &fg, pad);
				if (++i != nb_arg && nb_arg != 1)
					ft_putchar('\n');
				if (fg.ur)
					ft_recursive(&ls, fg, av[i]);
				closedir(dir);
				start++;
			}
		}
	}
}
