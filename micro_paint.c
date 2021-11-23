#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

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

void    print_rect(char rect[300][300], int width, int height)
{
    int     i;
    int     j;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            ft_putchar(rect[i][j]);
            j++;
        }
        ft_putchar('\n');
        i++;
    }
}

int main(int argc, char **argv)
{
    FILE    *fd;
    char    rect[300][300];
    int     i;
    int     j;
    int     ret;
    int     width;
    int     height;
    char    back_char;
    char    type;
    float   x;
    float   y;
    float   w;
    float   h;
    char    c;

    if (argc != 2)
    {
        ft_putstr("Error: argument\n");
        return (1);
    }
    if (!(fd = fopen(argv[1], "r"))
        || ((fscanf(fd, "%d %d %c\n", &width, &height, &back_char) != 3)
        || (width <= 0) || (width > 300) || (height <= 0) || (height > 300)))
    {
        ft_putstr("Error: Operation file corrupted\n");
        return (1);
    }
//    printf ("width = %d, height = %d, background = %c\n", width, height, back_char);
    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            rect[i][j] = back_char;
            j++;
        }
        i++;
    }
    while (1)
    {
        ret = fscanf(fd, "%c %f %f %f %f %c\n", &type, &x, &y, &w, &h, &c);
//        printf("ret = %d\n", ret);
 //       printf("type = %c, x = %f, y = %f, w = %f, h = %f, c = %c\n", type, x, y, w, h, c);
        if (ret == 6)
        {
            if ((w <= 0) || (h <= 0) || ((type != 'r') && (type != 'R')))
            {
                ft_putstr("Error: Operation file corrupted\n");
                break;
            }
            else
            {
                i = 0;
                while (i < height)
                {
                    j = 0;
                    while (j < width)
                    {
                        if (((float)j >= x) && ((float)j <= (x + w)) && ((float)i >= y) && ((float)i <= (y + h)))
                        {
                            if (type == 'r')
                            {
                                if (((float)j < (x + 1)) || ((float)j > (x + w - 1)) || ((float)i < (y + 1)) || ((float)i > (y + h - 1)))
                                    rect[i][j] = c;
                            }
                            else
                                rect[i][j] = c;
                        }
                        j++;
                    }
                    i++;
                }
            }
        }
        else if (ret == EOF)
        {
            print_rect(rect, width, height);
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