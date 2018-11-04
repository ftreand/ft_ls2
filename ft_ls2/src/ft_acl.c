/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_acl.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/09 14:05:16 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 14:57:42 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_get_acl(char *s)
{
	acl_t acl;

	acl = acl_get_file(s, ACL_TYPE_EXTENDED);
	if (acl)
	{
		acl_free(acl);
		return (1);
	}
	return (0);
}

int		ft_get_xattr(char *s)
{
	char list[255];

	if ((listxattr(s, list, 255, XATTR_NOFOLLOW) && ft_strlen(list)))
		return (1);
	return (0);
}
