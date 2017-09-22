DEFINES += GSL_DLL
INCLUDEPATH += $$PWD\include
LIBS += -L$$PWD\lib -llibgsl_dll
LIBS += -L$$PWD\lib -llibgslcblas_dll

LIBS += -L$$PWD\lib -llibgsl
LIBS += -L$$PWD\lib -llibgslcblas

LIBS += -L$$PWD\lib -llibgsl_d
LIBS += -L$$PWD\lib -llibgslcblas_d

LIBS += -L$$PWD\lib -llibgsl_dll_d
LIBS += -L$$PWD\lib -llibgslcblas_dll_d
