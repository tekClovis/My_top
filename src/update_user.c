/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** update_user
*/
#include "my_top.h"
#include "my.h"
#include <utmp.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static char *get_uid(int pid)
{
    char *path = NULL;
    char *file;
    char *next = NULL;
    char *search = NULL;

    asprintf(&path, "/proc/%d/status", pid);
    file = my_catchar(path);
    if (file == NULL)
        return NULL;
    next = strtok(file, "\t\n");
    while (next != NULL){
        search = next;
        next = strtok(NULL, "\t\n");
        if (strcmp(search, "Uid:") == 0){
            return next;
        }
    }
    return NULL;
}

static char *format_user(char *user)
{
    if (strlen(user) > 8){
        user[7] = '+';
        user[8] = '\0';
        return my_strdup(user);
    }
    user[strlen(user)] = '\0';
    return my_strdup(user);
}

static char *get_user_name(char *uid)
{
    FILE *file = fopen("/etc/passwd", "r");
    char search[300];
    char *user;
    char *is_uid;

    if (file == NULL)
        return NULL;
    while (fgets(search, 300, file) != NULL){
        user = strtok(search, ":");
        is_uid = strtok(NULL, ":");
        is_uid = strtok(NULL, ":");
        if (strcmp(is_uid, uid) == 0){
            fclose(file);
            return format_user(user);
        }
    }
    fclose(file);
    return NULL;
}

void update_user(list_t *process)
{
    node_t *current = process->head;
    char *uid = NULL;

    while (current != NULL){
        ((process_t *)current->data)->in_stat->USER = NULL;
        uid = get_uid(((process_t *)current->data)->in_stat->PID);
        if (uid == NULL){
            current = current->next;
            continue;
        }
        ((process_t *)current->data)->in_stat->USER = get_user_name(uid);
        current = current->next;
    }
}
