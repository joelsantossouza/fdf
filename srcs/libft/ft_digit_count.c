/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digit_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:22:41 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/11 09:19:31 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>

size_t	ft_digit_count(ssize_t nbr, unsigned int base)
{
	size_t	len;

	if (base < 2)
		return (0);
	len = 1;
	while (nbr / base)
	{
		nbr /= base;
		len++;
	}
	return (len);
}
