#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "c_lang_task.h"

#define endl printf("\n"); 

void print_stars(short);
// void write_nils_to_head_file_with_deleting(const char*);

int main(void) {
	TEST_memcpy_and_memset();
	endl;
	endl;
	TEST_read_i_string_from_file();

	// write_nils_to_head_file_with_deleting("test.txt");

	system("pause");
	return 0;
}

void print_number_table(short col, short raw) {
	// 
	int** table = (int**)calloc(raw, sizeof(int*));
	for (int i = 0; i < raw; i++) {
		table[i] = (int*)calloc(col, sizeof(int));
	}

	// Main part
	print_stars(col);
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < raw; j++) {
			table[i][j] = rand() % 10;
			if (j != raw - 1) {
				printf("|%d", table[i][j]);
			} 
			else {
				printf("|%d|", table[i][j]);
			}
		}
		endl;
		if (i != col - 1) {
			for (int j = 0; j < raw; j++) {
				if (j != raw - 1) {
					printf("|+");
				}
				else {
					printf("|+|");
				}
			}
			endl;
		}
	}
	print_stars(col);

	// Memory freeing
	for (int i = 0; i < raw; i++) {
		free(table[i]);
	}
	free(table);
}

void print_stars(short col) {
	printf(" ");
	for (int i = 0; i < col; i++) {
		if (i != col - 1) {
			printf("**");
		}
		else {
			printf("*");
		}
	}
	endl;
}

void write_nils_to_head_file(const char* full_fname, int N) {
	// Copy file to buffer
	FILE *main_file = fopen(full_fname, "a+");
	if (main_file == NULL) {
		printf("Missing file your file\n");
		return;
	}
	FILE *buffer = fopen("buffer.txt", "w");
	if (buffer == NULL) {
		fclose(main_file);
		printf("Missing file \"buffer.txt\"\n");
		return;
	}
	unsigned char char_buffer;
	fseek(main_file, 0, SEEK_SET);
	while (1) {
		fread(&char_buffer, 1, 1, main_file);
		if (feof(main_file)) {
			break;
		}
		fwrite(&char_buffer, 1, 1, buffer);
	}
	fclose(main_file);
	fclose(buffer);

	
	// Rewrite file
	main_file = fopen(full_fname, "w");
	if (main_file == NULL) {
		printf("Missing file your file\n");
		return;
	}
	buffer = fopen("buffer.txt", "r");
	if (buffer == NULL) {
		fclose(main_file);
		printf("Missing file \"buffer.txt\"\n");
		return;
	}
	char_buffer = 0x00;
	for (int i = 0; i < N; i++) {
		fwrite(&char_buffer, 1, 1, main_file);
	}
	fseek(buffer, 0, SEEK_SET);
	while (1) {
		fread(&char_buffer, 1, 1, buffer);
		if (feof(buffer)) {
			break;
		}
		fwrite(&char_buffer, 1, 1, main_file);
	}
	fclose(main_file);
	fclose(buffer);	
}

void write_ones_to_tail_file(const char* full_fname, int N) {
	FILE *main_file = fopen(full_fname, "r+");
	if (main_file == NULL) {
		printf("Missing your file\n");
		return;
	}
	unsigned char byte = 0xff;
	fseek(main_file, 0, SEEK_END);
	for (int i = 0; i < N; i++) {
		fwrite(&byte, 1, 1, main_file);
	}
	fclose(main_file);
}

