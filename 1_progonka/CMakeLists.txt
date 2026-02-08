cmake_minimum_required(VERSION 3.10)
project(ThreeDiagonalSolver)

# Находим все исходные файлы в папке src
file(GLOB SOURCES "src/*.cpp")

# Создаем исполняемый файл
add_executable(solver ${SOURCES})

# Указываем где искать заголовочные файлы
target_include_directories(solver PRIVATE include)