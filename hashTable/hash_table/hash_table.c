#include <hash_table.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUCKET_COUNT 1024

struct Binding
{
    const char *key;
    int value;
    struct Binding *next;
};

struct HashTable
{
    struct Binding *buckets[BUCKET_COUNT];
};

struct HashTable *create()
{
    struct HashTable *new_hash_table = malloc(sizeof(struct HashTable));
    return new_hash_table;
};

unsigned int hash(const char *key)
{

    unsigned int hash = 0;
    unsigned int holder = 0;
    int i = 0;
    int len = strlen(key);

    while (i < len)
    {
        holder += key[i];
        hash += holder;
        hash = (hash * key[i]);
        i += 1;
    }

    hash = hash * holder;
    hash = (hash) % BUCKET_COUNT;

    return hash;
};

bool add(struct HashTable *table, const char *key, int value)
{

    int key_hash_value = hash(key);

    if (table->buckets[key_hash_value] == NULL)
    {
        table->buckets[key_hash_value] = malloc(sizeof(struct Binding));

        table->buckets[key_hash_value]->key = key;
        table->buckets[key_hash_value]->next = NULL;
        table->buckets[key_hash_value]->value = value;

        return true;
    }
    else 
    {
        struct Binding *holder = table->buckets[key_hash_value];

        while (holder->key != key && holder->next != NULL)
        {
            struct Binding *tempBind = holder->next;
            holder = tempBind;
        }
        if (holder->key == key)
        {
            holder->value = value;

            return false;
        }
        else if (holder->next == NULL)
        {
            struct Binding *newBinding = malloc(sizeof(struct Binding));

            holder->next = newBinding;

            newBinding->key = key;
            newBinding->next = NULL;
            newBinding->value = value;

            return true;
        };
    }
}

struct Binding *find(struct HashTable *table, const char *key)

{

    unsigned int key_hash_value = hash(key);

    if (table->buckets[key_hash_value] == NULL)
    {
        return NULL;
    }
    else
    {
        struct Binding *search_in = table->buckets[key_hash_value];
        while (search_in->key != key && search_in->next != NULL)
        {
            search_in = search_in->next;
        }
        if (search_in->key == key)
        {
            return search_in;
        }
        else if (search_in->next == NULL)
        {
            return NULL;
        }
    }
};

bool remove(struct HashTable *table, const char *key)
{
    unsigned int hashed_key = hash(key);
    if (table->buckets[hashed_key] == NULL)
    {
        return false;
    }
    else
    {
        struct Binding *binding = table->buckets[hashed_key];
        struct Binding *prev_binding = NULL;

        while (binding->key != key && binding->next != NULL)
        {
            prev_binding = binding;
            binding = binding->next;
        }
        if (binding->key == key)
        {
            if (binding->next == NULL)
            {
                free(binding);
                binding = malloc(sizeof(NULL));
                binding= NULL;
            }
            else
            {
                prev_binding-> next = binding->next;
                free(binding);
                binding = malloc(sizeof(NULL));
                binding = NULL;
            }
            return true;
        }
        else if (binding->next == NULL)
        {
            return false;
        };
    }
};

void delete_table(struct HashTable *table)
{
    for (int i = 0; i < BUCKET_COUNT; i++)
    {
        if (table->buckets[i] != NULL)
        {
            struct Binding *value = table->buckets[i];

            while (value->next != NULL)
            {
                struct Binding *temp = value->next;

                free(value);

                value = temp;
            }
            free(value);
        }
    }

    free(table);
    table = malloc(sizeof(NULL));
    table = NULL;
};
