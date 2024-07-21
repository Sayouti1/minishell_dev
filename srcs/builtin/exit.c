#include "../../include/include.h"

//
// Created by aes-sayo on 7/13/24.
//

int    ft_exit(char **arg)
{

    if (NULL == arg)
    {
        set_exit_status(0);
        exit(0);
    }
    if (split_len(arg) > 1)
        return (printf("exit: too many arguments\n"), set_exit_status(1));
    if (str_isdigit(arg[0]) == 2)
    {
        set_exit_status(2);
        exit(2);
    }
    set_exit_status(ft_atoi(arg[0]));
    exit(ft_atoi(arg[0]));
}