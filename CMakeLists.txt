cmake_minimum_required(VERSION 3.31)
project("Threads"
	LANGUAGES CXX
)

SET(CMAKE_CXX_STANDARD 23)

add_subdirectory(ThirdParty/SDL)
add_subdirectory(ThirdParty/ImGui)

add_subdirectory(Canvas)
add_subdirectory(Test)

add_subdirectory(ClassicalProblems)
add_subdirectory(Project1)

