//
// Created by Jamar Slave on 10/01/2020.
//

#include "ft_printf.h"

void        check_zero(t_pf *pf)
{
    if (pf->width < 1 && (pf->precision == 0 || pf->precision == -1))
    {
        pf->filling = ft_strdup("");
        if (pf->need_format == 1)
            pf->filling = ft_strjoinfree_both(ft_strdup("0"), pf->filling);
    }
   else if (pf->width > 1 && (pf->precision == 0 || pf->precision == -1))
   {
       ft_memset(pf->filling, ' ', pf->width);
       if (pf->need_format == 1 && pf->align_left == 0)
           pf->filling[pf->width - 1] = '0';
       if (pf->need_format == 1 && pf->align_left == 1)
           pf->filling[0] = '0';
   }
}

void		print_int_oct(t_pf *pf)
{
    unsigned long long int num;

    num = ft_atoi_long_long_uns(pf->filling);
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
    if (pf->need_sign == 1 && num)
        handle_int_sign(pf, num);
    if (pf->need_spase == 1 && pf->need_sign != 1)
        handle_int_space_sec(pf, num);
    if (num == 0)
        check_zero(pf);
    ft_putstr(pf->filling);
    pf->printed+=ft_strlen(pf->filling);
}

int		handle_oct(t_pf *pf)
{
    unsigned long long int num;
    num = 0;

   if (pf->size_flag == NULL)
        num = (unsigned int)va_arg(pf->ap, unsigned int);
   else if (ft_strequ(pf->size_flag, "hh") == 1)
        num = (unsigned char)va_arg(pf->ap, unsigned int);
   else if (ft_strequ(pf->size_flag, "h") == 1)
        num = (unsigned short)va_arg(pf->ap, unsigned int);
   else if (ft_strequ(pf->size_flag, "ll") == 1)
        num = (unsigned long long int)va_arg(pf->ap, unsigned long long int);
   else if (ft_strequ(pf->size_flag, "l") == 1)
        num = (unsigned long int)va_arg(pf->ap,  unsigned long int);
   pf->filling = ft_itoa_base_unsigned(num, 8);
   if (pf->need_format == 1 && num)
        pf->filling = ft_strjoinfree_both(ft_strdup("0"), pf->filling);//
   print_int_oct(pf);
   return (pf->printed);
};