/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:56:46 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/18 16:38:17 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void	free_pic(t_pic *pic, void (*free_struct)(void *))
{
	free(pic->data);
	pic->width = 0;
	pic->height = 0;
	pic->data = 0;
	if (free_struct)
		free_struct(pic);
}
