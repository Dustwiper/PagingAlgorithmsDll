#pragma once

/** Макрос экспорта функций 
 *  Указывает, что функция или класс будут доступными как элемент публичного API.
*/

namespace dll_api{

#define PAGING_API __attribute__((visibility("default")))

}