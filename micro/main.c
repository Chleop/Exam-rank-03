/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:18:00 by cproesch          #+#    #+#             */
/*   Updated: 2021/11/04 17:22:16 by cproesch         ###   ########.fr       */
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
	draw->type = '\0';
	fscanf(fd, "%c", &(draw->type));
	draw->x = 0;
	fscanf(fd, "%f", &(draw->x));
	draw->y = 0;
	fscanf(fd, "%f", &(draw->y));
	draw->width = 0;
	fscanf(fd, "%f", &(draw->width));
	draw->height = 0;
	fscanf(fd, "%f", &(draw->height));
	fscanf(fd, "%s", (draw->pen));
	printf ("type = %c, x = %f, y = %f, width = %f, height = %f, pen = %s\n",
	draw->type, draw->x, draw->y, draw->width, draw->height, draw->pen);
	return;
}

void	set_zone(FILE *fd, t_data *data)
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

int	draw(float m, float n, int count, t_data *data)
{
	int i;

	i = 0;
	while (i < count)
	{
//		printf("n = %f, x = %f, m = %f, y = %f\n",n, (data->draw[i])->x, m, (data->draw[i])->y);
		
		if ((data->draw[i])->type == 'R')
		{
			if ((((int)(data->draw[i])->x < (int)n) && ((int)n < (int)((data->draw[i])->x + (data->draw[i])->width)))
				&& (((int)(data->draw[i])->y < (int)m) && ((int)m < (int)((data->draw[i])->y + (data->draw[i])->height))))
				write(1, ((data->draw)[i]->pen), 1);
			else
				write(1, (data->background_char), 1);
		}
		else if ((data->draw[i])->type == 'r')
		{
			if (((((int)((data->draw[i])->x) - (int)n) == 0) && ((data->draw[i])->y < (int)m))
				|| ((((int)((data->draw[i])->y) - (int)m) == 0) && ((data->draw[i])->x < (int)n)))
				write(1, ((data->draw)[i]->pen), 1);
			else
				write(1, (data->background_char), 1);
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
	float	m;
	float	n;
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
	set_zone(fd, data);
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
		write(1, "\n", 1);
		m++;
	}
	return (0);
}
