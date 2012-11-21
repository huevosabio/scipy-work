

#define PY_SSIZE_T_CLEAN
#include "Python.h"
#ifndef Py_PYTHON_H
    #error Python headers needed to compile C extensions, please install development version of Python.
#elif PY_VERSION_HEX < 0x02040000
    #error Cython requires Python 2.4+.
#else
#include <stddef.h> 
#ifndef offsetof
#define offsetof(type, member) ( (size_t) & ((type*)0) -> member )
#endif
#if !defined(WIN32) && !defined(MS_WINDOWS)
  #ifndef __stdcall
    #define __stdcall
  #endif
  #ifndef __cdecl
    #define __cdecl
  #endif
  #ifndef __fastcall
    #define __fastcall
  #endif
#endif
#ifndef DL_IMPORT
  #define DL_IMPORT(t) t
#endif
#ifndef DL_EXPORT
  #define DL_EXPORT(t) t
#endif
#ifndef PY_LONG_LONG
  #define PY_LONG_LONG LONG_LONG
#endif
#ifndef Py_HUGE_VAL
  #define Py_HUGE_VAL HUGE_VAL
#endif
#ifdef PYPY_VERSION
#define CYTHON_COMPILING_IN_PYPY 1
#define CYTHON_COMPILING_IN_CPYTHON 0
#else
#define CYTHON_COMPILING_IN_PYPY 0
#define CYTHON_COMPILING_IN_CPYTHON 1
#endif
#if PY_VERSION_HEX < 0x02050000
  typedef int Py_ssize_t;
  #define PY_SSIZE_T_MAX INT_MAX
  #define PY_SSIZE_T_MIN INT_MIN
  #define PY_FORMAT_SIZE_T ""
  #define CYTHON_FORMAT_SSIZE_T ""
  #define PyInt_FromSsize_t(z) PyInt_FromLong(z)
  #define PyInt_AsSsize_t(o)   __Pyx_PyInt_AsInt(o)
  #define PyNumber_Index(o)    ((PyNumber_Check(o) && !PyFloat_Check(o)) ? PyNumber_Int(o) : \
                                (PyErr_Format(PyExc_TypeError, \
                                              "expected index value, got %.200s", Py_TYPE(o)->tp_name), \
                                 (PyObject*)0))
  #define PyIndex_Check(o)     (PyNumber_Check(o) && !PyFloat_Check(o) && !PyComplex_Check(o))
  #define PyErr_WarnEx(category, message, stacklevel) PyErr_Warn(category, message)
  #define __PYX_BUILD_PY_SSIZE_T "i"
#else
  #define __PYX_BUILD_PY_SSIZE_T "n"
  #define CYTHON_FORMAT_SSIZE_T "z"
#endif
#if PY_VERSION_HEX < 0x02060000
  #define Py_REFCNT(ob) (((PyObject*)(ob))->ob_refcnt)
  #define Py_TYPE(ob)   (((PyObject*)(ob))->ob_type)
  #define Py_SIZE(ob)   (((PyVarObject*)(ob))->ob_size)
  #define PyVarObject_HEAD_INIT(type, size) \
          PyObject_HEAD_INIT(type) size,
  #define PyType_Modified(t)
  typedef struct {
     void *buf;
     PyObject *obj;
     Py_ssize_t len;
     Py_ssize_t itemsize;
     int readonly;
     int ndim;
     char *format;
     Py_ssize_t *shape;
     Py_ssize_t *strides;
     Py_ssize_t *suboffsets;
     void *internal;
  } Py_buffer;
  #define PyBUF_SIMPLE 0
  #define PyBUF_WRITABLE 0x0001
  #define PyBUF_FORMAT 0x0004
  #define PyBUF_ND 0x0008
  #define PyBUF_STRIDES (0x0010 | PyBUF_ND)
  #define PyBUF_C_CONTIGUOUS (0x0020 | PyBUF_STRIDES)
  #define PyBUF_F_CONTIGUOUS (0x0040 | PyBUF_STRIDES)
  #define PyBUF_ANY_CONTIGUOUS (0x0080 | PyBUF_STRIDES)
  #define PyBUF_INDIRECT (0x0100 | PyBUF_STRIDES)
  #define PyBUF_RECORDS (PyBUF_STRIDES | PyBUF_FORMAT | PyBUF_WRITABLE)
  #define PyBUF_FULL (PyBUF_INDIRECT | PyBUF_FORMAT | PyBUF_WRITABLE)
  typedef int (*getbufferproc)(PyObject *, Py_buffer *, int);
  typedef void (*releasebufferproc)(PyObject *, Py_buffer *);
#endif
#if PY_MAJOR_VERSION < 3
  #define __Pyx_BUILTIN_MODULE_NAME "__builtin__"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos) \
          PyCode_New(a, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
#else
  #define __Pyx_BUILTIN_MODULE_NAME "builtins"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos) \
          PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
#endif
#if PY_MAJOR_VERSION < 3 && PY_MINOR_VERSION < 6
  #define PyUnicode_FromString(s) PyUnicode_Decode(s, strlen(s), "UTF-8", "strict")
#endif
#if PY_MAJOR_VERSION >= 3
  #define Py_TPFLAGS_CHECKTYPES 0
  #define Py_TPFLAGS_HAVE_INDEX 0
#endif
#if (PY_VERSION_HEX < 0x02060000) || (PY_MAJOR_VERSION >= 3)
  #define Py_TPFLAGS_HAVE_NEWBUFFER 0
#endif
#if PY_VERSION_HEX > 0x03030000 && defined(PyUnicode_KIND)
  #define CYTHON_PEP393_ENABLED 1
  #define __Pyx_PyUnicode_READY(op)       (likely(PyUnicode_IS_READY(op)) ? \
                                              0 : _PyUnicode_Ready((PyObject *)(op)))
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_LENGTH(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) PyUnicode_READ_CHAR(u, i)
  #define __Pyx_PyUnicode_READ(k, d, i)   PyUnicode_READ(k, d, i)
#else
  #define CYTHON_PEP393_ENABLED 0
  #define __Pyx_PyUnicode_READY(op)       (0)
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_SIZE(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) ((Py_UCS4)(PyUnicode_AS_UNICODE(u)[i]))
  #define __Pyx_PyUnicode_READ(k, d, i)   ((k=k), (Py_UCS4)(((Py_UNICODE*)d)[i]))
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBaseString_Type            PyUnicode_Type
  #define PyStringObject               PyUnicodeObject
  #define PyString_Type                PyUnicode_Type
  #define PyString_Check               PyUnicode_Check
  #define PyString_CheckExact          PyUnicode_CheckExact
#endif
#if PY_VERSION_HEX < 0x02060000
  #define PyBytesObject                PyStringObject
  #define PyBytes_Type                 PyString_Type
  #define PyBytes_Check                PyString_Check
  #define PyBytes_CheckExact           PyString_CheckExact
  #define PyBytes_FromString           PyString_FromString
  #define PyBytes_FromStringAndSize    PyString_FromStringAndSize
  #define PyBytes_FromFormat           PyString_FromFormat
  #define PyBytes_DecodeEscape         PyString_DecodeEscape
  #define PyBytes_AsString             PyString_AsString
  #define PyBytes_AsStringAndSize      PyString_AsStringAndSize
  #define PyBytes_Size                 PyString_Size
  #define PyBytes_AS_STRING            PyString_AS_STRING
  #define PyBytes_GET_SIZE             PyString_GET_SIZE
  #define PyBytes_Repr                 PyString_Repr
  #define PyBytes_Concat               PyString_Concat
  #define PyBytes_ConcatAndDel         PyString_ConcatAndDel
#endif
#if PY_VERSION_HEX < 0x02060000
  #define PySet_Check(obj)             PyObject_TypeCheck(obj, &PySet_Type)
  #define PyFrozenSet_Check(obj)       PyObject_TypeCheck(obj, &PyFrozenSet_Type)
#endif
#ifndef PySet_CheckExact
  #define PySet_CheckExact(obj)        (Py_TYPE(obj) == &PySet_Type)
#endif
#define __Pyx_TypeCheck(obj, type) PyObject_TypeCheck(obj, (PyTypeObject *)type)
#if PY_MAJOR_VERSION >= 3
  #define PyIntObject                  PyLongObject
  #define PyInt_Type                   PyLong_Type
  #define PyInt_Check(op)              PyLong_Check(op)
  #define PyInt_CheckExact(op)         PyLong_CheckExact(op)
  #define PyInt_FromString             PyLong_FromString
  #define PyInt_FromUnicode            PyLong_FromUnicode
  #define PyInt_FromLong               PyLong_FromLong
  #define PyInt_FromSize_t             PyLong_FromSize_t
  #define PyInt_FromSsize_t            PyLong_FromSsize_t
  #define PyInt_AsLong                 PyLong_AsLong
  #define PyInt_AS_LONG                PyLong_AS_LONG
  #define PyInt_AsSsize_t              PyLong_AsSsize_t
  #define PyInt_AsUnsignedLongMask     PyLong_AsUnsignedLongMask
  #define PyInt_AsUnsignedLongLongMask PyLong_AsUnsignedLongLongMask
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBoolObject                 PyLongObject
#endif
#if PY_VERSION_HEX < 0x03020000
  typedef long Py_hash_t;
  #define __Pyx_PyInt_FromHash_t PyInt_FromLong
  #define __Pyx_PyInt_AsHash_t   PyInt_AsLong
#else
  #define __Pyx_PyInt_FromHash_t PyInt_FromSsize_t
  #define __Pyx_PyInt_AsHash_t   PyInt_AsSsize_t
#endif
#if (PY_MAJOR_VERSION < 3) || (PY_VERSION_HEX >= 0x03010300)
  #define __Pyx_PySequence_GetSlice(obj, a, b) PySequence_GetSlice(obj, a, b)
  #define __Pyx_PySequence_SetSlice(obj, a, b, value) PySequence_SetSlice(obj, a, b, value)
  #define __Pyx_PySequence_DelSlice(obj, a, b) PySequence_DelSlice(obj, a, b)
#else
  #define __Pyx_PySequence_GetSlice(obj, a, b) (unlikely(!(obj)) ? \
        (PyErr_SetString(PyExc_SystemError, "null argument to internal routine"), (PyObject*)0) : \
        (likely((obj)->ob_type->tp_as_mapping) ? (PySequence_GetSlice(obj, a, b)) : \
            (PyErr_Format(PyExc_TypeError, "'%.200s' object is unsliceable", (obj)->ob_type->tp_name), (PyObject*)0)))
  #define __Pyx_PySequence_SetSlice(obj, a, b, value) (unlikely(!(obj)) ? \
        (PyErr_SetString(PyExc_SystemError, "null argument to internal routine"), -1) : \
        (likely((obj)->ob_type->tp_as_mapping) ? (PySequence_SetSlice(obj, a, b, value)) : \
            (PyErr_Format(PyExc_TypeError, "'%.200s' object doesn't support slice assignment", (obj)->ob_type->tp_name), -1)))
  #define __Pyx_PySequence_DelSlice(obj, a, b) (unlikely(!(obj)) ? \
        (PyErr_SetString(PyExc_SystemError, "null argument to internal routine"), -1) : \
        (likely((obj)->ob_type->tp_as_mapping) ? (PySequence_DelSlice(obj, a, b)) : \
            (PyErr_Format(PyExc_TypeError, "'%.200s' object doesn't support slice deletion", (obj)->ob_type->tp_name), -1)))
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyMethod_New(func, self, klass) ((self) ? PyMethod_New(func, self) : PyInstanceMethod_New(func))
#endif
#if PY_VERSION_HEX < 0x02050000
  #define __Pyx_GetAttrString(o,n)   PyObject_GetAttrString((o),((char *)(n)))
  #define __Pyx_SetAttrString(o,n,a) PyObject_SetAttrString((o),((char *)(n)),(a))
  #define __Pyx_DelAttrString(o,n)   PyObject_DelAttrString((o),((char *)(n)))
#else
  #define __Pyx_GetAttrString(o,n)   PyObject_GetAttrString((o),(n))
  #define __Pyx_SetAttrString(o,n,a) PyObject_SetAttrString((o),(n),(a))
  #define __Pyx_DelAttrString(o,n)   PyObject_DelAttrString((o),(n))
#endif
#if PY_VERSION_HEX < 0x02050000
  #define __Pyx_NAMESTR(n) ((char *)(n))
  #define __Pyx_DOCSTR(n)  ((char *)(n))
#else
  #define __Pyx_NAMESTR(n) (n)
  #define __Pyx_DOCSTR(n)  (n)
#endif


#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_TrueDivide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceTrueDivide(x,y)
#else
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_Divide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceDivide(x,y)
#endif

#ifndef __PYX_EXTERN_C
  #ifdef __cplusplus
    #define __PYX_EXTERN_C extern "C"
  #else
    #define __PYX_EXTERN_C extern
  #endif
#endif

#if defined(WIN32) || defined(MS_WINDOWS)
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#define __PYX_HAVE__scipy__spatial__qhull
#define __PYX_HAVE_API__scipy__spatial__qhull
#include "numpy/ndarrayobject.h"
#include "stdio.h"
#include "stdlib.h"
#include "numpy/arrayobject.h"
#include "numpy/ufuncobject.h"
#include "math.h"
#include "qhull/src/qset.h"
#include "qhull/src/libqhull.h"
#include "qhull/src/poly.h"
#include "qhull/src/merge.h"
#include "qhull_blas.h"
#ifdef _OPENMP
#include <omp.h>
#endif 

#ifdef PYREX_WITHOUT_ASSERTIONS
#define CYTHON_WITHOUT_ASSERTIONS
#endif



#ifndef CYTHON_INLINE
  #if defined(__GNUC__)
    #define CYTHON_INLINE __inline__
  #elif defined(_MSC_VER)
    #define CYTHON_INLINE __inline
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_INLINE inline
  #else
    #define CYTHON_INLINE
  #endif
#endif


#ifndef CYTHON_UNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define CYTHON_UNUSED __attribute__ ((__unused__))
#   else
#     define CYTHON_UNUSED
#   endif
# elif defined(__ICC) || (defined(__INTEL_COMPILER) && !defined(_MSC_VER))
#   define CYTHON_UNUSED __attribute__ ((__unused__))
# else
#   define CYTHON_UNUSED
# endif
#endif

typedef struct {PyObject **p; char *s; const long n; const char* encoding; const char is_unicode; const char is_str; const char intern; } __Pyx_StringTabEntry; 




#define __Pyx_PyBytes_FromUString(s) PyBytes_FromString((char*)s)
#define __Pyx_PyBytes_AsUString(s)   ((unsigned char*) PyBytes_AsString(s))

#define __Pyx_Owned_Py_None(b) (Py_INCREF(Py_None), Py_None)
#define __Pyx_PyBool_FromLong(b) ((b) ? (Py_INCREF(Py_True), Py_True) : (Py_INCREF(Py_False), Py_False))
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject*);
static CYTHON_INLINE PyObject* __Pyx_PyNumber_Int(PyObject* x);

static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject*);
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t);
static CYTHON_INLINE size_t __Pyx_PyInt_AsSize_t(PyObject*);

#if CYTHON_COMPILING_IN_CPYTHON
#define __pyx_PyFloat_AsDouble(x) (PyFloat_CheckExact(x) ? PyFloat_AS_DOUBLE(x) : PyFloat_AsDouble(x))
#else
#define __pyx_PyFloat_AsDouble(x) PyFloat_AsDouble(x)
#endif
#define __pyx_PyFloat_AsFloat(x) ((float) __pyx_PyFloat_AsDouble(x))

#ifdef __GNUC__
  
  #if __GNUC__ > 2 || (__GNUC__ == 2 && (__GNUC_MINOR__ > 95))
    #define likely(x)   __builtin_expect(!!(x), 1)
    #define unlikely(x) __builtin_expect(!!(x), 0)
  #else 
    #define likely(x)   (x)
    #define unlikely(x) (x)
  #endif 
#else 
  #define likely(x)   (x)
  #define unlikely(x) (x)
#endif 
    
static PyObject *__pyx_m;
static PyObject *__pyx_b;
static PyObject *__pyx_empty_tuple;
static PyObject *__pyx_empty_bytes;
static int __pyx_lineno;
static int __pyx_clineno = 0;
static const char * __pyx_cfilenm= __FILE__;
static const char *__pyx_filename;

#if !defined(CYTHON_CCOMPLEX)
  #if defined(__cplusplus)
    #define CYTHON_CCOMPLEX 1
  #elif defined(_Complex_I)
    #define CYTHON_CCOMPLEX 1
  #else
    #define CYTHON_CCOMPLEX 0
  #endif
#endif
#if CYTHON_CCOMPLEX
  #ifdef __cplusplus
    #include <complex>
  #else
    #include <complex.h>
  #endif
#endif
#if CYTHON_CCOMPLEX && !defined(__cplusplus) && defined(__sun__) && defined(__GNUC__)
  #undef _Complex_I
  #define _Complex_I 1.0fj
#endif


static const char *__pyx_f[] = {
  "qhull.pyx",
  "numpy.pxd",
  "type.pxd",
};
#define IS_UNSIGNED(type) (((type) -1) > 0)
struct __Pyx_StructField_;
#define __PYX_BUF_FLAGS_PACKED_STRUCT (1 << 0)
typedef struct {
  const char* name; 
  struct __Pyx_StructField_* fields;
  size_t size;     
  size_t arraysize[8]; 
  int ndim;
  char typegroup; 
  char is_unsigned;
  int flags;
} __Pyx_TypeInfo;
typedef struct __Pyx_StructField_ {
  __Pyx_TypeInfo* type;
  const char* name;
  size_t offset;
} __Pyx_StructField;
typedef struct {
  __Pyx_StructField* field;
  size_t parent_offset;
} __Pyx_BufFmt_StackElem;
typedef struct {
  __Pyx_StructField root;
  __Pyx_BufFmt_StackElem* head;
  size_t fmt_offset;
  size_t new_count, enc_count;
  size_t struct_alignment;
  int is_complex;
  char enc_type;
  char new_packmode;
  char enc_packmode;
  char is_valid_array;
} __Pyx_BufFmt_Context;



typedef npy_int8 __pyx_t_5numpy_int8_t;


typedef npy_int16 __pyx_t_5numpy_int16_t;


typedef npy_int32 __pyx_t_5numpy_int32_t;


typedef npy_int64 __pyx_t_5numpy_int64_t;


typedef npy_uint8 __pyx_t_5numpy_uint8_t;


typedef npy_uint16 __pyx_t_5numpy_uint16_t;


typedef npy_uint32 __pyx_t_5numpy_uint32_t;


typedef npy_uint64 __pyx_t_5numpy_uint64_t;


typedef npy_float32 __pyx_t_5numpy_float32_t;


typedef npy_float64 __pyx_t_5numpy_float64_t;


typedef npy_long __pyx_t_5numpy_int_t;


typedef npy_longlong __pyx_t_5numpy_long_t;


typedef npy_longlong __pyx_t_5numpy_longlong_t;


typedef npy_ulong __pyx_t_5numpy_uint_t;


typedef npy_ulonglong __pyx_t_5numpy_ulong_t;


typedef npy_ulonglong __pyx_t_5numpy_ulonglong_t;


typedef npy_intp __pyx_t_5numpy_intp_t;


typedef npy_uintp __pyx_t_5numpy_uintp_t;


typedef npy_double __pyx_t_5numpy_float_t;


typedef npy_double __pyx_t_5numpy_double_t;


typedef npy_longdouble __pyx_t_5numpy_longdouble_t;
#if CYTHON_CCOMPLEX
  #ifdef __cplusplus
    typedef ::std::complex< float > __pyx_t_float_complex;
  #else
    typedef float _Complex __pyx_t_float_complex;
  #endif
#else
    typedef struct { float real, imag; } __pyx_t_float_complex;
#endif

#if CYTHON_CCOMPLEX
  #ifdef __cplusplus
    typedef ::std::complex< double > __pyx_t_double_complex;
  #else
    typedef double _Complex __pyx_t_double_complex;
  #endif
#else
    typedef struct { double real, imag; } __pyx_t_double_complex;
#endif



struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D;
struct __pyx_obj_5scipy_7spatial_5qhull__Qhull;


typedef npy_cfloat __pyx_t_5numpy_cfloat_t;


typedef npy_cdouble __pyx_t_5numpy_cdouble_t;


typedef npy_clongdouble __pyx_t_5numpy_clongdouble_t;


typedef npy_cdouble __pyx_t_5numpy_complex_t;
struct __pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t;
typedef struct __pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t __pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t;
struct __pyx_t_5scipy_7spatial_5qhull_RidgeIter2D_t;
typedef struct __pyx_t_5scipy_7spatial_5qhull_RidgeIter2D_t __pyx_t_5scipy_7spatial_5qhull_RidgeIter2D_t;
struct __pyx_defaults;
typedef struct __pyx_defaults __pyx_defaults;
struct __pyx_defaults1;
typedef struct __pyx_defaults1 __pyx_defaults1;
struct __pyx_defaults2;
typedef struct __pyx_defaults2 __pyx_defaults2;


struct __pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t {
  int ndim;
  int npoints;
  int nsimplex;
  double *points;
  int *vertices;
  int *neighbors;
  double *equations;
  double *transform;
  int *vertex_to_simplex;
  double paraboloid_scale;
  double paraboloid_shift;
  double *max_bound;
  double *min_bound;
};


struct __pyx_t_5scipy_7spatial_5qhull_RidgeIter2D_t {
  __pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *info;
  int index;
  int vertex;
  int vertex2;
  int triangle;
  int start_triangle;
  int start_index;
  int restart;
};
struct __pyx_defaults {
  PyObject *__pyx_arg_incremental;
};
struct __pyx_defaults1 {
  PyObject *__pyx_arg_force;
};
struct __pyx_defaults2 {
  PyObject *__pyx_arg_bruteforce;
};


struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D {
  PyObject_HEAD
  __pyx_t_5scipy_7spatial_5qhull_RidgeIter2D_t it;
  PyObject *delaunay;
  __pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t info;
};



struct __pyx_obj_5scipy_7spatial_5qhull__Qhull {
  PyObject_HEAD
  struct __pyx_vtabstruct_5scipy_7spatial_5qhull__Qhull *__pyx_vtab;
  qhT *_saved_qh;
  PyObject *_point_arrays;
  float paraboloid_scale;
  float paraboloid_shift;
  PyObject *_dirty_points;
  int _is_delaunay;
  int _ndim;
  int _n_dirty_points;
};



struct __pyx_vtabstruct_5scipy_7spatial_5qhull__Qhull {
  int (*_activate)(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *);
  int (*_deactivate)(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *);
  int (*_uninit)(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *);
};
static struct __pyx_vtabstruct_5scipy_7spatial_5qhull__Qhull *__pyx_vtabptr_5scipy_7spatial_5qhull__Qhull;
static int __pyx_f_5scipy_7spatial_5qhull_6_Qhull__activate(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *);
static int __pyx_f_5scipy_7spatial_5qhull_6_Qhull__deactivate(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *);
static int __pyx_f_5scipy_7spatial_5qhull_6_Qhull__uninit(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *);
#ifndef CYTHON_REFNANNY
  #define CYTHON_REFNANNY 0
#endif
#if CYTHON_REFNANNY
  typedef struct {
    void (*INCREF)(void*, PyObject*, int);
    void (*DECREF)(void*, PyObject*, int);
    void (*GOTREF)(void*, PyObject*, int);
    void (*GIVEREF)(void*, PyObject*, int);
    void* (*SetupContext)(const char*, int, const char*);
    void (*FinishContext)(void**);
  } __Pyx_RefNannyAPIStruct;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNanny = NULL;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname); 
  #define __Pyx_RefNannyDeclarations void *__pyx_refnanny = NULL;
#ifdef WITH_THREAD
  #define __Pyx_RefNannySetupContext(name, acquire_gil) \
          if (acquire_gil) { \
              PyGILState_STATE __pyx_gilstate_save = PyGILState_Ensure(); \
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__); \
              PyGILState_Release(__pyx_gilstate_save); \
          } else { \
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__); \
          }
#else
  #define __Pyx_RefNannySetupContext(name, acquire_gil) \
          __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__)
#endif
  #define __Pyx_RefNannyFinishContext() \
          __Pyx_RefNanny->FinishContext(&__pyx_refnanny)
  #define __Pyx_INCREF(r)  __Pyx_RefNanny->INCREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_DECREF(r)  __Pyx_RefNanny->DECREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GOTREF(r)  __Pyx_RefNanny->GOTREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GIVEREF(r) __Pyx_RefNanny->GIVEREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_XINCREF(r)  do { if((r) != NULL) {__Pyx_INCREF(r); }} while(0)
  #define __Pyx_XDECREF(r)  do { if((r) != NULL) {__Pyx_DECREF(r); }} while(0)
  #define __Pyx_XGOTREF(r)  do { if((r) != NULL) {__Pyx_GOTREF(r); }} while(0)
  #define __Pyx_XGIVEREF(r) do { if((r) != NULL) {__Pyx_GIVEREF(r);}} while(0)
#else
  #define __Pyx_RefNannyDeclarations
  #define __Pyx_RefNannySetupContext(name, acquire_gil)
  #define __Pyx_RefNannyFinishContext()
  #define __Pyx_INCREF(r) Py_INCREF(r)
  #define __Pyx_DECREF(r) Py_DECREF(r)
  #define __Pyx_GOTREF(r)
  #define __Pyx_GIVEREF(r)
  #define __Pyx_XINCREF(r) Py_XINCREF(r)
  #define __Pyx_XDECREF(r) Py_XDECREF(r)
  #define __Pyx_XGOTREF(r)
  #define __Pyx_XGIVEREF(r)
#endif 
#define __Pyx_CLEAR(r)    do { PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);} while(0)
#define __Pyx_XCLEAR(r)   do { if((r) != NULL) {PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);}} while(0)

static PyObject *__Pyx_GetName(PyObject *dict, PyObject *name); 

static void __Pyx_RaiseDoubleKeywordsError(const char* func_name, PyObject* kw_name); 

static int __Pyx_ParseOptionalKeywords(PyObject *kwds, PyObject **argnames[], \
    PyObject *kwds2, PyObject *values[], Py_ssize_t num_pos_args, \
    const char* function_name); 

static void __Pyx_RaiseArgtupleInvalid(const char* func_name, int exact,
    Py_ssize_t num_min, Py_ssize_t num_max, Py_ssize_t num_found); 

static int __Pyx_ArgTypeTest(PyObject *obj, PyTypeObject *type, int none_allowed,
    const char *name, int exact); 

static CYTHON_INLINE int  __Pyx_GetBufferAndValidate(Py_buffer* buf, PyObject* obj,
    __Pyx_TypeInfo* dtype, int flags, int nd, int cast, __Pyx_BufFmt_StackElem* stack);
static CYTHON_INLINE void __Pyx_SafeReleaseBuffer(Py_buffer* info);

static CYTHON_INLINE int __Pyx_PySequence_Contains(PyObject* item, PyObject* seq, int eq) {
    int result = PySequence_Contains(seq, item);
    return unlikely(result < 0) ? result : (result == (eq == Py_EQ));
}

static CYTHON_INLINE void __Pyx_ErrRestore(PyObject *type, PyObject *value, PyObject *tb); 
static CYTHON_INLINE void __Pyx_ErrFetch(PyObject **type, PyObject **value, PyObject **tb); 

static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb, PyObject *cause); 

static CYTHON_INLINE int __Pyx_TypeTest(PyObject *obj, PyTypeObject *type); 

static void __Pyx_RaiseBufferFallbackError(void); 

static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Generic(PyObject *o, PyObject* j) {
    PyObject *r;
    if (!j) return NULL;
    r = PyObject_GetItem(o, j);
    Py_DECREF(j);
    return r;
}
#define __Pyx_GetItemInt_List(o, i, size, to_py_func) (((size) <= sizeof(Py_ssize_t)) ? \
                                                    __Pyx_GetItemInt_List_Fast(o, i) : \
                                                    __Pyx_GetItemInt_Generic(o, to_py_func(i)))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_List_Fast(PyObject *o, Py_ssize_t i) {
#if CYTHON_COMPILING_IN_CPYTHON
    if (likely((0 <= i) & (i < PyList_GET_SIZE(o)))) {
        PyObject *r = PyList_GET_ITEM(o, i);
        Py_INCREF(r);
        return r;
    }
    else if ((-PyList_GET_SIZE(o) <= i) & (i < 0)) {
        PyObject *r = PyList_GET_ITEM(o, PyList_GET_SIZE(o) + i);
        Py_INCREF(r);
        return r;
    }
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
#else
    return PySequence_GetItem(o, i);
#endif
}
#define __Pyx_GetItemInt_Tuple(o, i, size, to_py_func) (((size) <= sizeof(Py_ssize_t)) ? \
                                                    __Pyx_GetItemInt_Tuple_Fast(o, i) : \
                                                    __Pyx_GetItemInt_Generic(o, to_py_func(i)))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Tuple_Fast(PyObject *o, Py_ssize_t i) {
#if CYTHON_COMPILING_IN_CPYTHON
    if (likely((0 <= i) & (i < PyTuple_GET_SIZE(o)))) {
        PyObject *r = PyTuple_GET_ITEM(o, i);
        Py_INCREF(r);
        return r;
    }
    else if ((-PyTuple_GET_SIZE(o) <= i) & (i < 0)) {
        PyObject *r = PyTuple_GET_ITEM(o, PyTuple_GET_SIZE(o) + i);
        Py_INCREF(r);
        return r;
    }
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
#else
    return PySequence_GetItem(o, i);
#endif
}
#define __Pyx_GetItemInt(o, i, size, to_py_func) (((size) <= sizeof(Py_ssize_t)) ? \
                                                    __Pyx_GetItemInt_Fast(o, i) : \
                                                    __Pyx_GetItemInt_Generic(o, to_py_func(i)))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Fast(PyObject *o, Py_ssize_t i) {
#if CYTHON_COMPILING_IN_CPYTHON
    if (PyList_CheckExact(o)) {
        Py_ssize_t n = (likely(i >= 0)) ? i : i + PyList_GET_SIZE(o);
        if (likely((n >= 0) & (n < PyList_GET_SIZE(o)))) {
            PyObject *r = PyList_GET_ITEM(o, n);
            Py_INCREF(r);
            return r;
        }
    }
    else if (PyTuple_CheckExact(o)) {
        Py_ssize_t n = (likely(i >= 0)) ? i : i + PyTuple_GET_SIZE(o);
        if (likely((n >= 0) & (n < PyTuple_GET_SIZE(o)))) {
            PyObject *r = PyTuple_GET_ITEM(o, n);
            Py_INCREF(r);
            return r;
        }
    } else {  
        PySequenceMethods *m = Py_TYPE(o)->tp_as_sequence;
        if (likely(m && m->sq_item)) {
            if (unlikely(i < 0) && likely(m->sq_length)) {
                Py_ssize_t l = m->sq_length(o);
                if (unlikely(l < 0)) return NULL;
                i += l;
            }
            return m->sq_item(o, i);
        }
    }
#else
    if (PySequence_Check(o)) {
        return PySequence_GetItem(o, i);
    }
#endif
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
}

#define __Pyx_BufPtrStrided1d(type, buf, i0, s0) (type)((char*)buf + i0 * s0)
#define __Pyx_BufPtrStrided2d(type, buf, i0, s0, i1, s1) (type)((char*)buf + i0 * s0 + i1 * s1)
#define __Pyx_BufPtrStrided3d(type, buf, i0, s0, i1, s1, i2, s2) (type)((char*)buf + i0 * s0 + i1 * s1 + i2 * s2)
static CYTHON_INLINE long __Pyx_div_long(long, long); 

static CYTHON_INLINE void __Pyx_RaiseTooManyValuesError(Py_ssize_t expected);

static CYTHON_INLINE void __Pyx_RaiseNeedMoreValuesError(Py_ssize_t index);

static CYTHON_INLINE int __Pyx_IterFinish(void); 

static int __Pyx_IternextUnpackEndCheck(PyObject *retval, Py_ssize_t expected); 

static int __Pyx_GetException(PyObject **type, PyObject **value, PyObject **tb); 

static CYTHON_INLINE void __Pyx_RaiseNoneNotIterableError(void);

static CYTHON_INLINE void __Pyx_ExceptionSave(PyObject **type, PyObject **value, PyObject **tb); 
static void __Pyx_ExceptionReset(PyObject *type, PyObject *value, PyObject *tb); 

typedef struct {
  Py_ssize_t shape, strides, suboffsets;
} __Pyx_Buf_DimInfo;
typedef struct {
  size_t refcount;
  Py_buffer pybuffer;
} __Pyx_Buffer;
typedef struct {
  __Pyx_Buffer *rcbuffer;
  char *data;
  __Pyx_Buf_DimInfo diminfo[8];
} __Pyx_LocalBuf_ND;

#if PY_MAJOR_VERSION < 3
    static int __Pyx_GetBuffer(PyObject *obj, Py_buffer *view, int flags);
    static void __Pyx_ReleaseBuffer(Py_buffer *view);
#else
    #define __Pyx_GetBuffer PyObject_GetBuffer
    #define __Pyx_ReleaseBuffer PyBuffer_Release
#endif


static Py_ssize_t __Pyx_zeros[] = {0, 0, 0, 0, 0, 0, 0, 0};
static Py_ssize_t __Pyx_minusones[] = {-1, -1, -1, -1, -1, -1, -1, -1};

static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, long level); 

static PyObject *__Pyx_FindPy2Metaclass(PyObject *bases); 

static PyObject *__Pyx_CreateClass(PyObject *bases, PyObject *dict, PyObject *name,
                                   PyObject *modname); 

#define __Pyx_CyFunction_USED 1
#include <structmember.h>
#define __Pyx_CYFUNCTION_STATICMETHOD  0x01
#define __Pyx_CYFUNCTION_CLASSMETHOD   0x02
#define __Pyx_CYFUNCTION_CCLASS        0x04
#define __Pyx_CyFunction_GetClosure(f) \
    (((__pyx_CyFunctionObject *) (f))->func_closure)
#define __Pyx_CyFunction_GetClassObj(f) \
    (((__pyx_CyFunctionObject *) (f))->func_classobj)
#define __Pyx_CyFunction_Defaults(type, f) \
    ((type *)(((__pyx_CyFunctionObject *) (f))->defaults))
#define __Pyx_CyFunction_SetDefaultsGetter(f, g) \
    ((__pyx_CyFunctionObject *) (f))->defaults_getter = (g)
typedef struct {
    PyCFunctionObject func;
    int flags;
    PyObject *func_dict;
    PyObject *func_weakreflist;
    PyObject *func_name;
    PyObject *func_doc;
    PyObject *func_code;
    PyObject *func_closure;
    PyObject *func_classobj; 
    void *defaults;
    int defaults_pyobjects;
    PyObject *defaults_tuple; 
    PyObject *(*defaults_getter)(PyObject *);
} __pyx_CyFunctionObject;
static PyTypeObject *__pyx_CyFunctionType = 0;
#define __Pyx_CyFunction_NewEx(ml, flags, self, module, code) \
    __Pyx_CyFunction_New(__pyx_CyFunctionType, ml, flags, self, module, code)
static PyObject *__Pyx_CyFunction_New(PyTypeObject *,
                                      PyMethodDef *ml, int flags,
                                      PyObject *self, PyObject *module,
                                      PyObject* code);
static CYTHON_INLINE void *__Pyx_CyFunction_InitDefaults(PyObject *m,
                                                         size_t size,
                                                         int pyobjects);
static CYTHON_INLINE void __Pyx_CyFunction_SetDefaultsTuple(PyObject *m,
                                                            PyObject *tuple);
static int __Pyx_CyFunction_init(void);

#ifndef __PYX_FORCE_INIT_THREADS
  #define __PYX_FORCE_INIT_THREADS 0
#endif

static CYTHON_INLINE PyObject *__Pyx_PyInt_to_py_flagT(flagT);

static CYTHON_INLINE PyObject *__Pyx_PyInt_to_py_Py_intptr_t(Py_intptr_t);

#if CYTHON_CCOMPLEX
  #ifdef __cplusplus
    #define __Pyx_CREAL(z) ((z).real())
    #define __Pyx_CIMAG(z) ((z).imag())
  #else
    #define __Pyx_CREAL(z) (__real__(z))
    #define __Pyx_CIMAG(z) (__imag__(z))
  #endif
#else
    #define __Pyx_CREAL(z) ((z).real)
    #define __Pyx_CIMAG(z) ((z).imag)
#endif
#if defined(_WIN32) && defined(__cplusplus) && CYTHON_CCOMPLEX
    #define __Pyx_SET_CREAL(z,x) ((z).real(x))
    #define __Pyx_SET_CIMAG(z,y) ((z).imag(y))
#else
    #define __Pyx_SET_CREAL(z,x) __Pyx_CREAL(z) = (x)
    #define __Pyx_SET_CIMAG(z,y) __Pyx_CIMAG(z) = (y)
#endif

static CYTHON_INLINE __pyx_t_float_complex __pyx_t_float_complex_from_parts(float, float);

#if CYTHON_CCOMPLEX
    #define __Pyx_c_eqf(a, b)   ((a)==(b))
    #define __Pyx_c_sumf(a, b)  ((a)+(b))
    #define __Pyx_c_difff(a, b) ((a)-(b))
    #define __Pyx_c_prodf(a, b) ((a)*(b))
    #define __Pyx_c_quotf(a, b) ((a)/(b))
    #define __Pyx_c_negf(a)     (-(a))
  #ifdef __cplusplus
    #define __Pyx_c_is_zerof(z) ((z)==(float)0)
    #define __Pyx_c_conjf(z)    (::std::conj(z))
    #if 1
        #define __Pyx_c_absf(z)     (::std::abs(z))
        #define __Pyx_c_powf(a, b)  (::std::pow(a, b))
    #endif
  #else
    #define __Pyx_c_is_zerof(z) ((z)==0)
    #define __Pyx_c_conjf(z)    (conjf(z))
    #if 1
        #define __Pyx_c_absf(z)     (cabsf(z))
        #define __Pyx_c_powf(a, b)  (cpowf(a, b))
    #endif
 #endif
#else
    static CYTHON_INLINE int __Pyx_c_eqf(__pyx_t_float_complex, __pyx_t_float_complex);
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_sumf(__pyx_t_float_complex, __pyx_t_float_complex);
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_difff(__pyx_t_float_complex, __pyx_t_float_complex);
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_prodf(__pyx_t_float_complex, __pyx_t_float_complex);
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_quotf(__pyx_t_float_complex, __pyx_t_float_complex);
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_negf(__pyx_t_float_complex);
    static CYTHON_INLINE int __Pyx_c_is_zerof(__pyx_t_float_complex);
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_conjf(__pyx_t_float_complex);
    #if 1
        static CYTHON_INLINE float __Pyx_c_absf(__pyx_t_float_complex);
        static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_powf(__pyx_t_float_complex, __pyx_t_float_complex);
    #endif
#endif

static CYTHON_INLINE __pyx_t_double_complex __pyx_t_double_complex_from_parts(double, double);

#if CYTHON_CCOMPLEX
    #define __Pyx_c_eq(a, b)   ((a)==(b))
    #define __Pyx_c_sum(a, b)  ((a)+(b))
    #define __Pyx_c_diff(a, b) ((a)-(b))
    #define __Pyx_c_prod(a, b) ((a)*(b))
    #define __Pyx_c_quot(a, b) ((a)/(b))
    #define __Pyx_c_neg(a)     (-(a))
  #ifdef __cplusplus
    #define __Pyx_c_is_zero(z) ((z)==(double)0)
    #define __Pyx_c_conj(z)    (::std::conj(z))
    #if 1
        #define __Pyx_c_abs(z)     (::std::abs(z))
        #define __Pyx_c_pow(a, b)  (::std::pow(a, b))
    #endif
  #else
    #define __Pyx_c_is_zero(z) ((z)==0)
    #define __Pyx_c_conj(z)    (conj(z))
    #if 1
        #define __Pyx_c_abs(z)     (cabs(z))
        #define __Pyx_c_pow(a, b)  (cpow(a, b))
    #endif
 #endif
#else
    static CYTHON_INLINE int __Pyx_c_eq(__pyx_t_double_complex, __pyx_t_double_complex);
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_sum(__pyx_t_double_complex, __pyx_t_double_complex);
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_diff(__pyx_t_double_complex, __pyx_t_double_complex);
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_prod(__pyx_t_double_complex, __pyx_t_double_complex);
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_quot(__pyx_t_double_complex, __pyx_t_double_complex);
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_neg(__pyx_t_double_complex);
    static CYTHON_INLINE int __Pyx_c_is_zero(__pyx_t_double_complex);
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_conj(__pyx_t_double_complex);
    #if 1
        static CYTHON_INLINE double __Pyx_c_abs(__pyx_t_double_complex);
        static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_pow(__pyx_t_double_complex, __pyx_t_double_complex);
    #endif
#endif

static CYTHON_INLINE unsigned char __Pyx_PyInt_AsUnsignedChar(PyObject *);

static CYTHON_INLINE unsigned short __Pyx_PyInt_AsUnsignedShort(PyObject *);

static CYTHON_INLINE unsigned int __Pyx_PyInt_AsUnsignedInt(PyObject *);

static CYTHON_INLINE char __Pyx_PyInt_AsChar(PyObject *);

static CYTHON_INLINE short __Pyx_PyInt_AsShort(PyObject *);

static CYTHON_INLINE int __Pyx_PyInt_AsInt(PyObject *);

static CYTHON_INLINE signed char __Pyx_PyInt_AsSignedChar(PyObject *);

static CYTHON_INLINE signed short __Pyx_PyInt_AsSignedShort(PyObject *);

static CYTHON_INLINE signed int __Pyx_PyInt_AsSignedInt(PyObject *);

static CYTHON_INLINE int __Pyx_PyInt_AsLongDouble(PyObject *);

static CYTHON_INLINE unsigned long __Pyx_PyInt_AsUnsignedLong(PyObject *);

static CYTHON_INLINE unsigned PY_LONG_LONG __Pyx_PyInt_AsUnsignedLongLong(PyObject *);

static CYTHON_INLINE long __Pyx_PyInt_AsLong(PyObject *);

static CYTHON_INLINE PY_LONG_LONG __Pyx_PyInt_AsLongLong(PyObject *);

static CYTHON_INLINE signed long __Pyx_PyInt_AsSignedLong(PyObject *);

static CYTHON_INLINE signed PY_LONG_LONG __Pyx_PyInt_AsSignedLongLong(PyObject *);

static int __Pyx_check_binary_version(void);

static int __Pyx_ExportFunction(const char *name, void (*f)(void), const char *sig); 

static int __Pyx_SetVtable(PyObject *dict, void *vtable); 

#if !defined(__Pyx_PyIdentifier_FromString)
#if PY_MAJOR_VERSION < 3
  #define __Pyx_PyIdentifier_FromString(s) PyString_FromString(s)
#else
  #define __Pyx_PyIdentifier_FromString(s) PyUnicode_FromString(s)
#endif
#endif

static PyObject *__Pyx_ImportModule(const char *name); 

static PyTypeObject *__Pyx_ImportType(const char *module_name, const char *class_name, size_t size, int strict);  

typedef struct {
    int code_line;
    PyCodeObject* code_object;
} __Pyx_CodeObjectCacheEntry;
struct __Pyx_CodeObjectCache {
    int count;
    int max_count;
    __Pyx_CodeObjectCacheEntry* entries;
};
static struct __Pyx_CodeObjectCache __pyx_code_cache = {0,0,NULL};
static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line);
static PyCodeObject *__pyx_find_code_object(int code_line);
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object);

static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename); 

static int __Pyx_InitStrings(__Pyx_StringTabEntry *t); 













static PyTypeObject *__pyx_ptype_7cpython_4type_type = 0;






static PyTypeObject *__pyx_ptype_5numpy_dtype = 0;
static PyTypeObject *__pyx_ptype_5numpy_flatiter = 0;
static PyTypeObject *__pyx_ptype_5numpy_broadcast = 0;
static PyTypeObject *__pyx_ptype_5numpy_ndarray = 0;
static PyTypeObject *__pyx_ptype_5numpy_ufunc = 0;
static CYTHON_INLINE char *__pyx_f_5numpy__util_dtypestring(PyArray_Descr *, char *, char *, int *); 




static PyTypeObject *__pyx_ptype_5scipy_7spatial_5qhull__Qhull = 0;
static PyTypeObject *__pyx_ptype_5scipy_7spatial_5qhull_RidgeIter2D = 0;
static PyObject *__pyx_v_5scipy_7spatial_5qhull__active_qhull = 0;
static int __pyx_f_5scipy_7spatial_5qhull__get_delaunay_info(__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *, PyObject *, int, int); 
static int __pyx_f_5scipy_7spatial_5qhull__barycentric_inside(int, double *, double *, double *, double); 
static void __pyx_f_5scipy_7spatial_5qhull__barycentric_coordinate_single(int, double *, double *, double *, int); 
static void __pyx_f_5scipy_7spatial_5qhull__barycentric_coordinates(int, double *, double *, double *); 
static void __pyx_f_5scipy_7spatial_5qhull__lift_point(__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *, double *, double *); 
static double __pyx_f_5scipy_7spatial_5qhull__distplane(__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *, int, double *); 
static int __pyx_f_5scipy_7spatial_5qhull__is_point_fully_outside(__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *, double *, double); 
static int __pyx_f_5scipy_7spatial_5qhull__find_simplex_bruteforce(__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *, double *, double *, double, double); 
static int __pyx_f_5scipy_7spatial_5qhull__find_simplex_directed(__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *, double *, double *, int *, double, double); 
static int __pyx_f_5scipy_7spatial_5qhull__find_simplex(__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *, double *, double *, int *, double, double); 
static void __pyx_f_5scipy_7spatial_5qhull__RidgeIter2D_init(__pyx_t_5scipy_7spatial_5qhull_RidgeIter2D_t *, __pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *, int); 
static void __pyx_f_5scipy_7spatial_5qhull__RidgeIter2D_next(__pyx_t_5scipy_7spatial_5qhull_RidgeIter2D_t *); 
static double __pyx_f_5scipy_7spatial_5qhull__matrix_norm1(int, double *); 
static __Pyx_TypeInfo __Pyx_TypeInfo_nn___pyx_t_5numpy_double_t = { "double_t", NULL, sizeof(__pyx_t_5numpy_double_t), { 0 }, 0, 'R', 0, 0 };
static __Pyx_TypeInfo __Pyx_TypeInfo_nn_npy_int = { "npy_int", NULL, sizeof(npy_int), { 0 }, 0, IS_UNSIGNED(npy_int) ? 'U' : 'I', IS_UNSIGNED(npy_int), 0 };
#define __Pyx_MODULE_NAME "scipy.spatial.qhull"
int __pyx_module_is_main_scipy__spatial__qhull = 0;


static PyObject *__pyx_builtin_RuntimeError;
static PyObject *__pyx_builtin_object;
static PyObject *__pyx_builtin_property;
static PyObject *__pyx_builtin_ValueError;
static PyObject *__pyx_builtin_range;
static PyObject *__pyx_builtin_xrange;
static PyObject *__pyx_builtin_StopIteration;
static int __pyx_pf_5scipy_7spatial_5qhull_6_Qhull___init__(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *__pyx_v_self, PyArrayObject *__pyx_v_points, PyObject *__pyx_v_delaunay, PyObject *__pyx_v_incremental, PyObject *__pyx_v_options); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_6_Qhull_2close(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_6_Qhull_4__del__(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_6_Qhull_6add_points(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *__pyx_v_self, PyObject *__pyx_v_points); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_6_Qhull_8flush(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_6_Qhull_10get_arrays(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull__get_barycentric_transforms(CYTHON_UNUSED PyObject *__pyx_self, PyArrayObject *__pyx_v_points, PyArrayObject *__pyx_v_vertices, double __pyx_v_eps); 
static int __pyx_pf_5scipy_7spatial_5qhull_11RidgeIter2D___init__(struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D *__pyx_v_self, PyObject *__pyx_v_delaunay, PyObject *__pyx_v_ivertex); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_11RidgeIter2D_2__iter__(struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_11RidgeIter2D_4__next__(struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_38__defaults__(CYTHON_UNUSED PyObject *__pyx_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay___init__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_points, PyObject *__pyx_v_incremental, PyObject *__pyx_v_qhull_options); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_2add_points(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_points); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_40__defaults__(CYTHON_UNUSED PyObject *__pyx_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_4_flush(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_force); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_6points(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_8vertices(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_10neighbors(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_12equations(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_14npoints(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_16nsimplex(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_18min_bound(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_20max_bound(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_22paraboloid_scale(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_24paraboloid_shift(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_26transform(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_28vertex_to_simplex(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_30convex_hull(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_42__defaults__(CYTHON_UNUSED PyObject *__pyx_self); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_32find_simplex(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_xi, PyObject *__pyx_v_bruteforce, PyObject *__pyx_v_tol); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_34plane_distance(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_xi); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_36lift_points(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_x); 
static PyObject *__pyx_pf_5scipy_7spatial_5qhull_2tsearch(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_tri, PyObject *__pyx_v_xi); 
static int __pyx_pf_5numpy_7ndarray___getbuffer__(PyArrayObject *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags); 
static void __pyx_pf_5numpy_7ndarray_2__releasebuffer__(PyArrayObject *__pyx_v_self, Py_buffer *__pyx_v_info); 
static char __pyx_k_3[] = "";
static char __pyx_k_4[] = "qhull d ";
static char __pyx_k_5[] = "qhull ";
static char __pyx_k_7[] = " %s ";
static char __pyx_k_8[] = "Qhull options %r are incompatible with incremental mode";
static char __pyx_k_9[] = "No points to triangulate";
static char __pyx_k_11[] = "Need at least 2-D data to triangulate";
static char __pyx_k_13[] = "Qhull error";
static char __pyx_k_15[] = "This Qhull instance is not alive";
static char __pyx_k_17[] = "qhull: did not free %d bytes (%d pieces)";
static char __pyx_k_20[] = "non-simplical facet generated";
static char __pyx_k_22[] = "RidgeIter2D supports only 2-D";
static char __pyx_k_24[] = "Qbb Qz Qt";
static char __pyx_k_25[] = "_get_barycentric_transforms";
static char __pyx_k_27[] = "wrong dimensionality in xi";
static char __pyx_k_29[] = "xi has different dimensionality than triangulation";
static char __pyx_k_36[] = "ndarray is not C contiguous";
static char __pyx_k_38[] = "ndarray is not Fortran contiguous";
static char __pyx_k_40[] = "Non-native byte order not supported";
static char __pyx_k_42[] = "unknown dtype code in numpy.pxd (%d)";
static char __pyx_k_43[] = "Format string allocated too short, see comment in numpy.pxd";
static char __pyx_k_46[] = "Format string allocated too short.";
static char __pyx_k_48[] = "\nWrappers for Qhull triangulation, plus some additional N-D geometry utilities\n\n.. versionadded:: 0.9\n\n";
static char __pyx_k_49[] = "scipy.spatial.qhull";
static char __pyx_k_52[] = "/home/pauli/prj/scipy/scipy/scipy/spatial/qhull.pyx";
static char __pyx_k_91[] = "\n    Delaunay(points)\n\n    Delaunay tesselation in N dimensions.\n\n    Parameters\n    ----------\n    points : ndarray of floats, shape (npoints, ndim)\n        Coordinates of points to triangulate\n    incremental : bool, optional\n        Whether to allow adding points incrementally to the triangulation.\n        Qhull does not support removing points from the triangulation,\n        and you may run into problems with coplanar facets.\n        Default: False.\n\n        .. versionadded:: 0.12.0\n    qhull_options : str, optional\n        Additional options to Qhull (separated by spaces). See Qhull\n        documentation [Qhull] for details.\n\n        .. versionadded:: 0.12.0\n\n    Attributes\n    ----------\n    points : ndarray of double, shape (npoints, ndim)\n        Points in the triangulation.\n    vertices : ndarray of ints, shape (nsimplex, ndim+1)\n        Indices of vertices forming simplices in the triangulation.\n    neighbors : ndarray of ints, shape (nsimplex, ndim+1)\n        Indices of neighbor simplices for each simplex.\n        The kth neighbor is opposite to the kth vertex.\n        For simplices at the boundary, -1 denotes no neighbor.\n    equations : ndarray of double, shape (nsimplex, ndim+2)\n        [normal, offset] forming the hyperplane equation of the facet\n        on the paraboloid (see [Qhull]_ documentation for more).\n    paraboloid_scale, paraboloid_shift : float\n        Scale and shift for the extra paraboloid dimension\n        (see [Qhull]_ documentation for more).\n    transform : ndarray of double, shape (nsimplex, ndim+1, ndim)\n        Affine transform from ``x`` to the barycentric coordinates ``c``.\n        This is defined by::\n\n            T c = x - r\n\n        At vertex ``j``, ``c_j = 1`` and the other coordinates zero.\n\n        For simplex ``i``, ``transform[i,:ndim,:ndim]`` contains\n        inverse of the matrix ``T``, and ``transform[i,ndim,:]``\n        contains the vector ``r``.\n    vertex_to_simplex"" : ndarray of int, shape (npoints,)\n        Lookup array, from a vertex, to some simplex which it is a part of.\n    convex_hull : ndarray of int, shape (nfaces, ndim)\n        Vertices of facets forming the convex hull of the point set.\n        The array contains the indices of the points belonging to\n        the (N-1)-dimensional facets that form the convex hull\n        of the triangulation.\n\n    Notes\n    -----\n    The tesselation is computed using the Qhull libary [Qhull]_.\n\n    .. versionadded:: 0.9\n\n    References\n    ----------\n    .. [Qhull] http://www.qhull.org/\n\n    ";
static char __pyx_k__1[] = "1";
static char __pyx_k__B[] = "B";
static char __pyx_k__H[] = "H";
static char __pyx_k__I[] = "I";
static char __pyx_k__L[] = "L";
static char __pyx_k__N[] = "N";
static char __pyx_k__O[] = "O";
static char __pyx_k__Q[] = "Q";
static char __pyx_k__T[] = "T";
static char __pyx_k__b[] = "b";
static char __pyx_k__c[] = "c";
static char __pyx_k__d[] = "d";
static char __pyx_k__f[] = "f";
static char __pyx_k__g[] = "g";
static char __pyx_k__h[] = "h";
static char __pyx_k__i[] = "i";
static char __pyx_k__j[] = "j";
static char __pyx_k__k[] = "k";
static char __pyx_k__l[] = "l";
static char __pyx_k__m[] = "m";
static char __pyx_k__n[] = "n";
static char __pyx_k__q[] = "q";
static char __pyx_k__x[] = "x";
static char __pyx_k__z[] = "z";
static char __pyx_k__Qt[] = "Qt";
static char __pyx_k__Qz[] = "Qz";
static char __pyx_k__Zd[] = "Zd";
static char __pyx_k__Zf[] = "Zf";
static char __pyx_k__Zg[] = "Zg";
static char __pyx_k__np[] = "np";
static char __pyx_k__x1[] = "x1";
static char __pyx_k__x2[] = "x2";
static char __pyx_k__x3[] = "x3";
static char __pyx_k__xi[] = "xi";
static char __pyx_k__y1[] = "y1";
static char __pyx_k__y2[] = "y2";
static char __pyx_k__y3[] = "y3";
static char __pyx_k__QBk[] = "QBk";
static char __pyx_k__QbB[] = "QbB";
static char __pyx_k__Qbb[] = "Qbb";
static char __pyx_k__Qbk[] = "Qbk";
static char __pyx_k__arr[] = "arr";
static char __pyx_k__det[] = "det";
static char __pyx_k__eps[] = "eps";
static char __pyx_k__lda[] = "lda";
static char __pyx_k__ldb[] = "ldb";
static char __pyx_k__max[] = "max";
static char __pyx_k__min[] = "min";
static char __pyx_k__nan[] = "nan";
static char __pyx_k__out[] = "out";
static char __pyx_k__sum[] = "sum";
static char __pyx_k__tol[] = "tol";
static char __pyx_k__tri[] = "tri";
static char __pyx_k__Lock[] = "Lock";
static char __pyx_k__axis[] = "axis";
static char __pyx_k__copy[] = "copy";
static char __pyx_k__fill[] = "fill";
static char __pyx_k__info[] = "info";
static char __pyx_k__intc[] = "intc";
static char __pyx_k__ipiv[] = "ipiv";
static char __pyx_k__ndim[] = "ndim";
static char __pyx_k__nrhs[] = "nrhs";
static char __pyx_k__out_[] = "out_";
static char __pyx_k__prod[] = "prod";
static char __pyx_k__self[] = "self";
static char __pyx_k__sqrt[] = "sqrt";
static char __pyx_k__work[] = "work";
static char __pyx_k__Tinvs[] = "Tinvs";
static char __pyx_k__anorm[] = "anorm";
static char __pyx_k__close[] = "close";
static char __pyx_k__dtype[] = "dtype";
static char __pyx_k__empty[] = "empty";
static char __pyx_k__finfo[] = "finfo";
static char __pyx_k__flush[] = "flush";
static char __pyx_k__force[] = "force";
static char __pyx_k__iwork[] = "iwork";
static char __pyx_k__msize[] = "msize";
static char __pyx_k__numpy[] = "numpy";
static char __pyx_k__range[] = "range";
static char __pyx_k__rcond[] = "rcond";
static char __pyx_k__shape[] = "shape";
static char __pyx_k__start[] = "start";
static char __pyx_k__zeros[] = "zeros";
static char __pyx_k___flush[] = "_flush";
static char __pyx_k___qhull[] = "_qhull";
static char __pyx_k__astype[] = "astype";
static char __pyx_k__double[] = "double";
static char __pyx_k__object[] = "object";
static char __pyx_k__points[] = "points";
static char __pyx_k__resize[] = "resize";
static char __pyx_k__vstack[] = "vstack";
static char __pyx_k__xrange[] = "xrange";
static char __pyx_k____all__[] = "__all__";
static char __pyx_k___points[] = "_points";
static char __pyx_k__acquire[] = "acquire";
static char __pyx_k__ivertex[] = "ivertex";
static char __pyx_k__npoints[] = "npoints";
static char __pyx_k__options[] = "options";
static char __pyx_k__release[] = "release";
static char __pyx_k__reshape[] = "reshape";
static char __pyx_k__tsearch[] = "tsearch";
static char __pyx_k__Delaunay[] = "Delaunay";
static char __pyx_k____init__[] = "__init__";
static char __pyx_k____main__[] = "__main__";
static char __pyx_k____test__[] = "__test__";
static char __pyx_k___npoints[] = "_npoints";
static char __pyx_k__centroid[] = "centroid";
static char __pyx_k__delaunay[] = "delaunay";
static char __pyx_k__isimplex[] = "isimplex";
static char __pyx_k__nsimplex[] = "nsimplex";
static char __pyx_k__property[] = "property";
static char __pyx_k__vertices[] = "vertices";
static char __pyx_k__xi_shape[] = "xi_shape";
static char __pyx_k___nsimplex[] = "_nsimplex";
static char __pyx_k___vertices[] = "_vertices";
static char __pyx_k__eps_broad[] = "eps_broad";
static char __pyx_k__equations[] = "equations";
static char __pyx_k__max_bound[] = "max_bound";
static char __pyx_k__min_bound[] = "min_bound";
static char __pyx_k__neighbors[] = "neighbors";
static char __pyx_k__threading[] = "threading";
static char __pyx_k__transform[] = "transform";
static char __pyx_k__QhullError[] = "QhullError";
static char __pyx_k__ValueError[] = "ValueError";
static char __pyx_k___equations[] = "_equations";
static char __pyx_k___max_bound[] = "_max_bound";
static char __pyx_k___min_bound[] = "_min_bound";
static char __pyx_k___neighbors[] = "_neighbors";
static char __pyx_k___transform[] = "_transform";
static char __pyx_k__add_points[] = "add_points";
static char __pyx_k__asanyarray[] = "asanyarray";
static char __pyx_k__bruteforce[] = "bruteforce";
static char __pyx_k__get_arrays[] = "get_arrays";
static char __pyx_k___deactivate[] = "_deactivate";
static char __pyx_k___qhull_lock[] = "_qhull_lock";
static char __pyx_k__convex_hull[] = "convex_hull";
static char __pyx_k__incremental[] = "incremental";
static char __pyx_k__lift_points[] = "lift_points";
static char __pyx_k__rcond_limit[] = "rcond_limit";
static char __pyx_k__RuntimeError[] = "RuntimeError";
static char __pyx_k__find_simplex[] = "find_simplex";
static char __pyx_k__StopIteration[] = "StopIteration";
static char __pyx_k__qhull_options[] = "qhull_options";
static char __pyx_k__plane_distance[] = "plane_distance";
static char __pyx_k__paraboloid_scale[] = "paraboloid_scale";
static char __pyx_k__paraboloid_shift[] = "paraboloid_shift";
static char __pyx_k__ascontiguousarray[] = "ascontiguousarray";
static char __pyx_k__vertex_to_simplex[] = "vertex_to_simplex";
static char __pyx_k___vertex_to_simplex[] = "_vertex_to_simplex";
static PyObject *__pyx_kp_s_11;
static PyObject *__pyx_kp_s_13;
static PyObject *__pyx_kp_s_15;
static PyObject *__pyx_kp_s_17;
static PyObject *__pyx_kp_s_20;
static PyObject *__pyx_kp_s_22;
static PyObject *__pyx_kp_s_24;
static PyObject *__pyx_n_s_25;
static PyObject *__pyx_kp_s_27;
static PyObject *__pyx_kp_s_29;
static PyObject *__pyx_kp_s_3;
static PyObject *__pyx_kp_u_36;
static PyObject *__pyx_kp_u_38;
static PyObject *__pyx_kp_b_4;
static PyObject *__pyx_kp_u_40;
static PyObject *__pyx_kp_u_42;
static PyObject *__pyx_kp_u_43;
static PyObject *__pyx_kp_u_46;
static PyObject *__pyx_n_s_49;
static PyObject *__pyx_kp_b_5;
static PyObject *__pyx_kp_s_52;
static PyObject *__pyx_kp_s_7;
static PyObject *__pyx_kp_s_8;
static PyObject *__pyx_kp_s_9;
static PyObject *__pyx_kp_s_91;
static PyObject *__pyx_n_s__Delaunay;
static PyObject *__pyx_n_s__Lock;
static PyObject *__pyx_n_s__QBk;
static PyObject *__pyx_n_s__QbB;
static PyObject *__pyx_n_s__Qbb;
static PyObject *__pyx_n_s__Qbk;
static PyObject *__pyx_n_s__QhullError;
static PyObject *__pyx_n_s__Qt;
static PyObject *__pyx_n_s__Qz;
static PyObject *__pyx_n_s__RuntimeError;
static PyObject *__pyx_n_s__StopIteration;
static PyObject *__pyx_n_s__T;
static PyObject *__pyx_n_s__Tinvs;
static PyObject *__pyx_n_s__ValueError;
static PyObject *__pyx_n_s____all__;
static PyObject *__pyx_n_s____init__;
static PyObject *__pyx_n_s____main__;
static PyObject *__pyx_n_s____test__;
static PyObject *__pyx_n_s___deactivate;
static PyObject *__pyx_n_s___equations;
static PyObject *__pyx_n_s___flush;
static PyObject *__pyx_n_s___max_bound;
static PyObject *__pyx_n_s___min_bound;
static PyObject *__pyx_n_s___neighbors;
static PyObject *__pyx_n_s___npoints;
static PyObject *__pyx_n_s___nsimplex;
static PyObject *__pyx_n_s___points;
static PyObject *__pyx_n_s___qhull;
static PyObject *__pyx_n_s___qhull_lock;
static PyObject *__pyx_n_s___transform;
static PyObject *__pyx_n_s___vertex_to_simplex;
static PyObject *__pyx_n_s___vertices;
static PyObject *__pyx_n_s__acquire;
static PyObject *__pyx_n_s__add_points;
static PyObject *__pyx_n_s__anorm;
static PyObject *__pyx_n_s__arr;
static PyObject *__pyx_n_s__asanyarray;
static PyObject *__pyx_n_s__ascontiguousarray;
static PyObject *__pyx_n_s__astype;
static PyObject *__pyx_n_s__axis;
static PyObject *__pyx_n_s__bruteforce;
static PyObject *__pyx_n_s__c;
static PyObject *__pyx_n_s__centroid;
static PyObject *__pyx_n_s__close;
static PyObject *__pyx_n_s__convex_hull;
static PyObject *__pyx_n_s__copy;
static PyObject *__pyx_n_s__delaunay;
static PyObject *__pyx_n_s__det;
static PyObject *__pyx_n_s__double;
static PyObject *__pyx_n_s__dtype;
static PyObject *__pyx_n_s__empty;
static PyObject *__pyx_n_s__eps;
static PyObject *__pyx_n_s__eps_broad;
static PyObject *__pyx_n_s__equations;
static PyObject *__pyx_n_s__fill;
static PyObject *__pyx_n_s__find_simplex;
static PyObject *__pyx_n_s__finfo;
static PyObject *__pyx_n_s__flush;
static PyObject *__pyx_n_s__force;
static PyObject *__pyx_n_s__get_arrays;
static PyObject *__pyx_n_s__i;
static PyObject *__pyx_n_s__incremental;
static PyObject *__pyx_n_s__info;
static PyObject *__pyx_n_s__intc;
static PyObject *__pyx_n_s__ipiv;
static PyObject *__pyx_n_s__isimplex;
static PyObject *__pyx_n_s__ivertex;
static PyObject *__pyx_n_s__iwork;
static PyObject *__pyx_n_s__j;
static PyObject *__pyx_n_s__k;
static PyObject *__pyx_n_s__lda;
static PyObject *__pyx_n_s__ldb;
static PyObject *__pyx_n_s__lift_points;
static PyObject *__pyx_n_s__m;
static PyObject *__pyx_n_s__max;
static PyObject *__pyx_n_s__max_bound;
static PyObject *__pyx_n_s__min;
static PyObject *__pyx_n_s__min_bound;
static PyObject *__pyx_n_s__msize;
static PyObject *__pyx_n_s__n;
static PyObject *__pyx_n_s__nan;
static PyObject *__pyx_n_s__ndim;
static PyObject *__pyx_n_s__neighbors;
static PyObject *__pyx_n_s__np;
static PyObject *__pyx_n_s__npoints;
static PyObject *__pyx_n_s__nrhs;
static PyObject *__pyx_n_s__nsimplex;
static PyObject *__pyx_n_s__numpy;
static PyObject *__pyx_n_s__object;
static PyObject *__pyx_n_s__options;
static PyObject *__pyx_n_s__out;
static PyObject *__pyx_n_s__out_;
static PyObject *__pyx_n_s__paraboloid_scale;
static PyObject *__pyx_n_s__paraboloid_shift;
static PyObject *__pyx_n_s__plane_distance;
static PyObject *__pyx_n_s__points;
static PyObject *__pyx_n_s__prod;
static PyObject *__pyx_n_s__property;
static PyObject *__pyx_n_s__qhull_options;
static PyObject *__pyx_n_s__range;
static PyObject *__pyx_n_s__rcond;
static PyObject *__pyx_n_s__rcond_limit;
static PyObject *__pyx_n_s__release;
static PyObject *__pyx_n_s__reshape;
static PyObject *__pyx_n_s__resize;
static PyObject *__pyx_n_s__self;
static PyObject *__pyx_n_s__shape;
static PyObject *__pyx_n_s__sqrt;
static PyObject *__pyx_n_s__start;
static PyObject *__pyx_n_s__sum;
static PyObject *__pyx_n_s__threading;
static PyObject *__pyx_n_s__tol;
static PyObject *__pyx_n_s__transform;
static PyObject *__pyx_n_s__tri;
static PyObject *__pyx_n_s__tsearch;
static PyObject *__pyx_n_s__vertex_to_simplex;
static PyObject *__pyx_n_s__vertices;
static PyObject *__pyx_n_s__vstack;
static PyObject *__pyx_n_s__work;
static PyObject *__pyx_n_s__x;
static PyObject *__pyx_n_s__x1;
static PyObject *__pyx_n_s__x2;
static PyObject *__pyx_n_s__x3;
static PyObject *__pyx_n_s__xi;
static PyObject *__pyx_n_s__xi_shape;
static PyObject *__pyx_n_s__xrange;
static PyObject *__pyx_n_s__y1;
static PyObject *__pyx_n_s__y2;
static PyObject *__pyx_n_s__y3;
static PyObject *__pyx_n_s__z;
static PyObject *__pyx_n_s__zeros;
static PyObject *__pyx_int_0;
static PyObject *__pyx_int_1;
static PyObject *__pyx_int_2;
static PyObject *__pyx_int_3;
static PyObject *__pyx_int_neg_1;
static PyObject *__pyx_int_15;
static PyObject *__pyx_int_100;
static PyObject *__pyx_k_1;
static PyObject *__pyx_k_2;
static PyObject *__pyx_k_tuple_6;
static PyObject *__pyx_k_slice_18;
static PyObject *__pyx_k_slice_31;
static PyObject *__pyx_k_tuple_10;
static PyObject *__pyx_k_tuple_12;
static PyObject *__pyx_k_tuple_14;
static PyObject *__pyx_k_tuple_16;
static PyObject *__pyx_k_tuple_19;
static PyObject *__pyx_k_tuple_21;
static PyObject *__pyx_k_tuple_23;
static PyObject *__pyx_k_tuple_26;
static PyObject *__pyx_k_tuple_28;
static PyObject *__pyx_k_tuple_30;
static PyObject *__pyx_k_tuple_32;
static PyObject *__pyx_k_tuple_33;
static PyObject *__pyx_k_tuple_34;
static PyObject *__pyx_k_tuple_35;
static PyObject *__pyx_k_tuple_37;
static PyObject *__pyx_k_tuple_39;
static PyObject *__pyx_k_tuple_41;
static PyObject *__pyx_k_tuple_44;
static PyObject *__pyx_k_tuple_45;
static PyObject *__pyx_k_tuple_47;
static PyObject *__pyx_k_tuple_50;
static PyObject *__pyx_k_tuple_53;
static PyObject *__pyx_k_tuple_55;
static PyObject *__pyx_k_tuple_57;
static PyObject *__pyx_k_tuple_59;
static PyObject *__pyx_k_tuple_61;
static PyObject *__pyx_k_tuple_63;
static PyObject *__pyx_k_tuple_65;
static PyObject *__pyx_k_tuple_67;
static PyObject *__pyx_k_tuple_69;
static PyObject *__pyx_k_tuple_71;
static PyObject *__pyx_k_tuple_73;
static PyObject *__pyx_k_tuple_75;
static PyObject *__pyx_k_tuple_77;
static PyObject *__pyx_k_tuple_79;
static PyObject *__pyx_k_tuple_81;
static PyObject *__pyx_k_tuple_83;
static PyObject *__pyx_k_tuple_85;
static PyObject *__pyx_k_tuple_87;
static PyObject *__pyx_k_tuple_89;
static PyObject *__pyx_k_tuple_92;
static PyObject *__pyx_k_codeobj_51;
static PyObject *__pyx_k_codeobj_54;
static PyObject *__pyx_k_codeobj_56;
static PyObject *__pyx_k_codeobj_58;
static PyObject *__pyx_k_codeobj_60;
static PyObject *__pyx_k_codeobj_62;
static PyObject *__pyx_k_codeobj_64;
static PyObject *__pyx_k_codeobj_66;
static PyObject *__pyx_k_codeobj_68;
static PyObject *__pyx_k_codeobj_70;
static PyObject *__pyx_k_codeobj_72;
static PyObject *__pyx_k_codeobj_74;
static PyObject *__pyx_k_codeobj_76;
static PyObject *__pyx_k_codeobj_78;
static PyObject *__pyx_k_codeobj_80;
static PyObject *__pyx_k_codeobj_82;
static PyObject *__pyx_k_codeobj_84;
static PyObject *__pyx_k_codeobj_86;
static PyObject *__pyx_k_codeobj_88;
static PyObject *__pyx_k_codeobj_90;
static PyObject *__pyx_k_codeobj_93;


static int __pyx_pw_5scipy_7spatial_5qhull_6_Qhull_1__init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static int __pyx_pw_5scipy_7spatial_5qhull_6_Qhull_1__init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyArrayObject *__pyx_v_points = 0;
  PyObject *__pyx_v_delaunay = 0;
  PyObject *__pyx_v_incremental = 0;
  PyObject *__pyx_v_options = 0;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__init__ (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s__points,&__pyx_n_s__delaunay,&__pyx_n_s__incremental,&__pyx_n_s__options,0};
    PyObject* values[4] = {0,0,0,0};
    values[1] = __pyx_k_1;
    values[2] = __pyx_k_2;
    values[3] = ((PyObject *)__pyx_kp_s_3);
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__points)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s__delaunay);
          if (value) { values[1] = value; kw_args--; }
        }
        case  2:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s__incremental);
          if (value) { values[2] = value; kw_args--; }
        }
        case  3:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s__options);
          if (value) { values[3] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__init__") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 174; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_points = ((PyArrayObject *)values[0]);
    __pyx_v_delaunay = values[1];
    __pyx_v_incremental = values[2];
    __pyx_v_options = values[3];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__init__", 0, 1, 4, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 174; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("scipy.spatial.qhull._Qhull.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return -1;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_points), __pyx_ptype_5numpy_ndarray, 1, "points", 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 174; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_6_Qhull___init__(((struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *)__pyx_v_self), __pyx_v_points, __pyx_v_delaunay, __pyx_v_incremental, __pyx_v_options);
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static int __pyx_pf_5scipy_7spatial_5qhull_6_Qhull___init__(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *__pyx_v_self, PyArrayObject *__pyx_v_points, PyObject *__pyx_v_delaunay, PyObject *__pyx_v_incremental, PyObject *__pyx_v_options) {
  char *__pyx_v_options_p;
  int __pyx_v_dim;
  int __pyx_v_numpoints;
  int __pyx_v_exitcode;
  PyObject *__pyx_v_bad_opts = NULL;
  PyObject *__pyx_v_bad_opt = NULL;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_points;
  __Pyx_Buffer __pyx_pybuffer_points;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  Py_ssize_t __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_t_5;
  PyObject *__pyx_t_6 = NULL;
  PyArrayObject *__pyx_t_7 = NULL;
  int __pyx_t_8;
  PyObject *__pyx_t_9 = NULL;
  PyObject *__pyx_t_10 = NULL;
  PyObject *__pyx_t_11 = NULL;
  char *__pyx_t_12;
  realT __pyx_t_13;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__init__", 0);
  __Pyx_INCREF((PyObject *)__pyx_v_points);
  __Pyx_INCREF(__pyx_v_options);
  __pyx_pybuffer_points.pybuffer.buf = NULL;
  __pyx_pybuffer_points.refcount = 0;
  __pyx_pybuffernd_points.data = NULL;
  __pyx_pybuffernd_points.rcbuffer = &__pyx_pybuffer_points;
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_points.rcbuffer->pybuffer, (PyObject*)__pyx_v_points, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack) == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 174; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_pybuffernd_points.diminfo[0].strides = __pyx_pybuffernd_points.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_points.diminfo[0].shape = __pyx_pybuffernd_points.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_points.diminfo[1].strides = __pyx_pybuffernd_points.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_points.diminfo[1].shape = __pyx_pybuffernd_points.rcbuffer->pybuffer.shape[1];

  
  __pyx_v_self->_saved_qh = NULL;

  
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->_dirty_points);
  __Pyx_DECREF(__pyx_v_self->_dirty_points);
  __pyx_v_self->_dirty_points = Py_None;

  
  __pyx_v_self->_n_dirty_points = 0;

  
  __pyx_t_1 = __Pyx_PyObject_IsTrue(__pyx_v_delaunay); if (unlikely(__pyx_t_1 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 189; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__pyx_t_1) {

    
    __pyx_t_2 = PyNumber_Add(((PyObject *)__pyx_kp_b_4), __pyx_v_options); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 190; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_v_options);
    __pyx_v_options = __pyx_t_2;
    __pyx_t_2 = 0;

    
    __pyx_v_self->_is_delaunay = 1;
    goto __pyx_L3;
  }
   {

    
    __pyx_t_2 = PyNumber_Add(((PyObject *)__pyx_kp_b_5), __pyx_v_options); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 193; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_v_options);
    __pyx_v_options = __pyx_t_2;
    __pyx_t_2 = 0;

    
    __pyx_v_self->_is_delaunay = 0;
  }
  __pyx_L3:;

  
  __pyx_t_1 = __Pyx_PyObject_IsTrue(__pyx_v_incremental); if (unlikely(__pyx_t_1 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 196; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__pyx_t_1) {

    
    __pyx_t_2 = PyList_New(0); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 197; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_v_bad_opts = __pyx_t_2;
    __pyx_t_2 = 0;

    
    __pyx_t_2 = ((PyObject *)__pyx_k_tuple_6); __Pyx_INCREF(__pyx_t_2); __pyx_t_3 = 0;
    for (;;) {
      if (__pyx_t_3 >= PyTuple_GET_SIZE(__pyx_t_2)) break;
      #if CYTHON_COMPILING_IN_CPYTHON
      __pyx_t_4 = PyTuple_GET_ITEM(__pyx_t_2, __pyx_t_3); __Pyx_INCREF(__pyx_t_4); __pyx_t_3++; if (unlikely(0 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 198; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      #else
      __pyx_t_4 = PySequence_ITEM(__pyx_t_2, __pyx_t_3); __pyx_t_3++; if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 198; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      #endif
      __Pyx_XDECREF(__pyx_v_bad_opt);
      __pyx_v_bad_opt = __pyx_t_4;
      __pyx_t_4 = 0;

      
      __pyx_t_4 = PyNumber_Remainder(((PyObject *)__pyx_kp_s_7), __pyx_v_bad_opt); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 199; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(((PyObject *)__pyx_t_4));
      __pyx_t_1 = (__Pyx_PySequence_Contains(((PyObject *)__pyx_t_4), __pyx_v_options, Py_EQ)); if (unlikely(__pyx_t_1 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 199; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(((PyObject *)__pyx_t_4)); __pyx_t_4 = 0;
      if (__pyx_t_1) {

        
        __pyx_t_5 = PyList_Append(__pyx_v_bad_opts, __pyx_v_bad_opt); if (unlikely(__pyx_t_5 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 200; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        goto __pyx_L7;
      }
      __pyx_L7:;
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

    
    __pyx_t_1 = (((PyObject *)__pyx_v_bad_opts) != Py_None) && (PyList_GET_SIZE(((PyObject *)__pyx_v_bad_opts)) != 0);
    if (__pyx_t_1) {

      
      __pyx_t_2 = PyNumber_Remainder(((PyObject *)__pyx_kp_s_8), ((PyObject *)__pyx_v_bad_opts)); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 202; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(((PyObject *)__pyx_t_2));
      __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 202; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_4);
      PyTuple_SET_ITEM(__pyx_t_4, 0, ((PyObject *)__pyx_t_2));
      __Pyx_GIVEREF(((PyObject *)__pyx_t_2));
      __pyx_t_2 = 0;
      __pyx_t_2 = PyObject_Call(__pyx_builtin_ValueError, ((PyObject *)__pyx_t_4), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 202; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(((PyObject *)__pyx_t_4)); __pyx_t_4 = 0;
      __Pyx_Raise(__pyx_t_2, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 202; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      goto __pyx_L8;
    }
    __pyx_L8:;
    goto __pyx_L4;
  }
  __pyx_L4:;

  
  __pyx_t_2 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 204; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = PyObject_GetAttr(__pyx_t_2, __pyx_n_s__ascontiguousarray); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 204; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 204; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(((PyObject *)__pyx_v_points));
  PyTuple_SET_ITEM(__pyx_t_2, 0, ((PyObject *)__pyx_v_points));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_points));
  __pyx_t_6 = PyObject_Call(__pyx_t_4, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 204; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  if (!(likely(((__pyx_t_6) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_6, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 204; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_7 = ((PyArrayObject *)__pyx_t_6);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_points.rcbuffer->pybuffer);
    __pyx_t_8 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_points.rcbuffer->pybuffer, (PyObject*)__pyx_t_7, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack);
    if (unlikely(__pyx_t_8 < 0)) {
      PyErr_Fetch(&__pyx_t_9, &__pyx_t_10, &__pyx_t_11);
      if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_points.rcbuffer->pybuffer, (PyObject*)__pyx_v_points, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack) == -1)) {
        Py_XDECREF(__pyx_t_9); Py_XDECREF(__pyx_t_10); Py_XDECREF(__pyx_t_11);
        __Pyx_RaiseBufferFallbackError();
      } else {
        PyErr_Restore(__pyx_t_9, __pyx_t_10, __pyx_t_11);
      }
    }
    __pyx_pybuffernd_points.diminfo[0].strides = __pyx_pybuffernd_points.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_points.diminfo[0].shape = __pyx_pybuffernd_points.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_points.diminfo[1].strides = __pyx_pybuffernd_points.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_points.diminfo[1].shape = __pyx_pybuffernd_points.rcbuffer->pybuffer.shape[1];
    if (unlikely(__pyx_t_8 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 204; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_7 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_v_points));
  __pyx_v_points = ((PyArrayObject *)__pyx_t_6);
  __pyx_t_6 = 0;

  
  __pyx_v_numpoints = (__pyx_v_points->dimensions[0]);

  
  __pyx_v_dim = (__pyx_v_points->dimensions[1]);

  
  __pyx_v_self->_ndim = __pyx_v_dim;

  
  __pyx_t_1 = (__pyx_v_numpoints <= 0);
  if (__pyx_t_1) {

    
    __pyx_t_6 = PyObject_Call(__pyx_builtin_ValueError, ((PyObject *)__pyx_k_tuple_10), NULL); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 210; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_Raise(__pyx_t_6, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 210; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    goto __pyx_L9;
  }
  __pyx_L9:;

  
  __pyx_t_1 = (__pyx_v_dim < 2);
  if (__pyx_t_1) {

    
    __pyx_t_6 = PyObject_Call(__pyx_builtin_ValueError, ((PyObject *)__pyx_k_tuple_12), NULL); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 213; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_Raise(__pyx_t_6, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 213; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    goto __pyx_L10;
  }
  __pyx_L10:;

  
  __pyx_t_1 = __Pyx_PyObject_IsTrue(__pyx_v_incremental); if (unlikely(__pyx_t_1 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 215; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__pyx_t_1) {

    
    __pyx_t_6 = PyObject_GetAttr(((PyObject *)__pyx_v_points), __pyx_n_s__copy); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 217; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_2 = PyObject_Call(__pyx_t_6, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 217; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    if (!(likely(((__pyx_t_2) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_2, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 217; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_t_7 = ((PyArrayObject *)__pyx_t_2);
    {
      __Pyx_BufFmt_StackElem __pyx_stack[1];
      __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_points.rcbuffer->pybuffer);
      __pyx_t_8 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_points.rcbuffer->pybuffer, (PyObject*)__pyx_t_7, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack);
      if (unlikely(__pyx_t_8 < 0)) {
        PyErr_Fetch(&__pyx_t_11, &__pyx_t_10, &__pyx_t_9);
        if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_points.rcbuffer->pybuffer, (PyObject*)__pyx_v_points, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack) == -1)) {
          Py_XDECREF(__pyx_t_11); Py_XDECREF(__pyx_t_10); Py_XDECREF(__pyx_t_9);
          __Pyx_RaiseBufferFallbackError();
        } else {
          PyErr_Restore(__pyx_t_11, __pyx_t_10, __pyx_t_9);
        }
      }
      __pyx_pybuffernd_points.diminfo[0].strides = __pyx_pybuffernd_points.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_points.diminfo[0].shape = __pyx_pybuffernd_points.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_points.diminfo[1].strides = __pyx_pybuffernd_points.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_points.diminfo[1].shape = __pyx_pybuffernd_points.rcbuffer->pybuffer.shape[1];
      if (unlikely(__pyx_t_8 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 217; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_t_7 = 0;
    __Pyx_DECREF(((PyObject *)__pyx_v_points));
    __pyx_v_points = ((PyArrayObject *)__pyx_t_2);
    __pyx_t_2 = 0;
    goto __pyx_L11;
  }
  __pyx_L11:;

  
  __pyx_t_2 = PyList_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 219; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(((PyObject *)__pyx_v_points));
  PyList_SET_ITEM(__pyx_t_2, 0, ((PyObject *)__pyx_v_points));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_points));
  __Pyx_GIVEREF(((PyObject *)__pyx_t_2));
  __Pyx_GOTREF(__pyx_v_self->_point_arrays);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->_point_arrays));
  __pyx_v_self->_point_arrays = __pyx_t_2;
  __pyx_t_2 = 0;

  
  __pyx_t_12 = PyBytes_AsString(__pyx_v_options); if (unlikely((!__pyx_t_12) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 221; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_v_options_p = __pyx_t_12;

  
  __pyx_t_2 = __Pyx_GetName(__pyx_m, __pyx_n_s___qhull_lock); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 223; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_6 = PyObject_GetAttr(__pyx_t_2, __pyx_n_s__acquire); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 223; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_Call(__pyx_t_6, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 223; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  
   {

    
    __pyx_t_1 = (__pyx_v_5scipy_7spatial_5qhull__active_qhull != Py_None);
    if (__pyx_t_1) {

      
      __pyx_t_2 = PyObject_GetAttr(__pyx_v_5scipy_7spatial_5qhull__active_qhull, __pyx_n_s___deactivate); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 226; __pyx_clineno = __LINE__; goto __pyx_L13;}
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_6 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 226; __pyx_clineno = __LINE__; goto __pyx_L13;}
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      goto __pyx_L15;
    }
    __pyx_L15:;

    
    __Pyx_INCREF(((PyObject *)__pyx_v_self));
    __Pyx_XGOTREF(__pyx_v_5scipy_7spatial_5qhull__active_qhull);
    __Pyx_DECREF(__pyx_v_5scipy_7spatial_5qhull__active_qhull);
    __Pyx_GIVEREF(((PyObject *)__pyx_v_self));
    __pyx_v_5scipy_7spatial_5qhull__active_qhull = ((PyObject *)__pyx_v_self);

    
    {
        #ifdef WITH_THREAD
        PyThreadState *_save = NULL;
        #endif
        Py_UNBLOCK_THREADS
         {

          
          __pyx_v_exitcode = qh_new_qhull(__pyx_v_dim, __pyx_v_numpoints, ((realT *)__pyx_v_points->data), 0, __pyx_v_options_p, NULL, stderr);
        }

        
         {
          Py_BLOCK_THREADS
        }
    }

    
    __pyx_t_1 = (__pyx_v_exitcode != 0);
    if (__pyx_t_1) {

      
      __pyx_t_6 = __Pyx_GetName(__pyx_m, __pyx_n_s__QhullError); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 234; __pyx_clineno = __LINE__; goto __pyx_L13;}
      __Pyx_GOTREF(__pyx_t_6);
      __pyx_t_2 = PyObject_Call(__pyx_t_6, ((PyObject *)__pyx_k_tuple_14), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 234; __pyx_clineno = __LINE__; goto __pyx_L13;}
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      __Pyx_Raise(__pyx_t_2, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 234; __pyx_clineno = __LINE__; goto __pyx_L13;}
      goto __pyx_L19;
    }
    __pyx_L19:;

    
    {
        #ifdef WITH_THREAD
        PyThreadState *_save = NULL;
        #endif
        Py_UNBLOCK_THREADS
         {

          
          qh_triangulate();
        }

        
         {
          Py_BLOCK_THREADS
        }
    }

    
    if (qh_qh->SCALElast) {

      
      __pyx_t_13 = (qh_qh->last_high - qh_qh->last_low);
      if (unlikely(__pyx_t_13 == 0)) {
        PyErr_Format(PyExc_ZeroDivisionError, "float division");
        {__pyx_filename = __pyx_f[0]; __pyx_lineno = 240; __pyx_clineno = __LINE__; goto __pyx_L13;}
      }

      
      __pyx_v_self->paraboloid_scale = (qh_qh->last_newhigh / __pyx_t_13);

      
      __pyx_v_self->paraboloid_shift = ((-qh_qh->last_low) * __pyx_v_self->paraboloid_scale);
      goto __pyx_L23;
    }
     {

      
      __pyx_v_self->paraboloid_scale = 1.0;

      
      __pyx_v_self->paraboloid_shift = 0.0;
    }
    __pyx_L23:;
  }

  
   {
    int __pyx_why;
    PyObject *__pyx_exc_type, *__pyx_exc_value, *__pyx_exc_tb;
    int __pyx_exc_lineno;
    __pyx_exc_type = 0; __pyx_exc_value = 0; __pyx_exc_tb = 0; __pyx_exc_lineno = 0;
    __pyx_why = 0; goto __pyx_L14;
    __pyx_L13: {
      __pyx_why = 4;
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_ErrFetch(&__pyx_exc_type, &__pyx_exc_value, &__pyx_exc_tb);
      __pyx_exc_lineno = __pyx_lineno;
      goto __pyx_L14;
    }
    __pyx_L14:;
    __pyx_t_2 = __Pyx_GetName(__pyx_m, __pyx_n_s___qhull_lock); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 247; __pyx_clineno = __LINE__; goto __pyx_L24_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_6 = PyObject_GetAttr(__pyx_t_2, __pyx_n_s__release); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 247; __pyx_clineno = __LINE__; goto __pyx_L24_error;}
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = PyObject_Call(__pyx_t_6, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 247; __pyx_clineno = __LINE__; goto __pyx_L24_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    goto __pyx_L25;
    __pyx_L24_error:;
    if (__pyx_why == 4) {
      Py_XDECREF(__pyx_exc_type);
      Py_XDECREF(__pyx_exc_value);
      Py_XDECREF(__pyx_exc_tb);
    }
    goto __pyx_L1_error;
    __pyx_L25:;
    switch (__pyx_why) {
      case 4: {
        __Pyx_ErrRestore(__pyx_exc_type, __pyx_exc_value, __pyx_exc_tb);
        __pyx_lineno = __pyx_exc_lineno;
        __pyx_exc_type = 0;
        __pyx_exc_value = 0;
        __pyx_exc_tb = 0;
        goto __pyx_L1_error;
      }
    }
  }

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_6);
  { PyObject *__pyx_type, *__pyx_value, *__pyx_tb;
    __Pyx_ErrFetch(&__pyx_type, &__pyx_value, &__pyx_tb);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_points.rcbuffer->pybuffer);
  __Pyx_ErrRestore(__pyx_type, __pyx_value, __pyx_tb);}
  __Pyx_AddTraceback("scipy.spatial.qhull._Qhull.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  goto __pyx_L2;
  __pyx_L0:;
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_points.rcbuffer->pybuffer);
  __pyx_L2:;
  __Pyx_XDECREF(__pyx_v_bad_opts);
  __Pyx_XDECREF(__pyx_v_bad_opt);
  __Pyx_XDECREF((PyObject *)__pyx_v_points);
  __Pyx_XDECREF(__pyx_v_options);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_6_Qhull_3close(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused); 
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_6_Qhull_3close(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("close (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_6_Qhull_2close(((struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_6_Qhull_2close(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_t_3;
  int __pyx_t_4;
  int __pyx_t_5;
  int __pyx_t_6;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("close", 0);

  
  __pyx_t_1 = __Pyx_GetName(__pyx_m, __pyx_n_s___qhull_lock); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 250; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__acquire); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 250; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 250; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  
   {

    
    __pyx_t_3 = (__pyx_v_5scipy_7spatial_5qhull__active_qhull == ((PyObject *)__pyx_v_self));
    if (!__pyx_t_3) {
      __pyx_t_4 = (__pyx_v_self->_saved_qh != NULL);
      __pyx_t_5 = __pyx_t_4;
    } else {
      __pyx_t_5 = __pyx_t_3;
    }
    if (__pyx_t_5) {

      
      __pyx_t_6 = __pyx_f_5scipy_7spatial_5qhull_6_Qhull__uninit(__pyx_v_self); if (unlikely(__pyx_t_6 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 253; __pyx_clineno = __LINE__; goto __pyx_L4;}
      goto __pyx_L6;
    }
    __pyx_L6:;
  }

  
   {
    int __pyx_why;
    PyObject *__pyx_exc_type, *__pyx_exc_value, *__pyx_exc_tb;
    int __pyx_exc_lineno;
    __pyx_exc_type = 0; __pyx_exc_value = 0; __pyx_exc_tb = 0; __pyx_exc_lineno = 0;
    __pyx_why = 0; goto __pyx_L5;
    __pyx_L4: {
      __pyx_why = 4;
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
      __Pyx_ErrFetch(&__pyx_exc_type, &__pyx_exc_value, &__pyx_exc_tb);
      __pyx_exc_lineno = __pyx_lineno;
      goto __pyx_L5;
    }
    __pyx_L5:;
    __pyx_t_1 = __Pyx_GetName(__pyx_m, __pyx_n_s___qhull_lock); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 255; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__release); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 255; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 255; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    goto __pyx_L8;
    __pyx_L7_error:;
    if (__pyx_why == 4) {
      Py_XDECREF(__pyx_exc_type);
      Py_XDECREF(__pyx_exc_value);
      Py_XDECREF(__pyx_exc_tb);
    }
    goto __pyx_L1_error;
    __pyx_L8:;
    switch (__pyx_why) {
      case 4: {
        __Pyx_ErrRestore(__pyx_exc_type, __pyx_exc_value, __pyx_exc_tb);
        __pyx_lineno = __pyx_exc_lineno;
        __pyx_exc_type = 0;
        __pyx_exc_value = 0;
        __pyx_exc_tb = 0;
        goto __pyx_L1_error;
      }
    }
  }

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("scipy.spatial.qhull._Qhull.close", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_6_Qhull_5__del__(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused); 
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_6_Qhull_5__del__(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_6_Qhull_4__del__(((struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_6_Qhull_4__del__(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__del__", 0);

  
  __pyx_t_1 = PyObject_GetAttr(((PyObject *)__pyx_v_self), __pyx_n_s__close); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 258; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 258; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("scipy.spatial.qhull._Qhull.__del__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static int __pyx_f_5scipy_7spatial_5qhull_6_Qhull__activate(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("_activate", 0);

  
  __pyx_t_1 = (__pyx_v_5scipy_7spatial_5qhull__active_qhull == ((PyObject *)__pyx_v_self));
  if (__pyx_t_1) {

    
    __pyx_r = 0;
    goto __pyx_L0;
    goto __pyx_L3;
  }

  
  __pyx_t_1 = (__pyx_v_5scipy_7spatial_5qhull__active_qhull != Py_None);
  if (__pyx_t_1) {

    
    __pyx_t_2 = PyObject_GetAttr(__pyx_v_5scipy_7spatial_5qhull__active_qhull, __pyx_n_s___deactivate); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 270; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_3 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 270; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    goto __pyx_L3;
  }
  __pyx_L3:;

  
  #ifndef CYTHON_WITHOUT_ASSERTIONS
  __pyx_t_1 = (__pyx_v_5scipy_7spatial_5qhull__active_qhull == Py_None);
  if (unlikely(!__pyx_t_1)) {
    PyErr_SetNone(PyExc_AssertionError);
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 272; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  #endif

  
  __pyx_t_1 = (__pyx_v_self->_saved_qh == NULL);
  if (__pyx_t_1) {

    
    __pyx_t_3 = PyObject_Call(__pyx_builtin_RuntimeError, ((PyObject *)__pyx_k_tuple_16), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 275; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_Raise(__pyx_t_3, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 275; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    goto __pyx_L4;
  }
  __pyx_L4:;

  
  qh_restore_qhull((&__pyx_v_self->_saved_qh));

  
  __pyx_v_self->_saved_qh = NULL;

  
  __Pyx_INCREF(((PyObject *)__pyx_v_self));
  __Pyx_XGOTREF(__pyx_v_5scipy_7spatial_5qhull__active_qhull);
  __Pyx_DECREF(__pyx_v_5scipy_7spatial_5qhull__active_qhull);
  __Pyx_GIVEREF(((PyObject *)__pyx_v_self));
  __pyx_v_5scipy_7spatial_5qhull__active_qhull = ((PyObject *)__pyx_v_self);

  
  __pyx_r = 0;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("scipy.spatial.qhull._Qhull._activate", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static int __pyx_f_5scipy_7spatial_5qhull_6_Qhull__deactivate(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("_deactivate", 0);

  
  __pyx_t_1 = (__pyx_v_5scipy_7spatial_5qhull__active_qhull != ((PyObject *)__pyx_v_self));
  if (__pyx_t_1) {

    
    __pyx_r = 0;
    goto __pyx_L0;
    goto __pyx_L3;
  }
  __pyx_L3:;

  
  #ifndef CYTHON_WITHOUT_ASSERTIONS
  if (unlikely(!(__pyx_v_self->_saved_qh == NULL))) {
    PyErr_SetNone(PyExc_AssertionError);
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 293; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  #endif

  
  __pyx_v_self->_saved_qh = qh_save_qhull();

  
  __Pyx_INCREF(Py_None);
  __Pyx_XGOTREF(__pyx_v_5scipy_7spatial_5qhull__active_qhull);
  __Pyx_DECREF(__pyx_v_5scipy_7spatial_5qhull__active_qhull);
  __Pyx_GIVEREF(Py_None);
  __pyx_v_5scipy_7spatial_5qhull__active_qhull = Py_None;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("scipy.spatial.qhull._Qhull._deactivate", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static int __pyx_f_5scipy_7spatial_5qhull_6_Qhull__uninit(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *__pyx_v_self) {
  int __pyx_v_curlong;
  int __pyx_v_totlong;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  int __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("_uninit", 0);

  
  __pyx_t_1 = __pyx_f_5scipy_7spatial_5qhull_6_Qhull__activate(__pyx_v_self); if (unlikely(__pyx_t_1 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 305; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  qh_freeqhull(0);

  
  qh_memfreeshort((&__pyx_v_curlong), (&__pyx_v_totlong));

  
  __pyx_t_2 = (__pyx_v_curlong != 0);
  if (!__pyx_t_2) {
    __pyx_t_3 = (__pyx_v_totlong != 0);
    __pyx_t_4 = __pyx_t_3;
  } else {
    __pyx_t_4 = __pyx_t_2;
  }
  if (__pyx_t_4) {

    
    __pyx_t_5 = PyInt_FromLong(__pyx_v_totlong); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_6 = PyInt_FromLong(__pyx_v_curlong); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_7 = PyTuple_New(2); if (unlikely(!__pyx_t_7)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_7);
    PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_5);
    __Pyx_GIVEREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_7, 1, __pyx_t_6);
    __Pyx_GIVEREF(__pyx_t_6);
    __pyx_t_5 = 0;
    __pyx_t_6 = 0;
    __pyx_t_6 = PyNumber_Remainder(((PyObject *)__pyx_kp_s_17), ((PyObject *)__pyx_t_7)); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 311; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(((PyObject *)__pyx_t_6));
    __Pyx_DECREF(((PyObject *)__pyx_t_7)); __pyx_t_7 = 0;
    __pyx_t_7 = PyTuple_New(1); if (unlikely(!__pyx_t_7)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 310; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_7);
    PyTuple_SET_ITEM(__pyx_t_7, 0, ((PyObject *)__pyx_t_6));
    __Pyx_GIVEREF(((PyObject *)__pyx_t_6));
    __pyx_t_6 = 0;
    __pyx_t_6 = PyObject_Call(__pyx_builtin_RuntimeError, ((PyObject *)__pyx_t_7), NULL); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 310; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(((PyObject *)__pyx_t_7)); __pyx_t_7 = 0;
    __Pyx_Raise(__pyx_t_6, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 310; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    goto __pyx_L3;
  }
  __pyx_L3:;

  
  __Pyx_INCREF(Py_None);
  __Pyx_XGOTREF(__pyx_v_5scipy_7spatial_5qhull__active_qhull);
  __Pyx_DECREF(__pyx_v_5scipy_7spatial_5qhull__active_qhull);
  __Pyx_GIVEREF(Py_None);
  __pyx_v_5scipy_7spatial_5qhull__active_qhull = Py_None;

  
  __pyx_v_self->_saved_qh = NULL;

  
  __pyx_r = 0;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_AddTraceback("scipy.spatial.qhull._Qhull._uninit", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_6_Qhull_7add_points(PyObject *__pyx_v_self, PyObject *__pyx_v_points); 
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_6_Qhull_7add_points(PyObject *__pyx_v_self, PyObject *__pyx_v_points) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("add_points (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_6_Qhull_6add_points(((struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *)__pyx_v_self), ((PyObject *)__pyx_v_points));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_6_Qhull_6add_points(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *__pyx_v_self, PyObject *__pyx_v_points) {
  PyObject *__pyx_v_n = NULL;
  PyObject *__pyx_v_n_new = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  Py_ssize_t __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_t_6;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("add_points", 0);

  
  __pyx_t_1 = PyObject_Length(__pyx_v_points); if (unlikely(__pyx_t_1 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 318; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_2 = PyInt_FromSsize_t(__pyx_t_1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 318; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_v_n = __pyx_t_2;
  __pyx_t_2 = 0;

  
  __pyx_t_3 = (__pyx_v_self->_dirty_points == Py_None);
  if (__pyx_t_3) {

    
    if (__pyx_v_self->_is_delaunay) {

      
      __pyx_t_2 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 322; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_4 = PyObject_GetAttr(__pyx_t_2, __pyx_n_s__empty); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 322; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_2 = PyInt_FromLong((__pyx_v_self->_ndim + 1)); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 322; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_5 = PyList_New(2); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 322; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_INCREF(__pyx_v_n);
      PyList_SET_ITEM(__pyx_t_5, 0, __pyx_v_n);
      __Pyx_GIVEREF(__pyx_v_n);
      PyList_SET_ITEM(__pyx_t_5, 1, __pyx_t_2);
      __Pyx_GIVEREF(__pyx_t_2);
      __pyx_t_2 = 0;
      __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 322; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      PyTuple_SET_ITEM(__pyx_t_2, 0, ((PyObject *)__pyx_t_5));
      __Pyx_GIVEREF(((PyObject *)__pyx_t_5));
      __Pyx_INCREF(((PyObject *)((PyObject*)(&PyFloat_Type))));
      PyTuple_SET_ITEM(__pyx_t_2, 1, ((PyObject *)((PyObject*)(&PyFloat_Type))));
      __Pyx_GIVEREF(((PyObject *)((PyObject*)(&PyFloat_Type))));
      __pyx_t_5 = 0;
      __pyx_t_5 = PyObject_Call(__pyx_t_4, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 322; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
      __Pyx_GIVEREF(__pyx_t_5);
      __Pyx_GOTREF(__pyx_v_self->_dirty_points);
      __Pyx_DECREF(__pyx_v_self->_dirty_points);
      __pyx_v_self->_dirty_points = __pyx_t_5;
      __pyx_t_5 = 0;
      goto __pyx_L4;
    }
     {

      
      __pyx_t_5 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 324; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_2 = PyObject_GetAttr(__pyx_t_5, __pyx_n_s__empty); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 324; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_5 = PyInt_FromLong(__pyx_v_self->_ndim); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 324; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_4 = PyList_New(2); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 324; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_INCREF(__pyx_v_n);
      PyList_SET_ITEM(__pyx_t_4, 0, __pyx_v_n);
      __Pyx_GIVEREF(__pyx_v_n);
      PyList_SET_ITEM(__pyx_t_4, 1, __pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_5);
      __pyx_t_5 = 0;
      __pyx_t_5 = PyTuple_New(2); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 324; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      PyTuple_SET_ITEM(__pyx_t_5, 0, ((PyObject *)__pyx_t_4));
      __Pyx_GIVEREF(((PyObject *)__pyx_t_4));
      __Pyx_INCREF(((PyObject *)((PyObject*)(&PyFloat_Type))));
      PyTuple_SET_ITEM(__pyx_t_5, 1, ((PyObject *)((PyObject*)(&PyFloat_Type))));
      __Pyx_GIVEREF(((PyObject *)((PyObject*)(&PyFloat_Type))));
      __pyx_t_4 = 0;
      __pyx_t_4 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_t_5), NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 324; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_DECREF(((PyObject *)__pyx_t_5)); __pyx_t_5 = 0;
      __Pyx_GIVEREF(__pyx_t_4);
      __Pyx_GOTREF(__pyx_v_self->_dirty_points);
      __Pyx_DECREF(__pyx_v_self->_dirty_points);
      __pyx_v_self->_dirty_points = __pyx_t_4;
      __pyx_t_4 = 0;
    }
    __pyx_L4:;
    goto __pyx_L3;
  }
   {

    
    __pyx_t_4 = PyInt_FromLong(__pyx_v_self->_n_dirty_points); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 326; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyNumber_Add(__pyx_t_4, __pyx_v_n); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 326; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = PyObject_GetAttr(__pyx_v_self->_dirty_points, __pyx_n_s__shape); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 326; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_2 = __Pyx_GetItemInt(__pyx_t_4, 0, sizeof(long), PyInt_FromLong); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 326; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = PyObject_RichCompare(__pyx_t_5, __pyx_t_2, Py_GT); __Pyx_XGOTREF(__pyx_t_4); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 326; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_3 = __Pyx_PyObject_IsTrue(__pyx_t_4); if (unlikely(__pyx_t_3 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 326; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    if (__pyx_t_3) {

      
      __pyx_t_4 = PyObject_GetAttr(__pyx_v_self->_dirty_points, __pyx_n_s__shape); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 327; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_2 = __Pyx_GetItemInt(__pyx_t_4, 0, sizeof(long), PyInt_FromLong); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 327; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_4 = PyNumber_Multiply(__pyx_int_3, __pyx_t_2); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 327; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_2 = PyNumber_FloorDivide(__pyx_t_4, __pyx_int_2); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 327; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_4 = PyNumber_Add(__pyx_t_2, __pyx_v_n); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 327; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_2 = PyNumber_Add(__pyx_t_4, __pyx_int_1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 327; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_v_n_new = __pyx_t_2;
      __pyx_t_2 = 0;

      
      __pyx_t_2 = PyObject_GetAttr(__pyx_v_self->_dirty_points, __pyx_n_s__resize); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 328; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_4 = PyObject_GetAttr(__pyx_v_self->_dirty_points, __pyx_n_s__shape); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 328; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_5 = __Pyx_GetItemInt(__pyx_t_4, 1, sizeof(long), PyInt_FromLong); if (!__pyx_t_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 328; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_4 = PyTuple_New(2); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 328; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_INCREF(__pyx_v_n_new);
      PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_v_n_new);
      __Pyx_GIVEREF(__pyx_v_n_new);
      PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_5);
      __pyx_t_5 = 0;
      __pyx_t_5 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_t_4), NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 328; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_DECREF(((PyObject *)__pyx_t_4)); __pyx_t_4 = 0;
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      goto __pyx_L5;
    }
    __pyx_L5:;
  }
  __pyx_L3:;

  
  __pyx_t_5 = PyInt_FromLong(__pyx_v_self->_n_dirty_points); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 330; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_4 = PyInt_FromLong(__pyx_v_self->_n_dirty_points); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 330; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_2 = PyNumber_Add(__pyx_t_4, __pyx_v_n); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 330; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = PySlice_New(__pyx_t_5, __pyx_t_2, Py_None); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 330; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyInt_FromLong(__pyx_v_self->_ndim); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 330; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_5 = PySlice_New(Py_None, __pyx_t_2, Py_None); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 330; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 330; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  if (PyObject_SetItem(__pyx_v_self->_dirty_points, ((PyObject *)__pyx_t_2), __pyx_v_points) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 330; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;

  
  __pyx_t_2 = PyInt_FromLong(__pyx_v_self->_n_dirty_points); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 331; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_5 = PyNumber_InPlaceAdd(__pyx_t_2, __pyx_v_n); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 331; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_6 = __Pyx_PyInt_AsInt(__pyx_t_5); if (unlikely((__pyx_t_6 == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 331; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_v_self->_n_dirty_points = __pyx_t_6;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("scipy.spatial.qhull._Qhull.add_points", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_n);
  __Pyx_XDECREF(__pyx_v_n_new);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_6_Qhull_9flush(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused); 
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_6_Qhull_9flush(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("flush (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_6_Qhull_8flush(((struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_6_Qhull_8flush(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *__pyx_v_self) {
  PyArrayObject *__pyx_v_d = 0;
  CYTHON_UNUSED int __pyx_v_j;
  int __pyx_v_n;
  int __pyx_v_m;
  int __pyx_v_ndim;
  facetT *__pyx_v_facet;
  realT *__pyx_v_p;
  realT __pyx_v_bestdist;
  boolT __pyx_v_isoutside;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_d;
  __Pyx_Buffer __pyx_pybuffer_d;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyArrayObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  int __pyx_t_9;
  int __pyx_t_10;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("flush", 0);
  __pyx_pybuffer_d.pybuffer.buf = NULL;
  __pyx_pybuffer_d.refcount = 0;
  __pyx_pybuffernd_d.data = NULL;
  __pyx_pybuffernd_d.rcbuffer = &__pyx_pybuffer_d;

  
  __pyx_t_1 = (__pyx_v_self->_dirty_points == Py_None);
  if (__pyx_t_1) {

    
    __Pyx_XDECREF(__pyx_r);
    __pyx_t_2 = __Pyx_PyBool_FromLong(0); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 342; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_r = __pyx_t_2;
    __pyx_t_2 = 0;
    goto __pyx_L0;
    goto __pyx_L3;
  }
  __pyx_L3:;

  
  if (!(likely(((__pyx_v_self->_dirty_points) == Py_None) || likely(__Pyx_TypeTest(__pyx_v_self->_dirty_points, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 344; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_3 = ((PyArrayObject *)__pyx_v_self->_dirty_points);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_d.rcbuffer->pybuffer);
    __pyx_t_4 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_d.rcbuffer->pybuffer, (PyObject*)__pyx_t_3, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack);
    if (unlikely(__pyx_t_4 < 0)) {
      PyErr_Fetch(&__pyx_t_5, &__pyx_t_6, &__pyx_t_7);
      if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_d.rcbuffer->pybuffer, (PyObject*)__pyx_v_d, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack) == -1)) {
        Py_XDECREF(__pyx_t_5); Py_XDECREF(__pyx_t_6); Py_XDECREF(__pyx_t_7);
        __Pyx_RaiseBufferFallbackError();
      } else {
        PyErr_Restore(__pyx_t_5, __pyx_t_6, __pyx_t_7);
      }
    }
    __pyx_pybuffernd_d.diminfo[0].strides = __pyx_pybuffernd_d.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_d.diminfo[0].shape = __pyx_pybuffernd_d.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_d.diminfo[1].strides = __pyx_pybuffernd_d.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_d.diminfo[1].shape = __pyx_pybuffernd_d.rcbuffer->pybuffer.shape[1];
    if (unlikely(__pyx_t_4 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 344; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_3 = 0;
  __Pyx_INCREF(__pyx_v_self->_dirty_points);
  __pyx_v_d = ((PyArrayObject *)__pyx_v_self->_dirty_points);

  
  __pyx_v_n = __pyx_v_self->_n_dirty_points;

  
  __pyx_t_2 = PyObject_GetAttr(__pyx_v_self->_dirty_points, __pyx_n_s__shape); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 346; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_8 = __Pyx_GetItemInt(__pyx_t_2, 1, sizeof(long), PyInt_FromLong); if (!__pyx_t_8) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 346; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_8);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_AsInt(__pyx_t_8); if (unlikely((__pyx_t_4 == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 346; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
  __pyx_v_m = __pyx_t_4;

  
  __pyx_v_ndim = __pyx_v_self->_ndim;

  
  __pyx_t_8 = __Pyx_GetName(__pyx_m, __pyx_n_s___qhull_lock); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 349; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_8);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_8, __pyx_n_s__acquire); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 349; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
  __pyx_t_8 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 349; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_8);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;

  
   {

    
    __pyx_t_4 = __pyx_f_5scipy_7spatial_5qhull_6_Qhull__activate(__pyx_v_self); if (unlikely(__pyx_t_4 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 351; __pyx_clineno = __LINE__; goto __pyx_L5;}

    
    __pyx_v_p = ((realT *)__pyx_v_d->data);

    
    {
        #ifdef WITH_THREAD
        PyThreadState *_save = NULL;
        #endif
        Py_UNBLOCK_THREADS
         {

          
          if (__pyx_v_self->_is_delaunay) {

            
            qh_setdelaunay((__pyx_v_ndim + 1), __pyx_v_n, __pyx_v_p);
            goto __pyx_L10;
          }
          __pyx_L10:;

          
          __pyx_t_4 = __pyx_v_n;
          for (__pyx_t_9 = 0; __pyx_t_9 < __pyx_t_4; __pyx_t_9+=1) {
            __pyx_v_j = __pyx_t_9;

            
            __pyx_v_facet = qh_findbestfacet(__pyx_v_p, (!qh_ALL), (&__pyx_v_bestdist), (&__pyx_v_isoutside));

            
            __pyx_v_p = (__pyx_v_p + __pyx_v_m);

            
            if (__pyx_v_isoutside) {

              
              __pyx_t_1 = (!qh_addpoint(__pyx_v_p, __pyx_v_facet, 0));
              if (__pyx_t_1) {

                
                goto __pyx_L12_break;
                goto __pyx_L14;
              }
              __pyx_L14:;
              goto __pyx_L13;
            }
            __pyx_L13:;
          }
          __pyx_L12_break:;

          
          qh_check_maxout();

          
          qh_qh->hasTriangulation = 0;

          
          qh_triangulate();
        }

        
         {
          Py_BLOCK_THREADS
        }
    }
  }

  
   {
    int __pyx_why;
    PyObject *__pyx_exc_type, *__pyx_exc_value, *__pyx_exc_tb;
    int __pyx_exc_lineno;
    __pyx_exc_type = 0; __pyx_exc_value = 0; __pyx_exc_tb = 0; __pyx_exc_lineno = 0;
    __pyx_why = 0; goto __pyx_L6;
    __pyx_L5: {
      __pyx_why = 4;
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_XDECREF(__pyx_t_8); __pyx_t_8 = 0;
      __Pyx_ErrFetch(&__pyx_exc_type, &__pyx_exc_value, &__pyx_exc_tb);
      __pyx_exc_lineno = __pyx_lineno;
      goto __pyx_L6;
    }
    __pyx_L6:;
    __pyx_t_8 = __Pyx_GetName(__pyx_m, __pyx_n_s___qhull_lock); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 372; __pyx_clineno = __LINE__; goto __pyx_L15_error;}
    __Pyx_GOTREF(__pyx_t_8);
    __pyx_t_2 = PyObject_GetAttr(__pyx_t_8, __pyx_n_s__release); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 372; __pyx_clineno = __LINE__; goto __pyx_L15_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    __pyx_t_8 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 372; __pyx_clineno = __LINE__; goto __pyx_L15_error;}
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    goto __pyx_L16;
    __pyx_L15_error:;
    if (__pyx_why == 4) {
      Py_XDECREF(__pyx_exc_type);
      Py_XDECREF(__pyx_exc_value);
      Py_XDECREF(__pyx_exc_tb);
    }
    goto __pyx_L1_error;
    __pyx_L16:;
    switch (__pyx_why) {
      case 4: {
        __Pyx_ErrRestore(__pyx_exc_type, __pyx_exc_value, __pyx_exc_tb);
        __pyx_lineno = __pyx_exc_lineno;
        __pyx_exc_type = 0;
        __pyx_exc_value = 0;
        __pyx_exc_tb = 0;
        goto __pyx_L1_error;
      }
    }
  }

  
  if (unlikely(((PyObject *)__pyx_v_self->_point_arrays) == Py_None)) {
    PyErr_Format(PyExc_AttributeError, "'NoneType' object has no attribute '%s'", "append");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 375; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_8 = PyInt_FromLong(__pyx_v_ndim); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 375; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_8);
  __pyx_t_2 = PySlice_New(Py_None, __pyx_t_8, Py_None); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 375; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
  __pyx_t_8 = PyTuple_New(2); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 375; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_8);
  __Pyx_INCREF(__pyx_k_slice_18);
  PyTuple_SET_ITEM(__pyx_t_8, 0, __pyx_k_slice_18);
  __Pyx_GIVEREF(__pyx_k_slice_18);
  PyTuple_SET_ITEM(__pyx_t_8, 1, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_GetItem(__pyx_v_self->_dirty_points, ((PyObject *)__pyx_t_8)); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 375; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(((PyObject *)__pyx_t_8)); __pyx_t_8 = 0;
  __pyx_t_10 = PyList_Append(__pyx_v_self->_point_arrays, __pyx_t_2); if (unlikely(__pyx_t_10 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 375; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->_dirty_points);
  __Pyx_DECREF(__pyx_v_self->_dirty_points);
  __pyx_v_self->_dirty_points = Py_None;

  
  __pyx_v_self->_n_dirty_points = 0;

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = __Pyx_PyBool_FromLong(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 379; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_8);
  { PyObject *__pyx_type, *__pyx_value, *__pyx_tb;
    __Pyx_ErrFetch(&__pyx_type, &__pyx_value, &__pyx_tb);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_d.rcbuffer->pybuffer);
  __Pyx_ErrRestore(__pyx_type, __pyx_value, __pyx_tb);}
  __Pyx_AddTraceback("scipy.spatial.qhull._Qhull.flush", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  goto __pyx_L2;
  __pyx_L0:;
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_d.rcbuffer->pybuffer);
  __pyx_L2:;
  __Pyx_XDECREF((PyObject *)__pyx_v_d);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_6_Qhull_11get_arrays(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused); 
static char __pyx_doc_5scipy_7spatial_5qhull_6_Qhull_10get_arrays[] = "\n        Return arrays currently in Qhull.\n\n        Returns\n        -------\n        points\n        vertices : array of int, shape (nfacets, ndim+1)\n            Indices of coordinates of vertices forming the simplical facets\n        neighbors : array of int, shape (nfacets, ndim)\n            Indices of neighboring facets.  The kth neighbor is opposite\n            the kth vertex, and the first neighbor is the horizon facet\n            for the first vertex. Facets extending to infinity are denoted\n            with index -1.\n        equations\n        ";
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_6_Qhull_11get_arrays(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("get_arrays (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_6_Qhull_10get_arrays(((struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_6_Qhull_10get_arrays(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *__pyx_v_self) {
  facetT *__pyx_v_facet;
  facetT *__pyx_v_neighbor;
  vertexT *__pyx_v_vertex;
  int __pyx_v_i;
  int __pyx_v_j;
  int __pyx_v_point;
  int __pyx_v_error_non_simplical;
  PyArrayObject *__pyx_v_vertices = 0;
  PyArrayObject *__pyx_v_neighbors = 0;
  PyArrayObject *__pyx_v_equations = 0;
  PyArrayObject *__pyx_v_id_map = 0;
  int __pyx_v_ndim;
  PyObject *__pyx_v_points = NULL;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_equations;
  __Pyx_Buffer __pyx_pybuffer_equations;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_id_map;
  __Pyx_Buffer __pyx_pybuffer_id_map;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_neighbors;
  __Pyx_Buffer __pyx_pybuffer_neighbors;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_vertices;
  __Pyx_Buffer __pyx_pybuffer_vertices;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyArrayObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  PyObject *__pyx_t_10 = NULL;
  int __pyx_t_11;
  int __pyx_t_12;
  unsigned int __pyx_t_13;
  PyArrayObject *__pyx_t_14 = NULL;
  PyArrayObject *__pyx_t_15 = NULL;
  PyArrayObject *__pyx_t_16 = NULL;
  long __pyx_t_17;
  int __pyx_t_18;
  int __pyx_t_19;
  unsigned int __pyx_t_20;
  int __pyx_t_21;
  int __pyx_t_22;
  int __pyx_t_23;
  int __pyx_t_24;
  Py_ssize_t __pyx_t_25;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("get_arrays", 0);
  __pyx_pybuffer_vertices.pybuffer.buf = NULL;
  __pyx_pybuffer_vertices.refcount = 0;
  __pyx_pybuffernd_vertices.data = NULL;
  __pyx_pybuffernd_vertices.rcbuffer = &__pyx_pybuffer_vertices;
  __pyx_pybuffer_neighbors.pybuffer.buf = NULL;
  __pyx_pybuffer_neighbors.refcount = 0;
  __pyx_pybuffernd_neighbors.data = NULL;
  __pyx_pybuffernd_neighbors.rcbuffer = &__pyx_pybuffer_neighbors;
  __pyx_pybuffer_equations.pybuffer.buf = NULL;
  __pyx_pybuffer_equations.refcount = 0;
  __pyx_pybuffernd_equations.data = NULL;
  __pyx_pybuffernd_equations.rcbuffer = &__pyx_pybuffer_equations;
  __pyx_pybuffer_id_map.pybuffer.buf = NULL;
  __pyx_pybuffer_id_map.refcount = 0;
  __pyx_pybuffernd_id_map.data = NULL;
  __pyx_pybuffernd_id_map.rcbuffer = &__pyx_pybuffer_id_map;

  
  __pyx_v_ndim = __pyx_v_self->_ndim;

  
  __pyx_t_1 = __Pyx_GetName(__pyx_m, __pyx_n_s___qhull_lock); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 412; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__acquire); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 412; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 412; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  
   {

    
    __pyx_t_3 = __pyx_f_5scipy_7spatial_5qhull_6_Qhull__activate(__pyx_v_self); if (unlikely(__pyx_t_3 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 414; __pyx_clineno = __LINE__; goto __pyx_L4;}

    
    __pyx_t_1 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 416; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__empty); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 416; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyLong_FromUnsignedLong(qh_qh->facet_id); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 416; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 416; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_1);
    __Pyx_GIVEREF(__pyx_t_1);
    __pyx_t_1 = 0;
    __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 416; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_1);
    PyTuple_SET_ITEM(__pyx_t_1, 0, ((PyObject *)__pyx_t_4));
    __Pyx_GIVEREF(((PyObject *)__pyx_t_4));
    __pyx_t_4 = 0;
    __pyx_t_4 = PyDict_New(); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 416; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(((PyObject *)__pyx_t_4));
    __pyx_t_5 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 416; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_6 = PyObject_GetAttr(__pyx_t_5, __pyx_n_s__intc); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 416; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    if (PyDict_SetItem(__pyx_t_4, ((PyObject *)__pyx_n_s__dtype), __pyx_t_6) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 416; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_6 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_t_1), ((PyObject *)__pyx_t_4)); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 416; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;
    __Pyx_DECREF(((PyObject *)__pyx_t_4)); __pyx_t_4 = 0;
    if (!(likely(((__pyx_t_6) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_6, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 416; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __pyx_t_7 = ((PyArrayObject *)__pyx_t_6);
    {
      __Pyx_BufFmt_StackElem __pyx_stack[1];
      __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_id_map.rcbuffer->pybuffer);
      __pyx_t_3 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_id_map.rcbuffer->pybuffer, (PyObject*)__pyx_t_7, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 1, 0, __pyx_stack);
      if (unlikely(__pyx_t_3 < 0)) {
        PyErr_Fetch(&__pyx_t_8, &__pyx_t_9, &__pyx_t_10);
        if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_id_map.rcbuffer->pybuffer, (PyObject*)__pyx_v_id_map, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 1, 0, __pyx_stack) == -1)) {
          Py_XDECREF(__pyx_t_8); Py_XDECREF(__pyx_t_9); Py_XDECREF(__pyx_t_10);
          __Pyx_RaiseBufferFallbackError();
        } else {
          PyErr_Restore(__pyx_t_8, __pyx_t_9, __pyx_t_10);
        }
      }
      __pyx_pybuffernd_id_map.diminfo[0].strides = __pyx_pybuffernd_id_map.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_id_map.diminfo[0].shape = __pyx_pybuffernd_id_map.rcbuffer->pybuffer.shape[0];
      if (unlikely(__pyx_t_3 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 416; __pyx_clineno = __LINE__; goto __pyx_L4;}
    }
    __pyx_t_7 = 0;
    __pyx_v_id_map = ((PyArrayObject *)__pyx_t_6);
    __pyx_t_6 = 0;

    
    __pyx_t_6 = PyObject_GetAttr(((PyObject *)__pyx_v_id_map), __pyx_n_s__fill); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 417; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_4 = PyObject_Call(__pyx_t_6, ((PyObject *)__pyx_k_tuple_19), NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 417; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

    
    __pyx_v_facet = qh_qh->facet_list;

    
    __pyx_v_j = 0;

    
    while (1) {
      if ((__pyx_v_facet != 0)) {
        __pyx_t_11 = (__pyx_v_facet->next != 0);
      } else {
        __pyx_t_11 = (__pyx_v_facet != 0);
      }
      if (!__pyx_t_11) break;

      
      if (__pyx_v_facet->simplicial) {
        __pyx_t_11 = (!__pyx_v_facet->upperdelaunay);
        __pyx_t_12 = __pyx_t_11;
      } else {
        __pyx_t_12 = __pyx_v_facet->simplicial;
      }
      if (__pyx_t_12) {

        
        __pyx_t_13 = __pyx_v_facet->id;
        *__Pyx_BufPtrStrided1d(npy_int *, __pyx_pybuffernd_id_map.rcbuffer->pybuffer.buf, __pyx_t_13, __pyx_pybuffernd_id_map.diminfo[0].strides) = __pyx_v_j;

        
        __pyx_v_j = (__pyx_v_j + 1);
        goto __pyx_L8;
      }
      __pyx_L8:;

      
      __pyx_v_facet = __pyx_v_facet->next;
    }

    
    __pyx_t_4 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 429; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_6 = PyObject_GetAttr(__pyx_t_4, __pyx_n_s__zeros); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 429; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = PyInt_FromLong(__pyx_v_j); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 429; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_1 = PyInt_FromLong((__pyx_v_ndim + 1)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 429; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 429; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_t_1);
    __Pyx_GIVEREF(__pyx_t_1);
    __pyx_t_4 = 0;
    __pyx_t_1 = 0;
    __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 429; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_1);
    PyTuple_SET_ITEM(__pyx_t_1, 0, ((PyObject *)__pyx_t_2));
    __Pyx_GIVEREF(((PyObject *)__pyx_t_2));
    __pyx_t_2 = 0;
    __pyx_t_2 = PyDict_New(); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 429; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(((PyObject *)__pyx_t_2));
    __pyx_t_4 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 429; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyObject_GetAttr(__pyx_t_4, __pyx_n_s__intc); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 429; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    if (PyDict_SetItem(__pyx_t_2, ((PyObject *)__pyx_n_s__dtype), __pyx_t_5) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 429; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_5 = PyObject_Call(__pyx_t_6, ((PyObject *)__pyx_t_1), ((PyObject *)__pyx_t_2)); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 429; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;
    __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
    if (!(likely(((__pyx_t_5) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_5, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 429; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __pyx_t_14 = ((PyArrayObject *)__pyx_t_5);
    {
      __Pyx_BufFmt_StackElem __pyx_stack[1];
      __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer);
      __pyx_t_3 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer, (PyObject*)__pyx_t_14, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 2, 0, __pyx_stack);
      if (unlikely(__pyx_t_3 < 0)) {
        PyErr_Fetch(&__pyx_t_10, &__pyx_t_9, &__pyx_t_8);
        if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer, (PyObject*)__pyx_v_vertices, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 2, 0, __pyx_stack) == -1)) {
          Py_XDECREF(__pyx_t_10); Py_XDECREF(__pyx_t_9); Py_XDECREF(__pyx_t_8);
          __Pyx_RaiseBufferFallbackError();
        } else {
          PyErr_Restore(__pyx_t_10, __pyx_t_9, __pyx_t_8);
        }
      }
      __pyx_pybuffernd_vertices.diminfo[0].strides = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_vertices.diminfo[0].shape = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_vertices.diminfo[1].strides = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_vertices.diminfo[1].shape = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.shape[1];
      if (unlikely(__pyx_t_3 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 429; __pyx_clineno = __LINE__; goto __pyx_L4;}
    }
    __pyx_t_14 = 0;
    __pyx_v_vertices = ((PyArrayObject *)__pyx_t_5);
    __pyx_t_5 = 0;

    
    __pyx_t_5 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 430; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_2 = PyObject_GetAttr(__pyx_t_5, __pyx_n_s__zeros); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 430; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_5 = PyInt_FromLong(__pyx_v_j); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 430; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_1 = PyInt_FromLong((__pyx_v_ndim + 1)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 430; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_6 = PyTuple_New(2); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 430; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_6);
    PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_5);
    __Pyx_GIVEREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_1);
    __Pyx_GIVEREF(__pyx_t_1);
    __pyx_t_5 = 0;
    __pyx_t_1 = 0;
    __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 430; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_1);
    PyTuple_SET_ITEM(__pyx_t_1, 0, ((PyObject *)__pyx_t_6));
    __Pyx_GIVEREF(((PyObject *)__pyx_t_6));
    __pyx_t_6 = 0;
    __pyx_t_6 = PyDict_New(); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 430; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(((PyObject *)__pyx_t_6));
    __pyx_t_5 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 430; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_4 = PyObject_GetAttr(__pyx_t_5, __pyx_n_s__intc); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 430; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    if (PyDict_SetItem(__pyx_t_6, ((PyObject *)__pyx_n_s__dtype), __pyx_t_4) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 430; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_t_1), ((PyObject *)__pyx_t_6)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 430; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;
    __Pyx_DECREF(((PyObject *)__pyx_t_6)); __pyx_t_6 = 0;
    if (!(likely(((__pyx_t_4) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_4, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 430; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __pyx_t_15 = ((PyArrayObject *)__pyx_t_4);
    {
      __Pyx_BufFmt_StackElem __pyx_stack[1];
      __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_neighbors.rcbuffer->pybuffer);
      __pyx_t_3 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_neighbors.rcbuffer->pybuffer, (PyObject*)__pyx_t_15, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 2, 0, __pyx_stack);
      if (unlikely(__pyx_t_3 < 0)) {
        PyErr_Fetch(&__pyx_t_8, &__pyx_t_9, &__pyx_t_10);
        if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_neighbors.rcbuffer->pybuffer, (PyObject*)__pyx_v_neighbors, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 2, 0, __pyx_stack) == -1)) {
          Py_XDECREF(__pyx_t_8); Py_XDECREF(__pyx_t_9); Py_XDECREF(__pyx_t_10);
          __Pyx_RaiseBufferFallbackError();
        } else {
          PyErr_Restore(__pyx_t_8, __pyx_t_9, __pyx_t_10);
        }
      }
      __pyx_pybuffernd_neighbors.diminfo[0].strides = __pyx_pybuffernd_neighbors.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_neighbors.diminfo[0].shape = __pyx_pybuffernd_neighbors.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_neighbors.diminfo[1].strides = __pyx_pybuffernd_neighbors.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_neighbors.diminfo[1].shape = __pyx_pybuffernd_neighbors.rcbuffer->pybuffer.shape[1];
      if (unlikely(__pyx_t_3 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 430; __pyx_clineno = __LINE__; goto __pyx_L4;}
    }
    __pyx_t_15 = 0;
    __pyx_v_neighbors = ((PyArrayObject *)__pyx_t_4);
    __pyx_t_4 = 0;

    
    __pyx_t_4 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 431; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_6 = PyObject_GetAttr(__pyx_t_4, __pyx_n_s__zeros); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 431; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = PyInt_FromLong(__pyx_v_j); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 431; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_1 = PyInt_FromLong((__pyx_v_ndim + 2)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 431; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 431; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_t_1);
    __Pyx_GIVEREF(__pyx_t_1);
    __pyx_t_4 = 0;
    __pyx_t_1 = 0;
    __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 431; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_1);
    PyTuple_SET_ITEM(__pyx_t_1, 0, ((PyObject *)__pyx_t_2));
    __Pyx_GIVEREF(((PyObject *)__pyx_t_2));
    __pyx_t_2 = 0;
    __pyx_t_2 = PyDict_New(); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 431; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(((PyObject *)__pyx_t_2));
    __pyx_t_4 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 431; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyObject_GetAttr(__pyx_t_4, __pyx_n_s__double); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 431; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    if (PyDict_SetItem(__pyx_t_2, ((PyObject *)__pyx_n_s__dtype), __pyx_t_5) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 431; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_5 = PyObject_Call(__pyx_t_6, ((PyObject *)__pyx_t_1), ((PyObject *)__pyx_t_2)); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 431; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;
    __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
    if (!(likely(((__pyx_t_5) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_5, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 431; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __pyx_t_16 = ((PyArrayObject *)__pyx_t_5);
    {
      __Pyx_BufFmt_StackElem __pyx_stack[1];
      __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_equations.rcbuffer->pybuffer);
      __pyx_t_3 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_equations.rcbuffer->pybuffer, (PyObject*)__pyx_t_16, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 2, 0, __pyx_stack);
      if (unlikely(__pyx_t_3 < 0)) {
        PyErr_Fetch(&__pyx_t_10, &__pyx_t_9, &__pyx_t_8);
        if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_equations.rcbuffer->pybuffer, (PyObject*)__pyx_v_equations, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 2, 0, __pyx_stack) == -1)) {
          Py_XDECREF(__pyx_t_10); Py_XDECREF(__pyx_t_9); Py_XDECREF(__pyx_t_8);
          __Pyx_RaiseBufferFallbackError();
        } else {
          PyErr_Restore(__pyx_t_10, __pyx_t_9, __pyx_t_8);
        }
      }
      __pyx_pybuffernd_equations.diminfo[0].strides = __pyx_pybuffernd_equations.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_equations.diminfo[0].shape = __pyx_pybuffernd_equations.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_equations.diminfo[1].strides = __pyx_pybuffernd_equations.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_equations.diminfo[1].shape = __pyx_pybuffernd_equations.rcbuffer->pybuffer.shape[1];
      if (unlikely(__pyx_t_3 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 431; __pyx_clineno = __LINE__; goto __pyx_L4;}
    }
    __pyx_t_16 = 0;
    __pyx_v_equations = ((PyArrayObject *)__pyx_t_5);
    __pyx_t_5 = 0;

    
    __pyx_v_error_non_simplical = 0;

    
    {
        #ifdef WITH_THREAD
        PyThreadState *_save = NULL;
        #endif
        Py_UNBLOCK_THREADS
         {

          
          __pyx_v_facet = qh_qh->facet_list;

          
          __pyx_v_j = 0;

          
          while (1) {
            if ((__pyx_v_facet != 0)) {
              __pyx_t_12 = (__pyx_v_facet->next != 0);
            } else {
              __pyx_t_12 = (__pyx_v_facet != 0);
            }
            if (!__pyx_t_12) break;

            
            __pyx_t_12 = (!__pyx_v_facet->simplicial);
            if (__pyx_t_12) {

              
              __pyx_v_error_non_simplical = 1;

              
              goto __pyx_L13_break;
              goto __pyx_L14;
            }
            __pyx_L14:;

            
            if (__pyx_v_facet->upperdelaunay) {

              
              __pyx_v_facet = __pyx_v_facet->next;

              
              goto __pyx_L12_continue;
              goto __pyx_L15;
            }
            __pyx_L15:;

            
            __pyx_t_17 = (__pyx_v_ndim + 1);
            for (__pyx_t_3 = 0; __pyx_t_3 < __pyx_t_17; __pyx_t_3+=1) {
              __pyx_v_i = __pyx_t_3;

              
              __pyx_v_vertex = ((vertexT *)(__pyx_v_facet->vertices->e[__pyx_v_i]).p);

              
              __pyx_v_point = qh_pointid(__pyx_v_vertex->point);

              
              __pyx_t_18 = __pyx_v_j;
              __pyx_t_19 = __pyx_v_i;
              if (__pyx_t_18 < 0) __pyx_t_18 += __pyx_pybuffernd_vertices.diminfo[0].shape;
              if (__pyx_t_19 < 0) __pyx_t_19 += __pyx_pybuffernd_vertices.diminfo[1].shape;
              *__Pyx_BufPtrStrided2d(npy_int *, __pyx_pybuffernd_vertices.rcbuffer->pybuffer.buf, __pyx_t_18, __pyx_pybuffernd_vertices.diminfo[0].strides, __pyx_t_19, __pyx_pybuffernd_vertices.diminfo[1].strides) = __pyx_v_point;
            }

            
            __pyx_t_17 = (__pyx_v_ndim + 1);
            for (__pyx_t_3 = 0; __pyx_t_3 < __pyx_t_17; __pyx_t_3+=1) {
              __pyx_v_i = __pyx_t_3;

              
              __pyx_v_neighbor = ((facetT *)(__pyx_v_facet->neighbors->e[__pyx_v_i]).p);

              
              __pyx_t_20 = __pyx_v_neighbor->id;
              __pyx_t_21 = __pyx_v_j;
              __pyx_t_22 = __pyx_v_i;
              if (__pyx_t_21 < 0) __pyx_t_21 += __pyx_pybuffernd_neighbors.diminfo[0].shape;
              if (__pyx_t_22 < 0) __pyx_t_22 += __pyx_pybuffernd_neighbors.diminfo[1].shape;
              *__Pyx_BufPtrStrided2d(npy_int *, __pyx_pybuffernd_neighbors.rcbuffer->pybuffer.buf, __pyx_t_21, __pyx_pybuffernd_neighbors.diminfo[0].strides, __pyx_t_22, __pyx_pybuffernd_neighbors.diminfo[1].strides) = (*__Pyx_BufPtrStrided1d(npy_int *, __pyx_pybuffernd_id_map.rcbuffer->pybuffer.buf, __pyx_t_20, __pyx_pybuffernd_id_map.diminfo[0].strides));
            }

            
            __pyx_t_17 = (__pyx_v_ndim + 1);
            for (__pyx_t_3 = 0; __pyx_t_3 < __pyx_t_17; __pyx_t_3+=1) {
              __pyx_v_i = __pyx_t_3;

              
              __pyx_t_23 = __pyx_v_j;
              __pyx_t_24 = __pyx_v_i;
              if (__pyx_t_23 < 0) __pyx_t_23 += __pyx_pybuffernd_equations.diminfo[0].shape;
              if (__pyx_t_24 < 0) __pyx_t_24 += __pyx_pybuffernd_equations.diminfo[1].shape;
              *__Pyx_BufPtrStrided2d(__pyx_t_5numpy_double_t *, __pyx_pybuffernd_equations.rcbuffer->pybuffer.buf, __pyx_t_23, __pyx_pybuffernd_equations.diminfo[0].strides, __pyx_t_24, __pyx_pybuffernd_equations.diminfo[1].strides) = (__pyx_v_facet->normal[__pyx_v_i]);
            }

            
            __pyx_t_3 = __pyx_v_j;
            __pyx_t_17 = (__pyx_v_ndim + 1);
            if (__pyx_t_3 < 0) __pyx_t_3 += __pyx_pybuffernd_equations.diminfo[0].shape;
            if (__pyx_t_17 < 0) __pyx_t_17 += __pyx_pybuffernd_equations.diminfo[1].shape;
            *__Pyx_BufPtrStrided2d(__pyx_t_5numpy_double_t *, __pyx_pybuffernd_equations.rcbuffer->pybuffer.buf, __pyx_t_3, __pyx_pybuffernd_equations.diminfo[0].strides, __pyx_t_17, __pyx_pybuffernd_equations.diminfo[1].strides) = __pyx_v_facet->offset;

            
            __pyx_v_j = (__pyx_v_j + 1);

            
            __pyx_v_facet = __pyx_v_facet->next;
            __pyx_L12_continue:;
          }
          __pyx_L13_break:;
        }

        
         {
          Py_BLOCK_THREADS
        }
    }

    
    if (__pyx_v_error_non_simplical) {

      
      __pyx_t_5 = __Pyx_GetName(__pyx_m, __pyx_n_s__QhullError); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 468; __pyx_clineno = __LINE__; goto __pyx_L4;}
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_2 = PyObject_Call(__pyx_t_5, ((PyObject *)__pyx_k_tuple_21), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 468; __pyx_clineno = __LINE__; goto __pyx_L4;}
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_Raise(__pyx_t_2, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 468; __pyx_clineno = __LINE__; goto __pyx_L4;}
      goto __pyx_L22;
    }
    __pyx_L22:;

    
    __pyx_t_2 = ((PyObject *)__pyx_v_self->_point_arrays);
    __Pyx_INCREF(__pyx_t_2);
    if (unlikely(__pyx_t_2 == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 470; __pyx_clineno = __LINE__; goto __pyx_L4;}
    }
    __pyx_t_25 = PyList_GET_SIZE(__pyx_t_2); if (unlikely(__pyx_t_25 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 470; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_12 = (__pyx_t_25 == 1);
    if (__pyx_t_12) {

      
      if (unlikely(((PyObject *)__pyx_v_self->_point_arrays) == Py_None)) {
        PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
        {__pyx_filename = __pyx_f[0]; __pyx_lineno = 471; __pyx_clineno = __LINE__; goto __pyx_L4;}
      }
      __Pyx_INCREF(PyList_GET_ITEM(__pyx_v_self->_point_arrays, 0));
      __pyx_v_points = PyList_GET_ITEM(__pyx_v_self->_point_arrays, 0);
      goto __pyx_L23;
    }
     {

      
      __pyx_t_2 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 473; __pyx_clineno = __LINE__; goto __pyx_L4;}
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_5 = PyObject_GetAttr(__pyx_t_2, __pyx_n_s__vstack); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 473; __pyx_clineno = __LINE__; goto __pyx_L4;}
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 473; __pyx_clineno = __LINE__; goto __pyx_L4;}
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_INCREF(((PyObject *)__pyx_v_self->_point_arrays));
      PyTuple_SET_ITEM(__pyx_t_2, 0, ((PyObject *)__pyx_v_self->_point_arrays));
      __Pyx_GIVEREF(((PyObject *)__pyx_v_self->_point_arrays));
      __pyx_t_1 = PyObject_Call(__pyx_t_5, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 473; __pyx_clineno = __LINE__; goto __pyx_L4;}
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
      __pyx_v_points = __pyx_t_1;
      __pyx_t_1 = 0;
    }
    __pyx_L23:;

    
    __Pyx_XDECREF(__pyx_r);
    __pyx_t_1 = PyTuple_New(4); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 475; __pyx_clineno = __LINE__; goto __pyx_L4;}
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(__pyx_v_points);
    PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_points);
    __Pyx_GIVEREF(__pyx_v_points);
    __Pyx_INCREF(((PyObject *)__pyx_v_vertices));
    PyTuple_SET_ITEM(__pyx_t_1, 1, ((PyObject *)__pyx_v_vertices));
    __Pyx_GIVEREF(((PyObject *)__pyx_v_vertices));
    __Pyx_INCREF(((PyObject *)__pyx_v_neighbors));
    PyTuple_SET_ITEM(__pyx_t_1, 2, ((PyObject *)__pyx_v_neighbors));
    __Pyx_GIVEREF(((PyObject *)__pyx_v_neighbors));
    __Pyx_INCREF(((PyObject *)__pyx_v_equations));
    PyTuple_SET_ITEM(__pyx_t_1, 3, ((PyObject *)__pyx_v_equations));
    __Pyx_GIVEREF(((PyObject *)__pyx_v_equations));
    __pyx_r = ((PyObject *)__pyx_t_1);
    __pyx_t_1 = 0;
    goto __pyx_L3;
  }

  
   {
    int __pyx_why;
    PyObject *__pyx_exc_type, *__pyx_exc_value, *__pyx_exc_tb;
    int __pyx_exc_lineno;
    __pyx_exc_type = 0; __pyx_exc_value = 0; __pyx_exc_tb = 0; __pyx_exc_lineno = 0;
    __pyx_why = 0; goto __pyx_L5;
    __pyx_L3: __pyx_exc_type = 0; __pyx_exc_value = 0; __pyx_exc_tb = 0; __pyx_exc_lineno = 0;
    __pyx_why = 3; goto __pyx_L5;
    __pyx_L4: {
      __pyx_why = 4;
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
      __Pyx_ErrFetch(&__pyx_exc_type, &__pyx_exc_value, &__pyx_exc_tb);
      __pyx_exc_lineno = __pyx_lineno;
      goto __pyx_L5;
    }
    __pyx_L5:;
    __pyx_t_1 = __Pyx_GetName(__pyx_m, __pyx_n_s___qhull_lock); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 477; __pyx_clineno = __LINE__; goto __pyx_L24_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__release); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 477; __pyx_clineno = __LINE__; goto __pyx_L24_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 477; __pyx_clineno = __LINE__; goto __pyx_L24_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    goto __pyx_L25;
    __pyx_L24_error:;
    if (__pyx_why == 4) {
      Py_XDECREF(__pyx_exc_type);
      Py_XDECREF(__pyx_exc_value);
      Py_XDECREF(__pyx_exc_tb);
    }
    goto __pyx_L1_error;
    __pyx_L25:;
    switch (__pyx_why) {
      case 3: goto __pyx_L0;
      case 4: {
        __Pyx_ErrRestore(__pyx_exc_type, __pyx_exc_value, __pyx_exc_tb);
        __pyx_lineno = __pyx_exc_lineno;
        __pyx_exc_type = 0;
        __pyx_exc_value = 0;
        __pyx_exc_tb = 0;
        goto __pyx_L1_error;
      }
    }
  }

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  { PyObject *__pyx_type, *__pyx_value, *__pyx_tb;
    __Pyx_ErrFetch(&__pyx_type, &__pyx_value, &__pyx_tb);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_equations.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_id_map.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_neighbors.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer);
  __Pyx_ErrRestore(__pyx_type, __pyx_value, __pyx_tb);}
  __Pyx_AddTraceback("scipy.spatial.qhull._Qhull.get_arrays", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  goto __pyx_L2;
  __pyx_L0:;
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_equations.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_id_map.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_neighbors.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer);
  __pyx_L2:;
  __Pyx_XDECREF((PyObject *)__pyx_v_vertices);
  __Pyx_XDECREF((PyObject *)__pyx_v_neighbors);
  __Pyx_XDECREF((PyObject *)__pyx_v_equations);
  __Pyx_XDECREF((PyObject *)__pyx_v_id_map);
  __Pyx_XDECREF(__pyx_v_points);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_1_get_barycentric_transforms(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static char __pyx_doc_5scipy_7spatial_5qhull__get_barycentric_transforms[] = "\n    Compute barycentric affine coordinate transformations for given\n    simplices.\n\n    Returns\n    -------\n    Tinvs : array, shape (nsimplex, ndim+1, ndim)\n        Barycentric transforms for each simplex.\n\n        Tinvs[i,:ndim,:ndim] contains inverse of the matrix ``T``,\n        and Tinvs[i,ndim,:] contains the vector ``r_n`` (see below).\n\n    Notes\n    -----\n    Barycentric transform from ``x`` to ``c`` is defined by::\n\n        T c = x - r_n\n\n    where the ``r_1, ..., r_n`` are the vertices of the simplex.\n    The matrix ``T`` is defined by the condition::\n\n        T e_j = r_j - r_n\n\n    where ``e_j`` is the unit axis vector, e.g, ``e_2 = [0,1,0,0,...]``\n    This implies that ``T_ij = (r_j - r_n)_i``.\n\n    For the barycentric transforms, we need to compute the inverse\n    matrix ``T^-1`` and store the vectors ``r_n`` for each vertex.\n    These are stacked into the `Tinvs` returned.\n\n    ";
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_1_get_barycentric_transforms = {__Pyx_NAMESTR("_get_barycentric_transforms"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_1_get_barycentric_transforms, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(__pyx_doc_5scipy_7spatial_5qhull__get_barycentric_transforms)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_1_get_barycentric_transforms(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyArrayObject *__pyx_v_points = 0;
  PyArrayObject *__pyx_v_vertices = 0;
  double __pyx_v_eps;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("_get_barycentric_transforms (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s__points,&__pyx_n_s__vertices,&__pyx_n_s__eps,0};
    PyObject* values[3] = {0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__points)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__vertices)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_get_barycentric_transforms", 1, 3, 3, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 488; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
        case  2:
        if (likely((values[2] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__eps)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_get_barycentric_transforms", 1, 3, 3, 2); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 488; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "_get_barycentric_transforms") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 488; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 3) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
    }
    __pyx_v_points = ((PyArrayObject *)values[0]);
    __pyx_v_vertices = ((PyArrayObject *)values[1]);
    __pyx_v_eps = __pyx_PyFloat_AsDouble(values[2]); if (unlikely((__pyx_v_eps == (double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 490; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("_get_barycentric_transforms", 1, 3, 3, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 488; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("scipy.spatial.qhull._get_barycentric_transforms", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_points), __pyx_ptype_5numpy_ndarray, 1, "points", 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 488; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_vertices), __pyx_ptype_5numpy_ndarray, 1, "vertices", 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 489; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull__get_barycentric_transforms(__pyx_self, __pyx_v_points, __pyx_v_vertices, __pyx_v_eps);
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull__get_barycentric_transforms(CYTHON_UNUSED PyObject *__pyx_self, PyArrayObject *__pyx_v_points, PyArrayObject *__pyx_v_vertices, double __pyx_v_eps) {
  PyArrayObject *__pyx_v_T = 0;
  PyArrayObject *__pyx_v_Tinvs = 0;
  int __pyx_v_isimplex;
  int __pyx_v_i;
  int __pyx_v_j;
  int __pyx_v_n;
  int __pyx_v_nrhs;
  int __pyx_v_lda;
  int __pyx_v_ldb;
  int __pyx_v_info;
  int __pyx_v_ipiv[(NPY_MAXDIMS + 1)];
  int __pyx_v_ndim;
  int __pyx_v_nsimplex;
  double __pyx_v_anorm;
  double __pyx_v_rcond;
  double __pyx_v_nan;
  double __pyx_v_rcond_limit;
  double __pyx_v_work[(4 * NPY_MAXDIMS)];
  int __pyx_v_iwork[NPY_MAXDIMS];
  __Pyx_LocalBuf_ND __pyx_pybuffernd_T;
  __Pyx_Buffer __pyx_pybuffer_T;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_Tinvs;
  __Pyx_Buffer __pyx_pybuffer_Tinvs;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_points;
  __Pyx_Buffer __pyx_pybuffer_points;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_vertices;
  __Pyx_Buffer __pyx_pybuffer_vertices;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  double __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyArrayObject *__pyx_t_7 = NULL;
  int __pyx_t_8;
  PyObject *__pyx_t_9 = NULL;
  PyObject *__pyx_t_10 = NULL;
  PyObject *__pyx_t_11 = NULL;
  PyArrayObject *__pyx_t_12 = NULL;
  int __pyx_t_13;
  int __pyx_t_14;
  int __pyx_t_15;
  int __pyx_t_16;
  int __pyx_t_17;
  npy_int __pyx_t_18;
  int __pyx_t_19;
  int __pyx_t_20;
  int __pyx_t_21;
  int __pyx_t_22;
  int __pyx_t_23;
  int __pyx_t_24;
  int __pyx_t_25;
  int __pyx_t_26;
  npy_int __pyx_t_27;
  int __pyx_t_28;
  int __pyx_t_29;
  int __pyx_t_30;
  int __pyx_t_31;
  int __pyx_t_32;
  int __pyx_t_33;
  int __pyx_t_34;
  int __pyx_t_35;
  long __pyx_t_36;
  int __pyx_t_37;
  int __pyx_t_38;
  int __pyx_t_39;
  int __pyx_t_40;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("_get_barycentric_transforms", 0);
  __pyx_pybuffer_T.pybuffer.buf = NULL;
  __pyx_pybuffer_T.refcount = 0;
  __pyx_pybuffernd_T.data = NULL;
  __pyx_pybuffernd_T.rcbuffer = &__pyx_pybuffer_T;
  __pyx_pybuffer_Tinvs.pybuffer.buf = NULL;
  __pyx_pybuffer_Tinvs.refcount = 0;
  __pyx_pybuffernd_Tinvs.data = NULL;
  __pyx_pybuffernd_Tinvs.rcbuffer = &__pyx_pybuffer_Tinvs;
  __pyx_pybuffer_points.pybuffer.buf = NULL;
  __pyx_pybuffer_points.refcount = 0;
  __pyx_pybuffernd_points.data = NULL;
  __pyx_pybuffernd_points.rcbuffer = &__pyx_pybuffer_points;
  __pyx_pybuffer_vertices.pybuffer.buf = NULL;
  __pyx_pybuffer_vertices.refcount = 0;
  __pyx_pybuffernd_vertices.data = NULL;
  __pyx_pybuffernd_vertices.rcbuffer = &__pyx_pybuffer_vertices;
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_points.rcbuffer->pybuffer, (PyObject*)__pyx_v_points, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack) == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 488; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_pybuffernd_points.diminfo[0].strides = __pyx_pybuffernd_points.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_points.diminfo[0].shape = __pyx_pybuffernd_points.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_points.diminfo[1].strides = __pyx_pybuffernd_points.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_points.diminfo[1].shape = __pyx_pybuffernd_points.rcbuffer->pybuffer.shape[1];
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer, (PyObject*)__pyx_v_vertices, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack) == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 488; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_pybuffernd_vertices.diminfo[0].strides = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_vertices.diminfo[0].shape = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_vertices.diminfo[1].strides = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_vertices.diminfo[1].shape = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.shape[1];

  
  __pyx_t_1 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 540; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__nan); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 540; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_3 = __pyx_PyFloat_AsDouble(__pyx_t_2); if (unlikely((__pyx_t_3 == (double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 540; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_nan = __pyx_t_3;

  
  __pyx_v_ndim = (__pyx_v_points->dimensions[1]);

  
  __pyx_v_nsimplex = (__pyx_v_vertices->dimensions[0]);

  
  __pyx_t_2 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 544; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyObject_GetAttr(__pyx_t_2, __pyx_n_s__zeros); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 544; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyInt_FromLong(__pyx_v_ndim); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 544; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = PyInt_FromLong(__pyx_v_ndim); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 544; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = PyTuple_New(2); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 544; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  __pyx_t_2 = 0;
  __pyx_t_4 = 0;
  __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 544; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_4, 0, ((PyObject *)__pyx_t_5));
  __Pyx_GIVEREF(((PyObject *)__pyx_t_5));
  __pyx_t_5 = 0;
  __pyx_t_5 = PyDict_New(); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 544; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(((PyObject *)__pyx_t_5));
  __pyx_t_2 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 544; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_6 = PyObject_GetAttr(__pyx_t_2, __pyx_n_s__double); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 544; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if (PyDict_SetItem(__pyx_t_5, ((PyObject *)__pyx_n_s__dtype), __pyx_t_6) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 544; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_t_4), ((PyObject *)__pyx_t_5)); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 544; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_4)); __pyx_t_4 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_5)); __pyx_t_5 = 0;
  if (!(likely(((__pyx_t_6) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_6, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 544; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_7 = ((PyArrayObject *)__pyx_t_6);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_T.rcbuffer->pybuffer);
    __pyx_t_8 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_T.rcbuffer->pybuffer, (PyObject*)__pyx_t_7, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 2, 0, __pyx_stack);
    if (unlikely(__pyx_t_8 < 0)) {
      PyErr_Fetch(&__pyx_t_9, &__pyx_t_10, &__pyx_t_11);
      if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_T.rcbuffer->pybuffer, (PyObject*)__pyx_v_T, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 2, 0, __pyx_stack) == -1)) {
        Py_XDECREF(__pyx_t_9); Py_XDECREF(__pyx_t_10); Py_XDECREF(__pyx_t_11);
        __Pyx_RaiseBufferFallbackError();
      } else {
        PyErr_Restore(__pyx_t_9, __pyx_t_10, __pyx_t_11);
      }
    }
    __pyx_pybuffernd_T.diminfo[0].strides = __pyx_pybuffernd_T.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_T.diminfo[0].shape = __pyx_pybuffernd_T.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_T.diminfo[1].strides = __pyx_pybuffernd_T.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_T.diminfo[1].shape = __pyx_pybuffernd_T.rcbuffer->pybuffer.shape[1];
    if (unlikely(__pyx_t_8 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 544; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_7 = 0;
  __pyx_v_T = ((PyArrayObject *)__pyx_t_6);
  __pyx_t_6 = 0;

  
  __pyx_t_6 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 545; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_5 = PyObject_GetAttr(__pyx_t_6, __pyx_n_s__zeros); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 545; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = PyInt_FromLong(__pyx_v_nsimplex); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 545; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_4 = PyInt_FromLong((__pyx_v_ndim + 1)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 545; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_1 = PyInt_FromLong(__pyx_v_ndim); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 545; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyTuple_New(3); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 545; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_6);
  __Pyx_GIVEREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_2, 2, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_6 = 0;
  __pyx_t_4 = 0;
  __pyx_t_1 = 0;
  __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 545; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_1, 0, ((PyObject *)__pyx_t_2));
  __Pyx_GIVEREF(((PyObject *)__pyx_t_2));
  __pyx_t_2 = 0;
  __pyx_t_2 = PyDict_New(); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 545; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(((PyObject *)__pyx_t_2));
  __pyx_t_4 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 545; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_6 = PyObject_GetAttr(__pyx_t_4, __pyx_n_s__double); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 545; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  if (PyDict_SetItem(__pyx_t_2, ((PyObject *)__pyx_n_s__dtype), __pyx_t_6) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 545; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = PyObject_Call(__pyx_t_5, ((PyObject *)__pyx_t_1), ((PyObject *)__pyx_t_2)); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 545; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  if (!(likely(((__pyx_t_6) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_6, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 545; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_12 = ((PyArrayObject *)__pyx_t_6);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_Tinvs.rcbuffer->pybuffer);
    __pyx_t_8 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_Tinvs.rcbuffer->pybuffer, (PyObject*)__pyx_t_12, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 3, 0, __pyx_stack);
    if (unlikely(__pyx_t_8 < 0)) {
      PyErr_Fetch(&__pyx_t_11, &__pyx_t_10, &__pyx_t_9);
      if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_Tinvs.rcbuffer->pybuffer, (PyObject*)__pyx_v_Tinvs, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 3, 0, __pyx_stack) == -1)) {
        Py_XDECREF(__pyx_t_11); Py_XDECREF(__pyx_t_10); Py_XDECREF(__pyx_t_9);
        __Pyx_RaiseBufferFallbackError();
      } else {
        PyErr_Restore(__pyx_t_11, __pyx_t_10, __pyx_t_9);
      }
    }
    __pyx_pybuffernd_Tinvs.diminfo[0].strides = __pyx_pybuffernd_Tinvs.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_Tinvs.diminfo[0].shape = __pyx_pybuffernd_Tinvs.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_Tinvs.diminfo[1].strides = __pyx_pybuffernd_Tinvs.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_Tinvs.diminfo[1].shape = __pyx_pybuffernd_Tinvs.rcbuffer->pybuffer.shape[1]; __pyx_pybuffernd_Tinvs.diminfo[2].strides = __pyx_pybuffernd_Tinvs.rcbuffer->pybuffer.strides[2]; __pyx_pybuffernd_Tinvs.diminfo[2].shape = __pyx_pybuffernd_Tinvs.rcbuffer->pybuffer.shape[2];
    if (unlikely(__pyx_t_8 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 545; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_12 = 0;
  __pyx_v_Tinvs = ((PyArrayObject *)__pyx_t_6);
  __pyx_t_6 = 0;

  
  __pyx_v_rcond_limit = (1000.0 * __pyx_v_eps);

  
  {
      #ifdef WITH_THREAD
      PyThreadState *_save = NULL;
      #endif
      Py_UNBLOCK_THREADS
       {

        
        __pyx_t_8 = __pyx_v_nsimplex;
        for (__pyx_t_13 = 0; __pyx_t_13 < __pyx_t_8; __pyx_t_13+=1) {
          __pyx_v_isimplex = __pyx_t_13;

          
          __pyx_t_14 = __pyx_v_ndim;
          for (__pyx_t_15 = 0; __pyx_t_15 < __pyx_t_14; __pyx_t_15+=1) {
            __pyx_v_i = __pyx_t_15;

            
            __pyx_t_16 = __pyx_v_isimplex;
            __pyx_t_17 = __pyx_v_ndim;
            if (__pyx_t_16 < 0) __pyx_t_16 += __pyx_pybuffernd_vertices.diminfo[0].shape;
            if (__pyx_t_17 < 0) __pyx_t_17 += __pyx_pybuffernd_vertices.diminfo[1].shape;
            __pyx_t_18 = (*__Pyx_BufPtrStrided2d(npy_int *, __pyx_pybuffernd_vertices.rcbuffer->pybuffer.buf, __pyx_t_16, __pyx_pybuffernd_vertices.diminfo[0].strides, __pyx_t_17, __pyx_pybuffernd_vertices.diminfo[1].strides));
            __pyx_t_19 = __pyx_v_i;
            if (__pyx_t_18 < 0) __pyx_t_18 += __pyx_pybuffernd_points.diminfo[0].shape;
            if (__pyx_t_19 < 0) __pyx_t_19 += __pyx_pybuffernd_points.diminfo[1].shape;
            __pyx_t_20 = __pyx_v_isimplex;
            __pyx_t_21 = __pyx_v_ndim;
            __pyx_t_22 = __pyx_v_i;
            if (__pyx_t_20 < 0) __pyx_t_20 += __pyx_pybuffernd_Tinvs.diminfo[0].shape;
            if (__pyx_t_21 < 0) __pyx_t_21 += __pyx_pybuffernd_Tinvs.diminfo[1].shape;
            if (__pyx_t_22 < 0) __pyx_t_22 += __pyx_pybuffernd_Tinvs.diminfo[2].shape;
            *__Pyx_BufPtrStrided3d(__pyx_t_5numpy_double_t *, __pyx_pybuffernd_Tinvs.rcbuffer->pybuffer.buf, __pyx_t_20, __pyx_pybuffernd_Tinvs.diminfo[0].strides, __pyx_t_21, __pyx_pybuffernd_Tinvs.diminfo[1].strides, __pyx_t_22, __pyx_pybuffernd_Tinvs.diminfo[2].strides) = (*__Pyx_BufPtrStrided2d(__pyx_t_5numpy_double_t *, __pyx_pybuffernd_points.rcbuffer->pybuffer.buf, __pyx_t_18, __pyx_pybuffernd_points.diminfo[0].strides, __pyx_t_19, __pyx_pybuffernd_points.diminfo[1].strides));

            
            __pyx_t_23 = __pyx_v_ndim;
            for (__pyx_t_24 = 0; __pyx_t_24 < __pyx_t_23; __pyx_t_24+=1) {
              __pyx_v_j = __pyx_t_24;

              
              __pyx_t_25 = __pyx_v_isimplex;
              __pyx_t_26 = __pyx_v_j;
              if (__pyx_t_25 < 0) __pyx_t_25 += __pyx_pybuffernd_vertices.diminfo[0].shape;
              if (__pyx_t_26 < 0) __pyx_t_26 += __pyx_pybuffernd_vertices.diminfo[1].shape;
              __pyx_t_27 = (*__Pyx_BufPtrStrided2d(npy_int *, __pyx_pybuffernd_vertices.rcbuffer->pybuffer.buf, __pyx_t_25, __pyx_pybuffernd_vertices.diminfo[0].strides, __pyx_t_26, __pyx_pybuffernd_vertices.diminfo[1].strides));
              __pyx_t_28 = __pyx_v_i;
              if (__pyx_t_27 < 0) __pyx_t_27 += __pyx_pybuffernd_points.diminfo[0].shape;
              if (__pyx_t_28 < 0) __pyx_t_28 += __pyx_pybuffernd_points.diminfo[1].shape;

              
              __pyx_t_29 = __pyx_v_isimplex;
              __pyx_t_30 = __pyx_v_ndim;
              __pyx_t_31 = __pyx_v_i;
              if (__pyx_t_29 < 0) __pyx_t_29 += __pyx_pybuffernd_Tinvs.diminfo[0].shape;
              if (__pyx_t_30 < 0) __pyx_t_30 += __pyx_pybuffernd_Tinvs.diminfo[1].shape;
              if (__pyx_t_31 < 0) __pyx_t_31 += __pyx_pybuffernd_Tinvs.diminfo[2].shape;

              
              __pyx_t_32 = __pyx_v_i;
              __pyx_t_33 = __pyx_v_j;
              if (__pyx_t_32 < 0) __pyx_t_32 += __pyx_pybuffernd_T.diminfo[0].shape;
              if (__pyx_t_33 < 0) __pyx_t_33 += __pyx_pybuffernd_T.diminfo[1].shape;
              *__Pyx_BufPtrStrided2d(__pyx_t_5numpy_double_t *, __pyx_pybuffernd_T.rcbuffer->pybuffer.buf, __pyx_t_32, __pyx_pybuffernd_T.diminfo[0].strides, __pyx_t_33, __pyx_pybuffernd_T.diminfo[1].strides) = ((*__Pyx_BufPtrStrided2d(__pyx_t_5numpy_double_t *, __pyx_pybuffernd_points.rcbuffer->pybuffer.buf, __pyx_t_27, __pyx_pybuffernd_points.diminfo[0].strides, __pyx_t_28, __pyx_pybuffernd_points.diminfo[1].strides)) - (*__Pyx_BufPtrStrided3d(__pyx_t_5numpy_double_t *, __pyx_pybuffernd_Tinvs.rcbuffer->pybuffer.buf, __pyx_t_29, __pyx_pybuffernd_Tinvs.diminfo[0].strides, __pyx_t_30, __pyx_pybuffernd_Tinvs.diminfo[1].strides, __pyx_t_31, __pyx_pybuffernd_Tinvs.diminfo[2].strides)));
            }

            
            __pyx_t_23 = __pyx_v_isimplex;
            __pyx_t_24 = __pyx_v_i;
            __pyx_t_34 = __pyx_v_i;
            if (__pyx_t_23 < 0) __pyx_t_23 += __pyx_pybuffernd_Tinvs.diminfo[0].shape;
            if (__pyx_t_24 < 0) __pyx_t_24 += __pyx_pybuffernd_Tinvs.diminfo[1].shape;
            if (__pyx_t_34 < 0) __pyx_t_34 += __pyx_pybuffernd_Tinvs.diminfo[2].shape;
            *__Pyx_BufPtrStrided3d(__pyx_t_5numpy_double_t *, __pyx_pybuffernd_Tinvs.rcbuffer->pybuffer.buf, __pyx_t_23, __pyx_pybuffernd_Tinvs.diminfo[0].strides, __pyx_t_24, __pyx_pybuffernd_Tinvs.diminfo[1].strides, __pyx_t_34, __pyx_pybuffernd_Tinvs.diminfo[2].strides) = 1.0;
          }

          
          __pyx_v_anorm = __pyx_f_5scipy_7spatial_5qhull__matrix_norm1(__pyx_v_ndim, ((double *)__pyx_v_T->data));

          
          __pyx_v_n = __pyx_v_ndim;

          
          __pyx_v_nrhs = __pyx_v_ndim;

          
          __pyx_v_lda = __pyx_v_ndim;

          
          __pyx_v_ldb = __pyx_v_ndim;

          
          qh_dgetrf((&__pyx_v_n), (&__pyx_v_n), ((double *)__pyx_v_T->data), (&__pyx_v_lda), __pyx_v_ipiv, (&__pyx_v_info));

          
          __pyx_t_35 = (__pyx_v_info == 0);
          if (__pyx_t_35) {

            
            qh_dgecon(__pyx_k__1, (&__pyx_v_n), ((double *)__pyx_v_T->data), (&__pyx_v_lda), (&__pyx_v_anorm), (&__pyx_v_rcond), __pyx_v_work, __pyx_v_iwork, (&__pyx_v_info));

            
            __pyx_t_35 = (__pyx_v_rcond < __pyx_v_rcond_limit);
            if (__pyx_t_35) {

              
              __pyx_v_info = 1;
              goto __pyx_L13;
            }
            __pyx_L13:;
            goto __pyx_L12;
          }
          __pyx_L12:;

          
          __pyx_t_35 = (__pyx_v_info == 0);
          if (__pyx_t_35) {

            
            qh_dgetrs(__pyx_k__N, (&__pyx_v_n), (&__pyx_v_nrhs), ((double *)__pyx_v_T->data), (&__pyx_v_lda), __pyx_v_ipiv, (((double *)__pyx_v_Tinvs->data) + ((__pyx_v_ndim * (__pyx_v_ndim + 1)) * __pyx_v_isimplex)), (&__pyx_v_ldb), (&__pyx_v_info));
            goto __pyx_L14;
          }
          __pyx_L14:;

          
          __pyx_t_35 = (__pyx_v_info != 0);
          if (__pyx_t_35) {

            
            __pyx_t_36 = (__pyx_v_ndim + 1);
            for (__pyx_t_14 = 0; __pyx_t_14 < __pyx_t_36; __pyx_t_14+=1) {
              __pyx_v_i = __pyx_t_14;

              
              __pyx_t_15 = __pyx_v_ndim;
              for (__pyx_t_37 = 0; __pyx_t_37 < __pyx_t_15; __pyx_t_37+=1) {
                __pyx_v_j = __pyx_t_37;

                
                __pyx_t_38 = __pyx_v_isimplex;
                __pyx_t_39 = __pyx_v_i;
                __pyx_t_40 = __pyx_v_j;
                if (__pyx_t_38 < 0) __pyx_t_38 += __pyx_pybuffernd_Tinvs.diminfo[0].shape;
                if (__pyx_t_39 < 0) __pyx_t_39 += __pyx_pybuffernd_Tinvs.diminfo[1].shape;
                if (__pyx_t_40 < 0) __pyx_t_40 += __pyx_pybuffernd_Tinvs.diminfo[2].shape;
                *__Pyx_BufPtrStrided3d(__pyx_t_5numpy_double_t *, __pyx_pybuffernd_Tinvs.rcbuffer->pybuffer.buf, __pyx_t_38, __pyx_pybuffernd_Tinvs.diminfo[0].strides, __pyx_t_39, __pyx_pybuffernd_Tinvs.diminfo[1].strides, __pyx_t_40, __pyx_pybuffernd_Tinvs.diminfo[2].strides) = __pyx_v_nan;
              }
            }
            goto __pyx_L15;
          }
          __pyx_L15:;
        }
      }

      
       {
        Py_BLOCK_THREADS
      }
  }

  
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_Tinvs));
  __pyx_r = ((PyObject *)__pyx_v_Tinvs);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  { PyObject *__pyx_type, *__pyx_value, *__pyx_tb;
    __Pyx_ErrFetch(&__pyx_type, &__pyx_value, &__pyx_tb);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_T.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_Tinvs.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_points.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer);
  __Pyx_ErrRestore(__pyx_type, __pyx_value, __pyx_tb);}
  __Pyx_AddTraceback("scipy.spatial.qhull._get_barycentric_transforms", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  goto __pyx_L2;
  __pyx_L0:;
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_T.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_Tinvs.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_points.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer);
  __pyx_L2:;
  __Pyx_XDECREF((PyObject *)__pyx_v_T);
  __Pyx_XDECREF((PyObject *)__pyx_v_Tinvs);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static double __pyx_f_5scipy_7spatial_5qhull__matrix_norm1(int __pyx_v_n, double *__pyx_v_a) {
  double __pyx_v_maxsum;
  double __pyx_v_colsum;
  CYTHON_UNUSED int __pyx_v_i;
  CYTHON_UNUSED int __pyx_v_j;
  double __pyx_r;
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  int __pyx_t_4;
  int __pyx_t_5;

  
  __pyx_v_maxsum = 0.0;

  
  __pyx_t_1 = __pyx_v_n;
  for (__pyx_t_2 = 0; __pyx_t_2 < __pyx_t_1; __pyx_t_2+=1) {
    __pyx_v_j = __pyx_t_2;

    
    __pyx_v_colsum = 0.0;

    
    __pyx_t_3 = __pyx_v_n;
    for (__pyx_t_4 = 0; __pyx_t_4 < __pyx_t_3; __pyx_t_4+=1) {
      __pyx_v_i = __pyx_t_4;

      
      __pyx_v_colsum = (__pyx_v_colsum + fabs((__pyx_v_a[0])));

      
      __pyx_v_a = (__pyx_v_a + 1);
    }

    
    __pyx_t_5 = (__pyx_v_maxsum < __pyx_v_colsum);
    if (__pyx_t_5) {

      
      __pyx_v_maxsum = __pyx_v_colsum;
      goto __pyx_L7;
    }
    __pyx_L7:;
  }

  
  __pyx_r = __pyx_v_maxsum;
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  return __pyx_r;
}



static int __pyx_f_5scipy_7spatial_5qhull__barycentric_inside(int __pyx_v_ndim, double *__pyx_v_transform, double *__pyx_v_x, double *__pyx_v_c, double __pyx_v_eps) {
  int __pyx_v_i;
  int __pyx_v_j;
  int __pyx_r;
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  int __pyx_t_4;
  int __pyx_t_5;
  int __pyx_t_6;
  int __pyx_t_7;

  
  (__pyx_v_c[__pyx_v_ndim]) = 1.0;

  
  __pyx_t_1 = __pyx_v_ndim;
  for (__pyx_t_2 = 0; __pyx_t_2 < __pyx_t_1; __pyx_t_2+=1) {
    __pyx_v_i = __pyx_t_2;

    
    (__pyx_v_c[__pyx_v_i]) = 0.0;

    
    __pyx_t_3 = __pyx_v_ndim;
    for (__pyx_t_4 = 0; __pyx_t_4 < __pyx_t_3; __pyx_t_4+=1) {
      __pyx_v_j = __pyx_t_4;

      
      __pyx_t_5 = __pyx_v_i;
      (__pyx_v_c[__pyx_t_5]) = ((__pyx_v_c[__pyx_t_5]) + ((__pyx_v_transform[((__pyx_v_ndim * __pyx_v_i) + __pyx_v_j)]) * ((__pyx_v_x[__pyx_v_j]) - (__pyx_v_transform[((__pyx_v_ndim * __pyx_v_ndim) + __pyx_v_j)]))));
    }

    
    __pyx_t_3 = __pyx_v_ndim;
    (__pyx_v_c[__pyx_t_3]) = ((__pyx_v_c[__pyx_t_3]) - (__pyx_v_c[__pyx_v_i]));

    
    __pyx_t_6 = ((-__pyx_v_eps) <= (__pyx_v_c[__pyx_v_i]));
    if (__pyx_t_6) {
      __pyx_t_6 = ((__pyx_v_c[__pyx_v_i]) <= (1.0 + __pyx_v_eps));
    }
    __pyx_t_7 = (!__pyx_t_6);
    if (__pyx_t_7) {

      
      __pyx_r = 0;
      goto __pyx_L0;
      goto __pyx_L7;
    }
    __pyx_L7:;
  }

  
  __pyx_t_7 = ((-__pyx_v_eps) <= (__pyx_v_c[__pyx_v_ndim]));
  if (__pyx_t_7) {
    __pyx_t_7 = ((__pyx_v_c[__pyx_v_ndim]) <= (1.0 + __pyx_v_eps));
  }
  __pyx_t_6 = (!__pyx_t_7);
  if (__pyx_t_6) {

    
    __pyx_r = 0;
    goto __pyx_L0;
    goto __pyx_L8;
  }
  __pyx_L8:;

  
  __pyx_r = 1;
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  return __pyx_r;
}



static void __pyx_f_5scipy_7spatial_5qhull__barycentric_coordinate_single(int __pyx_v_ndim, double *__pyx_v_transform, double *__pyx_v_x, double *__pyx_v_c, int __pyx_v_i) {
  int __pyx_v_j;
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  int __pyx_t_4;

  
  __pyx_t_1 = (__pyx_v_i == __pyx_v_ndim);
  if (__pyx_t_1) {

    
    (__pyx_v_c[__pyx_v_ndim]) = 1.0;

    
    __pyx_t_2 = __pyx_v_ndim;
    for (__pyx_t_3 = 0; __pyx_t_3 < __pyx_t_2; __pyx_t_3+=1) {
      __pyx_v_j = __pyx_t_3;

      
      __pyx_t_4 = __pyx_v_ndim;
      (__pyx_v_c[__pyx_t_4]) = ((__pyx_v_c[__pyx_t_4]) - (__pyx_v_c[__pyx_v_j]));
    }
    goto __pyx_L3;
  }
   {

    
    (__pyx_v_c[__pyx_v_i]) = 0.0;

    
    __pyx_t_2 = __pyx_v_ndim;
    for (__pyx_t_3 = 0; __pyx_t_3 < __pyx_t_2; __pyx_t_3+=1) {
      __pyx_v_j = __pyx_t_3;

      
      __pyx_t_4 = __pyx_v_i;
      (__pyx_v_c[__pyx_t_4]) = ((__pyx_v_c[__pyx_t_4]) + ((__pyx_v_transform[((__pyx_v_ndim * __pyx_v_i) + __pyx_v_j)]) * ((__pyx_v_x[__pyx_v_j]) - (__pyx_v_transform[((__pyx_v_ndim * __pyx_v_ndim) + __pyx_v_j)]))));
    }
  }
  __pyx_L3:;

}



static void __pyx_f_5scipy_7spatial_5qhull__barycentric_coordinates(int __pyx_v_ndim, double *__pyx_v_transform, double *__pyx_v_x, double *__pyx_v_c) {
  int __pyx_v_i;
  int __pyx_v_j;
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  int __pyx_t_4;
  int __pyx_t_5;

  
  (__pyx_v_c[__pyx_v_ndim]) = 1.0;

  
  __pyx_t_1 = __pyx_v_ndim;
  for (__pyx_t_2 = 0; __pyx_t_2 < __pyx_t_1; __pyx_t_2+=1) {
    __pyx_v_i = __pyx_t_2;

    
    (__pyx_v_c[__pyx_v_i]) = 0.0;

    
    __pyx_t_3 = __pyx_v_ndim;
    for (__pyx_t_4 = 0; __pyx_t_4 < __pyx_t_3; __pyx_t_4+=1) {
      __pyx_v_j = __pyx_t_4;

      
      __pyx_t_5 = __pyx_v_i;
      (__pyx_v_c[__pyx_t_5]) = ((__pyx_v_c[__pyx_t_5]) + ((__pyx_v_transform[((__pyx_v_ndim * __pyx_v_i) + __pyx_v_j)]) * ((__pyx_v_x[__pyx_v_j]) - (__pyx_v_transform[((__pyx_v_ndim * __pyx_v_ndim) + __pyx_v_j)]))));
    }

    
    __pyx_t_3 = __pyx_v_ndim;
    (__pyx_v_c[__pyx_t_3]) = ((__pyx_v_c[__pyx_t_3]) - (__pyx_v_c[__pyx_v_i]));
  }

}



static void __pyx_f_5scipy_7spatial_5qhull__lift_point(__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *__pyx_v_d, double *__pyx_v_x, double *__pyx_v_z) {
  int __pyx_v_i;
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;

  
  (__pyx_v_z[__pyx_v_d->ndim]) = 0.0;

  
  __pyx_t_1 = __pyx_v_d->ndim;
  for (__pyx_t_2 = 0; __pyx_t_2 < __pyx_t_1; __pyx_t_2+=1) {
    __pyx_v_i = __pyx_t_2;

    
    (__pyx_v_z[__pyx_v_i]) = (__pyx_v_x[__pyx_v_i]);

    
    __pyx_t_3 = __pyx_v_d->ndim;
    (__pyx_v_z[__pyx_t_3]) = ((__pyx_v_z[__pyx_t_3]) + pow((__pyx_v_x[__pyx_v_i]), 2.0));
  }

  
  __pyx_t_1 = __pyx_v_d->ndim;
  (__pyx_v_z[__pyx_t_1]) = ((__pyx_v_z[__pyx_t_1]) * __pyx_v_d->paraboloid_scale);

  
  __pyx_t_1 = __pyx_v_d->ndim;
  (__pyx_v_z[__pyx_t_1]) = ((__pyx_v_z[__pyx_t_1]) + __pyx_v_d->paraboloid_shift);

}



static double __pyx_f_5scipy_7spatial_5qhull__distplane(__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *__pyx_v_d, int __pyx_v_isimplex, double *__pyx_v_point) {
  double __pyx_v_dist;
  int __pyx_v_k;
  double __pyx_r;
  long __pyx_t_1;
  int __pyx_t_2;

  
  __pyx_v_dist = (__pyx_v_d->equations[(((__pyx_v_isimplex * (__pyx_v_d->ndim + 2)) + __pyx_v_d->ndim) + 1)]);

  
  __pyx_t_1 = (__pyx_v_d->ndim + 1);
  for (__pyx_t_2 = 0; __pyx_t_2 < __pyx_t_1; __pyx_t_2+=1) {
    __pyx_v_k = __pyx_t_2;

    
    __pyx_v_dist = (__pyx_v_dist + ((__pyx_v_d->equations[((__pyx_v_isimplex * (__pyx_v_d->ndim + 2)) + __pyx_v_k)]) * (__pyx_v_point[__pyx_v_k])));
  }

  
  __pyx_r = __pyx_v_dist;
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  return __pyx_r;
}



static void __pyx_f_5scipy_7spatial_5qhull__RidgeIter2D_init(__pyx_t_5scipy_7spatial_5qhull_RidgeIter2D_t *__pyx_v_it, __pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *__pyx_v_d, int __pyx_v_vertex) {
  int __pyx_v_k;
  int __pyx_v_ivertex;
  CYTHON_UNUSED int __pyx_v_start;
  int __pyx_t_1;
  int __pyx_t_2;

  
  __pyx_v_start = 0;

  
  __pyx_v_it->info = __pyx_v_d;

  
  __pyx_v_it->vertex = __pyx_v_vertex;

  
  __pyx_v_it->triangle = (__pyx_v_d->vertex_to_simplex[__pyx_v_vertex]);

  
  __pyx_v_it->start_triangle = __pyx_v_it->triangle;

  
  __pyx_v_it->restart = 0;

  
  __pyx_t_1 = (__pyx_v_it->triangle != -1);
  if (__pyx_t_1) {

    
    for (__pyx_t_2 = 0; __pyx_t_2 < 3; __pyx_t_2+=1) {
      __pyx_v_k = __pyx_t_2;

      
      __pyx_v_ivertex = (__pyx_v_it->info->vertices[((__pyx_v_it->triangle * 3) + __pyx_v_k)]);

      
      __pyx_t_1 = (__pyx_v_ivertex != __pyx_v_vertex);
      if (__pyx_t_1) {

        
        __pyx_v_it->vertex2 = __pyx_v_ivertex;

        
        __pyx_v_it->index = __pyx_v_k;

        
        __pyx_v_it->start_index = __pyx_v_k;

        
        goto __pyx_L5_break;
        goto __pyx_L6;
      }
      __pyx_L6:;
    }
    __pyx_L5_break:;
    goto __pyx_L3;
  }
   {

    
    __pyx_v_it->start_index = -1;

    
    __pyx_v_it->index = -1;
  }
  __pyx_L3:;

}



static void __pyx_f_5scipy_7spatial_5qhull__RidgeIter2D_next(__pyx_t_5scipy_7spatial_5qhull_RidgeIter2D_t *__pyx_v_it) {
  int __pyx_v_itri;
  int __pyx_v_k;
  int __pyx_v_ivertex;
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  int __pyx_t_4;

  
  if (__pyx_v_it->restart) {

    
    __pyx_t_1 = (__pyx_v_it->start_index == -1);
    if (__pyx_t_1) {

      
      __pyx_v_it->index = -1;

      
      goto __pyx_L0;
      goto __pyx_L4;
    }
    __pyx_L4:;

    
    __pyx_v_it->triangle = __pyx_v_it->start_triangle;

    
    for (__pyx_t_2 = 0; __pyx_t_2 < 3; __pyx_t_2+=1) {
      __pyx_v_k = __pyx_t_2;

      
      __pyx_v_ivertex = (__pyx_v_it->info->vertices[((__pyx_v_it->triangle * 3) + __pyx_v_k)]);

      
      __pyx_t_1 = (__pyx_v_ivertex != __pyx_v_it->vertex);
      if (__pyx_t_1) {
        __pyx_t_3 = (__pyx_v_k != __pyx_v_it->start_index);
        __pyx_t_4 = __pyx_t_3;
      } else {
        __pyx_t_4 = __pyx_t_1;
      }
      if (__pyx_t_4) {

        
        __pyx_v_it->index = __pyx_v_k;

        
        __pyx_v_it->vertex2 = __pyx_v_ivertex;

        
        goto __pyx_L6_break;
        goto __pyx_L7;
      }
      __pyx_L7:;
    }
    __pyx_L6_break:;

    
    __pyx_v_it->start_index = -1;

    
    __pyx_v_it->restart = 0;

    
    __pyx_t_4 = ((__pyx_v_it->info->neighbors[((__pyx_v_it->triangle * 3) + __pyx_v_it->index)]) == -1);
    if (__pyx_t_4) {

      
      __pyx_v_it->index = -1;

      
      goto __pyx_L0;
      goto __pyx_L8;
    }
     {

      
      __pyx_f_5scipy_7spatial_5qhull__RidgeIter2D_next(__pyx_v_it);

      
      __pyx_t_4 = (__pyx_v_it->index == -1);
      if (__pyx_t_4) {

        
        goto __pyx_L0;
        goto __pyx_L9;
      }
      __pyx_L9:;
    }
    __pyx_L8:;
    goto __pyx_L3;
  }
  __pyx_L3:;

  
  __pyx_v_itri = (__pyx_v_it->info->neighbors[((__pyx_v_it->triangle * 3) + __pyx_v_it->index)]);

  
  __pyx_t_4 = (__pyx_v_itri == -1);
  if (__pyx_t_4) {

    
    for (__pyx_t_2 = 0; __pyx_t_2 < 3; __pyx_t_2+=1) {
      __pyx_v_k = __pyx_t_2;

      
      __pyx_v_ivertex = (__pyx_v_it->info->vertices[((__pyx_v_it->triangle * 3) + __pyx_v_k)]);

      
      __pyx_t_4 = (__pyx_v_ivertex != __pyx_v_it->vertex);
      if (__pyx_t_4) {
        __pyx_t_1 = (__pyx_v_k != __pyx_v_it->index);
        __pyx_t_3 = __pyx_t_1;
      } else {
        __pyx_t_3 = __pyx_t_4;
      }
      if (__pyx_t_3) {

        
        __pyx_v_it->index = __pyx_v_k;

        
        __pyx_v_it->vertex2 = __pyx_v_ivertex;

        
        goto __pyx_L12_break;
        goto __pyx_L13;
      }
      __pyx_L13:;
    }
    __pyx_L12_break:;

    
    __pyx_v_it->restart = 1;

    
    goto __pyx_L0;
    goto __pyx_L10;
  }
  __pyx_L10:;

  
  for (__pyx_t_2 = 0; __pyx_t_2 < 3; __pyx_t_2+=1) {
    __pyx_v_k = __pyx_t_2;

    
    __pyx_v_ivertex = (__pyx_v_it->info->vertices[((__pyx_v_itri * 3) + __pyx_v_k)]);

    
    __pyx_t_3 = ((__pyx_v_it->info->neighbors[((__pyx_v_itri * 3) + __pyx_v_k)]) != __pyx_v_it->triangle);
    if (__pyx_t_3) {

      
      __pyx_t_4 = (__pyx_v_ivertex != __pyx_v_it->vertex);
      __pyx_t_1 = __pyx_t_4;
    } else {
      __pyx_t_1 = __pyx_t_3;
    }
    if (__pyx_t_1) {

      
      __pyx_v_it->index = __pyx_v_k;

      
      __pyx_v_it->vertex2 = __pyx_v_ivertex;

      
      goto __pyx_L15_break;
      goto __pyx_L16;
    }
    __pyx_L16:;
  }
  __pyx_L15_break:;

  
  __pyx_v_it->triangle = __pyx_v_itri;

  
  __pyx_t_1 = (__pyx_v_it->triangle == __pyx_v_it->start_triangle);
  if (__pyx_t_1) {

    
    __pyx_v_it->index = -1;

    
    goto __pyx_L0;
    goto __pyx_L17;
  }
  __pyx_L17:;

  __pyx_L0:;
}


static int __pyx_pw_5scipy_7spatial_5qhull_11RidgeIter2D_1__init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static int __pyx_pw_5scipy_7spatial_5qhull_11RidgeIter2D_1__init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_delaunay = 0;
  PyObject *__pyx_v_ivertex = 0;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__init__ (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s__delaunay,&__pyx_n_s__ivertex,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__delaunay)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__ivertex)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__init__", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 816; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__init__") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 816; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_delaunay = values[0];
    __pyx_v_ivertex = values[1];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__init__", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 816; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("scipy.spatial.qhull.RidgeIter2D.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return -1;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_11RidgeIter2D___init__(((struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D *)__pyx_v_self), __pyx_v_delaunay, __pyx_v_ivertex);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static int __pyx_pf_5scipy_7spatial_5qhull_11RidgeIter2D___init__(struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D *__pyx_v_self, PyObject *__pyx_v_delaunay, PyObject *__pyx_v_ivertex) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_t_3;
  int __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__init__", 0);

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_delaunay, __pyx_n_s__ndim); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 817; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_RichCompare(__pyx_t_1, __pyx_int_2, Py_NE); __Pyx_XGOTREF(__pyx_t_2); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 817; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_3 = __Pyx_PyObject_IsTrue(__pyx_t_2); if (unlikely(__pyx_t_3 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 817; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if (__pyx_t_3) {

    
    __pyx_t_2 = PyObject_Call(__pyx_builtin_ValueError, ((PyObject *)__pyx_k_tuple_23), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 818; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_Raise(__pyx_t_2, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 818; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    goto __pyx_L3;
  }
  __pyx_L3:;

  
  __Pyx_INCREF(__pyx_v_delaunay);
  __Pyx_GIVEREF(__pyx_v_delaunay);
  __Pyx_GOTREF(__pyx_v_self->delaunay);
  __Pyx_DECREF(__pyx_v_self->delaunay);
  __pyx_v_self->delaunay = __pyx_v_delaunay;

  
  __pyx_t_4 = __pyx_f_5scipy_7spatial_5qhull__get_delaunay_info((&__pyx_v_self->info), __pyx_v_delaunay, 0, 1); if (unlikely(__pyx_t_4 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 820; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_t_4 = __Pyx_PyInt_AsInt(__pyx_v_ivertex); if (unlikely((__pyx_t_4 == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 821; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_f_5scipy_7spatial_5qhull__RidgeIter2D_init((&__pyx_v_self->it), (&__pyx_v_self->info), __pyx_t_4);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("scipy.spatial.qhull.RidgeIter2D.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_11RidgeIter2D_3__iter__(PyObject *__pyx_v_self); 
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_11RidgeIter2D_3__iter__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__iter__ (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_11RidgeIter2D_2__iter__(((struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_11RidgeIter2D_2__iter__(struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__iter__", 0);

  
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self));
  __pyx_r = ((PyObject *)__pyx_v_self);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_11RidgeIter2D_5__next__(PyObject *__pyx_v_self); 
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_11RidgeIter2D_5__next__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__next__ (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_11RidgeIter2D_4__next__(((struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_11RidgeIter2D_4__next__(struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D *__pyx_v_self) {
  PyObject *__pyx_v_ret = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__next__", 0);

  
  __pyx_t_1 = (__pyx_v_self->it.index == -1);
  if (__pyx_t_1) {

    
    __pyx_t_2 = PyObject_Call(__pyx_builtin_StopIteration, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 828; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_Raise(__pyx_t_2, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 828; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    goto __pyx_L3;
  }
  __pyx_L3:;

  
  __pyx_t_2 = PyInt_FromLong(__pyx_v_self->it.vertex); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 829; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyInt_FromLong(__pyx_v_self->it.vertex2); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 829; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = PyInt_FromLong(__pyx_v_self->it.index); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 829; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = PyInt_FromLong(__pyx_v_self->it.triangle); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 829; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 829; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_v_ret = __pyx_t_6;
  __pyx_t_6 = 0;

  
  __pyx_f_5scipy_7spatial_5qhull__RidgeIter2D_next((&__pyx_v_self->it));

  
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_ret));
  __pyx_r = ((PyObject *)__pyx_v_ret);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("scipy.spatial.qhull.RidgeIter2D.__next__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_ret);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static int __pyx_f_5scipy_7spatial_5qhull__is_point_fully_outside(__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *__pyx_v_d, double *__pyx_v_x, double __pyx_v_eps) {
  int __pyx_v_i;
  int __pyx_r;
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  int __pyx_t_4;
  int __pyx_t_5;

  
  __pyx_t_1 = __pyx_v_d->ndim;
  for (__pyx_t_2 = 0; __pyx_t_2 < __pyx_t_1; __pyx_t_2+=1) {
    __pyx_v_i = __pyx_t_2;

    
    __pyx_t_3 = ((__pyx_v_x[__pyx_v_i]) < ((__pyx_v_d->min_bound[__pyx_v_i]) - __pyx_v_eps));
    if (!__pyx_t_3) {
      __pyx_t_4 = ((__pyx_v_x[__pyx_v_i]) > ((__pyx_v_d->max_bound[__pyx_v_i]) + __pyx_v_eps));
      __pyx_t_5 = __pyx_t_4;
    } else {
      __pyx_t_5 = __pyx_t_3;
    }
    if (__pyx_t_5) {

      
      __pyx_r = 1;
      goto __pyx_L0;
      goto __pyx_L5;
    }
    __pyx_L5:;
  }

  
  __pyx_r = 0;
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  return __pyx_r;
}



static int __pyx_f_5scipy_7spatial_5qhull__find_simplex_bruteforce(__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *__pyx_v_d, double *__pyx_v_c, double *__pyx_v_x, double __pyx_v_eps, double __pyx_v_eps_broad) {
  int __pyx_v_inside;
  int __pyx_v_isimplex;
  int __pyx_v_k;
  int __pyx_v_m;
  int __pyx_v_ineighbor;
  double *__pyx_v_transform;
  int __pyx_r;
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  long __pyx_t_4;
  int __pyx_t_5;
  long __pyx_t_6;
  int __pyx_t_7;
  int __pyx_t_8;

  
  __pyx_t_1 = __pyx_f_5scipy_7spatial_5qhull__is_point_fully_outside(__pyx_v_d, __pyx_v_x, __pyx_v_eps);
  if (__pyx_t_1) {

    
    __pyx_r = -1;
    goto __pyx_L0;
    goto __pyx_L3;
  }
  __pyx_L3:;

  
  __pyx_t_1 = __pyx_v_d->nsimplex;
  for (__pyx_t_2 = 0; __pyx_t_2 < __pyx_t_1; __pyx_t_2+=1) {
    __pyx_v_isimplex = __pyx_t_2;

    
    __pyx_v_transform = (__pyx_v_d->transform + ((__pyx_v_isimplex * __pyx_v_d->ndim) * (__pyx_v_d->ndim + 1)));

    
    __pyx_t_3 = ((__pyx_v_transform[0]) == (__pyx_v_transform[0]));
    if (__pyx_t_3) {

      
      __pyx_v_inside = __pyx_f_5scipy_7spatial_5qhull__barycentric_inside(__pyx_v_d->ndim, __pyx_v_transform, __pyx_v_x, __pyx_v_c, __pyx_v_eps);

      
      if (__pyx_v_inside) {

        
        __pyx_r = __pyx_v_isimplex;
        goto __pyx_L0;
        goto __pyx_L7;
      }
      __pyx_L7:;
      goto __pyx_L6;
    }
     {

      
      __pyx_t_4 = (__pyx_v_d->ndim + 1);
      for (__pyx_t_5 = 0; __pyx_t_5 < __pyx_t_4; __pyx_t_5+=1) {
        __pyx_v_k = __pyx_t_5;

        
        __pyx_v_ineighbor = (__pyx_v_d->neighbors[(((__pyx_v_d->ndim + 1) * __pyx_v_isimplex) + __pyx_v_k)]);

        
        __pyx_t_3 = (__pyx_v_ineighbor == -1);
        if (__pyx_t_3) {

          
          goto __pyx_L8_continue;
          goto __pyx_L10;
        }
        __pyx_L10:;

        
        __pyx_v_transform = (__pyx_v_d->transform + ((__pyx_v_ineighbor * __pyx_v_d->ndim) * (__pyx_v_d->ndim + 1)));

        
        __pyx_t_3 = ((__pyx_v_transform[0]) != (__pyx_v_transform[0]));
        if (__pyx_t_3) {

          
          goto __pyx_L8_continue;
          goto __pyx_L11;
        }
        __pyx_L11:;

        
        __pyx_f_5scipy_7spatial_5qhull__barycentric_coordinates(__pyx_v_d->ndim, __pyx_v_transform, __pyx_v_x, __pyx_v_c);

        
        __pyx_v_inside = 1;

        
        __pyx_t_6 = (__pyx_v_d->ndim + 1);
        for (__pyx_t_7 = 0; __pyx_t_7 < __pyx_t_6; __pyx_t_7+=1) {
          __pyx_v_m = __pyx_t_7;

          
          __pyx_t_3 = ((__pyx_v_d->neighbors[(((__pyx_v_d->ndim + 1) * __pyx_v_ineighbor) + __pyx_v_m)]) == __pyx_v_isimplex);
          if (__pyx_t_3) {

            
            __pyx_t_3 = ((-__pyx_v_eps_broad) <= (__pyx_v_c[__pyx_v_m]));
            if (__pyx_t_3) {
              __pyx_t_3 = ((__pyx_v_c[__pyx_v_m]) <= (1.0 + __pyx_v_eps));
            }
            __pyx_t_8 = (!__pyx_t_3);
            if (__pyx_t_8) {

              
              __pyx_v_inside = 0;

              
              goto __pyx_L13_break;
              goto __pyx_L15;
            }
            __pyx_L15:;
            goto __pyx_L14;
          }
           {

            
            __pyx_t_8 = ((-__pyx_v_eps) <= (__pyx_v_c[__pyx_v_m]));
            if (__pyx_t_8) {
              __pyx_t_8 = ((__pyx_v_c[__pyx_v_m]) <= (1.0 + __pyx_v_eps));
            }
            __pyx_t_3 = (!__pyx_t_8);
            if (__pyx_t_3) {

              
              __pyx_v_inside = 0;

              
              goto __pyx_L13_break;
              goto __pyx_L16;
            }
            __pyx_L16:;
          }
          __pyx_L14:;
        }
        __pyx_L13_break:;

        
        if (__pyx_v_inside) {

          
          __pyx_r = __pyx_v_ineighbor;
          goto __pyx_L0;
          goto __pyx_L17;
        }
        __pyx_L17:;
        __pyx_L8_continue:;
      }
    }
    __pyx_L6:;
  }

  
  __pyx_r = -1;
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  return __pyx_r;
}



static int __pyx_f_5scipy_7spatial_5qhull__find_simplex_directed(__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *__pyx_v_d, double *__pyx_v_c, double *__pyx_v_x, int *__pyx_v_start, double __pyx_v_eps, double __pyx_v_eps_broad) {
  int __pyx_v_k;
  int __pyx_v_m;
  int __pyx_v_ndim;
  int __pyx_v_inside;
  int __pyx_v_isimplex;
  CYTHON_UNUSED int __pyx_v_cycle_k;
  double *__pyx_v_transform;
  int __pyx_r;
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  long __pyx_t_4;
  int __pyx_t_5;
  long __pyx_t_6;
  int __pyx_t_7;

  
  __pyx_v_ndim = __pyx_v_d->ndim;

  
  __pyx_v_isimplex = (__pyx_v_start[0]);

  
  __pyx_t_1 = (__pyx_v_isimplex < 0);
  if (!__pyx_t_1) {
    __pyx_t_2 = (__pyx_v_isimplex >= __pyx_v_d->nsimplex);
    __pyx_t_3 = __pyx_t_2;
  } else {
    __pyx_t_3 = __pyx_t_1;
  }
  if (__pyx_t_3) {

    
    __pyx_v_isimplex = 0;
    goto __pyx_L3;
  }
  __pyx_L3:;

  
  __pyx_t_4 = (1 + __Pyx_div_long(__pyx_v_d->nsimplex, 4));
  for (__pyx_t_5 = 0; __pyx_t_5 < __pyx_t_4; __pyx_t_5+=1) {
    __pyx_v_cycle_k = __pyx_t_5;

    
    __pyx_t_3 = (__pyx_v_isimplex == -1);
    if (__pyx_t_3) {

      
      goto __pyx_L5_break;
      goto __pyx_L6;
    }
    __pyx_L6:;

    
    __pyx_v_transform = (__pyx_v_d->transform + ((__pyx_v_isimplex * __pyx_v_ndim) * (__pyx_v_ndim + 1)));

    
    __pyx_v_inside = 1;

    
    __pyx_t_6 = (__pyx_v_ndim + 1);
    for (__pyx_t_7 = 0; __pyx_t_7 < __pyx_t_6; __pyx_t_7+=1) {
      __pyx_v_k = __pyx_t_7;

      
      __pyx_f_5scipy_7spatial_5qhull__barycentric_coordinate_single(__pyx_v_ndim, __pyx_v_transform, __pyx_v_x, __pyx_v_c, __pyx_v_k);

      
      __pyx_t_3 = ((__pyx_v_c[__pyx_v_k]) < (-__pyx_v_eps));
      if (__pyx_t_3) {

        
        __pyx_v_m = (__pyx_v_d->neighbors[(((__pyx_v_ndim + 1) * __pyx_v_isimplex) + __pyx_v_k)]);

        
        __pyx_t_3 = (__pyx_v_m == -1);
        if (__pyx_t_3) {

          
          (__pyx_v_start[0]) = __pyx_v_isimplex;

          
          __pyx_r = -1;
          goto __pyx_L0;
          goto __pyx_L10;
        }
        __pyx_L10:;

        
        __pyx_v_isimplex = __pyx_v_m;

        
        __pyx_v_inside = -1;

        
        goto __pyx_L8_break;
        goto __pyx_L9;
      }

      
      __pyx_t_3 = ((__pyx_v_c[__pyx_v_k]) <= (1.0 + __pyx_v_eps));
      if (__pyx_t_3) {
        goto __pyx_L9;
      }
       {

        
        __pyx_v_inside = 0;
      }
      __pyx_L9:;
    }
    __pyx_L8_break:;

    
    switch (__pyx_v_inside) {

      
      case -1:

      
      goto __pyx_L4_continue;
      break;

      
      case 1:

      
      goto __pyx_L5_break;
      break;
      default:

      
      __pyx_v_isimplex = __pyx_f_5scipy_7spatial_5qhull__find_simplex_bruteforce(__pyx_v_d, __pyx_v_c, __pyx_v_x, __pyx_v_eps, __pyx_v_eps_broad);

      
      goto __pyx_L5_break;
      break;
    }
    __pyx_L4_continue:;
  }
   {

    
    __pyx_v_isimplex = __pyx_f_5scipy_7spatial_5qhull__find_simplex_bruteforce(__pyx_v_d, __pyx_v_c, __pyx_v_x, __pyx_v_eps, __pyx_v_eps_broad);
  }
  __pyx_L5_break:;

  
  (__pyx_v_start[0]) = __pyx_v_isimplex;

  
  __pyx_r = __pyx_v_isimplex;
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  return __pyx_r;
}



static int __pyx_f_5scipy_7spatial_5qhull__find_simplex(__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *__pyx_v_d, double *__pyx_v_c, double *__pyx_v_x, int *__pyx_v_start, double __pyx_v_eps, double __pyx_v_eps_broad) {
  int __pyx_v_isimplex;
  int __pyx_v_k;
  int __pyx_v_ineigh;
  int __pyx_v_ndim;
  double __pyx_v_z[(NPY_MAXDIMS + 1)];
  double __pyx_v_best_dist;
  double __pyx_v_dist;
  int __pyx_v_changed;
  int __pyx_r;
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  int __pyx_t_4;
  long __pyx_t_5;

  
  __pyx_t_1 = __pyx_f_5scipy_7spatial_5qhull__is_point_fully_outside(__pyx_v_d, __pyx_v_x, __pyx_v_eps);
  if (__pyx_t_1) {

    
    __pyx_r = -1;
    goto __pyx_L0;
    goto __pyx_L3;
  }
  __pyx_L3:;

  
  __pyx_t_2 = (__pyx_v_d->nsimplex <= 0);
  if (__pyx_t_2) {

    
    __pyx_r = -1;
    goto __pyx_L0;
    goto __pyx_L4;
  }
  __pyx_L4:;

  
  __pyx_v_ndim = __pyx_v_d->ndim;

  
  __pyx_v_isimplex = (__pyx_v_start[0]);

  
  __pyx_t_2 = (__pyx_v_isimplex < 0);
  if (!__pyx_t_2) {
    __pyx_t_3 = (__pyx_v_isimplex >= __pyx_v_d->nsimplex);
    __pyx_t_4 = __pyx_t_3;
  } else {
    __pyx_t_4 = __pyx_t_2;
  }
  if (__pyx_t_4) {

    
    __pyx_v_isimplex = 0;
    goto __pyx_L5;
  }
  __pyx_L5:;

  
  __pyx_f_5scipy_7spatial_5qhull__lift_point(__pyx_v_d, __pyx_v_x, __pyx_v_z);

  
  __pyx_v_best_dist = __pyx_f_5scipy_7spatial_5qhull__distplane(__pyx_v_d, __pyx_v_isimplex, __pyx_v_z);

  
  __pyx_v_changed = 1;

  
  while (1) {
    if (!__pyx_v_changed) break;

    
    __pyx_t_4 = (__pyx_v_best_dist > 0.0);
    if (__pyx_t_4) {

      
      goto __pyx_L7_break;
      goto __pyx_L8;
    }
    __pyx_L8:;

    
    __pyx_v_changed = 0;

    
    __pyx_t_5 = (__pyx_v_ndim + 1);
    for (__pyx_t_1 = 0; __pyx_t_1 < __pyx_t_5; __pyx_t_1+=1) {
      __pyx_v_k = __pyx_t_1;

      
      __pyx_v_ineigh = (__pyx_v_d->neighbors[(((__pyx_v_ndim + 1) * __pyx_v_isimplex) + __pyx_v_k)]);

      
      __pyx_t_4 = (__pyx_v_ineigh == -1);
      if (__pyx_t_4) {

        
        goto __pyx_L9_continue;
        goto __pyx_L11;
      }
      __pyx_L11:;

      
      __pyx_v_dist = __pyx_f_5scipy_7spatial_5qhull__distplane(__pyx_v_d, __pyx_v_ineigh, __pyx_v_z);

      
      __pyx_t_4 = (__pyx_v_dist > (__pyx_v_best_dist + (__pyx_v_eps * (1.0 + fabs(__pyx_v_best_dist)))));
      if (__pyx_t_4) {

        
        __pyx_v_isimplex = __pyx_v_ineigh;

        
        __pyx_v_best_dist = __pyx_v_dist;

        
        __pyx_v_changed = 1;
        goto __pyx_L12;
      }
      __pyx_L12:;
      __pyx_L9_continue:;
    }
  }
  __pyx_L7_break:;

  
  (__pyx_v_start[0]) = __pyx_v_isimplex;

  
  __pyx_r = __pyx_f_5scipy_7spatial_5qhull__find_simplex_directed(__pyx_v_d, __pyx_v_c, __pyx_v_x, __pyx_v_start, __pyx_v_eps, __pyx_v_eps_broad);
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_38__defaults__(CYTHON_UNUSED PyObject *__pyx_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__defaults__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1196; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__Pyx_CyFunction_Defaults(__pyx_defaults, __pyx_self)->__pyx_arg_incremental);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __Pyx_CyFunction_Defaults(__pyx_defaults, __pyx_self)->__pyx_arg_incremental);
  __Pyx_GIVEREF(__Pyx_CyFunction_Defaults(__pyx_defaults, __pyx_self)->__pyx_arg_incremental);
  __Pyx_INCREF(((PyObject *)Py_None));
  PyTuple_SET_ITEM(__pyx_t_1, 1, ((PyObject *)Py_None));
  __Pyx_GIVEREF(((PyObject *)Py_None));
  __pyx_r = ((PyObject *)__pyx_t_1);
  __pyx_t_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.__defaults__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_1__init__(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_1__init__ = {__Pyx_NAMESTR("__init__"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_1__init__, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_1__init__(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v_points = 0;
  PyObject *__pyx_v_incremental = 0;
  PyObject *__pyx_v_qhull_options = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__init__ (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s__self,&__pyx_n_s__points,&__pyx_n_s__incremental,&__pyx_n_s__qhull_options,0};
    PyObject* values[4] = {0,0,0,0};
    __pyx_defaults *__pyx_dynamic_args = __Pyx_CyFunction_Defaults(__pyx_defaults, __pyx_self);
    values[2] = __pyx_dynamic_args->__pyx_arg_incremental;
    values[3] = ((PyObject *)((PyObject *)Py_None));
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__self)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__points)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__init__", 0, 2, 4, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1196; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
        case  2:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s__incremental);
          if (value) { values[2] = value; kw_args--; }
        }
        case  3:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s__qhull_options);
          if (value) { values[3] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__init__") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1196; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_self = values[0];
    __pyx_v_points = values[1];
    __pyx_v_incremental = values[2];
    __pyx_v_qhull_options = values[3];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__init__", 0, 2, 4, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1196; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay___init__(__pyx_self, __pyx_v_self, __pyx_v_points, __pyx_v_incremental, __pyx_v_qhull_options);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay___init__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_points, PyObject *__pyx_v_incremental, PyObject *__pyx_v_qhull_options) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  int __pyx_t_5;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__init__", 0);
  __Pyx_INCREF(__pyx_v_points);
  __Pyx_INCREF(__pyx_v_qhull_options);

  
  __pyx_t_1 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1197; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__ascontiguousarray); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1197; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1197; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_v_points);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_points);
  __Pyx_GIVEREF(__pyx_v_points);
  __pyx_t_3 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_t_1), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1197; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetAttr(__pyx_t_3, __pyx_n_s__astype); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1197; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1197; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_3, __pyx_n_s__double); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1197; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1197; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_t_3), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1197; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_3)); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_v_points);
  __pyx_v_points = __pyx_t_2;
  __pyx_t_2 = 0;

  
  __pyx_t_4 = (__pyx_v_qhull_options == Py_None);
  if (__pyx_t_4) {

    
    __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_v_incremental); if (unlikely(__pyx_t_4 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1200; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    if (__pyx_t_4) {

      
      __Pyx_INCREF(((PyObject *)__pyx_n_s__Qt));
      __Pyx_DECREF(__pyx_v_qhull_options);
      __pyx_v_qhull_options = ((PyObject *)__pyx_n_s__Qt);
      goto __pyx_L4;
    }
     {

      
      __Pyx_INCREF(((PyObject *)__pyx_kp_s_24));
      __Pyx_DECREF(__pyx_v_qhull_options);
      __pyx_v_qhull_options = ((PyObject *)__pyx_kp_s_24);
    }
    __pyx_L4:;
    goto __pyx_L3;
  }
  __pyx_L3:;

  
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1205; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_points);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_points);
  __Pyx_GIVEREF(__pyx_v_points);
  __pyx_t_3 = PyDict_New(); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1205; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(((PyObject *)__pyx_t_3));
  __pyx_t_1 = __Pyx_PyBool_FromLong(1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1205; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_t_3, ((PyObject *)__pyx_n_s__delaunay), __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1205; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (PyDict_SetItem(__pyx_t_3, ((PyObject *)__pyx_n_s__incremental), __pyx_v_incremental) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1205; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  if (PyDict_SetItem(__pyx_t_3, ((PyObject *)__pyx_n_s__options), __pyx_v_qhull_options) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1205; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_1 = PyObject_Call(((PyObject *)((PyObject*)__pyx_ptype_5scipy_7spatial_5qhull__Qhull)), ((PyObject *)__pyx_t_2), ((PyObject *)__pyx_t_3)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1205; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_3)); __pyx_t_3 = 0;

  
  if (PyObject_SetAttr(__pyx_v_self, __pyx_n_s___qhull, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1205; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___flush); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1207; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = PyDict_New(); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1207; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(((PyObject *)__pyx_t_3));
  __pyx_t_2 = __Pyx_PyBool_FromLong(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1207; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_t_3, ((PyObject *)__pyx_n_s__force), __pyx_t_2) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1207; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_empty_tuple), ((PyObject *)__pyx_t_3)); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1207; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_3)); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  
  __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_v_incremental); if (unlikely(__pyx_t_4 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_5 = (!__pyx_t_4);
  if (__pyx_t_5) {

    
    __pyx_t_2 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___qhull); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1209; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_3 = PyObject_GetAttr(__pyx_t_2, __pyx_n_s__close); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1209; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = PyObject_Call(__pyx_t_3, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1209; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    goto __pyx_L5;
  }
  __pyx_L5:;

  
  __pyx_t_2 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___points); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1211; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyObject_GetAttr(__pyx_t_2, __pyx_n_s__shape); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1211; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_GetItemInt(__pyx_t_3, 1, sizeof(long), PyInt_FromLong); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1211; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (PyObject_SetAttr(__pyx_v_self, __pyx_n_s__ndim, __pyx_t_2) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1211; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_points);
  __Pyx_XDECREF(__pyx_v_qhull_options);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_3add_points(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_3add_points = {__Pyx_NAMESTR("add_points"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_3add_points, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_3add_points(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v_points = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("add_points (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s__self,&__pyx_n_s__points,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__self)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__points)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("add_points", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1213; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "add_points") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1213; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_self = values[0];
    __pyx_v_points = values[1];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("add_points", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1213; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.add_points", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_2add_points(__pyx_self, __pyx_v_self, __pyx_v_points);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_2add_points(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_points) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("add_points", 0);

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___qhull); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1214; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__add_points); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1214; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1214; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_v_points);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_points);
  __Pyx_GIVEREF(__pyx_v_points);
  __pyx_t_3 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_t_1), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1214; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.add_points", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_40__defaults__(CYTHON_UNUSED PyObject *__pyx_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__defaults__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1216; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__Pyx_CyFunction_Defaults(__pyx_defaults1, __pyx_self)->__pyx_arg_force);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __Pyx_CyFunction_Defaults(__pyx_defaults1, __pyx_self)->__pyx_arg_force);
  __Pyx_GIVEREF(__Pyx_CyFunction_Defaults(__pyx_defaults1, __pyx_self)->__pyx_arg_force);
  __pyx_r = ((PyObject *)__pyx_t_1);
  __pyx_t_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.__defaults__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_5_flush(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_5_flush = {__Pyx_NAMESTR("_flush"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_5_flush, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_5_flush(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v_force = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("_flush (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s__self,&__pyx_n_s__force,0};
    PyObject* values[2] = {0,0};
    __pyx_defaults1 *__pyx_dynamic_args = __Pyx_CyFunction_Defaults(__pyx_defaults1, __pyx_self);
    values[1] = __pyx_dynamic_args->__pyx_arg_force;
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__self)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s__force);
          if (value) { values[1] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "_flush") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1216; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_self = values[0];
    __pyx_v_force = values[1];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("_flush", 0, 1, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1216; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay._flush", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_4_flush(__pyx_self, __pyx_v_self, __pyx_v_force);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_4_flush(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_force) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_t_3;
  int __pyx_t_4;
  int __pyx_t_5;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  PyObject *(*__pyx_t_10)(PyObject *);
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("_flush", 0);

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___qhull); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1217; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__flush); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1217; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1217; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_3 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_3 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1217; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (!__pyx_t_3) {
    __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_v_force); if (unlikely(__pyx_t_4 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1217; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_t_5 = __pyx_t_4;
  } else {
    __pyx_t_5 = __pyx_t_3;
  }
  if (__pyx_t_5) {

    
    __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___qhull); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1219; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__get_arrays); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1219; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1219; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    if ((likely(PyTuple_CheckExact(__pyx_t_1))) || (PyList_CheckExact(__pyx_t_1))) {
      PyObject* sequence = __pyx_t_1;
      #if CYTHON_COMPILING_IN_CPYTHON
      Py_ssize_t size = Py_SIZE(sequence);
      #else
      Py_ssize_t size = PySequence_Size(sequence);
      #endif
      if (unlikely(size != 4)) {
        if (size > 4) __Pyx_RaiseTooManyValuesError(4);
        else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
        {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1218; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      }
      #if CYTHON_COMPILING_IN_CPYTHON
      if (likely(PyTuple_CheckExact(sequence))) {
        __pyx_t_2 = PyTuple_GET_ITEM(sequence, 0); 
        __pyx_t_6 = PyTuple_GET_ITEM(sequence, 1); 
        __pyx_t_7 = PyTuple_GET_ITEM(sequence, 2); 
        __pyx_t_8 = PyTuple_GET_ITEM(sequence, 3); 
      } else {
        __pyx_t_2 = PyList_GET_ITEM(sequence, 0); 
        __pyx_t_6 = PyList_GET_ITEM(sequence, 1); 
        __pyx_t_7 = PyList_GET_ITEM(sequence, 2); 
        __pyx_t_8 = PyList_GET_ITEM(sequence, 3); 
      }
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_6);
      __Pyx_INCREF(__pyx_t_7);
      __Pyx_INCREF(__pyx_t_8);
      #else
      Py_ssize_t i;
      PyObject** temps[4] = {&__pyx_t_2,&__pyx_t_6,&__pyx_t_7,&__pyx_t_8};
      for (i=0; i < 4; i++) {
        PyObject* item = PySequence_ITEM(sequence, i); if (unlikely(!item)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1218; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        *(temps[i]) = item;
      }
      #endif
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    } else
    {
      Py_ssize_t index = -1;
      PyObject** temps[4] = {&__pyx_t_2,&__pyx_t_6,&__pyx_t_7,&__pyx_t_8};
      __pyx_t_9 = PyObject_GetIter(__pyx_t_1); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1218; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_10 = Py_TYPE(__pyx_t_9)->tp_iternext;
      for (index=0; index < 4; index++) {
        PyObject* item = __pyx_t_10(__pyx_t_9); if (unlikely(!item)) goto __pyx_L4_unpacking_failed;
        __Pyx_GOTREF(item);
        *(temps[index]) = item;
      }
      if (__Pyx_IternextUnpackEndCheck(__pyx_t_10(__pyx_t_9), 4) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1218; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __pyx_t_10 = NULL;
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      goto __pyx_L5_unpacking_done;
      __pyx_L4_unpacking_failed:;
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      __pyx_t_10 = NULL;
      if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1218; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __pyx_L5_unpacking_done:;
    }

    
    if (PyObject_SetAttr(__pyx_v_self, __pyx_n_s___points, __pyx_t_2) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1218; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    if (PyObject_SetAttr(__pyx_v_self, __pyx_n_s___vertices, __pyx_t_6) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1218; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    if (PyObject_SetAttr(__pyx_v_self, __pyx_n_s___neighbors, __pyx_t_7) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1218; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    if (PyObject_SetAttr(__pyx_v_self, __pyx_n_s___equations, __pyx_t_8) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1218; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;

    
    __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___points); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1220; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_8 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__shape); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1220; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = __Pyx_GetItemInt(__pyx_t_8, 0, sizeof(long), PyInt_FromLong); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1220; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    if (PyObject_SetAttr(__pyx_v_self, __pyx_n_s___npoints, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1220; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    
    __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___vertices); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1221; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_8 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__shape); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1221; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = __Pyx_GetItemInt(__pyx_t_8, 0, sizeof(long), PyInt_FromLong); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1221; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    if (PyObject_SetAttr(__pyx_v_self, __pyx_n_s___nsimplex, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1221; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    
    __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___points); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1222; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_8 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__min); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1222; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1222; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(((PyObject *)__pyx_t_1));
    if (PyDict_SetItem(__pyx_t_1, ((PyObject *)__pyx_n_s__axis), __pyx_int_0) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1222; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_t_7 = PyObject_Call(__pyx_t_8, ((PyObject *)__pyx_empty_tuple), ((PyObject *)__pyx_t_1)); if (unlikely(!__pyx_t_7)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1222; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;
    if (PyObject_SetAttr(__pyx_v_self, __pyx_n_s___min_bound, __pyx_t_7) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1222; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;

    
    __pyx_t_7 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___points); if (unlikely(!__pyx_t_7)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1223; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_7);
    __pyx_t_1 = PyObject_GetAttr(__pyx_t_7, __pyx_n_s__max); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1223; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    __pyx_t_7 = PyDict_New(); if (unlikely(!__pyx_t_7)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1223; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(((PyObject *)__pyx_t_7));
    if (PyDict_SetItem(__pyx_t_7, ((PyObject *)__pyx_n_s__axis), __pyx_int_0) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1223; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_t_8 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_empty_tuple), ((PyObject *)__pyx_t_7)); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1223; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_DECREF(((PyObject *)__pyx_t_7)); __pyx_t_7 = 0;
    if (PyObject_SetAttr(__pyx_v_self, __pyx_n_s___max_bound, __pyx_t_8) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1223; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;

    
    if (PyObject_SetAttr(__pyx_v_self, __pyx_n_s___transform, Py_None) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1224; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

    
    if (PyObject_SetAttr(__pyx_v_self, __pyx_n_s___vertex_to_simplex, Py_None) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1225; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    goto __pyx_L3;
  }
  __pyx_L3:;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay._flush", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_7points(PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_7points = {__Pyx_NAMESTR("points"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_7points, METH_O, __Pyx_DOCSTR(0)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_7points(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("points (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_6points(__pyx_self, ((PyObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_6points(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("points", 0);

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___flush); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1229; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1229; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___points); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1230; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.points", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_9vertices(PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_9vertices = {__Pyx_NAMESTR("vertices"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_9vertices, METH_O, __Pyx_DOCSTR(0)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_9vertices(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("vertices (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_8vertices(__pyx_self, ((PyObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_8vertices(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("vertices", 0);

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___flush); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1234; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1234; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___vertices); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1235; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.vertices", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_11neighbors(PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_11neighbors = {__Pyx_NAMESTR("neighbors"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_11neighbors, METH_O, __Pyx_DOCSTR(0)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_11neighbors(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("neighbors (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_10neighbors(__pyx_self, ((PyObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_10neighbors(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("neighbors", 0);

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___flush); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1239; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1239; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___neighbors); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1240; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.neighbors", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_13equations(PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_13equations = {__Pyx_NAMESTR("equations"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_13equations, METH_O, __Pyx_DOCSTR(0)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_13equations(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("equations (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_12equations(__pyx_self, ((PyObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_12equations(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("equations", 0);

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___flush); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1244; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1244; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___equations); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1245; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.equations", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_15npoints(PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_15npoints = {__Pyx_NAMESTR("npoints"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_15npoints, METH_O, __Pyx_DOCSTR(0)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_15npoints(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("npoints (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_14npoints(__pyx_self, ((PyObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_14npoints(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("npoints", 0);

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___flush); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1249; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1249; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___npoints); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1250; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.npoints", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_17nsimplex(PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_17nsimplex = {__Pyx_NAMESTR("nsimplex"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_17nsimplex, METH_O, __Pyx_DOCSTR(0)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_17nsimplex(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("nsimplex (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_16nsimplex(__pyx_self, ((PyObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_16nsimplex(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("nsimplex", 0);

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___flush); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1254; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1254; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___nsimplex); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1255; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.nsimplex", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_19min_bound(PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_19min_bound = {__Pyx_NAMESTR("min_bound"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_19min_bound, METH_O, __Pyx_DOCSTR(0)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_19min_bound(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("min_bound (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_18min_bound(__pyx_self, ((PyObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_18min_bound(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("min_bound", 0);

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___flush); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1259; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1259; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___min_bound); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1260; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.min_bound", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_21max_bound(PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_21max_bound = {__Pyx_NAMESTR("max_bound"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_21max_bound, METH_O, __Pyx_DOCSTR(0)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_21max_bound(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("max_bound (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_20max_bound(__pyx_self, ((PyObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_20max_bound(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("max_bound", 0);

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___flush); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1264; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1264; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___max_bound); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1265; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.max_bound", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_23paraboloid_scale(PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_23paraboloid_scale = {__Pyx_NAMESTR("paraboloid_scale"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_23paraboloid_scale, METH_O, __Pyx_DOCSTR(0)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_23paraboloid_scale(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("paraboloid_scale (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_22paraboloid_scale(__pyx_self, ((PyObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_22paraboloid_scale(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("paraboloid_scale", 0);

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___qhull); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1269; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__paraboloid_scale); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1269; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.paraboloid_scale", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_25paraboloid_shift(PyObject *__pyx_self, PyObject *__pyx_v_self); 
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_25paraboloid_shift = {__Pyx_NAMESTR("paraboloid_shift"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_25paraboloid_shift, METH_O, __Pyx_DOCSTR(0)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_25paraboloid_shift(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("paraboloid_shift (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_24paraboloid_shift(__pyx_self, ((PyObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_24paraboloid_shift(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("paraboloid_shift", 0);

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___qhull); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1273; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__paraboloid_shift); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1273; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.paraboloid_shift", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_27transform(PyObject *__pyx_self, PyObject *__pyx_v_self); 
static char __pyx_doc_5scipy_7spatial_5qhull_8Delaunay_26transform[] = "\n        Affine transform from ``x`` to the barycentric coordinates ``c``.\n\n        :type: ndarray of double, shape (nsimplex, ndim+1, ndim)\n\n        This is defined by::\n\n            T c = x - r\n\n        At vertex ``j``, ``c_j = 1`` and the other coordinates zero.\n\n        For simplex ``i``, ``transform[i,:ndim,:ndim]`` contains\n        inverse of the matrix ``T``, and ``transform[i,ndim,:]``\n        contains the vector ``r``.\n\n        ";
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_27transform = {__Pyx_NAMESTR("transform"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_27transform, METH_O, __Pyx_DOCSTR(__pyx_doc_5scipy_7spatial_5qhull_8Delaunay_26transform)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_27transform(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("transform (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_26transform(__pyx_self, ((PyObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_26transform(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("transform", 0);

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___transform); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1293; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = (__pyx_t_1 == Py_None);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (__pyx_t_2) {

    
    __pyx_t_1 = __Pyx_GetName(__pyx_m, __pyx_n_s_25); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1294; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_3 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s__points); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1294; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);

    
    __pyx_t_4 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s__vertices); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1295; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);

    
    __pyx_t_5 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1296; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_6 = PyObject_GetAttr(__pyx_t_5, __pyx_n_s__finfo); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1296; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1296; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_INCREF(((PyObject *)((PyObject*)(&PyFloat_Type))));
    PyTuple_SET_ITEM(__pyx_t_5, 0, ((PyObject *)((PyObject*)(&PyFloat_Type))));
    __Pyx_GIVEREF(((PyObject *)((PyObject*)(&PyFloat_Type))));
    __pyx_t_7 = PyObject_Call(__pyx_t_6, ((PyObject *)__pyx_t_5), NULL); if (unlikely(!__pyx_t_7)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1296; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_DECREF(((PyObject *)__pyx_t_5)); __pyx_t_5 = 0;
    __pyx_t_5 = PyObject_GetAttr(__pyx_t_7, __pyx_n_s__eps); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1296; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    __pyx_t_7 = PyTuple_New(3); if (unlikely(!__pyx_t_7)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1294; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_7);
    PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_7, 1, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_7, 2, __pyx_t_5);
    __Pyx_GIVEREF(__pyx_t_5);
    __pyx_t_3 = 0;
    __pyx_t_4 = 0;
    __pyx_t_5 = 0;
    __pyx_t_5 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_t_7), NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1294; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_DECREF(((PyObject *)__pyx_t_7)); __pyx_t_7 = 0;

    
    if (PyObject_SetAttr(__pyx_v_self, __pyx_n_s___transform, __pyx_t_5) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1294; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    goto __pyx_L3;
  }
  __pyx_L3:;

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_5 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___transform); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1297; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_r = __pyx_t_5;
  __pyx_t_5 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.transform", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_29vertex_to_simplex(PyObject *__pyx_self, PyObject *__pyx_v_self); 
static char __pyx_doc_5scipy_7spatial_5qhull_8Delaunay_28vertex_to_simplex[] = "\n        Lookup array, from a vertex, to some simplex which it is a part of.\n\n        :type: ndarray of int, shape (npoints,)\n        ";
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_29vertex_to_simplex = {__Pyx_NAMESTR("vertex_to_simplex"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_29vertex_to_simplex, METH_O, __Pyx_DOCSTR(__pyx_doc_5scipy_7spatial_5qhull_8Delaunay_28vertex_to_simplex)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_29vertex_to_simplex(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("vertex_to_simplex (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_28vertex_to_simplex(__pyx_self, ((PyObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_28vertex_to_simplex(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self) {
  int __pyx_v_isimplex;
  int __pyx_v_k;
  int __pyx_v_ivertex;
  int __pyx_v_nsimplex;
  int __pyx_v_ndim;
  PyArrayObject *__pyx_v_vertices = 0;
  PyArrayObject *__pyx_v_arr = 0;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_arr;
  __Pyx_Buffer __pyx_pybuffer_arr;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_vertices;
  __Pyx_Buffer __pyx_pybuffer_vertices;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyArrayObject *__pyx_t_7 = NULL;
  int __pyx_t_8;
  PyObject *__pyx_t_9 = NULL;
  PyObject *__pyx_t_10 = NULL;
  PyObject *__pyx_t_11 = NULL;
  PyArrayObject *__pyx_t_12 = NULL;
  int __pyx_t_13;
  long __pyx_t_14;
  int __pyx_t_15;
  int __pyx_t_16;
  int __pyx_t_17;
  int __pyx_t_18;
  int __pyx_t_19;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("vertex_to_simplex", 0);
  __pyx_pybuffer_vertices.pybuffer.buf = NULL;
  __pyx_pybuffer_vertices.refcount = 0;
  __pyx_pybuffernd_vertices.data = NULL;
  __pyx_pybuffernd_vertices.rcbuffer = &__pyx_pybuffer_vertices;
  __pyx_pybuffer_arr.pybuffer.buf = NULL;
  __pyx_pybuffer_arr.refcount = 0;
  __pyx_pybuffernd_arr.data = NULL;
  __pyx_pybuffernd_arr.rcbuffer = &__pyx_pybuffer_arr;

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___vertex_to_simplex); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1311; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = (__pyx_t_1 == Py_None);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (__pyx_t_2) {

    
    __pyx_t_1 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_3 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__empty); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s__npoints); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_1);
    __Pyx_GIVEREF(__pyx_t_1);
    __pyx_t_1 = 0;
    __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    PyTuple_SET_ITEM(__pyx_t_1, 0, ((PyObject *)__pyx_t_4));
    __Pyx_GIVEREF(((PyObject *)__pyx_t_4));
    __pyx_t_4 = 0;
    __pyx_t_4 = PyDict_New(); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(((PyObject *)__pyx_t_4));
    __pyx_t_5 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_6 = PyObject_GetAttr(__pyx_t_5, __pyx_n_s__intc); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    if (PyDict_SetItem(__pyx_t_4, ((PyObject *)__pyx_n_s__dtype), __pyx_t_6) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_6 = PyObject_Call(__pyx_t_3, ((PyObject *)__pyx_t_1), ((PyObject *)__pyx_t_4)); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;
    __Pyx_DECREF(((PyObject *)__pyx_t_4)); __pyx_t_4 = 0;
    if (PyObject_SetAttr(__pyx_v_self, __pyx_n_s___vertex_to_simplex, __pyx_t_6) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

    
    __pyx_t_6 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___vertex_to_simplex); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1313; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_4 = PyObject_GetAttr(__pyx_t_6, __pyx_n_s__fill); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1313; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_6 = PyObject_Call(__pyx_t_4, ((PyObject *)__pyx_k_tuple_26), NULL); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1313; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

    
    __pyx_t_6 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___vertex_to_simplex); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1315; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    if (!(likely(((__pyx_t_6) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_6, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1315; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_t_7 = ((PyArrayObject *)__pyx_t_6);
    {
      __Pyx_BufFmt_StackElem __pyx_stack[1];
      __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_arr.rcbuffer->pybuffer);
      __pyx_t_8 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_arr.rcbuffer->pybuffer, (PyObject*)__pyx_t_7, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 1, 0, __pyx_stack);
      if (unlikely(__pyx_t_8 < 0)) {
        PyErr_Fetch(&__pyx_t_9, &__pyx_t_10, &__pyx_t_11);
        if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_arr.rcbuffer->pybuffer, (PyObject*)__pyx_v_arr, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 1, 0, __pyx_stack) == -1)) {
          Py_XDECREF(__pyx_t_9); Py_XDECREF(__pyx_t_10); Py_XDECREF(__pyx_t_11);
          __Pyx_RaiseBufferFallbackError();
        } else {
          PyErr_Restore(__pyx_t_9, __pyx_t_10, __pyx_t_11);
        }
      }
      __pyx_pybuffernd_arr.diminfo[0].strides = __pyx_pybuffernd_arr.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_arr.diminfo[0].shape = __pyx_pybuffernd_arr.rcbuffer->pybuffer.shape[0];
      if (unlikely(__pyx_t_8 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1315; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_t_7 = 0;
    __pyx_v_arr = ((PyArrayObject *)__pyx_t_6);
    __pyx_t_6 = 0;

    
    __pyx_t_6 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s__vertices); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1316; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    if (!(likely(((__pyx_t_6) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_6, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1316; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_t_12 = ((PyArrayObject *)__pyx_t_6);
    {
      __Pyx_BufFmt_StackElem __pyx_stack[1];
      __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer);
      __pyx_t_8 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer, (PyObject*)__pyx_t_12, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack);
      if (unlikely(__pyx_t_8 < 0)) {
        PyErr_Fetch(&__pyx_t_11, &__pyx_t_10, &__pyx_t_9);
        if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer, (PyObject*)__pyx_v_vertices, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack) == -1)) {
          Py_XDECREF(__pyx_t_11); Py_XDECREF(__pyx_t_10); Py_XDECREF(__pyx_t_9);
          __Pyx_RaiseBufferFallbackError();
        } else {
          PyErr_Restore(__pyx_t_11, __pyx_t_10, __pyx_t_9);
        }
      }
      __pyx_pybuffernd_vertices.diminfo[0].strides = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_vertices.diminfo[0].shape = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_vertices.diminfo[1].strides = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_vertices.diminfo[1].shape = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.shape[1];
      if (unlikely(__pyx_t_8 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1316; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_t_12 = 0;
    __pyx_v_vertices = ((PyArrayObject *)__pyx_t_6);
    __pyx_t_6 = 0;

    
    __pyx_t_6 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s__nsimplex); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1318; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_8 = __Pyx_PyInt_AsInt(__pyx_t_6); if (unlikely((__pyx_t_8 == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1318; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_v_nsimplex = __pyx_t_8;

    
    __pyx_t_6 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s__ndim); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1319; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_8 = __Pyx_PyInt_AsInt(__pyx_t_6); if (unlikely((__pyx_t_8 == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1319; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_v_ndim = __pyx_t_8;

    
    {
        #ifdef WITH_THREAD
        PyThreadState *_save = NULL;
        #endif
        Py_UNBLOCK_THREADS
         {

          
          __pyx_t_8 = __pyx_v_nsimplex;
          for (__pyx_t_13 = 0; __pyx_t_13 < __pyx_t_8; __pyx_t_13+=1) {
            __pyx_v_isimplex = __pyx_t_13;

            
            __pyx_t_14 = (__pyx_v_ndim + 1);
            for (__pyx_t_15 = 0; __pyx_t_15 < __pyx_t_14; __pyx_t_15+=1) {
              __pyx_v_k = __pyx_t_15;

              
              __pyx_t_16 = __pyx_v_isimplex;
              __pyx_t_17 = __pyx_v_k;
              if (__pyx_t_16 < 0) __pyx_t_16 += __pyx_pybuffernd_vertices.diminfo[0].shape;
              if (__pyx_t_17 < 0) __pyx_t_17 += __pyx_pybuffernd_vertices.diminfo[1].shape;
              __pyx_v_ivertex = (*__Pyx_BufPtrStrided2d(npy_int *, __pyx_pybuffernd_vertices.rcbuffer->pybuffer.buf, __pyx_t_16, __pyx_pybuffernd_vertices.diminfo[0].strides, __pyx_t_17, __pyx_pybuffernd_vertices.diminfo[1].strides));

              
              __pyx_t_18 = __pyx_v_ivertex;
              if (__pyx_t_18 < 0) __pyx_t_18 += __pyx_pybuffernd_arr.diminfo[0].shape;
              __pyx_t_2 = ((*__Pyx_BufPtrStrided1d(npy_int *, __pyx_pybuffernd_arr.rcbuffer->pybuffer.buf, __pyx_t_18, __pyx_pybuffernd_arr.diminfo[0].strides)) == -1);
              if (__pyx_t_2) {

                
                __pyx_t_19 = __pyx_v_ivertex;
                if (__pyx_t_19 < 0) __pyx_t_19 += __pyx_pybuffernd_arr.diminfo[0].shape;
                *__Pyx_BufPtrStrided1d(npy_int *, __pyx_pybuffernd_arr.rcbuffer->pybuffer.buf, __pyx_t_19, __pyx_pybuffernd_arr.diminfo[0].strides) = __pyx_v_isimplex;
                goto __pyx_L11;
              }
              __pyx_L11:;
            }
          }
        }

        
         {
          Py_BLOCK_THREADS
        }
    }
    goto __pyx_L3;
  }
  __pyx_L3:;

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_6 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s___vertex_to_simplex); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1328; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_r = __pyx_t_6;
  __pyx_t_6 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  { PyObject *__pyx_type, *__pyx_value, *__pyx_tb;
    __Pyx_ErrFetch(&__pyx_type, &__pyx_value, &__pyx_tb);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_arr.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer);
  __Pyx_ErrRestore(__pyx_type, __pyx_value, __pyx_tb);}
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.vertex_to_simplex", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  goto __pyx_L2;
  __pyx_L0:;
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_arr.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer);
  __pyx_L2:;
  __Pyx_XDECREF((PyObject *)__pyx_v_vertices);
  __Pyx_XDECREF((PyObject *)__pyx_v_arr);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_31convex_hull(PyObject *__pyx_self, PyObject *__pyx_v_self); 
static char __pyx_doc_5scipy_7spatial_5qhull_8Delaunay_30convex_hull[] = "\n        Vertices of facets forming the convex hull of the point set.\n\n        :type: ndarray of int, shape (nfaces, ndim)\n\n        The array contains the indices of the points\n        belonging to the (N-1)-dimensional facets that form the convex\n        hull of the triangulation.\n\n        ";
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_31convex_hull = {__Pyx_NAMESTR("convex_hull"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_31convex_hull, METH_O, __Pyx_DOCSTR(__pyx_doc_5scipy_7spatial_5qhull_8Delaunay_30convex_hull)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_31convex_hull(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("convex_hull (wrapper)", 0);
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_30convex_hull(__pyx_self, ((PyObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_30convex_hull(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self) {
  int __pyx_v_isimplex;
  int __pyx_v_k;
  int __pyx_v_j;
  int __pyx_v_ndim;
  int __pyx_v_nsimplex;
  int __pyx_v_m;
  int __pyx_v_msize;
  PyObject *__pyx_v_out = 0;
  PyArrayObject *__pyx_v_arr = 0;
  PyArrayObject *__pyx_v_neighbors = 0;
  PyArrayObject *__pyx_v_vertices = 0;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_arr;
  __Pyx_Buffer __pyx_pybuffer_arr;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_neighbors;
  __Pyx_Buffer __pyx_pybuffer_neighbors;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_vertices;
  __Pyx_Buffer __pyx_pybuffer_vertices;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyArrayObject *__pyx_t_2 = NULL;
  int __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyArrayObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  PyObject *__pyx_t_10 = NULL;
  PyObject *__pyx_t_11 = NULL;
  PyArrayObject *__pyx_t_12 = NULL;
  int __pyx_t_13;
  long __pyx_t_14;
  int __pyx_t_15;
  int __pyx_t_16;
  int __pyx_t_17;
  int __pyx_t_18;
  long __pyx_t_19;
  int __pyx_t_20;
  int __pyx_t_21;
  int __pyx_t_22;
  int __pyx_t_23;
  int __pyx_t_24;
  int __pyx_t_25;
  int __pyx_t_26;
  int __pyx_t_27;
  long __pyx_t_28;
  PyObject *__pyx_t_29 = NULL;
  PyObject *__pyx_t_30 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("convex_hull", 0);
  __pyx_pybuffer_arr.pybuffer.buf = NULL;
  __pyx_pybuffer_arr.refcount = 0;
  __pyx_pybuffernd_arr.data = NULL;
  __pyx_pybuffernd_arr.rcbuffer = &__pyx_pybuffer_arr;
  __pyx_pybuffer_neighbors.pybuffer.buf = NULL;
  __pyx_pybuffer_neighbors.refcount = 0;
  __pyx_pybuffernd_neighbors.data = NULL;
  __pyx_pybuffernd_neighbors.rcbuffer = &__pyx_pybuffer_neighbors;
  __pyx_pybuffer_vertices.pybuffer.buf = NULL;
  __pyx_pybuffer_vertices.refcount = 0;
  __pyx_pybuffernd_vertices.data = NULL;
  __pyx_pybuffernd_vertices.rcbuffer = &__pyx_pybuffer_vertices;

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s__neighbors); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1349; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (!(likely(((__pyx_t_1) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_1, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1349; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_2 = ((PyArrayObject *)__pyx_t_1);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_neighbors.rcbuffer->pybuffer);
    __pyx_t_3 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_neighbors.rcbuffer->pybuffer, (PyObject*)__pyx_t_2, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack);
    if (unlikely(__pyx_t_3 < 0)) {
      PyErr_Fetch(&__pyx_t_4, &__pyx_t_5, &__pyx_t_6);
      if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_neighbors.rcbuffer->pybuffer, (PyObject*)__pyx_v_neighbors, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack) == -1)) {
        Py_XDECREF(__pyx_t_4); Py_XDECREF(__pyx_t_5); Py_XDECREF(__pyx_t_6);
        __Pyx_RaiseBufferFallbackError();
      } else {
        PyErr_Restore(__pyx_t_4, __pyx_t_5, __pyx_t_6);
      }
    }
    __pyx_pybuffernd_neighbors.diminfo[0].strides = __pyx_pybuffernd_neighbors.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_neighbors.diminfo[0].shape = __pyx_pybuffernd_neighbors.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_neighbors.diminfo[1].strides = __pyx_pybuffernd_neighbors.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_neighbors.diminfo[1].shape = __pyx_pybuffernd_neighbors.rcbuffer->pybuffer.shape[1];
    if (unlikely(__pyx_t_3 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1349; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_2 = 0;
  __pyx_v_neighbors = ((PyArrayObject *)__pyx_t_1);
  __pyx_t_1 = 0;

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s__vertices); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1350; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (!(likely(((__pyx_t_1) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_1, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1350; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_7 = ((PyArrayObject *)__pyx_t_1);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer);
    __pyx_t_3 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer, (PyObject*)__pyx_t_7, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack);
    if (unlikely(__pyx_t_3 < 0)) {
      PyErr_Fetch(&__pyx_t_6, &__pyx_t_5, &__pyx_t_4);
      if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer, (PyObject*)__pyx_v_vertices, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack) == -1)) {
        Py_XDECREF(__pyx_t_6); Py_XDECREF(__pyx_t_5); Py_XDECREF(__pyx_t_4);
        __Pyx_RaiseBufferFallbackError();
      } else {
        PyErr_Restore(__pyx_t_6, __pyx_t_5, __pyx_t_4);
      }
    }
    __pyx_pybuffernd_vertices.diminfo[0].strides = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_vertices.diminfo[0].shape = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_vertices.diminfo[1].strides = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_vertices.diminfo[1].shape = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.shape[1];
    if (unlikely(__pyx_t_3 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1350; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_7 = 0;
  __pyx_v_vertices = ((PyArrayObject *)__pyx_t_1);
  __pyx_t_1 = 0;

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s__ndim); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1351; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = __Pyx_PyInt_AsInt(__pyx_t_1); if (unlikely((__pyx_t_3 == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1351; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_ndim = __pyx_t_3;

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s__nsimplex); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1352; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = __Pyx_PyInt_AsInt(__pyx_t_1); if (unlikely((__pyx_t_3 == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1352; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_nsimplex = __pyx_t_3;

  
  __pyx_v_msize = 10;

  
  __pyx_t_1 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1355; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_8 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__empty); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1355; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_8);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyInt_FromLong(__pyx_v_msize); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1355; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_9 = PyInt_FromLong(__pyx_v_ndim); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1355; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_9);
  __pyx_t_10 = PyTuple_New(2); if (unlikely(!__pyx_t_10)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1355; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_10);
  PyTuple_SET_ITEM(__pyx_t_10, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_10, 1, __pyx_t_9);
  __Pyx_GIVEREF(__pyx_t_9);
  __pyx_t_1 = 0;
  __pyx_t_9 = 0;
  __pyx_t_9 = PyTuple_New(1); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1355; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_9);
  PyTuple_SET_ITEM(__pyx_t_9, 0, ((PyObject *)__pyx_t_10));
  __Pyx_GIVEREF(((PyObject *)__pyx_t_10));
  __pyx_t_10 = 0;
  __pyx_t_10 = PyDict_New(); if (unlikely(!__pyx_t_10)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1355; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(((PyObject *)__pyx_t_10));
  __pyx_t_1 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1355; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_11 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__intc); if (unlikely(!__pyx_t_11)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1355; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_11);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (PyDict_SetItem(__pyx_t_10, ((PyObject *)__pyx_n_s__dtype), __pyx_t_11) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1355; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
  __pyx_t_11 = PyObject_Call(__pyx_t_8, ((PyObject *)__pyx_t_9), ((PyObject *)__pyx_t_10)); if (unlikely(!__pyx_t_11)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1355; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_11);
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_9)); __pyx_t_9 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_10)); __pyx_t_10 = 0;
  __pyx_v_out = __pyx_t_11;
  __pyx_t_11 = 0;

  
  if (!(likely(((__pyx_v_out) == Py_None) || likely(__Pyx_TypeTest(__pyx_v_out, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1356; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_12 = ((PyArrayObject *)__pyx_v_out);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_arr.rcbuffer->pybuffer);
    __pyx_t_3 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_arr.rcbuffer->pybuffer, (PyObject*)__pyx_t_12, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 2, 0, __pyx_stack);
    if (unlikely(__pyx_t_3 < 0)) {
      PyErr_Fetch(&__pyx_t_4, &__pyx_t_5, &__pyx_t_6);
      if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_arr.rcbuffer->pybuffer, (PyObject*)__pyx_v_arr, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 2, 0, __pyx_stack) == -1)) {
        Py_XDECREF(__pyx_t_4); Py_XDECREF(__pyx_t_5); Py_XDECREF(__pyx_t_6);
        __Pyx_RaiseBufferFallbackError();
      } else {
        PyErr_Restore(__pyx_t_4, __pyx_t_5, __pyx_t_6);
      }
    }
    __pyx_pybuffernd_arr.diminfo[0].strides = __pyx_pybuffernd_arr.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_arr.diminfo[0].shape = __pyx_pybuffernd_arr.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_arr.diminfo[1].strides = __pyx_pybuffernd_arr.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_arr.diminfo[1].shape = __pyx_pybuffernd_arr.rcbuffer->pybuffer.shape[1];
    if (unlikely(__pyx_t_3 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1356; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_12 = 0;
  __Pyx_INCREF(__pyx_v_out);
  __pyx_v_arr = ((PyArrayObject *)__pyx_v_out);

  
  __pyx_v_m = 0;

  
  __pyx_t_3 = __pyx_v_nsimplex;
  for (__pyx_t_13 = 0; __pyx_t_13 < __pyx_t_3; __pyx_t_13+=1) {
    __pyx_v_isimplex = __pyx_t_13;

    
    __pyx_t_14 = (__pyx_v_ndim + 1);
    for (__pyx_t_15 = 0; __pyx_t_15 < __pyx_t_14; __pyx_t_15+=1) {
      __pyx_v_k = __pyx_t_15;

      
      __pyx_t_16 = __pyx_v_isimplex;
      __pyx_t_17 = __pyx_v_k;
      if (__pyx_t_16 < 0) __pyx_t_16 += __pyx_pybuffernd_neighbors.diminfo[0].shape;
      if (__pyx_t_17 < 0) __pyx_t_17 += __pyx_pybuffernd_neighbors.diminfo[1].shape;
      __pyx_t_18 = ((*__Pyx_BufPtrStrided2d(npy_int *, __pyx_pybuffernd_neighbors.rcbuffer->pybuffer.buf, __pyx_t_16, __pyx_pybuffernd_neighbors.diminfo[0].strides, __pyx_t_17, __pyx_pybuffernd_neighbors.diminfo[1].strides)) == -1);
      if (__pyx_t_18) {

        
        __pyx_t_19 = (__pyx_v_ndim + 1);
        for (__pyx_t_20 = 0; __pyx_t_20 < __pyx_t_19; __pyx_t_20+=1) {
          __pyx_v_j = __pyx_t_20;

          
          __pyx_t_18 = (__pyx_v_j < __pyx_v_k);
          if (__pyx_t_18) {

            
            __pyx_t_21 = __pyx_v_isimplex;
            __pyx_t_22 = __pyx_v_j;
            if (__pyx_t_21 < 0) __pyx_t_21 += __pyx_pybuffernd_vertices.diminfo[0].shape;
            if (__pyx_t_22 < 0) __pyx_t_22 += __pyx_pybuffernd_vertices.diminfo[1].shape;
            __pyx_t_23 = __pyx_v_m;
            __pyx_t_24 = __pyx_v_j;
            if (__pyx_t_23 < 0) __pyx_t_23 += __pyx_pybuffernd_arr.diminfo[0].shape;
            if (__pyx_t_24 < 0) __pyx_t_24 += __pyx_pybuffernd_arr.diminfo[1].shape;
            *__Pyx_BufPtrStrided2d(npy_int *, __pyx_pybuffernd_arr.rcbuffer->pybuffer.buf, __pyx_t_23, __pyx_pybuffernd_arr.diminfo[0].strides, __pyx_t_24, __pyx_pybuffernd_arr.diminfo[1].strides) = (*__Pyx_BufPtrStrided2d(npy_int *, __pyx_pybuffernd_vertices.rcbuffer->pybuffer.buf, __pyx_t_21, __pyx_pybuffernd_vertices.diminfo[0].strides, __pyx_t_22, __pyx_pybuffernd_vertices.diminfo[1].strides));
            goto __pyx_L10;
          }

          
          __pyx_t_18 = (__pyx_v_j > __pyx_v_k);
          if (__pyx_t_18) {

            
            __pyx_t_25 = __pyx_v_isimplex;
            __pyx_t_26 = __pyx_v_j;
            if (__pyx_t_25 < 0) __pyx_t_25 += __pyx_pybuffernd_vertices.diminfo[0].shape;
            if (__pyx_t_26 < 0) __pyx_t_26 += __pyx_pybuffernd_vertices.diminfo[1].shape;
            __pyx_t_27 = __pyx_v_m;
            __pyx_t_28 = (__pyx_v_j - 1);
            if (__pyx_t_27 < 0) __pyx_t_27 += __pyx_pybuffernd_arr.diminfo[0].shape;
            if (__pyx_t_28 < 0) __pyx_t_28 += __pyx_pybuffernd_arr.diminfo[1].shape;
            *__Pyx_BufPtrStrided2d(npy_int *, __pyx_pybuffernd_arr.rcbuffer->pybuffer.buf, __pyx_t_27, __pyx_pybuffernd_arr.diminfo[0].strides, __pyx_t_28, __pyx_pybuffernd_arr.diminfo[1].strides) = (*__Pyx_BufPtrStrided2d(npy_int *, __pyx_pybuffernd_vertices.rcbuffer->pybuffer.buf, __pyx_t_25, __pyx_pybuffernd_vertices.diminfo[0].strides, __pyx_t_26, __pyx_pybuffernd_vertices.diminfo[1].strides));
            goto __pyx_L10;
          }
          __pyx_L10:;
        }

        
        __pyx_v_m = (__pyx_v_m + 1);

        
        __pyx_t_18 = (__pyx_v_m >= __pyx_v_msize);
        if (__pyx_t_18) {

          
          __pyx_t_12 = ((PyArrayObject *)Py_None);
          {
            __Pyx_BufFmt_StackElem __pyx_stack[1];
            __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_arr.rcbuffer->pybuffer);
            __pyx_t_20 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_arr.rcbuffer->pybuffer, (PyObject*)__pyx_t_12, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 2, 0, __pyx_stack);
            if (unlikely(__pyx_t_20 < 0)) {
              PyErr_Fetch(&__pyx_t_6, &__pyx_t_5, &__pyx_t_4);
              if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_arr.rcbuffer->pybuffer, (PyObject*)__pyx_v_arr, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 2, 0, __pyx_stack) == -1)) {
                Py_XDECREF(__pyx_t_6); Py_XDECREF(__pyx_t_5); Py_XDECREF(__pyx_t_4);
                __Pyx_RaiseBufferFallbackError();
              } else {
                PyErr_Restore(__pyx_t_6, __pyx_t_5, __pyx_t_4);
              }
            }
            __pyx_pybuffernd_arr.diminfo[0].strides = __pyx_pybuffernd_arr.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_arr.diminfo[0].shape = __pyx_pybuffernd_arr.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_arr.diminfo[1].strides = __pyx_pybuffernd_arr.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_arr.diminfo[1].shape = __pyx_pybuffernd_arr.rcbuffer->pybuffer.shape[1];
            if (unlikely(__pyx_t_20 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1370; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          }
          __pyx_t_12 = 0;
          __Pyx_INCREF(Py_None);
          __Pyx_DECREF(((PyObject *)__pyx_v_arr));
          __pyx_v_arr = ((PyArrayObject *)Py_None);

          
          __pyx_v_msize = ((2 * __pyx_v_msize) + 1);

          
          __pyx_t_11 = PyObject_GetAttr(__pyx_v_out, __pyx_n_s__resize); if (unlikely(!__pyx_t_11)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1372; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __Pyx_GOTREF(__pyx_t_11);
          __pyx_t_10 = PyInt_FromLong(__pyx_v_msize); if (unlikely(!__pyx_t_10)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1372; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __Pyx_GOTREF(__pyx_t_10);
          __pyx_t_9 = PyInt_FromLong(__pyx_v_ndim); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1372; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __Pyx_GOTREF(__pyx_t_9);
          __pyx_t_8 = PyTuple_New(2); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1372; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __Pyx_GOTREF(__pyx_t_8);
          PyTuple_SET_ITEM(__pyx_t_8, 0, __pyx_t_10);
          __Pyx_GIVEREF(__pyx_t_10);
          PyTuple_SET_ITEM(__pyx_t_8, 1, __pyx_t_9);
          __Pyx_GIVEREF(__pyx_t_9);
          __pyx_t_10 = 0;
          __pyx_t_9 = 0;
          __pyx_t_9 = PyObject_Call(__pyx_t_11, ((PyObject *)__pyx_t_8), NULL); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1372; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __Pyx_GOTREF(__pyx_t_9);
          __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
          __Pyx_DECREF(((PyObject *)__pyx_t_8)); __pyx_t_8 = 0;
          __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;

          
          if (!(likely(((__pyx_v_out) == Py_None) || likely(__Pyx_TypeTest(__pyx_v_out, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1373; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __pyx_t_12 = ((PyArrayObject *)__pyx_v_out);
          {
            __Pyx_BufFmt_StackElem __pyx_stack[1];
            __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_arr.rcbuffer->pybuffer);
            __pyx_t_20 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_arr.rcbuffer->pybuffer, (PyObject*)__pyx_t_12, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 2, 0, __pyx_stack);
            if (unlikely(__pyx_t_20 < 0)) {
              PyErr_Fetch(&__pyx_t_4, &__pyx_t_5, &__pyx_t_6);
              if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_arr.rcbuffer->pybuffer, (PyObject*)__pyx_v_arr, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 2, 0, __pyx_stack) == -1)) {
                Py_XDECREF(__pyx_t_4); Py_XDECREF(__pyx_t_5); Py_XDECREF(__pyx_t_6);
                __Pyx_RaiseBufferFallbackError();
              } else {
                PyErr_Restore(__pyx_t_4, __pyx_t_5, __pyx_t_6);
              }
            }
            __pyx_pybuffernd_arr.diminfo[0].strides = __pyx_pybuffernd_arr.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_arr.diminfo[0].shape = __pyx_pybuffernd_arr.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_arr.diminfo[1].strides = __pyx_pybuffernd_arr.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_arr.diminfo[1].shape = __pyx_pybuffernd_arr.rcbuffer->pybuffer.shape[1];
            if (unlikely(__pyx_t_20 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1373; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          }
          __pyx_t_12 = 0;
          __Pyx_INCREF(__pyx_v_out);
          __Pyx_DECREF(((PyObject *)__pyx_v_arr));
          __pyx_v_arr = ((PyArrayObject *)__pyx_v_out);
          goto __pyx_L11;
        }
        __pyx_L11:;
        goto __pyx_L7;
      }
      __pyx_L7:;
    }
  }

  
  __pyx_t_12 = ((PyArrayObject *)Py_None);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_arr.rcbuffer->pybuffer);
    __pyx_t_3 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_arr.rcbuffer->pybuffer, (PyObject*)__pyx_t_12, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 2, 0, __pyx_stack);
    if (unlikely(__pyx_t_3 < 0)) {
      PyErr_Fetch(&__pyx_t_6, &__pyx_t_5, &__pyx_t_4);
      if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_arr.rcbuffer->pybuffer, (PyObject*)__pyx_v_arr, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 2, 0, __pyx_stack) == -1)) {
        Py_XDECREF(__pyx_t_6); Py_XDECREF(__pyx_t_5); Py_XDECREF(__pyx_t_4);
        __Pyx_RaiseBufferFallbackError();
      } else {
        PyErr_Restore(__pyx_t_6, __pyx_t_5, __pyx_t_4);
      }
    }
    __pyx_pybuffernd_arr.diminfo[0].strides = __pyx_pybuffernd_arr.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_arr.diminfo[0].shape = __pyx_pybuffernd_arr.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_arr.diminfo[1].strides = __pyx_pybuffernd_arr.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_arr.diminfo[1].shape = __pyx_pybuffernd_arr.rcbuffer->pybuffer.shape[1];
    if (unlikely(__pyx_t_3 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1375; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_12 = 0;
  __Pyx_INCREF(Py_None);
  __Pyx_DECREF(((PyObject *)__pyx_v_arr));
  __pyx_v_arr = ((PyArrayObject *)Py_None);

  
  {
    __Pyx_ExceptionSave(&__pyx_t_4, &__pyx_t_5, &__pyx_t_6);
    __Pyx_XGOTREF(__pyx_t_4);
    __Pyx_XGOTREF(__pyx_t_5);
    __Pyx_XGOTREF(__pyx_t_6);
     {

      
      __pyx_t_9 = PyObject_GetAttr(__pyx_v_out, __pyx_n_s__resize); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1377; __pyx_clineno = __LINE__; goto __pyx_L12_error;}
      __Pyx_GOTREF(__pyx_t_9);
      __pyx_t_8 = PyInt_FromLong(__pyx_v_m); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1377; __pyx_clineno = __LINE__; goto __pyx_L12_error;}
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_11 = PyInt_FromLong(__pyx_v_ndim); if (unlikely(!__pyx_t_11)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1377; __pyx_clineno = __LINE__; goto __pyx_L12_error;}
      __Pyx_GOTREF(__pyx_t_11);
      __pyx_t_10 = PyTuple_New(2); if (unlikely(!__pyx_t_10)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1377; __pyx_clineno = __LINE__; goto __pyx_L12_error;}
      __Pyx_GOTREF(__pyx_t_10);
      PyTuple_SET_ITEM(__pyx_t_10, 0, __pyx_t_8);
      __Pyx_GIVEREF(__pyx_t_8);
      PyTuple_SET_ITEM(__pyx_t_10, 1, __pyx_t_11);
      __Pyx_GIVEREF(__pyx_t_11);
      __pyx_t_8 = 0;
      __pyx_t_11 = 0;
      __pyx_t_11 = PyObject_Call(__pyx_t_9, ((PyObject *)__pyx_t_10), NULL); if (unlikely(!__pyx_t_11)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1377; __pyx_clineno = __LINE__; goto __pyx_L12_error;}
      __Pyx_GOTREF(__pyx_t_11);
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      __Pyx_DECREF(((PyObject *)__pyx_t_10)); __pyx_t_10 = 0;
      __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
    }
    __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
    goto __pyx_L19_try_end;
    __pyx_L12_error:;
    __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_XDECREF(__pyx_t_8); __pyx_t_8 = 0;
    __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
    __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
    __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;

    
    __pyx_t_3 = PyErr_ExceptionMatches(__pyx_builtin_ValueError);
    if (__pyx_t_3) {
      __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.convex_hull", __pyx_clineno, __pyx_lineno, __pyx_filename);
      if (__Pyx_GetException(&__pyx_t_11, &__pyx_t_10, &__pyx_t_9) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1378; __pyx_clineno = __LINE__; goto __pyx_L14_except_error;}
      __Pyx_GOTREF(__pyx_t_11);
      __Pyx_GOTREF(__pyx_t_10);
      __Pyx_GOTREF(__pyx_t_9);

      
      __Pyx_XDECREF(__pyx_r);
      __pyx_t_8 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1381; __pyx_clineno = __LINE__; goto __pyx_L14_except_error;}
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_1 = PyObject_GetAttr(__pyx_t_8, __pyx_n_s__resize); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1381; __pyx_clineno = __LINE__; goto __pyx_L14_except_error;}
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
      __pyx_t_8 = PyInt_FromLong(__pyx_v_m); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1381; __pyx_clineno = __LINE__; goto __pyx_L14_except_error;}
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_29 = PyInt_FromLong(__pyx_v_ndim); if (unlikely(!__pyx_t_29)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1381; __pyx_clineno = __LINE__; goto __pyx_L14_except_error;}
      __Pyx_GOTREF(__pyx_t_29);
      __pyx_t_30 = PyTuple_New(2); if (unlikely(!__pyx_t_30)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1381; __pyx_clineno = __LINE__; goto __pyx_L14_except_error;}
      __Pyx_GOTREF(__pyx_t_30);
      PyTuple_SET_ITEM(__pyx_t_30, 0, __pyx_t_8);
      __Pyx_GIVEREF(__pyx_t_8);
      PyTuple_SET_ITEM(__pyx_t_30, 1, __pyx_t_29);
      __Pyx_GIVEREF(__pyx_t_29);
      __pyx_t_8 = 0;
      __pyx_t_29 = 0;
      __pyx_t_29 = PyTuple_New(2); if (unlikely(!__pyx_t_29)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1381; __pyx_clineno = __LINE__; goto __pyx_L14_except_error;}
      __Pyx_GOTREF(__pyx_t_29);
      __Pyx_INCREF(__pyx_v_out);
      PyTuple_SET_ITEM(__pyx_t_29, 0, __pyx_v_out);
      __Pyx_GIVEREF(__pyx_v_out);
      PyTuple_SET_ITEM(__pyx_t_29, 1, ((PyObject *)__pyx_t_30));
      __Pyx_GIVEREF(((PyObject *)__pyx_t_30));
      __pyx_t_30 = 0;
      __pyx_t_30 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_t_29), NULL); if (unlikely(!__pyx_t_30)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1381; __pyx_clineno = __LINE__; goto __pyx_L14_except_error;}
      __Pyx_GOTREF(__pyx_t_30);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __Pyx_DECREF(((PyObject *)__pyx_t_29)); __pyx_t_29 = 0;
      __pyx_r = __pyx_t_30;
      __pyx_t_30 = 0;
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
      __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
      goto __pyx_L15_except_return;
      __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
      __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      goto __pyx_L13_exception_handled;
    }
    __pyx_L14_except_error:;
    __Pyx_XGIVEREF(__pyx_t_4);
    __Pyx_XGIVEREF(__pyx_t_5);
    __Pyx_XGIVEREF(__pyx_t_6);
    __Pyx_ExceptionReset(__pyx_t_4, __pyx_t_5, __pyx_t_6);
    goto __pyx_L1_error;
    __pyx_L15_except_return:;
    __Pyx_XGIVEREF(__pyx_t_4);
    __Pyx_XGIVEREF(__pyx_t_5);
    __Pyx_XGIVEREF(__pyx_t_6);
    __Pyx_ExceptionReset(__pyx_t_4, __pyx_t_5, __pyx_t_6);
    goto __pyx_L0;
    __pyx_L13_exception_handled:;
    __Pyx_XGIVEREF(__pyx_t_4);
    __Pyx_XGIVEREF(__pyx_t_5);
    __Pyx_XGIVEREF(__pyx_t_6);
    __Pyx_ExceptionReset(__pyx_t_4, __pyx_t_5, __pyx_t_6);
    __pyx_L19_try_end:;
  }

  
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(__pyx_v_out);
  __pyx_r = __pyx_v_out;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_XDECREF(__pyx_t_10);
  __Pyx_XDECREF(__pyx_t_11);
  __Pyx_XDECREF(__pyx_t_29);
  __Pyx_XDECREF(__pyx_t_30);
  { PyObject *__pyx_type, *__pyx_value, *__pyx_tb;
    __Pyx_ErrFetch(&__pyx_type, &__pyx_value, &__pyx_tb);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_arr.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_neighbors.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer);
  __Pyx_ErrRestore(__pyx_type, __pyx_value, __pyx_tb);}
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.convex_hull", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  goto __pyx_L2;
  __pyx_L0:;
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_arr.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_neighbors.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer);
  __pyx_L2:;
  __Pyx_XDECREF(__pyx_v_out);
  __Pyx_XDECREF((PyObject *)__pyx_v_arr);
  __Pyx_XDECREF((PyObject *)__pyx_v_neighbors);
  __Pyx_XDECREF((PyObject *)__pyx_v_vertices);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_42__defaults__(CYTHON_UNUSED PyObject *__pyx_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__defaults__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1385; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__Pyx_CyFunction_Defaults(__pyx_defaults2, __pyx_self)->__pyx_arg_bruteforce);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __Pyx_CyFunction_Defaults(__pyx_defaults2, __pyx_self)->__pyx_arg_bruteforce);
  __Pyx_GIVEREF(__Pyx_CyFunction_Defaults(__pyx_defaults2, __pyx_self)->__pyx_arg_bruteforce);
  __Pyx_INCREF(((PyObject *)Py_None));
  PyTuple_SET_ITEM(__pyx_t_1, 1, ((PyObject *)Py_None));
  __Pyx_GIVEREF(((PyObject *)Py_None));
  __pyx_r = ((PyObject *)__pyx_t_1);
  __pyx_t_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.__defaults__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_33find_simplex(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static char __pyx_doc_5scipy_7spatial_5qhull_8Delaunay_32find_simplex[] = "\n        find_simplex(self, xi, bruteforce=False, tol=None)\n\n        Find the simplices containing the given points.\n\n        Parameters\n        ----------\n        tri : DelaunayInfo\n            Delaunay triangulation\n        xi : ndarray of double, shape (..., ndim)\n            Points to locate\n        bruteforce : bool, optional\n            Whether to only perform a brute-force search\n        tol : float, optional\n            Tolerance allowed in the inside-triangle check.\n            Default is ``100*eps``.\n\n        Returns\n        -------\n        i : ndarray of int, same shape as `xi`\n            Indices of simplices containing each point.\n            Points outside the triangulation get the value -1.\n\n        Notes\n        -----\n        This uses an algorithm adapted from Qhull's ``qh_findbestfacet``,\n        which makes use of the connection between a convex hull and a\n        Delaunay triangulation. After finding the simplex closest to\n        the point in N+1 dimensions, the algorithm falls back to\n        directed search in N dimensions.\n\n        ";
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_33find_simplex = {__Pyx_NAMESTR("find_simplex"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_33find_simplex, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(__pyx_doc_5scipy_7spatial_5qhull_8Delaunay_32find_simplex)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_33find_simplex(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v_xi = 0;
  PyObject *__pyx_v_bruteforce = 0;
  PyObject *__pyx_v_tol = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("find_simplex (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s__self,&__pyx_n_s__xi,&__pyx_n_s__bruteforce,&__pyx_n_s__tol,0};
    PyObject* values[4] = {0,0,0,0};
    __pyx_defaults2 *__pyx_dynamic_args = __Pyx_CyFunction_Defaults(__pyx_defaults2, __pyx_self);
    values[2] = __pyx_dynamic_args->__pyx_arg_bruteforce;
    values[3] = ((PyObject *)((PyObject *)Py_None));
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__self)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__xi)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("find_simplex", 0, 2, 4, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1385; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
        case  2:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s__bruteforce);
          if (value) { values[2] = value; kw_args--; }
        }
        case  3:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s__tol);
          if (value) { values[3] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "find_simplex") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1385; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_self = values[0];
    __pyx_v_xi = values[1];
    __pyx_v_bruteforce = values[2];
    __pyx_v_tol = values[3];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("find_simplex", 0, 2, 4, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1385; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.find_simplex", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_32find_simplex(__pyx_self, __pyx_v_self, __pyx_v_xi, __pyx_v_bruteforce, __pyx_v_tol);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_32find_simplex(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_xi, PyObject *__pyx_v_bruteforce, PyObject *__pyx_v_tol) {
  __pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t __pyx_v_info;
  int __pyx_v_isimplex;
  double __pyx_v_c[NPY_MAXDIMS];
  double __pyx_v_eps;
  double __pyx_v_eps_broad;
  int __pyx_v_start;
  int __pyx_v_k;
  PyArrayObject *__pyx_v_x = 0;
  PyArrayObject *__pyx_v_out_ = 0;
  PyObject *__pyx_v_xi_shape = NULL;
  PyObject *__pyx_v_out = NULL;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_out_;
  __Pyx_Buffer __pyx_pybuffer_out_;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_x;
  __Pyx_Buffer __pyx_pybuffer_x;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  PyArrayObject *__pyx_t_6 = NULL;
  int __pyx_t_7;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  PyObject *__pyx_t_10 = NULL;
  double __pyx_t_11;
  PyObject *__pyx_t_12 = NULL;
  PyArrayObject *__pyx_t_13 = NULL;
  npy_intp __pyx_t_14;
  int __pyx_t_15;
  int __pyx_t_16;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("find_simplex", 0);
  __Pyx_INCREF(__pyx_v_xi);
  __pyx_pybuffer_x.pybuffer.buf = NULL;
  __pyx_pybuffer_x.refcount = 0;
  __pyx_pybuffernd_x.data = NULL;
  __pyx_pybuffernd_x.rcbuffer = &__pyx_pybuffer_x;
  __pyx_pybuffer_out_.pybuffer.buf = NULL;
  __pyx_pybuffer_out_.refcount = 0;
  __pyx_pybuffernd_out_.data = NULL;
  __pyx_pybuffernd_out_.rcbuffer = &__pyx_pybuffer_out_;

  
  __pyx_t_1 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1427; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__asanyarray); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1427; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1427; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_v_xi);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_xi);
  __Pyx_GIVEREF(__pyx_v_xi);
  __pyx_t_3 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_t_1), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1427; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_v_xi);
  __pyx_v_xi = __pyx_t_3;
  __pyx_t_3 = 0;

  
  __pyx_t_3 = PyObject_GetAttr(__pyx_v_xi, __pyx_n_s__shape); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1429; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_1 = __Pyx_GetItemInt(__pyx_t_3, -1, sizeof(long), PyInt_FromLong); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1429; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s__ndim); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1429; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyObject_RichCompare(__pyx_t_1, __pyx_t_3, Py_NE); __Pyx_XGOTREF(__pyx_t_2); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1429; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_2); if (unlikely(__pyx_t_4 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1429; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if (__pyx_t_4) {

    
    __pyx_t_2 = PyObject_Call(__pyx_builtin_ValueError, ((PyObject *)__pyx_k_tuple_28), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1430; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_Raise(__pyx_t_2, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1430; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    goto __pyx_L3;
  }
  __pyx_L3:;

  
  __pyx_t_2 = PyObject_GetAttr(__pyx_v_xi, __pyx_n_s__shape); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1432; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_v_xi_shape = __pyx_t_2;
  __pyx_t_2 = 0;

  
  __pyx_t_2 = PyObject_GetAttr(__pyx_v_xi, __pyx_n_s__reshape); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1433; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1433; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_1 = PyObject_GetAttr(__pyx_t_3, __pyx_n_s__prod); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1433; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_GetAttr(__pyx_v_xi, __pyx_n_s__shape); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1433; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_5 = __Pyx_PySequence_GetSlice(__pyx_t_3, 0, -1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1433; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1433; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_5 = 0;
  __pyx_t_5 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_t_3), NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1433; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_3)); __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_GetAttr(__pyx_v_xi, __pyx_n_s__shape); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1433; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_1 = __Pyx_GetItemInt(__pyx_t_3, -1, sizeof(long), PyInt_FromLong); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1433; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyTuple_New(2); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1433; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_5 = 0;
  __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_t_3), NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1433; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_3)); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_v_xi);
  __pyx_v_xi = __pyx_t_1;
  __pyx_t_1 = 0;

  
  __pyx_t_1 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1434; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__ascontiguousarray); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1434; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_xi, __pyx_n_s__astype); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1434; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1434; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_5 = PyObject_GetAttr(__pyx_t_2, __pyx_n_s__double); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1434; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1434; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_5 = 0;
  __pyx_t_5 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1434; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1434; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_5 = 0;
  __pyx_t_5 = PyObject_Call(__pyx_t_3, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1434; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  if (!(likely(((__pyx_t_5) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_5, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1434; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_6 = ((PyArrayObject *)__pyx_t_5);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_x.rcbuffer->pybuffer);
    __pyx_t_7 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_x.rcbuffer->pybuffer, (PyObject*)__pyx_t_6, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack);
    if (unlikely(__pyx_t_7 < 0)) {
      PyErr_Fetch(&__pyx_t_8, &__pyx_t_9, &__pyx_t_10);
      if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_x.rcbuffer->pybuffer, (PyObject*)__pyx_v_x, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack) == -1)) {
        Py_XDECREF(__pyx_t_8); Py_XDECREF(__pyx_t_9); Py_XDECREF(__pyx_t_10);
        __Pyx_RaiseBufferFallbackError();
      } else {
        PyErr_Restore(__pyx_t_8, __pyx_t_9, __pyx_t_10);
      }
    }
    __pyx_pybuffernd_x.diminfo[0].strides = __pyx_pybuffernd_x.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_x.diminfo[0].shape = __pyx_pybuffernd_x.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_x.diminfo[1].strides = __pyx_pybuffernd_x.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_x.diminfo[1].shape = __pyx_pybuffernd_x.rcbuffer->pybuffer.shape[1];
    if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1434; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_6 = 0;
  __pyx_v_x = ((PyArrayObject *)__pyx_t_5);
  __pyx_t_5 = 0;

  
  __pyx_v_start = 0;

  
  __pyx_t_4 = (__pyx_v_tol == Py_None);
  if (__pyx_t_4) {

    
    __pyx_t_5 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1439; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_2 = PyObject_GetAttr(__pyx_t_5, __pyx_n_s__finfo); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1439; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_5 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1439; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_3 = PyObject_GetAttr(__pyx_t_5, __pyx_n_s__double); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1439; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1439; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_t_5), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1439; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(((PyObject *)__pyx_t_5)); __pyx_t_5 = 0;
    __pyx_t_5 = PyObject_GetAttr(__pyx_t_3, __pyx_n_s__eps); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1439; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = PyNumber_Multiply(__pyx_int_100, __pyx_t_5); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1439; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_11 = __pyx_PyFloat_AsDouble(__pyx_t_3); if (unlikely((__pyx_t_11 == (double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1439; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_v_eps = __pyx_t_11;
    goto __pyx_L4;
  }
   {

    
    __pyx_t_11 = __pyx_PyFloat_AsDouble(__pyx_v_tol); if (unlikely((__pyx_t_11 == (double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1441; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_v_eps = __pyx_t_11;
  }
  __pyx_L4:;

  
  __pyx_t_3 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1442; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_5 = PyObject_GetAttr(__pyx_t_3, __pyx_n_s__sqrt); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1442; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyFloat_FromDouble(__pyx_v_eps); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1442; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1442; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_Call(__pyx_t_5, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1442; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  __pyx_t_11 = __pyx_PyFloat_AsDouble(__pyx_t_3); if (unlikely((__pyx_t_11 == (double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1442; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_eps_broad = __pyx_t_11;

  
  __pyx_t_3 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1443; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_3, __pyx_n_s__zeros); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1443; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_GetAttr(__pyx_v_xi, __pyx_n_s__shape); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1443; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_5 = __Pyx_GetItemInt(__pyx_t_3, 0, sizeof(long), PyInt_FromLong); if (!__pyx_t_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1443; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1443; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_5 = 0;
  __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1443; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_5, 0, ((PyObject *)__pyx_t_3));
  __Pyx_GIVEREF(((PyObject *)__pyx_t_3));
  __pyx_t_3 = 0;
  __pyx_t_3 = PyDict_New(); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1443; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(((PyObject *)__pyx_t_3));
  __pyx_t_1 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1443; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_12 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__intc); if (unlikely(!__pyx_t_12)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1443; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_12);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (PyDict_SetItem(__pyx_t_3, ((PyObject *)__pyx_n_s__dtype), __pyx_t_12) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1443; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
  __pyx_t_12 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_t_5), ((PyObject *)__pyx_t_3)); if (unlikely(!__pyx_t_12)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1443; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_12);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_5)); __pyx_t_5 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_3)); __pyx_t_3 = 0;
  __pyx_v_out = __pyx_t_12;
  __pyx_t_12 = 0;

  
  if (!(likely(((__pyx_v_out) == Py_None) || likely(__Pyx_TypeTest(__pyx_v_out, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1444; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_13 = ((PyArrayObject *)__pyx_v_out);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_out_.rcbuffer->pybuffer);
    __pyx_t_7 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_out_.rcbuffer->pybuffer, (PyObject*)__pyx_t_13, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 1, 0, __pyx_stack);
    if (unlikely(__pyx_t_7 < 0)) {
      PyErr_Fetch(&__pyx_t_10, &__pyx_t_9, &__pyx_t_8);
      if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_out_.rcbuffer->pybuffer, (PyObject*)__pyx_v_out_, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 1, 0, __pyx_stack) == -1)) {
        Py_XDECREF(__pyx_t_10); Py_XDECREF(__pyx_t_9); Py_XDECREF(__pyx_t_8);
        __Pyx_RaiseBufferFallbackError();
      } else {
        PyErr_Restore(__pyx_t_10, __pyx_t_9, __pyx_t_8);
      }
    }
    __pyx_pybuffernd_out_.diminfo[0].strides = __pyx_pybuffernd_out_.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_out_.diminfo[0].shape = __pyx_pybuffernd_out_.rcbuffer->pybuffer.shape[0];
    if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1444; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_13 = 0;
  __Pyx_INCREF(__pyx_v_out);
  __pyx_v_out_ = ((PyArrayObject *)__pyx_v_out);

  
  __pyx_t_7 = __pyx_f_5scipy_7spatial_5qhull__get_delaunay_info((&__pyx_v_info), __pyx_v_self, 1, 0); if (unlikely(__pyx_t_7 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1445; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_v_bruteforce); if (unlikely(__pyx_t_4 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1447; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__pyx_t_4) {

    
    {
        #ifdef WITH_THREAD
        PyThreadState *_save = NULL;
        #endif
        Py_UNBLOCK_THREADS
         {

          
          __pyx_t_14 = (__pyx_v_x->dimensions[0]);
          for (__pyx_t_7 = 0; __pyx_t_7 < __pyx_t_14; __pyx_t_7+=1) {
            __pyx_v_k = __pyx_t_7;

            
            __pyx_v_isimplex = __pyx_f_5scipy_7spatial_5qhull__find_simplex_bruteforce((&__pyx_v_info), __pyx_v_c, (((double *)__pyx_v_x->data) + (__pyx_v_info.ndim * __pyx_v_k)), __pyx_v_eps, __pyx_v_eps_broad);

            
            __pyx_t_15 = __pyx_v_k;
            if (__pyx_t_15 < 0) __pyx_t_15 += __pyx_pybuffernd_out_.diminfo[0].shape;
            *__Pyx_BufPtrStrided1d(npy_int *, __pyx_pybuffernd_out_.rcbuffer->pybuffer.buf, __pyx_t_15, __pyx_pybuffernd_out_.diminfo[0].strides) = __pyx_v_isimplex;
          }
        }

        
         {
          Py_BLOCK_THREADS
        }
    }
    goto __pyx_L5;
  }
   {

    
    {
        #ifdef WITH_THREAD
        PyThreadState *_save = NULL;
        #endif
        Py_UNBLOCK_THREADS
         {

          
          __pyx_t_14 = (__pyx_v_x->dimensions[0]);
          for (__pyx_t_7 = 0; __pyx_t_7 < __pyx_t_14; __pyx_t_7+=1) {
            __pyx_v_k = __pyx_t_7;

            
            __pyx_v_isimplex = __pyx_f_5scipy_7spatial_5qhull__find_simplex((&__pyx_v_info), __pyx_v_c, (((double *)__pyx_v_x->data) + (__pyx_v_info.ndim * __pyx_v_k)), (&__pyx_v_start), __pyx_v_eps, __pyx_v_eps_broad);

            
            __pyx_t_16 = __pyx_v_k;
            if (__pyx_t_16 < 0) __pyx_t_16 += __pyx_pybuffernd_out_.diminfo[0].shape;
            *__Pyx_BufPtrStrided1d(npy_int *, __pyx_pybuffernd_out_.rcbuffer->pybuffer.buf, __pyx_t_16, __pyx_pybuffernd_out_.diminfo[0].strides) = __pyx_v_isimplex;
          }
        }

        
         {
          Py_BLOCK_THREADS
        }
    }
  }
  __pyx_L5:;

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_12 = PyObject_GetAttr(__pyx_v_out, __pyx_n_s__reshape); if (unlikely(!__pyx_t_12)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1463; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_12);
  __pyx_t_3 = __Pyx_PySequence_GetSlice(__pyx_v_xi_shape, 0, -1); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1463; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1463; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_Call(__pyx_t_12, ((PyObject *)__pyx_t_5), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1463; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_5)); __pyx_t_5 = 0;
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_12);
  { PyObject *__pyx_type, *__pyx_value, *__pyx_tb;
    __Pyx_ErrFetch(&__pyx_type, &__pyx_value, &__pyx_tb);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_out_.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_x.rcbuffer->pybuffer);
  __Pyx_ErrRestore(__pyx_type, __pyx_value, __pyx_tb);}
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.find_simplex", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  goto __pyx_L2;
  __pyx_L0:;
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_out_.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_x.rcbuffer->pybuffer);
  __pyx_L2:;
  __Pyx_XDECREF((PyObject *)__pyx_v_x);
  __Pyx_XDECREF((PyObject *)__pyx_v_out_);
  __Pyx_XDECREF(__pyx_v_xi_shape);
  __Pyx_XDECREF(__pyx_v_out);
  __Pyx_XDECREF(__pyx_v_xi);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_35plane_distance(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static char __pyx_doc_5scipy_7spatial_5qhull_8Delaunay_34plane_distance[] = "\n        plane_distance(self, xi)\n\n        Compute hyperplane distances to the point `xi` from all simplices.\n\n        ";
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_35plane_distance = {__Pyx_NAMESTR("plane_distance"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_35plane_distance, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(__pyx_doc_5scipy_7spatial_5qhull_8Delaunay_34plane_distance)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_35plane_distance(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v_xi = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("plane_distance (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s__self,&__pyx_n_s__xi,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__self)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__xi)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("plane_distance", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1466; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "plane_distance") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1466; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_self = values[0];
    __pyx_v_xi = values[1];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("plane_distance", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1466; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.plane_distance", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_34plane_distance(__pyx_self, __pyx_v_self, __pyx_v_xi);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_34plane_distance(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_xi) {
  PyArrayObject *__pyx_v_x = 0;
  PyArrayObject *__pyx_v_out_ = 0;
  __pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t __pyx_v_info;
  double __pyx_v_z[(NPY_MAXDIMS + 1)];
  int __pyx_v_i;
  int __pyx_v_j;
  PyObject *__pyx_v_xi_shape = NULL;
  PyObject *__pyx_v_out = NULL;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_out_;
  __Pyx_Buffer __pyx_pybuffer_out_;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_x;
  __Pyx_Buffer __pyx_pybuffer_x;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  PyArrayObject *__pyx_t_6 = NULL;
  int __pyx_t_7;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  PyObject *__pyx_t_10 = NULL;
  PyObject *__pyx_t_11 = NULL;
  PyArrayObject *__pyx_t_12 = NULL;
  npy_intp __pyx_t_13;
  int __pyx_t_14;
  int __pyx_t_15;
  int __pyx_t_16;
  int __pyx_t_17;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("plane_distance", 0);
  __Pyx_INCREF(__pyx_v_xi);
  __pyx_pybuffer_x.pybuffer.buf = NULL;
  __pyx_pybuffer_x.refcount = 0;
  __pyx_pybuffernd_x.data = NULL;
  __pyx_pybuffernd_x.rcbuffer = &__pyx_pybuffer_x;
  __pyx_pybuffer_out_.pybuffer.buf = NULL;
  __pyx_pybuffer_out_.refcount = 0;
  __pyx_pybuffernd_out_.data = NULL;
  __pyx_pybuffernd_out_.rcbuffer = &__pyx_pybuffer_out_;

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_xi, __pyx_n_s__shape); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1479; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_GetItemInt(__pyx_t_1, -1, sizeof(long), PyInt_FromLong); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1479; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s__ndim); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1479; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = PyObject_RichCompare(__pyx_t_2, __pyx_t_1, Py_NE); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1479; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_4 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1479; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (__pyx_t_4) {

    
    __pyx_t_3 = PyObject_Call(__pyx_builtin_ValueError, ((PyObject *)__pyx_k_tuple_30), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1480; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_Raise(__pyx_t_3, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1480; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    goto __pyx_L3;
  }
  __pyx_L3:;

  
  __pyx_t_3 = PyObject_GetAttr(__pyx_v_xi, __pyx_n_s__shape); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1483; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_v_xi_shape = __pyx_t_3;
  __pyx_t_3 = 0;

  
  __pyx_t_3 = PyObject_GetAttr(__pyx_v_xi, __pyx_n_s__reshape); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1484; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_1 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1484; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__prod); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1484; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_xi, __pyx_n_s__shape); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1484; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_5 = __Pyx_PySequence_GetSlice(__pyx_t_1, 0, -1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1484; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1484; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_5 = 0;
  __pyx_t_5 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_t_1), NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1484; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_xi, __pyx_n_s__shape); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1484; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_GetItemInt(__pyx_t_1, -1, sizeof(long), PyInt_FromLong); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1484; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1484; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_5 = 0;
  __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_Call(__pyx_t_3, ((PyObject *)__pyx_t_1), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1484; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_v_xi);
  __pyx_v_xi = __pyx_t_2;
  __pyx_t_2 = 0;

  
  __pyx_t_2 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1485; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyObject_GetAttr(__pyx_t_2, __pyx_n_s__ascontiguousarray); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1485; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_GetAttr(__pyx_v_xi, __pyx_n_s__astype); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1485; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1485; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_5 = PyObject_GetAttr(__pyx_t_3, __pyx_n_s__double); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1485; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1485; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_5 = 0;
  __pyx_t_5 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_t_3), NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1485; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_3)); __pyx_t_3 = 0;
  __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1485; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_5 = 0;
  __pyx_t_5 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_t_3), NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1485; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_3)); __pyx_t_3 = 0;
  if (!(likely(((__pyx_t_5) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_5, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1485; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_6 = ((PyArrayObject *)__pyx_t_5);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_x.rcbuffer->pybuffer);
    __pyx_t_7 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_x.rcbuffer->pybuffer, (PyObject*)__pyx_t_6, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack);
    if (unlikely(__pyx_t_7 < 0)) {
      PyErr_Fetch(&__pyx_t_8, &__pyx_t_9, &__pyx_t_10);
      if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_x.rcbuffer->pybuffer, (PyObject*)__pyx_v_x, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack) == -1)) {
        Py_XDECREF(__pyx_t_8); Py_XDECREF(__pyx_t_9); Py_XDECREF(__pyx_t_10);
        __Pyx_RaiseBufferFallbackError();
      } else {
        PyErr_Restore(__pyx_t_8, __pyx_t_9, __pyx_t_10);
      }
    }
    __pyx_pybuffernd_x.diminfo[0].strides = __pyx_pybuffernd_x.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_x.diminfo[0].shape = __pyx_pybuffernd_x.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_x.diminfo[1].strides = __pyx_pybuffernd_x.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_x.diminfo[1].shape = __pyx_pybuffernd_x.rcbuffer->pybuffer.shape[1];
    if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1485; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_6 = 0;
  __pyx_v_x = ((PyArrayObject *)__pyx_t_5);
  __pyx_t_5 = 0;

  
  __pyx_t_7 = __pyx_f_5scipy_7spatial_5qhull__get_delaunay_info((&__pyx_v_info), __pyx_v_self, 0, 0); if (unlikely(__pyx_t_7 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1487; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_t_5 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1489; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_3 = PyObject_GetAttr(__pyx_t_5, __pyx_n_s__zeros); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1489; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyInt_to_py_Py_intptr_t((__pyx_v_x->dimensions[0])); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1489; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_1 = PyInt_FromLong(__pyx_v_info.nsimplex); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1489; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1489; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_5 = 0;
  __pyx_t_1 = 0;
  __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1489; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_1, 0, ((PyObject *)__pyx_t_2));
  __Pyx_GIVEREF(((PyObject *)__pyx_t_2));
  __pyx_t_2 = 0;
  __pyx_t_2 = PyDict_New(); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1489; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(((PyObject *)__pyx_t_2));
  __pyx_t_5 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1489; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_11 = PyObject_GetAttr(__pyx_t_5, __pyx_n_s__double); if (unlikely(!__pyx_t_11)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1489; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_11);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  if (PyDict_SetItem(__pyx_t_2, ((PyObject *)__pyx_n_s__dtype), __pyx_t_11) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1489; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
  __pyx_t_11 = PyObject_Call(__pyx_t_3, ((PyObject *)__pyx_t_1), ((PyObject *)__pyx_t_2)); if (unlikely(!__pyx_t_11)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1489; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_11);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  __pyx_v_out = __pyx_t_11;
  __pyx_t_11 = 0;

  
  if (!(likely(((__pyx_v_out) == Py_None) || likely(__Pyx_TypeTest(__pyx_v_out, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1490; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_12 = ((PyArrayObject *)__pyx_v_out);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_out_.rcbuffer->pybuffer);
    __pyx_t_7 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_out_.rcbuffer->pybuffer, (PyObject*)__pyx_t_12, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 2, 0, __pyx_stack);
    if (unlikely(__pyx_t_7 < 0)) {
      PyErr_Fetch(&__pyx_t_10, &__pyx_t_9, &__pyx_t_8);
      if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_out_.rcbuffer->pybuffer, (PyObject*)__pyx_v_out_, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES| PyBUF_WRITABLE, 2, 0, __pyx_stack) == -1)) {
        Py_XDECREF(__pyx_t_10); Py_XDECREF(__pyx_t_9); Py_XDECREF(__pyx_t_8);
        __Pyx_RaiseBufferFallbackError();
      } else {
        PyErr_Restore(__pyx_t_10, __pyx_t_9, __pyx_t_8);
      }
    }
    __pyx_pybuffernd_out_.diminfo[0].strides = __pyx_pybuffernd_out_.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_out_.diminfo[0].shape = __pyx_pybuffernd_out_.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_out_.diminfo[1].strides = __pyx_pybuffernd_out_.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_out_.diminfo[1].shape = __pyx_pybuffernd_out_.rcbuffer->pybuffer.shape[1];
    if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1490; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_12 = 0;
  __Pyx_INCREF(__pyx_v_out);
  __pyx_v_out_ = ((PyArrayObject *)__pyx_v_out);

  
  {
      #ifdef WITH_THREAD
      PyThreadState *_save = NULL;
      #endif
      Py_UNBLOCK_THREADS
       {

        
        __pyx_t_13 = (__pyx_v_x->dimensions[0]);
        for (__pyx_t_7 = 0; __pyx_t_7 < __pyx_t_13; __pyx_t_7+=1) {
          __pyx_v_i = __pyx_t_7;

          
          __pyx_t_14 = __pyx_v_info.nsimplex;
          for (__pyx_t_15 = 0; __pyx_t_15 < __pyx_t_14; __pyx_t_15+=1) {
            __pyx_v_j = __pyx_t_15;

            
            __pyx_f_5scipy_7spatial_5qhull__lift_point((&__pyx_v_info), (((double *)__pyx_v_x->data) + (__pyx_v_info.ndim * __pyx_v_i)), __pyx_v_z);

            
            __pyx_t_16 = __pyx_v_i;
            __pyx_t_17 = __pyx_v_j;
            if (__pyx_t_16 < 0) __pyx_t_16 += __pyx_pybuffernd_out_.diminfo[0].shape;
            if (__pyx_t_17 < 0) __pyx_t_17 += __pyx_pybuffernd_out_.diminfo[1].shape;
            *__Pyx_BufPtrStrided2d(__pyx_t_5numpy_double_t *, __pyx_pybuffernd_out_.rcbuffer->pybuffer.buf, __pyx_t_16, __pyx_pybuffernd_out_.diminfo[0].strides, __pyx_t_17, __pyx_pybuffernd_out_.diminfo[1].strides) = __pyx_f_5scipy_7spatial_5qhull__distplane((&__pyx_v_info), __pyx_v_j, __pyx_v_z);
          }
        }
      }

      
       {
        Py_BLOCK_THREADS
      }
  }

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_11 = PyObject_GetAttr(__pyx_v_out, __pyx_n_s__reshape); if (unlikely(!__pyx_t_11)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1498; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_11);
  __pyx_t_2 = __Pyx_PySequence_GetSlice(__pyx_v_xi_shape, 0, -1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1498; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s__nsimplex); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1498; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1498; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyNumber_Add(__pyx_t_2, ((PyObject *)__pyx_t_3)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1498; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_3)); __pyx_t_3 = 0;
  __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1498; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_Call(__pyx_t_11, ((PyObject *)__pyx_t_3), NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1498; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_3)); __pyx_t_3 = 0;
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_11);
  { PyObject *__pyx_type, *__pyx_value, *__pyx_tb;
    __Pyx_ErrFetch(&__pyx_type, &__pyx_value, &__pyx_tb);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_out_.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_x.rcbuffer->pybuffer);
  __Pyx_ErrRestore(__pyx_type, __pyx_value, __pyx_tb);}
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.plane_distance", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  goto __pyx_L2;
  __pyx_L0:;
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_out_.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_x.rcbuffer->pybuffer);
  __pyx_L2:;
  __Pyx_XDECREF((PyObject *)__pyx_v_x);
  __Pyx_XDECREF((PyObject *)__pyx_v_out_);
  __Pyx_XDECREF(__pyx_v_xi_shape);
  __Pyx_XDECREF(__pyx_v_out);
  __Pyx_XDECREF(__pyx_v_xi);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_37lift_points(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static char __pyx_doc_5scipy_7spatial_5qhull_8Delaunay_36lift_points[] = "\n        lift_points(self, x)\n\n        Lift points to the Qhull paraboloid.\n\n        ";
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_37lift_points = {__Pyx_NAMESTR("lift_points"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_37lift_points, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(__pyx_doc_5scipy_7spatial_5qhull_8Delaunay_36lift_points)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_8Delaunay_37lift_points(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v_x = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("lift_points (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s__self,&__pyx_n_s__x,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__self)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__x)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("lift_points", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1500; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "lift_points") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1500; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_self = values[0];
    __pyx_v_x = values[1];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("lift_points", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1500; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.lift_points", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_36lift_points(__pyx_self, __pyx_v_self, __pyx_v_x);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_8Delaunay_36lift_points(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_x) {
  PyObject *__pyx_v_z = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("lift_points", 0);

  
  __pyx_t_1 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1507; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__zeros); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1507; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_x, __pyx_n_s__shape); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1507; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = __Pyx_PySequence_GetSlice(__pyx_t_1, 0, -1); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1507; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_x, __pyx_n_s__shape); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1507; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_4 = __Pyx_GetItemInt(__pyx_t_1, -1, sizeof(long), PyInt_FromLong); if (!__pyx_t_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1507; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyNumber_Add(__pyx_t_4, __pyx_int_1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1507; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1507; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyNumber_Add(__pyx_t_3, ((PyObject *)__pyx_t_4)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1507; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_4)); __pyx_t_4 = 0;
  __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1507; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1507; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(((PyObject *)__pyx_t_1));
  __pyx_t_3 = __Pyx_GetName(__pyx_m, __pyx_n_s__np); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1507; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_5 = PyObject_GetAttr(__pyx_t_3, __pyx_n_s__double); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1507; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (PyDict_SetItem(__pyx_t_1, ((PyObject *)__pyx_n_s__dtype), __pyx_t_5) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1507; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_t_4), ((PyObject *)__pyx_t_1)); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1507; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_4)); __pyx_t_4 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;
  __pyx_v_z = __pyx_t_5;
  __pyx_t_5 = 0;

  
  if (PyObject_SetItem(__pyx_v_z, ((PyObject *)__pyx_k_tuple_32), __pyx_v_x) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1508; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_t_5 = PyNumber_Power(__pyx_v_x, __pyx_int_2, Py_None); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1509; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_1 = PyObject_GetAttr(__pyx_t_5, __pyx_n_s__sum); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1509; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = PyDict_New(); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1509; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(((PyObject *)__pyx_t_5));
  if (PyDict_SetItem(__pyx_t_5, ((PyObject *)__pyx_n_s__axis), __pyx_int_neg_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1509; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_4 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_empty_tuple), ((PyObject *)__pyx_t_5)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1509; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_5)); __pyx_t_5 = 0;
  if (PyObject_SetItem(__pyx_v_z, ((PyObject *)__pyx_k_tuple_33), __pyx_t_4) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1509; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  
  __Pyx_INCREF(((PyObject *)__pyx_k_tuple_34));
  __pyx_t_6 = __pyx_k_tuple_34;
  __pyx_t_4 = PyObject_GetItem(__pyx_v_z, ((PyObject *)__pyx_t_6)); if (!__pyx_t_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1510; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s__paraboloid_scale); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1510; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_1 = PyNumber_InPlaceMultiply(__pyx_t_4, __pyx_t_5); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1510; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  if (PyObject_SetItem(__pyx_v_z, ((PyObject *)__pyx_t_6), __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1510; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_6)); __pyx_t_6 = 0;

  
  __Pyx_INCREF(((PyObject *)__pyx_k_tuple_35));
  __pyx_t_6 = __pyx_k_tuple_35;
  __pyx_t_1 = PyObject_GetItem(__pyx_v_z, ((PyObject *)__pyx_t_6)); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1511; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_5 = PyObject_GetAttr(__pyx_v_self, __pyx_n_s__paraboloid_shift); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1511; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_4 = PyNumber_InPlaceAdd(__pyx_t_1, __pyx_t_5); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1511; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  if (PyObject_SetItem(__pyx_v_z, ((PyObject *)__pyx_t_6), __pyx_t_4) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1511; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_6)); __pyx_t_6 = 0;

  
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(__pyx_v_z);
  __pyx_r = __pyx_v_z;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(((PyObject *)__pyx_t_6));
  __Pyx_AddTraceback("scipy.spatial.qhull.Delaunay.lift_points", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_z);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_5scipy_7spatial_5qhull_3tsearch(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static char __pyx_doc_5scipy_7spatial_5qhull_2tsearch[] = "\n    tsearch(tri, xi)\n\n    Find simplices containing the given points. This function does the\n    same thing as `Delaunay.find_simplex`.\n\n    .. versionadded:: 0.9\n\n    See Also\n    --------\n    Delaunay.find_simplex\n\n    ";
static PyMethodDef __pyx_mdef_5scipy_7spatial_5qhull_3tsearch = {__Pyx_NAMESTR("tsearch"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_3tsearch, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(__pyx_doc_5scipy_7spatial_5qhull_2tsearch)};
static PyObject *__pyx_pw_5scipy_7spatial_5qhull_3tsearch(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_tri = 0;
  PyObject *__pyx_v_xi = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("tsearch (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s__tri,&__pyx_n_s__xi,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__tri)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__xi)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("tsearch", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1515; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "tsearch") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1515; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_tri = values[0];
    __pyx_v_xi = values[1];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("tsearch", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1515; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("scipy.spatial.qhull.tsearch", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_5scipy_7spatial_5qhull_2tsearch(__pyx_self, __pyx_v_tri, __pyx_v_xi);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static PyObject *__pyx_pf_5scipy_7spatial_5qhull_2tsearch(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_tri, PyObject *__pyx_v_xi) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("tsearch", 0);

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_tri, __pyx_n_s__find_simplex); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1529; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1529; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_xi);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_xi);
  __Pyx_GIVEREF(__pyx_v_xi);
  __pyx_t_3 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1529; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("scipy.spatial.qhull.tsearch", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static int __pyx_f_5scipy_7spatial_5qhull__get_delaunay_info(__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *__pyx_v_info, PyObject *__pyx_v_obj, int __pyx_v_compute_transform, int __pyx_v_compute_vertex_to_simplex) {
  PyArrayObject *__pyx_v_transform = 0;
  PyArrayObject *__pyx_v_vertex_to_simplex = 0;
  PyArrayObject *__pyx_v_points = 0;
  PyArrayObject *__pyx_v_vertices = 0;
  PyArrayObject *__pyx_v_neighbors = 0;
  PyArrayObject *__pyx_v_equations = 0;
  PyArrayObject *__pyx_v_min_bound = 0;
  PyArrayObject *__pyx_v_max_bound = 0;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_equations;
  __Pyx_Buffer __pyx_pybuffer_equations;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_max_bound;
  __Pyx_Buffer __pyx_pybuffer_max_bound;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_min_bound;
  __Pyx_Buffer __pyx_pybuffer_min_bound;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_neighbors;
  __Pyx_Buffer __pyx_pybuffer_neighbors;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_points;
  __Pyx_Buffer __pyx_pybuffer_points;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_transform;
  __Pyx_Buffer __pyx_pybuffer_transform;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_vertex_to_simplex;
  __Pyx_Buffer __pyx_pybuffer_vertex_to_simplex;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_vertices;
  __Pyx_Buffer __pyx_pybuffer_vertices;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyArrayObject *__pyx_t_2 = NULL;
  PyArrayObject *__pyx_t_3 = NULL;
  PyArrayObject *__pyx_t_4 = NULL;
  PyArrayObject *__pyx_t_5 = NULL;
  PyArrayObject *__pyx_t_6 = NULL;
  PyArrayObject *__pyx_t_7 = NULL;
  double __pyx_t_8;
  PyArrayObject *__pyx_t_9 = NULL;
  int __pyx_t_10;
  PyObject *__pyx_t_11 = NULL;
  PyObject *__pyx_t_12 = NULL;
  PyObject *__pyx_t_13 = NULL;
  PyArrayObject *__pyx_t_14 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("_get_delaunay_info", 0);
  __pyx_pybuffer_transform.pybuffer.buf = NULL;
  __pyx_pybuffer_transform.refcount = 0;
  __pyx_pybuffernd_transform.data = NULL;
  __pyx_pybuffernd_transform.rcbuffer = &__pyx_pybuffer_transform;
  __pyx_pybuffer_vertex_to_simplex.pybuffer.buf = NULL;
  __pyx_pybuffer_vertex_to_simplex.refcount = 0;
  __pyx_pybuffernd_vertex_to_simplex.data = NULL;
  __pyx_pybuffernd_vertex_to_simplex.rcbuffer = &__pyx_pybuffer_vertex_to_simplex;
  __pyx_pybuffer_points.pybuffer.buf = NULL;
  __pyx_pybuffer_points.refcount = 0;
  __pyx_pybuffernd_points.data = NULL;
  __pyx_pybuffernd_points.rcbuffer = &__pyx_pybuffer_points;
  __pyx_pybuffer_vertices.pybuffer.buf = NULL;
  __pyx_pybuffer_vertices.refcount = 0;
  __pyx_pybuffernd_vertices.data = NULL;
  __pyx_pybuffernd_vertices.rcbuffer = &__pyx_pybuffer_vertices;
  __pyx_pybuffer_neighbors.pybuffer.buf = NULL;
  __pyx_pybuffer_neighbors.refcount = 0;
  __pyx_pybuffernd_neighbors.data = NULL;
  __pyx_pybuffernd_neighbors.rcbuffer = &__pyx_pybuffer_neighbors;
  __pyx_pybuffer_equations.pybuffer.buf = NULL;
  __pyx_pybuffer_equations.refcount = 0;
  __pyx_pybuffernd_equations.data = NULL;
  __pyx_pybuffernd_equations.rcbuffer = &__pyx_pybuffer_equations;
  __pyx_pybuffer_min_bound.pybuffer.buf = NULL;
  __pyx_pybuffer_min_bound.refcount = 0;
  __pyx_pybuffernd_min_bound.data = NULL;
  __pyx_pybuffernd_min_bound.rcbuffer = &__pyx_pybuffer_min_bound;
  __pyx_pybuffer_max_bound.pybuffer.buf = NULL;
  __pyx_pybuffer_max_bound.refcount = 0;
  __pyx_pybuffernd_max_bound.data = NULL;
  __pyx_pybuffernd_max_bound.rcbuffer = &__pyx_pybuffer_max_bound;

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_obj, __pyx_n_s__points); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1542; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (!(likely(((__pyx_t_1) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_1, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1542; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_2 = ((PyArrayObject *)__pyx_t_1);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_points.rcbuffer->pybuffer, (PyObject*)__pyx_t_2, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack) == -1)) {
      __pyx_v_points = ((PyArrayObject *)Py_None); __Pyx_INCREF(Py_None); __pyx_pybuffernd_points.rcbuffer->pybuffer.buf = NULL;
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1542; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    } else {__pyx_pybuffernd_points.diminfo[0].strides = __pyx_pybuffernd_points.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_points.diminfo[0].shape = __pyx_pybuffernd_points.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_points.diminfo[1].strides = __pyx_pybuffernd_points.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_points.diminfo[1].shape = __pyx_pybuffernd_points.rcbuffer->pybuffer.shape[1];
    }
  }
  __pyx_t_2 = 0;
  __pyx_v_points = ((PyArrayObject *)__pyx_t_1);
  __pyx_t_1 = 0;

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_obj, __pyx_n_s__vertices); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1543; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (!(likely(((__pyx_t_1) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_1, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1543; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_3 = ((PyArrayObject *)__pyx_t_1);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer, (PyObject*)__pyx_t_3, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack) == -1)) {
      __pyx_v_vertices = ((PyArrayObject *)Py_None); __Pyx_INCREF(Py_None); __pyx_pybuffernd_vertices.rcbuffer->pybuffer.buf = NULL;
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1543; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    } else {__pyx_pybuffernd_vertices.diminfo[0].strides = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_vertices.diminfo[0].shape = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_vertices.diminfo[1].strides = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_vertices.diminfo[1].shape = __pyx_pybuffernd_vertices.rcbuffer->pybuffer.shape[1];
    }
  }
  __pyx_t_3 = 0;
  __pyx_v_vertices = ((PyArrayObject *)__pyx_t_1);
  __pyx_t_1 = 0;

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_obj, __pyx_n_s__neighbors); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1544; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (!(likely(((__pyx_t_1) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_1, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1544; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_4 = ((PyArrayObject *)__pyx_t_1);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_neighbors.rcbuffer->pybuffer, (PyObject*)__pyx_t_4, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack) == -1)) {
      __pyx_v_neighbors = ((PyArrayObject *)Py_None); __Pyx_INCREF(Py_None); __pyx_pybuffernd_neighbors.rcbuffer->pybuffer.buf = NULL;
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1544; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    } else {__pyx_pybuffernd_neighbors.diminfo[0].strides = __pyx_pybuffernd_neighbors.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_neighbors.diminfo[0].shape = __pyx_pybuffernd_neighbors.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_neighbors.diminfo[1].strides = __pyx_pybuffernd_neighbors.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_neighbors.diminfo[1].shape = __pyx_pybuffernd_neighbors.rcbuffer->pybuffer.shape[1];
    }
  }
  __pyx_t_4 = 0;
  __pyx_v_neighbors = ((PyArrayObject *)__pyx_t_1);
  __pyx_t_1 = 0;

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_obj, __pyx_n_s__equations); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1545; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (!(likely(((__pyx_t_1) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_1, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1545; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_5 = ((PyArrayObject *)__pyx_t_1);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_equations.rcbuffer->pybuffer, (PyObject*)__pyx_t_5, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack) == -1)) {
      __pyx_v_equations = ((PyArrayObject *)Py_None); __Pyx_INCREF(Py_None); __pyx_pybuffernd_equations.rcbuffer->pybuffer.buf = NULL;
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1545; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    } else {__pyx_pybuffernd_equations.diminfo[0].strides = __pyx_pybuffernd_equations.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_equations.diminfo[0].shape = __pyx_pybuffernd_equations.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_equations.diminfo[1].strides = __pyx_pybuffernd_equations.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_equations.diminfo[1].shape = __pyx_pybuffernd_equations.rcbuffer->pybuffer.shape[1];
    }
  }
  __pyx_t_5 = 0;
  __pyx_v_equations = ((PyArrayObject *)__pyx_t_1);
  __pyx_t_1 = 0;

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_obj, __pyx_n_s__min_bound); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1546; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (!(likely(((__pyx_t_1) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_1, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1546; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_6 = ((PyArrayObject *)__pyx_t_1);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_min_bound.rcbuffer->pybuffer, (PyObject*)__pyx_t_6, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES, 1, 0, __pyx_stack) == -1)) {
      __pyx_v_min_bound = ((PyArrayObject *)Py_None); __Pyx_INCREF(Py_None); __pyx_pybuffernd_min_bound.rcbuffer->pybuffer.buf = NULL;
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1546; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    } else {__pyx_pybuffernd_min_bound.diminfo[0].strides = __pyx_pybuffernd_min_bound.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_min_bound.diminfo[0].shape = __pyx_pybuffernd_min_bound.rcbuffer->pybuffer.shape[0];
    }
  }
  __pyx_t_6 = 0;
  __pyx_v_min_bound = ((PyArrayObject *)__pyx_t_1);
  __pyx_t_1 = 0;

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_obj, __pyx_n_s__max_bound); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1547; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (!(likely(((__pyx_t_1) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_1, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1547; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_7 = ((PyArrayObject *)__pyx_t_1);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_max_bound.rcbuffer->pybuffer, (PyObject*)__pyx_t_7, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES, 1, 0, __pyx_stack) == -1)) {
      __pyx_v_max_bound = ((PyArrayObject *)Py_None); __Pyx_INCREF(Py_None); __pyx_pybuffernd_max_bound.rcbuffer->pybuffer.buf = NULL;
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1547; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    } else {__pyx_pybuffernd_max_bound.diminfo[0].strides = __pyx_pybuffernd_max_bound.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_max_bound.diminfo[0].shape = __pyx_pybuffernd_max_bound.rcbuffer->pybuffer.shape[0];
    }
  }
  __pyx_t_7 = 0;
  __pyx_v_max_bound = ((PyArrayObject *)__pyx_t_1);
  __pyx_t_1 = 0;

  
  __pyx_v_info->ndim = (__pyx_v_points->dimensions[1]);

  
  __pyx_v_info->npoints = (__pyx_v_points->dimensions[0]);

  
  __pyx_v_info->nsimplex = (__pyx_v_vertices->dimensions[0]);

  
  __pyx_v_info->points = ((double *)__pyx_v_points->data);

  
  __pyx_v_info->vertices = ((int *)__pyx_v_vertices->data);

  
  __pyx_v_info->neighbors = ((int *)__pyx_v_neighbors->data);

  
  __pyx_v_info->equations = ((double *)__pyx_v_equations->data);

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_obj, __pyx_n_s__paraboloid_scale); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1556; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_8 = __pyx_PyFloat_AsDouble(__pyx_t_1); if (unlikely((__pyx_t_8 == (double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1556; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_info->paraboloid_scale = __pyx_t_8;

  
  __pyx_t_1 = PyObject_GetAttr(__pyx_v_obj, __pyx_n_s__paraboloid_shift); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1557; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_8 = __pyx_PyFloat_AsDouble(__pyx_t_1); if (unlikely((__pyx_t_8 == (double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1557; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_info->paraboloid_shift = __pyx_t_8;

  
  if (__pyx_v_compute_transform) {

    
    __pyx_t_1 = PyObject_GetAttr(__pyx_v_obj, __pyx_n_s__transform); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1559; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    if (!(likely(((__pyx_t_1) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_1, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1559; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_t_9 = ((PyArrayObject *)__pyx_t_1);
    {
      __Pyx_BufFmt_StackElem __pyx_stack[1];
      __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_transform.rcbuffer->pybuffer);
      __pyx_t_10 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_transform.rcbuffer->pybuffer, (PyObject*)__pyx_t_9, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES, 3, 0, __pyx_stack);
      if (unlikely(__pyx_t_10 < 0)) {
        PyErr_Fetch(&__pyx_t_11, &__pyx_t_12, &__pyx_t_13);
        if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_transform.rcbuffer->pybuffer, (PyObject*)__pyx_v_transform, &__Pyx_TypeInfo_nn___pyx_t_5numpy_double_t, PyBUF_FORMAT| PyBUF_STRIDES, 3, 0, __pyx_stack) == -1)) {
          Py_XDECREF(__pyx_t_11); Py_XDECREF(__pyx_t_12); Py_XDECREF(__pyx_t_13);
          __Pyx_RaiseBufferFallbackError();
        } else {
          PyErr_Restore(__pyx_t_11, __pyx_t_12, __pyx_t_13);
        }
      }
      __pyx_pybuffernd_transform.diminfo[0].strides = __pyx_pybuffernd_transform.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_transform.diminfo[0].shape = __pyx_pybuffernd_transform.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_transform.diminfo[1].strides = __pyx_pybuffernd_transform.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_transform.diminfo[1].shape = __pyx_pybuffernd_transform.rcbuffer->pybuffer.shape[1]; __pyx_pybuffernd_transform.diminfo[2].strides = __pyx_pybuffernd_transform.rcbuffer->pybuffer.strides[2]; __pyx_pybuffernd_transform.diminfo[2].shape = __pyx_pybuffernd_transform.rcbuffer->pybuffer.shape[2];
      if (unlikely(__pyx_t_10 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1559; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_t_9 = 0;
    __pyx_v_transform = ((PyArrayObject *)__pyx_t_1);
    __pyx_t_1 = 0;

    
    __pyx_v_info->transform = ((double *)__pyx_v_transform->data);
    goto __pyx_L3;
  }
   {

    
    __pyx_v_info->transform = NULL;
  }
  __pyx_L3:;

  
  if (__pyx_v_compute_vertex_to_simplex) {

    
    __pyx_t_1 = PyObject_GetAttr(__pyx_v_obj, __pyx_n_s__vertex_to_simplex); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1564; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    if (!(likely(((__pyx_t_1) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_1, __pyx_ptype_5numpy_ndarray))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1564; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_t_14 = ((PyArrayObject *)__pyx_t_1);
    {
      __Pyx_BufFmt_StackElem __pyx_stack[1];
      __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_vertex_to_simplex.rcbuffer->pybuffer);
      __pyx_t_10 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_vertex_to_simplex.rcbuffer->pybuffer, (PyObject*)__pyx_t_14, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES, 1, 0, __pyx_stack);
      if (unlikely(__pyx_t_10 < 0)) {
        PyErr_Fetch(&__pyx_t_13, &__pyx_t_12, &__pyx_t_11);
        if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_vertex_to_simplex.rcbuffer->pybuffer, (PyObject*)__pyx_v_vertex_to_simplex, &__Pyx_TypeInfo_nn_npy_int, PyBUF_FORMAT| PyBUF_STRIDES, 1, 0, __pyx_stack) == -1)) {
          Py_XDECREF(__pyx_t_13); Py_XDECREF(__pyx_t_12); Py_XDECREF(__pyx_t_11);
          __Pyx_RaiseBufferFallbackError();
        } else {
          PyErr_Restore(__pyx_t_13, __pyx_t_12, __pyx_t_11);
        }
      }
      __pyx_pybuffernd_vertex_to_simplex.diminfo[0].strides = __pyx_pybuffernd_vertex_to_simplex.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_vertex_to_simplex.diminfo[0].shape = __pyx_pybuffernd_vertex_to_simplex.rcbuffer->pybuffer.shape[0];
      if (unlikely(__pyx_t_10 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1564; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_t_14 = 0;
    __pyx_v_vertex_to_simplex = ((PyArrayObject *)__pyx_t_1);
    __pyx_t_1 = 0;

    
    __pyx_v_info->vertex_to_simplex = ((int *)__pyx_v_vertex_to_simplex->data);
    goto __pyx_L4;
  }
   {

    
    __pyx_v_info->vertex_to_simplex = NULL;
  }
  __pyx_L4:;

  
  __pyx_v_info->min_bound = ((double *)__pyx_v_min_bound->data);

  
  __pyx_v_info->max_bound = ((double *)__pyx_v_max_bound->data);

  
  __pyx_r = 0;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  { PyObject *__pyx_type, *__pyx_value, *__pyx_tb;
    __Pyx_ErrFetch(&__pyx_type, &__pyx_value, &__pyx_tb);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_equations.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_max_bound.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_min_bound.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_neighbors.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_points.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_transform.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_vertex_to_simplex.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer);
  __Pyx_ErrRestore(__pyx_type, __pyx_value, __pyx_tb);}
  __Pyx_AddTraceback("scipy.spatial.qhull._get_delaunay_info", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  goto __pyx_L2;
  __pyx_L0:;
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_equations.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_max_bound.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_min_bound.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_neighbors.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_points.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_transform.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_vertex_to_simplex.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_vertices.rcbuffer->pybuffer);
  __pyx_L2:;
  __Pyx_XDECREF((PyObject *)__pyx_v_transform);
  __Pyx_XDECREF((PyObject *)__pyx_v_vertex_to_simplex);
  __Pyx_XDECREF((PyObject *)__pyx_v_points);
  __Pyx_XDECREF((PyObject *)__pyx_v_vertices);
  __Pyx_XDECREF((PyObject *)__pyx_v_neighbors);
  __Pyx_XDECREF((PyObject *)__pyx_v_equations);
  __Pyx_XDECREF((PyObject *)__pyx_v_min_bound);
  __Pyx_XDECREF((PyObject *)__pyx_v_max_bound);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static int __pyx_pw_5numpy_7ndarray_1__getbuffer__(PyObject *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags); 
static int __pyx_pw_5numpy_7ndarray_1__getbuffer__(PyObject *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__getbuffer__ (wrapper)", 0);
  __pyx_r = __pyx_pf_5numpy_7ndarray___getbuffer__(((PyArrayObject *)__pyx_v_self), ((Py_buffer *)__pyx_v_info), ((int)__pyx_v_flags));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static int __pyx_pf_5numpy_7ndarray___getbuffer__(PyArrayObject *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags) {
  int __pyx_v_copy_shape;
  int __pyx_v_i;
  int __pyx_v_ndim;
  int __pyx_v_endian_detector;
  int __pyx_v_little_endian;
  int __pyx_v_t;
  char *__pyx_v_f;
  PyArray_Descr *__pyx_v_descr = 0;
  int __pyx_v_offset;
  int __pyx_v_hasfields;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_t_5;
  int __pyx_t_6;
  int __pyx_t_7;
  PyObject *__pyx_t_8 = NULL;
  char *__pyx_t_9;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__getbuffer__", 0);
  if (__pyx_v_info != NULL) {
    __pyx_v_info->obj = Py_None; __Pyx_INCREF(Py_None);
    __Pyx_GIVEREF(__pyx_v_info->obj);
  }

  
  __pyx_t_1 = (__pyx_v_info == NULL);
  if (__pyx_t_1) {
    __pyx_r = 0;
    goto __pyx_L0;
    goto __pyx_L3;
  }
  __pyx_L3:;

  
  __pyx_v_endian_detector = 1;

  
  __pyx_v_little_endian = ((((char *)(&__pyx_v_endian_detector))[0]) != 0);

  
  __pyx_v_ndim = PyArray_NDIM(__pyx_v_self);

  
  __pyx_t_1 = ((sizeof(npy_intp)) != (sizeof(Py_ssize_t)));
  if (__pyx_t_1) {

    
    __pyx_v_copy_shape = 1;
    goto __pyx_L4;
  }
   {

    
    __pyx_v_copy_shape = 0;
  }
  __pyx_L4:;

  
  __pyx_t_1 = ((__pyx_v_flags & PyBUF_C_CONTIGUOUS) == PyBUF_C_CONTIGUOUS);
  if (__pyx_t_1) {

    
    __pyx_t_2 = (!PyArray_CHKFLAGS(__pyx_v_self, NPY_C_CONTIGUOUS));
    __pyx_t_3 = __pyx_t_2;
  } else {
    __pyx_t_3 = __pyx_t_1;
  }
  if (__pyx_t_3) {

    
    __pyx_t_4 = PyObject_Call(__pyx_builtin_ValueError, ((PyObject *)__pyx_k_tuple_37), NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 215; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_Raise(__pyx_t_4, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    {__pyx_filename = __pyx_f[1]; __pyx_lineno = 215; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    goto __pyx_L5;
  }
  __pyx_L5:;

  
  __pyx_t_3 = ((__pyx_v_flags & PyBUF_F_CONTIGUOUS) == PyBUF_F_CONTIGUOUS);
  if (__pyx_t_3) {

    
    __pyx_t_1 = (!PyArray_CHKFLAGS(__pyx_v_self, NPY_F_CONTIGUOUS));
    __pyx_t_2 = __pyx_t_1;
  } else {
    __pyx_t_2 = __pyx_t_3;
  }
  if (__pyx_t_2) {

    
    __pyx_t_4 = PyObject_Call(__pyx_builtin_ValueError, ((PyObject *)__pyx_k_tuple_39), NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 219; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_Raise(__pyx_t_4, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    {__pyx_filename = __pyx_f[1]; __pyx_lineno = 219; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    goto __pyx_L6;
  }
  __pyx_L6:;

  
  __pyx_v_info->buf = PyArray_DATA(__pyx_v_self);

  
  __pyx_v_info->ndim = __pyx_v_ndim;

  
  if (__pyx_v_copy_shape) {

    
    __pyx_v_info->strides = ((Py_ssize_t *)malloc((((sizeof(Py_ssize_t)) * ((size_t)__pyx_v_ndim)) * 2)));

    
    __pyx_v_info->shape = (__pyx_v_info->strides + __pyx_v_ndim);

    
    __pyx_t_5 = __pyx_v_ndim;
    for (__pyx_t_6 = 0; __pyx_t_6 < __pyx_t_5; __pyx_t_6+=1) {
      __pyx_v_i = __pyx_t_6;

      
      (__pyx_v_info->strides[__pyx_v_i]) = (PyArray_STRIDES(__pyx_v_self)[__pyx_v_i]);

      
      (__pyx_v_info->shape[__pyx_v_i]) = (PyArray_DIMS(__pyx_v_self)[__pyx_v_i]);
    }
    goto __pyx_L7;
  }
   {

    
    __pyx_v_info->strides = ((Py_ssize_t *)PyArray_STRIDES(__pyx_v_self));

    
    __pyx_v_info->shape = ((Py_ssize_t *)PyArray_DIMS(__pyx_v_self));
  }
  __pyx_L7:;

  
  __pyx_v_info->suboffsets = NULL;

  
  __pyx_v_info->itemsize = PyArray_ITEMSIZE(__pyx_v_self);

  
  __pyx_v_info->readonly = (!PyArray_ISWRITEABLE(__pyx_v_self));

  
  __pyx_v_f = NULL;

  
  __Pyx_INCREF(((PyObject *)__pyx_v_self->descr));
  __pyx_v_descr = __pyx_v_self->descr;

  
  __pyx_v_hasfields = PyDataType_HASFIELDS(__pyx_v_descr);

  
  __pyx_t_2 = (!__pyx_v_hasfields);
  if (__pyx_t_2) {
    __pyx_t_3 = (!__pyx_v_copy_shape);
    __pyx_t_1 = __pyx_t_3;
  } else {
    __pyx_t_1 = __pyx_t_2;
  }
  if (__pyx_t_1) {

    
    __Pyx_INCREF(Py_None);
    __Pyx_GIVEREF(Py_None);
    __Pyx_GOTREF(__pyx_v_info->obj);
    __Pyx_DECREF(__pyx_v_info->obj);
    __pyx_v_info->obj = Py_None;
    goto __pyx_L10;
  }
   {

    
    __Pyx_INCREF(((PyObject *)__pyx_v_self));
    __Pyx_GIVEREF(((PyObject *)__pyx_v_self));
    __Pyx_GOTREF(__pyx_v_info->obj);
    __Pyx_DECREF(__pyx_v_info->obj);
    __pyx_v_info->obj = ((PyObject *)__pyx_v_self);
  }
  __pyx_L10:;

  
  __pyx_t_1 = (!__pyx_v_hasfields);
  if (__pyx_t_1) {

    
    __pyx_v_t = __pyx_v_descr->type_num;

    
    __pyx_t_1 = (__pyx_v_descr->byteorder == '>');
    if (__pyx_t_1) {
      __pyx_t_2 = __pyx_v_little_endian;
    } else {
      __pyx_t_2 = __pyx_t_1;
    }
    if (!__pyx_t_2) {

      
      __pyx_t_1 = (__pyx_v_descr->byteorder == '<');
      if (__pyx_t_1) {
        __pyx_t_3 = (!__pyx_v_little_endian);
        __pyx_t_7 = __pyx_t_3;
      } else {
        __pyx_t_7 = __pyx_t_1;
      }
      __pyx_t_1 = __pyx_t_7;
    } else {
      __pyx_t_1 = __pyx_t_2;
    }
    if (__pyx_t_1) {

      
      __pyx_t_4 = PyObject_Call(__pyx_builtin_ValueError, ((PyObject *)__pyx_k_tuple_41), NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 257; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_Raise(__pyx_t_4, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      {__pyx_filename = __pyx_f[1]; __pyx_lineno = 257; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      goto __pyx_L12;
    }
    __pyx_L12:;

    
    __pyx_t_1 = (__pyx_v_t == NPY_BYTE);
    if (__pyx_t_1) {
      __pyx_v_f = __pyx_k__b;
      goto __pyx_L13;
    }

    
    __pyx_t_1 = (__pyx_v_t == NPY_UBYTE);
    if (__pyx_t_1) {
      __pyx_v_f = __pyx_k__B;
      goto __pyx_L13;
    }

    
    __pyx_t_1 = (__pyx_v_t == NPY_SHORT);
    if (__pyx_t_1) {
      __pyx_v_f = __pyx_k__h;
      goto __pyx_L13;
    }

    
    __pyx_t_1 = (__pyx_v_t == NPY_USHORT);
    if (__pyx_t_1) {
      __pyx_v_f = __pyx_k__H;
      goto __pyx_L13;
    }

    
    __pyx_t_1 = (__pyx_v_t == NPY_INT);
    if (__pyx_t_1) {
      __pyx_v_f = __pyx_k__i;
      goto __pyx_L13;
    }

    
    __pyx_t_1 = (__pyx_v_t == NPY_UINT);
    if (__pyx_t_1) {
      __pyx_v_f = __pyx_k__I;
      goto __pyx_L13;
    }

    
    __pyx_t_1 = (__pyx_v_t == NPY_LONG);
    if (__pyx_t_1) {
      __pyx_v_f = __pyx_k__l;
      goto __pyx_L13;
    }

    
    __pyx_t_1 = (__pyx_v_t == NPY_ULONG);
    if (__pyx_t_1) {
      __pyx_v_f = __pyx_k__L;
      goto __pyx_L13;
    }

    
    __pyx_t_1 = (__pyx_v_t == NPY_LONGLONG);
    if (__pyx_t_1) {
      __pyx_v_f = __pyx_k__q;
      goto __pyx_L13;
    }

    
    __pyx_t_1 = (__pyx_v_t == NPY_ULONGLONG);
    if (__pyx_t_1) {
      __pyx_v_f = __pyx_k__Q;
      goto __pyx_L13;
    }

    
    __pyx_t_1 = (__pyx_v_t == NPY_FLOAT);
    if (__pyx_t_1) {
      __pyx_v_f = __pyx_k__f;
      goto __pyx_L13;
    }

    
    __pyx_t_1 = (__pyx_v_t == NPY_DOUBLE);
    if (__pyx_t_1) {
      __pyx_v_f = __pyx_k__d;
      goto __pyx_L13;
    }

    
    __pyx_t_1 = (__pyx_v_t == NPY_LONGDOUBLE);
    if (__pyx_t_1) {
      __pyx_v_f = __pyx_k__g;
      goto __pyx_L13;
    }

    
    __pyx_t_1 = (__pyx_v_t == NPY_CFLOAT);
    if (__pyx_t_1) {
      __pyx_v_f = __pyx_k__Zf;
      goto __pyx_L13;
    }

    
    __pyx_t_1 = (__pyx_v_t == NPY_CDOUBLE);
    if (__pyx_t_1) {
      __pyx_v_f = __pyx_k__Zd;
      goto __pyx_L13;
    }

    
    __pyx_t_1 = (__pyx_v_t == NPY_CLONGDOUBLE);
    if (__pyx_t_1) {
      __pyx_v_f = __pyx_k__Zg;
      goto __pyx_L13;
    }

    
    __pyx_t_1 = (__pyx_v_t == NPY_OBJECT);
    if (__pyx_t_1) {
      __pyx_v_f = __pyx_k__O;
      goto __pyx_L13;
    }
     {

      
      __pyx_t_4 = PyInt_FromLong(__pyx_v_t); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_8 = PyNumber_Remainder(((PyObject *)__pyx_kp_u_42), __pyx_t_4); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(((PyObject *)__pyx_t_8));
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_4);
      PyTuple_SET_ITEM(__pyx_t_4, 0, ((PyObject *)__pyx_t_8));
      __Pyx_GIVEREF(((PyObject *)__pyx_t_8));
      __pyx_t_8 = 0;
      __pyx_t_8 = PyObject_Call(__pyx_builtin_ValueError, ((PyObject *)__pyx_t_4), NULL); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_DECREF(((PyObject *)__pyx_t_4)); __pyx_t_4 = 0;
      __Pyx_Raise(__pyx_t_8, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
      {__pyx_filename = __pyx_f[1]; __pyx_lineno = 276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_L13:;

    
    __pyx_v_info->format = __pyx_v_f;

    
    __pyx_r = 0;
    goto __pyx_L0;
    goto __pyx_L11;
  }
   {

    
    __pyx_v_info->format = ((char *)malloc(255));

    
    (__pyx_v_info->format[0]) = '^';

    
    __pyx_v_offset = 0;

    
    __pyx_t_9 = __pyx_f_5numpy__util_dtypestring(__pyx_v_descr, (__pyx_v_info->format + 1), (__pyx_v_info->format + 255), (&__pyx_v_offset)); if (unlikely(__pyx_t_9 == NULL)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 283; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_v_f = __pyx_t_9;

    
    (__pyx_v_f[0]) = '\x00';
  }
  __pyx_L11:;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_AddTraceback("numpy.ndarray.__getbuffer__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  if (__pyx_v_info != NULL && __pyx_v_info->obj != NULL) {
    __Pyx_GOTREF(__pyx_v_info->obj);
    __Pyx_DECREF(__pyx_v_info->obj); __pyx_v_info->obj = NULL;
  }
  goto __pyx_L2;
  __pyx_L0:;
  if (__pyx_v_info != NULL && __pyx_v_info->obj == Py_None) {
    __Pyx_GOTREF(Py_None);
    __Pyx_DECREF(Py_None); __pyx_v_info->obj = NULL;
  }
  __pyx_L2:;
  __Pyx_XDECREF((PyObject *)__pyx_v_descr);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static void __pyx_pw_5numpy_7ndarray_3__releasebuffer__(PyObject *__pyx_v_self, Py_buffer *__pyx_v_info); 
static void __pyx_pw_5numpy_7ndarray_3__releasebuffer__(PyObject *__pyx_v_self, Py_buffer *__pyx_v_info) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__releasebuffer__ (wrapper)", 0);
  __pyx_pf_5numpy_7ndarray_2__releasebuffer__(((PyArrayObject *)__pyx_v_self), ((Py_buffer *)__pyx_v_info));
  __Pyx_RefNannyFinishContext();
}



static void __pyx_pf_5numpy_7ndarray_2__releasebuffer__(PyArrayObject *__pyx_v_self, Py_buffer *__pyx_v_info) {
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __Pyx_RefNannySetupContext("__releasebuffer__", 0);

  
  __pyx_t_1 = PyArray_HASFIELDS(__pyx_v_self);
  if (__pyx_t_1) {

    
    free(__pyx_v_info->format);
    goto __pyx_L3;
  }
  __pyx_L3:;

  
  __pyx_t_1 = ((sizeof(npy_intp)) != (sizeof(Py_ssize_t)));
  if (__pyx_t_1) {

    
    free(__pyx_v_info->strides);
    goto __pyx_L4;
  }
  __pyx_L4:;

  __Pyx_RefNannyFinishContext();
}



static CYTHON_INLINE PyObject *__pyx_f_5numpy_PyArray_MultiIterNew1(PyObject *__pyx_v_a) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("PyArray_MultiIterNew1", 0);

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyArray_MultiIterNew(1, ((void *)__pyx_v_a)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 769; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("numpy.PyArray_MultiIterNew1", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static CYTHON_INLINE PyObject *__pyx_f_5numpy_PyArray_MultiIterNew2(PyObject *__pyx_v_a, PyObject *__pyx_v_b) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("PyArray_MultiIterNew2", 0);

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyArray_MultiIterNew(2, ((void *)__pyx_v_a), ((void *)__pyx_v_b)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 772; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("numpy.PyArray_MultiIterNew2", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static CYTHON_INLINE PyObject *__pyx_f_5numpy_PyArray_MultiIterNew3(PyObject *__pyx_v_a, PyObject *__pyx_v_b, PyObject *__pyx_v_c) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("PyArray_MultiIterNew3", 0);

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyArray_MultiIterNew(3, ((void *)__pyx_v_a), ((void *)__pyx_v_b), ((void *)__pyx_v_c)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 775; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("numpy.PyArray_MultiIterNew3", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static CYTHON_INLINE PyObject *__pyx_f_5numpy_PyArray_MultiIterNew4(PyObject *__pyx_v_a, PyObject *__pyx_v_b, PyObject *__pyx_v_c, PyObject *__pyx_v_d) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("PyArray_MultiIterNew4", 0);

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyArray_MultiIterNew(4, ((void *)__pyx_v_a), ((void *)__pyx_v_b), ((void *)__pyx_v_c), ((void *)__pyx_v_d)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 778; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("numpy.PyArray_MultiIterNew4", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static CYTHON_INLINE PyObject *__pyx_f_5numpy_PyArray_MultiIterNew5(PyObject *__pyx_v_a, PyObject *__pyx_v_b, PyObject *__pyx_v_c, PyObject *__pyx_v_d, PyObject *__pyx_v_e) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("PyArray_MultiIterNew5", 0);

  
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyArray_MultiIterNew(5, ((void *)__pyx_v_a), ((void *)__pyx_v_b), ((void *)__pyx_v_c), ((void *)__pyx_v_d), ((void *)__pyx_v_e)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 781; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("numpy.PyArray_MultiIterNew5", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static CYTHON_INLINE char *__pyx_f_5numpy__util_dtypestring(PyArray_Descr *__pyx_v_descr, char *__pyx_v_f, char *__pyx_v_end, int *__pyx_v_offset) {
  PyArray_Descr *__pyx_v_child = 0;
  int __pyx_v_endian_detector;
  int __pyx_v_little_endian;
  PyObject *__pyx_v_fields = 0;
  PyObject *__pyx_v_childname = NULL;
  PyObject *__pyx_v_new_offset = NULL;
  PyObject *__pyx_v_t = NULL;
  char *__pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  Py_ssize_t __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *(*__pyx_t_6)(PyObject *);
  int __pyx_t_7;
  int __pyx_t_8;
  int __pyx_t_9;
  int __pyx_t_10;
  long __pyx_t_11;
  char *__pyx_t_12;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("_util_dtypestring", 0);

  
  __pyx_v_endian_detector = 1;

  
  __pyx_v_little_endian = ((((char *)(&__pyx_v_endian_detector))[0]) != 0);

  
  if (unlikely(((PyObject *)__pyx_v_descr->names) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
    {__pyx_filename = __pyx_f[1]; __pyx_lineno = 794; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_1 = ((PyObject *)__pyx_v_descr->names); __Pyx_INCREF(__pyx_t_1); __pyx_t_2 = 0;
  for (;;) {
    if (__pyx_t_2 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
    #if CYTHON_COMPILING_IN_CPYTHON
    __pyx_t_3 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_2); __Pyx_INCREF(__pyx_t_3); __pyx_t_2++; if (unlikely(0 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 794; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    #else
    __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_2); __pyx_t_2++; if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 794; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    #endif
    __Pyx_XDECREF(__pyx_v_childname);
    __pyx_v_childname = __pyx_t_3;
    __pyx_t_3 = 0;

    
    __pyx_t_3 = PyObject_GetItem(__pyx_v_descr->fields, __pyx_v_childname); if (!__pyx_t_3) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 795; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    if (!(likely(PyTuple_CheckExact(__pyx_t_3))||((__pyx_t_3) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected tuple, got %.200s", Py_TYPE(__pyx_t_3)->tp_name), 0))) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 795; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_XDECREF(((PyObject *)__pyx_v_fields));
    __pyx_v_fields = ((PyObject*)__pyx_t_3);
    __pyx_t_3 = 0;

    
    if (likely(PyTuple_CheckExact(((PyObject *)__pyx_v_fields)))) {
      PyObject* sequence = ((PyObject *)__pyx_v_fields);
      #if CYTHON_COMPILING_IN_CPYTHON
      Py_ssize_t size = Py_SIZE(sequence);
      #else
      Py_ssize_t size = PySequence_Size(sequence);
      #endif
      if (unlikely(size != 2)) {
        if (size > 2) __Pyx_RaiseTooManyValuesError(2);
        else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
        {__pyx_filename = __pyx_f[1]; __pyx_lineno = 796; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      }
      #if CYTHON_COMPILING_IN_CPYTHON
      __pyx_t_3 = PyTuple_GET_ITEM(sequence, 0); 
      __pyx_t_4 = PyTuple_GET_ITEM(sequence, 1); 
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_4);
      #else
      __pyx_t_3 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 796; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __pyx_t_4 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 796; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      #endif
    } else if (1) {
      __Pyx_RaiseNoneNotIterableError(); {__pyx_filename = __pyx_f[1]; __pyx_lineno = 796; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    } else
    {
      Py_ssize_t index = -1;
      __pyx_t_5 = PyObject_GetIter(((PyObject *)__pyx_v_fields)); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 796; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_6 = Py_TYPE(__pyx_t_5)->tp_iternext;
      index = 0; __pyx_t_3 = __pyx_t_6(__pyx_t_5); if (unlikely(!__pyx_t_3)) goto __pyx_L5_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_3);
      index = 1; __pyx_t_4 = __pyx_t_6(__pyx_t_5); if (unlikely(!__pyx_t_4)) goto __pyx_L5_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_4);
      if (__Pyx_IternextUnpackEndCheck(__pyx_t_6(__pyx_t_5), 2) < 0) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 796; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __pyx_t_6 = NULL;
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      goto __pyx_L6_unpacking_done;
      __pyx_L5_unpacking_failed:;
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_6 = NULL;
      if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
      {__pyx_filename = __pyx_f[1]; __pyx_lineno = 796; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __pyx_L6_unpacking_done:;
    }
    if (!(likely(((__pyx_t_3) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_3, __pyx_ptype_5numpy_dtype))))) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 796; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_XDECREF(((PyObject *)__pyx_v_child));
    __pyx_v_child = ((PyArray_Descr *)__pyx_t_3);
    __pyx_t_3 = 0;
    __Pyx_XDECREF(__pyx_v_new_offset);
    __pyx_v_new_offset = __pyx_t_4;
    __pyx_t_4 = 0;

    
    __pyx_t_4 = PyInt_FromLong((__pyx_v_end - __pyx_v_f)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 798; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_3 = PyInt_FromLong((__pyx_v_offset[0])); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 798; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_5 = PyNumber_Subtract(__pyx_v_new_offset, __pyx_t_3); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 798; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = PyNumber_Subtract(__pyx_t_4, __pyx_t_5); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 798; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_5 = PyObject_RichCompare(__pyx_t_3, __pyx_int_15, Py_LT); __Pyx_XGOTREF(__pyx_t_5); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 798; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_5); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 798; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    if (__pyx_t_7) {

      
      __pyx_t_5 = PyObject_Call(__pyx_builtin_RuntimeError, ((PyObject *)__pyx_k_tuple_44), NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 799; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_Raise(__pyx_t_5, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      {__pyx_filename = __pyx_f[1]; __pyx_lineno = 799; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      goto __pyx_L7;
    }
    __pyx_L7:;

    
    __pyx_t_7 = (__pyx_v_child->byteorder == '>');
    if (__pyx_t_7) {
      __pyx_t_8 = __pyx_v_little_endian;
    } else {
      __pyx_t_8 = __pyx_t_7;
    }
    if (!__pyx_t_8) {

      
      __pyx_t_7 = (__pyx_v_child->byteorder == '<');
      if (__pyx_t_7) {
        __pyx_t_9 = (!__pyx_v_little_endian);
        __pyx_t_10 = __pyx_t_9;
      } else {
        __pyx_t_10 = __pyx_t_7;
      }
      __pyx_t_7 = __pyx_t_10;
    } else {
      __pyx_t_7 = __pyx_t_8;
    }
    if (__pyx_t_7) {

      
      __pyx_t_5 = PyObject_Call(__pyx_builtin_ValueError, ((PyObject *)__pyx_k_tuple_45), NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 803; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_Raise(__pyx_t_5, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      {__pyx_filename = __pyx_f[1]; __pyx_lineno = 803; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      goto __pyx_L8;
    }
    __pyx_L8:;

    
    while (1) {
      __pyx_t_5 = PyInt_FromLong((__pyx_v_offset[0])); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 813; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_3 = PyObject_RichCompare(__pyx_t_5, __pyx_v_new_offset, Py_LT); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 813; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 813; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (!__pyx_t_7) break;

      
      (__pyx_v_f[0]) = 120;

      
      __pyx_v_f = (__pyx_v_f + 1);

      
      __pyx_t_11 = 0;
      (__pyx_v_offset[__pyx_t_11]) = ((__pyx_v_offset[__pyx_t_11]) + 1);
    }

    
    __pyx_t_11 = 0;
    (__pyx_v_offset[__pyx_t_11]) = ((__pyx_v_offset[__pyx_t_11]) + __pyx_v_child->elsize);

    
    __pyx_t_7 = (!PyDataType_HASFIELDS(__pyx_v_child));
    if (__pyx_t_7) {

      
      __pyx_t_3 = PyInt_FromLong(__pyx_v_child->type_num); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 821; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_XDECREF(__pyx_v_t);
      __pyx_v_t = __pyx_t_3;
      __pyx_t_3 = 0;

      
      __pyx_t_7 = ((__pyx_v_end - __pyx_v_f) < 5);
      if (__pyx_t_7) {

        
        __pyx_t_3 = PyObject_Call(__pyx_builtin_RuntimeError, ((PyObject *)__pyx_k_tuple_47), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 823; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_Raise(__pyx_t_3, 0, 0, 0);
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
        {__pyx_filename = __pyx_f[1]; __pyx_lineno = 823; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        goto __pyx_L12;
      }
      __pyx_L12:;

      
      __pyx_t_3 = PyInt_FromLong(NPY_BYTE); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 826; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_5 = PyObject_RichCompare(__pyx_v_t, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_5); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 826; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_5); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 826; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      if (__pyx_t_7) {
        (__pyx_v_f[0]) = 98;
        goto __pyx_L13;
      }

      
      __pyx_t_5 = PyInt_FromLong(NPY_UBYTE); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 827; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_t, __pyx_t_5, Py_EQ); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 827; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 827; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_7) {
        (__pyx_v_f[0]) = 66;
        goto __pyx_L13;
      }

      
      __pyx_t_3 = PyInt_FromLong(NPY_SHORT); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 828; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_5 = PyObject_RichCompare(__pyx_v_t, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_5); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 828; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_5); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 828; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      if (__pyx_t_7) {
        (__pyx_v_f[0]) = 104;
        goto __pyx_L13;
      }

      
      __pyx_t_5 = PyInt_FromLong(NPY_USHORT); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 829; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_t, __pyx_t_5, Py_EQ); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 829; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 829; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_7) {
        (__pyx_v_f[0]) = 72;
        goto __pyx_L13;
      }

      
      __pyx_t_3 = PyInt_FromLong(NPY_INT); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 830; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_5 = PyObject_RichCompare(__pyx_v_t, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_5); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 830; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_5); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 830; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      if (__pyx_t_7) {
        (__pyx_v_f[0]) = 105;
        goto __pyx_L13;
      }

      
      __pyx_t_5 = PyInt_FromLong(NPY_UINT); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 831; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_t, __pyx_t_5, Py_EQ); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 831; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 831; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_7) {
        (__pyx_v_f[0]) = 73;
        goto __pyx_L13;
      }

      
      __pyx_t_3 = PyInt_FromLong(NPY_LONG); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 832; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_5 = PyObject_RichCompare(__pyx_v_t, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_5); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 832; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_5); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 832; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      if (__pyx_t_7) {
        (__pyx_v_f[0]) = 108;
        goto __pyx_L13;
      }

      
      __pyx_t_5 = PyInt_FromLong(NPY_ULONG); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 833; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_t, __pyx_t_5, Py_EQ); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 833; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 833; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_7) {
        (__pyx_v_f[0]) = 76;
        goto __pyx_L13;
      }

      
      __pyx_t_3 = PyInt_FromLong(NPY_LONGLONG); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 834; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_5 = PyObject_RichCompare(__pyx_v_t, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_5); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 834; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_5); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 834; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      if (__pyx_t_7) {
        (__pyx_v_f[0]) = 113;
        goto __pyx_L13;
      }

      
      __pyx_t_5 = PyInt_FromLong(NPY_ULONGLONG); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 835; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_t, __pyx_t_5, Py_EQ); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 835; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 835; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_7) {
        (__pyx_v_f[0]) = 81;
        goto __pyx_L13;
      }

      
      __pyx_t_3 = PyInt_FromLong(NPY_FLOAT); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 836; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_5 = PyObject_RichCompare(__pyx_v_t, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_5); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 836; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_5); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 836; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      if (__pyx_t_7) {
        (__pyx_v_f[0]) = 102;
        goto __pyx_L13;
      }

      
      __pyx_t_5 = PyInt_FromLong(NPY_DOUBLE); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 837; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_t, __pyx_t_5, Py_EQ); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 837; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 837; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_7) {
        (__pyx_v_f[0]) = 100;
        goto __pyx_L13;
      }

      
      __pyx_t_3 = PyInt_FromLong(NPY_LONGDOUBLE); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 838; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_5 = PyObject_RichCompare(__pyx_v_t, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_5); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 838; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_5); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 838; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      if (__pyx_t_7) {
        (__pyx_v_f[0]) = 103;
        goto __pyx_L13;
      }

      
      __pyx_t_5 = PyInt_FromLong(NPY_CFLOAT); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 839; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_t, __pyx_t_5, Py_EQ); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 839; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 839; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_7) {
        (__pyx_v_f[0]) = 90;
        (__pyx_v_f[1]) = 102;
        __pyx_v_f = (__pyx_v_f + 1);
        goto __pyx_L13;
      }

      
      __pyx_t_3 = PyInt_FromLong(NPY_CDOUBLE); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 840; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_5 = PyObject_RichCompare(__pyx_v_t, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_5); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 840; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_5); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 840; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      if (__pyx_t_7) {
        (__pyx_v_f[0]) = 90;
        (__pyx_v_f[1]) = 100;
        __pyx_v_f = (__pyx_v_f + 1);
        goto __pyx_L13;
      }

      
      __pyx_t_5 = PyInt_FromLong(NPY_CLONGDOUBLE); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 841; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_t, __pyx_t_5, Py_EQ); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 841; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 841; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_7) {
        (__pyx_v_f[0]) = 90;
        (__pyx_v_f[1]) = 103;
        __pyx_v_f = (__pyx_v_f + 1);
        goto __pyx_L13;
      }

      
      __pyx_t_3 = PyInt_FromLong(NPY_OBJECT); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 842; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_5 = PyObject_RichCompare(__pyx_v_t, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_5); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 842; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_5); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 842; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      if (__pyx_t_7) {
        (__pyx_v_f[0]) = 79;
        goto __pyx_L13;
      }
       {

        
        __pyx_t_5 = PyNumber_Remainder(((PyObject *)__pyx_kp_u_42), __pyx_v_t); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 844; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __Pyx_GOTREF(((PyObject *)__pyx_t_5));
        __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 844; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __Pyx_GOTREF(__pyx_t_3);
        PyTuple_SET_ITEM(__pyx_t_3, 0, ((PyObject *)__pyx_t_5));
        __Pyx_GIVEREF(((PyObject *)__pyx_t_5));
        __pyx_t_5 = 0;
        __pyx_t_5 = PyObject_Call(__pyx_builtin_ValueError, ((PyObject *)__pyx_t_3), NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 844; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __Pyx_GOTREF(__pyx_t_5);
        __Pyx_DECREF(((PyObject *)__pyx_t_3)); __pyx_t_3 = 0;
        __Pyx_Raise(__pyx_t_5, 0, 0, 0);
        __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
        {__pyx_filename = __pyx_f[1]; __pyx_lineno = 844; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      }
      __pyx_L13:;

      
      __pyx_v_f = (__pyx_v_f + 1);
      goto __pyx_L11;
    }
     {

      
      __pyx_t_12 = __pyx_f_5numpy__util_dtypestring(__pyx_v_child, __pyx_v_f, __pyx_v_end, __pyx_v_offset); if (unlikely(__pyx_t_12 == NULL)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 849; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __pyx_v_f = __pyx_t_12;
    }
    __pyx_L11:;
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  
  __pyx_r = __pyx_v_f;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("numpy._util_dtypestring", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF((PyObject *)__pyx_v_child);
  __Pyx_XDECREF(__pyx_v_fields);
  __Pyx_XDECREF(__pyx_v_childname);
  __Pyx_XDECREF(__pyx_v_new_offset);
  __Pyx_XDECREF(__pyx_v_t);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}



static CYTHON_INLINE void __pyx_f_5numpy_set_array_base(PyArrayObject *__pyx_v_arr, PyObject *__pyx_v_base) {
  PyObject *__pyx_v_baseptr;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __Pyx_RefNannySetupContext("set_array_base", 0);

  
  __pyx_t_1 = (__pyx_v_base == Py_None);
  if (__pyx_t_1) {

    
    __pyx_v_baseptr = NULL;
    goto __pyx_L3;
  }
   {

    
    Py_INCREF(__pyx_v_base);

    
    __pyx_v_baseptr = ((PyObject *)__pyx_v_base);
  }
  __pyx_L3:;

  
  Py_XDECREF(__pyx_v_arr->base);

  
  __pyx_v_arr->base = __pyx_v_baseptr;

  __Pyx_RefNannyFinishContext();
}



static CYTHON_INLINE PyObject *__pyx_f_5numpy_get_array_base(PyArrayObject *__pyx_v_arr) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __Pyx_RefNannySetupContext("get_array_base", 0);

  
  __pyx_t_1 = (__pyx_v_arr->base == NULL);
  if (__pyx_t_1) {

    
    __Pyx_XDECREF(__pyx_r);
    __Pyx_INCREF(Py_None);
    __pyx_r = Py_None;
    goto __pyx_L0;
    goto __pyx_L3;
  }
   {

    
    __Pyx_XDECREF(__pyx_r);
    __Pyx_INCREF(((PyObject *)__pyx_v_arr->base));
    __pyx_r = ((PyObject *)__pyx_v_arr->base);
    goto __pyx_L0;
  }
  __pyx_L3:;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static struct __pyx_vtabstruct_5scipy_7spatial_5qhull__Qhull __pyx_vtable_5scipy_7spatial_5qhull__Qhull;

static PyObject *__pyx_tp_new_5scipy_7spatial_5qhull__Qhull(PyTypeObject *t, CYTHON_UNUSED PyObject *a, CYTHON_UNUSED PyObject *k) {
  struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *p;
  PyObject *o = (*t->tp_alloc)(t, 0);
  if (!o) return 0;
  p = ((struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *)o);
  p->__pyx_vtab = __pyx_vtabptr_5scipy_7spatial_5qhull__Qhull;
  p->_point_arrays = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->_dirty_points = Py_None; Py_INCREF(Py_None);
  return o;
}

static void __pyx_tp_dealloc_5scipy_7spatial_5qhull__Qhull(PyObject *o) {
  struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *p = (struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *)o;
  Py_CLEAR(p->_point_arrays);
  Py_CLEAR(p->_dirty_points);
  (*Py_TYPE(o)->tp_free)(o);
}

static int __pyx_tp_traverse_5scipy_7spatial_5qhull__Qhull(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *p = (struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *)o;
  if (p->_point_arrays) {
    e = (*v)(p->_point_arrays, a); if (e) return e;
  }
  if (p->_dirty_points) {
    e = (*v)(p->_dirty_points, a); if (e) return e;
  }
  return 0;
}

static int __pyx_tp_clear_5scipy_7spatial_5qhull__Qhull(PyObject *o) {
  struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *p = (struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *)o;
  PyObject* tmp;
  tmp = ((PyObject*)p->_point_arrays);
  p->_point_arrays = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->_dirty_points);
  p->_dirty_points = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  return 0;
}

static PyMethodDef __pyx_methods_5scipy_7spatial_5qhull__Qhull[] = {
  {__Pyx_NAMESTR("close"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_6_Qhull_3close, METH_NOARGS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("__del__"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_6_Qhull_5__del__, METH_NOARGS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("add_points"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_6_Qhull_7add_points, METH_O, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("flush"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_6_Qhull_9flush, METH_NOARGS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("get_arrays"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_6_Qhull_11get_arrays, METH_NOARGS, __Pyx_DOCSTR(__pyx_doc_5scipy_7spatial_5qhull_6_Qhull_10get_arrays)},
  {0, 0, 0, 0}
};

static PyNumberMethods __pyx_tp_as_number__Qhull = {
  0, 
  0, 
  0, 
  #if PY_MAJOR_VERSION < 3
  0, 
  #endif
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  #if PY_MAJOR_VERSION < 3
  0, 
  #endif
  0, 
  #if PY_MAJOR_VERSION < 3
  0, 
  #else
  0, 
  #endif
  0, 
  #if PY_MAJOR_VERSION < 3
  0, 
  #endif
  #if PY_MAJOR_VERSION < 3
  0, 
  #endif
  0, 
  0, 
  0, 
  #if PY_MAJOR_VERSION < 3
  0, 
  #endif
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  #if PY_VERSION_HEX >= 0x02050000
  0, 
  #endif
};

static PySequenceMethods __pyx_tp_as_sequence__Qhull = {
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
};

static PyMappingMethods __pyx_tp_as_mapping__Qhull = {
  0, 
  0, 
  0, 
};

static PyBufferProcs __pyx_tp_as_buffer__Qhull = {
  #if PY_MAJOR_VERSION < 3
  0, 
  #endif
  #if PY_MAJOR_VERSION < 3
  0, 
  #endif
  #if PY_MAJOR_VERSION < 3
  0, 
  #endif
  #if PY_MAJOR_VERSION < 3
  0, 
  #endif
  #if PY_VERSION_HEX >= 0x02060000
  0, 
  #endif
  #if PY_VERSION_HEX >= 0x02060000
  0, 
  #endif
};

static PyTypeObject __pyx_type_5scipy_7spatial_5qhull__Qhull = {
  PyVarObject_HEAD_INIT(0, 0)
  __Pyx_NAMESTR("scipy.spatial.qhull._Qhull"), 
  sizeof(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull), 
  0, 
  __pyx_tp_dealloc_5scipy_7spatial_5qhull__Qhull, 
  0, 
  0, 
  0, 
  #if PY_MAJOR_VERSION < 3
  0, 
  #else
  0, 
  #endif
  0, 
  &__pyx_tp_as_number__Qhull, 
  &__pyx_tp_as_sequence__Qhull, 
  &__pyx_tp_as_mapping__Qhull, 
  0, 
  0, 
  0, 
  0, 
  0, 
  &__pyx_tp_as_buffer__Qhull, 
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_NEWBUFFER|Py_TPFLAGS_HAVE_GC, 
  __Pyx_DOCSTR("\n    Thin wrapper for Qhull.\n\n    Attributes\n    ----------\n    paraboloid_scale : float\n    paraboloid_shift : float\n    "), 
  __pyx_tp_traverse_5scipy_7spatial_5qhull__Qhull, 
  __pyx_tp_clear_5scipy_7spatial_5qhull__Qhull, 
  0, 
  0, 
  0, 
  0, 
  __pyx_methods_5scipy_7spatial_5qhull__Qhull, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  __pyx_pw_5scipy_7spatial_5qhull_6_Qhull_1__init__, 
  0, 
  __pyx_tp_new_5scipy_7spatial_5qhull__Qhull, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  #if PY_VERSION_HEX >= 0x02060000
  0, 
  #endif
};

static PyObject *__pyx_tp_new_5scipy_7spatial_5qhull_RidgeIter2D(PyTypeObject *t, CYTHON_UNUSED PyObject *a, CYTHON_UNUSED PyObject *k) {
  struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D *p;
  PyObject *o = (*t->tp_alloc)(t, 0);
  if (!o) return 0;
  p = ((struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D *)o);
  p->delaunay = Py_None; Py_INCREF(Py_None);
  return o;
}

static void __pyx_tp_dealloc_5scipy_7spatial_5qhull_RidgeIter2D(PyObject *o) {
  struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D *p = (struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D *)o;
  Py_CLEAR(p->delaunay);
  (*Py_TYPE(o)->tp_free)(o);
}

static int __pyx_tp_traverse_5scipy_7spatial_5qhull_RidgeIter2D(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D *p = (struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D *)o;
  if (p->delaunay) {
    e = (*v)(p->delaunay, a); if (e) return e;
  }
  return 0;
}

static int __pyx_tp_clear_5scipy_7spatial_5qhull_RidgeIter2D(PyObject *o) {
  struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D *p = (struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D *)o;
  PyObject* tmp;
  tmp = ((PyObject*)p->delaunay);
  p->delaunay = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  return 0;
}

static PyMethodDef __pyx_methods_5scipy_7spatial_5qhull_RidgeIter2D[] = {
  {__Pyx_NAMESTR("__next__"), (PyCFunction)__pyx_pw_5scipy_7spatial_5qhull_11RidgeIter2D_5__next__, METH_NOARGS|METH_COEXIST, __Pyx_DOCSTR(0)},
  {0, 0, 0, 0}
};

static PyNumberMethods __pyx_tp_as_number_RidgeIter2D = {
  0, 
  0, 
  0, 
  #if PY_MAJOR_VERSION < 3
  0, 
  #endif
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  #if PY_MAJOR_VERSION < 3
  0, 
  #endif
  0, 
  #if PY_MAJOR_VERSION < 3
  0, 
  #else
  0, 
  #endif
  0, 
  #if PY_MAJOR_VERSION < 3
  0, 
  #endif
  #if PY_MAJOR_VERSION < 3
  0, 
  #endif
  0, 
  0, 
  0, 
  #if PY_MAJOR_VERSION < 3
  0, 
  #endif
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  #if PY_VERSION_HEX >= 0x02050000
  0, 
  #endif
};

static PySequenceMethods __pyx_tp_as_sequence_RidgeIter2D = {
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
};

static PyMappingMethods __pyx_tp_as_mapping_RidgeIter2D = {
  0, 
  0, 
  0, 
};

static PyBufferProcs __pyx_tp_as_buffer_RidgeIter2D = {
  #if PY_MAJOR_VERSION < 3
  0, 
  #endif
  #if PY_MAJOR_VERSION < 3
  0, 
  #endif
  #if PY_MAJOR_VERSION < 3
  0, 
  #endif
  #if PY_MAJOR_VERSION < 3
  0, 
  #endif
  #if PY_VERSION_HEX >= 0x02060000
  0, 
  #endif
  #if PY_VERSION_HEX >= 0x02060000
  0, 
  #endif
};

static PyTypeObject __pyx_type_5scipy_7spatial_5qhull_RidgeIter2D = {
  PyVarObject_HEAD_INIT(0, 0)
  __Pyx_NAMESTR("scipy.spatial.qhull.RidgeIter2D"), 
  sizeof(struct __pyx_obj_5scipy_7spatial_5qhull_RidgeIter2D), 
  0, 
  __pyx_tp_dealloc_5scipy_7spatial_5qhull_RidgeIter2D, 
  0, 
  0, 
  0, 
  #if PY_MAJOR_VERSION < 3
  0, 
  #else
  0, 
  #endif
  0, 
  &__pyx_tp_as_number_RidgeIter2D, 
  &__pyx_tp_as_sequence_RidgeIter2D, 
  &__pyx_tp_as_mapping_RidgeIter2D, 
  0, 
  0, 
  0, 
  0, 
  0, 
  &__pyx_tp_as_buffer_RidgeIter2D, 
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_NEWBUFFER|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_HAVE_GC, 
  0, 
  __pyx_tp_traverse_5scipy_7spatial_5qhull_RidgeIter2D, 
  __pyx_tp_clear_5scipy_7spatial_5qhull_RidgeIter2D, 
  0, 
  0, 
  __pyx_pw_5scipy_7spatial_5qhull_11RidgeIter2D_3__iter__, 
  __pyx_pw_5scipy_7spatial_5qhull_11RidgeIter2D_5__next__, 
  __pyx_methods_5scipy_7spatial_5qhull_RidgeIter2D, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  __pyx_pw_5scipy_7spatial_5qhull_11RidgeIter2D_1__init__, 
  0, 
  __pyx_tp_new_5scipy_7spatial_5qhull_RidgeIter2D, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  #if PY_VERSION_HEX >= 0x02060000
  0, 
  #endif
};

static PyMethodDef __pyx_methods[] = {
  {0, 0, 0, 0}
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef __pyx_moduledef = {
    PyModuleDef_HEAD_INIT,
    __Pyx_NAMESTR("qhull"),
    __Pyx_DOCSTR(__pyx_k_48), 
    -1, 
    __pyx_methods ,
    NULL, 
    NULL, 
    NULL, 
    NULL 
};
#endif

static __Pyx_StringTabEntry __pyx_string_tab[] = {
  {&__pyx_kp_s_11, __pyx_k_11, sizeof(__pyx_k_11), 0, 0, 1, 0},
  {&__pyx_kp_s_13, __pyx_k_13, sizeof(__pyx_k_13), 0, 0, 1, 0},
  {&__pyx_kp_s_15, __pyx_k_15, sizeof(__pyx_k_15), 0, 0, 1, 0},
  {&__pyx_kp_s_17, __pyx_k_17, sizeof(__pyx_k_17), 0, 0, 1, 0},
  {&__pyx_kp_s_20, __pyx_k_20, sizeof(__pyx_k_20), 0, 0, 1, 0},
  {&__pyx_kp_s_22, __pyx_k_22, sizeof(__pyx_k_22), 0, 0, 1, 0},
  {&__pyx_kp_s_24, __pyx_k_24, sizeof(__pyx_k_24), 0, 0, 1, 0},
  {&__pyx_n_s_25, __pyx_k_25, sizeof(__pyx_k_25), 0, 0, 1, 1},
  {&__pyx_kp_s_27, __pyx_k_27, sizeof(__pyx_k_27), 0, 0, 1, 0},
  {&__pyx_kp_s_29, __pyx_k_29, sizeof(__pyx_k_29), 0, 0, 1, 0},
  {&__pyx_kp_s_3, __pyx_k_3, sizeof(__pyx_k_3), 0, 0, 1, 0},
  {&__pyx_kp_u_36, __pyx_k_36, sizeof(__pyx_k_36), 0, 1, 0, 0},
  {&__pyx_kp_u_38, __pyx_k_38, sizeof(__pyx_k_38), 0, 1, 0, 0},
  {&__pyx_kp_b_4, __pyx_k_4, sizeof(__pyx_k_4), 0, 0, 0, 0},
  {&__pyx_kp_u_40, __pyx_k_40, sizeof(__pyx_k_40), 0, 1, 0, 0},
  {&__pyx_kp_u_42, __pyx_k_42, sizeof(__pyx_k_42), 0, 1, 0, 0},
  {&__pyx_kp_u_43, __pyx_k_43, sizeof(__pyx_k_43), 0, 1, 0, 0},
  {&__pyx_kp_u_46, __pyx_k_46, sizeof(__pyx_k_46), 0, 1, 0, 0},
  {&__pyx_n_s_49, __pyx_k_49, sizeof(__pyx_k_49), 0, 0, 1, 1},
  {&__pyx_kp_b_5, __pyx_k_5, sizeof(__pyx_k_5), 0, 0, 0, 0},
  {&__pyx_kp_s_52, __pyx_k_52, sizeof(__pyx_k_52), 0, 0, 1, 0},
  {&__pyx_kp_s_7, __pyx_k_7, sizeof(__pyx_k_7), 0, 0, 1, 0},
  {&__pyx_kp_s_8, __pyx_k_8, sizeof(__pyx_k_8), 0, 0, 1, 0},
  {&__pyx_kp_s_9, __pyx_k_9, sizeof(__pyx_k_9), 0, 0, 1, 0},
  {&__pyx_kp_s_91, __pyx_k_91, sizeof(__pyx_k_91), 0, 0, 1, 0},
  {&__pyx_n_s__Delaunay, __pyx_k__Delaunay, sizeof(__pyx_k__Delaunay), 0, 0, 1, 1},
  {&__pyx_n_s__Lock, __pyx_k__Lock, sizeof(__pyx_k__Lock), 0, 0, 1, 1},
  {&__pyx_n_s__QBk, __pyx_k__QBk, sizeof(__pyx_k__QBk), 0, 0, 1, 1},
  {&__pyx_n_s__QbB, __pyx_k__QbB, sizeof(__pyx_k__QbB), 0, 0, 1, 1},
  {&__pyx_n_s__Qbb, __pyx_k__Qbb, sizeof(__pyx_k__Qbb), 0, 0, 1, 1},
  {&__pyx_n_s__Qbk, __pyx_k__Qbk, sizeof(__pyx_k__Qbk), 0, 0, 1, 1},
  {&__pyx_n_s__QhullError, __pyx_k__QhullError, sizeof(__pyx_k__QhullError), 0, 0, 1, 1},
  {&__pyx_n_s__Qt, __pyx_k__Qt, sizeof(__pyx_k__Qt), 0, 0, 1, 1},
  {&__pyx_n_s__Qz, __pyx_k__Qz, sizeof(__pyx_k__Qz), 0, 0, 1, 1},
  {&__pyx_n_s__RuntimeError, __pyx_k__RuntimeError, sizeof(__pyx_k__RuntimeError), 0, 0, 1, 1},
  {&__pyx_n_s__StopIteration, __pyx_k__StopIteration, sizeof(__pyx_k__StopIteration), 0, 0, 1, 1},
  {&__pyx_n_s__T, __pyx_k__T, sizeof(__pyx_k__T), 0, 0, 1, 1},
  {&__pyx_n_s__Tinvs, __pyx_k__Tinvs, sizeof(__pyx_k__Tinvs), 0, 0, 1, 1},
  {&__pyx_n_s__ValueError, __pyx_k__ValueError, sizeof(__pyx_k__ValueError), 0, 0, 1, 1},
  {&__pyx_n_s____all__, __pyx_k____all__, sizeof(__pyx_k____all__), 0, 0, 1, 1},
  {&__pyx_n_s____init__, __pyx_k____init__, sizeof(__pyx_k____init__), 0, 0, 1, 1},
  {&__pyx_n_s____main__, __pyx_k____main__, sizeof(__pyx_k____main__), 0, 0, 1, 1},
  {&__pyx_n_s____test__, __pyx_k____test__, sizeof(__pyx_k____test__), 0, 0, 1, 1},
  {&__pyx_n_s___deactivate, __pyx_k___deactivate, sizeof(__pyx_k___deactivate), 0, 0, 1, 1},
  {&__pyx_n_s___equations, __pyx_k___equations, sizeof(__pyx_k___equations), 0, 0, 1, 1},
  {&__pyx_n_s___flush, __pyx_k___flush, sizeof(__pyx_k___flush), 0, 0, 1, 1},
  {&__pyx_n_s___max_bound, __pyx_k___max_bound, sizeof(__pyx_k___max_bound), 0, 0, 1, 1},
  {&__pyx_n_s___min_bound, __pyx_k___min_bound, sizeof(__pyx_k___min_bound), 0, 0, 1, 1},
  {&__pyx_n_s___neighbors, __pyx_k___neighbors, sizeof(__pyx_k___neighbors), 0, 0, 1, 1},
  {&__pyx_n_s___npoints, __pyx_k___npoints, sizeof(__pyx_k___npoints), 0, 0, 1, 1},
  {&__pyx_n_s___nsimplex, __pyx_k___nsimplex, sizeof(__pyx_k___nsimplex), 0, 0, 1, 1},
  {&__pyx_n_s___points, __pyx_k___points, sizeof(__pyx_k___points), 0, 0, 1, 1},
  {&__pyx_n_s___qhull, __pyx_k___qhull, sizeof(__pyx_k___qhull), 0, 0, 1, 1},
  {&__pyx_n_s___qhull_lock, __pyx_k___qhull_lock, sizeof(__pyx_k___qhull_lock), 0, 0, 1, 1},
  {&__pyx_n_s___transform, __pyx_k___transform, sizeof(__pyx_k___transform), 0, 0, 1, 1},
  {&__pyx_n_s___vertex_to_simplex, __pyx_k___vertex_to_simplex, sizeof(__pyx_k___vertex_to_simplex), 0, 0, 1, 1},
  {&__pyx_n_s___vertices, __pyx_k___vertices, sizeof(__pyx_k___vertices), 0, 0, 1, 1},
  {&__pyx_n_s__acquire, __pyx_k__acquire, sizeof(__pyx_k__acquire), 0, 0, 1, 1},
  {&__pyx_n_s__add_points, __pyx_k__add_points, sizeof(__pyx_k__add_points), 0, 0, 1, 1},
  {&__pyx_n_s__anorm, __pyx_k__anorm, sizeof(__pyx_k__anorm), 0, 0, 1, 1},
  {&__pyx_n_s__arr, __pyx_k__arr, sizeof(__pyx_k__arr), 0, 0, 1, 1},
  {&__pyx_n_s__asanyarray, __pyx_k__asanyarray, sizeof(__pyx_k__asanyarray), 0, 0, 1, 1},
  {&__pyx_n_s__ascontiguousarray, __pyx_k__ascontiguousarray, sizeof(__pyx_k__ascontiguousarray), 0, 0, 1, 1},
  {&__pyx_n_s__astype, __pyx_k__astype, sizeof(__pyx_k__astype), 0, 0, 1, 1},
  {&__pyx_n_s__axis, __pyx_k__axis, sizeof(__pyx_k__axis), 0, 0, 1, 1},
  {&__pyx_n_s__bruteforce, __pyx_k__bruteforce, sizeof(__pyx_k__bruteforce), 0, 0, 1, 1},
  {&__pyx_n_s__c, __pyx_k__c, sizeof(__pyx_k__c), 0, 0, 1, 1},
  {&__pyx_n_s__centroid, __pyx_k__centroid, sizeof(__pyx_k__centroid), 0, 0, 1, 1},
  {&__pyx_n_s__close, __pyx_k__close, sizeof(__pyx_k__close), 0, 0, 1, 1},
  {&__pyx_n_s__convex_hull, __pyx_k__convex_hull, sizeof(__pyx_k__convex_hull), 0, 0, 1, 1},
  {&__pyx_n_s__copy, __pyx_k__copy, sizeof(__pyx_k__copy), 0, 0, 1, 1},
  {&__pyx_n_s__delaunay, __pyx_k__delaunay, sizeof(__pyx_k__delaunay), 0, 0, 1, 1},
  {&__pyx_n_s__det, __pyx_k__det, sizeof(__pyx_k__det), 0, 0, 1, 1},
  {&__pyx_n_s__double, __pyx_k__double, sizeof(__pyx_k__double), 0, 0, 1, 1},
  {&__pyx_n_s__dtype, __pyx_k__dtype, sizeof(__pyx_k__dtype), 0, 0, 1, 1},
  {&__pyx_n_s__empty, __pyx_k__empty, sizeof(__pyx_k__empty), 0, 0, 1, 1},
  {&__pyx_n_s__eps, __pyx_k__eps, sizeof(__pyx_k__eps), 0, 0, 1, 1},
  {&__pyx_n_s__eps_broad, __pyx_k__eps_broad, sizeof(__pyx_k__eps_broad), 0, 0, 1, 1},
  {&__pyx_n_s__equations, __pyx_k__equations, sizeof(__pyx_k__equations), 0, 0, 1, 1},
  {&__pyx_n_s__fill, __pyx_k__fill, sizeof(__pyx_k__fill), 0, 0, 1, 1},
  {&__pyx_n_s__find_simplex, __pyx_k__find_simplex, sizeof(__pyx_k__find_simplex), 0, 0, 1, 1},
  {&__pyx_n_s__finfo, __pyx_k__finfo, sizeof(__pyx_k__finfo), 0, 0, 1, 1},
  {&__pyx_n_s__flush, __pyx_k__flush, sizeof(__pyx_k__flush), 0, 0, 1, 1},
  {&__pyx_n_s__force, __pyx_k__force, sizeof(__pyx_k__force), 0, 0, 1, 1},
  {&__pyx_n_s__get_arrays, __pyx_k__get_arrays, sizeof(__pyx_k__get_arrays), 0, 0, 1, 1},
  {&__pyx_n_s__i, __pyx_k__i, sizeof(__pyx_k__i), 0, 0, 1, 1},
  {&__pyx_n_s__incremental, __pyx_k__incremental, sizeof(__pyx_k__incremental), 0, 0, 1, 1},
  {&__pyx_n_s__info, __pyx_k__info, sizeof(__pyx_k__info), 0, 0, 1, 1},
  {&__pyx_n_s__intc, __pyx_k__intc, sizeof(__pyx_k__intc), 0, 0, 1, 1},
  {&__pyx_n_s__ipiv, __pyx_k__ipiv, sizeof(__pyx_k__ipiv), 0, 0, 1, 1},
  {&__pyx_n_s__isimplex, __pyx_k__isimplex, sizeof(__pyx_k__isimplex), 0, 0, 1, 1},
  {&__pyx_n_s__ivertex, __pyx_k__ivertex, sizeof(__pyx_k__ivertex), 0, 0, 1, 1},
  {&__pyx_n_s__iwork, __pyx_k__iwork, sizeof(__pyx_k__iwork), 0, 0, 1, 1},
  {&__pyx_n_s__j, __pyx_k__j, sizeof(__pyx_k__j), 0, 0, 1, 1},
  {&__pyx_n_s__k, __pyx_k__k, sizeof(__pyx_k__k), 0, 0, 1, 1},
  {&__pyx_n_s__lda, __pyx_k__lda, sizeof(__pyx_k__lda), 0, 0, 1, 1},
  {&__pyx_n_s__ldb, __pyx_k__ldb, sizeof(__pyx_k__ldb), 0, 0, 1, 1},
  {&__pyx_n_s__lift_points, __pyx_k__lift_points, sizeof(__pyx_k__lift_points), 0, 0, 1, 1},
  {&__pyx_n_s__m, __pyx_k__m, sizeof(__pyx_k__m), 0, 0, 1, 1},
  {&__pyx_n_s__max, __pyx_k__max, sizeof(__pyx_k__max), 0, 0, 1, 1},
  {&__pyx_n_s__max_bound, __pyx_k__max_bound, sizeof(__pyx_k__max_bound), 0, 0, 1, 1},
  {&__pyx_n_s__min, __pyx_k__min, sizeof(__pyx_k__min), 0, 0, 1, 1},
  {&__pyx_n_s__min_bound, __pyx_k__min_bound, sizeof(__pyx_k__min_bound), 0, 0, 1, 1},
  {&__pyx_n_s__msize, __pyx_k__msize, sizeof(__pyx_k__msize), 0, 0, 1, 1},
  {&__pyx_n_s__n, __pyx_k__n, sizeof(__pyx_k__n), 0, 0, 1, 1},
  {&__pyx_n_s__nan, __pyx_k__nan, sizeof(__pyx_k__nan), 0, 0, 1, 1},
  {&__pyx_n_s__ndim, __pyx_k__ndim, sizeof(__pyx_k__ndim), 0, 0, 1, 1},
  {&__pyx_n_s__neighbors, __pyx_k__neighbors, sizeof(__pyx_k__neighbors), 0, 0, 1, 1},
  {&__pyx_n_s__np, __pyx_k__np, sizeof(__pyx_k__np), 0, 0, 1, 1},
  {&__pyx_n_s__npoints, __pyx_k__npoints, sizeof(__pyx_k__npoints), 0, 0, 1, 1},
  {&__pyx_n_s__nrhs, __pyx_k__nrhs, sizeof(__pyx_k__nrhs), 0, 0, 1, 1},
  {&__pyx_n_s__nsimplex, __pyx_k__nsimplex, sizeof(__pyx_k__nsimplex), 0, 0, 1, 1},
  {&__pyx_n_s__numpy, __pyx_k__numpy, sizeof(__pyx_k__numpy), 0, 0, 1, 1},
  {&__pyx_n_s__object, __pyx_k__object, sizeof(__pyx_k__object), 0, 0, 1, 1},
  {&__pyx_n_s__options, __pyx_k__options, sizeof(__pyx_k__options), 0, 0, 1, 1},
  {&__pyx_n_s__out, __pyx_k__out, sizeof(__pyx_k__out), 0, 0, 1, 1},
  {&__pyx_n_s__out_, __pyx_k__out_, sizeof(__pyx_k__out_), 0, 0, 1, 1},
  {&__pyx_n_s__paraboloid_scale, __pyx_k__paraboloid_scale, sizeof(__pyx_k__paraboloid_scale), 0, 0, 1, 1},
  {&__pyx_n_s__paraboloid_shift, __pyx_k__paraboloid_shift, sizeof(__pyx_k__paraboloid_shift), 0, 0, 1, 1},
  {&__pyx_n_s__plane_distance, __pyx_k__plane_distance, sizeof(__pyx_k__plane_distance), 0, 0, 1, 1},
  {&__pyx_n_s__points, __pyx_k__points, sizeof(__pyx_k__points), 0, 0, 1, 1},
  {&__pyx_n_s__prod, __pyx_k__prod, sizeof(__pyx_k__prod), 0, 0, 1, 1},
  {&__pyx_n_s__property, __pyx_k__property, sizeof(__pyx_k__property), 0, 0, 1, 1},
  {&__pyx_n_s__qhull_options, __pyx_k__qhull_options, sizeof(__pyx_k__qhull_options), 0, 0, 1, 1},
  {&__pyx_n_s__range, __pyx_k__range, sizeof(__pyx_k__range), 0, 0, 1, 1},
  {&__pyx_n_s__rcond, __pyx_k__rcond, sizeof(__pyx_k__rcond), 0, 0, 1, 1},
  {&__pyx_n_s__rcond_limit, __pyx_k__rcond_limit, sizeof(__pyx_k__rcond_limit), 0, 0, 1, 1},
  {&__pyx_n_s__release, __pyx_k__release, sizeof(__pyx_k__release), 0, 0, 1, 1},
  {&__pyx_n_s__reshape, __pyx_k__reshape, sizeof(__pyx_k__reshape), 0, 0, 1, 1},
  {&__pyx_n_s__resize, __pyx_k__resize, sizeof(__pyx_k__resize), 0, 0, 1, 1},
  {&__pyx_n_s__self, __pyx_k__self, sizeof(__pyx_k__self), 0, 0, 1, 1},
  {&__pyx_n_s__shape, __pyx_k__shape, sizeof(__pyx_k__shape), 0, 0, 1, 1},
  {&__pyx_n_s__sqrt, __pyx_k__sqrt, sizeof(__pyx_k__sqrt), 0, 0, 1, 1},
  {&__pyx_n_s__start, __pyx_k__start, sizeof(__pyx_k__start), 0, 0, 1, 1},
  {&__pyx_n_s__sum, __pyx_k__sum, sizeof(__pyx_k__sum), 0, 0, 1, 1},
  {&__pyx_n_s__threading, __pyx_k__threading, sizeof(__pyx_k__threading), 0, 0, 1, 1},
  {&__pyx_n_s__tol, __pyx_k__tol, sizeof(__pyx_k__tol), 0, 0, 1, 1},
  {&__pyx_n_s__transform, __pyx_k__transform, sizeof(__pyx_k__transform), 0, 0, 1, 1},
  {&__pyx_n_s__tri, __pyx_k__tri, sizeof(__pyx_k__tri), 0, 0, 1, 1},
  {&__pyx_n_s__tsearch, __pyx_k__tsearch, sizeof(__pyx_k__tsearch), 0, 0, 1, 1},
  {&__pyx_n_s__vertex_to_simplex, __pyx_k__vertex_to_simplex, sizeof(__pyx_k__vertex_to_simplex), 0, 0, 1, 1},
  {&__pyx_n_s__vertices, __pyx_k__vertices, sizeof(__pyx_k__vertices), 0, 0, 1, 1},
  {&__pyx_n_s__vstack, __pyx_k__vstack, sizeof(__pyx_k__vstack), 0, 0, 1, 1},
  {&__pyx_n_s__work, __pyx_k__work, sizeof(__pyx_k__work), 0, 0, 1, 1},
  {&__pyx_n_s__x, __pyx_k__x, sizeof(__pyx_k__x), 0, 0, 1, 1},
  {&__pyx_n_s__x1, __pyx_k__x1, sizeof(__pyx_k__x1), 0, 0, 1, 1},
  {&__pyx_n_s__x2, __pyx_k__x2, sizeof(__pyx_k__x2), 0, 0, 1, 1},
  {&__pyx_n_s__x3, __pyx_k__x3, sizeof(__pyx_k__x3), 0, 0, 1, 1},
  {&__pyx_n_s__xi, __pyx_k__xi, sizeof(__pyx_k__xi), 0, 0, 1, 1},
  {&__pyx_n_s__xi_shape, __pyx_k__xi_shape, sizeof(__pyx_k__xi_shape), 0, 0, 1, 1},
  {&__pyx_n_s__xrange, __pyx_k__xrange, sizeof(__pyx_k__xrange), 0, 0, 1, 1},
  {&__pyx_n_s__y1, __pyx_k__y1, sizeof(__pyx_k__y1), 0, 0, 1, 1},
  {&__pyx_n_s__y2, __pyx_k__y2, sizeof(__pyx_k__y2), 0, 0, 1, 1},
  {&__pyx_n_s__y3, __pyx_k__y3, sizeof(__pyx_k__y3), 0, 0, 1, 1},
  {&__pyx_n_s__z, __pyx_k__z, sizeof(__pyx_k__z), 0, 0, 1, 1},
  {&__pyx_n_s__zeros, __pyx_k__zeros, sizeof(__pyx_k__zeros), 0, 0, 1, 1},
  {0, 0, 0, 0, 0, 0, 0}
};
static int __Pyx_InitCachedBuiltins(void) {
  __pyx_builtin_RuntimeError = __Pyx_GetName(__pyx_b, __pyx_n_s__RuntimeError); if (!__pyx_builtin_RuntimeError) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 479; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_builtin_object = __Pyx_GetName(__pyx_b, __pyx_n_s__object); if (!__pyx_builtin_object) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_builtin_property = __Pyx_GetName(__pyx_b, __pyx_n_s__property); if (!__pyx_builtin_property) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1227; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_builtin_ValueError = __Pyx_GetName(__pyx_b, __pyx_n_s__ValueError); if (!__pyx_builtin_ValueError) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 202; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_builtin_range = __Pyx_GetName(__pyx_b, __pyx_n_s__range); if (!__pyx_builtin_range) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 360; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #if PY_MAJOR_VERSION >= 3
  __pyx_builtin_xrange = __Pyx_GetName(__pyx_b, __pyx_n_s__range); if (!__pyx_builtin_xrange) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 449; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #else
  __pyx_builtin_xrange = __Pyx_GetName(__pyx_b, __pyx_n_s__xrange); if (!__pyx_builtin_xrange) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 449; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  __pyx_builtin_StopIteration = __Pyx_GetName(__pyx_b, __pyx_n_s__StopIteration); if (!__pyx_builtin_StopIteration) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 828; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  return 0;
  __pyx_L1_error:;
  return -1;
}

static int __Pyx_InitCachedConstants(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_InitCachedConstants", 0);

  
  __pyx_k_tuple_6 = PyTuple_New(5); if (unlikely(!__pyx_k_tuple_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 198; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_6);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__Qbb));
  PyTuple_SET_ITEM(__pyx_k_tuple_6, 0, ((PyObject *)__pyx_n_s__Qbb));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__Qbb));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__Qbk));
  PyTuple_SET_ITEM(__pyx_k_tuple_6, 1, ((PyObject *)__pyx_n_s__Qbk));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__Qbk));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__Qz));
  PyTuple_SET_ITEM(__pyx_k_tuple_6, 2, ((PyObject *)__pyx_n_s__Qz));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__Qz));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__QBk));
  PyTuple_SET_ITEM(__pyx_k_tuple_6, 3, ((PyObject *)__pyx_n_s__QBk));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__QBk));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__QbB));
  PyTuple_SET_ITEM(__pyx_k_tuple_6, 4, ((PyObject *)__pyx_n_s__QbB));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__QbB));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_6));

  
  __pyx_k_tuple_10 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_10)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 210; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_10);
  __Pyx_INCREF(((PyObject *)__pyx_kp_s_9));
  PyTuple_SET_ITEM(__pyx_k_tuple_10, 0, ((PyObject *)__pyx_kp_s_9));
  __Pyx_GIVEREF(((PyObject *)__pyx_kp_s_9));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_10));

  
  __pyx_k_tuple_12 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_12)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 213; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_12);
  __Pyx_INCREF(((PyObject *)__pyx_kp_s_11));
  PyTuple_SET_ITEM(__pyx_k_tuple_12, 0, ((PyObject *)__pyx_kp_s_11));
  __Pyx_GIVEREF(((PyObject *)__pyx_kp_s_11));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_12));

  
  __pyx_k_tuple_14 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_14)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 234; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_14);
  __Pyx_INCREF(((PyObject *)__pyx_kp_s_13));
  PyTuple_SET_ITEM(__pyx_k_tuple_14, 0, ((PyObject *)__pyx_kp_s_13));
  __Pyx_GIVEREF(((PyObject *)__pyx_kp_s_13));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_14));

  
  __pyx_k_tuple_16 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_16)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 275; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_16);
  __Pyx_INCREF(((PyObject *)__pyx_kp_s_15));
  PyTuple_SET_ITEM(__pyx_k_tuple_16, 0, ((PyObject *)__pyx_kp_s_15));
  __Pyx_GIVEREF(((PyObject *)__pyx_kp_s_15));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_16));

  
  __pyx_k_slice_18 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_k_slice_18)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 375; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_slice_18);
  __Pyx_GIVEREF(__pyx_k_slice_18);

  
  __pyx_k_tuple_19 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_19)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 417; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_19);
  __Pyx_INCREF(__pyx_int_neg_1);
  PyTuple_SET_ITEM(__pyx_k_tuple_19, 0, __pyx_int_neg_1);
  __Pyx_GIVEREF(__pyx_int_neg_1);
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_19));

  
  __pyx_k_tuple_21 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_21)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 468; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_21);
  __Pyx_INCREF(((PyObject *)__pyx_kp_s_20));
  PyTuple_SET_ITEM(__pyx_k_tuple_21, 0, ((PyObject *)__pyx_kp_s_20));
  __Pyx_GIVEREF(((PyObject *)__pyx_kp_s_20));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_21));

  
  __pyx_k_tuple_23 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_23)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 818; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_23);
  __Pyx_INCREF(((PyObject *)__pyx_kp_s_22));
  PyTuple_SET_ITEM(__pyx_k_tuple_23, 0, ((PyObject *)__pyx_kp_s_22));
  __Pyx_GIVEREF(((PyObject *)__pyx_kp_s_22));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_23));

  
  __pyx_k_tuple_26 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_26)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1313; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_26);
  __Pyx_INCREF(__pyx_int_neg_1);
  PyTuple_SET_ITEM(__pyx_k_tuple_26, 0, __pyx_int_neg_1);
  __Pyx_GIVEREF(__pyx_int_neg_1);
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_26));

  
  __pyx_k_tuple_28 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_28)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1430; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_28);
  __Pyx_INCREF(((PyObject *)__pyx_kp_s_27));
  PyTuple_SET_ITEM(__pyx_k_tuple_28, 0, ((PyObject *)__pyx_kp_s_27));
  __Pyx_GIVEREF(((PyObject *)__pyx_kp_s_27));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_28));

  
  __pyx_k_tuple_30 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_30)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1480; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_30);
  __Pyx_INCREF(((PyObject *)__pyx_kp_s_29));
  PyTuple_SET_ITEM(__pyx_k_tuple_30, 0, ((PyObject *)__pyx_kp_s_29));
  __Pyx_GIVEREF(((PyObject *)__pyx_kp_s_29));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_30));

  
  __pyx_k_slice_31 = PySlice_New(Py_None, __pyx_int_neg_1, Py_None); if (unlikely(!__pyx_k_slice_31)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1508; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_slice_31);
  __Pyx_GIVEREF(__pyx_k_slice_31);
  __pyx_k_tuple_32 = PyTuple_New(2); if (unlikely(!__pyx_k_tuple_32)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1508; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_32);
  __Pyx_INCREF(Py_Ellipsis);
  PyTuple_SET_ITEM(__pyx_k_tuple_32, 0, Py_Ellipsis);
  __Pyx_GIVEREF(Py_Ellipsis);
  __Pyx_INCREF(__pyx_k_slice_31);
  PyTuple_SET_ITEM(__pyx_k_tuple_32, 1, __pyx_k_slice_31);
  __Pyx_GIVEREF(__pyx_k_slice_31);
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_32));

  
  __pyx_k_tuple_33 = PyTuple_New(2); if (unlikely(!__pyx_k_tuple_33)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1509; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_33);
  __Pyx_INCREF(Py_Ellipsis);
  PyTuple_SET_ITEM(__pyx_k_tuple_33, 0, Py_Ellipsis);
  __Pyx_GIVEREF(Py_Ellipsis);
  __Pyx_INCREF(__pyx_int_neg_1);
  PyTuple_SET_ITEM(__pyx_k_tuple_33, 1, __pyx_int_neg_1);
  __Pyx_GIVEREF(__pyx_int_neg_1);
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_33));

  
  __pyx_k_tuple_34 = PyTuple_New(2); if (unlikely(!__pyx_k_tuple_34)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1510; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_34);
  __Pyx_INCREF(Py_Ellipsis);
  PyTuple_SET_ITEM(__pyx_k_tuple_34, 0, Py_Ellipsis);
  __Pyx_GIVEREF(Py_Ellipsis);
  __Pyx_INCREF(__pyx_int_neg_1);
  PyTuple_SET_ITEM(__pyx_k_tuple_34, 1, __pyx_int_neg_1);
  __Pyx_GIVEREF(__pyx_int_neg_1);
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_34));

  
  __pyx_k_tuple_35 = PyTuple_New(2); if (unlikely(!__pyx_k_tuple_35)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1511; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_35);
  __Pyx_INCREF(Py_Ellipsis);
  PyTuple_SET_ITEM(__pyx_k_tuple_35, 0, Py_Ellipsis);
  __Pyx_GIVEREF(Py_Ellipsis);
  __Pyx_INCREF(__pyx_int_neg_1);
  PyTuple_SET_ITEM(__pyx_k_tuple_35, 1, __pyx_int_neg_1);
  __Pyx_GIVEREF(__pyx_int_neg_1);
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_35));

  
  __pyx_k_tuple_37 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_37)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 215; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_37);
  __Pyx_INCREF(((PyObject *)__pyx_kp_u_36));
  PyTuple_SET_ITEM(__pyx_k_tuple_37, 0, ((PyObject *)__pyx_kp_u_36));
  __Pyx_GIVEREF(((PyObject *)__pyx_kp_u_36));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_37));

  
  __pyx_k_tuple_39 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_39)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 219; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_39);
  __Pyx_INCREF(((PyObject *)__pyx_kp_u_38));
  PyTuple_SET_ITEM(__pyx_k_tuple_39, 0, ((PyObject *)__pyx_kp_u_38));
  __Pyx_GIVEREF(((PyObject *)__pyx_kp_u_38));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_39));

  
  __pyx_k_tuple_41 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_41)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 257; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_41);
  __Pyx_INCREF(((PyObject *)__pyx_kp_u_40));
  PyTuple_SET_ITEM(__pyx_k_tuple_41, 0, ((PyObject *)__pyx_kp_u_40));
  __Pyx_GIVEREF(((PyObject *)__pyx_kp_u_40));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_41));

  
  __pyx_k_tuple_44 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_44)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 799; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_44);
  __Pyx_INCREF(((PyObject *)__pyx_kp_u_43));
  PyTuple_SET_ITEM(__pyx_k_tuple_44, 0, ((PyObject *)__pyx_kp_u_43));
  __Pyx_GIVEREF(((PyObject *)__pyx_kp_u_43));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_44));

  
  __pyx_k_tuple_45 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_45)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 803; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_45);
  __Pyx_INCREF(((PyObject *)__pyx_kp_u_40));
  PyTuple_SET_ITEM(__pyx_k_tuple_45, 0, ((PyObject *)__pyx_kp_u_40));
  __Pyx_GIVEREF(((PyObject *)__pyx_kp_u_40));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_45));

  
  __pyx_k_tuple_47 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_47)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 823; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_47);
  __Pyx_INCREF(((PyObject *)__pyx_kp_u_46));
  PyTuple_SET_ITEM(__pyx_k_tuple_47, 0, ((PyObject *)__pyx_kp_u_46));
  __Pyx_GIVEREF(((PyObject *)__pyx_kp_u_46));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_47));

  
  __pyx_k_tuple_50 = PyTuple_New(32); if (unlikely(!__pyx_k_tuple_50)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 488; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_50);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__points));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 0, ((PyObject *)__pyx_n_s__points));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__points));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__vertices));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 1, ((PyObject *)__pyx_n_s__vertices));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__vertices));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__eps));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 2, ((PyObject *)__pyx_n_s__eps));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__eps));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__T));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 3, ((PyObject *)__pyx_n_s__T));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__T));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__Tinvs));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 4, ((PyObject *)__pyx_n_s__Tinvs));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__Tinvs));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__isimplex));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 5, ((PyObject *)__pyx_n_s__isimplex));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__isimplex));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__i));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 6, ((PyObject *)__pyx_n_s__i));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__i));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__j));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 7, ((PyObject *)__pyx_n_s__j));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__j));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__n));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 8, ((PyObject *)__pyx_n_s__n));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__n));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__nrhs));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 9, ((PyObject *)__pyx_n_s__nrhs));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__nrhs));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__lda));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 10, ((PyObject *)__pyx_n_s__lda));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__lda));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__ldb));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 11, ((PyObject *)__pyx_n_s__ldb));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__ldb));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__info));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 12, ((PyObject *)__pyx_n_s__info));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__info));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__ipiv));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 13, ((PyObject *)__pyx_n_s__ipiv));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__ipiv));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__ndim));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 14, ((PyObject *)__pyx_n_s__ndim));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__ndim));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__nsimplex));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 15, ((PyObject *)__pyx_n_s__nsimplex));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__nsimplex));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__centroid));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 16, ((PyObject *)__pyx_n_s__centroid));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__centroid));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__c));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 17, ((PyObject *)__pyx_n_s__c));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__c));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__transform));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 18, ((PyObject *)__pyx_n_s__transform));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__transform));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__anorm));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 19, ((PyObject *)__pyx_n_s__anorm));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__anorm));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__rcond));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 20, ((PyObject *)__pyx_n_s__rcond));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__rcond));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__nan));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 21, ((PyObject *)__pyx_n_s__nan));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__nan));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__rcond_limit));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 22, ((PyObject *)__pyx_n_s__rcond_limit));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__rcond_limit));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__work));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 23, ((PyObject *)__pyx_n_s__work));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__work));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__iwork));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 24, ((PyObject *)__pyx_n_s__iwork));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__iwork));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__x1));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 25, ((PyObject *)__pyx_n_s__x1));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__x1));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__x2));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 26, ((PyObject *)__pyx_n_s__x2));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__x2));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__x3));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 27, ((PyObject *)__pyx_n_s__x3));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__x3));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__y1));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 28, ((PyObject *)__pyx_n_s__y1));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__y1));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__y2));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 29, ((PyObject *)__pyx_n_s__y2));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__y2));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__y3));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 30, ((PyObject *)__pyx_n_s__y3));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__y3));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__det));
  PyTuple_SET_ITEM(__pyx_k_tuple_50, 31, ((PyObject *)__pyx_n_s__det));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__det));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_50));
  __pyx_k_codeobj_51 = (PyObject*)__Pyx_PyCode_New(3, 0, 32, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_50, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s_25, 488, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_51)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 488; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_53 = PyTuple_New(4); if (unlikely(!__pyx_k_tuple_53)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1196; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_53);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_53, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__points));
  PyTuple_SET_ITEM(__pyx_k_tuple_53, 1, ((PyObject *)__pyx_n_s__points));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__points));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__incremental));
  PyTuple_SET_ITEM(__pyx_k_tuple_53, 2, ((PyObject *)__pyx_n_s__incremental));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__incremental));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__qhull_options));
  PyTuple_SET_ITEM(__pyx_k_tuple_53, 3, ((PyObject *)__pyx_n_s__qhull_options));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__qhull_options));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_53));
  __pyx_k_codeobj_54 = (PyObject*)__Pyx_PyCode_New(4, 0, 4, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_53, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s____init__, 1196, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_54)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1196; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_55 = PyTuple_New(2); if (unlikely(!__pyx_k_tuple_55)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1213; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_55);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_55, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__points));
  PyTuple_SET_ITEM(__pyx_k_tuple_55, 1, ((PyObject *)__pyx_n_s__points));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__points));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_55));
  __pyx_k_codeobj_56 = (PyObject*)__Pyx_PyCode_New(2, 0, 2, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_55, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s__add_points, 1213, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_56)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1213; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_57 = PyTuple_New(2); if (unlikely(!__pyx_k_tuple_57)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1216; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_57);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_57, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__force));
  PyTuple_SET_ITEM(__pyx_k_tuple_57, 1, ((PyObject *)__pyx_n_s__force));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__force));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_57));
  __pyx_k_codeobj_58 = (PyObject*)__Pyx_PyCode_New(2, 0, 2, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_57, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s___flush, 1216, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_58)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1216; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_59 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_59)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1228; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_59);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_59, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_59));
  __pyx_k_codeobj_60 = (PyObject*)__Pyx_PyCode_New(1, 0, 1, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_59, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s__points, 1228, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_60)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1228; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_61 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_61)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1233; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_61);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_61, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_61));
  __pyx_k_codeobj_62 = (PyObject*)__Pyx_PyCode_New(1, 0, 1, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_61, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s__vertices, 1233, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_62)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1233; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_63 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_63)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1238; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_63);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_63, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_63));
  __pyx_k_codeobj_64 = (PyObject*)__Pyx_PyCode_New(1, 0, 1, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_63, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s__neighbors, 1238, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_64)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1238; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_65 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_65)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1243; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_65);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_65, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_65));
  __pyx_k_codeobj_66 = (PyObject*)__Pyx_PyCode_New(1, 0, 1, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_65, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s__equations, 1243, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_66)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1243; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_67 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_67)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1248; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_67);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_67, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_67));
  __pyx_k_codeobj_68 = (PyObject*)__Pyx_PyCode_New(1, 0, 1, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_67, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s__npoints, 1248, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_68)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1248; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_69 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_69)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1253; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_69);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_69, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_69));
  __pyx_k_codeobj_70 = (PyObject*)__Pyx_PyCode_New(1, 0, 1, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_69, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s__nsimplex, 1253, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_70)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1253; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_71 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_71)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1258; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_71);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_71, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_71));
  __pyx_k_codeobj_72 = (PyObject*)__Pyx_PyCode_New(1, 0, 1, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_71, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s__min_bound, 1258, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_72)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1258; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_73 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_73)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1263; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_73);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_73, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_73));
  __pyx_k_codeobj_74 = (PyObject*)__Pyx_PyCode_New(1, 0, 1, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_73, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s__max_bound, 1263, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_74)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1263; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_75 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_75)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1268; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_75);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_75, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_75));
  __pyx_k_codeobj_76 = (PyObject*)__Pyx_PyCode_New(1, 0, 1, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_75, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s__paraboloid_scale, 1268, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_76)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1268; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_77 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_77)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1272; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_77);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_77, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_77));
  __pyx_k_codeobj_78 = (PyObject*)__Pyx_PyCode_New(1, 0, 1, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_77, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s__paraboloid_shift, 1272, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_78)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1272; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_79 = PyTuple_New(1); if (unlikely(!__pyx_k_tuple_79)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_79);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_79, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_79));
  __pyx_k_codeobj_80 = (PyObject*)__Pyx_PyCode_New(1, 0, 1, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_79, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s__transform, 1276, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_80)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_81 = PyTuple_New(8); if (unlikely(!__pyx_k_tuple_81)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1301; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_81);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_81, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__isimplex));
  PyTuple_SET_ITEM(__pyx_k_tuple_81, 1, ((PyObject *)__pyx_n_s__isimplex));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__isimplex));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__k));
  PyTuple_SET_ITEM(__pyx_k_tuple_81, 2, ((PyObject *)__pyx_n_s__k));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__k));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__ivertex));
  PyTuple_SET_ITEM(__pyx_k_tuple_81, 3, ((PyObject *)__pyx_n_s__ivertex));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__ivertex));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__nsimplex));
  PyTuple_SET_ITEM(__pyx_k_tuple_81, 4, ((PyObject *)__pyx_n_s__nsimplex));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__nsimplex));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__ndim));
  PyTuple_SET_ITEM(__pyx_k_tuple_81, 5, ((PyObject *)__pyx_n_s__ndim));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__ndim));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__vertices));
  PyTuple_SET_ITEM(__pyx_k_tuple_81, 6, ((PyObject *)__pyx_n_s__vertices));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__vertices));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__arr));
  PyTuple_SET_ITEM(__pyx_k_tuple_81, 7, ((PyObject *)__pyx_n_s__arr));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__arr));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_81));
  __pyx_k_codeobj_82 = (PyObject*)__Pyx_PyCode_New(1, 0, 8, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_81, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s__vertex_to_simplex, 1301, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_82)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1301; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_83 = PyTuple_New(12); if (unlikely(!__pyx_k_tuple_83)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1332; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_83);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_83, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__isimplex));
  PyTuple_SET_ITEM(__pyx_k_tuple_83, 1, ((PyObject *)__pyx_n_s__isimplex));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__isimplex));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__k));
  PyTuple_SET_ITEM(__pyx_k_tuple_83, 2, ((PyObject *)__pyx_n_s__k));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__k));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__j));
  PyTuple_SET_ITEM(__pyx_k_tuple_83, 3, ((PyObject *)__pyx_n_s__j));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__j));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__ndim));
  PyTuple_SET_ITEM(__pyx_k_tuple_83, 4, ((PyObject *)__pyx_n_s__ndim));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__ndim));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__nsimplex));
  PyTuple_SET_ITEM(__pyx_k_tuple_83, 5, ((PyObject *)__pyx_n_s__nsimplex));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__nsimplex));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__m));
  PyTuple_SET_ITEM(__pyx_k_tuple_83, 6, ((PyObject *)__pyx_n_s__m));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__m));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__msize));
  PyTuple_SET_ITEM(__pyx_k_tuple_83, 7, ((PyObject *)__pyx_n_s__msize));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__msize));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__out));
  PyTuple_SET_ITEM(__pyx_k_tuple_83, 8, ((PyObject *)__pyx_n_s__out));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__out));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__arr));
  PyTuple_SET_ITEM(__pyx_k_tuple_83, 9, ((PyObject *)__pyx_n_s__arr));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__arr));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__neighbors));
  PyTuple_SET_ITEM(__pyx_k_tuple_83, 10, ((PyObject *)__pyx_n_s__neighbors));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__neighbors));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__vertices));
  PyTuple_SET_ITEM(__pyx_k_tuple_83, 11, ((PyObject *)__pyx_n_s__vertices));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__vertices));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_83));
  __pyx_k_codeobj_84 = (PyObject*)__Pyx_PyCode_New(1, 0, 12, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_83, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s__convex_hull, 1332, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_84)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1332; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_85 = PyTuple_New(15); if (unlikely(!__pyx_k_tuple_85)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1385; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_85);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_85, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__xi));
  PyTuple_SET_ITEM(__pyx_k_tuple_85, 1, ((PyObject *)__pyx_n_s__xi));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__xi));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__bruteforce));
  PyTuple_SET_ITEM(__pyx_k_tuple_85, 2, ((PyObject *)__pyx_n_s__bruteforce));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__bruteforce));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__tol));
  PyTuple_SET_ITEM(__pyx_k_tuple_85, 3, ((PyObject *)__pyx_n_s__tol));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__tol));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__info));
  PyTuple_SET_ITEM(__pyx_k_tuple_85, 4, ((PyObject *)__pyx_n_s__info));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__info));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__isimplex));
  PyTuple_SET_ITEM(__pyx_k_tuple_85, 5, ((PyObject *)__pyx_n_s__isimplex));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__isimplex));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__c));
  PyTuple_SET_ITEM(__pyx_k_tuple_85, 6, ((PyObject *)__pyx_n_s__c));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__c));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__eps));
  PyTuple_SET_ITEM(__pyx_k_tuple_85, 7, ((PyObject *)__pyx_n_s__eps));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__eps));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__eps_broad));
  PyTuple_SET_ITEM(__pyx_k_tuple_85, 8, ((PyObject *)__pyx_n_s__eps_broad));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__eps_broad));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__start));
  PyTuple_SET_ITEM(__pyx_k_tuple_85, 9, ((PyObject *)__pyx_n_s__start));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__start));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__k));
  PyTuple_SET_ITEM(__pyx_k_tuple_85, 10, ((PyObject *)__pyx_n_s__k));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__k));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__x));
  PyTuple_SET_ITEM(__pyx_k_tuple_85, 11, ((PyObject *)__pyx_n_s__x));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__x));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__out_));
  PyTuple_SET_ITEM(__pyx_k_tuple_85, 12, ((PyObject *)__pyx_n_s__out_));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__out_));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__xi_shape));
  PyTuple_SET_ITEM(__pyx_k_tuple_85, 13, ((PyObject *)__pyx_n_s__xi_shape));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__xi_shape));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__out));
  PyTuple_SET_ITEM(__pyx_k_tuple_85, 14, ((PyObject *)__pyx_n_s__out));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__out));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_85));
  __pyx_k_codeobj_86 = (PyObject*)__Pyx_PyCode_New(4, 0, 15, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_85, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s__find_simplex, 1385, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_86)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1385; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_87 = PyTuple_New(11); if (unlikely(!__pyx_k_tuple_87)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1466; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_87);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_87, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__xi));
  PyTuple_SET_ITEM(__pyx_k_tuple_87, 1, ((PyObject *)__pyx_n_s__xi));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__xi));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__x));
  PyTuple_SET_ITEM(__pyx_k_tuple_87, 2, ((PyObject *)__pyx_n_s__x));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__x));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__out_));
  PyTuple_SET_ITEM(__pyx_k_tuple_87, 3, ((PyObject *)__pyx_n_s__out_));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__out_));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__info));
  PyTuple_SET_ITEM(__pyx_k_tuple_87, 4, ((PyObject *)__pyx_n_s__info));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__info));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__z));
  PyTuple_SET_ITEM(__pyx_k_tuple_87, 5, ((PyObject *)__pyx_n_s__z));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__z));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__i));
  PyTuple_SET_ITEM(__pyx_k_tuple_87, 6, ((PyObject *)__pyx_n_s__i));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__i));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__j));
  PyTuple_SET_ITEM(__pyx_k_tuple_87, 7, ((PyObject *)__pyx_n_s__j));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__j));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__k));
  PyTuple_SET_ITEM(__pyx_k_tuple_87, 8, ((PyObject *)__pyx_n_s__k));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__k));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__xi_shape));
  PyTuple_SET_ITEM(__pyx_k_tuple_87, 9, ((PyObject *)__pyx_n_s__xi_shape));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__xi_shape));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__out));
  PyTuple_SET_ITEM(__pyx_k_tuple_87, 10, ((PyObject *)__pyx_n_s__out));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__out));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_87));
  __pyx_k_codeobj_88 = (PyObject*)__Pyx_PyCode_New(2, 0, 11, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_87, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s__plane_distance, 1466, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_88)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1466; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_89 = PyTuple_New(3); if (unlikely(!__pyx_k_tuple_89)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1500; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_89);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__self));
  PyTuple_SET_ITEM(__pyx_k_tuple_89, 0, ((PyObject *)__pyx_n_s__self));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__self));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__x));
  PyTuple_SET_ITEM(__pyx_k_tuple_89, 1, ((PyObject *)__pyx_n_s__x));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__x));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__z));
  PyTuple_SET_ITEM(__pyx_k_tuple_89, 2, ((PyObject *)__pyx_n_s__z));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__z));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_89));
  __pyx_k_codeobj_90 = (PyObject*)__Pyx_PyCode_New(2, 0, 3, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_89, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s__lift_points, 1500, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_90)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1500; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  
  __pyx_k_tuple_92 = PyTuple_New(2); if (unlikely(!__pyx_k_tuple_92)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1515; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_92);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__tri));
  PyTuple_SET_ITEM(__pyx_k_tuple_92, 0, ((PyObject *)__pyx_n_s__tri));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__tri));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__xi));
  PyTuple_SET_ITEM(__pyx_k_tuple_92, 1, ((PyObject *)__pyx_n_s__xi));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__xi));
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_92));
  __pyx_k_codeobj_93 = (PyObject*)__Pyx_PyCode_New(2, 0, 2, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_92, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_52, __pyx_n_s__tsearch, 1515, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_93)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1515; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_RefNannyFinishContext();
  return 0;
  __pyx_L1_error:;
  __Pyx_RefNannyFinishContext();
  return -1;
}

static int __Pyx_InitGlobals(void) {
  if (__Pyx_InitStrings(__pyx_string_tab) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  __pyx_int_0 = PyInt_FromLong(0); if (unlikely(!__pyx_int_0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  __pyx_int_1 = PyInt_FromLong(1); if (unlikely(!__pyx_int_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  __pyx_int_2 = PyInt_FromLong(2); if (unlikely(!__pyx_int_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  __pyx_int_3 = PyInt_FromLong(3); if (unlikely(!__pyx_int_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  __pyx_int_neg_1 = PyInt_FromLong(-1); if (unlikely(!__pyx_int_neg_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  __pyx_int_15 = PyInt_FromLong(15); if (unlikely(!__pyx_int_15)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  __pyx_int_100 = PyInt_FromLong(100); if (unlikely(!__pyx_int_100)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  return 0;
  __pyx_L1_error:;
  return -1;
}

#if PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initqhull(void); 
PyMODINIT_FUNC initqhull(void)
#else
PyMODINIT_FUNC PyInit_qhull(void); 
PyMODINIT_FUNC PyInit_qhull(void)
#endif
{
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  __Pyx_RefNannyDeclarations
  #if CYTHON_REFNANNY
  __Pyx_RefNanny = __Pyx_RefNannyImportAPI("refnanny");
  if (!__Pyx_RefNanny) {
      PyErr_Clear();
      __Pyx_RefNanny = __Pyx_RefNannyImportAPI("Cython.Runtime.refnanny");
      if (!__Pyx_RefNanny)
          Py_FatalError("failed to import 'refnanny' module");
  }
  #endif
  __Pyx_RefNannySetupContext("PyMODINIT_FUNC PyInit_qhull(void)", 0);
  if ( __Pyx_check_binary_version() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_empty_tuple = PyTuple_New(0); if (unlikely(!__pyx_empty_tuple)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_empty_bytes = PyBytes_FromStringAndSize("", 0); if (unlikely(!__pyx_empty_bytes)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #ifdef __Pyx_CyFunction_USED
  if (__Pyx_CyFunction_init() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  #ifdef __Pyx_FusedFunction_USED
  if (__pyx_FusedFunction_init() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  #ifdef __Pyx_Generator_USED
  if (__pyx_Generator_init() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  
  
  #if defined(__PYX_FORCE_INIT_THREADS) && __PYX_FORCE_INIT_THREADS
  #ifdef WITH_THREAD 
  PyEval_InitThreads();
  #endif
  #endif
  
  #if PY_MAJOR_VERSION < 3
  __pyx_m = Py_InitModule4(__Pyx_NAMESTR("qhull"), __pyx_methods, __Pyx_DOCSTR(__pyx_k_48), 0, PYTHON_API_VERSION); Py_XINCREF(__pyx_m);
  #else
  __pyx_m = PyModule_Create(&__pyx_moduledef);
  #endif
  if (unlikely(!__pyx_m)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_b = PyImport_AddModule(__Pyx_NAMESTR(__Pyx_BUILTIN_MODULE_NAME)); if (unlikely(!__pyx_b)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #if CYTHON_COMPILING_IN_PYPY
  Py_INCREF(__pyx_b);
  #endif
  if (__Pyx_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  
  if (unlikely(__Pyx_InitGlobals() < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__pyx_module_is_main_scipy__spatial__qhull) {
    if (__Pyx_SetAttrString(__pyx_m, "__name__", __pyx_n_s____main__) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  }
  
  if (unlikely(__Pyx_InitCachedBuiltins() < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  
  if (unlikely(__Pyx_InitCachedConstants() < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  
  __pyx_v_5scipy_7spatial_5qhull__active_qhull = Py_None; Py_INCREF(Py_None);
  
  
  if (__Pyx_ExportFunction("_get_delaunay_info", (void (*)(void))__pyx_f_5scipy_7spatial_5qhull__get_delaunay_info, "int (__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *, PyObject *, int, int)") < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_ExportFunction("_barycentric_inside", (void (*)(void))__pyx_f_5scipy_7spatial_5qhull__barycentric_inside, "int (int, double *, double *, double *, double)") < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_ExportFunction("_barycentric_coordinate_single", (void (*)(void))__pyx_f_5scipy_7spatial_5qhull__barycentric_coordinate_single, "void (int, double *, double *, double *, int)") < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_ExportFunction("_barycentric_coordinates", (void (*)(void))__pyx_f_5scipy_7spatial_5qhull__barycentric_coordinates, "void (int, double *, double *, double *)") < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_ExportFunction("_lift_point", (void (*)(void))__pyx_f_5scipy_7spatial_5qhull__lift_point, "void (__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *, double *, double *)") < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_ExportFunction("_distplane", (void (*)(void))__pyx_f_5scipy_7spatial_5qhull__distplane, "double (__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *, int, double *)") < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_ExportFunction("_is_point_fully_outside", (void (*)(void))__pyx_f_5scipy_7spatial_5qhull__is_point_fully_outside, "int (__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *, double *, double)") < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_ExportFunction("_find_simplex_bruteforce", (void (*)(void))__pyx_f_5scipy_7spatial_5qhull__find_simplex_bruteforce, "int (__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *, double *, double *, double, double)") < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_ExportFunction("_find_simplex_directed", (void (*)(void))__pyx_f_5scipy_7spatial_5qhull__find_simplex_directed, "int (__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *, double *, double *, int *, double, double)") < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_ExportFunction("_find_simplex", (void (*)(void))__pyx_f_5scipy_7spatial_5qhull__find_simplex, "int (__pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *, double *, double *, int *, double, double)") < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_ExportFunction("_RidgeIter2D_init", (void (*)(void))__pyx_f_5scipy_7spatial_5qhull__RidgeIter2D_init, "void (__pyx_t_5scipy_7spatial_5qhull_RidgeIter2D_t *, __pyx_t_5scipy_7spatial_5qhull_DelaunayInfo_t *, int)") < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_ExportFunction("_RidgeIter2D_next", (void (*)(void))__pyx_f_5scipy_7spatial_5qhull__RidgeIter2D_next, "void (__pyx_t_5scipy_7spatial_5qhull_RidgeIter2D_t *)") < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  
  __pyx_vtabptr_5scipy_7spatial_5qhull__Qhull = &__pyx_vtable_5scipy_7spatial_5qhull__Qhull;
  __pyx_vtable_5scipy_7spatial_5qhull__Qhull._activate = (int (*)(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *))__pyx_f_5scipy_7spatial_5qhull_6_Qhull__activate;
  __pyx_vtable_5scipy_7spatial_5qhull__Qhull._deactivate = (int (*)(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *))__pyx_f_5scipy_7spatial_5qhull_6_Qhull__deactivate;
  __pyx_vtable_5scipy_7spatial_5qhull__Qhull._uninit = (int (*)(struct __pyx_obj_5scipy_7spatial_5qhull__Qhull *))__pyx_f_5scipy_7spatial_5qhull_6_Qhull__uninit;
  if (PyType_Ready(&__pyx_type_5scipy_7spatial_5qhull__Qhull) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 156; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_SetVtable(__pyx_type_5scipy_7spatial_5qhull__Qhull.tp_dict, __pyx_vtabptr_5scipy_7spatial_5qhull__Qhull) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 156; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_SetAttrString(__pyx_m, "_Qhull", (PyObject *)&__pyx_type_5scipy_7spatial_5qhull__Qhull) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 156; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_ptype_5scipy_7spatial_5qhull__Qhull = &__pyx_type_5scipy_7spatial_5qhull__Qhull;
  if (PyType_Ready(&__pyx_type_5scipy_7spatial_5qhull_RidgeIter2D) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 811; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_SetAttrString(__pyx_m, "RidgeIter2D", (PyObject *)&__pyx_type_5scipy_7spatial_5qhull_RidgeIter2D) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 811; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_ptype_5scipy_7spatial_5qhull_RidgeIter2D = &__pyx_type_5scipy_7spatial_5qhull_RidgeIter2D;
  
  __pyx_ptype_7cpython_4type_type = __Pyx_ImportType(__Pyx_BUILTIN_MODULE_NAME, "type", 
  #if CYTHON_COMPILING_IN_PYPY
  sizeof(PyTypeObject),
  #else
  sizeof(PyHeapTypeObject),
  #endif
  0); if (unlikely(!__pyx_ptype_7cpython_4type_type)) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 9; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_ptype_5numpy_dtype = __Pyx_ImportType("numpy", "dtype", sizeof(PyArray_Descr), 0); if (unlikely(!__pyx_ptype_5numpy_dtype)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 155; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_ptype_5numpy_flatiter = __Pyx_ImportType("numpy", "flatiter", sizeof(PyArrayIterObject), 0); if (unlikely(!__pyx_ptype_5numpy_flatiter)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 165; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_ptype_5numpy_broadcast = __Pyx_ImportType("numpy", "broadcast", sizeof(PyArrayMultiIterObject), 0); if (unlikely(!__pyx_ptype_5numpy_broadcast)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 169; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_ptype_5numpy_ndarray = __Pyx_ImportType("numpy", "ndarray", sizeof(PyArrayObject), 0); if (unlikely(!__pyx_ptype_5numpy_ndarray)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 178; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_ptype_5numpy_ufunc = __Pyx_ImportType("numpy", "ufunc", sizeof(PyUFuncObject), 0); if (unlikely(!__pyx_ptype_5numpy_ufunc)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 861; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  
  
  

  
  __pyx_t_1 = __Pyx_Import(((PyObject *)__pyx_n_s__threading), 0, -1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 13; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyObject_SetAttr(__pyx_m, __pyx_n_s__threading, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 13; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  
  __pyx_t_1 = __Pyx_Import(((PyObject *)__pyx_n_s__numpy), 0, -1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 14; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyObject_SetAttr(__pyx_m, __pyx_n_s__np, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 14; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  
  __pyx_t_1 = PyList_New(2); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 19; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__Delaunay));
  PyList_SET_ITEM(__pyx_t_1, 0, ((PyObject *)__pyx_n_s__Delaunay));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__Delaunay));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__tsearch));
  PyList_SET_ITEM(__pyx_t_1, 1, ((PyObject *)__pyx_n_s__tsearch));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__tsearch));
  if (PyObject_SetAttr(__pyx_m, __pyx_n_s____all__, ((PyObject *)__pyx_t_1)) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 19; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;

  
  __pyx_t_1 = __Pyx_GetName(__pyx_m, __pyx_n_s__threading); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 150; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_n_s__Lock); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 150; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 150; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if (PyObject_SetAttr(__pyx_m, __pyx_n_s___qhull_lock, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 150; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  
  __Pyx_INCREF(Py_None);
  __Pyx_XGOTREF(__pyx_v_5scipy_7spatial_5qhull__active_qhull);
  __Pyx_DECREF(__pyx_v_5scipy_7spatial_5qhull__active_qhull);
  __Pyx_GIVEREF(Py_None);
  __pyx_v_5scipy_7spatial_5qhull__active_qhull = Py_None;

  
  __pyx_t_1 = __Pyx_PyBool_FromLong(1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 175; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_k_1 = __pyx_t_1;
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;

  
  __pyx_t_1 = __Pyx_PyBool_FromLong(0); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 176; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_k_2 = __pyx_t_1;
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;

  
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 479; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(((PyObject *)__pyx_t_1));
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 479; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_builtin_RuntimeError);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_builtin_RuntimeError);
  __Pyx_GIVEREF(__pyx_builtin_RuntimeError);
  __pyx_t_3 = __Pyx_CreateClass(((PyObject *)__pyx_t_2), ((PyObject *)__pyx_t_1), __pyx_n_s__QhullError, __pyx_n_s_49); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 479; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  if (PyObject_SetAttr(__pyx_m, __pyx_n_s__QhullError, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 479; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;

  
  __pyx_t_1 = PyCFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_1_get_barycentric_transforms, NULL, __pyx_n_s_49); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 488; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyObject_SetAttr(__pyx_m, __pyx_n_s_25, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 488; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(((PyObject *)__pyx_t_1));

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_1__init__, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_54)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1196; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  if (!__Pyx_CyFunction_InitDefaults(__pyx_t_3, sizeof(__pyx_defaults), 1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1196; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_2 = __Pyx_PyBool_FromLong(0); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1196; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_CyFunction_Defaults(__pyx_defaults, __pyx_t_3)->__pyx_arg_incremental = __pyx_t_2;
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __Pyx_CyFunction_SetDefaultsGetter(__pyx_t_3, __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_38__defaults__);
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s____init__, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1196; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_3add_points, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_56)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1213; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s__add_points, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1213; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_5_flush, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_58)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1216; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  if (!__Pyx_CyFunction_InitDefaults(__pyx_t_3, sizeof(__pyx_defaults1), 1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1216; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_2 = __Pyx_PyBool_FromLong(0); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1216; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_CyFunction_Defaults(__pyx_defaults1, __pyx_t_3)->__pyx_arg_force = __pyx_t_2;
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __Pyx_CyFunction_SetDefaultsGetter(__pyx_t_3, __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_40__defaults__);
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s___flush, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1216; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_7points, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_60)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1228; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1227; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_Call(__pyx_builtin_property, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1227; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s__points, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1228; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_9vertices, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_62)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1233; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1232; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_Call(__pyx_builtin_property, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1232; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s__vertices, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1233; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_11neighbors, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_64)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1238; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1237; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_Call(__pyx_builtin_property, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1237; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s__neighbors, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1238; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_13equations, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_66)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1243; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1242; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_Call(__pyx_builtin_property, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1242; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s__equations, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1243; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_15npoints, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_68)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1248; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1247; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_Call(__pyx_builtin_property, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1247; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s__npoints, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1248; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_17nsimplex, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_70)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1253; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1252; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_Call(__pyx_builtin_property, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1252; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s__nsimplex, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1253; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_19min_bound, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_72)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1258; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1257; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_Call(__pyx_builtin_property, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1257; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s__min_bound, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1258; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_21max_bound, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_74)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1263; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1262; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_Call(__pyx_builtin_property, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1262; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s__max_bound, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1263; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_23paraboloid_scale, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_76)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1268; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1267; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_Call(__pyx_builtin_property, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1267; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s__paraboloid_scale, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1268; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_25paraboloid_shift, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_78)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1272; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1271; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_Call(__pyx_builtin_property, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1271; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s__paraboloid_shift, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1272; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_27transform, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_80)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1275; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_Call(__pyx_builtin_property, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1275; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s__transform, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_29vertex_to_simplex, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_82)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1301; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1299; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_Call(__pyx_builtin_property, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1299; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s__vertex_to_simplex, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1301; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_31convex_hull, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_84)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1332; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1330; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_Call(__pyx_builtin_property, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1330; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s__convex_hull, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1332; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_33find_simplex, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_86)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1385; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  if (!__Pyx_CyFunction_InitDefaults(__pyx_t_3, sizeof(__pyx_defaults2), 1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1385; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_2 = __Pyx_PyBool_FromLong(0); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1385; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_CyFunction_Defaults(__pyx_defaults2, __pyx_t_3)->__pyx_arg_bruteforce = __pyx_t_2;
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __Pyx_CyFunction_SetDefaultsGetter(__pyx_t_3, __pyx_pf_5scipy_7spatial_5qhull_8Delaunay_42__defaults__);
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s__find_simplex, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1385; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_35plane_distance, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_88)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1466; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s__plane_distance, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1466; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_8Delaunay_37lift_points, 0, NULL, __pyx_n_s_49, ((PyObject *)__pyx_k_codeobj_90)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1500; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s__lift_points, __pyx_t_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1500; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  
  __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_INCREF(__pyx_builtin_object);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_builtin_object);
  __Pyx_GIVEREF(__pyx_builtin_object);
  if (PyDict_SetItemString(((PyObject *)__pyx_t_1), "__doc__", ((PyObject *)__pyx_kp_s_91)) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_2 = __Pyx_CreateClass(((PyObject *)__pyx_t_3), ((PyObject *)__pyx_t_1), __pyx_n_s__Delaunay, __pyx_n_s_49); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(((PyObject *)__pyx_t_3)); __pyx_t_3 = 0;
  if (PyObject_SetAttr(__pyx_m, __pyx_n_s__Delaunay, __pyx_t_2) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;

  
  __pyx_t_1 = PyCFunction_NewEx(&__pyx_mdef_5scipy_7spatial_5qhull_3tsearch, NULL, __pyx_n_s_49); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1515; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyObject_SetAttr(__pyx_m, __pyx_n_s__tsearch, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1515; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(((PyObject *)__pyx_t_1));
  if (PyObject_SetAttr(__pyx_m, __pyx_n_s____test__, ((PyObject *)__pyx_t_1)) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;

  
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  if (__pyx_m) {
    __Pyx_AddTraceback("init scipy.spatial.qhull", __pyx_clineno, __pyx_lineno, __pyx_filename);
    Py_DECREF(__pyx_m); __pyx_m = 0;
  } else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_ImportError, "init scipy.spatial.qhull");
  }
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  #if PY_MAJOR_VERSION < 3
  return;
  #else
  return __pyx_m;
  #endif
}


#if CYTHON_REFNANNY
static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname) {
    PyObject *m = NULL, *p = NULL;
    void *r = NULL;
    m = PyImport_ImportModule((char *)modname);
    if (!m) goto end;
    p = PyObject_GetAttrString(m, (char *)"RefNannyAPI");
    if (!p) goto end;
    r = PyLong_AsVoidPtr(p);
end:
    Py_XDECREF(p);
    Py_XDECREF(m);
    return (__Pyx_RefNannyAPIStruct *)r;
}
#endif 

static PyObject *__Pyx_GetName(PyObject *dict, PyObject *name) {
    PyObject *result;
    result = PyObject_GetAttr(dict, name);
    if (!result) {
        if (dict != __pyx_b) {
            PyErr_Clear();
            result = PyObject_GetAttr(__pyx_b, name);
        }
        if (!result) {
            PyErr_SetObject(PyExc_NameError, name);
        }
    }
    return result;
}

static void __Pyx_RaiseDoubleKeywordsError(
    const char* func_name,
    PyObject* kw_name)
{
    PyErr_Format(PyExc_TypeError,
        #if PY_MAJOR_VERSION >= 3
        "%s() got multiple values for keyword argument '%U'", func_name, kw_name);
        #else
        "%s() got multiple values for keyword argument '%s'", func_name,
        PyString_AsString(kw_name));
        #endif
}

static int __Pyx_ParseOptionalKeywords(
    PyObject *kwds,
    PyObject **argnames[],
    PyObject *kwds2,
    PyObject *values[],
    Py_ssize_t num_pos_args,
    const char* function_name)
{
    PyObject *key = 0, *value = 0;
    Py_ssize_t pos = 0;
    PyObject*** name;
    PyObject*** first_kw_arg = argnames + num_pos_args;
    while (PyDict_Next(kwds, &pos, &key, &value)) {
        name = first_kw_arg;
        while (*name && (**name != key)) name++;
        if (*name) {
            values[name-argnames] = value;
            continue;
        }
        name = first_kw_arg;
        #if PY_MAJOR_VERSION < 3
        if (likely(PyString_CheckExact(key)) || likely(PyString_Check(key))) {
            while (*name) {
                if ((CYTHON_COMPILING_IN_PYPY || PyString_GET_SIZE(**name) == PyString_GET_SIZE(key))
                        && _PyString_Eq(**name, key)) {
                    values[name-argnames] = value;
                    break;
                }
                name++;
            }
            if (*name) continue;
            else {
                PyObject*** argname = argnames;
                while (argname != first_kw_arg) {
                    if ((**argname == key) || (
                            (CYTHON_COMPILING_IN_PYPY || PyString_GET_SIZE(**argname) == PyString_GET_SIZE(key))
                             && _PyString_Eq(**argname, key))) {
                        goto arg_passed_twice;
                    }
                    argname++;
                }
            }
        } else
        #endif
        if (likely(PyUnicode_Check(key))) {
            while (*name) {
                int cmp = (**name == key) ? 0 :
                #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION >= 3
                    (PyUnicode_GET_SIZE(**name) != PyUnicode_GET_SIZE(key)) ? 1 :
                #endif
                    PyUnicode_Compare(**name, key);
                if (cmp < 0 && unlikely(PyErr_Occurred())) goto bad;
                if (cmp == 0) {
                    values[name-argnames] = value;
                    break;
                }
                name++;
            }
            if (*name) continue;
            else {
                PyObject*** argname = argnames;
                while (argname != first_kw_arg) {
                    int cmp = (**argname == key) ? 0 :
                    #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION >= 3
                        (PyUnicode_GET_SIZE(**argname) != PyUnicode_GET_SIZE(key)) ? 1 :
                    #endif
                        PyUnicode_Compare(**argname, key);
                    if (cmp < 0 && unlikely(PyErr_Occurred())) goto bad;
                    if (cmp == 0) goto arg_passed_twice;
                    argname++;
                }
            }
        } else
            goto invalid_keyword_type;
        if (kwds2) {
            if (unlikely(PyDict_SetItem(kwds2, key, value))) goto bad;
        } else {
            goto invalid_keyword;
        }
    }
    return 0;
arg_passed_twice:
    __Pyx_RaiseDoubleKeywordsError(function_name, key);
    goto bad;
invalid_keyword_type:
    PyErr_Format(PyExc_TypeError,
        "%s() keywords must be strings", function_name);
    goto bad;
invalid_keyword:
    PyErr_Format(PyExc_TypeError,
    #if PY_MAJOR_VERSION < 3
        "%s() got an unexpected keyword argument '%s'",
        function_name, PyString_AsString(key));
    #else
        "%s() got an unexpected keyword argument '%U'",
        function_name, key);
    #endif
bad:
    return -1;
}

static void __Pyx_RaiseArgtupleInvalid(
    const char* func_name,
    int exact,
    Py_ssize_t num_min,
    Py_ssize_t num_max,
    Py_ssize_t num_found)
{
    Py_ssize_t num_expected;
    const char *more_or_less;
    if (num_found < num_min) {
        num_expected = num_min;
        more_or_less = "at least";
    } else {
        num_expected = num_max;
        more_or_less = "at most";
    }
    if (exact) {
        more_or_less = "exactly";
    }
    PyErr_Format(PyExc_TypeError,
                 "%s() takes %s %" CYTHON_FORMAT_SSIZE_T "d positional argument%s (%" CYTHON_FORMAT_SSIZE_T "d given)",
                 func_name, more_or_less, num_expected,
                 (num_expected == 1) ? "" : "s", num_found);
}

static int __Pyx_ArgTypeTest(PyObject *obj, PyTypeObject *type, int none_allowed,
    const char *name, int exact)
{
    if (!type) {
        PyErr_Format(PyExc_SystemError, "Missing type object");
        return 0;
    }
    if (none_allowed && obj == Py_None) return 1;
    else if (exact) {
        if (Py_TYPE(obj) == type) return 1;
    }
    else {
        if (PyObject_TypeCheck(obj, type)) return 1;
    }
    PyErr_Format(PyExc_TypeError,
        "Argument '%s' has incorrect type (expected %s, got %s)",
        name, type->tp_name, Py_TYPE(obj)->tp_name);
    return 0;
}

static CYTHON_INLINE int __Pyx_IsLittleEndian(void) {
  unsigned int n = 1;
  return *(unsigned char*)(&n) != 0;
}
static void __Pyx_BufFmt_Init(__Pyx_BufFmt_Context* ctx,
                              __Pyx_BufFmt_StackElem* stack,
                              __Pyx_TypeInfo* type) {
  stack[0].field = &ctx->root;
  stack[0].parent_offset = 0;
  ctx->root.type = type;
  ctx->root.name = "buffer dtype";
  ctx->root.offset = 0;
  ctx->head = stack;
  ctx->head->field = &ctx->root;
  ctx->fmt_offset = 0;
  ctx->head->parent_offset = 0;
  ctx->new_packmode = '@';
  ctx->enc_packmode = '@';
  ctx->new_count = 1;
  ctx->enc_count = 0;
  ctx->enc_type = 0;
  ctx->is_complex = 0;
  ctx->is_valid_array = 0;
  ctx->struct_alignment = 0;
  while (type->typegroup == 'S') {
    ++ctx->head;
    ctx->head->field = type->fields;
    ctx->head->parent_offset = 0;
    type = type->fields->type;
  }
}
static int __Pyx_BufFmt_ParseNumber(const char** ts) {
    int count;
    const char* t = *ts;
    if (*t < '0' || *t > '9') {
      return -1;
    } else {
        count = *t++ - '0';
        while (*t >= '0' && *t < '9') {
            count *= 10;
            count += *t++ - '0';
        }
    }
    *ts = t;
    return count;
}
static int __Pyx_BufFmt_ExpectNumber(const char **ts) {
    int number = __Pyx_BufFmt_ParseNumber(ts);
    if (number == -1) 
        PyErr_Format(PyExc_ValueError,\
                     "Does not understand character buffer dtype format string ('%c')", **ts);
    return number;
}
static void __Pyx_BufFmt_RaiseUnexpectedChar(char ch) {
  PyErr_Format(PyExc_ValueError,
               "Unexpected format string character: '%c'", ch);
}
static const char* __Pyx_BufFmt_DescribeTypeChar(char ch, int is_complex) {
  switch (ch) {
    case 'c': return "'char'";
    case 'b': return "'signed char'";
    case 'B': return "'unsigned char'";
    case 'h': return "'short'";
    case 'H': return "'unsigned short'";
    case 'i': return "'int'";
    case 'I': return "'unsigned int'";
    case 'l': return "'long'";
    case 'L': return "'unsigned long'";
    case 'q': return "'long long'";
    case 'Q': return "'unsigned long long'";
    case 'f': return (is_complex ? "'complex float'" : "'float'");
    case 'd': return (is_complex ? "'complex double'" : "'double'");
    case 'g': return (is_complex ? "'complex long double'" : "'long double'");
    case 'T': return "a struct";
    case 'O': return "Python object";
    case 'P': return "a pointer";
    case 's': case 'p': return "a string";
    case 0: return "end";
    default: return "unparseable format string";
  }
}
static size_t __Pyx_BufFmt_TypeCharToStandardSize(char ch, int is_complex) {
  switch (ch) {
    case '?': case 'c': case 'b': case 'B': case 's': case 'p': return 1;
    case 'h': case 'H': return 2;
    case 'i': case 'I': case 'l': case 'L': return 4;
    case 'q': case 'Q': return 8;
    case 'f': return (is_complex ? 8 : 4);
    case 'd': return (is_complex ? 16 : 8);
    case 'g': {
      PyErr_SetString(PyExc_ValueError, "Python does not define a standard format string size for long double ('g')..");
      return 0;
    }
    case 'O': case 'P': return sizeof(void*);
    default:
      __Pyx_BufFmt_RaiseUnexpectedChar(ch);
      return 0;
    }
}
static size_t __Pyx_BufFmt_TypeCharToNativeSize(char ch, int is_complex) {
  switch (ch) {
    case 'c': case 'b': case 'B': case 's': case 'p': return 1;
    case 'h': case 'H': return sizeof(short);
    case 'i': case 'I': return sizeof(int);
    case 'l': case 'L': return sizeof(long);
    #ifdef HAVE_LONG_LONG
    case 'q': case 'Q': return sizeof(PY_LONG_LONG);
    #endif
    case 'f': return sizeof(float) * (is_complex ? 2 : 1);
    case 'd': return sizeof(double) * (is_complex ? 2 : 1);
    case 'g': return sizeof(long double) * (is_complex ? 2 : 1);
    case 'O': case 'P': return sizeof(void*);
    default: {
      __Pyx_BufFmt_RaiseUnexpectedChar(ch);
      return 0;
    }
  }
}
typedef struct { char c; short x; } __Pyx_st_short;
typedef struct { char c; int x; } __Pyx_st_int;
typedef struct { char c; long x; } __Pyx_st_long;
typedef struct { char c; float x; } __Pyx_st_float;
typedef struct { char c; double x; } __Pyx_st_double;
typedef struct { char c; long double x; } __Pyx_st_longdouble;
typedef struct { char c; void *x; } __Pyx_st_void_p;
#ifdef HAVE_LONG_LONG
typedef struct { char c; PY_LONG_LONG x; } __Pyx_st_longlong;
#endif
static size_t __Pyx_BufFmt_TypeCharToAlignment(char ch, CYTHON_UNUSED int is_complex) {
  switch (ch) {
    case '?': case 'c': case 'b': case 'B': case 's': case 'p': return 1;
    case 'h': case 'H': return sizeof(__Pyx_st_short) - sizeof(short);
    case 'i': case 'I': return sizeof(__Pyx_st_int) - sizeof(int);
    case 'l': case 'L': return sizeof(__Pyx_st_long) - sizeof(long);
#ifdef HAVE_LONG_LONG
    case 'q': case 'Q': return sizeof(__Pyx_st_longlong) - sizeof(PY_LONG_LONG);
#endif
    case 'f': return sizeof(__Pyx_st_float) - sizeof(float);
    case 'd': return sizeof(__Pyx_st_double) - sizeof(double);
    case 'g': return sizeof(__Pyx_st_longdouble) - sizeof(long double);
    case 'P': case 'O': return sizeof(__Pyx_st_void_p) - sizeof(void*);
    default:
      __Pyx_BufFmt_RaiseUnexpectedChar(ch);
      return 0;
    }
}

typedef struct { short x; char c; } __Pyx_pad_short;
typedef struct { int x; char c; } __Pyx_pad_int;
typedef struct { long x; char c; } __Pyx_pad_long;
typedef struct { float x; char c; } __Pyx_pad_float;
typedef struct { double x; char c; } __Pyx_pad_double;
typedef struct { long double x; char c; } __Pyx_pad_longdouble;
typedef struct { void *x; char c; } __Pyx_pad_void_p;
#ifdef HAVE_LONG_LONG
typedef struct { PY_LONG_LONG x; char c; } __Pyx_pad_longlong;
#endif
static size_t __Pyx_BufFmt_TypeCharToPadding(char ch, CYTHON_UNUSED int is_complex) {
  switch (ch) {
    case '?': case 'c': case 'b': case 'B': case 's': case 'p': return 1;
    case 'h': case 'H': return sizeof(__Pyx_pad_short) - sizeof(short);
    case 'i': case 'I': return sizeof(__Pyx_pad_int) - sizeof(int);
    case 'l': case 'L': return sizeof(__Pyx_pad_long) - sizeof(long);
#ifdef HAVE_LONG_LONG
    case 'q': case 'Q': return sizeof(__Pyx_pad_longlong) - sizeof(PY_LONG_LONG);
#endif
    case 'f': return sizeof(__Pyx_pad_float) - sizeof(float);
    case 'd': return sizeof(__Pyx_pad_double) - sizeof(double);
    case 'g': return sizeof(__Pyx_pad_longdouble) - sizeof(long double);
    case 'P': case 'O': return sizeof(__Pyx_pad_void_p) - sizeof(void*);
    default:
      __Pyx_BufFmt_RaiseUnexpectedChar(ch);
      return 0;
    }
}
static char __Pyx_BufFmt_TypeCharToGroup(char ch, int is_complex) {
  switch (ch) {
    case 'c':
        return 'H';
    case 'b': case 'h': case 'i':
    case 'l': case 'q': case 's': case 'p':
        return 'I';
    case 'B': case 'H': case 'I': case 'L': case 'Q':
        return 'U';
    case 'f': case 'd': case 'g':
        return (is_complex ? 'C' : 'R');
    case 'O':
        return 'O';
    case 'P':
        return 'P';
    default: {
      __Pyx_BufFmt_RaiseUnexpectedChar(ch);
      return 0;
    }
  }
}
static void __Pyx_BufFmt_RaiseExpected(__Pyx_BufFmt_Context* ctx) {
  if (ctx->head == NULL || ctx->head->field == &ctx->root) {
    const char* expected;
    const char* quote;
    if (ctx->head == NULL) {
      expected = "end";
      quote = "";
    } else {
      expected = ctx->head->field->type->name;
      quote = "'";
    }
    PyErr_Format(PyExc_ValueError,
                 "Buffer dtype mismatch, expected %s%s%s but got %s",
                 quote, expected, quote,
                 __Pyx_BufFmt_DescribeTypeChar(ctx->enc_type, ctx->is_complex));
  } else {
    __Pyx_StructField* field = ctx->head->field;
    __Pyx_StructField* parent = (ctx->head - 1)->field;
    PyErr_Format(PyExc_ValueError,
                 "Buffer dtype mismatch, expected '%s' but got %s in '%s.%s'",
                 field->type->name, __Pyx_BufFmt_DescribeTypeChar(ctx->enc_type, ctx->is_complex),
                 parent->type->name, field->name);
  }
}
static int __Pyx_BufFmt_ProcessTypeChunk(__Pyx_BufFmt_Context* ctx) {
  char group;
  size_t size, offset, arraysize = 1;
  if (ctx->enc_type == 0) return 0;
  if (ctx->head->field->type->arraysize[0]) {
    int i, ndim = 0;
    if (ctx->enc_type == 's' || ctx->enc_type == 'p') {
        ctx->is_valid_array = ctx->head->field->type->ndim == 1;
        ndim = 1;
        if (ctx->enc_count != ctx->head->field->type->arraysize[0]) {
            PyErr_Format(PyExc_ValueError,
                         "Expected a dimension of size %zu, got %zu",
                         ctx->head->field->type->arraysize[0], ctx->enc_count);
            return -1;
        }
    }
    if (!ctx->is_valid_array) {
      PyErr_Format(PyExc_ValueError, "Expected %d dimensions, got %d",
                   ctx->head->field->type->ndim, ndim);
      return -1;
    }
    for (i = 0; i < ctx->head->field->type->ndim; i++) {
      arraysize *= ctx->head->field->type->arraysize[i];
    }
    ctx->is_valid_array = 0;
    ctx->enc_count = 1;
  }
  group = __Pyx_BufFmt_TypeCharToGroup(ctx->enc_type, ctx->is_complex);
  do {
    __Pyx_StructField* field = ctx->head->field;
    __Pyx_TypeInfo* type = field->type;
    if (ctx->enc_packmode == '@' || ctx->enc_packmode == '^') {
      size = __Pyx_BufFmt_TypeCharToNativeSize(ctx->enc_type, ctx->is_complex);
    } else {
      size = __Pyx_BufFmt_TypeCharToStandardSize(ctx->enc_type, ctx->is_complex);
    }
    if (ctx->enc_packmode == '@') {
      size_t align_at = __Pyx_BufFmt_TypeCharToAlignment(ctx->enc_type, ctx->is_complex);
      size_t align_mod_offset;
      if (align_at == 0) return -1;
      align_mod_offset = ctx->fmt_offset % align_at;
      if (align_mod_offset > 0) ctx->fmt_offset += align_at - align_mod_offset;
      if (ctx->struct_alignment == 0)
          ctx->struct_alignment = __Pyx_BufFmt_TypeCharToPadding(ctx->enc_type,
                                                                 ctx->is_complex);
    }
    if (type->size != size || type->typegroup != group) {
      if (type->typegroup == 'C' && type->fields != NULL) {
        size_t parent_offset = ctx->head->parent_offset + field->offset;
        ++ctx->head;
        ctx->head->field = type->fields;
        ctx->head->parent_offset = parent_offset;
        continue;
      }
      if ((type->typegroup == 'H' || group == 'H') && type->size == size) {
      } else {
          __Pyx_BufFmt_RaiseExpected(ctx);
          return -1;
      }
    }
    offset = ctx->head->parent_offset + field->offset;
    if (ctx->fmt_offset != offset) {
      PyErr_Format(PyExc_ValueError,
                   "Buffer dtype mismatch; next field is at offset %" CYTHON_FORMAT_SSIZE_T "d but %" CYTHON_FORMAT_SSIZE_T "d expected",
                   (Py_ssize_t)ctx->fmt_offset, (Py_ssize_t)offset);
      return -1;
    }
    ctx->fmt_offset += size;
    if (arraysize)
      ctx->fmt_offset += (arraysize - 1) * size;
    --ctx->enc_count; 
    while (1) {
      if (field == &ctx->root) {
        ctx->head = NULL;
        if (ctx->enc_count != 0) {
          __Pyx_BufFmt_RaiseExpected(ctx);
          return -1;
        }
        break; 
      }
      ctx->head->field = ++field;
      if (field->type == NULL) {
        --ctx->head;
        field = ctx->head->field;
        continue;
      } else if (field->type->typegroup == 'S') {
        size_t parent_offset = ctx->head->parent_offset + field->offset;
        if (field->type->fields->type == NULL) continue; 
        field = field->type->fields;
        ++ctx->head;
        ctx->head->field = field;
        ctx->head->parent_offset = parent_offset;
        break;
      } else {
        break;
      }
    }
  } while (ctx->enc_count);
  ctx->enc_type = 0;
  ctx->is_complex = 0;
  return 0;
}
static CYTHON_INLINE PyObject *
__pyx_buffmt_parse_array(__Pyx_BufFmt_Context* ctx, const char** tsp)
{
    const char *ts = *tsp;
    int i = 0, number;
    int ndim = ctx->head->field->type->ndim;
;
    ++ts;
    if (ctx->new_count != 1) {
        PyErr_SetString(PyExc_ValueError,
                        "Cannot handle repeated arrays in format string");
        return NULL;
    }
    if (__Pyx_BufFmt_ProcessTypeChunk(ctx) == -1) return NULL;
    while (*ts && *ts != ')') {
        if (isspace(*ts))
            continue;
        number = __Pyx_BufFmt_ExpectNumber(&ts);
        if (number == -1) return NULL;
        if (i < ndim && (size_t) number != ctx->head->field->type->arraysize[i])
            return PyErr_Format(PyExc_ValueError,
                        "Expected a dimension of size %zu, got %d",
                        ctx->head->field->type->arraysize[i], number);
        if (*ts != ',' && *ts != ')')
            return PyErr_Format(PyExc_ValueError,
                                "Expected a comma in format string, got '%c'", *ts);
        if (*ts == ',') ts++;
        i++;
    }
    if (i != ndim)
        return PyErr_Format(PyExc_ValueError, "Expected %d dimension(s), got %d",
                            ctx->head->field->type->ndim, i);
    if (!*ts) {
        PyErr_SetString(PyExc_ValueError,
                        "Unexpected end of format string, expected ')'");
        return NULL;
    }
    ctx->is_valid_array = 1;
    ctx->new_count = 1;
    *tsp = ++ts;
    return Py_None;
}
static const char* __Pyx_BufFmt_CheckString(__Pyx_BufFmt_Context* ctx, const char* ts) {
  int got_Z = 0;
  while (1) {
    switch(*ts) {
      case 0:
        if (ctx->enc_type != 0 && ctx->head == NULL) {
          __Pyx_BufFmt_RaiseExpected(ctx);
          return NULL;
        }
        if (__Pyx_BufFmt_ProcessTypeChunk(ctx) == -1) return NULL;
        if (ctx->head != NULL) {
          __Pyx_BufFmt_RaiseExpected(ctx);
          return NULL;
        }
                return ts;
      case ' ':
      case 10:
      case 13:
        ++ts;
        break;
      case '<':
        if (!__Pyx_IsLittleEndian()) {
          PyErr_SetString(PyExc_ValueError, "Little-endian buffer not supported on big-endian compiler");
          return NULL;
        }
        ctx->new_packmode = '=';
        ++ts;
        break;
      case '>':
      case '!':
        if (__Pyx_IsLittleEndian()) {
          PyErr_SetString(PyExc_ValueError, "Big-endian buffer not supported on little-endian compiler");
          return NULL;
        }
        ctx->new_packmode = '=';
        ++ts;
        break;
      case '=':
      case '@':
      case '^':
        ctx->new_packmode = *ts++;
        break;
      case 'T': 
        {
          const char* ts_after_sub;
          size_t i, struct_count = ctx->new_count;
          size_t struct_alignment = ctx->struct_alignment;
          ctx->new_count = 1;
          ++ts;
          if (*ts != '{') {
            PyErr_SetString(PyExc_ValueError, "Buffer acquisition: Expected '{' after 'T'");
            return NULL;
          }
          if (__Pyx_BufFmt_ProcessTypeChunk(ctx) == -1) return NULL;
          ctx->enc_type = 0; 
          ctx->enc_count = 0;
          ctx->struct_alignment = 0;
          ++ts;
          ts_after_sub = ts;
          for (i = 0; i != struct_count; ++i) {
            ts_after_sub = __Pyx_BufFmt_CheckString(ctx, ts);
            if (!ts_after_sub) return NULL;
          }
          ts = ts_after_sub;
          if (struct_alignment) ctx->struct_alignment = struct_alignment;
        }
        break;
      case '}': 
        {
          size_t alignment = ctx->struct_alignment;
          ++ts;
          if (__Pyx_BufFmt_ProcessTypeChunk(ctx) == -1) return NULL;
          ctx->enc_type = 0; 
          if (alignment && ctx->fmt_offset % alignment) {
            ctx->fmt_offset += alignment - (ctx->fmt_offset % alignment);
          }
        }
        return ts;
      case 'x':
        if (__Pyx_BufFmt_ProcessTypeChunk(ctx) == -1) return NULL;
        ctx->fmt_offset += ctx->new_count;
        ctx->new_count = 1;
        ctx->enc_count = 0;
        ctx->enc_type = 0;
        ctx->enc_packmode = ctx->new_packmode;
        ++ts;
        break;
      case 'Z':
        got_Z = 1;
        ++ts;
        if (*ts != 'f' && *ts != 'd' && *ts != 'g') {
          __Pyx_BufFmt_RaiseUnexpectedChar('Z');
          return NULL;
        }        
      case 'c': case 'b': case 'B': case 'h': case 'H': case 'i': case 'I':
      case 'l': case 'L': case 'q': case 'Q':
      case 'f': case 'd': case 'g':
      case 'O': case 's': case 'p':
        if (ctx->enc_type == *ts && got_Z == ctx->is_complex &&
            ctx->enc_packmode == ctx->new_packmode) {
          ctx->enc_count += ctx->new_count;
        } else {
          if (__Pyx_BufFmt_ProcessTypeChunk(ctx) == -1) return NULL;
          ctx->enc_count = ctx->new_count;
          ctx->enc_packmode = ctx->new_packmode;
          ctx->enc_type = *ts;
          ctx->is_complex = got_Z;
        }
        ++ts;
        ctx->new_count = 1;
        got_Z = 0;
        break;
      case ':':
        ++ts;
        while(*ts != ':') ++ts;
        ++ts;
        break;
      case '(':
        if (!__pyx_buffmt_parse_array(ctx, &ts)) return NULL;
        break;
      default:
        {
          int number = __Pyx_BufFmt_ExpectNumber(&ts);
          if (number == -1) return NULL;
          ctx->new_count = (size_t)number;
        }
    }
  }
}
static CYTHON_INLINE void __Pyx_ZeroBuffer(Py_buffer* buf) {
  buf->buf = NULL;
  buf->obj = NULL;
  buf->strides = __Pyx_zeros;
  buf->shape = __Pyx_zeros;
  buf->suboffsets = __Pyx_minusones;
}
static CYTHON_INLINE int __Pyx_GetBufferAndValidate(
        Py_buffer* buf, PyObject* obj,  __Pyx_TypeInfo* dtype, int flags,
        int nd, int cast, __Pyx_BufFmt_StackElem* stack)
{
  if (obj == Py_None || obj == NULL) {
    __Pyx_ZeroBuffer(buf);
    return 0;
  }
  buf->buf = NULL;
  if (__Pyx_GetBuffer(obj, buf, flags) == -1) goto fail;
  if (buf->ndim != nd) {
    PyErr_Format(PyExc_ValueError,
                 "Buffer has wrong number of dimensions (expected %d, got %d)",
                 nd, buf->ndim);
    goto fail;
  }
  if (!cast) {
    __Pyx_BufFmt_Context ctx;
    __Pyx_BufFmt_Init(&ctx, stack, dtype);
    if (!__Pyx_BufFmt_CheckString(&ctx, buf->format)) goto fail;
  }
  if ((unsigned)buf->itemsize != dtype->size) {
    PyErr_Format(PyExc_ValueError,
      "Item size of buffer (%" CYTHON_FORMAT_SSIZE_T "d byte%s) does not match size of '%s' (%" CYTHON_FORMAT_SSIZE_T "d byte%s)",
      buf->itemsize, (buf->itemsize > 1) ? "s" : "",
      dtype->name, (Py_ssize_t)dtype->size, (dtype->size > 1) ? "s" : "");
    goto fail;
  }
  if (buf->suboffsets == NULL) buf->suboffsets = __Pyx_minusones;
  return 0;
fail:;
  __Pyx_ZeroBuffer(buf);
  return -1;
}
static CYTHON_INLINE void __Pyx_SafeReleaseBuffer(Py_buffer* info) {
  if (info->buf == NULL) return;
  if (info->suboffsets == __Pyx_minusones) info->suboffsets = NULL;
  __Pyx_ReleaseBuffer(info);
}

static CYTHON_INLINE void __Pyx_ErrRestore(PyObject *type, PyObject *value, PyObject *tb) {
#if CYTHON_COMPILING_IN_CPYTHON
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    PyThreadState *tstate = PyThreadState_GET();
    tmp_type = tstate->curexc_type;
    tmp_value = tstate->curexc_value;
    tmp_tb = tstate->curexc_traceback;
    tstate->curexc_type = type;
    tstate->curexc_value = value;
    tstate->curexc_traceback = tb;
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
#else
    PyErr_Restore(type, value, tb);
#endif
}
static CYTHON_INLINE void __Pyx_ErrFetch(PyObject **type, PyObject **value, PyObject **tb) {
#if CYTHON_COMPILING_IN_CPYTHON
    PyThreadState *tstate = PyThreadState_GET();
    *type = tstate->curexc_type;
    *value = tstate->curexc_value;
    *tb = tstate->curexc_traceback;
    tstate->curexc_type = 0;
    tstate->curexc_value = 0;
    tstate->curexc_traceback = 0;
#else
    PyErr_Fetch(type, value, tb);
#endif
}

#if PY_MAJOR_VERSION < 3
static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb,
                        CYTHON_UNUSED PyObject *cause) {
    Py_XINCREF(type);
    if (!value || value == Py_None)
        value = NULL;
    else
        Py_INCREF(value);
    if (!tb || tb == Py_None)
        tb = NULL;
    else {
        Py_INCREF(tb);
        if (!PyTraceBack_Check(tb)) {
            PyErr_SetString(PyExc_TypeError,
                "raise: arg 3 must be a traceback or None");
            goto raise_error;
        }
    }
    #if PY_VERSION_HEX < 0x02050000
    if (PyClass_Check(type)) {
    #else
    if (PyType_Check(type)) {
    #endif
#if CYTHON_COMPILING_IN_PYPY
        if (!value) {
            Py_INCREF(Py_None);
            value = Py_None;
        }
#endif
        PyErr_NormalizeException(&type, &value, &tb);
    } else {
        if (value) {
            PyErr_SetString(PyExc_TypeError,
                "instance exception may not have a separate value");
            goto raise_error;
        }
        value = type;
        #if PY_VERSION_HEX < 0x02050000
            if (PyInstance_Check(type)) {
                type = (PyObject*) ((PyInstanceObject*)type)->in_class;
                Py_INCREF(type);
            }
            else {
                type = 0;
                PyErr_SetString(PyExc_TypeError,
                    "raise: exception must be an old-style class or instance");
                goto raise_error;
            }
        #else
            type = (PyObject*) Py_TYPE(type);
            Py_INCREF(type);
            if (!PyType_IsSubtype((PyTypeObject *)type, (PyTypeObject *)PyExc_BaseException)) {
                PyErr_SetString(PyExc_TypeError,
                    "raise: exception class must be a subclass of BaseException");
                goto raise_error;
            }
        #endif
    }
    __Pyx_ErrRestore(type, value, tb);
    return;
raise_error:
    Py_XDECREF(value);
    Py_XDECREF(type);
    Py_XDECREF(tb);
    return;
}
#else 
static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb, PyObject *cause) {
    PyObject* owned_instance = NULL;
    if (tb == Py_None) {
        tb = 0;
    } else if (tb && !PyTraceBack_Check(tb)) {
        PyErr_SetString(PyExc_TypeError,
            "raise: arg 3 must be a traceback or None");
        goto bad;
    }
    if (value == Py_None)
        value = 0;
    if (PyExceptionInstance_Check(type)) {
        if (value) {
            PyErr_SetString(PyExc_TypeError,
                "instance exception may not have a separate value");
            goto bad;
        }
        value = type;
        type = (PyObject*) Py_TYPE(value);
    } else if (PyExceptionClass_Check(type)) {
        PyObject *args;
        if (!value)
            args = PyTuple_New(0);
        else if (PyTuple_Check(value)) {
            Py_INCREF(value);
            args = value;
        }
        else
            args = PyTuple_Pack(1, value);
        if (!args)
            goto bad;
        owned_instance = PyEval_CallObject(type, args);
        Py_DECREF(args);
        if (!owned_instance)
            goto bad;
        value = owned_instance;
        if (!PyExceptionInstance_Check(value)) {
            PyErr_Format(PyExc_TypeError,
                         "calling %R should have returned an instance of "
                         "BaseException, not %R",
                         type, Py_TYPE(value));
            goto bad;
        }
    } else {
        PyErr_SetString(PyExc_TypeError,
            "raise: exception class must be a subclass of BaseException");
        goto bad;
    }
    if (cause && cause != Py_None) {
        PyObject *fixed_cause;
        if (PyExceptionClass_Check(cause)) {
            fixed_cause = PyObject_CallObject(cause, NULL);
            if (fixed_cause == NULL)
                goto bad;
        }
        else if (PyExceptionInstance_Check(cause)) {
            fixed_cause = cause;
            Py_INCREF(fixed_cause);
        }
        else {
            PyErr_SetString(PyExc_TypeError,
                            "exception causes must derive from "
                            "BaseException");
            goto bad;
        }
        PyException_SetCause(value, fixed_cause);
    }
    PyErr_SetObject(type, value);
    if (tb) {
        PyThreadState *tstate = PyThreadState_GET();
        PyObject* tmp_tb = tstate->curexc_traceback;
        if (tb != tmp_tb) {
            Py_INCREF(tb);
            tstate->curexc_traceback = tb;
            Py_XDECREF(tmp_tb);
        }
    }
bad:
    Py_XDECREF(owned_instance);
    return;
}
#endif

static CYTHON_INLINE int __Pyx_TypeTest(PyObject *obj, PyTypeObject *type) {
    if (unlikely(!type)) {
        PyErr_Format(PyExc_SystemError, "Missing type object");
        return 0;
    }
    if (likely(PyObject_TypeCheck(obj, type)))
        return 1;
    PyErr_Format(PyExc_TypeError, "Cannot convert %.200s to %.200s",
                 Py_TYPE(obj)->tp_name, type->tp_name);
    return 0;
}

static void __Pyx_RaiseBufferFallbackError(void) {
  PyErr_Format(PyExc_ValueError,
     "Buffer acquisition failed on assignment; and then reacquiring the old buffer failed too!");
}

static CYTHON_INLINE long __Pyx_div_long(long a, long b) {
    long q = a / b;
    long r = a - q*b;
    q -= ((r != 0) & ((r ^ b) < 0));
    return q;
}

static CYTHON_INLINE void __Pyx_RaiseTooManyValuesError(Py_ssize_t expected) {
    PyErr_Format(PyExc_ValueError,
                 "too many values to unpack (expected %" CYTHON_FORMAT_SSIZE_T "d)", expected);
}

static CYTHON_INLINE void __Pyx_RaiseNeedMoreValuesError(Py_ssize_t index) {
    PyErr_Format(PyExc_ValueError,
                 "need more than %" CYTHON_FORMAT_SSIZE_T "d value%s to unpack",
                 index, (index == 1) ? "" : "s");
}

static CYTHON_INLINE int __Pyx_IterFinish(void) {
#if CYTHON_COMPILING_IN_CPYTHON
    PyThreadState *tstate = PyThreadState_GET();
    PyObject* exc_type = tstate->curexc_type;
    if (unlikely(exc_type)) {
        if (likely(exc_type == PyExc_StopIteration) || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration)) {
            PyObject *exc_value, *exc_tb;
            exc_value = tstate->curexc_value;
            exc_tb = tstate->curexc_traceback;
            tstate->curexc_type = 0;
            tstate->curexc_value = 0;
            tstate->curexc_traceback = 0;
            Py_DECREF(exc_type);
            Py_XDECREF(exc_value);
            Py_XDECREF(exc_tb);
            return 0;
        } else {
            return -1;
        }
    }
    return 0;
#else
    if (unlikely(PyErr_Occurred())) {
        if (likely(PyErr_ExceptionMatches(PyExc_StopIteration))) {
            PyErr_Clear();
            return 0;
        } else {
            return -1;
        }
    }
    return 0;
#endif
}

static int __Pyx_IternextUnpackEndCheck(PyObject *retval, Py_ssize_t expected) {
    if (unlikely(retval)) {
        Py_DECREF(retval);
        __Pyx_RaiseTooManyValuesError(expected);
        return -1;
    } else {
        return __Pyx_IterFinish();
    }
    return 0;
}

static int __Pyx_GetException(PyObject **type, PyObject **value, PyObject **tb) {
    PyObject *local_type, *local_value, *local_tb;
#if CYTHON_COMPILING_IN_CPYTHON
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    PyThreadState *tstate = PyThreadState_GET();
    local_type = tstate->curexc_type;
    local_value = tstate->curexc_value;
    local_tb = tstate->curexc_traceback;
    tstate->curexc_type = 0;
    tstate->curexc_value = 0;
    tstate->curexc_traceback = 0;
#else
    PyErr_Fetch(&local_type, &local_value, &local_tb);
#endif
    PyErr_NormalizeException(&local_type, &local_value, &local_tb);
#if CYTHON_COMPILING_IN_CPYTHON
    if (unlikely(tstate->curexc_type))
#else
    if (unlikely(PyErr_Occurred()))
#endif
        goto bad;
    #if PY_MAJOR_VERSION >= 3
    if (unlikely(PyException_SetTraceback(local_value, local_tb) < 0))
        goto bad;
    #endif
    Py_INCREF(local_type);
    Py_INCREF(local_value);
    Py_INCREF(local_tb);
    *type = local_type;
    *value = local_value;
    *tb = local_tb;
#if CYTHON_COMPILING_IN_CPYTHON
    tmp_type = tstate->exc_type;
    tmp_value = tstate->exc_value;
    tmp_tb = tstate->exc_traceback;
    tstate->exc_type = local_type;
    tstate->exc_value = local_value;
    tstate->exc_traceback = local_tb;
    
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
#else
    PyErr_SetExcInfo(local_type, local_value, local_tb);
#endif
    return 0;
bad:
    *type = 0;
    *value = 0;
    *tb = 0;
    Py_XDECREF(local_type);
    Py_XDECREF(local_value);
    Py_XDECREF(local_tb);
    return -1;
}

static CYTHON_INLINE void __Pyx_RaiseNoneNotIterableError(void) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
}

static CYTHON_INLINE void __Pyx_ExceptionSave(PyObject **type, PyObject **value, PyObject **tb) {
#if CYTHON_COMPILING_IN_CPYTHON
    PyThreadState *tstate = PyThreadState_GET();
    *type = tstate->exc_type;
    *value = tstate->exc_value;
    *tb = tstate->exc_traceback;
    Py_XINCREF(*type);
    Py_XINCREF(*value);
    Py_XINCREF(*tb);
#else
    PyErr_GetExcInfo(type, value, tb);
#endif
}
static void __Pyx_ExceptionReset(PyObject *type, PyObject *value, PyObject *tb) {
#if CYTHON_COMPILING_IN_CPYTHON
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    PyThreadState *tstate = PyThreadState_GET();
    tmp_type = tstate->exc_type;
    tmp_value = tstate->exc_value;
    tmp_tb = tstate->exc_traceback;
    tstate->exc_type = type;
    tstate->exc_value = value;
    tstate->exc_traceback = tb;
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
#else
    PyErr_SetExcInfo(type, value, tb);
#endif
}

#if PY_MAJOR_VERSION < 3
static int __Pyx_GetBuffer(PyObject *obj, Py_buffer *view, int flags) {
    CYTHON_UNUSED PyObject *getbuffer_cobj;
  #if PY_VERSION_HEX >= 0x02060000
    if (PyObject_CheckBuffer(obj)) return PyObject_GetBuffer(obj, view, flags);
  #endif
        if (PyObject_TypeCheck(obj, __pyx_ptype_5numpy_ndarray)) return __pyx_pw_5numpy_7ndarray_1__getbuffer__(obj, view, flags);
  #if PY_VERSION_HEX < 0x02060000
    if (obj->ob_type->tp_dict &&
        (getbuffer_cobj = PyMapping_GetItemString(obj->ob_type->tp_dict,
                                             "__pyx_getbuffer"))) {
        getbufferproc func;
      #if PY_VERSION_HEX >= 0x02070000 && !(PY_MAJOR_VERSION == 3 && PY_MINOR_VERSION == 0)
        func = (getbufferproc) PyCapsule_GetPointer(getbuffer_cobj, "getbuffer(obj, view, flags)");
      #else
        func = (getbufferproc) PyCObject_AsVoidPtr(getbuffer_cobj);
      #endif
        Py_DECREF(getbuffer_cobj);
        if (!func)
            goto fail;
        return func(obj, view, flags);
    } else {
        PyErr_Clear();
    }
  #endif
    PyErr_Format(PyExc_TypeError, "'%100s' does not have the buffer interface", Py_TYPE(obj)->tp_name);
#if PY_VERSION_HEX < 0x02060000
fail:
#endif
    return -1;
}
static void __Pyx_ReleaseBuffer(Py_buffer *view) {
    PyObject *obj = view->obj;
    CYTHON_UNUSED PyObject *releasebuffer_cobj;
    if (!obj) return;
  #if PY_VERSION_HEX >= 0x02060000
    if (PyObject_CheckBuffer(obj)) {
        PyBuffer_Release(view);
        return;
    }
  #endif
        if (PyObject_TypeCheck(obj, __pyx_ptype_5numpy_ndarray)) { __pyx_pw_5numpy_7ndarray_3__releasebuffer__(obj, view); return; }
  #if PY_VERSION_HEX < 0x02060000
    if (obj->ob_type->tp_dict &&
        (releasebuffer_cobj = PyMapping_GetItemString(obj->ob_type->tp_dict,
                                                      "__pyx_releasebuffer"))) {
        releasebufferproc func;
      #if PY_VERSION_HEX >= 0x02070000 && !(PY_MAJOR_VERSION == 3 && PY_MINOR_VERSION == 0)
        func = (releasebufferproc) PyCapsule_GetPointer(releasebuffer_cobj, "releasebuffer(obj, view)");
      #else
        func = (releasebufferproc) PyCObject_AsVoidPtr(releasebuffer_cobj);
      #endif
        Py_DECREF(releasebuffer_cobj);
        if (!func)
            goto fail;
        func(obj, view);
        return;
    } else {
        PyErr_Clear();
    }
  #endif
    goto nofail;
#if PY_VERSION_HEX < 0x02060000
fail:
#endif
    PyErr_WriteUnraisable(obj);
nofail:
    Py_DECREF(obj);
    view->obj = NULL;
}
#endif 


    static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, long level) {
    PyObject *py_import = 0;
    PyObject *empty_list = 0;
    PyObject *module = 0;
    PyObject *global_dict = 0;
    PyObject *empty_dict = 0;
    PyObject *list;
    py_import = __Pyx_GetAttrString(__pyx_b, "__import__");
    if (!py_import)
        goto bad;
    if (from_list)
        list = from_list;
    else {
        empty_list = PyList_New(0);
        if (!empty_list)
            goto bad;
        list = empty_list;
    }
    global_dict = PyModule_GetDict(__pyx_m);
    if (!global_dict)
        goto bad;
    empty_dict = PyDict_New();
    if (!empty_dict)
        goto bad;
    #if PY_VERSION_HEX >= 0x02050000
    {
        #if PY_MAJOR_VERSION >= 3
        if (level == -1) {
            if (strchr(__Pyx_MODULE_NAME, '.')) {
                
                PyObject *py_level = PyInt_FromLong(1);
                if (!py_level)
                    goto bad;
                module = PyObject_CallFunctionObjArgs(py_import,
                    name, global_dict, empty_dict, list, py_level, NULL);
                Py_DECREF(py_level);
                if (!module) {
                    if (!PyErr_ExceptionMatches(PyExc_ImportError))
                        goto bad;
                    PyErr_Clear();
                }
            }
            level = 0; 
        }
        #endif
        if (!module) {
            PyObject *py_level = PyInt_FromLong(level);
            if (!py_level)
                goto bad;
            module = PyObject_CallFunctionObjArgs(py_import,
                name, global_dict, empty_dict, list, py_level, NULL);
            Py_DECREF(py_level);
        }
    }
    #else
    if (level>0) {
        PyErr_SetString(PyExc_RuntimeError, "Relative import is not supported for Python <=2.4.");
        goto bad;
    }
    module = PyObject_CallFunctionObjArgs(py_import,
        name, global_dict, empty_dict, list, NULL);
    #endif
bad:
    Py_XDECREF(empty_list);
    Py_XDECREF(py_import);
    Py_XDECREF(empty_dict);
    return module;
}

static PyObject *__Pyx_FindPy2Metaclass(PyObject *bases) {
    PyObject *metaclass;
#if PY_MAJOR_VERSION < 3
    if (PyTuple_Check(bases) && PyTuple_GET_SIZE(bases) > 0) {
        PyObject *base = PyTuple_GET_ITEM(bases, 0);
        metaclass = PyObject_GetAttrString(base, (char *)"__class__");
        if (!metaclass) {
            PyErr_Clear();
            metaclass = (PyObject*) Py_TYPE(base);
        }
    } else {
        metaclass = (PyObject *) &PyClass_Type;
    }
#else
    if (PyTuple_Check(bases) && PyTuple_GET_SIZE(bases) > 0) {
        PyObject *base = PyTuple_GET_ITEM(bases, 0);
        metaclass = (PyObject*) Py_TYPE(base);
    } else {
        metaclass = (PyObject *) &PyType_Type;
    }
#endif
    Py_INCREF(metaclass);
    return metaclass;
}

static PyObject *__Pyx_CreateClass(PyObject *bases, PyObject *dict, PyObject *name,
                                   PyObject *modname) {
    PyObject *result;
    PyObject *metaclass;
    if (PyDict_SetItemString(dict, "__module__", modname) < 0)
        return NULL;
    metaclass = PyDict_GetItemString(dict, "__metaclass__");
    if (metaclass) {
        Py_INCREF(metaclass);
    } else {
        metaclass = __Pyx_FindPy2Metaclass(bases);
    }
    result = PyObject_CallFunctionObjArgs(metaclass, name, bases, dict, NULL);
    Py_DECREF(metaclass);
    return result;
}

static PyObject *
__Pyx_CyFunction_get_doc(__pyx_CyFunctionObject *op, CYTHON_UNUSED void *closure)
{
    if (op->func_doc == NULL && op->func.m_ml->ml_doc) {
#if PY_MAJOR_VERSION >= 3
        op->func_doc = PyUnicode_FromString(op->func.m_ml->ml_doc);
#else
        op->func_doc = PyString_FromString(op->func.m_ml->ml_doc);
#endif
    }
    if (op->func_doc == 0) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    Py_INCREF(op->func_doc);
    return op->func_doc;
}
static int
__Pyx_CyFunction_set_doc(__pyx_CyFunctionObject *op, PyObject *value)
{
    PyObject *tmp = op->func_doc;
    if (value == NULL)
        op->func_doc = Py_None; 
    else
        op->func_doc = value;
    Py_INCREF(op->func_doc);
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_name(__pyx_CyFunctionObject *op)
{
    if (op->func_name == NULL) {
#if PY_MAJOR_VERSION >= 3
        op->func_name = PyUnicode_InternFromString(op->func.m_ml->ml_name);
#else
        op->func_name = PyString_InternFromString(op->func.m_ml->ml_name);
#endif
    }
    Py_INCREF(op->func_name);
    return op->func_name;
}
static int
__Pyx_CyFunction_set_name(__pyx_CyFunctionObject *op, PyObject *value)
{
    PyObject *tmp;
#if PY_MAJOR_VERSION >= 3
    if (value == NULL || !PyUnicode_Check(value)) {
#else
    if (value == NULL || !PyString_Check(value)) {
#endif
        PyErr_SetString(PyExc_TypeError,
                        "__name__ must be set to a string object");
        return -1;
    }
    tmp = op->func_name;
    Py_INCREF(value);
    op->func_name = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_self(__pyx_CyFunctionObject *m, CYTHON_UNUSED void *closure)
{
    PyObject *self;
    self = m->func_closure;
    if (self == NULL)
        self = Py_None;
    Py_INCREF(self);
    return self;
}
static PyObject *
__Pyx_CyFunction_get_dict(__pyx_CyFunctionObject *op)
{
    if (op->func_dict == NULL) {
        op->func_dict = PyDict_New();
        if (op->func_dict == NULL)
            return NULL;
    }
    Py_INCREF(op->func_dict);
    return op->func_dict;
}
static int
__Pyx_CyFunction_set_dict(__pyx_CyFunctionObject *op, PyObject *value)
{
    PyObject *tmp;
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError,
               "function's dictionary may not be deleted");
        return -1;
    }
    if (!PyDict_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
               "setting function's dictionary to a non-dict");
        return -1;
    }
    tmp = op->func_dict;
    Py_INCREF(value);
    op->func_dict = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_globals(CYTHON_UNUSED __pyx_CyFunctionObject *op)
{
    PyObject* dict = PyModule_GetDict(__pyx_m);
    Py_XINCREF(dict);
    return dict;
}
static PyObject *
__Pyx_CyFunction_get_closure(CYTHON_UNUSED __pyx_CyFunctionObject *op)
{
    Py_INCREF(Py_None);
    return Py_None;
}
static PyObject *
__Pyx_CyFunction_get_code(__pyx_CyFunctionObject *op)
{
    PyObject* result = (op->func_code) ? op->func_code : Py_None;
    Py_INCREF(result);
    return result;
}
static PyObject *
__Pyx_CyFunction_get_defaults(__pyx_CyFunctionObject *op)
{
    if (op->defaults_tuple) {
        Py_INCREF(op->defaults_tuple);
        return op->defaults_tuple;
    }
    if (op->defaults_getter) {
        PyObject *res = op->defaults_getter((PyObject *) op);
        if (res) {
            Py_INCREF(res);
            op->defaults_tuple = res;
        }
        return res;
    }
    Py_INCREF(Py_None);
    return Py_None;
}
static PyGetSetDef __pyx_CyFunction_getsets[] = {
    {(char *) "func_doc", (getter)__Pyx_CyFunction_get_doc, (setter)__Pyx_CyFunction_set_doc, 0, 0},
    {(char *) "__doc__",  (getter)__Pyx_CyFunction_get_doc, (setter)__Pyx_CyFunction_set_doc, 0, 0},
    {(char *) "func_name", (getter)__Pyx_CyFunction_get_name, (setter)__Pyx_CyFunction_set_name, 0, 0},
    {(char *) "__name__", (getter)__Pyx_CyFunction_get_name, (setter)__Pyx_CyFunction_set_name, 0, 0},
    {(char *) "__self__", (getter)__Pyx_CyFunction_get_self, 0, 0, 0},
    {(char *) "func_dict", (getter)__Pyx_CyFunction_get_dict, (setter)__Pyx_CyFunction_set_dict, 0, 0},
    {(char *) "__dict__", (getter)__Pyx_CyFunction_get_dict, (setter)__Pyx_CyFunction_set_dict, 0, 0},
    {(char *) "func_globals", (getter)__Pyx_CyFunction_get_globals, 0, 0, 0},
    {(char *) "__globals__", (getter)__Pyx_CyFunction_get_globals, 0, 0, 0},
    {(char *) "func_closure", (getter)__Pyx_CyFunction_get_closure, 0, 0, 0},
    {(char *) "__closure__", (getter)__Pyx_CyFunction_get_closure, 0, 0, 0},
    {(char *) "func_code", (getter)__Pyx_CyFunction_get_code, 0, 0, 0},
    {(char *) "__code__", (getter)__Pyx_CyFunction_get_code, 0, 0, 0},
    {(char *) "func_defaults", (getter)__Pyx_CyFunction_get_defaults, 0, 0, 0},
    {(char *) "__defaults__", (getter)__Pyx_CyFunction_get_defaults, 0, 0, 0},
    {0, 0, 0, 0, 0}
};
#ifndef PY_WRITE_RESTRICTED 
#define PY_WRITE_RESTRICTED WRITE_RESTRICTED
#endif
static PyMemberDef __pyx_CyFunction_members[] = {
    {(char *) "__module__", T_OBJECT, offsetof(__pyx_CyFunctionObject, func.m_module), PY_WRITE_RESTRICTED, 0},
    {0, 0, 0,  0, 0}
};
static PyObject *
__Pyx_CyFunction_reduce(__pyx_CyFunctionObject *m, CYTHON_UNUSED PyObject *args)
{
#if PY_MAJOR_VERSION >= 3
    return PyUnicode_FromString(m->func.m_ml->ml_name);
#else
    return PyString_FromString(m->func.m_ml->ml_name);
#endif
}
static PyMethodDef __pyx_CyFunction_methods[] = {
    {__Pyx_NAMESTR("__reduce__"), (PyCFunction)__Pyx_CyFunction_reduce, METH_VARARGS, 0},
    {0, 0, 0, 0}
};
static PyObject *__Pyx_CyFunction_New(PyTypeObject *type, PyMethodDef *ml, int flags,
                                      PyObject *closure, PyObject *module, PyObject* code) {
    __pyx_CyFunctionObject *op = PyObject_GC_New(__pyx_CyFunctionObject, type);
    if (op == NULL)
        return NULL;
    op->flags = flags;
    op->func_weakreflist = NULL;
    op->func.m_ml = ml;
    op->func.m_self = (PyObject *) op;
    Py_XINCREF(closure);
    op->func_closure = closure;
    Py_XINCREF(module);
    op->func.m_module = module;
    op->func_dict = NULL;
    op->func_name = NULL;
    op->func_doc = NULL;
    op->func_classobj = NULL;
    Py_XINCREF(code);
    op->func_code = code;
    op->defaults_pyobjects = 0;
    op->defaults = NULL;
    op->defaults_tuple = NULL;
    op->defaults_getter = NULL;
    PyObject_GC_Track(op);
    return (PyObject *) op;
}
static int
__Pyx_CyFunction_clear(__pyx_CyFunctionObject *m)
{
    Py_CLEAR(m->func_closure);
    Py_CLEAR(m->func.m_module);
    Py_CLEAR(m->func_dict);
    Py_CLEAR(m->func_name);
    Py_CLEAR(m->func_doc);
    Py_CLEAR(m->func_code);
    Py_CLEAR(m->func_classobj);
    Py_CLEAR(m->defaults_tuple);
    if (m->defaults) {
        PyObject **pydefaults = __Pyx_CyFunction_Defaults(PyObject *, m);
        int i;
        for (i = 0; i < m->defaults_pyobjects; i++)
            Py_XDECREF(pydefaults[i]);
        PyMem_Free(m->defaults);
        m->defaults = NULL;
    }
    return 0;
}
static void __Pyx_CyFunction_dealloc(__pyx_CyFunctionObject *m)
{
    PyObject_GC_UnTrack(m);
    if (m->func_weakreflist != NULL)
        PyObject_ClearWeakRefs((PyObject *) m);
    __Pyx_CyFunction_clear(m);
    PyObject_GC_Del(m);
}
static int __Pyx_CyFunction_traverse(__pyx_CyFunctionObject *m, visitproc visit, void *arg)
{
    Py_VISIT(m->func_closure);
    Py_VISIT(m->func.m_module);
    Py_VISIT(m->func_dict);
    Py_VISIT(m->func_name);
    Py_VISIT(m->func_doc);
    Py_VISIT(m->func_code);
    Py_VISIT(m->func_classobj);
    Py_VISIT(m->defaults_tuple);
    if (m->defaults) {
        PyObject **pydefaults = __Pyx_CyFunction_Defaults(PyObject *, m);
        int i;
        for (i = 0; i < m->defaults_pyobjects; i++)
            Py_VISIT(pydefaults[i]);
    }
    return 0;
}
static PyObject *__Pyx_CyFunction_descr_get(PyObject *func, PyObject *obj, PyObject *type)
{
    __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *) func;
    if (m->flags & __Pyx_CYFUNCTION_STATICMETHOD) {
        Py_INCREF(func);
        return func;
    }
    if (m->flags & __Pyx_CYFUNCTION_CLASSMETHOD) {
        if (type == NULL)
            type = (PyObject *)(Py_TYPE(obj));
        return PyMethod_New(func,
                            type, (PyObject *)(Py_TYPE(type)));
    }
    if (obj == Py_None)
        obj = NULL;
    return PyMethod_New(func, obj, type);
}
static PyObject*
__Pyx_CyFunction_repr(__pyx_CyFunctionObject *op)
{
    PyObject *func_name = __Pyx_CyFunction_get_name(op);
#if PY_MAJOR_VERSION >= 3
    return PyUnicode_FromFormat("<cyfunction %U at %p>",
                                func_name, (void *)op);
#else
    return PyString_FromFormat("<cyfunction %s at %p>",
                               PyString_AsString(func_name), (void *)op);
#endif
}
#if CYTHON_COMPILING_IN_PYPY
static PyObject * __Pyx_CyFunction_Call(PyObject *func, PyObject *arg, PyObject *kw) {
    PyCFunctionObject* f = (PyCFunctionObject*)func;
    PyCFunction meth = PyCFunction_GET_FUNCTION(func);
    PyObject *self = PyCFunction_GET_SELF(func);
    Py_ssize_t size;
    switch (PyCFunction_GET_FLAGS(func) & ~(METH_CLASS | METH_STATIC | METH_COEXIST)) {
    case METH_VARARGS:
        if (likely(kw == NULL) || PyDict_Size(kw) == 0)
            return (*meth)(self, arg);
        break;
    case METH_VARARGS | METH_KEYWORDS:
        return (*(PyCFunctionWithKeywords)meth)(self, arg, kw);
    case METH_NOARGS:
        if (likely(kw == NULL) || PyDict_Size(kw) == 0) {
            size = PyTuple_GET_SIZE(arg);
            if (size == 0)
                return (*meth)(self, NULL);
            PyErr_Format(PyExc_TypeError,
                "%.200s() takes no arguments (%zd given)",
                f->m_ml->ml_name, size);
            return NULL;
        }
        break;
    case METH_O:
        if (likely(kw == NULL) || PyDict_Size(kw) == 0) {
            size = PyTuple_GET_SIZE(arg);
            if (size == 1)
                return (*meth)(self, PyTuple_GET_ITEM(arg, 0));
            PyErr_Format(PyExc_TypeError,
                "%.200s() takes exactly one argument (%zd given)",
                f->m_ml->ml_name, size);
            return NULL;
        }
        break;
    default:
        PyErr_SetString(PyExc_SystemError, "Bad call flags in "
                        "__Pyx_CyFunction_Call. METH_OLDARGS is no "
                        "longer supported!");
        return NULL;
    }
    PyErr_Format(PyExc_TypeError, "%.200s() takes no keyword arguments",
                 f->m_ml->ml_name);
    return NULL;
}
#else
static PyObject * __Pyx_CyFunction_Call(PyObject *func, PyObject *arg, PyObject *kw) {
	return PyCFunction_Call(func, arg, kw);
}
#endif
static PyTypeObject __pyx_CyFunctionType_type = {
    PyVarObject_HEAD_INIT(0, 0)
    __Pyx_NAMESTR("cython_function_or_method"), 
    sizeof(__pyx_CyFunctionObject),   
    0,                                  
    (destructor) __Pyx_CyFunction_dealloc, 
    0,                                  
    0,                                  
    0,                                  
#if PY_MAJOR_VERSION < 3
    0,                                  
#else
    0,                                  
#endif
    (reprfunc) __Pyx_CyFunction_repr,   
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    __Pyx_CyFunction_Call,              
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC, 
    0,                                  
    (traverseproc) __Pyx_CyFunction_traverse,   
    (inquiry) __Pyx_CyFunction_clear,   
    0,                                  
    offsetof(__pyx_CyFunctionObject, func_weakreflist), 
    0,                                  
    0,                                  
    __pyx_CyFunction_methods,           
    __pyx_CyFunction_members,           
    __pyx_CyFunction_getsets,           
    0,                                  
    0,                                  
    __Pyx_CyFunction_descr_get,         
    0,                                  
    offsetof(__pyx_CyFunctionObject, func_dict),
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
#if PY_VERSION_HEX >= 0x02060000
    0,                                  
#endif
};
static int __Pyx_CyFunction_init(void) {
#if !CYTHON_COMPILING_IN_PYPY
    __pyx_CyFunctionType_type.tp_call = PyCFunction_Call;
#endif
    if (PyType_Ready(&__pyx_CyFunctionType_type) < 0)
        return -1;
    __pyx_CyFunctionType = &__pyx_CyFunctionType_type;
    return 0;
}
static CYTHON_INLINE void *__Pyx_CyFunction_InitDefaults(PyObject *func, size_t size, int pyobjects) {
    __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *) func;
    m->defaults = PyMem_Malloc(size);
    if (!m->defaults)
        return PyErr_NoMemory();
    memset(m->defaults, 0, sizeof(size));
    m->defaults_pyobjects = pyobjects;
    return m->defaults;
}
static CYTHON_INLINE void __Pyx_CyFunction_SetDefaultsTuple(PyObject *func, PyObject *tuple) {
    __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *) func;
    m->defaults_tuple = tuple;
    Py_INCREF(tuple);
}

static CYTHON_INLINE PyObject *__Pyx_PyInt_to_py_flagT(flagT val) {
    const flagT neg_one = (flagT)-1, const_zero = (flagT)0;
    const int is_unsigned = const_zero < neg_one;
    if ((sizeof(flagT) == sizeof(char))  ||
        (sizeof(flagT) == sizeof(short))) {
        return PyInt_FromLong((long)val);
    } else if ((sizeof(flagT) == sizeof(int)) ||
               (sizeof(flagT) == sizeof(long))) {
        if (is_unsigned)
            return PyLong_FromUnsignedLong((unsigned long)val);
        else
            return PyInt_FromLong((long)val);
    } else if (sizeof(flagT) == sizeof(PY_LONG_LONG)) {
        if (is_unsigned)
            return PyLong_FromUnsignedLongLong((unsigned PY_LONG_LONG)val);
        else
            return PyLong_FromLongLong((PY_LONG_LONG)val);
    } else {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&val;
        return _PyLong_FromByteArray(bytes, sizeof(flagT),
                                     little, !is_unsigned);
    }
}

static CYTHON_INLINE PyObject *__Pyx_PyInt_to_py_Py_intptr_t(Py_intptr_t val) {
    const Py_intptr_t neg_one = (Py_intptr_t)-1, const_zero = (Py_intptr_t)0;
    const int is_unsigned = const_zero < neg_one;
    if ((sizeof(Py_intptr_t) == sizeof(char))  ||
        (sizeof(Py_intptr_t) == sizeof(short))) {
        return PyInt_FromLong((long)val);
    } else if ((sizeof(Py_intptr_t) == sizeof(int)) ||
               (sizeof(Py_intptr_t) == sizeof(long))) {
        if (is_unsigned)
            return PyLong_FromUnsignedLong((unsigned long)val);
        else
            return PyInt_FromLong((long)val);
    } else if (sizeof(Py_intptr_t) == sizeof(PY_LONG_LONG)) {
        if (is_unsigned)
            return PyLong_FromUnsignedLongLong((unsigned PY_LONG_LONG)val);
        else
            return PyLong_FromLongLong((PY_LONG_LONG)val);
    } else {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&val;
        return _PyLong_FromByteArray(bytes, sizeof(Py_intptr_t),
                                     little, !is_unsigned);
    }
}

#if CYTHON_CCOMPLEX
  #ifdef __cplusplus
    static CYTHON_INLINE __pyx_t_float_complex __pyx_t_float_complex_from_parts(float x, float y) {
      return ::std::complex< float >(x, y);
    }
  #else
    static CYTHON_INLINE __pyx_t_float_complex __pyx_t_float_complex_from_parts(float x, float y) {
      return x + y*(__pyx_t_float_complex)_Complex_I;
    }
  #endif
#else
    static CYTHON_INLINE __pyx_t_float_complex __pyx_t_float_complex_from_parts(float x, float y) {
      __pyx_t_float_complex z;
      z.real = x;
      z.imag = y;
      return z;
    }
#endif

#if CYTHON_CCOMPLEX
#else
    static CYTHON_INLINE int __Pyx_c_eqf(__pyx_t_float_complex a, __pyx_t_float_complex b) {
       return (a.real == b.real) && (a.imag == b.imag);
    }
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_sumf(__pyx_t_float_complex a, __pyx_t_float_complex b) {
        __pyx_t_float_complex z;
        z.real = a.real + b.real;
        z.imag = a.imag + b.imag;
        return z;
    }
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_difff(__pyx_t_float_complex a, __pyx_t_float_complex b) {
        __pyx_t_float_complex z;
        z.real = a.real - b.real;
        z.imag = a.imag - b.imag;
        return z;
    }
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_prodf(__pyx_t_float_complex a, __pyx_t_float_complex b) {
        __pyx_t_float_complex z;
        z.real = a.real * b.real - a.imag * b.imag;
        z.imag = a.real * b.imag + a.imag * b.real;
        return z;
    }
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_quotf(__pyx_t_float_complex a, __pyx_t_float_complex b) {
        __pyx_t_float_complex z;
        float denom = b.real * b.real + b.imag * b.imag;
        z.real = (a.real * b.real + a.imag * b.imag) / denom;
        z.imag = (a.imag * b.real - a.real * b.imag) / denom;
        return z;
    }
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_negf(__pyx_t_float_complex a) {
        __pyx_t_float_complex z;
        z.real = -a.real;
        z.imag = -a.imag;
        return z;
    }
    static CYTHON_INLINE int __Pyx_c_is_zerof(__pyx_t_float_complex a) {
       return (a.real == 0) && (a.imag == 0);
    }
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_conjf(__pyx_t_float_complex a) {
        __pyx_t_float_complex z;
        z.real =  a.real;
        z.imag = -a.imag;
        return z;
    }
    #if 1
        static CYTHON_INLINE float __Pyx_c_absf(__pyx_t_float_complex z) {
          #if !defined(HAVE_HYPOT) || defined(_MSC_VER)
            return sqrtf(z.real*z.real + z.imag*z.imag);
          #else
            return hypotf(z.real, z.imag);
          #endif
        }
        static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_powf(__pyx_t_float_complex a, __pyx_t_float_complex b) {
            __pyx_t_float_complex z;
            float r, lnr, theta, z_r, z_theta;
            if (b.imag == 0 && b.real == (int)b.real) {
                if (b.real < 0) {
                    float denom = a.real * a.real + a.imag * a.imag;
                    a.real = a.real / denom;
                    a.imag = -a.imag / denom;
                    b.real = -b.real;
                }
                switch ((int)b.real) {
                    case 0:
                        z.real = 1;
                        z.imag = 0;
                        return z;
                    case 1:
                        return a;
                    case 2:
                        z = __Pyx_c_prodf(a, a);
                        return __Pyx_c_prodf(a, a);
                    case 3:
                        z = __Pyx_c_prodf(a, a);
                        return __Pyx_c_prodf(z, a);
                    case 4:
                        z = __Pyx_c_prodf(a, a);
                        return __Pyx_c_prodf(z, z);
                }
            }
            if (a.imag == 0) {
                if (a.real == 0) {
                    return a;
                }
                r = a.real;
                theta = 0;
            } else {
                r = __Pyx_c_absf(a);
                theta = atan2f(a.imag, a.real);
            }
            lnr = logf(r);
            z_r = expf(lnr * b.real - theta * b.imag);
            z_theta = theta * b.real + lnr * b.imag;
            z.real = z_r * cosf(z_theta);
            z.imag = z_r * sinf(z_theta);
            return z;
        }
    #endif
#endif

#if CYTHON_CCOMPLEX
  #ifdef __cplusplus
    static CYTHON_INLINE __pyx_t_double_complex __pyx_t_double_complex_from_parts(double x, double y) {
      return ::std::complex< double >(x, y);
    }
  #else
    static CYTHON_INLINE __pyx_t_double_complex __pyx_t_double_complex_from_parts(double x, double y) {
      return x + y*(__pyx_t_double_complex)_Complex_I;
    }
  #endif
#else
    static CYTHON_INLINE __pyx_t_double_complex __pyx_t_double_complex_from_parts(double x, double y) {
      __pyx_t_double_complex z;
      z.real = x;
      z.imag = y;
      return z;
    }
#endif

#if CYTHON_CCOMPLEX
#else
    static CYTHON_INLINE int __Pyx_c_eq(__pyx_t_double_complex a, __pyx_t_double_complex b) {
       return (a.real == b.real) && (a.imag == b.imag);
    }
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_sum(__pyx_t_double_complex a, __pyx_t_double_complex b) {
        __pyx_t_double_complex z;
        z.real = a.real + b.real;
        z.imag = a.imag + b.imag;
        return z;
    }
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_diff(__pyx_t_double_complex a, __pyx_t_double_complex b) {
        __pyx_t_double_complex z;
        z.real = a.real - b.real;
        z.imag = a.imag - b.imag;
        return z;
    }
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_prod(__pyx_t_double_complex a, __pyx_t_double_complex b) {
        __pyx_t_double_complex z;
        z.real = a.real * b.real - a.imag * b.imag;
        z.imag = a.real * b.imag + a.imag * b.real;
        return z;
    }
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_quot(__pyx_t_double_complex a, __pyx_t_double_complex b) {
        __pyx_t_double_complex z;
        double denom = b.real * b.real + b.imag * b.imag;
        z.real = (a.real * b.real + a.imag * b.imag) / denom;
        z.imag = (a.imag * b.real - a.real * b.imag) / denom;
        return z;
    }
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_neg(__pyx_t_double_complex a) {
        __pyx_t_double_complex z;
        z.real = -a.real;
        z.imag = -a.imag;
        return z;
    }
    static CYTHON_INLINE int __Pyx_c_is_zero(__pyx_t_double_complex a) {
       return (a.real == 0) && (a.imag == 0);
    }
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_conj(__pyx_t_double_complex a) {
        __pyx_t_double_complex z;
        z.real =  a.real;
        z.imag = -a.imag;
        return z;
    }
    #if 1
        static CYTHON_INLINE double __Pyx_c_abs(__pyx_t_double_complex z) {
          #if !defined(HAVE_HYPOT) || defined(_MSC_VER)
            return sqrt(z.real*z.real + z.imag*z.imag);
          #else
            return hypot(z.real, z.imag);
          #endif
        }
        static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_pow(__pyx_t_double_complex a, __pyx_t_double_complex b) {
            __pyx_t_double_complex z;
            double r, lnr, theta, z_r, z_theta;
            if (b.imag == 0 && b.real == (int)b.real) {
                if (b.real < 0) {
                    double denom = a.real * a.real + a.imag * a.imag;
                    a.real = a.real / denom;
                    a.imag = -a.imag / denom;
                    b.real = -b.real;
                }
                switch ((int)b.real) {
                    case 0:
                        z.real = 1;
                        z.imag = 0;
                        return z;
                    case 1:
                        return a;
                    case 2:
                        z = __Pyx_c_prod(a, a);
                        return __Pyx_c_prod(a, a);
                    case 3:
                        z = __Pyx_c_prod(a, a);
                        return __Pyx_c_prod(z, a);
                    case 4:
                        z = __Pyx_c_prod(a, a);
                        return __Pyx_c_prod(z, z);
                }
            }
            if (a.imag == 0) {
                if (a.real == 0) {
                    return a;
                }
                r = a.real;
                theta = 0;
            } else {
                r = __Pyx_c_abs(a);
                theta = atan2(a.imag, a.real);
            }
            lnr = log(r);
            z_r = exp(lnr * b.real - theta * b.imag);
            z_theta = theta * b.real + lnr * b.imag;
            z.real = z_r * cos(z_theta);
            z.imag = z_r * sin(z_theta);
            return z;
        }
    #endif
#endif

static CYTHON_INLINE unsigned char __Pyx_PyInt_AsUnsignedChar(PyObject* x) {
    const unsigned char neg_one = (unsigned char)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(unsigned char) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(unsigned char)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to unsigned char" :
                    "value too large to convert to unsigned char");
            }
            return (unsigned char)-1;
        }
        return (unsigned char)val;
    }
    return (unsigned char)__Pyx_PyInt_AsUnsignedLong(x);
}

static CYTHON_INLINE unsigned short __Pyx_PyInt_AsUnsignedShort(PyObject* x) {
    const unsigned short neg_one = (unsigned short)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(unsigned short) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(unsigned short)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to unsigned short" :
                    "value too large to convert to unsigned short");
            }
            return (unsigned short)-1;
        }
        return (unsigned short)val;
    }
    return (unsigned short)__Pyx_PyInt_AsUnsignedLong(x);
}

static CYTHON_INLINE unsigned int __Pyx_PyInt_AsUnsignedInt(PyObject* x) {
    const unsigned int neg_one = (unsigned int)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(unsigned int) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(unsigned int)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to unsigned int" :
                    "value too large to convert to unsigned int");
            }
            return (unsigned int)-1;
        }
        return (unsigned int)val;
    }
    return (unsigned int)__Pyx_PyInt_AsUnsignedLong(x);
}

static CYTHON_INLINE char __Pyx_PyInt_AsChar(PyObject* x) {
    const char neg_one = (char)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(char) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(char)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to char" :
                    "value too large to convert to char");
            }
            return (char)-1;
        }
        return (char)val;
    }
    return (char)__Pyx_PyInt_AsLong(x);
}

static CYTHON_INLINE short __Pyx_PyInt_AsShort(PyObject* x) {
    const short neg_one = (short)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(short) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(short)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to short" :
                    "value too large to convert to short");
            }
            return (short)-1;
        }
        return (short)val;
    }
    return (short)__Pyx_PyInt_AsLong(x);
}

static CYTHON_INLINE int __Pyx_PyInt_AsInt(PyObject* x) {
    const int neg_one = (int)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(int) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(int)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to int" :
                    "value too large to convert to int");
            }
            return (int)-1;
        }
        return (int)val;
    }
    return (int)__Pyx_PyInt_AsLong(x);
}

static CYTHON_INLINE signed char __Pyx_PyInt_AsSignedChar(PyObject* x) {
    const signed char neg_one = (signed char)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(signed char) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(signed char)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to signed char" :
                    "value too large to convert to signed char");
            }
            return (signed char)-1;
        }
        return (signed char)val;
    }
    return (signed char)__Pyx_PyInt_AsSignedLong(x);
}

static CYTHON_INLINE signed short __Pyx_PyInt_AsSignedShort(PyObject* x) {
    const signed short neg_one = (signed short)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(signed short) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(signed short)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to signed short" :
                    "value too large to convert to signed short");
            }
            return (signed short)-1;
        }
        return (signed short)val;
    }
    return (signed short)__Pyx_PyInt_AsSignedLong(x);
}

static CYTHON_INLINE signed int __Pyx_PyInt_AsSignedInt(PyObject* x) {
    const signed int neg_one = (signed int)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(signed int) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(signed int)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to signed int" :
                    "value too large to convert to signed int");
            }
            return (signed int)-1;
        }
        return (signed int)val;
    }
    return (signed int)__Pyx_PyInt_AsSignedLong(x);
}

static CYTHON_INLINE int __Pyx_PyInt_AsLongDouble(PyObject* x) {
    const int neg_one = (int)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(int) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(int)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to int" :
                    "value too large to convert to int");
            }
            return (int)-1;
        }
        return (int)val;
    }
    return (int)__Pyx_PyInt_AsLong(x);
}

static CYTHON_INLINE unsigned long __Pyx_PyInt_AsUnsignedLong(PyObject* x) {
    const unsigned long neg_one = (unsigned long)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_VERSION_HEX < 0x03000000
    if (likely(PyInt_Check(x))) {
        long val = PyInt_AS_LONG(x);
        if (is_unsigned && unlikely(val < 0)) {
            PyErr_SetString(PyExc_OverflowError,
                            "can't convert negative value to unsigned long");
            return (unsigned long)-1;
        }
        return (unsigned long)val;
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
            if (unlikely(Py_SIZE(x) < 0)) {
                PyErr_SetString(PyExc_OverflowError,
                                "can't convert negative value to unsigned long");
                return (unsigned long)-1;
            }
            return (unsigned long)PyLong_AsUnsignedLong(x);
        } else {
            return (unsigned long)PyLong_AsLong(x);
        }
    } else {
        unsigned long val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (unsigned long)-1;
        val = __Pyx_PyInt_AsUnsignedLong(tmp);
        Py_DECREF(tmp);
        return val;
    }
}

static CYTHON_INLINE unsigned PY_LONG_LONG __Pyx_PyInt_AsUnsignedLongLong(PyObject* x) {
    const unsigned PY_LONG_LONG neg_one = (unsigned PY_LONG_LONG)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_VERSION_HEX < 0x03000000
    if (likely(PyInt_Check(x))) {
        long val = PyInt_AS_LONG(x);
        if (is_unsigned && unlikely(val < 0)) {
            PyErr_SetString(PyExc_OverflowError,
                            "can't convert negative value to unsigned PY_LONG_LONG");
            return (unsigned PY_LONG_LONG)-1;
        }
        return (unsigned PY_LONG_LONG)val;
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
            if (unlikely(Py_SIZE(x) < 0)) {
                PyErr_SetString(PyExc_OverflowError,
                                "can't convert negative value to unsigned PY_LONG_LONG");
                return (unsigned PY_LONG_LONG)-1;
            }
            return (unsigned PY_LONG_LONG)PyLong_AsUnsignedLongLong(x);
        } else {
            return (unsigned PY_LONG_LONG)PyLong_AsLongLong(x);
        }
    } else {
        unsigned PY_LONG_LONG val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (unsigned PY_LONG_LONG)-1;
        val = __Pyx_PyInt_AsUnsignedLongLong(tmp);
        Py_DECREF(tmp);
        return val;
    }
}

static CYTHON_INLINE long __Pyx_PyInt_AsLong(PyObject* x) {
    const long neg_one = (long)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_VERSION_HEX < 0x03000000
    if (likely(PyInt_Check(x))) {
        long val = PyInt_AS_LONG(x);
        if (is_unsigned && unlikely(val < 0)) {
            PyErr_SetString(PyExc_OverflowError,
                            "can't convert negative value to long");
            return (long)-1;
        }
        return (long)val;
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
            if (unlikely(Py_SIZE(x) < 0)) {
                PyErr_SetString(PyExc_OverflowError,
                                "can't convert negative value to long");
                return (long)-1;
            }
            return (long)PyLong_AsUnsignedLong(x);
        } else {
            return (long)PyLong_AsLong(x);
        }
    } else {
        long val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (long)-1;
        val = __Pyx_PyInt_AsLong(tmp);
        Py_DECREF(tmp);
        return val;
    }
}

static CYTHON_INLINE PY_LONG_LONG __Pyx_PyInt_AsLongLong(PyObject* x) {
    const PY_LONG_LONG neg_one = (PY_LONG_LONG)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_VERSION_HEX < 0x03000000
    if (likely(PyInt_Check(x))) {
        long val = PyInt_AS_LONG(x);
        if (is_unsigned && unlikely(val < 0)) {
            PyErr_SetString(PyExc_OverflowError,
                            "can't convert negative value to PY_LONG_LONG");
            return (PY_LONG_LONG)-1;
        }
        return (PY_LONG_LONG)val;
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
            if (unlikely(Py_SIZE(x) < 0)) {
                PyErr_SetString(PyExc_OverflowError,
                                "can't convert negative value to PY_LONG_LONG");
                return (PY_LONG_LONG)-1;
            }
            return (PY_LONG_LONG)PyLong_AsUnsignedLongLong(x);
        } else {
            return (PY_LONG_LONG)PyLong_AsLongLong(x);
        }
    } else {
        PY_LONG_LONG val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (PY_LONG_LONG)-1;
        val = __Pyx_PyInt_AsLongLong(tmp);
        Py_DECREF(tmp);
        return val;
    }
}

static CYTHON_INLINE signed long __Pyx_PyInt_AsSignedLong(PyObject* x) {
    const signed long neg_one = (signed long)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_VERSION_HEX < 0x03000000
    if (likely(PyInt_Check(x))) {
        long val = PyInt_AS_LONG(x);
        if (is_unsigned && unlikely(val < 0)) {
            PyErr_SetString(PyExc_OverflowError,
                            "can't convert negative value to signed long");
            return (signed long)-1;
        }
        return (signed long)val;
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
            if (unlikely(Py_SIZE(x) < 0)) {
                PyErr_SetString(PyExc_OverflowError,
                                "can't convert negative value to signed long");
                return (signed long)-1;
            }
            return (signed long)PyLong_AsUnsignedLong(x);
        } else {
            return (signed long)PyLong_AsLong(x);
        }
    } else {
        signed long val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (signed long)-1;
        val = __Pyx_PyInt_AsSignedLong(tmp);
        Py_DECREF(tmp);
        return val;
    }
}

static CYTHON_INLINE signed PY_LONG_LONG __Pyx_PyInt_AsSignedLongLong(PyObject* x) {
    const signed PY_LONG_LONG neg_one = (signed PY_LONG_LONG)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_VERSION_HEX < 0x03000000
    if (likely(PyInt_Check(x))) {
        long val = PyInt_AS_LONG(x);
        if (is_unsigned && unlikely(val < 0)) {
            PyErr_SetString(PyExc_OverflowError,
                            "can't convert negative value to signed PY_LONG_LONG");
            return (signed PY_LONG_LONG)-1;
        }
        return (signed PY_LONG_LONG)val;
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
            if (unlikely(Py_SIZE(x) < 0)) {
                PyErr_SetString(PyExc_OverflowError,
                                "can't convert negative value to signed PY_LONG_LONG");
                return (signed PY_LONG_LONG)-1;
            }
            return (signed PY_LONG_LONG)PyLong_AsUnsignedLongLong(x);
        } else {
            return (signed PY_LONG_LONG)PyLong_AsLongLong(x);
        }
    } else {
        signed PY_LONG_LONG val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (signed PY_LONG_LONG)-1;
        val = __Pyx_PyInt_AsSignedLongLong(tmp);
        Py_DECREF(tmp);
        return val;
    }
}

static int __Pyx_check_binary_version(void) {
    char ctversion[4], rtversion[4];
    PyOS_snprintf(ctversion, 4, "%d.%d", PY_MAJOR_VERSION, PY_MINOR_VERSION);
    PyOS_snprintf(rtversion, 4, "%s", Py_GetVersion());
    if (ctversion[0] != rtversion[0] || ctversion[2] != rtversion[2]) {
        char message[200];
        PyOS_snprintf(message, sizeof(message),
                      "compiletime version %s of module '%.100s' "
                      "does not match runtime version %s",
                      ctversion, __Pyx_MODULE_NAME, rtversion);
        #if PY_VERSION_HEX < 0x02050000
        return PyErr_Warn(NULL, message);
        #else
        return PyErr_WarnEx(NULL, message, 1);
        #endif
    }
    return 0;
}

static int __Pyx_ExportFunction(const char *name, void (*f)(void), const char *sig) {
    PyObject *d = 0;
    PyObject *cobj = 0;
    union {
        void (*fp)(void);
        void *p;
    } tmp;
    d = PyObject_GetAttrString(__pyx_m, (char *)"__pyx_capi__");
    if (!d) {
        PyErr_Clear();
        d = PyDict_New();
        if (!d)
            goto bad;
        Py_INCREF(d);
        if (PyModule_AddObject(__pyx_m, (char *)"__pyx_capi__", d) < 0)
            goto bad;
    }
    tmp.fp = f;
#if PY_VERSION_HEX >= 0x02070000 && !(PY_MAJOR_VERSION==3&&PY_MINOR_VERSION==0)
    cobj = PyCapsule_New(tmp.p, sig, 0);
#else
    cobj = PyCObject_FromVoidPtrAndDesc(tmp.p, (void *)sig, 0);
#endif
    if (!cobj)
        goto bad;
    if (PyDict_SetItemString(d, name, cobj) < 0)
        goto bad;
    Py_DECREF(cobj);
    Py_DECREF(d);
    return 0;
bad:
    Py_XDECREF(cobj);
    Py_XDECREF(d);
    return -1;
}

static int __Pyx_SetVtable(PyObject *dict, void *vtable) {
#if PY_VERSION_HEX >= 0x02070000 && !(PY_MAJOR_VERSION==3&&PY_MINOR_VERSION==0)
    PyObject *ob = PyCapsule_New(vtable, 0, 0);
#else
    PyObject *ob = PyCObject_FromVoidPtr(vtable, 0);
#endif
    if (!ob)
        goto bad;
    if (PyDict_SetItemString(dict, "__pyx_vtable__", ob) < 0)
        goto bad;
    Py_DECREF(ob);
    return 0;
bad:
    Py_XDECREF(ob);
    return -1;
}

#ifndef __PYX_HAVE_RT_ImportModule
#define __PYX_HAVE_RT_ImportModule
static PyObject *__Pyx_ImportModule(const char *name) {
    PyObject *py_name = 0;
    PyObject *py_module = 0;
    py_name = __Pyx_PyIdentifier_FromString(name);
    if (!py_name)
        goto bad;
    py_module = PyImport_Import(py_name);
    Py_DECREF(py_name);
    return py_module;
bad:
    Py_XDECREF(py_name);
    return 0;
}
#endif

#ifndef __PYX_HAVE_RT_ImportType
#define __PYX_HAVE_RT_ImportType
static PyTypeObject *__Pyx_ImportType(const char *module_name, const char *class_name,
    size_t size, int strict)
{
    PyObject *py_module = 0;
    PyObject *result = 0;
    PyObject *py_name = 0;
    char warning[200];
    py_module = __Pyx_ImportModule(module_name);
    if (!py_module)
        goto bad;
    py_name = __Pyx_PyIdentifier_FromString(class_name);
    if (!py_name)
        goto bad;
    result = PyObject_GetAttr(py_module, py_name);
    Py_DECREF(py_name);
    py_name = 0;
    Py_DECREF(py_module);
    py_module = 0;
    if (!result)
        goto bad;
    if (!PyType_Check(result)) {
        PyErr_Format(PyExc_TypeError,
            "%s.%s is not a type object",
            module_name, class_name);
        goto bad;
    }
    if (!strict && (size_t)((PyTypeObject *)result)->tp_basicsize > size) {
        PyOS_snprintf(warning, sizeof(warning),
            "%s.%s size changed, may indicate binary incompatibility",
            module_name, class_name);
        #if PY_VERSION_HEX < 0x02050000
        if (PyErr_Warn(NULL, warning) < 0) goto bad;
        #else
        if (PyErr_WarnEx(NULL, warning, 0) < 0) goto bad;
        #endif
    }
    else if ((size_t)((PyTypeObject *)result)->tp_basicsize != size) {
        PyErr_Format(PyExc_ValueError,
            "%s.%s has the wrong size, try recompiling",
            module_name, class_name);
        goto bad;
    }
    return (PyTypeObject *)result;
bad:
    Py_XDECREF(py_module);
    Py_XDECREF(result);
    return NULL;
}
#endif

static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line) {
    int start = 0, mid = 0, end = count - 1;
    if (end >= 0 && code_line > entries[end].code_line) {
        return count;
    }
    while (start < end) {
        mid = (start + end) / 2;
        if (code_line < entries[mid].code_line) {
            end = mid;
        } else if (code_line > entries[mid].code_line) {
             start = mid + 1;
        } else {
            return mid;
        }
    }
    if (code_line <= entries[mid].code_line) {
        return mid;
    } else {
        return mid + 1;
    }
}
static PyCodeObject *__pyx_find_code_object(int code_line) {
    PyCodeObject* code_object;
    int pos;
    if (unlikely(!code_line) || unlikely(!__pyx_code_cache.entries)) {
        return NULL;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if (unlikely(pos >= __pyx_code_cache.count) || unlikely(__pyx_code_cache.entries[pos].code_line != code_line)) {
        return NULL;
    }
    code_object = __pyx_code_cache.entries[pos].code_object;
    Py_INCREF(code_object);
    return code_object;
}
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object) {
    int pos, i;
    __Pyx_CodeObjectCacheEntry* entries = __pyx_code_cache.entries;
    if (unlikely(!code_line)) {
        return;
    }
    if (unlikely(!entries)) {
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Malloc(64*sizeof(__Pyx_CodeObjectCacheEntry));
        if (likely(entries)) {
            __pyx_code_cache.entries = entries;
            __pyx_code_cache.max_count = 64;
            __pyx_code_cache.count = 1;
            entries[0].code_line = code_line;
            entries[0].code_object = code_object;
            Py_INCREF(code_object);
        }
        return;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if ((pos < __pyx_code_cache.count) && unlikely(__pyx_code_cache.entries[pos].code_line == code_line)) {
        PyCodeObject* tmp = entries[pos].code_object;
        entries[pos].code_object = code_object;
        Py_DECREF(tmp);
        return;
    }
    if (__pyx_code_cache.count == __pyx_code_cache.max_count) {
        int new_max = __pyx_code_cache.max_count + 64;
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Realloc(
            __pyx_code_cache.entries, new_max*sizeof(__Pyx_CodeObjectCacheEntry));
        if (unlikely(!entries)) {
            return;
        }
        __pyx_code_cache.entries = entries;
        __pyx_code_cache.max_count = new_max;
    }
    for (i=__pyx_code_cache.count; i>pos; i--) {
        entries[i] = entries[i-1];
    }
    entries[pos].code_line = code_line;
    entries[pos].code_object = code_object;
    __pyx_code_cache.count++;
    Py_INCREF(code_object);
}

#include "compile.h"
#include "frameobject.h"
#include "traceback.h"
static PyCodeObject* __Pyx_CreateCodeObjectForTraceback(
            const char *funcname, int c_line,
            int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyObject *py_srcfile = 0;
    PyObject *py_funcname = 0;
    #if PY_MAJOR_VERSION < 3
    py_srcfile = PyString_FromString(filename);
    #else
    py_srcfile = PyUnicode_FromString(filename);
    #endif
    if (!py_srcfile) goto bad;
    if (c_line) {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        #else
        py_funcname = PyUnicode_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        #endif
    }
    else {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromString(funcname);
        #else
        py_funcname = PyUnicode_FromString(funcname);
        #endif
    }
    if (!py_funcname) goto bad;
    py_code = __Pyx_PyCode_New(
        0,            
        0,            
        0,            
        0,            
        0,            
        __pyx_empty_bytes, 
        __pyx_empty_tuple, 
        __pyx_empty_tuple, 
        __pyx_empty_tuple, 
        __pyx_empty_tuple, 
        __pyx_empty_tuple, 
        py_srcfile,   
        py_funcname,  
        py_line,      
        __pyx_empty_bytes  
    );
    Py_DECREF(py_srcfile);
    Py_DECREF(py_funcname);
    return py_code;
bad:
    Py_XDECREF(py_srcfile);
    Py_XDECREF(py_funcname);
    return NULL;
}
static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyObject *py_globals = 0;
    PyFrameObject *py_frame = 0;
    py_code = __pyx_find_code_object(c_line ? c_line : py_line);
    if (!py_code) {
        py_code = __Pyx_CreateCodeObjectForTraceback(
            funcname, c_line, py_line, filename);
        if (!py_code) goto bad;
        __pyx_insert_code_object(c_line ? c_line : py_line, py_code);
    }
    py_globals = PyModule_GetDict(__pyx_m);
    if (!py_globals) goto bad;
    py_frame = PyFrame_New(
        PyThreadState_GET(), 
        py_code,             
        py_globals,          
        0                    
    );
    if (!py_frame) goto bad;
    py_frame->f_lineno = py_line;
    PyTraceBack_Here(py_frame);
bad:
    Py_XDECREF(py_code);
    Py_XDECREF(py_frame);
}

static int __Pyx_InitStrings(__Pyx_StringTabEntry *t) {
    while (t->p) {
        #if PY_MAJOR_VERSION < 3
        if (t->is_unicode) {
            *t->p = PyUnicode_DecodeUTF8(t->s, t->n - 1, NULL);
        } else if (t->intern) {
            *t->p = PyString_InternFromString(t->s);
        } else {
            *t->p = PyString_FromStringAndSize(t->s, t->n - 1);
        }
        #else  
        if (t->is_unicode | t->is_str) {
            if (t->intern) {
                *t->p = PyUnicode_InternFromString(t->s);
            } else if (t->encoding) {
                *t->p = PyUnicode_Decode(t->s, t->n - 1, t->encoding, NULL);
            } else {
                *t->p = PyUnicode_FromStringAndSize(t->s, t->n - 1);
            }
        } else {
            *t->p = PyBytes_FromStringAndSize(t->s, t->n - 1);
        }
        #endif
        if (!*t->p)
            return -1;
        ++t;
    }
    return 0;
}




static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject* x) {
   int is_true = x == Py_True;
   if (is_true | (x == Py_False) | (x == Py_None)) return is_true;
   else return PyObject_IsTrue(x);
}

static CYTHON_INLINE PyObject* __Pyx_PyNumber_Int(PyObject* x) {
  PyNumberMethods *m;
  const char *name = NULL;
  PyObject *res = NULL;
#if PY_VERSION_HEX < 0x03000000
  if (PyInt_Check(x) || PyLong_Check(x))
#else
  if (PyLong_Check(x))
#endif
    return Py_INCREF(x), x;
  m = Py_TYPE(x)->tp_as_number;
#if PY_VERSION_HEX < 0x03000000
  if (m && m->nb_int) {
    name = "int";
    res = PyNumber_Int(x);
  }
  else if (m && m->nb_long) {
    name = "long";
    res = PyNumber_Long(x);
  }
#else
  if (m && m->nb_int) {
    name = "int";
    res = PyNumber_Long(x);
  }
#endif
  if (res) {
#if PY_VERSION_HEX < 0x03000000
    if (!PyInt_Check(res) && !PyLong_Check(res)) {
#else
    if (!PyLong_Check(res)) {
#endif
      PyErr_Format(PyExc_TypeError,
                   "__%s__ returned non-%s (type %.200s)",
                   name, name, Py_TYPE(res)->tp_name);
      Py_DECREF(res);
      return NULL;
    }
  }
  else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_TypeError,
                    "an integer is required");
  }
  return res;
}

static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject* b) {
  Py_ssize_t ival;
  PyObject* x = PyNumber_Index(b);
  if (!x) return -1;
  ival = PyInt_AsSsize_t(x);
  Py_DECREF(x);
  return ival;
}

static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t ival) {
#if PY_VERSION_HEX < 0x02050000
   if (ival <= LONG_MAX)
       return PyInt_FromLong((long)ival);
   else {
       unsigned char *bytes = (unsigned char *) &ival;
       int one = 1; int little = (int)*(unsigned char*)&one;
       return _PyLong_FromByteArray(bytes, sizeof(size_t), little, 0);
   }
#else
   return PyInt_FromSize_t(ival);
#endif
}

static CYTHON_INLINE size_t __Pyx_PyInt_AsSize_t(PyObject* x) {
   unsigned PY_LONG_LONG val = __Pyx_PyInt_AsUnsignedLongLong(x);
   if (unlikely(val == (unsigned PY_LONG_LONG)-1 && PyErr_Occurred())) {
       return (size_t)-1;
   } else if (unlikely(val != (unsigned PY_LONG_LONG)(size_t)val)) {
       PyErr_SetString(PyExc_OverflowError,
                       "value too large to convert to size_t");
       return (size_t)-1;
   }
   return (size_t)val;
}


#endif 
