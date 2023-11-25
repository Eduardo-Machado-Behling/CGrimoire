#include "CGrimoire/string.h"
#include "CGrimoire/vector.h"

typedef struct cg_string_t {
    cg_vector_t *data;

    cg_iterator_t *it;
} cg_string_t;

cg_string_t *cg_string_create(size_t initial_size) {
    cg_string_t *str;
    CG_SAFE_ALLOC(str, sizeof(cg_string_t), return NULL);

    str->data = cg_vector_create(initial_size, sizeof(char));
    if (!str->data) {
        cg_string_destroy(&str);
        return NULL;
    }
    str->it = cg_iterator_create();
    if (!str->it) {
        cg_string_destroy(&str);
        return NULL;
    }

    return str;
}
cg_string_t *cg_string_copy(cg_string_t *str, cg_string_t *other);

cg_string_t *cg_string_create_from_cstr(const char *cstr, size_t len) {
    cg_string_t *str = cg_string_create(len * 2);

    for (size_t i = 0; i < len; i++)
        cg_vector_push_back(str->data, CG_AS_MEMORY(cstr[i]));

    return str;
}

cg_string_t *cg_string_assign(cg_string_t *str, const char *cstr) {
    for (size_t i = 0; cstr[i]; i++) {
        if (i < cg_vector_size(str->data))
            cg_vector_change(str->data, i, CG_AS_MEMORY(cstr[i]));
        else
            cg_vector_push_back(str->data, CG_AS_MEMORY(cstr[i]));
    }

    return str;
}

size_t cg_string_len(cg_string_t *str) { return cg_vector_size(str->data); }
bool cg_string_empty(cg_string_t *str) { return cg_vector_empty(str->data); }

char cg_string_at(cg_string_t *str, size_t index) {
    char ch = '\0';
    cg_vector_at(str->data, index, CG_AS_MEMORY(ch));
    return ch;
}
char cg_string_front(cg_string_t *str) {
    char ch = '\0';
    cg_vector_front(str->data, CG_AS_MEMORY(ch));
    return ch;
}
char cg_string_back(cg_string_t *str) {
    char ch = '\0';
    cg_vector_back(str->data, CG_AS_MEMORY(ch));
    return ch;
}
char *cg_string_cstr(cg_string_t *str, char *cstr) {
    if (!cstr)
        CG_SAFE_ALLOC(cstr, cg_vector_size(str->data) + 1, return NULL);

    size_t i = 0;
    for (cg_vector_begin(str->data, str->it); cg_iterator_distance(str->it, cg_vector_cend(str->data)) > 0; cg_iterator_next(str->it, 1), i++) {
        cstr[i] = CG_ITERATOR_GET_DATA(str->it, char);
    }
    cstr[i] = '\0';
    return cstr;
}

cg_string_t *cg_string_append(cg_string_t *str, const char ch) {
    if (!cg_vector_push_back(str->data, CG_AS_MEMORY(ch)))
        return NULL;
    return str;
}
cg_string_t *cg_string_append_range(cg_string_t *str, const char *cstr) {
    if (!cg_vector_push_back_range(str->data, CG_AS_MEMORY(cstr), strlen(cstr)))
        return NULL;
    return str;
}
cg_string_t *cg_string_change(cg_string_t *str, size_t index, const char ch) {
    if (!cg_vector_change(str->data, index, CG_AS_MEMORY(ch)))
        return NULL;
    return str;
}
cg_string_t *cg_string_insert(cg_string_t *str, size_t index, const char ch) {
    if (!cg_vector_insert(str->data, index, CG_AS_MEMORY(ch)))
        return NULL;
    return str;
}
cg_string_t *cg_string_insert_range(cg_string_t *str, size_t index, const char *cstr) {
    if (!cg_vector_insert_range(str->data, index, CG_AS_MEMORY(cstr), strlen(cstr)))
        return NULL;
    return str;
}
cg_string_t *cg_string_replace(cg_string_t *str, const char *from, const char *to);

bool cg_string_starts_with(cg_string_t *str, const char *cstr) {
    size_t i = 0;
    for (cg_vector_begin(str->data, str->it); cg_iterator_distance(str->it, cg_vector_cend(str->data)) > 0 && cstr[i]; cg_iterator_next(str->it, 1), i++) {
        if (cstr[i] != CG_ITERATOR_GET_DATA(str->it, char))
            return false;
    }
    return true;
}
bool cg_string_ends_with(cg_string_t *str, const char *cstr) {
    size_t len = strlen(cstr);
    for (size_t i = 0; i < len; i++) {
        size_t ri = cg_vector_size(str->data) - i - 1;
        size_t rj = len - i - 1;
        char at;
        cg_vector_at(str->data, ri, CG_AS_MEMORY(at));
        if (at != cstr[rj])
            return false;
    }

    return true;
}
bool cg_string_contains(cg_string_t *str, const char *cstr) {
    size_t i = 0;
    bool found = false, contains = false;
    for (cg_vector_begin(str->data, str->it); cg_iterator_distance(str->it, cg_vector_cend(str->data)) > 0 && cstr[i]; cg_iterator_next(str->it, 1)) {
        char ch = CG_ITERATOR_GET_DATA(str->it, char);
        if (!found && cstr[i] == ch) {
            found = true;
            contains = true;
        }

        if (found && cstr[i++] != ch) {
            cg_iterator_prev(str->it, i - 1);
            found = false;
            contains = false;
            i = 0;
        }
    }
    return contains;
}
bool cg_string_equal(cg_string_t *str, const char *cstr) {
    size_t len = strlen(cstr);

    if (len != cg_vector_size(str->data))
        return false;

    size_t i = 0;
    for (cg_vector_begin(str->data, str->it); cg_iterator_distance(str->it, cg_vector_cend(str->data)) > 0; cg_iterator_next(str->it, 1), i++) {
        if (cstr[i] != CG_ITERATOR_GET_DATA(str->it, char))
            return false;
    }
    return true;
}

cg_string_t *cg_string_substr(cg_string_t *str, cg_string_t *dest);

void cg_string_destroy(cg_string_t **string) {
    if (!string)
        return;

    cg_string_t *str = *string;
    *string = NULL;

    if (str)
        return;

    if (str->data)
        cg_vector_destroy(&str->data);
    if (str->it)
        cg_iterator_destroy(str->it);
}