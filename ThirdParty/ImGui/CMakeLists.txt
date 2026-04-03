project("ImGui")

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false CONFIGURE_DEPENDS "Source/*.cpp")

add_library(${PROJECT_NAME} ${SOURCES})
add_library(ImGui::ImGui ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

target_include_directories(${PROJECT_NAME} PUBLIC "Source")
target_include_directories(${PROJECT_NAME} PUBLIC "Backends")

# Backend

file(GLOB BACKEND_SOURCES "Backends/imgui_impl_sdl3.cpp" "Backends/imgui_impl_sdlrenderer3.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${BACKEND_SOURCES}) 


