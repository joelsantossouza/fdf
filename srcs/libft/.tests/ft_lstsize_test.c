/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:25:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/08 08:55:53 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdarg.h>
#include <atf-c.h>

#define RED		"\e[0;31m"
#define GREEN	"\e[0;32m"
#define RESET	"\e[0m"
#define NELEM(tab) (sizeof(tab) / sizeof(t_list *))

void    print_list(t_list *begin)                                                                                                                                                             
{                                                                                                                                                                                             
	while (begin)                                                                                                                                                                         
	{                                                                                                                                                                                     
		printf("%p%s", begin->content, !begin->next ? "" : ", ");                                                                                                                     
		begin = begin->next;                                                                                                                                                          
	}                                                                                                                                                                                     
	printf("\n");                                                                                                                                                                         
} 

int lstsize(t_list *lst)
{
    int count;
    
    count = 0;
    while (lst != NULL)
    {
        count++;
        lst = lst->next;
    }
    return (count);
}

void	test(t_list *tab[], size_t size)
{
	int		output;
	int		expected;
	char	*color;

	while (size--)
	{
		expected = lstsize(tab[size]);
		output = ft_lstsize(tab[size]);
		color = output == expected ? GREEN : RED;

		printf("%s", color);
		printf("Input:   \t"); print_list(tab[size]);
		printf("Expected:\t%d\n", expected);
		printf("Output:  \t%d\n", output);
		printf("%s", RESET);

		ATF_CHECK(output == expected);
		printf("----------\n");

		ft_lstclear(&tab[size], 0);
	}
}

t_list	*init_list(char *head, ...)
{
	t_list	*list;
	t_list	*new;
	va_list	args;
	void	*value;

	list = 0;
	va_start(args, head);
	value = va_arg(args, void *);
	while (value)
	{
		new = ft_lstnew(value);
		if (!new)
			continue ;
		ft_lstadd_front(&list, new);
		value = va_arg(args, void *);
	}
	va_end(args);
	return (list);
}

ATF_TC(test00);
ATF_TC_HEAD(test00, tc)
{
	atf_tc_set_md_var(tc, "descr", "Testing some inputs in creation of a node of a linked list");
}
ATF_TC_BODY(test00, tc)
{
	int	nbr1;
	int	nbr2;

	t_list	*lst1 = init_list("lst1", "This", "is", "a", "big", "test", &nbr1, &nbr2, 0);
	t_list	*lst2 = init_list("lst1", "This", "is", "a", "b", 0);
	t_list	*lst3 = init_list("lst1", "a", "big", "test", &nbr1, &nbr2, 0);
	t_list	*lst4 = init_list("lst1", 0);

	t_list	*tab[] = {
		0,
		lst1,
		lst2,
		lst3,
		lst4,
	};

	test(tab, NELEM(tab));
}
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);

	return (atf_no_error());
}
