#include <stdio.h>
#include <stdlib.h>

#define CACHE_SIZE 4

typedef struct {
    int value;
} CacheItem;

CacheItem cache[CACHE_SIZE];
int counter = 0;

void push(int value) {
    for (int i = CACHE_SIZE - 1; i > 0; i--) {
        cache[i] = cache[i - 1];
    }
    cache[0].value = value;
}

void lru(int value) {
    if (counter < CACHE_SIZE) {
        cache[counter].value = value;
        counter++;
    } else {
        push(value);
    }
}

void printCache() {
    printf("LRU Cache: ");
    for (int i = 0; i < CACHE_SIZE; i++) {
        printf("%d ", cache[i].value);
    }
    printf("\n");
}

int main() {
    int numPages;
    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    printf("Enter the page references: ");
    for (int i = 0; i < numPages; i++) {
        int page;
        scanf("%d", &page);
        lru(page);
        printCache();
    }

    return 0;
}

