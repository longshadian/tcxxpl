
IF(WIN32)
    FIND_PATH(BOOST_INCLUDE_DIR boost/asio.hpp
        PATHS
        E:\\gitpro\\vcpkg\\installed\\x86-windows\\include
        
        NO_DEFAULT_PATH
    )
ELSEIF(UNIX)
    FIND_PATH(BOOST_INCLUDE_DIR boost/asio.hpp
        PATHS
        /usr/include
        /usr/local/include
        
        NO_DEFAULT_PATH
    )
ENDIF(WIN32)

IF(NOT BOOST_INCLUDE_DIR)
    MESSAGE(FATAL_ERROR "Can't find BOOST_INCLUDE_DIR: ${BOOST_INCLUDE_DIR}")
  ELSE()
    MESSAGE("Set BOOST_INCLUDE_DIR: ${BOOST_INCLUDE_DIR}")
ENDIF()


IF(WIN32)
    FIND_PATH(BOOST_LIBRARY_DIR boost_system-vc140-mt-gd.lib
        PATHS
        E:\\gitpro\\vcpkg\\installed\\x86-windows\\debug\\lib
        
        NO_DEFAULT_PATH
    )
ELSEIF(UNIX)
    FIND_PATH(BOOST_LIBRARY_DIR libboost_system.so
        PATHS
        /usr/lib
        /usr/local/lib
        
        NO_DEFAULT_PATH
    )
ENDIF(WIN32)

IF(NOT BOOST_LIBRARY_DIR)
    MESSAGE(FATAL_ERROR "Can't find BOOST_LIBRARY_DIR: ${BOOST_LIBRARY_DIR}")
  ELSE()
    MESSAGE("Set BOOST_LIBRARY_DIR: ${BOOST_LIBRARY_DIR}")
ENDIF()

IF(WIN32)
    FIND_LIBRARY(LIB_BOOST_LOG boost_log-vc140-mt-gd.lib PATHS ${BOOST_LIBRARY_DIR})
    FIND_LIBRARY(LIB_BOOST_THREAD boost_thread-vc140-mt-gd.lib PATHS ${BOOST_LIBRARY_DIR})
    FIND_LIBRARY(LIB_BOOST_DATE_TIME boost_date_time-vc140-mt-gd.lib PATHS ${BOOST_LIBRARY_DIR})
    FIND_LIBRARY(LIB_BOOST_FILESYSTEM boost_filesystem-vc140-mt-gd.lib PATHS ${BOOST_LIBRARY_DIR})
    FIND_LIBRARY(LIB_BOOST_SYSTEM boost_system-vc140-mt-gd.lib PATHS ${BOOST_LIBRARY_DIR})
ELSEIF(UNIX)
    FIND_LIBRARY(LIB_BOOST_LOG libboost_log.so PATHS ${BOOST_LIBRARY_DIR})
    FIND_LIBRARY(LIB_BOOST_THREAD libboost_thread.so PATHS ${BOOST_LIBRARY_DIR})
    FIND_LIBRARY(LIB_BOOST_DATE_TIME libboost_date_time.so PATHS ${BOOST_LIBRARY_DIR})
    FIND_LIBRARY(LIB_BOOST_FILESYSTEM libboost_filesystem.so PATHS ${BOOST_LIBRARY_DIR})
    FIND_LIBRARY(LIB_BOOST_SYSTEM libboost_system.so PATHS ${BOOST_LIBRARY_DIR})
ENDIF(WIN32)

IF(NOT LIB_BOOST_LOG)
    MESSAGE(FATAL_ERROR "Can't find LIB_BOOST_LOG")
ENDIF()

IF(NOT LIB_BOOST_THREAD)
    MESSAGE(FATAL_ERROR "Can't find LIB_BOOST_THREAD")
ENDIF()

IF(NOT LIB_BOOST_DATE_TIME)
    MESSAGE(FATAL_ERROR "Can't find LIB_BOOST_DATE_TIME")
ENDIF()

IF(NOT LIB_BOOST_SYSTEM)
    MESSAGE(FATAL_ERROR "Can't find LIB_BOOST_SYSTEM")
ENDIF()

IF(NOT LIB_BOOST_FILESYSTEM)
    MESSAGE(FATAL_ERROR "Can't find LIB_BOOST_FILESYSTEM")
ENDIF()

SET(BOOST_LIBRARIES ${LIB_BOOST_LOG}
                    ${LIB_BOOST_THREAD}
                    ${LIB_BOOST_DATE_TIME}
                    ${LIB_BOOST_FILESYSTEM}
                    ${LIB_BOOST_SYSTEM}
    CACHE STRING "boost libraries")