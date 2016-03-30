/**
 * @file csv_file.c
 * @author Frederic Simard, Atlants Embedded (frederic.simard.1@outlook.com)
 * @brief feature output interface, initialize a CSV file for feature output.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv_file.h"

/**
 * void* csv_init_file(void *options)
 * @brief Initialize the CSV output interface
 * @param options, options defining the interface
 * @return a pointer to the interface or NULL if invalid
 */
void *csv_init_file(void *options)
{

	/*allocate memory */
	csv_output_t *this_csv = (csv_output_t *) malloc(sizeof(csv_output_t));

	/*copy the options */
	memcpy(&(this_csv->options), options, sizeof(csv_output_options_t));

	/*open a read/write file */
	this_csv->fp = fopen(this_csv->options.filename, "w+");

	/*check if opened correctly */
	if (this_csv->fp == NULL) {
		return NULL;
	}

	/*return the pointer */
	return this_csv;
}

/**
 * int csv_write_in_file(void *feature_buf, void *csv_interface)
 * @brief Writes the data received in a csv file, skipping a line at the end
 * @param feature_buf, (data_t*) feature buffer to be written
 * @param csv_interface, (csv_output_t*) pointer to the csv interface
 * @return if successful, EXIT_SUCCESS, otherwise, EXIT_FAILURE
 */
int csv_write_in_file(void *csv_file_ptr, void *input)
{

	int i;
	/*recast pointers */
	data_t *data = (data_t *) input;
	csv_output_t *this_csv = (csv_output_t *) csv_file_ptr;
	
	
	if(this_csv->options.data_type==DOUBLE_DATA){
		
		double *data_buf = (double *)data->ptr;

		/*check if file valid */
		if (this_csv->fp == NULL) {
			return EXIT_FAILURE;
		}

		/*write feature vector to csv file */
		for (i = 0; i < data->nb_data; i++) {
			fprintf(this_csv->fp, "%lf;", data_buf[i]);
		}

		/*skip a line */
		fprintf(this_csv->fp, "\n");
	}
	else if(this_csv->options.data_type==FLOAT_DATA){
		
		float *data_buf = (float *)data->ptr;

		printf("About to write\n");
		
		/*check if file valid */
		if (this_csv->fp == NULL) {
			return EXIT_FAILURE;
		}
		
		printf("Writing in file\n");
		printf("Nb data = %d\n",data->nb_data);

		/*write feature vector to csv file */
		for (i = 0; i < data->nb_data; i++) {
			printf("%f;",data_buf[i]);
			fprintf(this_csv->fp, "%f;", data_buf[i]);
		}

		/*skip a line */
		printf("\n");
		fprintf(this_csv->fp, "\n");
		
		fflush(this_csv->fp);
	}

	return EXIT_SUCCESS;
}

/**
 * int csv_close_file(void *csv_interface)
 * @brief Close the csv file
 * @param param (unused)
 * @return if successful, EXIT_SUCCESS, otherwise, EXIT_FAILURE
 */
int csv_close_file(void *csv_interface)
{

	/*recast the pointer */
	csv_output_t *this_csv = (csv_output_t *) csv_interface;

	/*check if file is valid */
	if (this_csv->fp == NULL) {
		return EXIT_FAILURE;
	}

	/*close and free the interface memory */
	fclose(this_csv->fp);
	free(this_csv);

	/*done */
	return EXIT_SUCCESS;
}
