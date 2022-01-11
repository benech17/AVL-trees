#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "dict.h"

dict_t **dictAlloc(void)
{
   return malloc(sizeof(dict_t));
}

void dictDealloc(dict_t **dict)
{
   free(dict);
}

void incrementItem(dict_t **dict, char *key)
{
   dict_t *ptr;
   for (ptr = *dict; ptr != NULL; ptr = ptr->next)
   {
      if (strcmp(ptr->key, key) == 0)
      {
         ptr->value++;
      }
   }
}

int getItem(dict_t **dict, char *key)
{
   dict_t *ptr;
   for (ptr = *dict; ptr != NULL; ptr = ptr->next)
   {
      if (strcmp(ptr->key, key) == 0)
      {
         return ptr->value;
      }
   }
   return INT_MIN;
}

void delItem(dict_t **dict, char *key)
{
   dict_t *ptr, *prev;
   for (ptr = *dict, prev = NULL; ptr != NULL; prev = ptr, ptr = ptr->next)
   {
      if (strcmp(ptr->key, key) == 0)
      {
         if (ptr->next != NULL)
         {
            if (prev == NULL)
            {
               *dict = ptr->next;
            }
            else
            {
               prev->next = ptr->next;
            }
         }
         else if (prev != NULL)
         {
            prev->next = NULL;
         }
         else
         {
            *dict = NULL;
         }

         free(ptr->key);
         free(ptr);

         return;
      }
   }
}

void addItem(dict_t **dict, char *key, int value)
{
   delItem(dict, key); /* If we already have a item with this key, delete it. */
   dict_t *d = malloc(sizeof(struct dict_t_struct));
   d->key = malloc(strlen(key) + 1);
   strcpy(d->key, key);
   d->value = value;
   d->next = *dict;
   *dict = d;
}

void printDict(dict_t **dict)
{
   dict_t *ptr;
   int count =0;
   for (ptr = *dict; ptr != NULL; ptr = ptr->next)
   {
      printf("%s | %d\n", ptr->key, ptr->value);
      count++;
   }
   printf("%d signatures.\n",count);
}

/*void deleteDoublons(dict_t **dict)
{
   dict_t *ptr;
   for (ptr = *dict; ptr != NULL; ptr = ptr->next)
   {
      if(strcmp(ptr->key,ptr->next->key) || strcmp(ptr->key,ptr->next->next->key) )
      delItem(dict,ptr->key);
   }
}
*/