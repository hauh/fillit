/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 15:58:37 by smorty            #+#    #+#             */
/*   Updated: 2019/04/24 20:30:15 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	free_tetris(t_tetris *list)
{
	int	i;

	if (list)
	{
		free_tetris(list->next);
		i = 0;
		while (list->figure[i])
		{
			free(list->figure[i]);
			i++;
		}
		free(list->figure);
		free(list);
	}
}

static void	print_and_free(char **square)
{
	int i;

	i = 0;
	while (square[i])
	{
		ft_putendl(square[i]);
		free(square[i]);
		i++;
	}
	free(square);
}

static void	usage(void)
{
	ft_putstr("usage: fillit file\n");
	exit(1);
}

void		error(void)
{
	ft_putstr("error\n");
	exit(1);
}

int			main(int argc, char **argv)
{
	char		**solution;
	t_tetris	*list;
	int			fd;

	if (argc != 2)
		usage();
	validate(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error();
	list = store_tetris(fd);
	close(fd);
	if (!list)
		error();
	solution = fillit(list);
	free_tetris(list);
	if (!solution)
		error();
	print_and_free(solution);
	return (0);
}
