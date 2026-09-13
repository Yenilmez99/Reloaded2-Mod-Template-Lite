cmake_minimum_required(VERSION 3.15)

# --- C++ Project ---
project(Reloaded2_Template LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(ModCXX SHARED src/main.cpp)

set_target_properties(ModCXX PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "x86")
set_target_properties(ModCXX PROPERTIES OUTPUT_NAME "ModCXX_Output")

target_include_directories(ModCXX PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# --- C# Project (For Configure Menu) ---
add_custom_target(CSharpBase ALL
	COMMAND dotnet build "${CMAKE_CURRENT_SOURCE_DIR}/CSharpBase.csproj"
		-c Release
		-o "$<TARGET_FILE_DIR:ModCXX>"
	WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/csharp"
	COMMENT "Building C# Mod Menu via dotnet CLI..."
)

# --- Copying Other Files ---
add_custom_command(TARGET ModCXX POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${CMAKE_CURRENT_SOURCE_DIR}/src/ModConfig.json"
		"$<TARGET_FILE_DIR:ModCXX>/ModConfig.json"

	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${CMAKE_CURRENT_SOURCE_DIR}/src/Preview.png"
		"$<TARGET_FILE_DIR:ModCXX>/Preview.png"

	COMMENT "Copying Other Files..."
)