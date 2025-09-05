
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>

#include "./include/parser.h"
#include "./utils/str.h"
#include "./utils/os.h"


static char *read_string(const char **text)
{
    const char *start = *text;
    while (**text != '[' && **text != '\0') {
	(*text)++;
    }
    size_t   length = (size_t)(*text - start);
    char *result = (char*)malloc(length + 1);
    strncpy(result, start, length);
    result[length] = '\0';
    return result;
}

// NOTE: It doesn't seem to be the better approach. Perhaps merging all these functions into a monolith one.
char *read_header(const char **text)
{
    if (**text != '[') return NULL;
    (*text)++;
    
    if (strncmp(*text, "header]", 7) == 1)  return NULL;
    *text += 7;
    
    char *result = read_string(text);
    
    if (strncmp(*text, "[header]", 8) == 0) {
	(*text) += 8;
    };
    return result;
}

char *read_para(const char **text)
{
    if (**text != '[') return NULL;
    (*text)++;
    
    if (strncmp(*text, "para]", 5) == 1)  return NULL;
    *text += 5;
    
    char *result = read_string(text);
    
    if (strncmp(*text, "[para]", 6) == 0) {
	(*text) += 6;
    };
    return result;
}

char *read_link(const char **text)
{
    if (**text != '[') return NULL;
    (*text)++;
    
    if (strncmp(*text, "link]", 5) == 1)  return NULL;
    *text += 5;
    
    char *result = read_string(text);
    
    if (strncmp(*text, "[link]", 6) == 0) {
	(*text) += 6;
    };
    return result;
}

void jump_space(const char ** text)
{
    while(**text == ' ' || **text == '\n') {
	(*text)++;
    }
    return;
}

RadownValue *parse(const char **text)
{
    jump_space(text);
    
    if (strncmp(*text, "[para]", 6) == 0) {
	RadownValue *value = malloc(sizeof(RadownValue));
	value->type = TYPE_PARA;
	value->value = read_para(text);
	return value;
    }
    else if (strncmp(*text, "[header]", 8) == 0) {
	RadownValue *value = malloc(sizeof(RadownValue));
	value->type = TYPE_HEADER;
	value->value = read_header(text);
	return value;
    }
    else if (strncmp(*text, "[link]", 6) == 0) {
	RadownValue *value = malloc(sizeof(RadownValue));
	value->type = TYPE_LINK;
	value->value = read_link(text);
	return value;
    }
    return NULL;
}

char *lexer(const char *tmp)
{
    RadownValue *main = parse(&tmp);
    char *content = "";
    while (main != NULL) {
	char *_old = content;
	char *_new = "";
	if (main->type == TYPE_HEADER) {
	    const char *tag = "<h1></h1>";
	    size_t length = (strlen(main->value) + strlen(tag) + 1);
	    _new = (char*)malloc(length);
	    
	    snprintf(_new, length, "<h1>%s</h1>", main->value);
	}
	else if (main->type == TYPE_PARA) {
	    const char *tag = "<p></p>";
	    size_t length = (strlen(main->value) + strlen(tag) + 1);
	    _new = (char*)malloc(length);
	    
	    snprintf(_new, length, "<p>%s</p>", main->value);
	}
	else if (main->type == TYPE_LINK) {
	    // TODO: refactor it.
	    const char *tag = "<a href=''></a>";
	    size_t length = ((strlen(main->value) * 2) + strlen(tag) + 1);
	    _new = (char*)malloc(length);
	    
	    snprintf(_new, length, "<a href='%s'>%s</a>", main->value, main->value);
	}
	size_t total_length = (strlen(_old) + strlen(_new) + 1);
	content = (char*)malloc(total_length);
	snprintf(content, total_length, "%s%s", _old, _new);
	main = parse(&tmp);
    }
    printf("\n%s\n\n", content);
    free(main);
    return content;
}

