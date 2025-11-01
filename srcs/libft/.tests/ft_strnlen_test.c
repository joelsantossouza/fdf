/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:55:34 by joesanto          #+#    #+#             */
/*   Updated: 2025/09/28 17:39:53 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <atf-c.h>
#include <stdio.h>

#define	NELEM(tab, data_type) (sizeof(tab) / sizeof(data_type))
#define RED		"\e[0;31m"
#define GREEN	"\e[0;32m"
#define RESET	"\e[0m"

static int	i;

void	test(char *strs[], int size, size_t expected)
{
	size_t		output;
	char		*color;

	printf("---> test%02d (Expected=%lu)\n", i, expected);
	while (size--)
	{
		output = ft_strnlen(strs[size], 100);
		color = expected == output ? GREEN : RED;

		printf("%s", color);
		printf("Input:\t%s\t\t\t\tOutput: %lu\n", strs[size], output);
		printf("%s", RESET);

		ATF_CHECK_EQ(expected, output);
	}
	printf("\n\n");
}

typedef struct s_input
{
	char	*str;
	size_t	maxlen;
}	t_input;

void	test_libc(t_input tab[], int size)
{
	size_t		output;
	size_t		expected;
	char		*color;

	printf("---> test%02d\n", i);
	while (size--)
	{
		expected = strnlen(tab[size].str, tab[size].maxlen);
		output = ft_strnlen(tab[size].str, tab[size].maxlen);
		color = expected == output ? GREEN : RED;

		printf("%s", color);
		printf("Input:    \t%s\n", tab[size].str);
		printf("Expected: \t%lu\n", expected);
		printf("Output:   \t%lu\n", output);
		printf("%s", RESET);

		ATF_CHECK_EQ(expected, output);
		printf("\n");
	}
}

// TEST 00
ATF_TC(test00);
ATF_TC_HEAD(test00, tc)
{
	atf_tc_set_md_var(tc, "descr", "String of size 0");
}
ATF_TC_BODY(test00, tc)
{
	char	*test00[] = {"", 0, "\0"};
	size_t	expected = 0;

	i = 0;
	test(test00, NELEM(test00, char *), expected);
}

// TEST 01
ATF_TC(test01);
ATF_TC_HEAD(test01, tc)
{
	atf_tc_set_md_var(tc, "descr", "String of size 1");
}
ATF_TC_BODY(test01, tc)
{
	char	*test01[] = {"a", "\n", "\001", "\177", "\x0a", "\200", "", "", "Z"};
	size_t	expected = 1;

	i = 1;
	test(test01, NELEM(test01, char *), expected);
}

// TEST 02
ATF_TC(test02);
ATF_TC_HEAD(test02, tc)
{
	atf_tc_set_md_var(tc, "descr", "String of size 32");
}
ATF_TC_BODY(test02, tc)
{
	char	*test02[] = {
		"W0gJvWSs0PqdrCNYo5cxIiMxd0EPXvUd",
		"qZLNW8RwHSTdjwjigW5tocnjQ28k6rS2",
		"hZ7jDCE1c82StgFLRztBGwFPeTAg48Bw",
		"QN7Umc862ZGKOSlR1HO2zbmoBpH90YeZ",
		"gKibl5vfUuwDIca8EfCJV3YQAXyL1P6t"
	};
	size_t	expected = 32;

	i = 2;
	test(test02, NELEM(test02, char *), expected);
}

// BONUS TEST
#ifdef LONG_STR
# include <string.h>
ATF_TC(test03);
ATF_TC_HEAD(test03, tc)
{
	atf_tc_set_md_var(tc, "descr", "String of long size");
}
ATF_TC_BODY(test03, tc)
{
	char	*test03[] = {
		LONG_STR
	};
	size_t	expected = strlen(LONG_STR);

	i = 3
	test(test03, NELEM(test03, char *), expected);
}
#endif

// TEST 04
ATF_TC(test04);
ATF_TC_HEAD(test04, tc)
{
	atf_tc_set_md_var(tc, "descr", "String of size 32");
}
ATF_TC_BODY(test04, tc)
{
	t_input	tab[] = {
		{"`79F*6(+LPWFkœ\\\"Wra?Zf/1λIMv^8Q94%Njl^(ö>œdµzFr]l`)9S3gMHv:wcfw-~2u}UUHMf]<n~Yñj!VC9ü", 21},
		{"tx}5>} f~sT0uµ<[t?:)λ8ΩvIccGqXg>Z};#>*m3anzLcGXµtUf'Oñ~C}l cKu~{]o_µp+lAß8ψQe[:Q:U", 71},
		{"(nkA5hös|SZJ`*öU=e-œ8JaV\\\\#T1j%6y$;RYdoψf`nO99?}P|;k0FkΩüdYzLbrñ{äv[", 95},
		{"m``,p*{ZX}λ<2-+}w)/`|Qm;ñze&)5", 18},
		{"ψ/3o<ijdlpkn@", 45},
		{"$7mDäyayU<%5XhäBl':}u2}k;ü*:E", 66},
		{"`HW?.ZuUs^Pö@^böAΩjψs4|tDZ}QP@E6\\\\*`8e^nΩV_JAO34F2uψ]Gλ77Xöjy:.dAtMu<b\\\"t,2", 63},
		{"µœ4>#W';Cµ|)J", 87},
		{"|λ8r$YIOU\\\\hœr0-|λ[)9WS{+KU*T=\\\"µ>;#Kw,jTF$xk", 8},
		{"Wgzq\\\\5λ\\\"λPMfV,pkpa}.$MqUψ\\\"iHI\\\"sPj|B_ßCkp_;y\\\"üS+T>ßcv59;9}hrW{Iñi);ß2ñvmGK1ZDm85-2Pög^]", 27},
		{"qeP.λV8Pö8obEµl.qkCF|", 88},
		{"FΩ@mI@0l/ZHCCZ.>bK:!3:λ^?7nw[^iAoE>2büeeM|:üfhQn*bs{", 39},
		{"#]Nej)yOh8 4<3[smhiyV#µ9Xpi3@H;G#M", 61},
		{":3lµ9üpüP", 75},
		{"6Ba*G!µ@yM\\\"e\\\\?G3œjCK}œl*2`ö!f0$6D.CdgLµM\\\" ?2q2λk;#mAG$?Mh?qh}ve`ñe@c'' 7T+^λG2@]lœ$y^öyANLcλLmcuv", 95},
		{"qz`r&.t<}3-?Q4>B]BDOMQmQ~t]h$7ddTQllnJœQ6Aa-tN$_0n@uywL/üxE4TX]Xl57c", 41},
		{"ä?.JFxuKä+9BU4MjäAOä\\\\ß9RWkœT$?!?ΩKi6*Unλpß9m%f_K z0lxG~0W_'FüTys|)`F/c 2KK,9]Z+I(k1V3", 16},
		{"wF}Qhßi;Yy|&kLψüJœVrQ NKT\\\"@fd4q85ßzmBRFPgKAS+tkhCB#cLWofdñJ[3FX( ñ<1jV_`9JiMBx(}M8u%", 56},
		{"0|Qkwv\\\\6?D~pZ5eJLpµ.0[ñEnoZRstxd6WqR@`S-œ+äPvy\\\\", 63},
		{"[|Fxua{äea o ObJßGnaœ", 61},
		{"8@uKäa_Jψhr~^qMVLcmF^}cQGl7#mXm\\\\-ötßV_oOytmc;Nλ1/I& -]/L3LPΩ| f`MB=}ylq[5steH7*) @λψ3qoh", 25},
		{"b#(iX=öQv\\\\#U::8>oUMRñxD6\\\\F7huw<+Y2;07\\\"^WQssx0hd1=~{IA=$+<qü6(.2[2#EF]@*;d-ä'Qj(*\\\"sF|üd|$d5.knG", 84},
		{"?\\\\E=#/E#,^:1Q8;X{b*%HDT}[tΩea]VcJœ(ψ*F@}WöI7vßwPWHP[e6FN[4cüvvßPFS#be<ooΩ4v2YUöü~Lk/S*^\\\\häZ b", 79},
		{"cH", 89},
		{"tAh\\\\=WzJCA>#&-7az", 37},
		{"3 5üd5!`IµTxh`H;uVßs`f5K)k&43gDAß{FvT\\\"ΩS.M>ßKStöu}9fL*W?\\\\d9\\\"ö\\\"@λQRaD@œ", 88},
		{"ñä_<0~t!wsn E&WoaJrvKL>Y_zψ5EIäQpñRñ{$1%hx_Wq('bF>ü!ödD6V[qV)%ψ RZgV~zrI/sH", 23},
		{"'H#ü93ß5s?gKe5t[TNmi)öm<Zi!wZNB{tAß", 86},
		{"ls.dvEl-P!G0M8XöBü-/~V:8}pUQarQ nPFΩ|PvA3ctG{7yO#f;Aœ X3d;JPuZ+i,o#T\\\\[,vñ%vtS,EbE", 36},
		{"/{ß~ClbSJXV,rbOAHUnnd[P\\\\*QIUBDΩΩmQA=^ FWGf$wQu", 98},
		{"~1_5VtB-=^ä5yxG>g/z^FTñE(_hFY7|Vœ>`Ce8Khpä4\\\"Wyfh&M)hj=-e{-jM;UλZJ2UΩ4/d~@R{tg_4öü9_dL_", 29},
		{"W>ilñ6?+z%<FQU)eäO9VnFWLF[ß'$k+6_Gk4Sλcœ$λ!$vLC'läiλ", 76},
		{"xüX:!\\\\J<Ωö8@btñs@EnY\\\"C`a5w<D*`G9.4ELn%~U=fr/NOΩ/Cp#dΩn]Q-\\\\ß[yeaö0_q=|_FTtUamsp^Z?", 48},
		{"p1FgYhuSyq']w4*wZFu~[4H^mSY:œ/#ßq/'HIj?;u;Bk$l\\\"LHICu;VuXI,oΩ7!#wUXxXyRkDöµAp*O^D", 7},
		{"l7f|g3Ω)z_\\\"<rDvvUE`Y[>2äl7NKXbe{\\\"œ |b(I&'hßö!f/_tNäµL^o6c*Qlw6SP_E~ß", 17},
		{"qTX8Q$QLTh?üsi-@eß%h/&/T> u8fHB,hœB)iλ;dqR", 51},
		{"@w0 LψuKAj=l&", 22},
		{"M1aQ[/kJWg]$ *[{#Wvüe^qAG|\\\"N(_CKdpV", 61},
		{")!0URytλNEH$|82_=K=-4$9fλ*nügH1f%7*äm@\\\\j^\\\\i)C]}*(\\\">$vFne,[ö", 49},
		{"'Hjm=0%Ui`x>C'RI~Cö0p!Käœ4/{Ppce-^Uä(q", 7},
		{"\\\\8Wp>7n[:8%];aZä,bXψy,Aiv\\\\g:BTxλi9J*qn;|a", 90},
		{"zuscü_pHµZy+gVZ-Rvvµß.Z!~R%^NchEAœλ(oy=B\\\\<ñ(2µo[q@sTSwQ~VqifTE", 49},
		{"Q", 2},
		{"F>^.Wp9I-1:EOψW|piœJmGYW9iXµ1µz*ΩdΩ@ß!vKλ#:üZsq%ßuk(=P$;JFq%Mz?%jf_ä[uDTjOΩn':v655", 20},
		{"/hf^~[h($r,6/HHßGAS>~pw,aö0s>vFe\\\"0/S9>p5töAUW}4kZm8d B 6n&œ!ñ'#FW9üßü>\\\\[k", 59},
		{"<.öX5#lt 9qü9r(7µQ#XC+4?mJaqyi_uKä6fP", 76},
		{"ψq@V<jqcMäd0'$0P%FhbYtiñ.\\\"dLSd??5yäe0n*B}T1W<oä", 82},
		{"iE1MñG,Ah}I6w%ΩKe)D]yψäncλ`40X!µSX7[/T]eJc_^|CrQ+v\\\\-G _Sß", 74},
		{"^b5Uh&EU:tG^/G\\\">ψ%<-$)q", 95},
		{"$U{wΩ1A46", 19},
	};

	i = 4;
	test_libc(tab, NELEM(tab, t_input));
}

// TEST PROGRAM
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);
	ATF_TP_ADD_TC(tp, test01);
	ATF_TP_ADD_TC(tp, test02);
#ifdef LONG_STR
	ATF_TP_ADD_TC(tp, test03);
#endif
	ATF_TP_ADD_TC(tp, test04);

	return atf_no_error();
}
