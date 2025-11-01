/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stpcpy_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:09:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/08 13:22:18 by joesanto         ###   ########.fr       */
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
	"Null Data",
	"Empty strings",
	"Size of One",
	"Size of Five",
	"Dest bigger than src",
	"Src bigger than dest",
};
static int	i;

typedef struct s_input
{
	const char	*src;
	size_t		size;
}	t_input;

void	test(t_input tab[], int size)
{
	char	*output;
	char	*output_dst;
	char	*expected;
	char	*expected_dst;
	char	*color;

	printf("\n<test%02d> %s\n", i, test_titles[i]);
	while (size--)
	{
		output_dst = malloc(tab[size].size);
		if (!output_dst)
			return ;
		expected_dst = malloc(tab[size].size);
		if (!expected_dst)
		{
			free(output_dst);
			return ;
		}
		expected = stpcpy(expected_dst, tab[size].src) - expected_dst + output_dst;
		output = ft_stpcpy(output_dst, tab[size].src);
		color = expected == output && !strcmp(output_dst, expected_dst) ? GREEN : RED;

		printf("%s", color);
		printf("Input:   \t(%p) %s\n", output_dst, tab[size].src);
		printf("Expected:\t(%p) %s\n", expected, expected_dst);
		printf("Output:  \t(%p) %s\n", output, output_dst);
		printf("%s", RESET_COLOR);

		ATF_CHECK(expected == output && !strcmp(output_dst, expected_dst));
		printf("----------\n");
		free(output_dst);
		free(expected_dst);
	}
}

void	test_expect(t_input tab[], int size, int flags)
{
	char	*output;
	char	*output_dst;
	char	*expected;
	char	*color;

	printf("\n-- My own Cases --\n");
	while (size--)
	{
		if (flags & TEST_NULLS)
			output_dst = 0;
		else
		{
			output_dst = malloc(tab[size].size);
			if (!output_dst)
				return ;
		}
		expected = tab[size].src ? output_dst : 0;
		output = ft_stpcpy(output_dst, tab[size].src);
		color = expected == output ? GREEN : RED;

		printf("%s", color);
		printf("Input:    \t%p\n", tab[size].src);
		printf("Expected: \t%p\n", expected);
		printf("Output:   \t%p\n", output);
		printf("%s", RESET_COLOR);

		ATF_CHECK(expected == output);
		printf("----------\n");
		free(output_dst);
	}
}

// TEST 00 --> NULL DATA
ATF_TC(test00);
ATF_TC_HEAD(test00, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[0]);
}
ATF_TC_BODY(test00, tc)
{
	t_input	tab1[] = {
		{0, 0},
		{0, 1},
		{0, 10},
		{0, 100},
		{0, 2000},
		{0, 10000},
	};

	t_input	tab2[] = {
		{"This is a test", 0},
		{"This is a test", 1},
		{"This is a test", 10},
		{"This is a test", 100},
		{"This is a test", 2000},
	};

	i = 0;
	printf("\n<test%02d> %s\n", i, test_titles[i]);
	test_expect(tab1, NELEM(tab1), 0);
	test_expect(tab1, NELEM(tab1), TEST_NULLS);
	test_expect(tab2, NELEM(tab2), TEST_NULLS);
}

// TEST 01 --> EMPTY STRINGS
ATF_TC(test01);
ATF_TC_HEAD(test01, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[1]);
}
ATF_TC_BODY(test01, tc)
{
	t_input	tab[] = {
		{"", 0},
		{"", 1},
		{"", 2},
		{"", 50},
		{"", 100},
		{"", 1000},
		{"", 100000},
		{"", 10000000},
	};

	i = 1;
	test(tab, NELEM(tab));
}

// TEST 02 --> SIZE OF ONE
ATF_TC(test02);
ATF_TC_HEAD(test02, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[2]);
}
ATF_TC_BODY(test02, tc)
{
	char	neg = -1;
	t_input	tab[] = {
		{"A", 0},
		{"A", 1},
		{"A", 2},
		{"A", 4},
		{"A", 10},
		{"A", 100},
		{"A", 1000},
		{"", 0},
		{"", 1},
		{"", 2},
		{"", 4},
		{"", 10},
		{"", 100},
		{"", 1000},
		{"\232", 0},
		{"\232", 1},
		{"\232", 2},
		{"\232", 4},
		{"\232", 10},
		{"\232", 100},
		{"\232", 1000},
		{&neg, 0},
		{&neg, 1},
		{&neg, 2},
		{&neg, 4},
		{&neg, 10},
		{&neg, 100},
		{&neg, 1000},
	};

	i = 2;
	test(tab, NELEM(tab));
}

