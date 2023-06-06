
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hash_map {
	  char *key;
	  char *value;
	  struct hash_map *next;
};

#define HASH_MAP_SIZE 10
struct hash_map *hash_map[HASH_MAP_SIZE];

unsigned long hash(char *str) {
	  unsigned long hash = 5381;
	    int c;

	      while (c = *str++)
		          hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	        return hash % HASH_MAP_SIZE;
}

void hash_map_put(char *key, char *value) {
	  unsigned long index = hash(key);

	    struct hash_map *entry = malloc(sizeof(struct hash_map));
	      entry->key = key;
	      entry->value = value;
	      entry->next = hash_map[index];
	      hash_map[index] = entry;
}

char *hash_map_get(char *key) {
	  unsigned long index = hash(key);

	    struct hash_map *entry;
	      for (entry = hash_map[index]; entry != NULL; entry = entry->next) {
		          if (strcmp(entry->key, key) == 0)
				        return entry->value;
			    }

	        return NULL;
}

int main() {
	     char *keys[] = {"apple", "banana", "cherry"};
	     char *values[] = {"red", "yellow", "red"};
	     int i;
	     for (i = 0; i < 3; i++)
	     hash_map_put(keys[i], values[i]);
	                   printf("apple: %s\n", hash_map_get("apple"));
	                   printf("banana: %s\n", hash_map_get("banana"));
	                   printf("cherry: %s\n", hash_map_get("cherry"));
	                   printf("grape: %s\n", hash_map_get("grape"));
	                           return 0;
	                           }

