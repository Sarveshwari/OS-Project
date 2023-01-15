#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "Threads/linearSearchThread.c"
#include "Threads/binarySearchThread.c"
#include "Threads/bubbleSortThread.c"

void bubbleSortRun()
{
    int i;
    int N;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &N);
    srand(time(NULL));
    // Filling the array with random integers
    for (i = 0; i < N; i++)
        arr[i] = rand() % 100;
    printf("Unsorted Array:\n");
    for (i = 0; i < N; i++)
        printf("%d ", arr[i]);
    printf("\n");
    pthread_t sorters[2];
    clock_t startingTime, endingTime;
    startingTime = clock();
    printf("Sorted Array :\n");
    for (i = 0; i < 2; i++)
    {
        pthread_create(&sorters[i], NULL, sortArr, (int *)i);
        pthread_join(sorters[i], NULL);
    }
    endingTime = clock();
    printf("Time taken: %f\n", (endingTime - startingTime) / (double)CLOCKS_PER_SEC);
    pthread_exit(NULL);
}
void linearSearchRun()
{
    pthread_t thread[THREAD_MAX];
    clock_t startingTime, endingTime;
    startingTime = clock();
    for (int i = 0; i < THREAD_MAX; i++)
        pthread_create(&thread[i], NULL, ThreadSearch, (void *)NULL); // create multiple threads
    for (int i = 0; i < THREAD_MAX; i++)
        pthread_join(thread[i], NULL); // wait untill all of the threads are completed
    endingTime = clock();
    if (flag == 1)
        printf("Key found in the array\n");
    else
        printf("Key not found\n");
    printf("Time taken: %f\n", (endingTime - startingTime) / (double)CLOCKS_PER_SEC);
    pthread_exit(NULL);
}
void binarySearchRun()
{
    pthread_t threads[MAX_THREAD];
    clock_t startingTime, endingTime;
    startingTime = clock();
    for (int i = 0; i < MAX_THREAD; i++)
        pthread_create(&threads[i], NULL, binary_search, (void *)NULL);
    for (int i = 0; i < MAX_THREAD; i++)
        pthread_join(threads[i], NULL); // wait, to join with the main thread
    endingTime = clock();
    if (found == 1)
        printf("Key found in the array\n");
    else
        printf("Key not found\n");
    printf("Time taken: %f\n", (endingTime - startingTime) / (double)CLOCKS_PER_SEC);
    pthread_exit(NULL);
}
int main()
{
    int choice;
    do
    {
        printf(" 1. Bubble Sort\n 2. Linear Search\n 3. Binary Search\n 4. Exit \n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            bubbleSortRun();
            break;
        case 2:
            linearSearchRun();
            break;
        case 3:
            binarySearchRun();
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice\n");
            break;
        }
    } while (choice != 4);
    return 0;
}