SET(TARGET sort_project_main)

add_executable(${TARGET}
    stdafx.cpp
    SortAlgorithm.cpp
	AppEnv.cpp
    main.cpp
)

target_include_directories(${TARGET} PRIVATE
    ../includes
    ../includes/SFML
)

IF (WIN32)
target_link_libraries(${TARGET} PRIVATE
	flac
	freetype
	ogg
	openal32
	vorbis
	vorbisenc
	vorbisfile
	sfml-main
	sfml-graphics
	sfml-audio
	sfml-window
	sfml-system
	sfml-network
)
ELSE()
target_link_libraries(${TARGET} PRIVATE
    sfml-graphics
    sfml-audio
    sfml-window
    sfml-system
    sfml-network
)

target_compile_options(${TARGET} PRIVATE
    -std=c++11
    -stdlib=libc++
    -g3
)
ENDIF()