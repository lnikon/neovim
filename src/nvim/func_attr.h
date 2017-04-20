// If DEFINE_FUNC_ATTRIBUTES macro is not defined then all function attributes 
// are defined as empty values.
//
// If DO_NOT_DEFINE_EMPTY_ATTRIBUTES then empty macros are not defined. Thus 
// undefined DEFINE_FUNC_ATTRIBUTES and defined DO_NOT_DEFINE_EMPTY_ATTRIBUTES 
// leaves file with untouched FUNC_ATTR_* macros. This variant is used for 
// scripts/gendeclarations.lua.
//
// Empty macros are used for *.c files. (undefined DEFINE_FUNC_ATTRIBUTES and 
// undefined DO_NOT_DEFINE_EMPTY_ATTRIBUTES)
//
// Macros defined as __attribute__((*)) are used by generated header files. 
// (defined DEFINE_FUNC_ATTRIBUTES and undefined 
// DO_NOT_DEFINE_EMPTY_ATTRIBUTES)
//
// Defined DEFINE_FUNC_ATTRIBUTES and defined DO_NOT_DEFINE_EMPTY_ATTRIBUTES is 
// not used by anything.

// FUNC_ATTR_* macros should be in *.c files for declarations generator. If you 
// define a function for which declaration is not generated by 
// gendeclarations.lua (e.g. template hash implementation) then you should use 
// REAL_FATTR_* macros.

// gcc and clang expose their version as follows:
//
// gcc 4.7.2:
//   __GNUC__          = 4
//   __GNUC_MINOR__    = 7
//   __GNUC_PATCHLEVEL = 2
//
// clang 3.4 (claims compat with gcc 4.2.1):
//   __GNUC__          = 4
//   __GNUC_MINOR__    = 2
//   __GNUC_PATCHLEVEL = 1
//   __clang__         = 1
//   __clang_major__   = 3
//   __clang_minor__   = 4
//
// To view the default defines of these compilers, you can perform:
//
// $ gcc -E -dM - </dev/null
// $ echo | clang -dM -E -

#ifdef FUNC_ATTR_MALLOC
# undef FUNC_ATTR_MALLOC
#endif

#ifdef FUNC_ATTR_ALLOC_SIZE
# undef FUNC_ATTR_ALLOC_SIZE
#endif

#ifdef FUNC_ATTR_ALLOC_SIZE_PROD
# undef FUNC_ATTR_ALLOC_SIZE_PROD
#endif

#ifdef FUNC_ATTR_ALLOC_ALIGN
# undef FUNC_ATTR_ALLOC_ALIGN
#endif

#ifdef FUNC_ATTR_PURE
# undef FUNC_ATTR_PURE
#endif

#ifdef FUNC_ATTR_CONST
# undef FUNC_ATTR_CONST
#endif

#ifdef FUNC_ATTR_WARN_UNUSED_RESULT
# undef FUNC_ATTR_WARN_UNUSED_RESULT
#endif

#ifdef FUNC_ATTR_ALWAYS_INLINE
# undef FUNC_ATTR_ALWAYS_INLINE
#endif

#ifdef FUNC_ATTR_UNUSED
# undef FUNC_ATTR_UNUSED
#endif

#ifdef FUNC_ATTR_NONNULL_ALL
# undef FUNC_ATTR_NONNULL_ALL
#endif

#ifdef FUNC_ATTR_NONNULL_ARG
# undef FUNC_ATTR_NONNULL_ARG
#endif

#ifdef FUNC_ATTR_NONNULL_RET
# undef FUNC_ATTR_NONNULL_RET
#endif

#ifdef FUNC_ATTR_NORETURN
# undef FUNC_ATTR_NORETURN
#endif

#ifndef DID_REAL_ATTR
# define DID_REAL_ATTR
# ifdef __GNUC__
// place defines for all gnulikes here, for now that's gcc, clang and
// intel.

// place these after the argument list of the function declaration
// (not definition), like so:
// void myfunc(void) REAL_FATTR_ALWAYS_INLINE;
#  define REAL_FATTR_MALLOC __attribute__((malloc))
#  define REAL_FATTR_ALLOC_ALIGN(x) __attribute__((alloc_align(x)))
#  define REAL_FATTR_PURE __attribute__ ((pure))
#  define REAL_FATTR_CONST __attribute__((const))
#  define REAL_FATTR_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#  define REAL_FATTR_ALWAYS_INLINE __attribute__((always_inline))
#  define REAL_FATTR_UNUSED __attribute__((unused))
#  define REAL_FATTR_NONNULL_ALL __attribute__((nonnull))
#  define REAL_FATTR_NONNULL_ARG(...) __attribute__((nonnull(__VA_ARGS__)))
#  define REAL_FATTR_NORETURN __attribute__((noreturn))

