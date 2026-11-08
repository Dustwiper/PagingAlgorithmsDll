#include <string>
#include <exception>

namespace paging{

    /**
     * @brief Класс, представляющий ошибки инициализации исходных данных
     * @details Реализует интерфейсы ошибок, возможных при заполненении исходной 
     *          структуры данных, обеспечивая безопасную работу вычислений алгоритма. 
     *          Наследуеся от std::exception.
     */
    class InitializationError : public std::exception{
    public:

        InitializationError(const std::string& message) : m_message(message)
        {}

        virtual const char* what() const noexcept override{
            return m_message.c_str();
        }

    private:
        std::string m_message;
    };

    /**
     * @brief Ошибка возможного выхода за пределы выделенной памяти.
     * @details Возникает, если количество фреймов памяти 
     *          меньше количества страниц в исходном состоянии памяти.
     */
    class ExceededMemoryError : public InitializationError{
    public:
        ExceededMemoryError(const std::string& initErrMessage) : 
                            InitializationError(initErrMessage) {}
        
    };

    /**
     * @brief Ошибка неопределённого поведения(undefind behavior).
     * @details Возникает, если установленное количество фреймов памяти = 0.
     */

    class ZeroMemorySlotsError : public InitializationError{
    public:
        ZeroMemorySlotsError(const std::string& memorySlotsError) :
                            InitializationError(memorySlotsError)
        {}
    };

    /**
     * @brief Ошибка дубликатов данных.
     * @details Возникает, если в исходых фреймах памяти присутствуют страницы с одинаковыми номерами.
     */

    class DuplicatesError : public InitializationError{
        public:
        DuplicatesError(const std::string& DuplicatesError) :
                        InitializationError(DuplicatesError)
        {}
    };

}