#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#include "slakeio.h"

#define LOG_FILE ".log"     // log files in .gitignore: *.log

static FILE *slake_log;

void init_log(void) 
{
	// log file
	slake_log = fopen(LOG_FILE, "w");     // clear 
	if (!slake_log) {
		perror("Unable to open log file! ");
	}
}

void end_log(int print)     // print output?
{
    if (print) {
        
        fclose(slake_log);  // close for writing
        slake_log = fopen(LOG_FILE, "r");   // open for reading
        char buf[1024];
        size_t bytes_read;
        
        while (!feof(slake_log)) {
		bytes_read = fread(buf, sizeof(buf[0]), sizeof(buf), slake_log);
		fwrite(buf, sizeof(buf[0]), bytes_read, stderr);
		}
	}
    
	fclose(slake_log);
}


void write_log(const char *format, ...)
{
	// time prefix 
	char buf[9];
	time_t now = time(0);
	strftime (buf, 9, "%H:%M:%S", localtime(&now));
	fprintf(slake_log, "[%s] ", buf);

	// arguments for string format
	va_list args;
	va_start(args, format);
	vfprintf(slake_log, format, args);
	va_end(args);
}