// TEST 03 --> SIZE OF FIVE
ATF_TC(test03);
ATF_TC_HEAD(test03, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[3]);
}
ATF_TC_BODY(test03, tc)
{
	t_input	tab[] = {
		{"N#r{)", 0},
		{"f(90W", 1},
		{"Xw=!m", 2},
		{"b8/Z/", 4},
		{"\203\123\330\300\123", 4},
		{"Rm_;6", 10},
		{"qgRW_", 100},
		{"y9:rJ", 1000},
		{"%wjqG", 100000},
		{"]uE$e", 0},
		{".r]$E", 1},
		{"9q]w&", 2},
		{"KF#[]", 4},
		{"*ei1%", 10},
		{"hrA&a", 100},
		{"B!W7[", 1000},
		{"Xv!rt", 100000},
		{"Ud&Ug", 0},
		{"Sh]5+", 1},
		{"3u=L$", 2},
		{"cDj4v", 4},
		{"S4R;E", 10},
		{"BT__=", 100},
		{"e#CSM", 1000},
		{"8L;6{", 100000},
	};

	i = 3;
	test(tab, NELEM(tab));
}

// TEST 04 --> DEST BIGGER THAN SRC
ATF_TC(test04);
ATF_TC_HEAD(test04, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[4]);
}
ATF_TC_BODY(test04, tc)
{
	t_input	tab[] = {
		{"v@", ft_strlen("v@") + (3)},
		{"xR8tL", ft_strlen("xR8tL") + (7)},
		{"qZ7^NdYp#k", ft_strlen("qZ7^NdYp#k") + (2)},
		{"mJ6$vR", ft_strlen("mJ6$vR") + (9)},
		{"sF1&KLo9qP", ft_strlen("sF1&KLo9qP") + (5)},
		{"hZt4%", ft_strlen("hZt4%") + (8)},
		{"bR9qWpV@T1x", ft_strlen("bR9qWpV@T1x") + (1)},
		{"nT3mX!", ft_strlen("nT3mX!") + (6)},
		{"aY7vCkJ#", ft_strlen("aY7vCkJ#") + (4)},
		{"pL2rQ$", ft_strlen("pL2rQ$") + (10)},
		{"G^8nKp&", ft_strlen("G^8nKp&") + (2)},
		{"jT*5vL8rZ", ft_strlen("jT*5vL8rZ") + (6)},
		{"xF3mR#", ft_strlen("xF3mR#") + (1)},
		{"zH9p!QmLk7", ft_strlen("zH9p!QmLk7") + (5)},
		{"wJ2v@K", ft_strlen("wJ2v@K") + (3)},
		{"eB6q$N", ft_strlen("eB6q$N") + (9)},
		{"kL8m#V1aT", ft_strlen("kL8m#V1aT") + (8)},
		{"yP1t*J", ft_strlen("yP1t*J") + (2)},
		{"rS4v^X8mBq", ft_strlen("rS4v^X8mBq") + (7)},
		{"uN7x!F", ft_strlen("uN7x!F") + (10)},
		{"cQ2m&Y", ft_strlen("cQ2m&Y") + (1)},
		{"oK5p%Lk9M2x", ft_strlen("oK5p%Lk9M2x") + (4)},
		{"iH8t#V", ft_strlen("iH8t#V") + (6)},
		{"fJ3r@N", ft_strlen("fJ3r@N") + (9)},
		{"sM6x!Q", ft_strlen("sM6x!Q") + (3)},
		{"vR1b^PzT8qL", ft_strlen("vR1b^PzT8qL") + (8)},
		{"nT9q*K", ft_strlen("nT9q*K") + (5)},
		{"aF4m%J", ft_strlen("aF4m%J") + (2)},
		{"bL7v#Z1pQ8rW", ft_strlen("bL7v#Z1pQ8rW") + (10)},
		{"dP2t@X", ft_strlen("dP2t@X") + (1)},
		{"gN5x$R", ft_strlen("gN5x$R") + (6)},
		{"hK8v!Y", ft_strlen("hK8v!Y") + (9)},
		{"jL3r^M", ft_strlen("jL3r^M") + (4)},
		{"mR6q*Kp8vL1xZ", ft_strlen("mR6q*Kp8vL1xZ") + (7)},
		{"pT1b%F", ft_strlen("pT1b%F") + (2)},
		{"qF9x#J", ft_strlen("qF9x#J") + (5)},
		{"rL4v&N", ft_strlen("rL4v&N") + (10)},
		{"sN7t!K", ft_strlen("sN7t!K") + (1)},
		{"tK2r^X", ft_strlen("tK2r^X") + (4)},
		{"uP5v$M", ft_strlen("uP5v$M") + (6)},
		{"vJ8b!R", ft_strlen("vJ8b!R") + (9)},
		{"wL3x#V", ft_strlen("wL3x#V") + (3)},
		{"xN6q%Y", ft_strlen("xN6q%Y") + (8)},
		{"yF1v@K", ft_strlen("yF1v@K") + (5)},
		{"zR4m^J", ft_strlen("zR4m^J") + (2)},
		{"aK7t!N", ft_strlen("aK7t!N") + (7)},
		{"bL2r$M8x9QpR", ft_strlen("bL2r$M8x9QpR") + (10)},
		{"cP5v#X", ft_strlen("cP5v#X") + (1)},
		{"dQ8x!RzT1", ft_strlen("dQ8x!RzT1") + (4)},
		{"eT3m%K", ft_strlen("eT3m%K") + (6)},
		{"fB6v^J", ft_strlen("fB6v^J") + (9)},
		{"gN1r!L", ft_strlen("gN1r!L") + (3)},
	};

	i = 4;
	test(tab, NELEM(tab));
}

