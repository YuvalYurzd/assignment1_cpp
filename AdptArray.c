#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "AdptArray.h"

// The defenition of the requested struct
typedef struct AdptArray_ {
    int arr_Size;
    PElement* p_Elem_Arr;
    COPY_FUNC copy_Func;
    DEL_FUNC del_Func;
    PRINT_FUNC print_Func;
} AdptArray;

// Create function - alloctes memory for the addaptive array and sets its initial arguments
PAdptArray CreateAdptArray(COPY_FUNC copy_Func, DEL_FUNC del_Func, PRINT_FUNC print_Func) {
    PAdptArray array = (PAdptArray) malloc(sizeof(AdptArray));
    if(array == NULL)
    {
        printf("Failed to allocate memory, exiting program...");
        free(array);
        exit(1);
    }
    array->arr_Size = 0;
    array->p_Elem_Arr = NULL;
    array->copy_Func = copy_Func;
    array->del_Func = del_Func;
    array->print_Func = print_Func;
    return array;
}

// Delete function - free the adaptive array and all its elements
void DeleteAdptArray(PAdptArray array) {
    if (array == NULL) 
        return;
    for (int i = 0; i < array->arr_Size; ++i) {
        if (array->p_Elem_Arr[i] != NULL)
        {
            array->del_Func((array->p_Elem_Arr)[i]);
        }
    }
    free(array->p_Elem_Arr);
    free(array);
}

// Set function - adds a new element to the adaptive array, frees the old element if exists
Result SetAdptArrayAt(PAdptArray array, int i, PElement p_New_Elem) {
    PElement *new_p_Elem_Arr;
    if (array == NULL)
        return FAIL;
    if (i >= array->arr_Size) {
        if ((new_p_Elem_Arr = (PElement *) calloc((i + 1), sizeof(PElement))) == NULL)
            return FAIL;
        memcpy(new_p_Elem_Arr, array->p_Elem_Arr, (array->arr_Size) * sizeof(PElement));
        if (array->p_Elem_Arr != NULL)
            free(array->p_Elem_Arr);      
        array->p_Elem_Arr = new_p_Elem_Arr;
    }
    if (array->p_Elem_Arr[i] != NULL)
        array->del_Func((array->p_Elem_Arr)[i]);
    (array->p_Elem_Arr)[i] = array->copy_Func(p_New_Elem);
    if(i >= array->arr_Size)
    {
        array->arr_Size = i + 1;
    }
    return SUCCESS;
}

// Get function - returns an element at a given index
PElement GetAdptArrayAt(PAdptArray array, int i) {
    if (!array) 
        return NULL;
    if(array->p_Elem_Arr[i] == NULL) 
        return NULL;
    PElement elem = array->copy_Func(array->p_Elem_Arr[i]);
    return elem;
}

// Get size function - returns the adaptive array size
int GetAdptArraySize(PAdptArray array) {
    if (!array) 
        return -1;
    return array->arr_Size;
}

// Print function - print the elements in the adaptive array
void PrintDB(PAdptArray array) {
    if (!array) 
        return;
    for (int i = 0; i < array->arr_Size; i++) {
        if (array->p_Elem_Arr[i] != NULL)
            array->print_Func(array->p_Elem_Arr[i]);
    }
}
