/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 09:30:13 by joesanto          #+#    #+#             */
/*   Updated: 2025/09/29 10:10:13 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <atf-c.h>
#include <stdio.h>

#define LIBC_EXPECT	0
#define MY_EXPECT	1<<0
#define NELEM(tab) (sizeof(tab) / sizeof(t_input))
#define GREEN		"\e[0;32m"
#define RED			"\e[0;31m"
#define RESET_COLOR "\e[0m"

/*
	STRUCTURE -->
		- INPUTS struct
		- FUNCTION that compare original strcmp output with the same input as ft_strcmp
		- A INPUT, EXPECTED and OUTPUT structure of print result
*/

char	*test_titles[] = {
	"Empty strings",
	"Nulls strings",
	"Size of One",
	"Size of Five",
	"Different Sizes"
};
static int	i;

typedef struct s_input
{
	char	*s1;
	char	*s2;
	int		expected;
}	t_input;

void	test(t_input tab[], int size, int flags)
{
	int			expected;
	int			output;
	char		*color;
	size_t		cmp_size;
	size_t		len;

	printf("\n<test%02d> %s\n\n", i, test_titles[i]);
	while (size--)
	{
		cmp_size = -1;
		len = ft_strlen(tab[size].s1) + ft_strlen(tab[size].s2);
		while (++cmp_size < len)
		{
			if (flags & MY_EXPECT)
				expected = cmp_size == 0 ? 0 : tab[size].expected;
			else
				expected = strncmp(tab[size].s1, tab[size].s2, cmp_size);

			output = ft_strncmp(tab[size].s1, tab[size].s2, cmp_size);
			color = output == expected ? GREEN : RED;

			printf("%s", color);
			printf("Input:   \t\"%s\"\t-\t\"%s\"\n", tab[size].s1, tab[size].s2);
			printf("Expected:\t%3d\n", expected);
			printf("Output:  \t%3d\n\n", output);
			printf("%s", RESET_COLOR);

			ATF_CHECK_EQ(expected, output);
			printf("----------\n");
		}
	}
}

// TEST 00 --> EMPTY STRINGS
ATF_TC(test00);
ATF_TC_HEAD(test00, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[0]);
}
ATF_TC_BODY(test00, tc)
{
	char	neg = -1;
	t_input tab[] = {
		{"", "", LIBC_EXPECT},
		{"", "A", LIBC_EXPECT},
		{"A", "", LIBC_EXPECT},
		{"", "", LIBC_EXPECT},
		{"", "", LIBC_EXPECT},
		{"", "\200", LIBC_EXPECT},
		{"\200", "", LIBC_EXPECT},
		{"", "\207", LIBC_EXPECT},
		{"\207", "", LIBC_EXPECT},
		{"", "\207\300", LIBC_EXPECT},
		{"\207\300", "", LIBC_EXPECT},
		{"", "\x99\x60", LIBC_EXPECT},
		{"\x99\x60", "", LIBC_EXPECT},
		{"", "\000", LIBC_EXPECT},
		{"\000", "", LIBC_EXPECT},
		{"", "\x00", LIBC_EXPECT},
		{"\x00", "", LIBC_EXPECT},
		{"", "0", LIBC_EXPECT},
		{"0", "", LIBC_EXPECT},
		{"", "dx[[e@kd9uzRJ)BqLEv9uqt!Q/P}H[", LIBC_EXPECT},
		{"dx[[e@kd9uzRJ)BqLEv9uqt!Q/P}H[", "", LIBC_EXPECT},
		{"", &neg, LIBC_EXPECT},
		{&neg, "", LIBC_EXPECT},
	};

	i = 0;
	test(tab, NELEM(tab), LIBC_EXPECT);
}

// TEST 01 --> NULL STRINGS
ATF_TC(test01);
ATF_TC_HEAD(test01, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[1]);
}
ATF_TC_BODY(test01, tc)
{
	char	neg = -1;
	t_input	tab[] = {
		{0, 0, 0},
		{"", 0, 1},
		{0, "", -1},
		{"joel", 0, 1},
		{0, "joel", -1},
		{&neg, 0, 1},
		{0, &neg, -1},
	};

	i = 1;
	test(tab, NELEM(tab), MY_EXPECT);
}

