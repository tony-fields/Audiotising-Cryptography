#include <Python.h>
#include <stdio.h>
#include "wavHeader.h"
#include <string.h>

//method to split file into header.bin and content.bin
static PyObject* split_wav(PyObject* self, PyObject* args){
    int bufferSize = 128*1024; //128kb
    const char *file;
    if (!PyArg_ParseTuple(args, "s", &file)) {
       return NULL;
    }

    FILE *fp = fopen(file, "rb");
    FILE *header = fopen("header.bin", "wb");
    FILE *content = fopen("content.bin", "wb");

    if(fp == 0){
        PyErr_SetString(PyExc_FileNotFoundError, "Could not open the given WAV file.");
        return NULL;
    }

    struct wav_header wavH;
    fread(&wavH, sizeof(struct wav_header), 1, fp);
    fwrite(&wavH, sizeof(struct wav_header), 1, header);
    fclose(header);

    char buffer[bufferSize];

    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, bufferSize, fp)) > 0) {
        fwrite(buffer, 1, bytesRead, content);
    }


    fclose(fp);
    fclose(content);
    return Py_BuildValue("(iHH)",wavH.srate, wavH.bits_per_samp, wavH.num_chans);
}

//combine a header and contents of file to make new wav file
static PyObject* combine_files(PyObject* self, PyObject* args) {
    int bufferSize = 128*1024; //128kb
    const char *fileName, *header, *content;
    if (!PyArg_ParseTuple(args, "sss", &fileName, &header, &content)) {
        return NULL;
    }
    FILE *fp = fopen(fileName, "wb");
    FILE *head = fopen(header, "rb");
    FILE *cont = fopen(content, "rb");
    
    if (fp == NULL || head == NULL || cont == NULL) {
        PyErr_SetString(PyExc_FileNotFoundError, "Could not open one of the input files.");
        return NULL;
    }

    struct wav_header wavH;
    fread(&wavH, sizeof(struct wav_header), 1, head);
    fwrite(&wavH, sizeof(struct wav_header), 1, fp);
    fclose(head);

    char buffer[bufferSize];

    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, bufferSize, cont)) > 0) {
        fwrite(buffer, 1, bytesRead, fp);
    }

    fclose(fp);
    fclose(cont);
    Py_RETURN_NONE;
}


//method definition
static PyMethodDef WavMethods[] = {
    {"split_wav", split_wav, METH_VARARGS, "Split a WAV file into header and content files."},
    {"combine_files", combine_files, METH_VARARGS, 
     "Combine header and content files into a WAV file and return metadata as a tuple: "
     "(sampling rate, bytes per second, bytes per sample, bits per sample)."},
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Module definition
static struct PyModuleDef wavmodule = {
    PyModuleDef_HEAD_INIT,
    "myWav_module",  // Module name
    "Module for splitting and combining WAV files.",  // Module docstring
    -1,  // Size of per-interpreter state (or -1 for global state)
    WavMethods
};

// Module initialization
PyMODINIT_FUNC PyInit_myWav_module(void) {
    return PyModule_Create(&wavmodule);
}
