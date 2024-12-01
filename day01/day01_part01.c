#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare(const void *nb_one, const void *nb_two) {
    return (*(int*)nb_one - *(int*)nb_two);
}

static void split_into_lists(const char *line, int *list_one, int *list_two) {
    if (sscanf(line, "%d %d", list_one, list_two) != 2) {
        fprintf(stderr, "Error: Unable to read two integers from line: '%s'\n", line);
        exit(EXIT_FAILURE);
    }
}

static void sort_lists(int *list_one, int *list_two, int num_lines) {
    qsort(list_one, num_lines, sizeof(int), compare);
    qsort(list_two, num_lines, sizeof(int), compare);
}

static int calculate_distance_sum(int *list_one, int *list_two, int num_lines) {
    int sum = 0;
    for (int i = 0; i < num_lines; i++) {
        sum += abs(list_one[i] - list_two[i]);
    }
    return sum;
}
static void read_input(const char *input) {
    FILE *stream = fopen(input, "r");
    if (!stream) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }
    int num_lines = 0;
    char *line = NULL;
    size_t length = 0;
    ssize_t nread;
    while ((nread = getline(&line, &length, stream)) != -1) {
        num_lines++;
    }
    rewind(stream);
    int *list_one = malloc(sizeof(int) * num_lines);
    int *list_two = malloc(sizeof(int) * num_lines);
    if (!list_one || !list_two) {
        perror("malloc failed for list_one or list_two");
        fclose(stream);
        exit(EXIT_FAILURE);
    }
    int nb_line = 0;
    while ((nread = getline(&line, &length, stream)) != -1) {
        split_into_lists(line, &list_one[nb_line], &list_two[nb_line]);
        nb_line++;
    }
    fclose(stream);
    free(line);
    sort_lists(list_one, list_two, num_lines);
    int sum = calculate_distance_sum(list_one, list_two, num_lines);
    printf("Total distance = %d\n", sum);
    free(list_one);
    free(list_two);
}

int main(int ac, const char *av[]) {
    if (ac != 2) {
        fprintf(stderr, "Usage: %s input.txt\n", av[0]);
        return 1;
    }
    read_input(av[1]);
    return 0;
}
