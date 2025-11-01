/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:25:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/07 15:41:58 by joesanto         ###   ########.fr       */
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
	t_list	*list;
	void	(*fun)(void *);
}	t_input;

t_list	*init_list(void	**tab, size_t size)
{
	t_list	*list;
	t_list	*new;

	list = 0;
	while (size--)
	{
		new = ft_lstnew(tab[size]);
		if (!new)
			continue ;
		ft_lstadd_front(&list, new);
	}
	return (list);
}

void	test(t_input tab[], size_t size)
{
	char	*color;

	while (size--)
	{
		ft_lstclear(&tab[size].list, tab[size].fun);
		color = !tab[size].list ? GREEN : RED;

		printf("%s", color);
		printf("List Now is NULL: %s\n", !tab[size].list ? "YES" : "NO");
		printf("%s", RESET);
	}
}

int	main(void)
{
	printf("--- For this test please use Valgrind! ---\n\n");
	
	int	nbr1;
	int	nbr2;

	t_list	*node1 = ft_lstnew("This is a test");
	t_list	*node2 = ft_lstnew(&nbr1);
	t_list	*node3 = ft_lstnew(&nbr2);
	char	*str = malloc(1000);

	void	*tab1[] = {"joel", "is", "a", "programmer", &nbr1, &nbr2};
	void	*tab2[] = {node1, node2, node3, str};

	t_list	*list1 = init_list(tab1, sizeof(tab1) / sizeof(*tab1));
	t_list	*list2 = init_list(tab2, sizeof(tab2) / sizeof(*tab2));

	t_input	test00[] = {
		{0, 0},
		{0, free},
		{list1, 0},
		{list2, free},
	};

	test(test00, NELEM(test00));
	return (0);
}
