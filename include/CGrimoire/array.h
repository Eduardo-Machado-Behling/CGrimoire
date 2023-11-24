#pragma once

#include "CGrimoire/details/defines.h"
#include "CGrimoire/iterator.h"

#define CG_ARRAY_INVALID_POS SIZE_MAX
#define CG_ARRAY_INVALID_ELEM_SIZE SIZE_MAX

/// @brief A array, use cg_array_create to get a instance and cg_array_destroy to free,
/// and the cg_array_* methods to manipulate this data structure.
typedef struct cg_array_t cg_array_t;

/// @brief creates a array, the ownership is yours.
/// @param capacity how many elements to store.
/// @param element_size_in_bytes how many Bytes each element occupy. use sizeof()
/// @return return a heap allocated array, that will need to be cleared with cg_array_destroy().
/// can return NULL if the memory allocation fails.
cg_array_t *cg_array_create(size_t capacity, size_t element_size_in_bytes);

/// @brief create a copy of OTHER, the OTHER isn't mutated, the ownership is yours
/// @param other the cg_array to copy from.
/// @return return a heap copy of the OTHER array, that will need to be cleared with cg_array_destroy().
/// can return NULL if the memory allocation fails or OTHER is a invalid cg_array_t.
cg_array_t *cg_array_copy(cg_array_t *array, const cg_array_t *other);

cg_array_t *cg_array_move(cg_array_t *array, cg_array_t **other);

/// @brief resizes a cg_array_t to be NEW_SIZE long
/// @param array a initialized cg_array_t.
/// @param new_size
/// @return true if successful, can fail on memory allocation or when passed a invalid ARRAY.
cg_array_t *cg_array_reserve(cg_array_t *array, size_t new_size);

/// @brief gets the element at INDEX from ARRAY and puts its value into DEST.
/// @param array cg_array to search element from.
/// @param index index of the element in the ARRAY.
/// @param dest a pointer to a variable with the same datatype as the ones stored in the array. use CG_AS_MEMORY(x) to pass the variable to store the element.
/// @return true if successful, can fail if ARRAY or DEST are invalid pointers or index is bigger than the array.
const cg_array_t *cg_array_at(const cg_array_t *array, size_t index, byte_t *dest);

/// @brief insert the DATA value into the INDEX position of the ARRAY
/// @param array the cg_array to insert the value.
/// @param index position that DATA will be inserted to.
/// @param data a pointer of the same datatype as the ones the array holds. the value in this pointer will be inserted, use CG_AS_MEMORY(<var>).
/// @return true if successful.
cg_array_t *cg_array_change(cg_array_t *array, size_t index, const byte_t *data);

/// @param array a cg_array_t.
/// @return the size of the array.
size_t cg_array_capacity(const cg_array_t *array);

/// @param array a cg_array_t.
/// @return the size in Bytes of the elements being stored in ARRAY.
size_t cg_array_element_size(const cg_array_t *array);

/// @brief assigns the values in C_ARRAY to the ARRAY, C_ARRAY and ARRAY must have the same size.
/// @param array a cg_array_t
/// @param c_array a pointer to a C array of elements, use CG_AS_MEMORY(<var>).
/// @return true if successful
cg_array_t *cg_array_assign(cg_array_t *array, const byte_t *c_array);

cg_array_t *cg_array_assign_range(cg_array_t *array, size_t start, const byte_t *c_array, size_t c_array_sizes);

iterator_t *cg_array_begin(cg_array_t *array, iterator_t *it);
iterator_t *cg_array_end(cg_array_t *array, iterator_t *it);

const iterator_t *cg_array_cbegin(cg_array_t *array);
const iterator_t *cg_array_cend(cg_array_t *array);

/// @brief swaps the contents of DEST with SOURCE
/// @return true if successful
cg_array_t *cg_array_swap(cg_array_t *dest, cg_array_t *source);

/// @brief fill all elements of ARRAY with the VALUE
/// @param array a cg_array_t.
/// @param value a pointer to the value to be stored, use CG_AS_MEMORY(<var>).
/// @return true if successful.
cg_array_t *cg_array_fill(cg_array_t *array, const byte_t *value);

/// @brief resizes ARRAY to NEW_SIZE and assigns the default value DATA to allocated elements, if NEW_SIZE < ARRAY's capacity does nothing.
/// @param array a cg_array_t
/// @param new_size new_size to ARRAY
/// @param data a pointer to the data to used as default values.
/// @return true if successful, can fail if memory allocation fails or invalid DATA or ARRAY are passed.
cg_array_t *cg_array_resize(cg_array_t *array, size_t new_size, const byte_t *data);

/// @brief free appropriately a instance of cg_array_t.
/// @param array the cg_array_t.
void cg_array_destroy(cg_array_t *array);