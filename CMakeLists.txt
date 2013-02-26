#/*
#-----------------------------------------------------------------------------
#Filename:   CMakeLists.txt
#-----------------------------------------------------------------------------
# This is based on the CMakeLists.txt from the Ogre Wiki Tutorial Framework
#-----------------------------------------------------------------------------
#*/
cmake_minimum_required(VERSION 2.6)

# Sets the C++ compiler. We can add debug marker here.
set(EXECUTABLE_NAME OxenApp)

if(UNIX)
	add_definitions(-std=c++11)
endif(UNIX)

project(${EXECUTABLE_NAME})

#{{{ Libraries and Include Directories

#{{{ Find the OGRE directory
if(WIN32)
	set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
	set(OGRE_SAMPLES_INCLUDEPATH
		$ENV{OGRE_HOME}/Samples/include
	)
endif(WIN32)

if(UNIX)
	if(EXISTS "/usr/local/lib/OGRE/cmake")

	  set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	  set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") # We could just *assume* that developers uses this basepath : /usr/local
	elseif(EXISTS "/usr/lib/OGRE/cmake")

	  set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	  set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/") # Otherwise, this one

	else ()
	  message(SEND_ERROR "Failed to find module path.")
	endif(EXISTS "/usr/local/lib/OGRE/cmake")
endif(UNIX)
 
if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()
 
set(CMAKE_DEBUG_POSTFIX "_d")

# Set the install install directory (i.e. the location of the bin folder to be
# /dist
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/dist")
#}}}

#{{{ Find OGRE
find_package(OGRE REQUIRED)

#if(NOT "${OGRE_VERSION_NAME}" STREQUAL "Cthugha")
#	message(SEND_ERROR "You need Ogre 1.7 Cthugha to build this.")
#endif()
# }}}

#{{{ Find OIS

find_package(OIS REQUIRED)

if(NOT OIS_FOUND)
	message(SEND_ERROR "Failed to find OIS.")
endif()
#}}}

#{{{ Find Boost
if (NOT OGRE_BUILD_PLATFORM_IPHONE)
	if (WIN32 OR APPLE)
		set(Boost_USE_STATIC_LIBS TRUE)
	else ()
		# Statically linking boost to a dynamic Ogre build doesn't work on
		# Linux 64bit
		set(Boost_USE_STATIC_LIBS ${OGRE_STATIC})
	endif ()

	if (MINGW)
		# this is probably a bug in CMake: the boost find module tries to look
		# for boost libraries with name libboost_*, but CMake already prefixes
		# library search names with "lib". This is the workaround.
		set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
	endif ()

	set(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
	# Components that need linking (NB does not include header-only components
    # like bind)
	set(OGRE_BOOST_COMPONENTS system thread date_time)
	find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)

	if (NOT Boost_FOUND)
		# Try again with the other type of libs
		set(Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
		find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	endif()

	find_package(Boost QUIET)

	# Set up referencing of Boost
	include_directories(${Boost_INCLUDE_DIR})
	add_definitions(-DBOOST_ALL_NO_LIB)
	set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
endif()
#}}}

#{{{ Find the CEGUI libraries and include directories 
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules;${CMAKE_MODULE_PATH}")
find_package(CEGUI REQUIRED COMPONENTS Ogre)

# If we find the CEGUI libraries and include directories add them to the project
if(CEGUI_FOUND)
	set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${CEGUI_LIBRARY})
endif(CEGUI_FOUND)
#}}}

#}}}

#{{{ Headers and Sources
set(HDRS
	# Dependecies
	rapidxml/rapidxml.hpp

	#Game
	AppState.h
	AppStateManager.h
	Framework.h
	MainMenu.h
	GameState.h
	MenuManager.h
	OxenApp.h
	# Engine code
	Engine/Engine.h
	Engine/RenderEntity.h
	Engine/PhysicsEntity.h
	Engine/EntityMgr.h
	# Engine Networking code
	Engine/Networking/NetworkedEntity.h
)
 
set(SRCS
	#Game
	AppStateManager.cpp
	Framework.cpp
	MainMenu.cpp
	GameState.cpp
	main.cpp
	MenuManager.cpp
	OxenApp.cpp
	# Engine code
	Engine/Engine.cpp
	Engine/RenderEntity.cpp
	Engine/PhysicsEntity.cpp
	Engine/EntityMgr.cpp
)
#}}}

#{{{ Include Directories
 
include_directories( ${OIS_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	${OGRE_SAMPLES_INCLUDEPATH}
	${CEGUI_INCLUDE_DIR}
	)
#}}}

#{{{ Making the exectuable
add_executable(${EXECUTABLE_NAME} WIN32 ${HDRS} ${SRCS})

set_target_properties(${EXECUTABLE_NAME} PROPERTIES DEBUG_POSTFIX _d)

target_link_libraries(${EXECUTABLE_NAME} ${OGRE_LIBRARIES} ${OIS_LIBRARIES})

#file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/bin)
#file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/media)
file(COPY ${CMAKE_SOURCE_DIR}/dist DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# post-build copy for win32
if(WIN32 AND NOT MINGW)
	add_custom_command( TARGET ${EXECUTABLE_NAME} PRE_BUILD
		COMMAND if not exist .\\dist\\bin mkdir .\\dist\\bin )
	add_custom_command( TARGET ${EXECUTABLE_NAME} POST_BUILD
		COMMAND copy \"$(TargetPath)\" .\\dist\\bin ) #"# Makes vims colouring work
endif(WIN32 AND NOT MINGW)

if(MINGW OR UNIX)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)
endif(MINGW OR UNIX)
#}}}
 
#{{{ Install
#{{{ Windows
if(WIN32)
	install(TARGETS ${EXECUTABLE_NAME}
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)

	install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/Media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
		)

	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
		)

	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins_d.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources_d.cfg
		DESTINATION bin
		CONFIGURATIONS Debug
		)

	# NOTE: for the 1.7.1 sdk the OIS dll is called OIS.dll instead of
	# libOIS.dll so you'll have to change that to make it work with 1.7.1
	install(FILES ${OGRE_PLUGIN_DIR_REL}/OgreMain.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_Direct3D9.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL.dll
		${OGRE_PLUGIN_DIR_REL}/libOIS.dll
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
		)

	install(FILES ${OGRE_PLUGIN_DIR_DBG}/OgreMain_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_Direct3D9_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_GL_d.dll
		${OGRE_PLUGIN_DIR_DBG}/libOIS_d.dll
		DESTINATION bin
		CONFIGURATIONS Debug
		)

	# as of sdk 1.7.2 we need to copy the boost dll's as well
	# because they're not linked statically (it worked with 1.7.1 though)
	install(FILES ${Boost_DATE_TIME_LIBRARY_RELEASE}
		${Boost_THREAD_LIBRARY_RELEASE}
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
		)

	install(FILES ${Boost_DATE_TIME_LIBRARY_DEBUG}
		${Boost_THREAD_LIBRARY_DEBUG}
		DESTINATION bin
		CONFIGURATIONS Debug
		)
endif(WIN32)
#}}}

#{{{ Unix
if(UNIX)

	install(TARGETS ${EXECUTABLE_NAME}
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)

	install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
		)

	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
endif(UNIX)
#}}}
#}}}

# vim: foldmethod=marker
