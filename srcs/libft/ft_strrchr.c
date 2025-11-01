/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 09:29:05 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/14 08:42:41 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	const char	*ptr;
	char		find;

	ptr = 0;
	find = (char) c;
	if (s)
	{
		while (*s)
			if (*s++ == find)
				ptr = (s - 1);
		if (find == 0)
			ptr = s;
	}
	return ((char *) ptr);
}
