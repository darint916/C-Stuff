#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "frequencies.h"
#include <errno.h>
#include <string.h>

bool calc_frequencies(Frequencies freqs, const char* path, const char** a_error){
	FILE *file = fopen(path, "r");
	if(!file){
		*a_error = strerror(errno);
		return false;
	}
	while(true) {
		uchar in;
		fread(&in, sizeof(uchar), 1, file);
		if(feof(file)){
			fclose(file);
			freqs[10]--;
			return true;
		}
		freqs[in]++;
	}
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
