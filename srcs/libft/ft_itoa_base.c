/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:23:30 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/10 16:54:46 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

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

char	*ft_itoa_base(int nbr, const char *base)
{
	unsigned int	u_nbr;
	unsigned int	is_neg;
	char			*str;
	size_t			base_len;
	size_t			nbr_len;

	base_len = get_base(base);
	if (base_len <= 1)
		return (0);
	is_neg = nbr < 0;
	nbr_len = ft_digit_count(nbr, base_len) + is_neg;
	str = (char *) malloc(sizeof(char) * (nbr_len + 1));
	if (!str)
		return (0);
	u_nbr = nbr;
	if (is_neg)
		u_nbr = -nbr;
	str[0] = '-';
	str[nbr_len] = 0;
	while (nbr_len-- > is_neg)
	{
		str[nbr_len] = base[u_nbr % base_len];
		u_nbr /= base_len;
	}
	return (str);
}
