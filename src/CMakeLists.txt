set(SOURCES
  ${PROJECT_SOURCE_DIR}/src/converter.cpp
  ${PROJECT_SOURCE_DIR}/src/hevc_manager.cpp
)

add_library(
  ${PROJECT_NAME}
  OBJECT
  ${SOURCES}
)

add_executable(
  ${PROJECT_NAME}-bin
  $<TARGET_OBJECTS:${PROJECT_NAME}>
  ${PROJECT_SOURCE_DIR}/src/main.cpp
)

include_directories (${INCLUDE_ROOT_DIR})