#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "coconut.h"
#include "string_macros.h"
#include "utils.h"

// Fatal black
// Major red
// Minor yellow
// Info cyan
static const char *colors[4] = {
    "\x1b[30m\x1b[2m",
    "\x1b[31m",
    "\x1b[33m",
    "\x1b[36m"};

static void write_verbose(const error_content_t *error)
{
    FILE *file = NULL;
    char *line = NULL;
    size_t len = 0;
    int line_nb = 0;

    if (is_object_file(error->filepath) == true)
        return;
    file = fopen(error->filepath, "r");
    if (is_file_stream_null(file, "Error opening file\n"))
        return;
    line_nb = atoi(error->line);
    for (int i = 0; i < line_nb && getline(&line, &len, file) != -1; i++);
    line[strlen(line) - 1] = 0;
    printf("        │ -> %.120s\n", line);
    if (line)
        free(line);
    fclose(file);
}

static void write_formatted_error(const error_content_t *error, int error_nb)
{
    char *error_message = NULL;
    const char *color_code = NULL;

    color_code = colors[error->severity];
    error_message = get_error_message(error->error_code);
    printf(ERROR_STR, error_nb, color_code, error->filepath, error->line,
        5 - (int)strlen(error->line), "     ", error->error_code,
        &error_message[4]);
}

// Looks ugly?
// Might need to refactor
//
// First two lines always have a space inbetween
// because going from empty to value changes the value
static bool add_space_between_errors(
    int sort_mask, const error_content_t *error)
{
    static char *last_value = "";
    static int last_number = -1;

    if (sort_mask == 0 && strcmp(last_value, error->filepath) != 0) {
        last_value = error->filepath;
        return true;
    }
    if (sort_mask == 1 && strcmp(last_value, error->error_code) != 0) {
        last_value = error->error_code;
        return true;
    }
    if (sort_mask == 2 && last_number != error->severity) {
        last_number = error->severity;
        return true;
    }
    return false;
}

void write_errors(
    const error_content_t *errors,
    const error_stats_t *stats,
    const arguments_t *arguments)
{
    for (int i = 0; i < stats->total; i++) {
        if (arguments->add_spaces && i != 0 &&
            add_space_between_errors(arguments->sort_mask, &errors[i]))
            write(1, "\n", 1);
        write_formatted_error(&errors[i], i + 1);
        if (arguments->verbose)
            write_verbose(&errors[i]);
    }
}
