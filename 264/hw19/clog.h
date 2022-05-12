#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#ifndef __CLOG_H__
#define __CLOG_H__

#ifndef NDEBUG
#    define logf_(...) printf(__VA_ARGS__)
#else 
#    define logf_(...)
#endif

#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_BLUE "\x1b[34m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_CYAN "\x1b[36m"
#define ANSI_RESET "\x1b[0m"
#    define log_float(n) logf_("%s == %.016f\n", #n, n)
#    define log_bool(n) logf_("%s == %s\n", #n, n?"true":"false")
#    define log_msg(msg) logf_("%s", msg)
#    define log_int(n) logf_("%s == %d\n", (#n), (n))
#    define log_str(s) logf_("%s == \"%s\"\n", #s, s)
#    define log_char(ch) logf_("%s == '%c'\n", #ch, ch)
#    define log_addr(addr) logf_("%s == %p\n", #addr, (void*) addr)
#    define logf_red(...)  __mu_log_color(ANSI_RED, __VA_ARGS__)
#    define logf_green(...)  __mu_log_color(ANSI_GREEN, __VA_ARGS__)
#    define logf_yellow(...)  __mu_log_color(ANSI_YELLOW, __VA_ARGS__)
#    define logf_blue(...)  __mu_log_color(ANSI_BLUE, __VA_ARGS__)
#    define logf_magenta(...)  __mu_log_color(ANSI_MAGENTA, __VA_ARGS__)
#    define logf_cyan(...)  __mu_log_color(ANSI_CYAN, __VA_ARGS__)
#    define __mu_log_color(ansi_color_code, ...) \
	do { \
		if(isatty(STDOUT_FILENO)){ \
			printf(ansi_color_code); \
		}\
		logf_(__VA_ARGS__); \
		if(isatty(STDOUT_FILENO)){\
			printf(ANSI_RESET); \
		}\
	} while(0)
#endif
