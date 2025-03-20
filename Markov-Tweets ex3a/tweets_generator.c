#define FILE_PATH_ERROR "Error: incorrect file path"
#define NUM_ARGS_ERROR "Usage: invalid number of arguments"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "markov_chain.h"
#include "linked_list.h"
#include "unistd.h"
#define DELIMITERS " \n\t\r"
#define MAX_LINE_LEN 1000
#define MAX_LEN_TWEET 20
#define RADIX 10
#define ACCESS_RETURN -1
#define FOURARGS 4
#define FIVEARGS 5
void print_tweets (MarkovChain *chain, long tweet_num)
{
  for (int i = 1; i <= tweet_num; i++)
    {
      printf ("Tweet %d: ", i);
      generate_tweet (get_first_random_node (chain), MAX_LEN_TWEET);
      printf ("\n");
    }
}

int check_if_end_word (const char *word)
{
  size_t len = strlen (word);
  if (word[len - 1] == '.')
    {
      return EXIT_SUCCESS;
    }
  return EXIT_FAILURE;
}
int fill_database (FILE *fp, int words_to_read, MarkovChain *markov_chain)
{
  int num_of_words = 0;
  char line[MAX_LINE_LEN];
  while (fgets (line, sizeof (line), fp))// get a line from the file
    {
      Node *previous_node = NULL; //every new line the previous pointer null
      char *words = strtok (line, DELIMITERS); //split the words
      if (!markov_chain->database->size) // if there is no data base
        {
          num_of_words += 1;
          previous_node = add_to_database (markov_chain, words);// make the first node for the data base
          if (previous_node == NULL)
            {
              return EXIT_FAILURE;
            }
          words = strtok (NULL, DELIMITERS);// skip to the next word
        }
      while (words && num_of_words < words_to_read)//iterate over the words
        {
          Node *cur = get_node_from_database (markov_chain, words);
          if (!cur) // if the word not in the database
            {
              cur = add_to_database (markov_chain, words);
              if (cur == NULL)
                {
                  return EXIT_FAILURE;
                }
            }
          if (previous_node)// check if the previous node is null
            {
              if (add_node_to_frequency_list (previous_node->data, cur->data))
                {
                  return EXIT_FAILURE;
                }
            }
          if (!check_if_end_word (words))// if the word end with a "."
            {
              previous_node = NULL;
            }
          else
            {
              previous_node = cur;
            }
          num_of_words += 1;
          words = strtok (NULL, DELIMITERS);// skip to the next word

        }
    }
  return EXIT_SUCCESS;
}

int count_words_infile (FILE *fp)
{
  int counter = 0;
  char len_line[MAX_LINE_LEN];
  while (fgets (len_line, sizeof (len_line), fp))
    {
      char *word = strtok (len_line, DELIMITERS); //split the words
      while (word)
        {
          counter += 1;
          word++;
        }

    }
  return counter;
}
MarkovChain *init (MarkovChain *chain)
{
  LinkedList *data = malloc (sizeof (LinkedList));
  if (!data)
    {
      return NULL;
    }
  chain->database = data;
  data->first = NULL;
  data->last = NULL;
  data->size = 0;
  return chain;
}
int main (int argc, char *argv[])
{
  if (argc == FOURARGS || argc ==FIVEARGS)
    {size_t seed = strtol (argv[1], NULL, RADIX);
      srand (seed);
      const char *file = argv[3];
      FILE *fp = fopen (file, "r");
      if (!fp || access (file,F_OK)==ACCESS_RETURN)
        {printf (FILE_PATH_ERROR);
          return EXIT_FAILURE;
        }
      MarkovChain *chain = malloc (sizeof (MarkovChain));
      if (!chain)
        {printf (ALLOCATION_ERROR_MASSAGE);
          fclose (fp);
          return EXIT_FAILURE;
        }
      chain = init (chain);
      if (argc == FOURARGS)
        {int words_to_read = count_words_infile (fp);
          if (fill_database (fp, words_to_read, chain))
            {free_database (&chain);
              fclose (fp);
              return EXIT_FAILURE;
            }
          long int tweet_num = strtol (argv[2], NULL, RADIX);
          print_tweets (chain, tweet_num);
          free_database (&chain);
          fclose (fp);
          return EXIT_SUCCESS;
        }else{
          int words_to_read = strtol (argv[4], NULL, RADIX);
          if (fill_database (fp, words_to_read, chain))
            {
              free_database (&chain);
              fclose (fp);
              return EXIT_FAILURE;
            }
          long int tweet_num = strtol (argv[2], NULL, RADIX);
          print_tweets (chain, tweet_num);
          free_database (&chain);
          fclose (fp);
          return EXIT_SUCCESS;
        }
    }

  printf (NUM_ARGS_ERROR);
  return EXIT_FAILURE;
}