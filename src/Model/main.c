#include "parser.h"
#include <time.h>

int main() {
    Elements elements = {NULL, NULL, 0, 0, 0};
    const char *path = "../Models/luster.obj";
    clock_t tStart = clock();
    Parser(&elements, path);
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}