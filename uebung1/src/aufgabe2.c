#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


void* car(void* arg) {
    int car_id = *(int*)arg;

    printf("Auto %d wartet auf einen Parkplatz...\n", car_id);
    printf("Auto %d parkt.\n", car_id);
    sleep(1); // Simuliert das Parken
    printf("Auto %d verlässt den Parkplatz.\n", car_id);

    return NULL;
}

int main() {
    pthread_t cars[5];
    int car_ids[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        pthread_create(&cars[i], NULL, car, &car_ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(cars[i], NULL);
    }

    return 0;
}