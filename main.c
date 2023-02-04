#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <inttypes.h>

int add_last(void **arr, int *len, data_structure *data) {
	if (*arr == NULL) {
		int length = sizeof(data->header->len) + sizeof(data->header->type);
		length = length + data->header->len;
		*arr = malloc(length);
		length = sizeof(data->header->type);
		memcpy(*arr, &data->header->type, length);
		memcpy(*arr + length, &data->header->len, sizeof(data->header->len));
		length = length + sizeof(data->header->len);
		memcpy(*arr + length, data->data, data->header->len);
		*len = *len + 1;
	} else {
		unsigned int length = 0;
		for (int i = 0; i < *len; i++) {
			length = length + 
			sizeof(data->header->len) + sizeof(data->header->type);

			length = length 
			+ *(unsigned int*)(*arr + length - sizeof(data->header->len));
		}
		int length2 = sizeof(data->header->len) + sizeof(data->header->type);
		length2 = length2 + data->header->len;
		*arr = realloc(*arr, length + length2);
		length2 = sizeof(data->header->type);
		memcpy(*arr + length, &data->header->type, length2);
		memcpy(*arr + length + length2, 
		&data->header->len, sizeof(data->header->len));

		length2 = length2 + sizeof(data->header->len);
		memcpy(*arr + length + length2, data->data, data->header->len);
		*len = *len + 1;
	}
	return 0;
}

void print(void *arr, int len) {
	data_structure *data = malloc(sizeof(data_structure));
	data->header = malloc(sizeof(head));
	unsigned char type = 0;
	int lenght = 0;
	for (int z = 0; z < len; z++) {
		type = *(unsigned char*)(arr + lenght);
		printf("Tipul %d\n", type);
		if (type == 1) {
			lenght = lenght + sizeof(data->header->type);
			lenght = lenght + sizeof(data->header->len);
			printf("%s ", (char*)(arr + lenght));
			lenght = lenght + strlen((char*)(arr + lenght)) + 1;
			printf("pentru ");
			printf("%s\n", (char*)(arr + lenght + 2 * sizeof(int8_t)));
			printf("%"PRId8"\n", *(int8_t*)(arr + lenght));
			printf("%"PRId8"\n", *(int8_t*)(arr + lenght + sizeof(int8_t)));
			lenght = lenght + 2 * sizeof(int8_t);
			lenght = lenght + strlen((char*)(arr + lenght)) + 1;
		} else {
			if (type == 2) {
				lenght = lenght + sizeof(data->header->type);
				lenght = lenght + sizeof(data->header->len);
				printf("%s ", (char*)(arr + lenght));
				lenght = lenght + strlen((char*)(arr + lenght)) + 1;
				printf("pentru ");
				printf("%s\n", (char*)(arr + lenght + 
				sizeof(int16_t) + sizeof(int32_t)));

				printf("%"PRId16"\n", *(int16_t*)(arr + lenght));
				printf("%"PRId32"\n", 
				*(int32_t*)(arr + lenght + sizeof(int16_t)));

				lenght = lenght + sizeof(int16_t) + sizeof(int32_t);
				lenght = lenght + strlen((char*)(arr + lenght)) + 1;

			} else {
				if (type == 3) {
					lenght = lenght + sizeof(data->header->type);
					lenght = lenght + sizeof(data->header->len);
					printf("%s ", (char*)(arr + lenght));
					lenght = lenght + strlen((char*)(arr + lenght)) + 1;
					printf("pentru ");
					printf("%s\n", 
					(char*)(arr + lenght + 2 * sizeof(int32_t)));

					printf("%"PRId32"\n", *(int32_t*)(arr + lenght));
					printf("%"PRId32"\n", 

					*(int32_t*)(arr + lenght + sizeof(int32_t)));
					lenght = lenght + 2 * sizeof(int32_t);
					lenght = lenght + strlen((char*)(arr + lenght)) + 1;
				}
			}
		}
		printf("\n");
	}
	free(data->header);
	free(data);
}

