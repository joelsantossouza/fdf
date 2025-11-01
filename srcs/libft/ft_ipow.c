/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ipow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:44:15 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/10 20:47:47 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

double	ft_ipow(double base, size_t exponent)
{
	double	result;

	result = 1;
	while (exponent > 0)
	{
		if (exponent & 1)
			result *= base;
		base *= base;
		exponent >>= 1;
	}
	return (result);
}
