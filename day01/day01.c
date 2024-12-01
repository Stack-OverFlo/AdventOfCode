#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare(const void *nb_one, const void *nb_two) {
    int a = *(const int*)nb_one;
    int b = *(const int*)nb_two;
    if (a < b) return -1;
    else if (a > b) return 1;
    else return 0;
}

static void split_into_lists(char *line, int *list_one, int *list_two) {
    if (sscanf(line, "%d   %d", list_one, list_two) != 2) {
        fprintf(stderr, "Error: Unable to read two integers from line: '%s'\n", line);
        exit(EXIT_FAILURE);
    }
}

static void sort_lists(int *list_one, int *list_two, int num_lines) {
    qsort(list_one, num_lines, sizeof(int), compare);
    qsort(list_two, num_lines, sizeof(int), compare);
    printf("list_one sorted: ");
    for (int i = 0; i < num_lines; i++) {
        printf("%d ", list_one[i]);
    }
    printf("\n");
    printf("list_two sorted: ");
    for (int i = 0; i < num_lines; i++) {
        printf("%d ", list_two[i]);
    }
    printf("\n");
    int *total_distance = (int *)malloc(sizeof(int) * num_lines);
    if (total_distance == NULL) {
        perror("malloc failed for total_distance");
        exit(EXIT_FAILURE);
    }
    int sum = 0;
    for (int i = 0; i < num_lines; i++) {
        total_distance[i] = abs(list_one[i] - list_two[i]);
        sum += total_distance[i];
        printf("total_distance[%d] = %d\n", i, total_distance[i]);
    }
    printf("Total distance = %d\n", sum);
    free(total_distance);
}

static void read_input(const char *input) {
    FILE *stream;
    char *line = NULL;
    size_t length = 0;
    ssize_t nread;
    const int num_lines = 1000;
    int *list_one = (int *)malloc(sizeof(int) * num_lines);
    int *list_two = (int *)malloc(sizeof(int) * num_lines);
    int nb_line = 0;

    if (list_one == NULL || list_two == NULL) {
        perror("malloc failed for list_one or list_two");
        exit(EXIT_FAILURE);
    }
    stream = fopen(input, "r");
    if (stream == NULL) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }
    while ((nread = getline(&line, &length, stream)) != -1 && nb_line < num_lines) {
        split_into_lists(line, &list_one[nb_line], &list_two[nb_line]);
        nb_line++;
    }
    fclose(stream);
    sort_lists(list_one, list_two, nb_line);
    free(line);
    free(list_one);
    free(list_two);
}

int main(int ac, const char *av[]) {
    if (ac != 2) {
        perror("Usage: ./day01 input.txt");
        return 1;
    }
    read_input(av[1]);
    return 0;
}
