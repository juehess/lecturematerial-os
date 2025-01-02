#include <stdio.h>
#include <unistd.h> // Für usleep

int counter = 0; // Gemeinsame Ressource

void* increment(void* arg) {
	int thread_id = *(int*)arg;
	for (int i = 0; i < 100; i++) {

		printf("Thread %d arbeitet, counter: %d\n", thread_id, counter);
		int temp = counter; // Lese den aktuellen Wert
		usleep(0.2);
		temp = temp + 1;    // Erhöhe den Wert
		counter = temp;     // Schreibe den neuen Wert zurück
	}
	return NULL;
}

int main() {
	pthread_t t1, t2;

	int id1 = 1, id2 = 2;
	pthread_create(&t1, NULL, increment, &id1);
	pthread_create(&t2, NULL, increment, &id2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("Finaler Counter-Wert: %d\n", counter);
	return 0;
}