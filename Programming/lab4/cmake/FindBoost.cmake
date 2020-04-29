add_library(Boost::Boost UNKNOWN IMPORTED)

target_include_directories(Boost::Boost INTERFACE "${Boost_INCLUDE_DIRS}")

set_target_properties(Boost::Boost PROPERTIES
    IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
    IMPORTED_LOCATION {${Boost_LIBS}})
