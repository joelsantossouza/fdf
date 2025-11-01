/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:48:52 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/01 20:57:01 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define ERROR		-1
# define SUCCESS	0

# define DEC_BASE	"0123456789"

typedef struct s_map
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	total;
	unsigned int	*color;	
	int				*altitude;	
}	t_map;

#endif