// TEST 02 --> Size of One
ATF_TC(test02);
ATF_TC_HEAD(test02, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[2]);
}
ATF_TC_BODY(test02, tc)
{
	char	neg = -1;
	char	overflow = (char)9518755619835756;
	t_input	tab[] = {
		{"1", "1", LIBC_EXPECT},
		{"2", "1", LIBC_EXPECT},
		{"1", "2", LIBC_EXPECT},
		{"2", "2", LIBC_EXPECT},
		{"A", "a", LIBC_EXPECT},
		{"a", "a", LIBC_EXPECT},
		{"a", "A", LIBC_EXPECT},
		{"a", "Z", LIBC_EXPECT},
		{"\300", "\300", LIBC_EXPECT},
		{"\300", "\000", LIBC_EXPECT},
		{"\000", "\300", LIBC_EXPECT},
		{"\x99", "\x90", LIBC_EXPECT},
		{"\x90", "\x99", LIBC_EXPECT},
		{"", "", LIBC_EXPECT},
		{"0", "", LIBC_EXPECT},
		{"", "0", LIBC_EXPECT},
		{"\n", "\n", LIBC_EXPECT},
		{"\\", "\\", LIBC_EXPECT},
		{"\e", "\e", LIBC_EXPECT},
		{"\a", "\b", LIBC_EXPECT},
		{&neg, &neg, LIBC_EXPECT},
		{&overflow, &overflow, LIBC_EXPECT},
	};

	i = 2;
	test(tab, NELEM(tab), LIBC_EXPECT);
}

