#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct  s_back
{
    FILE    *fd;
    char    rect[300][300];
    int     width;
    int     height;
    char    c;
}   t_back;

typedef struct  s_operation
{
    char    type;
    float   x;
    float   y;
    float   r;
    char    c;
}   t_operation;

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void    ft_putstr(char *str)
{
    if (!str)
        return;
    write(1, str, ft_strlen(str));
}

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    print_rect(t_back *back)
{
    int     i;
    int     j;

    i = 0;
    while (i < back->height)
    {
        j = 0;
        while (j < back->width)
        {
            ft_putchar(back->rect[i][j]);
            j++;
        }
        ft_putchar('\n');
        i++;
    }
}

void    draw_background(t_back *back)
{
    int     i;
    int     j;

    i = 0;
    while (i < back->height)
    {
        j = 0;
        while (j < back->width)
        {
            back->rect[i][j] = back->c;
            j++;
        }
        i++;
    }
}

void    draw_operation(t_back *back, t_operation *operation)
{
    int     i;
    int     j;

    i = 0;
    while (i < back->height)
    {
        j = 0;
        while (j < back->width)
        {
            if ((sqrtf(((float)j - operation->x) * ((float)j - operation->x) + ((float)i - operation->y) * ((float)i - operation->y))) <= operation->r)
            {
                if (operation->type == 'c')
                {
                    if ((sqrtf(((float)j - operation->x) * ((float)j - operation->x) + ((float)i - operation->y) * ((float)i - operation->y))) > (operation->r - 1))
                        back->rect[i][j] = operation->c;
                }
                else
                    back->rect[i][j] = operation->c;
            }
            j++;
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    t_back      back;
    t_operation operation;
    int         ret;

    if (argc != 2)
    {
        ft_putstr("Error: argument\n");
        return (1);
    }
    if (!(back.fd = fopen(argv[1], "r"))
        || ((fscanf(back.fd, "%d %d %c\n", &(back.width), &(back.height), &(back.c)) != 3)
        || (back.width <= 0) || (back.width > 300) || (back.height <= 0) || (back.height > 300)))
    {
        ft_putstr("Error: Operation file corrupted\n");
        return (1);
    }
    draw_background(&back);
    while (1)
    {
        ret = fscanf(back.fd, "%c %f %f %f %c\n", &(operation.type), &operation.x, &operation.y, &operation.r, &operation.c);
        if (ret == 5)
        {
            if ((operation.r <= 0) || ((operation.type != 'c') && (operation.type != 'C')))
            {
                ft_putstr("Error: Operation file corrupted\n");
                break;
            }
            else
                draw_operation(&back, &operation);
        }
        else if (ret == EOF)
        {
            print_rect(&back);
            return (0);
        }
        else
        {
            ft_putstr("Error: Operation file corrupted\n");
            break;
        }
    }
    return (1);
}
