add_subdirectory(QArchive)

add_library(StageManagerLib SHARED
    File.h
    File.cpp
    Linux.h
    Linux.cpp
    System.h
)

set_target_properties(StageManagerLib PROPERTIES OUTPUT_NAME "StageManager")
target_link_libraries(StageManagerLib PRIVATE ${LibArchive_LIBRARY})
include_directories(${LibArchive_INCLUDE})
