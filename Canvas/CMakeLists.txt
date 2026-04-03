project("Canvas")

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false CONFIGURE_DEPENDS "Source/*.cpp")

add_library(${PROJECT_NAME} ${SOURCES})
add_library(Canvas::Canvas ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC Source)
target_link_libraries(${PROJECT_NAME} 
	PUBLIC
		SDL3::SDL3
		ImGui::ImGui
)