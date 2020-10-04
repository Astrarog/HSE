add_library(OpenCV::OpenCV UNKNOWN IMPORTED)

target_include_directories(OpenCV::OpenCV INTERFACE "${OpenCV_INCLUDE_DIRS}")

set_target_properties(OpenCV::OpenCV PROPERTIES
    IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
    IMPORTED_LOCATION {${OpenCV_LIBS}})
