#include <stdio.h>
#include <stdlib.h>
#include "count_words.h"

int main(int argc, char* argv[]) {

	printf("count_words(\"My apples are sweet.\") == %d\n",
	        count_words("My apples are sweet."));

	printf("count_words(\"My friend's apples are sweeter.\") == %d\n",
	        count_words("My friend's apples are sweeter."));

	printf("count_words(\"A pear is sweeter than an apple..\") == %d\n",
	        count_words("A pear is sweeter than an apple.."));

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
