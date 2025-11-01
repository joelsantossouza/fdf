/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrnul_diff.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 22:50:59 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/02 12:31:27 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchrnul_diff(const char *s, int c)
{
	char	find;

	find = (char) c;
	if (s)
		while (*s)
			if (*s++ != find)
				return ((char *)(s - 1));
	return ((char *) s);
}
