/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:18:50 by cproesch          #+#    #+#             */
/*   Updated: 2021/11/04 18:28:35 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICRO_PAINT_H
# define MICRO_PAINT_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef	struct s_draw
{
	char	type;
	int		x;
	int		y;
	int		width;
	int		height;
	char	pen[2];
}	t_draw;

typedef	struct s_data
{
	int		width;
	int		height;
	char	background_char[2];
	t_draw	draw[1000][1000];
	char	*tab[1000][1000];
}	t_data;

#endif

