#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

#define ARG_ERR "Usage: arg error\n"
#define VALID_INPUT "The valid input is 1 of 4: by_duration , by_distance , by_name , test \n"
#define NUMBER_OF_LINE "Enter number of lines. Then enter\n" //PRINT TO STDOUT
#define LINE_INFO "Enter line info. Then enter\n" //PRINT TO STDOUT
#define MAX_LINE_SIZE 61
#define MAX_SIZE_FIELD 21
#define NAME_ERR "Error: bus name should contains only digits and small chars\n"
#define DURATION_ERR "Error: duration should be an integer between 10 and 100 (includes)\n"
#define DISTANCE_ERR "Error: distance should be an integer between 0 and 1000 (includes)\n"
#define MIN_DISTANCE 0
#define MAX_DISTANCE 1000
#define MIN_DURATION 10
#define MAX_DURATION 100
#define MSG_NUM_LINE "Error: num line should be a positive integer\n"

void print_bus_lines (BusLine *start, BusLine *end)
{
  for (BusLine *ptr = start; ptr < end; ptr++)
    {
      printf ("%s,%d,%d\n", ptr->name, ptr->distance, ptr->duration);
    }
}
int validate_input (const char *name, int distance, int duration)
{
  for (int i = 0; name[i] != '\0'; i++)
    {
      if (!islower(name[i])&&!isdigit (name[i]))
        {
          printf (NAME_ERR);
          return EXIT_FAILURE;
        }
      if (!(MIN_DISTANCE <= distance && distance <= MAX_DISTANCE))
        {
          printf (DISTANCE_ERR);
          return EXIT_FAILURE;
        }
      if (!(MIN_DURATION <= duration && duration <= MAX_DURATION))
        {
          printf (DURATION_ERR);
          return EXIT_FAILURE;
        }
    }
  return EXIT_SUCCESS;
}

int get_num_lines()
{
  char input[MAX_LINE_SIZE];
  int num_lines;
  do {
      fprintf(stdout,NUMBER_OF_LINE);
      fgets(input, sizeof(input), stdin);
      sscanf(input, "%d", &num_lines);
      if (num_lines <= 0)
      {
        fprintf(stdout,MSG_NUM_LINE);
      }
    } while (num_lines <= 0);
  return num_lines;
}
void init_input (int line_num, BusLine *start)
{
  char input[MAX_LINE_SIZE];
  char name[MAX_SIZE_FIELD];
  int distance;
  int duration;
  int i = 0;
  while (i < line_num)
    {
      printf ("%s", LINE_INFO);
      if (fgets (input, sizeof (input), stdin) != NULL)
        {
          sscanf (input, "%20[^,],%d,%d", name, &distance, &duration);
          if (!validate_input (name, distance, duration))
            {
              strcpy ((start + i)->name, name);
              (start + i)->distance = distance;
              (start + i)->duration = duration;
              i++;
            }
        }
    }
}

void get_input (const char *argv)
{
  int line_num=get_num_lines();

  BusLine *bus_line_start = malloc (sizeof (BusLine) * line_num);

  init_input (line_num, bus_line_start);

  if (!strcmp (argv, "by_duration"))
    {
      quick_sort (bus_line_start, bus_line_start + line_num, DURATION);
      print_bus_lines (bus_line_start, bus_line_start + line_num);
    }
  if (!strcmp (argv, "by_distance"))
    {
      quick_sort (bus_line_start, bus_line_start + line_num , DISTANCE);

      print_bus_lines (bus_line_start, bus_line_start + line_num );
    }
  if (!strcmp (argv, "by_name") )
    {

      bubble_sort (bus_line_start, bus_line_start + line_num);
      print_bus_lines (bus_line_start, bus_line_start + line_num );

    }
  free (bus_line_start);
}
void test (){
  int line_num=get_num_lines();
  BusLine *bus_line_start =  malloc (sizeof (BusLine) * line_num);
  init_input (line_num, bus_line_start);
  BusLine *copied_array =  malloc (sizeof (BusLine) * line_num);
  memcpy (copied_array, bus_line_start, sizeof (BusLine) * line_num);
  if (!is_sorted_by_distance (bus_line_start, bus_line_start + line_num-1))
    {printf ("TEST 1 FAILED: Not sorted by distance\n");}else
    {printf ("TEST 1 PASSED: The array is sorted by distance\n");}
  if (!is_equal (bus_line_start, bus_line_start + line_num-1, copied_array, copied_array + line_num-1))
    {printf ("TEST 2 FAILED: Not sorted by distance\n");}else
    {printf ("TEST 2 PASSED: The array has the same items after sorting\n");}
  if (!is_sorted_by_duration (bus_line_start, bus_line_start + line_num-1))
    {printf ("TEST 3 FAILED: Not sorted by distance\n");}
    else{printf ("TEST 3 PASSED: The array is sorted by duration\n");}
  if (!is_equal (bus_line_start, bus_line_start + line_num-1, copied_array, copied_array + line_num-1))
    {printf ("TEST 4 FAILED: Not sorted by distance\n");}
    else{printf ("TEST 4 PASSED: The array has the same items after sorting\n");}
  if (!is_sorted_by_name (bus_line_start, bus_line_start + line_num-1))
    {printf ("TEST 5 FAILED: Not sorted by distance\n");}
    else{printf ("TEST 5 PASSED: The array is sorted by name\n");}
  if (!is_equal (bus_line_start, bus_line_start + line_num-1, copied_array, copied_array + line_num-1))
    {printf ("TEST 6 FAILED: Not sorted by distance\n");}
    else{printf ("TEST 6 PASSED: The array has the same items after sorting\n");}
  free (bus_line_start);
  free (copied_array);
}

int main (int argc, char *argv[])
{
  if (argc != 2)
    {
      fprintf (stdout, ARG_ERR);
      printf (VALID_INPUT);
      return EXIT_FAILURE;
    }
  if (!(strcmp (argv[1], "by_name")) ||!(strcmp (argv[1], "by_distance")) ||!(strcmp (argv[1], "by_duration")))
    {
      get_input (argv[1]);
      return EXIT_SUCCESS;
    }
  if (!(strcmp (argv[1], "test")))
    {
      test ();
      return EXIT_SUCCESS;
    }
  fprintf (stdout,ARG_ERR);
  printf (VALID_INPUT);
  return EXIT_FAILURE;
}


