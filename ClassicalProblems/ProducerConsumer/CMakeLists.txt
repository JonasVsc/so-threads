project("ProducerConsumer")


file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false CONFIGURE_DEPENDS "Source/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})