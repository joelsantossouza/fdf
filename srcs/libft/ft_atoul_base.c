/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoul_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:23:30 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/11 10:04:15 by joesanto         ###   ########.fr       */
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

size_t	ft_atoul_base(const char *nptr, char **endptr, const char *base)
{
	size_t	base_len;
	char	*found;
	char	sign;
	size_t	n;

	n = 0;
	sign = 1;
	base_len = get_base(base);
	if (nptr && base_len > 1)
	{
		while (ft_isspace(*nptr))
			nptr++;
		if (*nptr == '-' || *nptr == '+')
			if (*nptr++ == '-')
				sign = -1;
		found = ft_memchr(base, *nptr, base_len);
		while (found)
		{
			n = n * base_len + (found - base);
			found = ft_memchr(base, *++nptr, base_len);
		}
	}
	if (endptr)
		*endptr = (char *) nptr;
	return (n * sign);
}
