/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:00:46 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/11 09:48:23 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen(ssize_t nbr, unsigned int base)
{
	size_t	len;

	if (base < 2)
		return (0);
	len = 1 + (nbr < 0);
	while (nbr / base)
	{
		nbr /= base;
		len++;
	}
	return (len);
}