// TEST 03 --> Size of Five
ATF_TC(test03);
ATF_TC_HEAD(test03, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[3]);
}
ATF_TC_BODY(test03, tc)
{
	t_input	tab[] = {
		{"\x01\x7C\xAB\x05\x7B", "\xBE\x1F\x30\xBF\xA7", LIBC_EXPECT},
		{"\xF8\x61\xE2\xFF\x05", "\xC5\xF2\x29\x4D\x32", LIBC_EXPECT},
		{"\x32\x28\xA8\x9D\xE4", "\xB6\xE8\xE3\x76\x0F", LIBC_EXPECT},
		{"\x8A\x05\x75\xE3\x02", "\xA4\x54\x1F\x23\x4A", LIBC_EXPECT},
		{"\xA5\x4F\xE8\x44\xB7", "\x36\xF1\xC1\xB4\xF0", LIBC_EXPECT},
		{"\xD4\x0E\x02\xD2\x27", "\x26\xD0\xBC\x35\xD5", LIBC_EXPECT},
		{"\x5D\x45\x3C\x85\x5F", "\x54\x7E\x7B\xD2\x6A", LIBC_EXPECT},
		{"\x63\x59\x5C\xF0\x9E", "\x3F\x43\x7F\x0E\x21", LIBC_EXPECT},
		{"\x59\x9F\x3E\x2F\xBE", "\xA3\x70\x61\x32\x9D", LIBC_EXPECT},
		{"\xCB\xBD\x1A\x2D\xCD", "\x1E\x21\x0B\x7E\xFE", LIBC_EXPECT},
		{"\x8C\x22\x40\xA8\x08", "\x05\x50\x9E\x66\xE8", LIBC_EXPECT},
		{"\xA4\x36\xFC\x8A\x51", "\xAC\x64\xAD\x7F\x06", LIBC_EXPECT},
		{"\xB1\x3E\xF9\x68\x0B", "\x49\xA0\x7E\xD0\x99", LIBC_EXPECT},
		{"\x41\xFF\xB7\xAF\x21", "\xFD\x8D\x91\xA7\xE2", LIBC_EXPECT},
		{"\x4C\x14\x41\x22\x27", "\x52\xE9\x8E\xA9\x8F", LIBC_EXPECT},
		{"\x5B\x3C\xA1\x64\x91", "\x05\x0A\xF4\xEA\xEC", LIBC_EXPECT},
		{"\x24\x21\xAA\xBF\xE3", "\x85\x56\x0A\x1E\x13", LIBC_EXPECT},
		{"\xE0\x93\x56\xE0\xB6", "\x19\x0C\x10\x0B\x63", LIBC_EXPECT},
		{"\xEB\x07\x8B\x69\x82", "\x8B\x73\xA8\x58\x14", LIBC_EXPECT},
		{"\xE8\x1B\x17\x58\x8D", "\xD7\x0B\x49\xE8\xDB", LIBC_EXPECT},
		{"\x41\xAC\xF1\x23\x9E", "\xCB\xFE\x15\x17\x34", LIBC_EXPECT},
		{"\x45\x8E\x29\x55\x1A", "\x5F\x12\x20\x81\x8D", LIBC_EXPECT},
		{"\xAD\x6F\x4A\x8C\x71", "\x44\x1F\x84\x86\x68", LIBC_EXPECT},
		{"\x26\x3B\xD5\x65\x69", "\x10\x01\xBD\x3A\xF4", LIBC_EXPECT},
		{"\x24\x91\x00\x2F\xA8", "\x5C\x92\x1A\x7F\xC6", LIBC_EXPECT},
		{"\x63\x94\x4B\x03\x79", "\xB6\xFF\x9B\xE1\x6A", LIBC_EXPECT},
		{"\x70\x02\x32\x96\xF4", "\xC5\x31\x04\x2F\x3D", LIBC_EXPECT},
		{"\x33\xA1\x29\x57\x7E", "\xC3\x49\xDD\x79\x13", LIBC_EXPECT},
		{"\x8C\xE9\x84\x64\x9D", "\xE5\xA2\x5B\xCB\x7D", LIBC_EXPECT},
		{"\xC2\x55\xC5\x5B\x95", "\x08\xF7\x13\xC9\xD1", LIBC_EXPECT},
		{"\x30\x2F\x9F\x68\x97", "\x08\xDF\x36\x9C\x24", LIBC_EXPECT},
		{"\x10\x09\xCB\x1A\xA8", "\xD7\xDA\x04\x11\x68", LIBC_EXPECT},
		{"\xE5\xBD\xF5\x5B\x82", "\x55\x51\xF5\x8C\xFB", LIBC_EXPECT},
		{"\x10\x6C\x7C\x77\x76", "\x6C\x5D\x21\xD5\x14", LIBC_EXPECT},
		{"\xF0\x26\x55\xFA\x37", "\xCF\x9B\x03\x92\xF6", LIBC_EXPECT},
		{"\xDC\xA0\x0D\x7B\xA5", "\x00\x49\x8E\xE0\xEB", LIBC_EXPECT},
		{"\x02\x82\xD5\x50\xAC", "\xB1\x5E\x0D\xFE\x9D", LIBC_EXPECT},
		{"\x1E\x35\x21\x34\x54", "\xF2\x21\xEB\x0A\x67", LIBC_EXPECT},
		{"\x95\xC4\x14\x17\xAB", "\xEF\x23\x6A\xA1\x03", LIBC_EXPECT},
		{"\x83\x5B\x8D\xD9\x5E", "\x0A\xF5\x14\x1F\x69", LIBC_EXPECT},
		{"\x78\x7D\x2A\x20\xAC", "\x11\xA6\x93\x93\xC2", LIBC_EXPECT},
		{"\xC5\x54\x48\xD9\x12", "\xBB\xA3\x4F\xC9\xCC", LIBC_EXPECT},
		{"\x05\xFF\x96\xB7\x1B", "\x64\x7D\x5F\xF4\xE5", LIBC_EXPECT},
		{"\x57\xD3\x46\xA1\x20", "\xCD\xC8\xA1\xB5\x3C", LIBC_EXPECT},
		{"\xD2\xAE\x47\xCF\x5F", "\x3B\x71\xC0\x63\x9A", LIBC_EXPECT},
		{"\xBC\x25\xAE\x3E\x2B", "\xB6\x93\xD2\x3A\x34", LIBC_EXPECT},
		{"\x38\x2E\x08\x53\xAF", "\xDB\x0D\x78\x48\x4E", LIBC_EXPECT},
		{"\x51\x32\x86\x49\xE4", "\x8A\x57\xF7\x76\xF4", LIBC_EXPECT},
		{"\x21\xA7\xF4\x25\xD8", "\x02\x1D\xD6\xC2\xFA", LIBC_EXPECT},
		{"\x47\x57\xB9\xE0\x0F", "\xFF\x07\x78\x69\x09", LIBC_EXPECT},
		{"\xE4\x30\x46\x50\x51", "\x0A\xC8\xAD\x78\x75", LIBC_EXPECT},
		{"\xE3\x1D\x83\x14\x7B", "\xE5\xAA\xC5\xCD\x68", LIBC_EXPECT},
		{"\xAC\x58\xAC\x06\x1A", "\x26\xFD\x3E\x5E\x8D", LIBC_EXPECT},
		{"\xFB\x4B\x44\xD7\x2D", "\xE9\x85\xBC\x31\xE9", LIBC_EXPECT},
		{"\xCF\xF5\x6A\x58\x1B", "\xF0\x8C\x77\xDA\x49", LIBC_EXPECT},
		{"\x58\xD7\x13\x46\x2D", "\xEB\x8A\x84\x05\x12", LIBC_EXPECT},
		{"\x17\x29\x4C\xD6\x11", "\x97\x28\xC0\xE1\x60", LIBC_EXPECT},
		{"\xAE\xFC\xD9\x05\x8E", "\xDE\xE9\x11\xD6\xFD", LIBC_EXPECT},
		{"\xBC\x8F\xE9\x73\x31", "\x24\xB6\x39\x39\xED", LIBC_EXPECT},
		{"\xD1\x18\xD7\x73\xFE", "\x70\xA9\xD4\x5B\xAB", LIBC_EXPECT},
		{"\x8D\x21\xB4\x13\x23", "\xCE\x38\x1A\xE5\x5A", LIBC_EXPECT},
		{"\x0C\x62\x93\x71\x24", "\x3A\x24\xFE\xBA\x29", LIBC_EXPECT},
		{"\x2A\xB4\xCB\x0B\xD4", "\xD2\x7E\x97\x1D\x8B", LIBC_EXPECT},
		{"\x34\x83\x0E\xE3\xAD", "\x4B\x94\xC7\x69\xB6", LIBC_EXPECT},
		{"\xAA\x14\xE4\x14\x35", "\x9D\xE9\x31\xD7\xD1", LIBC_EXPECT},
		{"\xBA\x9C\xC2\xBE\x3C", "\x39\x7C\xD9\x61\x6F", LIBC_EXPECT},
		{"\xE6\xAE\x3D\xB0\x6F", "\xDC\x87\xBA\xFC\x2D", LIBC_EXPECT},
		{"\xB0\x2E\xA7\x40\x75", "\x53\x74\x42\xF8\x3B", LIBC_EXPECT},
		{"\xB5\x5C\x57\xF4\x3E", "\xF8\x16\x4F\xD7\x50", LIBC_EXPECT},
		{"\x55\xE3\x4F\x86\x9A", "\xE1\x00\x87\x8E\xD6", LIBC_EXPECT},
		{"\x4B\x70\x50\x7A\xB8", "\x54\xE5\x14\x2A\x1C", LIBC_EXPECT},
		{"\x9E\x22\xF2\xF6\x88", "\x3B\x13\x2D\x52\xE9", LIBC_EXPECT},
		{"\x33\xA4\x98\x98\xB2", "\x3B\xCA\xDF\x18\x7F", LIBC_EXPECT},
		{"\xEB\x4A\xAD\x84\xFF", "\x8C\x89\xAB\x78\x60", LIBC_EXPECT},
		{"\x11\xCC\xD2\xE8\xFA", "\x54\xBF\x31\x5A\x48", LIBC_EXPECT},
		{"\xA4\xC9\xA0\xC9\x82", "\xEB\xA5\x01\x26\xE2", LIBC_EXPECT},
		{"\xD1\x66\xF2\xC0\x90", "\x0D\x47\x6D\x0E\x19", LIBC_EXPECT},
		{"\x39\x92\xFE\xF6\x82", "\x68\x9F\x56\x94\xD6", LIBC_EXPECT},
		{"\x49\xBF\x89\x15\x3A", "\xCC\x4B\x3D\x9C\xE5", LIBC_EXPECT},
		{"\x25\x3F\xAB\xA2\xF6", "\xD4\x34\xC8\xA1\x26", LIBC_EXPECT},
		{"\xA9\x44\x2A\xFE\x18", "\x8E\x5F\xE0\x1F\x34", LIBC_EXPECT},
		{"\x23\x5F\x2E\xBA\xA1", "\xA9\x39\xC0\xD4\x5D", LIBC_EXPECT},
		{"\x47\x3A\xE7\x69\xDB", "\x6F\xDD\xC2\xAF\xCB", LIBC_EXPECT},
		{"\xE9\x1A\x49\x8A\x12", "\xB7\x2D\x2B\x61\x12", LIBC_EXPECT},
		{"\x42\xBC\x67\x79\x68", "\x2D\xC4\x6A\x7A\x2F", LIBC_EXPECT},
		{"\x34\xB7\xEA\x6A\xBA", "\x5E\x6A\x5F\x05\x64", LIBC_EXPECT},
		{"\x1F\x1C\x5C\x84\x8B", "\x5C\x0E\x98\x27\xE1", LIBC_EXPECT},
		{"\x79\x49\x46\x64\x4D", "\xAD\x19\xC9\xB8\x5E", LIBC_EXPECT},
		{"\x81\xFB\xC2\xDA\x2D", "\x26\xE6\x91\xED\x92", LIBC_EXPECT},
		{"\x42\xFA\x48\x54\xA6", "\x1B\xC3\x07\x21\x2F", LIBC_EXPECT},
		{"\x39\x15\x95\xFB\x4D", "\xF9\x7C\xF7\xE3\xE5", LIBC_EXPECT},
		{"\x59\xE3\x56\x65\xCB", "\x19\x67\x59\xFC\x34", LIBC_EXPECT},
		{"\x6A\x3D\x59\x6B\xDD", "\xFF\x68\x6C\x65\x16", LIBC_EXPECT},
		{"\xD3\xED\x67\x17\x10", "\x43\x4E\x81\x3D\x59", LIBC_EXPECT},
		{"\x7D\x5C\xF0\xFA\x99", "\x99\xC3\xC3\x17\x68", LIBC_EXPECT},
		{"\x87\xAF\x38\x13\x87", "\xBC\x11\xC8\xA4\xE2", LIBC_EXPECT},
		{"\x49\xB9\x4E\xE4\x6A", "\xD3\x59\xD6\x83\x0E", LIBC_EXPECT},
		{"\x81\x89\xD0\x58\x8E", "\x59\x2A\xBE\x13\xEA", LIBC_EXPECT},
		{"\x1C\xDC\x20\x75\x0F", "\x95\xEC\xA5\x0D\xBF", LIBC_EXPECT},
		{"\x48\x19\xEF\x84\x9C", "\x45\x38\xF2\x97\xF4", LIBC_EXPECT},
	};

	i = 3;
	test(tab, NELEM(tab), LIBC_EXPECT);
}

