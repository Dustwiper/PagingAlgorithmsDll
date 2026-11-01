# Минимальная версия для сборки проекта через CMAKE
cmake_minimum_required(VERSION 3.30)

# Имя проекта
set(PROJECT_NAME Paging_Algorithm_DLL)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME})

# Стандарт языка С++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Исходные файлы
target_sources(${PROJECT_NAME}
    PRIVATE
    source/main.cpp
    source/FIFO.cpp
    source/input_output_handler.cpp
    source/LRU.cpp
)

# Заголовочные файлы
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

# Флаги сборки
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

### Настройки dll ###

# Создание новой цели-библиотеки из перечисленных файлов исходного кода
add_library(Paging_Algorithm_lib SHARED
    source/FIFO.cpp
    source/LRU.cpp
)

# Указание пути к заголовочным файлам.
target_include_directories(Paging_Algorithm_lib
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/headers"
)

# Указание возможностей языка, требуемых для сборки
target_compile_features(Paging_Algorithm_lib
    PUBLIC cxx_std_17
)

# Все символы библиотеки по умолчанию скрыты
set_target_properties(Paging_Algorithm_lib PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    # Дополнительно позволяет скрывать многие inline функции
    VISIBILITY_INLINES_HIDDEN YES
)

### Тема документации Doxygen ###

# Нахождение установленного DOXYGEN с требованием строгой обязательности
find_package(Doxygen REQUIRED)

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
        source/FIFO.cpp
        source/LRU.cpp
    )

    target_include_directories(dll_tests
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/headers/
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/
    )

    target_link_libraries(dll_tests
        PRIVATE
            GTest::gtest_main)

    # Регистрация тестов
    include(GoogleTest)
    gtest_discover_tests(dll_tests)
endif()