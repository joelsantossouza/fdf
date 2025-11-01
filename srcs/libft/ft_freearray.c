/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freearray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:25:25 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/03 09:28:36 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_freearray(void **array, void (*free_memb)(void *))
{
	void	**parray;

	if (!array)
		return ;
	parray = array;
	while (*parray)
	{
		free_memb(*parray);
		*parray++ = 0;
	}
	free(array);
}
