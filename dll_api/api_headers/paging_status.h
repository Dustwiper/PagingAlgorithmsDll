#ifndef PAGING_STATUS_H
#define PAGING_STATUS_H

/*Коды ошибок состояния*/

typedef enum PagingStatus{
    PAGING_SUCCESS = 0,    //Успешное выполнение
    PAGING_NULL_POINTER	= 1,	//Некорректный нулевой указатель
    PAGING_ZERO_MEMORY_FRAMES = 2,	//Нулевое количество кадров
    PAGING_MEMORY_LIMIT_EXCEEDED = 3,	//Превышен лимит кадров памяти
    PAGING_QUERY_LIMIT_EXCEEDED	= 4,	//Превышен лимит очереди запросов
    PAGING_EXCEEDED_MEMORY = 5,	//Начальное состояние превышает вместимость памяти
    PAGING_DUPLICATE_PAGES	= 6,	//Дубликаты начальных страниц
    PAGING_ALLOCATION_ERROR	= 7,	//Ошибка выделения памяти
    PAGING_INTERNAL_ERROR = 8,	//Прочая внутренняя ошибка библиотеки
} PagingStatus;

#endif