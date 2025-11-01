/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:09:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/08 11:09:17 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <atf-c.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

#define RED			"\e[0;31m"
#define GREEN		"\e[0;32m"
#define RESET_COLOR	"\e[0m"
#define NELEM(tab) (sizeof(tab) / sizeof(t_list *))
#define TEST_NULLS	1<<0

int file;

void	putstr(void *p)
{
	char	*str = p;

	if (!str)
		return (putstr("(nil)"));
	while (*str)
		write(file, str++, 1);
}

void    print_list(t_list *begin)                                                              
{                                                                                              
	while (begin)                                                                          
	{                                                                                      
		printf("%s%s", (char *) begin->content, !begin->next ? "" : ", ");                      
		begin = begin->next;                                                           
	}                                                                                      
	printf("\n");                                                                          
}

int	init_vars(t_list *list, char **expected_dst, char **output_dst, size_t *len)
{
	t_list	*ptr;
	char	*copy;

	ptr = list;
	*len = 0;
	while (ptr)
	{
		*len += ft_strlen(ptr->content);
		ptr = ptr->next;
	}
	*expected_dst = malloc(*len);
	if (!*expected_dst)
		return (0);
	*output_dst = malloc(*len);
	if (!*output_dst)
	{
		free(*expected_dst);
		return (0);
	}
	ptr = list;
	copy = *expected_dst;
	while (ptr)
	{
		copy = ft_stpcpy(copy, ptr->content);
		ptr = ptr->next;
	}
	return (1);
}

void	test(t_list *tab[], int size)
{
	char	*output_dst;
	char	*expected_dst;
	char	*color;
	size_t	len;
	char	template[] = "/home/joel/coding/exercises/libft/.tests/XXXXXX";

	file = mkstemp(template);
	if (file < 0)
		return ;
	while (size--)
	{
		if (!init_vars(tab[size], &expected_dst, &output_dst, &len))
			continue ;
		ft_lstiter(tab[size], putstr);
		lseek(file, -len, SEEK_CUR);
		read(file, output_dst, len);

		color = !ft_strncmp(expected_dst, output_dst, len) ? GREEN : RED;

		printf("%s", color);
		printf("Input:   \t"); print_list(tab[size]);
		printf("Expected:\t%.*s\n", (int) len, expected_dst);
		printf("Output:  \t%.*s\n", (int) len, output_dst);
		printf("%s", RESET_COLOR);
		
		ATF_CHECK(!ft_strncmp(expected_dst, output_dst, len));
		printf("----------\n");

		free(output_dst);
	}
	unlink(template);
}

t_list  *init_list(char *head, ...)
{
	t_list  *list;
	t_list  *new;                                                                                                                                                                         
	va_list args;                          
	void    *value;                        

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
	atf_tc_set_md_var(tc, "descr", "Testing linked list functions");
}
ATF_TC_BODY(test00, tc)
{
	t_list  *lst1 = init_list("lst1", "This", "is", "a", "big", "test", "now", 0);
	t_list  *lst2 = init_list("lst1", "This", "is", "a", "b", 0);
	t_list  *lst3 = init_list("lst1", "a", "big", "test", 0);
	t_list  *lst4 = init_list("lst1", 0);

	t_list	*tab[] = {
		0,
		lst1,
		lst2,
		lst3,
		lst4,
	};

	test(tab, NELEM(tab));
}

// TEST PROGRAM
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);

	return (atf_no_error());
}
