/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_recup_info.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 19:04:02 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/05 18:54:38 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include <stdio.h>
#include <errno.h>

void	ft_putspace(char *av, size_t j)
{
	size_t i;

	i = ft_strlen(av);
	if (i < j)
	{
		while (i++ < j)
			ft_putchar(' ');
	}
}

int		ft_recup_len_max(char **av, int start)
{
	size_t	i;
	DIR		*dir;

	i = 0;
	while (start++ < ft_tablen(av))
	{
		errno = 0;
		dir = opendir(av[start]);
		if (errno == 20)
			i = ft_strlen(av[start]) > i ? (ft_strlen(av[start]) + 1) : i;
	}
	return (i);
}

void	ft_display_wrong_dir(char **av, t_flags fg)
{
	ft_errno_2(av, fg.start);
	ft_errno_20(av, fg.start, fg);
//	ft_errno_13(av, fg.start);
}

void	ft_sort_av(char **av, char *(dup)(const char *s), int *i, t_flags fg)
{
	int		j;
	char	*tmp;

	while (fg.start < ft_tablen(av))
	{
		j = fg.start;
		while (av[j])
		{
			if (((ft_strcmp(av[fg.start], av[j])) < 0) && fg.r)
			{
				tmp = (dup)(av[fg.start]);
				av[fg.start] = (dup)(av[j]);
				av[j] = (dup)(tmp);
			}
			else if ((ft_strcmp(av[fg.start], av[j]) > 0) && !fg.r)
			{
				tmp = (dup)(av[fg.start]);
				av[fg.start] = (dup)(av[j]);
				av[j] = (dup)(tmp);
			}
			j++;
		}
		fg.start++;
		*i += 1;
	}
}

int		ft_recup_start(char **av)
{
	int i;

	i = 1;
	while (av[i] && av[i][0] == '-')
	{
		if (!av[i][1])
			break ;
		if (av[i][1] == '-')
		{
			if (av[i][2])
			{
				ft_error_flag(av[i][1]);
			}
			i++;
			break ;
		}
		i++;
	}
	return (i);
}
