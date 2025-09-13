
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>

#include "./include/request_handler.h"
#include "./include/parser.h"
#include "./utils/str.h"
#include "./utils/os.h"

#define CURRENT_PROJECT_FOLDER "../../moc_project/"
#define CURRENT_FILE CURRENT_PROJECT_FOLDER"main.rd"
#define BUFFER_SIZE 1024

static const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

static char *get_filename(const char *filename) {
    char *last_extension;
    char *result;
    if (filename == NULL) return NULL;
    if ((result = malloc(strlen (filename) + 1)) == NULL) return NULL;
    strcpy(result, filename);
    last_extension = strrchr(result, '.');
    if (last_extension != NULL) *last_extension = '\0';
    return result;
}

static const char *translate_content(const char *current_file)
{
    char *file = load_file(current_file);
    if (!file) {
	fprintf(stderr, "[FAILED] : Main file could not be loaded.\n");
	return NULL;
    }
    const char *content = lexer((char const *)file);
    if (content == NULL) {
	fprintf(stderr, "[FAILED] : Failed to parse main file.\n");
	return NULL;
    }
    return content;
}

static int render_content()
{
    struct dirent *directory_entry;
    DIR *directory;
    
    if ((directory = opendir(CURRENT_PROJECT_FOLDER)) == NULL) {
	fprintf(stderr, "[FAILED] : Porject folder could not be opened.\n");
	return -1;
    }
    while ((directory_entry = readdir(directory)) != NULL) {
	const char *file_ext = get_filename_ext(directory_entry->d_name);
	
	if (strcmp(file_ext, "rd") == 0) {
	    // printf("[INFO] : %s\n", directory_entry->d_name);
	    const char *templ  = file_to_char("../../index.html");
	    size_t file_path_length = strlen(CURRENT_PROJECT_FOLDER) + strlen(directory_entry->d_name) + 1;
	    char *file_path;
	    if ((file_path = (char*)malloc(file_path_length)) == NULL) { fprintf(stderr, "[FAILED] Failed to allocated memory blah blah blah.\n"); return -1; }
	    snprintf(file_path, file_path_length, "%s%s", CURRENT_PROJECT_FOLDER, directory_entry->d_name);
	    const char *result = translate_content(file_path);
	    
	    if (templ == NULL || result == NULL) {
		fprintf(stderr, "[FAILED] : Failed to load content.\n");
		return -1;
	    }
	    char *content = strrep(templ, "[content]", result);
	    if (content == NULL) {
		fprintf(stderr, "[FAILED] : Failed to inject Radown files content into HTML template.\n");
		return -1;
	    }
	    mkdir(CURRENT_PROJECT_FOLDER"bin", 0777);
	    char *filename = get_filename(directory_entry->d_name);
	    
	    size_t length = strlen(CURRENT_PROJECT_FOLDER"bin/") + strlen(filename) + strlen(".html") + 1;
	    char *new_file_path;
	    if ((new_file_path = (char*)malloc(length)) == NULL) {
		fprintf(stderr, "[FAILED] : Failed at allocating memory into filepath string.\n");
		return -1;
	    }
	    snprintf(new_file_path, length, "%s%s.html", CURRENT_PROJECT_FOLDER"bin/", filename);
	    FILE *new_html;
	    if ((new_html = fopen(new_file_path, "w")) == NULL) {
		fprintf(stderr, "[FAILED] : New html script file could not be created.\n");
		return -1;
	    }
	    free(filename);
	    fprintf(new_html, "%s", content);
	    fclose(new_html);
	    continue;
	}
    }
    closedir(directory);
    return 0;
}

int handle_client(int socket)
{
    char buffer[BUFFER_SIZE] = { 0 };
    read(socket, buffer, BUFFER_SIZE);
    render_content();
    
    const char *content = file_to_char(CURRENT_PROJECT_FOLDER"bin/main.html");
    if (content) {
	const char *http_header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
	write(socket, http_header, strlen(http_header));
	write(socket, content, strlen(content));
    } else {
	const char* not_found_response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>404 Not Found</h1>";
	write(socket, not_found_response, strlen(not_found_response));
	close(socket);
	return -1;
    }
    close(socket);
    return 0;
}
