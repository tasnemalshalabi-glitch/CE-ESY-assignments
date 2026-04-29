#include <stdio.h>
#include <string.h>

#define SIZE 20

typedef struct {
	char buffer[SIZE];
	int head;
	int tail;
	int count;
} CircularBuffer;

void init(CircularBuffer *cb) {
	cb->head = 0;
	cb->tail = 0;
	cb->count = 0;
}

int isFull(CircularBuffer *cb) {
	return cb->count == SIZE;
}

int isEmpty(CircularBuffer *cb) {
	return cb->count == 0;
}

void writeBuffer(CircularBuffer *cb, char data) {
	if (isFull(cb)) {
		printf("Buffer Overflow\n");
		return;
	}

	cb->buffer[cb->head] = data;
	cb->head = (cb->head + 1) % SIZE;
	cb->count++;
}

char readBuffer(CircularBuffer *cb) {
	if (isEmpty(cb)) {
		printf("Buffer Underflow\n");
		return '\0';
	}

	char data = cb->buffer[cb->tail];
	cb->tail = (cb->tail + 1) % SIZE;
	cb->count--;
	return data;
}

int main() {
	CircularBuffer cb;
	init(&cb);

	char name[50];
	printf("Enter your name: ");
	
	if (fgets(name, sizeof(name), stdin)) {
		name[strcspn(name, "\n")] = '\0';
	}

	strcat(name, "CE-ESY");

	for (int i = 0; i < strlen(name); i++) {
		writeBuffer(&cb, name[i]);
	}

	printf("Output: ");
	while (!isEmpty(&cb)) {
		printf("%c", readBuffer(&cb));
	}

	printf("\nBuffer empty? %s\n", isEmpty(&cb) ? "Yes" : "No");

	return 0;
}