#include <stdio.h>
#include <stdbool.h>
#include "./hash_table/hash_table.h"
#include <assert.h>

int main(int argc, char const *argv[])
{
    struct HashTable *table = create();

    assert(find(table, "Test Key") == NULL);

    assert(add(table, "Test Key", 11) == true);

    assert(add(table, "Test Key", 11) == false);

    struct Binding *binding = find(table, "Test Key");

    // assert( binding != NULL &&  binding->value == 11);

    assert(find(table, " Key") == find(table, " Key"));

    // assert(find(table, "Test Key") == NULL);

    delete_table(table);

    assert(find(table, "Test Key") == NULL);

    return 0;
}