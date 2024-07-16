#include "../../include/include.h"

//
// Created by aes-sayo on 7/13/24.
//

int    ft_exit(char *arg)
{

    if (NULL == arg)
    {
        set_exit_status(0);
        exit(0);
    }
    if (str_isdigit(arg) == 2)
    {
        set_exit_status(2);
        exit(2);
    }
    set_exit_status(ft_atoi(arg));
    exit(ft_atoi(arg));
}