/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:25:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/07 14:50:37 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

#define TEST_NULL	1<<0
#define NELEM(tab) (sizeof(tab) / sizeof(t_input))
#define RED		"\e[0;31m"
#define GREEN	"\e[0;32m"
#define RESET	"\e[0m"

typedef struct s_input
{
	t_list	*node;
	void	(*fun)(void *);
}	t_input;

void	test(t_input tab[], size_t size)
{
	while (size--)
		ft_lstdelone(tab[size].node, tab[size].fun);
}

int	main(void)
{
	printf("--- For this test please use Valgrind! ---\n\n");

	t_list	*node1 = ft_lstnew("This is a test");
	t_list	*tmp = ft_lstnew("tmp");
	t_list	*node2 = ft_lstnew(tmp);

	t_input	test00[] = {
		{0, 0},
		{0, free},
		{node1, 0},
		{node2, free},
	};

	test(test00, NELEM(test00));
	return (0);
}
