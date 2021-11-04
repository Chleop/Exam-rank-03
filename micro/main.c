/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:18:00 by cproesch          #+#    #+#             */
/*   Updated: 2021/11/04 18:31:29 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "micro_paint.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	nbr;
	int		n;

	i = 0;
	nbr = 0;
	n = 1;
	while ((str[i] == ' ') || ((str[i] >= '\t') && (str[i] <= '\r')))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			n = -n;
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		nbr = (nbr * 10) + (str[i] - 48);
		i++;
		if ((n * nbr) > 2147483647)
			return (-1);
		if ((n * nbr) < -2147483648)
			return (0);
	}
	return (n * (int)nbr);
}

void	set_draw_param(FILE *fd, t_draw *draw)
{
	float f;

	draw->type = '\0';
	fscanf(fd, "%c", &(draw->type));
	fscanf(fd, "%f", &f);
	draw->x = (int)f;
	fscanf(fd, "%f", &f);
	draw->y = (int)f;
	fscanf(fd, "%f", &f);
	draw->width = (int)f;
	fscanf(fd, "%f", &f);
	draw->height = (int)f;
	fscanf(fd, "%s", (draw->pen));
	printf ("type = %c, x = %d, y = %d, width = %d, height = %d, pen = %s\n",
	draw->type, draw->x, draw->y, draw->width, draw->height, draw->pen);
	return;
}

void	set_zone_param(FILE *fd, t_data *data)
{
	char	str[1000];

	fscanf(fd, "%s", str);
	data->width = ft_atoi(str);
	fscanf(fd, "%s", str);
	data->height = ft_atoi(str);
	fscanf(fd, "%s", data->background_char);
	printf ("w = %d, h = %d, bc = %s\n", data->width, data->height, data->background_char);
	return ;
}

int	draw(int m, int n, int count, t_data *data)
{
	int 	i;
	char	type;
	int		x;
	int	y;
	int	width;
	int	height;

	i = 0;
	while (i < count)
	{
		type = (data->draw[i])->type;
		x = (data->draw[i])->x;
		y = (data->draw[i])->y;
		width = (data->draw[i])->width;
		height = (data->draw[i])->height;		
		if (type == 'R')
		{
			if (((n > x) && ((x + width) >= n)) && ((m > y) && ((y + height) >= m)))
				data->tab[m][n] = (data->draw)[i]->pen;
			else
				data->tab[m][n] = data->background_char;
		}
		else if (type == 'r')
		{
			if ((((n == (x + 1)) && ((m > y) && ((y + height) >= m))) || ((m == (y + 1)) && ((n > x) && ((x + width) >= n))))
				|| (((n == (x + width)) && ((m > y) && ((y + height) >= m))) || ((m == (y + height)) && ((n > x) && ((x + width) >= n)))))
				data->tab[m][n] = (data->draw)[i]->pen;
			else
				data->tab[m][n] = data->background_char;
		}
		else
		{
			ft_putstr("Error\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	main (int argc, char **argv)
{
	FILE	*fd;
	t_data	*data;
	int		i;
	int		count_line;
	int	m;
	int	n;
	char	c;

	data = malloc (1 * sizeof(t_data));
	if (argc != 2)
	{
		ft_putstr("Error: argument\n");
		return (1);
	}
	fd = fopen(argv[1], "r");
	if (fd < 0)
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	set_zone_param(fd, data);
	i = 0;
	while (fscanf(fd, "%c", &c) != EOF)
	{
		set_draw_param(fd, (data->draw)[i]);
		i++;
	}
	count_line = i;
	m = 0;
	while (m < data->height)
	{
		n = 0;
		while (n < data->width)
		{
			if (draw(m, n, count_line, data) < 0)
				return (1);
			n++;
		}
		m++;
	}
	m = 0;
	while (m < data->height)
	{
		n = 0;
		while (n < data->width)
		{
			write(1, data->tab[m][n], 1);
			n++;
		}
		write(1, "\n", 1);
		m++;
	}
	return (0);
}
