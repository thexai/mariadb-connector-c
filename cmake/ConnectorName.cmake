#
#  Copyright (C) 2013-2016 MariaDB Corporation AB
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the COPYING-CMAKE-SCRIPTS file.
#

include(CheckSymbolExists)

check_symbol_exists(_X86_ "Windows.h" _X86_)
check_symbol_exists(_AMD64_ "Windows.h" _AMD64_)
check_symbol_exists(_ARM_ "Windows.h" _ARM_)
check_symbol_exists(_ARM64_ "Windows.h" _ARM64_)

MACRO(GET_CONNECTOR_PACKAGE_NAME name)
SET (PLATFORM_NAME ${CMAKE_SYSTEM_NAME})
SET (MACHINE_NAME ${CMAKE_SYSTEM_PROCESSOR})
SET (CONCAT_SIGN "-")

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
  IF(CMAKE_SYSTEM_NAME MATCHES "WindowsStore")
    SET(PLATFORM_NAME "winstore")
   ELSE()
    SET(PLATFORM_NAME "win")
  ENDIF()
  SET(CONCAT_SIGN "")
  IF(_x86_)
    SET(MACHINE_NAME "32")
  ELSEIF(_AMD64_)
    SET(MACHINE_NAME "x64")
  ELSEIF(_ARM_)
    SET(MACHINE_NAME "arm")
  ELSEIF(_ARM64_)
    SET(MACHINE_NAME "arm64")
  ENDIF()
ENDIF()

SET(product_name "mysql-connector-c-${CPACK_PACKAGE_VERSION}-${PLATFORM_NAME}${CONCAT_SIGN}${MACHINE_NAME}")
STRING(TOLOWER ${product_name} ${name})
ENDMACRO()
