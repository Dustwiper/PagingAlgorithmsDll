#pragma once

/** Макрос экспорта функций 
 *  Указывает, что функция или класс будут доступными как элемент публичного API.
*/

#define PAGING_API __attribute__((visibility("default")))