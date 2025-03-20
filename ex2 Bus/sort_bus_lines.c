#include "sort_bus_lines.h"

//TODO add implementation here


void bubble_sort(BusLine *start, BusLine *end)
{
  int swapped=1;
  BusLine *ptr1;
  BusLine *ptr2;
  while (swapped)
  {
      swapped = 0;
      for (ptr1 = start; ptr1 < end - 1; ptr1++)
      {
          ptr2 = ptr1 + 1;
          if (strcmp(ptr1->name,ptr2->name) > 0) {
              BusLine temp = *ptr1;
              *ptr1 = *ptr2;
              *ptr2 = temp;
              swapped = 1;
            }
        }
      end--;
    }
}

BusLine* partition(BusLine *start, BusLine *end, SortType sort_type) {
  BusLine pivot = *(end - 1);
  BusLine *i = start - 1;

  for (BusLine *j = start; j < end - 1; j++) {
      int condition = 0;
      if (sort_type == DISTANCE)
      {
          condition = (j->distance < pivot.distance);
      }
      else if (sort_type == DURATION)
      {
          condition = (j->duration < pivot.duration);
      }

      if (condition)
      {
          i++;
          BusLine temp = *i;
          *i = *j;
          *j = temp;
        }
    }

  BusLine temp = *(i + 1);
  *(i + 1) = *(end - 1);
  *(end - 1) = temp;

  return i + 1;
}

void quick_sort(BusLine *start,BusLine *end, SortType sort_type)
{
  if (start < end -1)
  {
    BusLine *pi = partition(start, end, sort_type);
    quick_sort(start, pi, sort_type);
    quick_sort(pi + 1, end, sort_type);
  }
}