// TEST 05 --> SRC BIGGER THAN DEST
ATF_TC(test05);
ATF_TC_HEAD(test05, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[5]);
}
ATF_TC_BODY(test05, tc)
{
	t_input tab[] = {
		{"vT9@kL#pWqRsD!mZxYbCjHnGfLqUe", ft_strlen("vT9@kL#pWqRsD!mZxYbCjHnGfLqUe") - (12)},
		{"Xr8vB#tN!sLqPfKcZmJwGhYdRpQxS", ft_strlen("Xr8vB#tN!sLqPfKcZmJwGhYdRpQxS") - (15)},
		{"qZ7^NdYp#kLmRsWvTxUoPzJhBcGfK", ft_strlen("qZ7^NdYp#kLmRsWvTxUoPzJhBcGfK") - (10)},
		{"mJ6$vR!xLqTnPcYbGkHsDzFjWvQmA", ft_strlen("mJ6$vR!xLqTnPcYbGkHsDzFjWvQmA") - (14)},
		{"sF1&KLo9qPnVxYbTzGhRwMfJkLpAe", ft_strlen("sF1&KLo9qPnVxYbTzGhRwMfJkLpAe") - (20)},
		{"hZt4%KjLpQwErTnMvXyZaCbGfHsJd", ft_strlen("hZt4%KjLpQwErTnMvXyZaCbGfHsJd") - (12)},
		{"bR9qWpV@T1xLzYnGcDhMfKjRqSwPe", ft_strlen("bR9qWpV@T1xLzYnGcDhMfKjRqSwPe") - (18)},
		{"nT3mX!LpRzQvBkTsGwYhJdFcNzAmP", ft_strlen("nT3mX!LpRzQvBkTsGwYhJdFcNzAmP") - (15)},
		{"aY7vCkJ#LpQwErTyUiOpAsDfGhJkL", ft_strlen("aY7vCkJ#LpQwErTyUiOpAsDfGhJkL") - (22)},
		{"pL2rQ$XnVbMkJhGfDsAzLqPwErTyU", ft_strlen("pL2rQ$XnVbMkJhGfDsAzLqPwErTyU") - (19)},
		{"G^8nKp&RtYwQzXlCvMbNgHsJdFfLp", ft_strlen("G^8nKp&RtYwQzXlCvMbNgHsJdFfLp") - (11)},
		{"jT*5vL8rZxQwBpAsDfGhJkLmNoPqR", ft_strlen("jT*5vL8rZxQwBpAsDfGhJkLmNoPqR") - (17)},
		{"xF3mR#LpTnQcVzXyAaSbDcEfGhJiK", ft_strlen("xF3mR#LpTnQcVzXyAaSbDcEfGhJiK") - (20)},
		{"zH9p!QmLk7RtYwNvXbGcDfHsJqPmK", ft_strlen("zH9p!QmLk7RtYwNvXbGcDfHsJqPmK") - (14)},
		{"wJ2v@KxLmNpQrStUvWxYzAbCdEfGh", ft_strlen("wJ2v@KxLmNpQrStUvWxYzAbCdEfGh") - (16)},
		{"eB6q$NpLsRtUvWxYzAbCdEfGhIjKl", ft_strlen("eB6q$NpLsRtUvWxYzAbCdEfGhIjKl") - (12)},
		{"kL8m#V1aTxYbCfGhJkLpQrStUvWxZ", ft_strlen("kL8m#V1aTxYbCfGhJkLpQrStUvWxZ") - (15)},
		{"yP1t*JmNkLpQrStUvWxYzAbCdEfGh", ft_strlen("yP1t*JmNkLpQrStUvWxYzAbCdEfGh") - (18)},
		{"rS4v^X8mBqLnRpTsUwXyZaCbDfGhJ", ft_strlen("rS4v^X8mBqLnRpTsUwXyZaCbDfGhJ") - (19)},
		{"uN7x!FkLpQrStUvWxYzAbCdEfGhIj", ft_strlen("uN7x!FkLpQrStUvWxYzAbCdEfGhIj") - (14)},
		{"cQ2m&YbNpQrStUvWxYzAbCdEfGhIjK", ft_strlen("cQ2m&YbNpQrStUvWxYzAbCdEfGhIjK") - (20)},
		{"oK5p%LkJhGfDsAzXyBwCeVtRgUyIo", ft_strlen("oK5p%LkJhGfDsAzXyBwCeVtRgUyIo") - (13)},
		{"iH8t#VpLsRtUvWxYzAbCdEfGhIjKlM", ft_strlen("iH8t#VpLsRtUvWxYzAbCdEfGhIjKlM") - (22)},
		{"fJ3r@NkLpQrStUvWxYzAbCdEfGhIjK", ft_strlen("fJ3r@NkLpQrStUvWxYzAbCdEfGhIjK") - (17)},
		{"sM6x!QvBpAsDfGhJkLmNoPqRtYwXz", ft_strlen("sM6x!QvBpAsDfGhJkLmNoPqRtYwXz") - (20)},
		{"vR1b^PzT8qLpQrStUvWxYzAbCdEfGh", ft_strlen("vR1b^PzT8qLpQrStUvWxYzAbCdEfGh") - (18)},
		{"nT9q*KjLpQrStUvWxYzAbCdEfGhIjK", ft_strlen("nT9q*KjLpQrStUvWxYzAbCdEfGhIjK") - (15)},
		{"aF4m%JxYbCfGhJkLpQrStUvWxYzAbC", ft_strlen("aF4m%JxYbCfGhJkLpQrStUvWxYzAbC") - (21)},
		{"bL7v#Z1pQ8rWxYzAbCdEfGhIjKlMnO", ft_strlen("bL7v#Z1pQ8rWxYzAbCdEfGhIjKlMnO") - (20)},
		{"dP2t@XyZaCbDfGhIjKlMnOpQrStUvW", ft_strlen("dP2t@XyZaCbDfGhIjKlMnOpQrStUvW") - (19)},
		{"gN5x$RtYwQzXlCvMbNgHsJdFfLpQrS", ft_strlen("gN5x$RtYwQzXlCvMbNgHsJdFfLpQrS") - (20)},
		{"hK8v!YxLmNpQrStUvWxYzAbCdEfGhJ", ft_strlen("hK8v!YxLmNpQrStUvWxYzAbCdEfGhJ") - (22)},
		{"jL3r^MpLsRtUvWxYzAbCdEfGhIjKlM", ft_strlen("jL3r^MpLsRtUvWxYzAbCdEfGhIjKlM") - (18)},
		{"mR6q*Kp8vL1xZyAbCdEfGhIjKlMnOp", ft_strlen("mR6q*Kp8vL1xZyAbCdEfGhIjKlMnOp") - (20)},
		{"pT1b%FvBpAsDfGhJkLmNoPqRtYwXzZ", ft_strlen("pT1b%FvBpAsDfGhJkLmNoPqRtYwXzZ") - (19)},
		{"qF9x#JxYbCfGhJkLpQrStUvWxYzAbC", ft_strlen("qF9x#JxYbCfGhJkLpQrStUvWxYzAbC") - (18)},
		{"rL4v&NpQrStUvWxYzAbCdEfGhIjKlM", ft_strlen("rL4v&NpQrStUvWxYzAbCdEfGhIjKlM") - (20)},
		{"sN7t!KxLmNpQrStUvWxYzAbCdEfGhJ", ft_strlen("sN7t!KxLmNpQrStUvWxYzAbCdEfGhJ") - (17)},
		{"tK2r^XvBpAsDfGhJkLmNoPqRtYwXzQ", ft_strlen("tK2r^XvBpAsDfGhJkLmNoPqRtYwXzQ") - (15)},
		{"uP5v$MxYbCfGhJkLpQrStUvWxYzAbC", ft_strlen("uP5v$MxYbCfGhJkLpQrStUvWxYzAbC") - (18)},
		{"vJ8b!RpLsRtUvWxYzAbCdEfGhIjKlM", ft_strlen("vJ8b!RpLsRtUvWxYzAbCdEfGhIjKlM") - (20)},
		{"wL3x#VxLmNpQrStUvWxYzAbCdEfGhJ", ft_strlen("wL3x#VxLmNpQrStUvWxYzAbCdEfGhJ") - (19)},
		{"xN6q%YvBpAsDfGhJkLmNoPqRtYwXzZ", ft_strlen("xN6q%YvBpAsDfGhJkLmNoPqRtYwXzZ") - (20)},
		{"yF1v@KxYbCfGhJkLpQrStUvWxYzAbC", ft_strlen("yF1v@KxYbCfGhJkLpQrStUvWxYzAbC") - (18)},
		{"zR4m^JpLsRtUvWxYzAbCdEfGhIjKlM", ft_strlen("zR4m^JpLsRtUvWxYzAbCdEfGhIjKlM") - (17)},
		{"aK7t!NpQrStUvWxYzAbCdEfGhIjKlM", ft_strlen("aK7t!NpQrStUvWxYzAbCdEfGhIjKlM") - (19)},
		{"bL2r$MxLmNpQrStUvWxYzAbCdEfGhJ", ft_strlen("bL2r$MxLmNpQrStUvWxYzAbCdEfGhJ") - (20)},
		{"cP5v#XvBpAsDfGhJkLmNoPqRtYwXzQ", ft_strlen("cP5v#XvBpAsDfGhJkLmNoPqRtYwXzQ") - (18)},
		{"dQ8x!RzYbCfGhJkLpQrStUvWxYzAbC", ft_strlen("dQ8x!RzYbCfGhJkLpQrStUvWxYzAbC") - (15)},
		{"eT3m%KpLsRtUvWxYzAbCdEfGhIjKlM", ft_strlen("eT3m%KpLsRtUvWxYzAbCdEfGhIjKlM") - (20)},
		{"fB6v^JxLmNpQrStUvWxYzAbCdEfGhJ", ft_strlen("fB6v^JxLmNpQrStUvWxYzAbCdEfGhJ") - (19)},
		{"gN1r!LpBpAsDfGhJkLmNoPqRtYwXzZ", ft_strlen("gN1r!LpBpAsDfGhJkLmNoPqRtYwXzZ") - (17)},
	};

	i = 5;
	test(tab, NELEM(tab));
}

// TEST PROGRAM
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);
	ATF_TP_ADD_TC(tp, test01);
	ATF_TP_ADD_TC(tp, test02);
	ATF_TP_ADD_TC(tp, test03);
	ATF_TP_ADD_TC(tp, test04);
	ATF_TP_ADD_TC(tp, test05);

	return (atf_no_error());
}
