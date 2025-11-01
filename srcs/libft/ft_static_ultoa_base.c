/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_static_ultoa_base.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:57:29 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/13 15:58:40 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_base(const char *base)
{
	const char	*p;

	if (!base)
		return (0);
	p = base - 1;
	while (*++p)
		if (*p == '+' || *p == '-' || ft_isspace(*p) || ft_strchr(p + 1, *p))
			return (0);
	return (p - base);
}

size_t	ft_static_ultoa_base(size_t nbr, char **sptr, const char *base)
{
	static char	buf[21];
	size_t		base_len;
	size_t		nbr_len;

	*sptr = 0;
	base_len = get_base(base);
	if (base_len < 2)
		return (0);
	nbr_len = ft_udigit_count(nbr, base_len);
	*sptr = buf + nbr_len;
	**sptr = 0;
	while ((*sptr)-- > buf)
	{
		**sptr = base[nbr % base_len];
		nbr /= base_len;
	}
	*sptr = buf;
	return (nbr_len);
}
