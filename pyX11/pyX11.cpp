#!/usr/bin/env python
# encoding: utf-8

#include "Python.h"
#include "x11.h"

#define DEBUG_ASSERT(cond) \
if(!(cond)) \
{ \
	fprintf(stderr, "Assert: %s | Function: %s\n", #cond, __FUNCTION__); \
	assert(0); \
}

static PyObject* x11_hash_wrapper(PyObject *self, PyObject *args) {
	char* input_data;
	int input_data_len;
	char hash_data[32];
	char* p = (char*)hash_data;
	int hash_data_len = 32;

    DEBUG_ASSERT(input_data != NULL);

	PyArg_ParseTuple(args, "s#" , &input_data, &input_data_len);
    x11_hash(input_data, p, input_data_len);
	PyObject* resultObject = Py_BuildValue("s#", hash_data, hash_data_len);
	return resultObject;
}

static PyMethodDef x11_methods[] = {
	{"x11_hash", x11_hash_wrapper, METH_VARARGS, "x11_hash(input_data)"},
	{NULL, NULL, 0, NULL}
};

extern "C" {
	void initpyX11(void) {
		Py_InitModule("pyX11", x11_methods);
	}
}


