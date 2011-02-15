#include "fwrap_ktp_header.h"

#if !defined(FORTRAN_CALLSPEC)
#define FORTRAN_CALLSPEC
#endif

#if !defined(NO_FORTRAN_MANGLING)
    #if !defined(PREPEND_FORTRAN) && defined(NO_APPEND_FORTRAN) && !defined(UPPERCASE_FORTRAN)
        #define NO_FORTRAN_MANGLING 1
    #endif
#endif
#if defined(NO_FORTRAN_MANGLING)
    #define F_FUNC_MANGLING(f,F) f
#else
    #if defined(PREPEND_FORTRAN)
        #if defined(NO_APPEND_FORTRAN)
            #if defined(UPPERCASE_FORTRAN)
                #define F_FUNC_MANGLING(f,F) _##F
            #else
                #define F_FUNC_MANGLING(f,F) _##f
            #endif
        #else
            #if defined(UPPERCASE_FORTRAN)
                #define F_FUNC_MANGLING(f,F) _##F##_
            #else
                #define F_FUNC_MANGLING(f,F) _##f##_
            #endif
        #endif
    #else
        #if defined(NO_APPEND_FORTRAN)
            #if defined(UPPERCASE_FORTRAN)
                #define F_FUNC_MANGLING(f,F) F
            #else
                #error Can not happen
            #endif
        #else
            #if defined(UPPERCASE_FORTRAN)
                #define F_FUNC_MANGLING(f,F) F##_
            #else
                #define F_FUNC_MANGLING(f,F) f##_
            #endif
        #endif
    #endif
#endif

#if defined(__cplusplus)
#define F_FUNC(f,F) ::F_FUNC_MANGLING(f,F)
#else
#define F_FUNC(f,F) F_FUNC_MANGLING(f,F)
#endif


#if defined(__cplusplus)
extern "C" {
#endif
FORTRAN_CALLSPEC void F_FUNC_MANGLING(dopri5,DOPRI5)(
    fwi_integer_t * n,
    void (*fcn)(fwi_integer_t *, fwr_dbl_t *, fwr_dbl_t *, fwr_dbl_t *, void *, void *),
    fwr_dbl_t * x,
    fwr_dbl_t * y,
    fwr_dbl_t * xend,
    fwr_dbl_t * rtol,
    fwr_dbl_t * atol,
    fwi_integer_t * itol,
    void (*solout)(fwi_integer_t *, fwr_dbl_t *, fwr_dbl_t *, fwr_dbl_t *, fwi_integer_t *, fwr_dbl_t *, fwi_integer_t *, fwi_integer_t *, void *, void *, fwi_integer_t *),
    fwi_integer_t * iout,
    fwr_dbl_t * work,
    fwi_integer_t * lwork,
    fwi_integer_t * iwork,
    fwi_integer_t * liwork,
    void * rpar, /* caller context */
    void * ipar, /* caller context */
    fwi_integer_t * idid
);
FORTRAN_CALLSPEC void F_FUNC_MANGLING(dop853,DOP853)(
    fwi_integer_t * n,
    void (*fcn)(fwi_integer_t *, fwr_dbl_t *, fwr_dbl_t *, fwr_dbl_t *, void *, void *),
    fwr_dbl_t * x,
    fwr_dbl_t * y,
    fwr_dbl_t * xend,
    fwr_dbl_t * rtol,
    fwr_dbl_t * atol,
    fwi_integer_t * itol,
    void (*solout)(fwi_integer_t *, fwr_dbl_t *, fwr_dbl_t *, fwr_dbl_t *, fwi_integer_t *, fwr_dbl_t *, fwi_integer_t *, fwi_integer_t *, void *, void *, fwi_integer_t *),
    fwi_integer_t * iout,
    fwr_dbl_t * work,
    fwi_integer_t * lwork,
    fwi_integer_t * iwork,
    fwi_integer_t * liwork,
    void * rpar, /* caller context */
    void * ipar, /* caller context */
    fwi_integer_t * idid
);
#if defined(__cplusplus)
} /* extern "C" */
#endif

