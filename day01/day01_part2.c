#include <stdio.h>
#include <stdlib.h>

static void split_into_lists(const char *line, int *list_one, int *list_two) {
  if (sscanf(line, "%d %d", list_one, list_two) != 2) {
     fprintf(stderr, "Error: Unable to read two integers from line: '%s'\n", line);
     exit(EXIT_FAILURE);
  }
}                                                                                                                                                                                                                 

static int count_occurencies(int *list, int nb, int list_size)
{
  int counter = 0;
  for (int i = 0; i < list_size; i++) {
    if (list[i] == nb)
      counter++;
  }
  return counter;
}

static void compute_similarity(int *list_one, int *list_two, int nb_line)
{
  int sum = 0;
  for (int i = 0; i < nb_line ; i++) {
    sum += list_one[i] * count_occurencies(list_two, list_one[i], nb_line);
  }
  printf("%d\n", sum);
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
  compute_similarity(list_one, list_two, nb_line);
  fclose(stream);
  free(line);
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
