#pragma once

#include "CGrimoire/details/defines.h"

#define CG_ARRAY_NPOS SIZE_MAX

/// @brief A array, use cg_array_create to get a instance and cg_array_destroy to free,
/// and the cg_array_* methods to manipulate this data structure.
typedef struct cg_array_t cg_array_t;

/// @brief creates a array, the ownership is yours.
/// @param capacity how many elements to store.
/// @param element_size_in_bytes how many Bytes each element occupy. use sizeof()
/// @return return a heap allocated array, that will need to be cleared with cg_array_destroy().
cg_array_t *cg_array_create(size_t capacity, size_t element_size_in_bytes);

/// @brief create a copy of OTHER, the OTHER isn't mutated, the ownership is yours
/// @param other the cg_array to copy from.
/// @return return a heap copy of the OTHER array, that will need to be cleared with cg_array_destroy().
cg_array_t *cg_array_copy(const cg_array_t *other);

/// @brief gets the element at INDEX from ARRAY and puts its value into DEST.
/// @param array cg_array to search element from.
/// @param index index of the element in the ARRAY.
/// @param dest a pointer to a variable with the same datatype as the ones stored in the array. use AS_MEMORY(x) to pass the variable to store the element.
/// @return true if successful
bool cg_array_at(const cg_array_t *array, size_t index, byte_t *dest);

/// @brief insert the DATA value into the INDEX position of the ARRAY
/// @param array the cg_array to insert the value.
/// @param index position that DATA will be inserted to.
/// @param data a pointer of the same datatype as the ones the array holds. the value in this pointer will be inserted, use AS_MEMORY(<var>).
/// @return true if successful.
bool cg_array_insert(cg_array_t *array, size_t index, const byte_t *data);

/// @brief return the size of the ARRAY.
/// @param array a cg_array_t.
/// @return the size of the array.
size_t cg_array_size(const cg_array_t *array);

/// @brief assigns the values in C_ARRAY to the ARRAY, C_ARRAY and ARRAY must have the same size.
/// @param array a cg_array_t
/// @param c_array a pointer to a C array of elements, use AS_MEMORY(<var>).
/// @return true if successful
bool cg_array_assign(cg_array_t *array, const byte_t *c_array);

/// @brief swaps the contents of DEST with SOURCE
/// @return true if successful
bool cg_array_swap(cg_array_t *dest, cg_array_t *source);

/// @brief fill all elements of ARRAY with the VALUE
/// @param array a cg_array_t.
/// @param value a pointer to the value to be stored, use AS_MEMORY(<var>).
/// @return true if successful.
bool cg_array_fill(cg_array_t *array, const byte_t *value);

/// @brief free appropriately a instance of cg_array_t.
/// @param array the cg_array_t.
void cg_array_destroy(cg_array_t *array);