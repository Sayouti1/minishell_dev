#include "../../include/include.h"

//
// Created by abdelaziz on 7/17/24.
//

int redirect_to_file(char *cmd, char *arg, int append)
{
    int fd;
    int std_out;
    char **split;

    (void)arg;
    split = ft_split_del(cmd, ">");
    if (!split)
        return (0);
    fd = -1;
    while (split[++fd])
        split[fd] = trim_and_free(split[fd]);
    if (append)
        fd = open(split[1], O_CREAT | O_APPEND | O_RDWR , 0644);
    else
        fd = open(split[1], O_CREAT | O_TRUNC | O_RDWR , 0644);
    std_out = dup(STDOUT_FILENO);
    printf("split[0] = [%s]\nsplit[1] = [%s]\n", split[0], split[1]);
    dup2(fd , 1);
    exec_simple_cmd(split[0]);
//    close(fd);
    dup2(std_out, 1);
    return  (1);
}

int has_redirect(char *cmd)
{
    (void)cmd;
    return (1);
}
