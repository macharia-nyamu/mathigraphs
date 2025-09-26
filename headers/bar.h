#ifndef BAR_H
#define BAR_H

typedef struct {
    char *file;
    char *x;
    char *y;
    char *title;
    char *compute;
    char *sort;
} BarOptions;

typedef struct {
    char *label;
    double sum;
    int count;
    double min;
    double max;
} Group;

void display_bar(char *command);

void draw_bar(const BarOptions *opts);

#endif