#  ifdef __clang__
// clang only
#  elif defined(__INTEL_COMPILER)
// intel only
#  else
#   define GCC_VERSION \
            (__GNUC__ * 10000 + \
             __GNUC_MINOR__ * 100 + \
             __GNUC_PATCHLEVEL__)
// gcc only
#   define REAL_FATTR_ALLOC_SIZE(x) __attribute__((alloc_size(x)))
#   define REAL_FATTR_ALLOC_SIZE_PROD(x, y) __attribute__((alloc_size(x, y)))
#   if GCC_VERSION >= 40900
#    define REAL_FATTR_NONNULL_RET __attribute__((returns_nonnull))
#   endif
#  endif
# endif

// define function attributes that haven't been defined for this specific
// compiler.

# ifndef REAL_FATTR_MALLOC
#  define REAL_FATTR_MALLOC
# endif

# ifndef REAL_FATTR_ALLOC_SIZE
#  define REAL_FATTR_ALLOC_SIZE(x)
# endif

# ifndef REAL_FATTR_ALLOC_SIZE_PROD
#  define REAL_FATTR_ALLOC_SIZE_PROD(x, y)
# endif

# ifndef REAL_FATTR_ALLOC_ALIGN
#  define REAL_FATTR_ALLOC_ALIGN(x)
# endif

# ifndef REAL_FATTR_PURE
#  define REAL_FATTR_PURE
# endif

# ifndef REAL_FATTR_CONST
#  define REAL_FATTR_CONST
# endif

# ifndef REAL_FATTR_WARN_UNUSED_RESULT
#  define REAL_FATTR_WARN_UNUSED_RESULT
# endif

# ifndef REAL_FATTR_ALWAYS_INLINE
#  define REAL_FATTR_ALWAYS_INLINE
# endif

# ifndef REAL_FATTR_UNUSED
#  define REAL_FATTR_UNUSED
# endif

# ifndef REAL_FATTR_NONNULL_ALL
#  define REAL_FATTR_NONNULL_ALL
# endif

# ifndef REAL_FATTR_NONNULL_ARG
#  define REAL_FATTR_NONNULL_ARG(...)
# endif

# ifndef REAL_FATTR_NONNULL_RET
#  define REAL_FATTR_NONNULL_RET
# endif

# ifndef REAL_FATTR_NORETURN
#  define REAL_FATTR_NORETURN
# endif
#endif

#ifdef DEFINE_FUNC_ATTRIBUTES
# define FUNC_API_ASYNC
# define FUNC_API_NOEXPORT
# define FUNC_API_REMOTE_ONLY
# define FUNC_API_SINCE(X)
# define FUNC_API_DEPRECATED_SINCE(X)
# define FUNC_ATTR_MALLOC REAL_FATTR_MALLOC
# define FUNC_ATTR_ALLOC_SIZE(x) REAL_FATTR_ALLOC_SIZE(x)
# define FUNC_ATTR_ALLOC_SIZE_PROD(x, y) REAL_FATTR_ALLOC_SIZE_PROD(x, y)
# define FUNC_ATTR_ALLOC_ALIGN(x) REAL_FATTR_ALLOC_ALIGN(x)
# define FUNC_ATTR_PURE REAL_FATTR_PURE
# define FUNC_ATTR_CONST REAL_FATTR_CONST
# define FUNC_ATTR_WARN_UNUSED_RESULT REAL_FATTR_WARN_UNUSED_RESULT
# define FUNC_ATTR_ALWAYS_INLINE REAL_FATTR_ALWAYS_INLINE
# define FUNC_ATTR_UNUSED REAL_FATTR_UNUSED
# define FUNC_ATTR_NONNULL_ALL REAL_FATTR_NONNULL_ALL
# define FUNC_ATTR_NONNULL_ARG(...) REAL_FATTR_NONNULL_ARG(__VA_ARGS__)
# define FUNC_ATTR_NONNULL_RET REAL_FATTR_NONNULL_RET
# define FUNC_ATTR_NORETURN REAL_FATTR_NORETURN
#elif !defined(DO_NOT_DEFINE_EMPTY_ATTRIBUTES)
# define FUNC_ATTR_MALLOC
# define FUNC_ATTR_ALLOC_SIZE(x)
# define FUNC_ATTR_ALLOC_SIZE_PROD(x, y)
# define FUNC_ATTR_ALLOC_ALIGN(x)
# define FUNC_ATTR_PURE
# define FUNC_ATTR_CONST
# define FUNC_ATTR_WARN_UNUSED_RESULT
# define FUNC_ATTR_ALWAYS_INLINE
# define FUNC_ATTR_UNUSED
# define FUNC_ATTR_NONNULL_ALL
# define FUNC_ATTR_NONNULL_ARG(...)
# define FUNC_ATTR_NONNULL_RET
# define FUNC_ATTR_NORETURN
#endif
