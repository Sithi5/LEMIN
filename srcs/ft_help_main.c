/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabouce <mabouce@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 15:52:25 by mabouce           #+#    #+#             */
/*   Updated: 2019/05/16 16:38:31 by mabouce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_lenint(int *tab, t_s *s)
{
	int		i;

	i = 0;
	while (tab[i] != -5 && i != s->totalroom)
		i++;
	return (i);
}

void	ft_calcul_nb_pipes(t_s *s)
{
	int		i;

	i = -1;
	s->liaisons = 0;
	while (++i < s->totalroom)
		s->liaisons += s->matrice[i][i];
}

int		ft_detect_room_or_pipe(t_s *s)
{
	if (ft_is_room(s) > 0)
	{
		s->oneroomisset = 1;
		if (s->settingpipe == 1)
			return (-2);
		if (!(ft_push_room(s)))
			return (-2);
	}
	else if (ft_is_pipe(s) > 0 && s->startset == 1 && s->endset == 1)
	{
		s->onepipeisset = 1;
		if (!(ft_push_pipe(s)))
			return (-2);
	}
	else if (s->onepipeisset == 0)
		return (-2);
	else
		return (2);
	return (1);
}

int		ft_detect_line_type(t_s *s)
{
	if (ft_strncmp(s->str, "##", 2) == 0 && s->str[2] && s->str[2] != '#')
	{
		if (ft_is_command(s) < 0)
			return (-2);
	}
	else if (ft_is_comment(s))
	{
		if (!(ft_list_push_back(&s->comment, ft_strdupd(s->str))))
			return (-2);
		return (1);
	}
	else if ((s->ret = ft_detect_room_or_pipe(s)) < 0)
		return (s->ret);
	if (!(ft_list_push_back(&s->input, ft_strdupd(s->str))))
		return (-2);
	return (1);
}
