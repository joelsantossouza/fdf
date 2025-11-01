/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:09:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/01 15:58:05 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <atf-c.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define RED			"\e[0;31m"
#define GREEN		"\e[0;32m"
#define RESET_COLOR	"\e[0m"
#define NELEM(tab) (sizeof(tab) / sizeof(t_input))
#define TEST_NULLS	1<<0

char	*test_titles[] = {
	"Alloc 0",
	"Alloc Regular Size",
	"Alloc Int overflow",
	"Force malloc error",
};
static int	i;

typedef struct s_input
{
	size_t	nmemb;
	size_t	size;
}	t_input;

void	ft_put_row(char *type, const char *buf, size_t size)
{
	printf("%s\t", type);
	if (!buf)
		printf("(null");
	else
		while (size--)
			printf("\\%02X", *buf++);
	printf("\n");
}

void	test(t_input tab[], int size)
{
	void	*output_dst;
	void	*expected_dst;
	char	*color;
	size_t	bytes;

	printf("\n<test%02d> %s\n", i, test_titles[i]);
	while (size--)
	{
		bytes = tab[size].nmemb * tab[size].size;

		expected_dst = calloc(tab[size].nmemb, tab[size].size);
		output_dst = ft_calloc(tab[size].nmemb, tab[size].size);
		color = !bytes || !ft_memcmp(output_dst, expected_dst, bytes) ? GREEN : RED;

		printf("%s", color);
		printf("Input:  \t%lu | %lu\n", tab[size].nmemb, bytes);
		ft_put_row("Expected:", (char *) expected_dst, bytes);
		ft_put_row("Output:  ", (char *) output_dst, bytes);
		printf("%s", RESET_COLOR);

		ATF_CHECK(!bytes || !ft_memcmp(output_dst, expected_dst, bytes));
		printf("----------\n");
		free(output_dst);
		free(expected_dst);
	}
}
// TEST 00 --> ALLOC 0
ATF_TC(test00);
ATF_TC_HEAD(test00, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[0]);
}
ATF_TC_BODY(test00, tc)
{
	t_input	tab[] = {
		{0, 0},
		{10, 0},
		{0, 10},
		{100, 0},
		{0, 100},
		{10000, 0},
		{0, 10000},
	};

	i = 0;
	test(tab, NELEM(tab));
}

// TEST 01 --> ALLOC REGULAR SIZE
ATF_TC(test01);
ATF_TC_HEAD(test01, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[1]);
}
ATF_TC_BODY(test01, tc)
{
	t_input	tab[] = {
		{1, 1},
		{10, 1},
		{100, 1},
		{100, 2},
		{500, 10},
		{1073022, 2},
	};

	i = 1;
	test(tab, NELEM(tab));
}

// TEST 02 --> ALLOC INT OVERFLOW
ATF_TC(test02);
ATF_TC_HEAD(test02, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[2]);
}
ATF_TC_BODY(test02, tc)
{
	t_input	tab[] = {
		{1073741823, 1073741823},
		{10737410823, 1073741823},
		{10737410823, 10731823},
	};

	i = 2;
	test(tab, NELEM(tab));
}

// TEST 03 --> FORCE MALLOC ERROR
ATF_TC(test03);
ATF_TC_HEAD(test03, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[3]);
}
ATF_TC_BODY(test03, tc)
{
	t_input	tab[] = {
		{9223372036854775807, 2},
		{2, 9223372036854775807},
		{3, 9223372036854},
	};

	i = 3;
	test(tab, NELEM(tab));
}

// TEST PROGRAM
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);
	ATF_TP_ADD_TC(tp, test01);
	ATF_TP_ADD_TC(tp, test02);
	ATF_TP_ADD_TC(tp, test03);

	return (atf_no_error());
}
