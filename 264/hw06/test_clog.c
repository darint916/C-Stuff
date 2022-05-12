#include <stdlib.h>
#include "clog.h"
#include <stdio.h>
int main(int argc, char* argv[]) {
//	char* city_name = "Bogota";
//	int population_pct = 15;
//	char* a_n = city_name;
	
	logf_red("%d%% of Columbians live in %s.\n", population_pct, city_name);
	logf_blue("wabba\n");
	logf_red("%s\n", "RED");
	logf_cyan("oog\n");
	logf_green("g\n");
	logf_magenta("test\n");
	logf_yellow("test\n");
	log_int(3+4);
	log_int(population_pct);
	log_char('A');
	log_char(65);
	log_char(city_name[0]);
	log_str(city_name);
	log_addr(city_name);
	log_addr(a_n);
	log_addr(&city_name);
	log_float(0.5 / 2.0);
	log_bool(3 > 5);
	log_bool(3 > 1);
	return EXIT_SUCCESS;
}
