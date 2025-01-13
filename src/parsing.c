/*
** EPITECH PROJECT, 2024
** Semester_1
** File description:
** parsing
*/
#include "my_top.h"
#include "my.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int check_uservalid(char *user, flag_t *flag)
{
    int fd = 0;
    char buffer[30000];
    char **tab;
    char **temp;

    fd = open("/etc/passwd", O_RDONLY);
    if (fd == -1) {
        write(2, "Error with open\n", 17);
        return 84;
    }
    read(fd, buffer, 29999);
    tab = my_str_to_word_array(buffer, '\n');
    for (int i = 0; tab[i] != NULL; i++){
        temp = my_str_to_word_array(tab[i], ':');
        if (my_strcmp(temp[0], user) == 0) {
            flag->User = my_strdup(temp[0]);
            return 0;
        }
    }
    return 84;
}

int get_str_to_float(char *delay_s, flag_t *flag)
{
    int len_int = 0;
    float power = 0;

    flag->delay = 0;
    for (; delay_s[len_int] != '.' && delay_s[len_int] != '\0'; len_int++);
    for (int i = 0; delay_s[i] != '.' && delay_s[i] != '\0'; i++){
        if ('9' < delay_s[i] && '0' > delay_s[i])
            return 84;
        power = my_compute_power_rec_f(10.0, len_int - i - 1);
        flag->delay += (delay_s[i] - 48) * power;
    }
    if (delay_s[len_int] == '\0')
        return 0;
    for (int i = len_int + 1; delay_s[i] != '\0'; i++){
        if ('9' < delay_s[i] && '0' > delay_s[i])
            return 84;
        power = my_compute_power_rec_f(0.1, i - len_int);
        flag->delay += (delay_s[i] - 48) * power;
    }
    return 0;
}

int get_str_to_int(char *frame, flag_t *flag)
{
    int power = 0;

    for (int i = 0; frame[i] != '\0'; i++){
        if ('9' < frame[i] && '0' > frame[i])
            return 84;
        power = my_compute_power_rec(10, my_strlen(frame) - i - 1);
        flag->frame += (frame[i] - 48) * power;
    }
    if (flag->frame < 1)
        return 84;
    return 0;
}

int parsing(int ac, char **av, flag_t *flag)
{
    int err = 0;

    for (int i = 1; i < ac; i += 2) {
        if ((my_strcmp("-U", av[i]) != 0 && my_strcmp("-d", av[i]) != 0
            && my_strcmp("-n", av[i]) != 0) || av[i + 1] == NULL){
            write(2, "invalid flag or argument\n", 25);
            return 84;
        }
        if (my_strcmp("-U", av[i]) == 0)
            err = check_uservalid(av[i + 1], flag);
        if (my_strcmp("-d", av[i]) == 0)
            err = get_str_to_float(av[i + 1], flag);
        if (my_strcmp("-n", av[i]) == 0)
            err = get_str_to_int(av[i + 1], flag);
        if (err == 84){
            write(2, "invalid flag or argument\n", 25);
            return 84;
        }
    }
    return 0;
}
