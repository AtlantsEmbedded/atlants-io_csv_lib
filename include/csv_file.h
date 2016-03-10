#ifndef CSV_FILE_H
#define CSV_FILE_H
/**
 * @file csv_file.h
 * @author Frederic Simard, Atlants Embedded (frederic.simard.1@outlook.com)
 * @brief Handles the CSV file function pointers
 */

/**Structure containing the configuration of the CSV output including number of channels*/
typedef struct csv_output_options_s {

	char *filename;
	int nb_data_channels;

} csv_output_options_t;

/** Structure which contains information the CSV*/
typedef struct csv_output_s {

	csv_output_options_t options;
	FILE *fp;

} csv_output_t;

/** defines the data structure that contains the data to be sent*/
typedef struct data_s {
	float *ptr;
	int nb_data;
} data_t;

void *csv_init_file(void *param);
int csv_write_in_file(void *csv_file_ptr, void *input);
int csv_close_file(void *csv_file_ptr);

#endif
