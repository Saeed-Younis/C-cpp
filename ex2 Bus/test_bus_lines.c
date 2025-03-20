#include "test_bus_lines.h"

//TODO add implementation here
// number of lines
 int is_sorted_by_distance(const BusLine *start,const BusLine *end)
{
  quick_sort ((BusLine*)start,(BusLine*)end,DISTANCE);
  const BusLine *pointer= start;
  while (pointer<end)
    {
      if (pointer->distance > (pointer + 1)->distance)
        {
          return 0;

        }
        pointer++;
    }
    return 1;

}
int is_sorted_by_duration (const BusLine *start, const BusLine *end)
{
  quick_sort ((BusLine*)start,(BusLine*)end,DURATION);
  const BusLine *pointer=start;
  while (pointer<end)
    {
      if (pointer->duration > (pointer + 1)->duration)
        {
          return 0;

        }
      pointer++;
    }
  return 1;
}
int is_sorted_by_name ( const BusLine *start,const  BusLine *end)
{
  bubble_sort ((BusLine*)start,(BusLine*)end);
  const BusLine *pointer=start;
  while(pointer<end)
    {
      if (strcmp(pointer->name,(pointer+1)->name)>0)
        {
          return 0;
        }
        pointer++;
    }
    return 1;
}
int is_equal (const BusLine *start_sorted,const BusLine *end_sorted,const BusLine *start_original,const BusLine *end_original)
{
  int sorted_size=end_sorted-start_sorted;
  int original_size=end_original-start_original;
  if (sorted_size!=original_size)
  {
    return 0;
  }

  for (const BusLine *original_ptr=start_original;original_ptr<end_original;original_ptr++)
    {
      int flag = 0;
      for(const BusLine*sorted_ptr=start_sorted;sorted_ptr<end_sorted;sorted_ptr++)
        {
          if(strcmp (original_ptr->name,sorted_ptr->name)==0)
            {
              flag =1 ;
              break;
            }

        }
        if (flag==0)
          {
            return 0;
          }
    }
    return 1;
}