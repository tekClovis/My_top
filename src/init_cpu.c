/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** init_tasks
*/
#include "my_top.h"
#include "my.h"
#include <string.h>
#include <stdlib.h>

static t2_t *t2_init(void)
{
    t2_t *t2 = malloc(sizeof(t2_t));

    if (t2 == NULL)
        return NULL;
    t2->user = 0;
    t2->system = 0;
    t2->nice = 0;
    t2->idle = 0;
    t2->iowait = 0;
    t2->irq = 0;
    t2->sofirq = 0;
    t2->steal = 0;
    t2->total = 0;
    return t2;
}

static delta_t *init_delta(void)
{
    delta_t *delta = malloc(sizeof(delta_t));

    if (delta == NULL)
        return NULL;
    delta->user = 0;
    delta->system = 0;
    delta->nice = 0;
    delta->idle = 0;
    delta->iowait = 0;
    delta->irq = 0;
    delta->sofirq = 0;
    delta->steal = 0;
    return delta;
}

m_cpu_t *init_cpu(void)
{
    m_cpu_t *cpu = malloc(sizeof(m_cpu_t));
    t1_t *t1 = malloc(sizeof(t1_t));
    t2_t *t2 = t2_init();
    delta_t *delta = init_delta();
    info_cpu_t *inf_cpu = malloc(sizeof(info_cpu_t));

    if (cpu == NULL || delta == NULL || t1 == NULL || inf_cpu == NULL ||
        t2 == NULL)
        return NULL;
    cpu->inf_cpu = inf_cpu;
    cpu->t1 = t1;
    cpu->t2 = t2;
    cpu->delta = delta;
    return cpu;
}

static void delta_update(m_cpu_t *cpu)
{
    cpu->delta->user = cpu->t2->user - cpu->t1->user;
    cpu->delta->nice = cpu->t2->nice - cpu->t1->nice;
    cpu->delta->system = cpu->t2->system - cpu->t1->system;
    cpu->delta->idle = cpu->t2->idle - cpu->t1->idle;
    cpu->delta->iowait = cpu->t2->iowait - cpu->t1->iowait;
    cpu->delta->irq = cpu->t2->irq - cpu->t1->irq;
    cpu->delta->sofirq = cpu->t2->sofirq - cpu->t1->sofirq;
    cpu->delta->steal = cpu->t2->steal - cpu->t1->steal;
}

static void t1_update(m_cpu_t *cpu)
{
    cpu->t1->user = cpu->t2->user;
    cpu->t1->nice = cpu->t2->nice;
    cpu->t1->system = cpu->t2->system;
    cpu->t1->idle = cpu->t2->idle;
    cpu->t1->iowait = cpu->t2->iowait;
    cpu->t1->irq = cpu->t2->irq;
    cpu->t1->sofirq = cpu->t2->sofirq;
    cpu->t1->steal = cpu->t2->steal;
    cpu->t1->total = cpu->t2->total;
}

static void t2_update(m_cpu_t *cpu)
{
    char *file = my_catchar("/proc/stat");

    if (file == NULL)
        return;
    strtok(file, " ");
    cpu->t2->user = strtoull(strtok(NULL, " "), NULL, 10);
    cpu->t2->nice = strtoull(strtok(NULL, " "), NULL, 10);
    cpu->t2->system = strtoull(strtok(NULL, " "), NULL, 10);
    cpu->t2->idle = strtoull(strtok(NULL, " "), NULL, 10);
    cpu->t2->iowait = strtoull(strtok(NULL, " "), NULL, 10);
    cpu->t2->irq = strtoull(strtok(NULL, " "), NULL, 10);
    cpu->t2->sofirq = strtoull(strtok(NULL, " "), NULL, 10);
    cpu->t2->steal = strtoull(strtok(NULL, " "), NULL, 10);
    cpu->t2->total = cpu->t2->user + cpu->t2->system + cpu->t2->nice
        + cpu->t2->idle + cpu->t2->iowait + cpu->t2->irq
        + cpu->t2->sofirq + cpu->t2->steal;
    free(file);
}

void inf_cpu_update(m_cpu_t *cpu)
{
    cpu->inf_cpu->user = 100.0 *
        ((double)cpu->delta->user / (double)cpu->total_diff);
    cpu->inf_cpu->nice = 100.0 *
        ((double)cpu->delta->nice / (double)cpu->total_diff);
    cpu->inf_cpu->system = 100.0 *
        ((double)cpu->delta->system / (double)cpu->total_diff);
    cpu->inf_cpu->idle = 100.0 *
        ((double)cpu->delta->idle / (double)cpu->total_diff);
    cpu->inf_cpu->iowait = 100.0 *
        ((double)cpu->delta->iowait / (double)cpu->total_diff);
    cpu->inf_cpu->irq = 100.0 *
        ((double)cpu->delta->irq / (double)cpu->total_diff);
    cpu->inf_cpu->sofirq = 100.0 *
        ((double)cpu->delta->sofirq / (double)cpu->total_diff);
    cpu->inf_cpu->steal = 100.0 *
        ((double)cpu->delta->steal / (double)cpu->total_diff);
}

void cpu_update(m_cpu_t *cpu)
{
    t1_update(cpu);
    t2_update(cpu);
    delta_update(cpu);
    cpu->total_diff = cpu->t2->total - cpu->t1->total;
    inf_cpu_update(cpu);
}
