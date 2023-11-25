#pragma once

#include "CGrimoire/details/defines.h"

typedef struct cg_string_t cg_string_t;

cg_string_t *cg_string_create(size_t initial_size);
cg_string_t *cg_string_copy(cg_string_t *str, cg_string_t *other);

cg_string_t *cg_string_create_from_cstr(const char *cstr, size_t len);

cg_string_t *cg_string_assign(cg_string_t *str, const char *cstr);

size_t cg_string_len(cg_string_t *str);
bool cg_string_empty(cg_string_t *str);

char cg_string_at(cg_string_t *str, size_t index);
char cg_string_front(cg_string_t *str);
char cg_string_back(cg_string_t *str);
char *cg_string_cstr(cg_string_t *str, char *cstr);

cg_string_t *cg_string_append(cg_string_t *str, const char ch);
cg_string_t *cg_string_append_range(cg_string_t *str, const char *cstr);
cg_string_t *cg_string_change(cg_string_t *str, size_t index, const char ch);
cg_string_t *cg_string_insert(cg_string_t *str, size_t index, const char ch);
cg_string_t *cg_string_insert_range(cg_string_t *str, size_t index, const char *cstr);
cg_string_t *cg_string_replace(cg_string_t *str, const char *from, const char *to);

bool cg_string_starts_with(cg_string_t *str, const char *cstr);
bool cg_string_ends_with(cg_string_t *str, const char *cstr);
bool cg_string_contains(cg_string_t *str, const char *cstr);
bool cg_string_equal(cg_string_t *str, const char *cstr);

cg_string_t *cg_string_substr(cg_string_t *str, cg_string_t *dest);

cg_string_t *cg_string_reserve(cg_string_t *str, size_t new_size);

void cg_string_destroy(cg_string_t **str);