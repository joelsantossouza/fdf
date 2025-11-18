/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:13:17 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/18 19:25:09 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void	free_img(t_img *img, void (*free_struct)(void *))
{
	free(img->data);
	*img = (t_img){};
	if (free_struct)
		free_struct(img);
}
