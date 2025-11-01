/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_static_ltoa_base_test.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:25:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/13 15:20:35 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <atf-c.h>

#define RED		"\e[0;31m"
#define GREEN	"\e[0;32m"
#define RESET	"\e[0m"
#define NELEM(tab) (sizeof(tab) / sizeof(char *))

char	*tests_titles[] = {
	"Null inputs",
	"Empty inputs",
	"Invalid base",
	"Valid base",
};
static int	i;

typedef struct s_range
{
	ssize_t	min;
	ssize_t	max;
}	t_range;
t_range _range = {-1234, 1324};

static size_t   get_base(const char *base)
{
	const char      *p;

	if (!base)
		return (0);
	p = base - 1;
	while (*++p)
		if (*p == '+' || *p == '-' || ft_isspace(*p) || ft_strchr(p + 1, *p))
			return (0);
	return (p - base);
}

void	test(t_range range, char *tab[], size_t size)
{
	ssize_t	expected;
	ssize_t	input;
	char	*output;
	char	*color;

	printf("\n<test%02d> %s\n", i, tests_titles[i]);
	while (size--)
	{
		input = range.min - 1;
		while (++input <= range.max)
		{
			expected = get_base(tab[size]) < 2 ? 0 : input;
			ft_static_ltoa_base(input, &output, tab[size]);
			color = expected == ft_atol_base(output, 0, tab[size]) ? GREEN : RED;

			printf("%s", color);
			printf("Input:   \t%ld - %s\n", input, tab[size]);
			printf("Expected:\t%ld (In decimal)\n", expected);
			printf("Output:  \t%s\n", output);
			printf("%s", RESET);

			ATF_CHECK(expected == ft_atol_base(output, 0, tab[size]));
			printf("----------\n");
		}
	}
}

// TEST 00 --> NULL INPUTS
ATF_TC(test00);
ATF_TC_HEAD(test00, tc)
{
	atf_tc_set_md_var(tc, "descr", tests_titles[0]);
}
ATF_TC_BODY(test00, tc)
{
	char	*tab[] = {
		0
	};

	i = 0;
	test(_range, tab, NELEM(tab));
}

// TEST 01 --> EMPTY INPUTS
ATF_TC(test01);
ATF_TC_HEAD(test01, tc)
{
	atf_tc_set_md_var(tc, "descr", tests_titles[1]);
}
ATF_TC_BODY(test01, tc)
{
	char	*tab[] = {
		"",
	};

	i = 1;
	test(_range, tab, NELEM(tab));
}

// TEST 02 --> INVALID BASE
ATF_TC(test02);
ATF_TC_HEAD(test02, tc)
{
	atf_tc_set_md_var(tc, "descr", tests_titles[2]);
}
ATF_TC_BODY(test02, tc)
{
	char	*tab[] = {
		"0",
		"120234",
		"f[3oij-",
		"f[3oij",
		"123478-0asrf1",
		"j-2rj-",
		"",
		"1",
		"01234567890",
		"01234 56789",
		"01234+56789",
		"01234-56789",
		" 0123456789",
		"01234\t56789",
		"01233456789",
		"abcdefgaa",
		"a+b-c",
		"0123\n456789",
		"  ",
		"\t\n",
		"00",
		"aa",
		"01 ",
		"01+",
		"01-",
		"0\t1",
		"01",
		"0123456789",
		"abc",
		"01",
		"abcdef",
		"abcdef",
		"0123456789",
		"01",
		"abc",
		"0123456789",
	};

	i = 2;
	test(_range, tab, NELEM(tab));
}

// TEST 03 --> VALID BASE
ATF_TC(test03);
ATF_TC_HEAD(test03, tc)
{
	atf_tc_set_md_var(tc, "descr", tests_titles[3]);
}
ATF_TC_BODY(test03, tc)
{
	char	*tab2[] = {
		"0123456789abcdef",
		"0123456789",
		"01234567",
		"01",
	};
	t_range	custom_range = {-2147483648, -2147483647};

	i = 3;
	test(_range, tab2, NELEM(tab2));
	test(custom_range, tab2, NELEM(tab2));
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
