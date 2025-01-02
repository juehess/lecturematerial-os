#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define PUFFERGROESSE 3
int puffer[PUFFERGROESSE];
int zaehler = 0;

sem_t frei, belegt; // Semaphoren für freie und belegte Plätze
pthread_mutex_t lock; // Schutz des Puffers

void* erzeuger(void* arg) {
    for (int i = 0; i < 5; i++) {
        sem_wait(&frei); // Warte auf freien Platz
        pthread_mutex_lock(&lock);

        puffer[zaehler++] = i; // Element hinzufügen und Zähler erhöhen
        printf("Erzeuger fügt %d hinzu. Puffergröße: %d\n", i, zaehler);

        pthread_mutex_unlock(&lock);
        sem_post(&belegt); // Signalisiere belegten Platz
        sleep(1);
    }
    return NULL;
}

void* verbraucher(void* arg) {
    for (int i = 0; i < 5; i++) {
        sem_wait(&belegt); // Warte auf ein belegtes Element
        pthread_mutex_lock(&lock);

        int element = puffer[--zaehler]; // Zähler verringern und Element entfernen
        printf("Verbraucher entnimmt %d. Puffergröße: %d\n", element, zaehler);

        pthread_mutex_unlock(&lock);
        sem_post(&frei); // Signalisiere freien Platz
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&frei, 0, PUFFERGROESSE); // Puffer startet mit allen freien Plätzen
    sem_init(&belegt, 0, 0); // Keine belegten Plätze
    pthread_mutex_init(&lock, NULL);

    pthread_create(&prod, NULL, erzeuger, NULL);
    pthread_create(&cons, NULL, verbraucher, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&frei);
    sem_destroy(&belegt);
    pthread_mutex_destroy(&lock);

    return 0;
}