/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:56:21 by jslave            #+#    #+#             */
/*   Updated: 2019/12/17 16:56:23 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		handle_char(t_pf *pf)
{
	char alpha;

	alpha = va_arg(pf->ap, int);
	if (alpha != '\0')
	{
		pf->filling = ft_memalloc(sizeof(char) * 2);
		pf->filling[0] = alpha;
	}
	else
	{
		pf->filling = ft_memalloc(sizeof(char));
		pf->printed = 1;//////nado ili net?
	}
};

void		handle_string(t_pf *pf)
{
	pf->filling = (char *)va_arg(pf->ap, char *);///prec!!!!
	if (pf->filling == NULL && pf->precision != -1)
		pf->filling = ("(null)");
};

void		handle_percent(t_pf *pf)
{
	pf->filling = ft_memalloc(sizeof(char) *2);
	pf->filling[0] = '%';
};
