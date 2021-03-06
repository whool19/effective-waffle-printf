/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ints.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 16:17:57 by jslave            #+#    #+#             */
/*   Updated: 2019/12/26 16:17:58 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void        turn_width_more_prec(t_pf *pf, long long int num, int len)
{
    char *zero;
    if (num < 0 && ft_strlen(pf->str_empty) > (size_t)find_step(num))
    {
        if (pf->precision < pf->width)
        {
            if (pf->align_left == 1)
            {
                ft_memcpy(pf->str_empty, pf->filling, ft_strlen(pf->filling));
            }
            else
            {
                int test = find_step(num);
                if (pf->precision >= test)
                {
                   pf->filling = ft_itoa_long_long(num * -1);///FREEE
                    int test2 = pf->precision - ft_strlen(pf->filling);
                    zero = ft_strnew(test2);
                    ft_memset(zero, '0', test2);
                    pf->filling = ft_strjoinfree_both(zero, pf->filling);////FREEEEEE
                    pf->filling = ft_strjoinfree_both(ft_strdup("-"), pf->filling);
                    ft_memcpy(&pf->str_empty[pf->width - ft_strlen(pf->filling)], pf->filling, ft_strlen(pf->filling));
                }
                else
                    ft_memcpy(&pf->str_empty[pf->width - len], pf->filling, ft_strlen(pf->filling));
            }
            free(pf->filling);
            pf->filling = ft_strdup(pf->str_empty);
        }
    }
    else if (ft_strlen(pf->str_empty) > (size_t)len)
    {
        if (pf->align_left != 1)
            ft_memcpy(&pf->str_empty[pf->width - len], pf->filling, len);
        else
            ft_memcpy(pf->str_empty, pf->filling, len);
        free(pf->filling);
        pf->filling = ft_strdup(pf->str_empty);
    }
}

void        handle_int_precision_sec(t_pf *pf, long long int num)
{
    char *zero;
    int len;

    len = ft_strlen(pf->filling);
    if (pf->precision > len)
    {
        if (num < 0)
        {
            pf->filling = ft_itoa_long_long(num * -1);///FREEE
            len--;
        }
        zero = fill_zero_string(pf, len, num);
        pf->filling = ft_strjoinfree_both(zero, pf->filling);////FREEEEEE
        if (num < 0)
            put_sign(pf, num);
    }
}

void        handle_int_width_and_precision_sec(t_pf *pf, long long int num)
{
    int len;

    handle_int_precision_sec(pf, num);
    len = ft_strlen(pf->filling);
    if (pf->width > pf->precision )
    {
        if (pf->precision != 0 && pf->precision != -1)
            turn_width_more_prec(pf, num, len);
        else if (pf->precision <= 0 && num == 0)
        {
            free(pf->filling);
            pf->filling = ft_strdup(pf->str_empty);
            if (pf->need_sign == 1 && pf->align_left != 1)
                pf->filling[ft_strlen(pf->filling) - 1] = '+';
            else if (pf->need_sign == 1 && pf->align_left == 1)
                pf->filling[0] = '+';
        }
    }
    else
        handle_int_precision_sec(pf, num);
}

void        handle_int_width_sec(t_pf *pf, long long int num)
{
    int len;

    len = ft_strlen(pf->filling);
    if (pf->width > len)
    {
        if (num < 0)
            fill_empty_str_neg_num(pf, len, num);
        else
            fill_empty_str_pos_num(pf, len);
        pf->filling = ft_strdup(pf->str_empty);
    }
}

void        turn_width_more_prec_prec_more_num(t_pf *pf, int len , int i)
{
    if ((i == len || i == 0) && pf->filling[pf->width -1] != ' ')
        pf->filling = ft_strjoinfree_both(ft_strdup("+"), pf->filling);
    else if ((i == len || i == 0) && pf->filling[pf->width -1] == ' ')
    {
        i = pf->width -1;
        while (pf->filling[i] == ' ')
            i--;
        while (i >= 0)
        {
            pf->filling[i + 1] = pf->filling[i];
            i--;
        }
        pf->filling[0] = '+';
    }
    else if (i < len && i)
    {
        if (pf->filling[0] == '0')
            pf->filling[0] = '+';
        else if (pf->filling[i - 1])
            pf->filling[i - 1] = '+';
    }
}

void        turn_width_more_prec_prec_less_num(t_pf *pf, int len, int i, int num)
{
    if (i == 0 && pf->zero_filling == 1 && pf->width > find_step(num) && pf->align_left != 1)
        pf->filling[0] = '+';
    else if ((i == len || i == 0) && pf->filling[pf->width -1] != ' ')
        pf->filling = ft_strlen(pf->filling) ? ft_strjoinfree_s2(ft_strdup("+"), pf->filling) : ft_strjoin(ft_strdup("+"), pf->filling);//////////leak
    else if ((i == len || i == 0) && pf->filling[pf->width -1] == ' ' && num)
    {
        i = pf->width -1;
        while (pf->filling[i] == ' ')
            i--;
        while (i >= 0)
        {
            pf->filling[i + 1] = pf->filling[i];
            i--;
        }
        pf->filling[0] = '+';
    }
    else if (i < len || (num == 0 && i == len)) {
        if (pf->filling[0] == '0' || (pf->filling[i - 1] && pf->align_left == 1))
            pf->filling[0] = '+';
        else if (pf->filling[i - 1] && pf->align_left != 1)
            pf->filling[i - 1] = '+';
    }
}

void        handle_int_sign(t_pf *pf, long long int num)
{
    int i;
    char stop;
    int len;

    len = (int)ft_strlen(pf->filling);
    i = 0;
    stop = ' ';
    while (pf->filling[i] == stop && pf->filling[i] != '\0')
        i++;
   if (pf->precision > find_step(num) && pf->width > pf->precision)
       turn_width_more_prec_prec_more_num(pf, len , i);
   else if (pf->precision < find_step(num) && pf->width > pf->precision)
       turn_width_more_prec_prec_less_num(pf, len, i, num);
   else if ((pf->width == 0 && pf->precision < 0) || pf->width <= pf->precision)
       pf->filling = ft_strlen(pf->filling) ? ft_strjoinfree_both(ft_strdup("+"), pf->filling) : ft_strjoin(ft_strdup("+"), pf->filling);/////////leak
}

void        handle_int_space_sec(t_pf *pf, long long int num)
{
    int len;

    if (handle_max_and_min_long_long(pf) == 1)
        return;
    len = find_step((int)num);
    if (num >= 0 && pf->need_sign != 1)
    {
        if (pf->width <= len)
            pf->filling = ft_strjoinfree_both(ft_strdup(" "), pf->filling);////FREEEE
        if (pf->width > len + 1 && pf->align_left == 1)
            ft_str_overlap_copy(pf->filling);
        pf->filling[0] = ' ';
    }
}

void        print_int_second_edition(t_pf *pf, long long int num)
{
    if (pf->precision >= 0 && pf->width > 0)
        handle_int_width_and_precision_sec(pf, num);
    else if (pf->precision < 0)
    {
        if (pf->width != 0)
            handle_int_width_sec(pf, num);
        else
            handle_int_precision_sec(pf, num);
    }
    else if (pf->precision > 0 && pf->precision > find_step(num))
        handle_int_precision_sec(pf, num);
    if (pf->need_sign == 1 && num >= 0)
        handle_int_sign(pf, num);
    if (pf->need_spase == 1 && pf->need_sign != 1)
        handle_int_space_sec(pf, num);
    ft_putstr(pf->filling);
    pf->printed+=ft_strlen(pf->filling);
}


int		    handle_int(t_pf *pf)
{
	long long int num;

	num = 0;
	free(pf->filling);///TEST
	if (ft_strequ(pf->size_flag, "") == 1)//////////////////////////EXAMPLEE
		num = va_arg(pf->ap, int);
	else if (ft_strequ(pf->size_flag, "hh") == 1)
		num = (signed char)va_arg(pf->ap, int);
	else if (ft_strequ(pf->size_flag, "h") == 1)
		num = (short)va_arg(pf->ap, int);
	else if (ft_strequ(pf->size_flag, "ll") == 1)
		num = (long long int)va_arg(pf->ap, long long int);
	else if (ft_strequ(pf->size_flag, "l") == 1)
		num = (long int)va_arg(pf->ap,  long int);
	if (num == 0 && (pf->precision == -1 || pf->precision == 0))
	    pf->filling = "";
	else
	    pf->filling = ft_itoa_long_long(num);///itoa long long!
	print_int_second_edition(pf, num);
    return (pf->printed);
}

void        ft_str_overlap_copy(char *str)
{
    char *tmp;
    size_t len;
    int i;
    int j;

    i = 1;
    j = 0;
    len = ft_strlen(str);

    tmp = ft_strnew(len);
    ft_memcpy(tmp, str, len);
    while (len-1)
    {
        str[i] = tmp[j];
        i++;
        j++;
        len--;
    }
    free(tmp);
}

int handle_max_and_min_long_long(t_pf *pf)
{
    if (ft_strequ(pf->filling, "9223372036854775807") == 1)
    {
        pf->filling = " 9223372036854775807";
        return (1);
    }
    else if (ft_strequ(pf->filling, "-9223372036854775807") == 1)
    {
        pf->filling = "-9223372036854775807";
        return (1);
    }
    return (0);
}
