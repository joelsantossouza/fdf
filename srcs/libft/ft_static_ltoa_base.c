/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_static_ltoa_base.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:57:29 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/13 15:58:56 by joesanto         ###   ########.fr       */
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

size_t	ft_static_ltoa_base(ssize_t nbr, char **sptr, const char *base)
{
	static char	buf[21];
	const char	*begin = buf + (nbr < 0);
	size_t		u_nbr;
	size_t		base_len;
	size_t		nbr_len;

	*sptr = 0;
	base_len = get_base(base);
	if (base_len < 2)
		return (0);
	nbr_len = ft_nbrlen(nbr, base_len);
	u_nbr = ft_abs(nbr);
	*sptr = buf + nbr_len;
	**sptr = 0;
	buf[0] = '-';
	while ((*sptr)-- > begin)
	{
		**sptr = base[u_nbr % base_len];
		u_nbr /= base_len;
	}
	*sptr = buf;
	return (nbr_len);
}