int read_i_string_from_file(const char* full_fname, int i, char* out_str, int max_sz) {
	FILE *main_file = fopen(full_fname, "r");
	if (main_file == NULL) {
		printf("Missing your file\n");
		return 0;
	}
	char* buffer = (char*)calloc(80, sizeof(char));
	for (int current_string_number = 0; current_string_number < i; current_string_number++) {
		fgets(buffer, 80, main_file);
	}
	free(buffer);
	int amout_of_written_symbols = 0;
	char small_buffer;
	while (1) {
		fread(&small_buffer, 1, 1, main_file);
		if (small_buffer == '\n' || amout_of_written_symbols >= max_sz) {
			break;
		}
		if (feof(main_file)) {
			return amout_of_written_symbols;
		}
		out_str[amout_of_written_symbols] = small_buffer;
		amout_of_written_symbols++;
	}
	// out_str[amout_of_written_symbols + 1] = '\0';
	// amout_of_written_symbols++;
	fclose(main_file);

	return amout_of_written_symbols;
}

void TEST_memcpy_and_memset(void) {
	// Creating
	char* array_of_char = (char*)calloc(80, sizeof(char));
	int* array_of_int = (int*)calloc(40, sizeof(int));
	double* array_of_double = (double*)calloc(20, sizeof(double));

	// Reassigning memory
	memset(array_of_char, 0x01, sizeof(char) * 80);
	for (int i = 0; i < 40; i++) {
		memset(array_of_int + i, 0x00, 3);
		memset(array_of_int + i, 0x01, 1);
	}
	memset(array_of_double, 0x0, sizeof(double) * 20);

	// Print
	for (int i = 0; i < 10; i++) {
		printf("%c | ", array_of_char[i]);
	}
	endl;
	for (int i = 0; i < 10; i++) {
		printf("%d | ", array_of_int[i]);
	}
	endl;
	for (int i = 0; i < 10; i++) {
		printf("%f | ", array_of_double[i]);
	}
	endl;

	// Copy memory
	memcpy(array_of_char, array_of_int, sizeof(char) * 80);
	memcpy(array_of_int, array_of_double, sizeof(int) * 40);
	memcpy(array_of_double, array_of_char, sizeof(char) * 80);
	
	// Print
	for (int i = 0; i < 10; i++) {
		printf("%c | ", array_of_char[i]);
	}
	endl;
	for (int i = 0; i < 10; i++) {
		printf("%d | ", array_of_int[i]);
	}
	endl;
	for (int i = 0; i < 10; i++) {
		printf("%f | ", array_of_double[i]);
	}
	endl;

	free(array_of_char);
	free(array_of_int);
	free(array_of_double);
}

void TEST_read_i_string_from_file(void) {
	// Creating array of strings
	char** test_str = (char**)calloc(5, sizeof(char*));
	for (int i = 0; i < 5; i++) {
		test_str[i] = (char*)calloc(10, sizeof(char));
	}

	// Write array in file "test_str.txt"
	FILE *main_file = fopen("test_str.txt", "w");
	if (main_file == NULL) {
		printf("Missing file \"test_str.txt\"\n");
		return;
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			test_str[i][j] = 'a' + (rand() % 10);
			fwrite(&test_str[i][j], sizeof(char), 1, main_file);
		}
		fputc('\n', main_file);
	}
	fclose(main_file);

	// Free memory
	for (int i = 0; i < 5; i++) {
		free(test_str[i]);
	}
	free(test_str);

	char* out_str = (char*)calloc(15, sizeof(char));

	// out_str > i-string
	read_i_string_from_file("test_str.txt", 3, out_str, 10);
	printf("%s\n", out_str);

	free(out_str);

	out_str = (char*)calloc(6, sizeof(char));

	// out_str < i-string
	read_i_string_from_file("test_str.txt", 4, out_str, 5);
	printf("%s\n", out_str);

	// i-string - non-existent
	read_i_string_from_file("test_str.txt", 10, out_str, 4);
	printf("%s\n", out_str);

	free(out_str);
}

//void write_nils_to_head_file_with_deleting(const char* full_fname) {
//	FILE *main_file = fopen(full_fname, "r+b");
//	if (main_file == NULL) {
//		printf("Error");
//		return;
//	}
//	fseek(main_file, 0, SEEK_SET);
//	unsigned char byte = 0x00;
//	fputc(byte, main_file);
//	fclose(main_file);
//}