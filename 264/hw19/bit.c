#include <assert.h>
#include "bit_writer.h"

BitWriter open_bit_writer(const char* path) {
	return (BitWriter) {.file = fopen(path, "w"), .current_byte = 0, .num_bits_left = 8};
}

void write_bits(BitWriter* a_writer, uint8_t bits, uint8_t num_bits_to_write) {
	assert(num_bits_to_write >= 0 && num_bits_to_write <= 8);
	assert(a_writer -> num_bits_left >= 1 && a_writer -> num_bits_left <=8);
	
	//Checks if there is need for overwriting
	uint8_t emptyLeft = (a_writer -> num_bits_left - num_bits_to_write);
	uint8_t overWrite = 0;
	if(emptyLeft < 0){
		emptyLeft = 0;
		overWrite = emptyLeft * -1;
	}

	uint8_t pulledBit = bits & ~(0xff << num_bits_to_write); //pull to write
	a_writer -> current_byte |= (pulledBit >> overWrite << emptyLeft); //Deletes overwrite, aligns to left
	a_writer -> num_bits_left = emptyLeft;

	if(emptyLeft == 0){ //Writes if storage byte fills then reset
		for(int i = 0; i < 8; i++){
			fprintf(a_writer -> file, "%d", a_writer -> current_byte >> i & (uint8_t)(0x1)); 
		}
		a_writer -> bits = 0;
		a_writer -> num_bits_left = 8;
		if(overWrite > 0){  //If there are more bits to be read
			write_bits(a_writer, bits, overWrite);
		}
	}

	assert(a_writer -> num_bits_left >= 1 && a_writer -> num_bits_left <=8);
}

void flush_bit_writer(BitWriter* a_writer) {
	for(int i = 0; i < 8; i++){
		fprintf(a_writer -> file, "%d", a_writer -> current_byte >> i & (uint8_t)(0x1));
	} 
	a_writer -> current_byte = 0;
	a_writer -> num_bits_left = 8;
}

void close_bit_writer(BitWriter* a_writer) {
	flush_bit_writer(a_writer);
	fclose(a_writer -> file);
	a_writer -> file = NULL;
}

#define __BIT_WRITER_C_V1__
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab colorcolumn=96: */
