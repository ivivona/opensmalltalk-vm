SET (USE_LIBFFI)

IF (OPT_without-ffi)
  PLUGIN_DISABLE ()
ELSE ()
  IF (vm-host-cpu STREQUAL "powerpc" OR vm-host-cpu STREQUAL "ppc")
    SET (cpu ppc)
  ELSEIF (vm-host-cpu MATCHES  "i[3456789]86")
    SET (cpu x86)
  ELSEIF (vm-host-cpu STREQUAL "x86_64" AND CMAKE_ARCH_FLAGS STREQUAL "-m32")
    SET (cpu x86)
  ELSE ()
    SET (USE_LIBFFI 1)
  ENDIF ()

  IF (vm-host-os STREQUAL "linux")
    SET (abi sysv)
  ELSEIF (vm-host-os MATCHES "darwin.*")
    SET (abi darwin)
  ELSE ()
    SET (USE_LIBFFI 1)
  ENDIF ()

  IF (USE_LIBFFI
      OR NOT EXISTS "${unix}/plugins/${plugin}/${cpu}-${abi}.c"
      OR NOT EXISTS "${unix}/plugins/${plugin}/${cpu}-${abi}-asm.S")
    SET (cpu any)
    SET (abi libffi)
    PLUGIN_MESSAGE ("${cpu}-${abi}")
    PLUGIN_FIND_PACKAGE (LIBFFI libffi)
    IF (NOT LIBFFI_FOUND)
      CHECK_INCLUDE_FILE (ffi.h HAVE_FFI_H)
      CHECK_INCLUDE_FILE (ffi/ffi.h HAVE_FFI_FFI_H)
      IF (NOT HAVE_FFI_H AND NOT HAVE_FFI_FFI_H)
        PLUGIN_DISABLE ()
      ELSE ()
        PLUGIN_REQUIRE_LIBRARY (FFI ffi)
      ENDIF ()
    ENDIF ()
  ENDIF ()
  IF (EXISTS    "${src}/plugins/${plugin}/${plugin}.c")
    SET (SQFFIC "${src}/plugins/${plugin}/${plugin}.c")
  ELSEIF (EXISTS "${src}/vm/intplugins/${plugin}/${plugin}.c")
    SET (SQFFIC  "${src}/vm/intplugins/${plugin}/${plugin}.c")
  ELSE ()
    PLUGIN_DISABLE ()
  ENDIF ()
  ENABLE_LANGUAGE (ASM)
  PLUGIN_SOURCES ("${cross}/plugins/${plugin}/sqManualSurface.c ${SQFFIC} ${unix}/plugins/${plugin}/${cpu}-${abi}.c ${unix}/plugins/${plugin}/${cpu}-${abi}-asm.S")
  IF (CMAKE_COMPILER_IS_GNUCC)
    SET (CMAKE_ASM_COMPILER "${CMAKE_C_COMPILER}")
    SET (CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -c")
  ENDIF (CMAKE_COMPILER_IS_GNUCC)
ENDIF ()

CONFIG_DEFINE (HAVE_FFI_H)
CONFIG_DEFINE (HAVE_FFI_FFI_H)
