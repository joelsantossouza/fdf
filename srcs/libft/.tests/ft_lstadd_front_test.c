/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:25:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/07 16:28:00 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <atf-c.h>

#define RED		"\e[0;31m"
#define GREEN	"\e[0;32m"
#define RESET	"\e[0m"
#define NELEM(tab) (sizeof(tab) / sizeof(void *))

t_list	*init_list(void *tab[], size_t size)
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

int	lst_cmp(void *tab[], t_list *list, size_t size)
{
	if (!tab && !list)
		return (0);
	if (!tab != !list)
		return (1);
	while (size-- > 1 && *tab == list->content)
	{
		tab++;
		list = list->next;
	}
	return (*tab - list->content);
}

void	print_pointers(void	**tab, size_t size, int rev)
{
	if (!rev)
		while (size--)
			printf("%p%s", tab[size], !size ? "" : ", ");
	else
		while (size--)
			printf("%p%s", *tab++, !size ? "" : ", ");
	printf("\n");
}

void	print_list(t_list *begin)
{
	while (begin)
	{
		printf("%p%s", begin->content, !begin->next ? "" : ", ");
		begin = begin->next;
	}
	printf("\n");
}

void	test(void *tab[], size_t size)
{
	t_list	*output;

	char	*color;

	while (size--)
	{
		output = init_list(tab, size);
		color = (!size && !output) || !lst_cmp(tab, output, size) ? GREEN : RED;

		printf("%s", color);
		printf("Input:   \t"); print_pointers(tab, size, 0);
		printf("Expected:\t"); print_pointers(tab, size, 1);
		printf("Output:  \t"); print_list(output);
		printf("%s", RESET);

		ATF_CHECK((!size && !output) || !lst_cmp(tab, output, size));
		printf("----------\n");

		ft_lstclear(&output, 0);
	}
}

ATF_TC(test00);
ATF_TC_HEAD(test00, tc)
{
	atf_tc_set_md_var(tc, "descr", "Testing some inputs in creation of a node of a linked list");
}
ATF_TC_BODY(test00, tc)
{
	char	*str = "This is a test";
	int		nbr = 42;
	char	chr = 'Z';
	t_list	*node = ft_lstnew(str);

	void	*tab[] = {
		0,
		str,
		&nbr,
		&chr,
		node,
	};

	test(tab, NELEM(tab));
}
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);

	return (atf_no_error());
}