int add_at(void **arr, int *len, data_structure *data, int index) {
	if (index > *len) {
		add_last(arr, len, data);
		return 0;
	}
	unsigned int length1 = 0;
	unsigned int length2 = 0;
	for (int i = 0; i < *len; i++) {
		length1 = length1 + 
		sizeof(data->header->len) + sizeof(data->header->type);

		length1 = length1 
		+ *(unsigned int*)(*arr + length1 - sizeof(data->header->len));
	}
	int i = 0;
	for (i = 0; i < index; i++) {
		length2 = length2 + 
		sizeof(data->header->len) + sizeof(data->header->type);

		length2 = length2 + 
		*(unsigned int*)(*arr + length2 - sizeof(data->header->len));
	}
	int size = sizeof(data->header->len) + sizeof(data->header->type);
	*arr = realloc(*arr, length1 + data->header->len + size);
	memcpy(*arr + length2 + data->header->len + size, 
	*(arr + length2), length1 - length2);

	memcpy(*arr + length2, &data->header->type, 
	sizeof(data->header->type));

	memcpy(*arr + length2 + sizeof(data->header->type), 
	&(data->header->len), sizeof(data->header->len));

	memcpy(*arr + length2 + size, data->data, data->header->len);
	*len = *len + 1;
	return 0;
}

void find(void *data_block, int len, int index) {
	if (index < 0 || index >= len)
	return;
	data_structure * data = malloc(sizeof(data_structure));
	data->header = malloc(sizeof(head));
	unsigned int length2 = 0;
	for (int i = 0; i < index; i++) {
		length2 = length2 + 
		sizeof(data->header->len) + sizeof(data->header->type);

		length2 = length2 + 
		*(unsigned int*)(data_block + length2 - sizeof(data->header->len));
	}
	free(data->header);
	free(data);
	print(data_block + length2, 1);
}

int delete_at(void **arr, int *len, int index) {
	data_structure * data = malloc(sizeof(data_structure));
	data->header = malloc(sizeof(head));
	unsigned int length = 0;
	for (int i = 0; i < *len; i++) {
		length = length + 
		sizeof(data->header->len) + sizeof(data->header->type);

		length = length 
		+ *(unsigned int*)(*arr + length - sizeof(data->header->len));
	}

	unsigned int length2 = 0;
	for (int i = 0; i < index; i++) {
		length2 = length2 + 
		sizeof(data->header->len) + sizeof(data->header->type);

		length2 = length2 
		+ *(unsigned int*)(*arr + length2 - sizeof(data->header->len));
	}

	unsigned int rm_len = 0;
	rm_len = *(unsigned int*)(*arr + length2 + sizeof(data->header->type));
	rm_len = rm_len + sizeof(data->header->type);
	rm_len = rm_len + sizeof(data->header->len);
	

	if (index == (*len - 1)) {
		*arr = realloc(*arr, length - rm_len);
		*len = *len - 1;
	} else {
		memcpy(*arr + length2, *arr + length2 + rm_len, (length - rm_len - length2));
		*arr = realloc(*arr, (length - rm_len));
		*len = *len - 1;
	}
	free(data->header);
	free(data);
	return 0;
}

