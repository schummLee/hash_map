#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
typedef struct node { char *key; char *value; struct node *next; } node;
typedef struct hashmap { node **table; } hashmap;

hashmap *create_hashmap()
 { hashmap *map = malloc(sizeof(hashmap)); map->table = calloc(TABLE_SIZE, sizeof(node *)); return map; }

unsigned int hash(char *key)
 { unsigned int hash = 0; for (int i = 0; i < strlen(key); ++i) { hash = (hash << 5) + hash + key[i]; }
    return hash % TABLE_SIZE; }

void insert(hashmap *map, char *key, char *value)
 { unsigned int index = hash(key); node *new_node = malloc(sizeof(node));
   new_node->key = key; new_node->value = value; new_node->next = NULL;
   if (map->table[index] == NULL) { map->table[index] = new_node; }
   else { node *current_node = map->table[index]; while (current_node->next != NULL) { current_node = current_node->next; }
   current_node->next = new_node; } }

char *search(hashmap *map, char *key)
 { unsigned int index = hash(key); node *current_node = map->table[index]; while (current_node != NULL) {
   if (strcmp(current_node->key, key) == 0) { return current_node->value; }
   current_node = current_node->next; } return NULL; }

void free_hashmap(hashmap *map) {
  for (int i = 0; i < TABLE_SIZE; ++i)
 { node *current_node = map->table[i]; while (current_node != NULL)
 { node *temp = current_node; current_node = current_node->next; free(temp); } }
  free(map->table); free(map); }

int main()
 { hashmap *map = create_hashmap();
   insert(map, "key1", "value1"); insert(map, "key2", "value2");
   printf("%s\n", search(map, "key1")); printf("%s\n", search(map, "key2"));
   free_hashmap(map);
}
