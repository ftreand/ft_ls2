/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_display_color2.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/27 15:54:30 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 17:04:00 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	ft_print_bold_cyan(char *s)
{
	ft_putstr("\033[1;36m");
	ft_putendl(s);
	ft_putstr("\033[0m");
}

void	ft_print_exec_file(char *s)
{
	ft_putstr("\033[0;31m");
	ft_putendl(s);
	ft_putstr("\033[0m");
}

void	ft_print_socket(char *s)
{
	ft_putstr("\033[0;32m");
	ft_putendl(s);
	ft_putstr("\033[0m");
}
