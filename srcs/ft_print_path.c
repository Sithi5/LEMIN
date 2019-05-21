/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabouce <mabouce@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 11:51:01 by mabouce           #+#    #+#             */
/*   Updated: 2019/05/16 15:33:39 by mabouce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ft_dispatch_ants(int **tab, t_s *s)
{
	int		ants;
	int		i;
	int		max;

	max = 0;
	ants = s->nbant;
	while (ants && ++max < s->maxway && (i = -1))
		while (ants && ++i < max)
			while (ants && tab[i][0] + tab[i][1] != tab[max][0] + tab[max][1])
			{
				tab[i][1]++;
				ants--;
			}
	while (ants && (i = -1))
		while (++i < max)
		{
			if (ants == 0)
				break ;
			ants--;
			tab[i][1]++;
		}
	i = -1;
	while (++i < s->maxway)
		tab[i][1] > 0 ? tab[i][2] = 1 : 0;
}

static int		ft_print_path_while_malloc(t_s *s, t_list *beg, int **tab)
{
	while (++s->i < s->maxway)
	{
		s->j = -1;
		if (!(s->ants_in_way[s->i] = (int*)malloc(sizeof(int) * s->totalroom)))
			return (-9);
		if (!(tab[s->i] = (int*)malloc(sizeof(int) * 3)))
			return (-9);
		while (++s->j < s->totalroom)
			s->ants_in_way[s->i][s->j] = -5;
		tab[s->i][0] = s->algo == 1 ? ft_lenint(beg->ttab[0], s)
			: ft_lenint(beg->tab, s);
		tab[s->i][1] = 0;
		beg = beg->next;
	}
	ft_dispatch_ants(tab, s);
	!s->flag_n ? miniprintf("\n") : 0;
	if (!ft_color(s))
		ft_error(s, -10);
	return (1);
}

int				ft_print_path(t_s *s)
{
	int		number_ants;
	int		**tab;
	t_list	*beg;
	int		i;

	beg = s->finalways;
	s->maxway = ft_list_size(s->finalways);
	number_ants = 0;
	s->i = -1;
	s->k = s->maxway;
	if (!(s->ants_in_way = (int**)malloc(sizeof(int*) * (s->maxway))))
		ft_error(s, -9);
	if (!(tab = (int**)malloc(sizeof(int*) * (s->maxway))))
	{
		ft_inttabdel(&tab, s->maxway);
		ft_error(s, -9);
	}
	if ((i = ft_print_path_while_malloc(s, beg, tab)) < 0)
	{
		ft_inttabdel(&tab, s->maxway);
		ft_error(s, -9);
	}
	ft_print_path_suite(s, number_ants, tab);
	ft_inttabdel(&tab, s->maxway);
	return (1);
}
