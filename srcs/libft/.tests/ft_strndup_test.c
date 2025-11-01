/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:09:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/02 09:33:08 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <atf-c.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define RED			"\e[0;31m"
#define GREEN		"\e[0;32m"
#define RESET_COLOR	"\e[0m"
#define NELEM(tab) (sizeof(tab) / sizeof(char *))
#define TEST_NULLS	1<<0

char	*test_titles[] = {
	"Null strings",
	"Empty Strings",
	"Regular Strings",
	"Big Strings",
};
static int	i;

void	test(char *tab[], int size)
{
	char	*output_dst;
	char	*expected_dst;
	char	*color;
	size_t	n;
	size_t	len;

	printf("\n<test%02d> %s\n", i, test_titles[i]);
	while (size--)
	{
		len = ft_strlen(tab[size]) + 1;
		n = -1;
		while (++n <= len)
		{
			if (tab[size])
				expected_dst = strndup(tab[size], n);
			else
				expected_dst = 0;
			output_dst = ft_strndup(tab[size], n);
			color = !ft_strncmp(expected_dst, output_dst, ft_strlen(tab[size]) + 1) ? GREEN : RED;

			printf("%s", color);
			printf("Input:   \t%s\n", tab[size]);
			printf("Expected:\t%s\n", expected_dst);
			printf("Output:  \t%s\n", output_dst);
			printf("%s", RESET_COLOR);
			
			ATF_CHECK(!ft_strncmp(expected_dst, output_dst, ft_strlen(tab[size]) + 1));
			printf("----------\n");
			free(output_dst);
			free(expected_dst);
		}
	}
}
// TEST 00 --> NULL STRINGS
ATF_TC(test00);
ATF_TC_HEAD(test00, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[0]);
}
ATF_TC_BODY(test00, tc)
{
	char	*tab[] = {
		0,
	};

	i = 0;
	test(tab, NELEM(tab));
}

// TEST 01 --> EMPTY STRINGS
ATF_TC(test01);
ATF_TC_HEAD(test01, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[1]);
}
ATF_TC_BODY(test01, tc)
{
	char	*tab[] = {
		"",
	};

	i = 1;
	test(tab, NELEM(tab));
}

// TEST 02 --> REGULAR STRINGS
ATF_TC(test02);
ATF_TC_HEAD(test02, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[2]);
}
ATF_TC_BODY(test02, tc)
{
	char	*tab[] = {
		"\000\101\077\300\012",
		"\123\045\011",
		"\200\177\176\175\174\173\172",
		"",
		"\001",
		"\002\003\004\005\006",
		"\010\011\012\013\014\015",
		"\077\100\101\102\103\104\105\106\107",
		"\120\121\122\123\124\125\126\127",
		"\300\277\276\275",
		"\055\056\057",
		"\040\041\042\043\044",
		"\050\051\052\053\054\055\056",
		"\060\061\062\063\064\065\066\067",
		"\070\071\072\073\074\075\076\077",
		"\101\102\103\104\105\106\107\110",
		"\111\112\113\114\115\116\117\120",
		"\130\131\132\133\134\135\136\137",
		"\141\142\143\144\145\146\147",
		"\150\151\152\153\154\155\156\157",
		"\160\161\162\163\164\165\166\167",
		"\170\171\172\173\174\175\176\177",
		"\200\201\202\203\204\205",
		"\206\207\210\211\212\213\214\215",
		"\216\217\220\221\222\223\224\225",
		"\226\227\230\231\232\233\234\235",
		"\236\237\240\241\242\243\244\245",
		"\246\247\250\251\252\253\254\255",
		"\256\257\260\261\262\263\264\265",
		"\266\267\270\271\272\273\274\275",
		"\276\277\300",
		"\000\111\222\333",
		"\123\234\145\256",
		"\067\210\131\252\173\214\235",
		"\276\177\100\001\002",
		"\300\277\276\275\274\273\272",
		"\123\111\101\077\055",
		"\040\100\200\300",
		"\150\160\170\200\210\220\230\240",
		"\041\042\043\044\045\046\047\050",
		"\051\052\053\054\055\056\057\060",
		"\061\062\063\064\065\066\067\070",
		"\071\072\073\074\075\076\077",
		"\111\112\113\114\115\116\117",
		"\120\121\122\123\124\125\126",
		"\127\130\131\132\133\134\135",
		"\136\137\140\141\142\143\144",
		"\145\146\147\150\151\152\153",
		"\154\155\156\157\160\161\162",
		"\163\164\165\166\167\170\171",
		"\172\173\174\175\176\177\200",
		"\201\202\203\204\205\206\207",
		"\210\211\212\213\214\215\216",
		"\217\220\221\222\223\224\225",
		"\226\227\230\231\232\233\234",
		"\235\236\237\240\241\242\243",
		"\244\245\246\247\250\251\252",
		"\253\254\255\256\257\260\261",
		"\262\263\264\265\266\267\270",
		"\271\272\273\274\275\276\277",
		"\300",
		"\000\010\020\030\040\050\060\070",
		"\100\110\120\130\140\150\160\170",
		"\200\210\220\230\240\250\260\270",
		"\101\202\303",
		"\011\022\033\044\055\066\077",
		"\012\024\036\050\062\074",
		"\075\076\077\100\101\102\103",
		"\111\122\133\144\155\166\177",
		"\177\176\175\174\173\172",
		"\011\012\013\014\015",
		"\123\223\323\023",
		"\101\201\301",
		"\055\155\255",
		"\077\177\277",
		"\011\111\211\311",
		"\012\112\212\312",
		"\013\113\213\313",
		"\014\114\214\314",
		"\015\115\215\315",
		"\016\116\216\316",
		"\017\117\217\317",
		"\020\120\220\320",
		"\021\121\221\321",
		"\022\122\222\322",
		"\023\123\223\323",
		"\024\124\224\324",
		"\025\125\225\325",
		"\026\126\226\326",
		"\027\127\227\327",
		"\030\130\230\330",
		"\031\131\231\331",
		"\032\132\232\332",
		"\033\133\233\333",
		"\034\134\234\334",
		"\035\135\235\335",
		"\036\136\236\336",
		"\037\137\237\337",
		"\040\140\240\340"
	};

	i = 2;
	test(tab, NELEM(tab));
}

// TEST 03 --> BIG STRINGS
ATF_TC(test03);
ATF_TC_HEAD(test03, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[3]);
}
ATF_TC_BODY(test03, tc)
{
	char	*tab[] = {
		"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",
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
