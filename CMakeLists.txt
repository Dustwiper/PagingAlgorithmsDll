# Минимальная версия для сборки проекта через CMAKE
cmake_minimum_required(VERSION 3.30)

# Имя проекта
set(PROJECT_NAME Paging_Algorithm_DLL)
project(${PROJECT_NAME})

# Стандарт языка С++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Компановка вычислительной части
add_library(PagingCore
    OBJECT
        source/paging_algorithm.cpp
        source/FIFO.cpp
        source/LRU.cpp
)

# Подключение заголовочных файлов
target_include_directories(PagingCore
    PUBLIC
        ${CMAKE_SOURCE_DIR}/headers
)

# Дополнительные настройки и флаги компиляции
target_compile_options(PagingCore
    PRIVATE
        -Wall
        -Wextra
)

# Настройка свойств целей
set_target_properties(PagingCore
    PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN YES
)

### Динамическая библиотека ###

add_library(Paging_Algorithm_lib SHARED)

# Использование уже прописанных путей от вычисительного модуля для библиотеки
target_link_libraries(Paging_Algorithm_lib
    PRIVATE
        PagingCore
)

set_target_properties(Paging_Algorithm_lib
    PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN YES
)

### Консольное приложение ###

# Создание цели для консольного приложения
add_executable(Paging_Algorithm_DLL
    source/main.cpp
    source/output_handler.cpp
)

target_link_libraries(Paging_Algorithm_DLL
    PRIVATE
        PagingCore
)

### Тема документации Doxygen ###

# Нахождение установленного DOXYGEN
find_package(Doxygen)

# Модуль загрузки зависимостей CMake
cmake_policy(SET CMP0168 NEW)
include(FetchContent) 

FetchContent_Declare(
    doxygen-awesome-css
    URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/heads/main.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# Загрузка темы и объявление её файлов доступными
FetchContent_MakeAvailable(doxygen-awesome-css)

FetchContent_GetProperties(doxygen-awesome-css)

set(AWESOME_CSS_DIR "${doxygen-awesome-css_SOURCE_DIR}")

message(STATUS "Doxygen Awesome CSS: ${AWESOME_CSS_DIR}")

# Путь к директории для сохранения документации
set(DOCS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/docs)

# Путь к Doxyfile.in
set(DOXYFILE_IN ${DOCS_DIR}/Doxyfile.in)
# Путь к Doxyfile.out
set(DOXYFILE_OUT ${DOCS_DIR}/Doxyfile.out)

# Создание дирктории под документацию
file(MAKE_DIRECTORY "${DOCS_DIR}")

# Создание Doxyfile из шаблона
configure_file(
    "${DOXYFILE_IN}"
    "${DOXYFILE_OUT}"
    @ONLY
)

# Добавление команды сборки документации
add_custom_target(
    docs
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating Doxygen Documentation"
    VERBATIM
)  

### Google Tests ###

# Запись параметров сторонней библиотеки
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.18.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# Скачивание и распаковка библиотеки
FetchContent_MakeAvailable(googletest)

message(STATUS GoogleTest: )

include(CTest)

if(BUILD_TESTING)
    # Создание цели 
    add_executable(dll_tests
        tests/FIFO_tests.cpp
        tests/LRU_tests.cpp
    )

    target_include_directories(dll_tests
        PRIVATE
           "${CMAKE_SOURCE_DIR}/tests"
    )

    target_link_libraries(dll_tests
        PRIVATE
            PagingCore
            GTest::gtest_main)

    # Регистрация тестов
    include(GoogleTest)
    gtest_discover_tests(dll_tests)
endif()