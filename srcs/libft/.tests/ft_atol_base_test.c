/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_base_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:25:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/10 22:55:43 by joesanto         ###   ########.fr       */
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
#define NELEM(tab, type) (sizeof(tab) / sizeof(type))

char	*tests_titles[] = {
	"Null inputs",
	"Empty inputs",
	"Invalid base and No match in str",
	"Valid base and Valid str",
};
static int	i;

typedef struct s_input_libc
{
	const char	*str;
	const char	*base;
}	t_input_libc;

typedef struct s_input_myown
{
	const char	*str;
	const char	*base;
	ssize_t		expected;
}	t_input_myown;

void	test_libc(t_input_libc tab[], size_t size)
{
	ssize_t	output;
	ssize_t	expected;
	char	*color;
	char	*output_end;
	char	*expected_end;

	printf("\n<test%02d> %s\n", i, tests_titles[i]);
	while (size--)
	{
		expected = strtol(tab[size].str, &expected_end, ft_strlen(tab[size].base));
		output = ft_atol_base(tab[size].str, &output_end, tab[size].base);
		color = expected == output && expected_end == output_end ? GREEN : RED;

		printf("%s", color);
		printf("Input:   \t(%s) %s\n", tab[size].base, tab[size].str);
		printf("Expected:\t%ld - %s\n", expected, expected_end);
		printf("Output:  \t%ld - %s\n", output, output_end);
		printf("%s", RESET);

		ATF_CHECK(expected == output && expected_end == output_end);
		printf("----------\n");
	}
}

void	test_myown(t_input_myown tab[], size_t size)
{
	ssize_t	expected;
	ssize_t	output;
	char	*color;

	printf("\n<test%02d> %s\n", i, tests_titles[i]);
	while (size--)
	{
		expected = tab[size].str && tab[size].base ? tab[size].expected : 0;
		output = ft_atol_base(tab[size].str, 0, tab[size].base);
		color = expected == output ? GREEN : RED;

		printf("%s", color);
		printf("Input:   \t(%s) %s\n", tab[size].base, tab[size].str);
		printf("Expected:\t%ld\n", expected);
		printf("Output:  \t%ld\n", output);
		printf("%s", RESET);

		ATF_CHECK(expected == output);
		printf("----------\n");
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
	t_input_myown	tab[] = {
		{0, "123", 0},
		{"123", 0, 0},
		{0, 0, 0},
		{0, "", 0},
		{"", 0, 0},
		{"-+", 0, 0},
		{0, "-+", 0},
	};

	i = 0;
	test_myown(tab, NELEM(tab, t_input_myown));
}

// TEST 01 --> EMPTY INPUTS
ATF_TC(test01);
ATF_TC_HEAD(test01, tc)
{
	atf_tc_set_md_var(tc, "descr", tests_titles[1]);
}
ATF_TC_BODY(test01, tc)
{
	t_input_myown	tab[] = {
		{"", "", 0},
		{"1234", "", 0},
		{"", "1234", 0},
		{"", "-+", 0},
		{"-+", "", 0},
		{"  234f2 ", "", 0},
		{"", "  234f2 ", 0},
		{"", "987642", 0},
		{"987642", "", 0},
	};

	i = 1;
	test_myown(tab, NELEM(tab, t_input_myown));
}

// TEST 02 --> INVALID BASE AND NO MATCH IN STR
ATF_TC(test02);
ATF_TC_HEAD(test02, tc)
{
	atf_tc_set_md_var(tc, "descr", tests_titles[2]);
}
ATF_TC_BODY(test02, tc)
{
	t_input_myown	tab[] = {
		{"+120234", "0", 0},
		{"-1", "120234", 0},
		{"42", "f[3oij-", 0},
		{"zf3jjji", "f[3oij", 0},
		{"124jkl", "123478-0asrf1", 0},
		{"-123", "j-2rj-", 0},
		{"123", "", 0},
		{"123", "1", 0},
		{"123", "01234567890", 0},
		{"123", "01234 56789", 0},
		{"123", "01234+56789", 0},
		{"123", "01234-56789", 0},
		{"  123", " 0123456789", 0},
		{"123", "01234\t56789", 0},
		{" 123", "01233456789", 0},
		{"123", "abcdefgaa", 0},
		{"123", "a+b-c", 0},
		{"123", "0123\n456789", 0},
		{"  123", "  ", 0},
		{"  123", "\t\n", 0},
		{"123", "00", 0},
		{"123", "aa", 0},
		{"123", "01 ", 0},
		{"123", "01+", 0},
		{"123", "01-", 0},
		{"123", "0\t1", 0},
		{"XYZ", "01", 0},
		{"hello", "0123456789", 0},
		{"999", "abc", 0},
		{"\t\t\t\n\vworld", "01", 0},
		{"      \t\t\n***", "abcdef", 0},
		{"123", "abcdef", 0},
		{"qwerty", "0123456789", 0},
		{"###", "01", 0},
		{"zzz", "abc", 0},
		{"---", "0123456789", 0},
	};

	i = 2;
	test_myown(tab, NELEM(tab, t_input_myown));
}

// TEST 03 --> VALID BASE AND VALID STRING
ATF_TC(test03);
ATF_TC_HEAD(test03, tc)
{
	atf_tc_set_md_var(tc, "descr", tests_titles[3]);
}
ATF_TC_BODY(test03, tc)
{
	t_input_libc	tab2[] = {
		{"      \t -1023f00223r2r", "0123456789abcdef"},
		{"      \t -10fadff23f00223r2r", "0123456789abcdef"},
		{"   +1203f0023r2r", "0123456789"},
		{"   +120233f0023r2r", "0123456789"},
		{"    -1203f0223r2r", "01234567"},
		{"    -223411234f", "01234567"},
		{" +12002343f23r2r", "01"},
		{" 10010011143f23r2r", "01"},
		{" -0010101010101010101", "01"},
	};

	i = 3;
	test_libc(tab2, NELEM(tab2, t_input_libc));
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
