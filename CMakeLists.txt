project(UsabilitySurvey)

find_package(Boost REQUIRED)
find_package(KDE4 REQUIRED)

include(KDE4Defaults)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
enable_testing()

add_definitions(
    ${QT_DEFINITIONS}
    ${KDE4_DEFINITIONS}
    ${KDE4_ENABLE_EXCEPTIONS}
)

include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   ${KDE4_INCLUDES}
)

add_subdirectory(contents)