int main() {
	void *arr = NULL;
	int len = 0;

	data_structure * data = NULL;
	data = malloc(sizeof(data_structure));
	data->data = NULL;
	data->header = malloc(sizeof(head));
	char *string = NULL;
	string = calloc(256,1);
	fgets(string, 255, stdin);
	int index = 0;
	while (strncmp(string, "exit", 4) != 0) {
		int i = 0;
		char * command = strtok(string, " \n");
		i = strlen(command);
		if (strncmp(command, "insert", 6) == 0) {
			i++;
			if (strncmp(command, "insert_at", 7) == 0) {
				char *nr = strtok(string + i, " ");
				index = (int)atoi(nr);
				i = i + strlen(nr) + 1;
			}
			if (strncmp(string + i, "1", 1) == 0) {
				i += 2;
				data->header->type = 1;
				char *p = NULL;
				char *name_1 = NULL, *name_2 = NULL;
				int8_t banck1 = 0;
				int8_t banck2 = 0;
				
				p = strtok(string + i, " ");
				unsigned int length = strlen(p) + 1;
				name_1 = malloc(strlen(p) + 1);
				memcpy(name_1, p, strlen(p));
				memcpy(name_1 + strlen(p), "\0", 1);
				p = strtok(NULL, " ");
				banck1 = (int8_t)atoi(p);
				length = length + sizeof(int8_t);
				p = strtok(NULL, " ");
				banck2 = (int8_t)atoi(p);
				length = length + sizeof(int8_t);
				p = strtok(NULL, "\n");
				name_2 = malloc(strlen(p) + 1);
				memcpy(name_2, p, strlen(p));
				memcpy(name_2 + strlen(p), "\0", 1);
				length = length + strlen(p) + 1;
				data->data = NULL;
				data->data = calloc(length, 1);
				memcpy(data->data, name_1, strlen(name_1));
				memcpy(data->data + strlen(name_1) + 1, 
				&banck1, sizeof(int8_t));

				memcpy(data->data + strlen(name_1) + 1 + 
				sizeof(int8_t), &banck2, sizeof(int8_t));

				memcpy(data->data + strlen(name_1) + 1 + 
				sizeof(int8_t) + sizeof(int8_t), name_2, strlen(name_2));

				data->header->len = length;

				if (strcmp(command, "insert_at") == 0) {
					add_at(&arr, &len, data, index);
				} else {
					add_last(&arr, &len, data);
				}
				free(data->data);
				free(name_1);
				free(name_2);
			}
			if (strncmp(string + i, "2", 1) == 0) {
				i += 2;
				data->header->type = 2;
				char *p = NULL;
				char *name_1 = NULL, *name_2 = NULL;
				int16_t banck1 = 0;
				int32_t banck2 = 0;

				p = strtok(string + i, " ");
				unsigned int length = strlen(p) + 1;
				name_1 = malloc(strlen(p) + 1);
				memcpy(name_1, p, strlen(p));
				memcpy(name_1 + strlen(p), "\0", 1);
				p = strtok(NULL, " ");
				banck1 = (int16_t)atoi(p);
				length = length + sizeof(int16_t);
				p = strtok(NULL, " ");
				banck2 = (int32_t)atoi(p);
				length = length + sizeof(int32_t);
				p = strtok(NULL, "\n");
				name_2 = malloc(strlen(p) + 1);
				memcpy(name_2, p, strlen(p));
				memcpy(name_2 + strlen(p), "\0", 1);
				length = length + strlen(p) + 1;
				data->data = calloc(length, 1);
				memcpy(data->data, name_1, strlen(name_1));
				memcpy(data->data + strlen(name_1) + 1, 
				&banck1, sizeof(int16_t));

				memcpy(data->data + strlen(name_1) + 1 + 
				sizeof(int16_t), &banck2, sizeof(int32_t));

				memcpy(data->data + strlen(name_1) + 1 + 
				sizeof(int16_t) + sizeof(int32_t), name_2, strlen(name_2));

				data->header->len = length;

				if (strcmp(command, "insert_at") == 0) {
					add_at(&arr, &len, data, index);
				} else {
					add_last(&arr, &len, data);
				}
				free(data->data);
				free(name_1);
				free(name_2);
			}
			if (strncmp(string + i, "3", 1) == 0) {
				i += 2;
				data->header->type = 3;
				char *p = NULL;
				char *name_1 = NULL, *name_2 = NULL;
				int32_t banck1 = 0;
				int32_t banck2 = 0;

				p = strtok(string + i, " ");
				unsigned int length = strlen(p) + 1;
				name_1 = malloc(strlen(p) + 1);
				memcpy(name_1, p, strlen(p));
				memcpy(name_1 + strlen(p), "\0", 1);
				p = strtok(NULL, " ");
				banck1 = (int32_t)atoi(p);
				length = length + sizeof(int32_t);
				p = strtok(NULL, " ");
				banck2 = (int32_t)atoi(p);
				length = length + sizeof(int32_t);
				p = strtok(NULL, "\n");
				name_2 = malloc(strlen(p) + 1);
				memcpy(name_2, p, strlen(p));
				memcpy(name_2 + strlen(p), "\0", 1);
				length = length + strlen(p) + 1;
				data->data = calloc(length, 1);
				memcpy(data->data, name_1, strlen(name_1));
				memcpy(data->data + strlen(name_1) + 1, 
				&banck1, sizeof(int32_t));

				memcpy(data->data + strlen(name_1) + 1 + 
				sizeof(int32_t), &banck2, sizeof(int32_t));

				memcpy(data->data + strlen(name_1) + 1 + 
				sizeof(int32_t) + sizeof(int32_t), name_2, strlen(name_2));

				data->header->len = length;

				if (strcmp(command, "insert_at") == 0) {
					add_at(&arr, &len, data, index);
				} else {
					add_last(&arr, &len, data);
				}
				free(data->data);
				free(name_1);
				free(name_2);
			}
		} else {
			if (strncmp(command, "print", 5) == 0) {
				print(arr, len);
			} else {
				if (strncmp(command, "delete_at", 9) == 0) {
					i++;
					char *nr = strtok(string + i, "\n");
					int index = (int)atoi(nr);
					delete_at(&arr, &len, index);
				} else {
					if (strcmp(command, "find") == 0) {
						i++;
						char *nr = strtok(string + i, "\n");
						int index = (int)atoi(nr);
						find(arr, len, index);
					}
				}
			}
		}
		fgets(string, 256, stdin);
	}
	free(string);
	free(arr);
	free(data->header);
	free(data);
	return 0;
}