// TEST 04 --> Different Sizes
ATF_TC(test04);
ATF_TC_HEAD(test04, tc)
{
	atf_tc_set_md_var(tc, "descr", test_titles[4]);
}
ATF_TC_BODY(test04, tc)
{
	t_input	tab[] = {
		{"]M~", "-MH~W]cG9", LIBC_EXPECT},
		{"@UoF|9", "nvm1h3v|cn((", LIBC_EXPECT},
		{"9xha*2Zx:s", "*%G|12Cej~$", LIBC_EXPECT},
		{"XN_.mG", "a;I%L`Tml", LIBC_EXPECT},
		{"Z1!'", "j`\\`", LIBC_EXPECT},
		{"06.nQ%Fc-", "[^f1>q]B<\\1", LIBC_EXPECT},
		{"/^E]&CfdZ", "mc>$k-PDwR[`", LIBC_EXPECT},
		{"W'qG* v|A", "xl0)uO4`", LIBC_EXPECT},
		{",s*5(*", "wK:", LIBC_EXPECT},
		{"_OX:4:WEP", "Jjcj'", LIBC_EXPECT},
		{"^w/3dQ3'O+\\=", "G>Z;$-bQB", LIBC_EXPECT},
		{"'Oc/", "T&MB7r=C4O", LIBC_EXPECT},
		{"4yF^4S6z", "DWQz$z7q}#$", LIBC_EXPECT},
		{"WY#($=l1", ")S4w(lM8", LIBC_EXPECT},
		{"fTm", "U %K1mFn", LIBC_EXPECT},
		{"9Rk_j5M", "@:d6PHaNa<F", LIBC_EXPECT},
		{"vqe", "y{)3rb", LIBC_EXPECT},
		{"rZj", "B1pG-`tIM9", LIBC_EXPECT},
		{"H5r&c624\\zL'", "{7_1%|%!V<*", LIBC_EXPECT},
		{"2VRD", "0%!ln/", LIBC_EXPECT},
		{"9|j", "}WlO}2", LIBC_EXPECT},
		{")W5kb", "|j_/~CXez{", LIBC_EXPECT},
		{"SVRivE25Ea{0", "q%UXrl}|\\k", LIBC_EXPECT},
		{"7wI`KB/ize[q", "yV1%Nr", LIBC_EXPECT},
		{"es@", "dq !)7RB", LIBC_EXPECT},
		{"1p'Cb7MjAd?", "h;W<-xBj", LIBC_EXPECT},
		{"q2#^WlnC", "PSax=", LIBC_EXPECT},
		{"U+:<F;5%", "M}Z+}\\b", LIBC_EXPECT},
		{"Xhm\\sg", ":b4@L~", LIBC_EXPECT},
		{"pei{EzLQ!", "{oW.*v", LIBC_EXPECT},
		{"6o'W[bgQu", "c];lkSa@oxc'", LIBC_EXPECT},
		{"l+3e$:*AZ^g", "PY%7;q", LIBC_EXPECT},
		{"f1J~", "do\\p7f#F[", LIBC_EXPECT},
		{":MJ/:_8!7||", "HeEFydCB+`/", LIBC_EXPECT},
		{"qZLH", "u Lg?s52P", LIBC_EXPECT},
		{"H_`8C", "aevg#l\\:(Vg", LIBC_EXPECT},
		{")\\w$?", "WyPo nhd!*<7", LIBC_EXPECT},
		{"rfjG4`djoF", "<8l|7", LIBC_EXPECT},
		{"NX|9FQSOaib", "wqqo2R", LIBC_EXPECT},
		{"XrLj,5G#6", "]VZ~#M79", LIBC_EXPECT},
		{"ikwR", "pkm^`PX@?", LIBC_EXPECT},
		{"\\Q^M|Y K%.&", "&]]5", LIBC_EXPECT},
		{"1]KE3kI(", "n)h:26>!Z", LIBC_EXPECT},
		{"grM+uQ:", "#Pf_?d!YD", LIBC_EXPECT},
		{"kCqqis{[|P", "gs_c", LIBC_EXPECT},
		{"+lR3L}", "+Y}o?C", LIBC_EXPECT},
		{"1jbP", "0R>F", LIBC_EXPECT},
		{"sr;9h", "C_)5?1U`", LIBC_EXPECT},
		{"KXG8K;>K", "srL)fn", LIBC_EXPECT},
		{"}-LU(>2", "NsQ /eAbN5J`", LIBC_EXPECT},
		{"L4 KA", "~4uj*u-?)", LIBC_EXPECT},
		{"IUm?qrF7", "PE*l", LIBC_EXPECT},
		{"$ID/E", "stU2X?b*l/", LIBC_EXPECT},
		{"WDju8;z,", "E6[u6Q|G3M", LIBC_EXPECT},
		{"piNa~.{#", "0^6rl-,K.^*", LIBC_EXPECT},
		{"/GfuZuy", "dW.", LIBC_EXPECT},
		{"2BQp2", "C,aA!", LIBC_EXPECT},
		{"l'Qd", "3~S0BX9)_K4", LIBC_EXPECT},
		{"Yzg!6PL+oI", "orgd=l_ tb}", LIBC_EXPECT},
		{"iK|", "(]q\\", LIBC_EXPECT},
		{"-y+ !%", "`Q{QarcIc7dm", LIBC_EXPECT},
		{"<(YW", "_:W2", LIBC_EXPECT},
		{"*Kao+", "5 K", LIBC_EXPECT},
		{"K`GXL6r", ":d&~$A(qbL,H", LIBC_EXPECT},
		{"e-.", "'W ^`G7", LIBC_EXPECT},
		{"~K4/xSyE@aJ", "|iO*YVIj!0}", LIBC_EXPECT},
		{")5Mws11", "(SJ9J", LIBC_EXPECT},
		{"5|h]A[f^m.z", "kR8dP)/M", LIBC_EXPECT},
		{"<}Oez", "!'*8B&3e8", LIBC_EXPECT},
		{"!aw0n", "kj-R", LIBC_EXPECT},
		{"XT[V(=eyX1=", "^,!Pv", LIBC_EXPECT},
		{"q*24s", "EYX*@rB", LIBC_EXPECT},
		{"]k.ZOZ2YgMB%", "V HK^X3>", LIBC_EXPECT},
		{"g}S'O%vJBL5", "|Ok2|/`D", LIBC_EXPECT},
		{"Sxb", "g~W6hT!n!q<J", LIBC_EXPECT},
		{"\\sTTT62", "rkj|kPq1&{S", LIBC_EXPECT},
		{"Nbla{FzX", "\\{gj7", LIBC_EXPECT},
		{"nicC`WW5", "eAqO+hq!IH", LIBC_EXPECT},
		{">[7?#}a?w'-6", "K:Ep/", LIBC_EXPECT},
		{"iE9w*cqG", "GZHWw", LIBC_EXPECT},
		{"i)&$dv=|", "L`h", LIBC_EXPECT},
		{"H#HDR", "vm*", LIBC_EXPECT},
		{"rX?(T%X3k", "crk2O>w4", LIBC_EXPECT},
		{"OOyQ|}8WcO", "7h+~)(.", LIBC_EXPECT},
		{"aM6A", "n94M", LIBC_EXPECT},
		{"*B+tt", "aNE~", LIBC_EXPECT},
		{"baF&;kv`", "?H8;Fi1@,", LIBC_EXPECT},
		{"t-voX}BRK2]P", "6w^E0nk+o", LIBC_EXPECT},
		{"MHYl+OlsSkZ", "$O)Lp%1(^", LIBC_EXPECT},
		{"c.7MMheMc", "W6ucZu1qPrn", LIBC_EXPECT},
		{"`gr2|", "!|6i", LIBC_EXPECT},
		{"a82kS+L4", "^vzg`iA", LIBC_EXPECT},
		{">}%s", "eX,I", LIBC_EXPECT},
		{"ns[^a(x@.t", "?T=y#gfk!a ", LIBC_EXPECT},
		{"9H8p=q1", "z9}@!6q", LIBC_EXPECT},
		{">flASJ-3", "r(x+9t!Z::B", LIBC_EXPECT},
		{"Q^b0m5v)Q", "q3P/P:R[g<cY", LIBC_EXPECT},
		{"gd'u", "JEk8]vi:", LIBC_EXPECT},
		{"|SP*-*|", "ke>EJ^#^ZZ8", LIBC_EXPECT},
		{"H3LB`ITpk", " r$?*", LIBC_EXPECT},
	};

	i = 4;
	test(tab, NELEM(tab), LIBC_EXPECT);
}

// TEST PROGRAM
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);
	ATF_TP_ADD_TC(tp, test01);
	ATF_TP_ADD_TC(tp, test02);
	ATF_TP_ADD_TC(tp, test03);
	ATF_TP_ADD_TC(tp, test04);

	return (atf_no_error());
}
