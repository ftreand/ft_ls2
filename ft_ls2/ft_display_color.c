/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_display_color.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/26 11:28:55 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/26 16:52:21 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include <stdio.h>

void	ft_print_green_bg(char *s)
{
	ft_putstr("\033[30;42m");
	ft_putstr(s);
	ft_putstr("\033[0m");
	ft_putchar('\n');
}

void	ft_print_green(char *s)
{
	ft_putstr("\033[0;31m");
	ft_putendl(s);
	ft_putstr("\033[0m");
}

void	ft_print_blue_yellow_bg(char *s)
{
	ft_putstr("\033[34;43");
	ft_putstr(s);
	ft_putstr("\033[0m");
	ft_putchar('\n');
}

void	ft_display_color(t_flags *fg, char *s, char *mode, char *lk)
{
	(void)fg;
//	printf("mode = %s\n", mode);
//	printf("name = %s\n", s);
	if (mode[0] == 'd' && mode[9] != 't')
	{
		ft_putstr("\033[1;36m");
		ft_putendl(s);
		ft_putstr("\033[0m");
	}
	else if (mode[0] == '-' && mode[9] == 'x')
	{
		ft_putstr("\033[0;31m");
		ft_putendl(s);
		ft_putstr("\033[0m");
	}
	else if (mode[0] == 's')
	{
		ft_putstr("\033[0;32m");
		ft_putendl(s);
		ft_putstr("\033[0m");
	}
	else if (mode [0] == 'l')
	{
		ft_putstr("\033[0;35m");
		fg->l ? ft_putstr(s) : ft_putendl(s);
		ft_putstr("\033[0m");
		if (fg->l)
		{
			ft_putstr(" -> ");
			ft_putendl(lk);
		}
	}
//	else if (mode[0] == 'c')
//		ft_print_blue_yellow_bg(s);
	else if (mode[0] == 's')
		ft_print_green(s);
	else if (mode[9] == 't')
		ft_print_green_bg(s);
	else
		ft_putendl(s);
}
