#include <stdafx.h>
#include <Graphics.hpp>
#include <AppEnv.h>

/**
	@file
		Файл для декларации классов сортировок
	@author
		Zyukov Alexander Vadimovich (ellusive)
	@date
		2020 April 25
*/

namespace Sort {
    /**
	@short
	    Базовый класс для описания алгоритма сортировки
    */
    class Algorithm {
    public:
	/**
	    @short
		Конструктор по умолчанию
	*/
        Algorithm();
        
        /**
    	    @short
    		Конструктор с параметрами
    	    @param[in] name - имя алгоритма сортировки
        */
        Algorithm(std::string const & name);
        
	/**
	    @short
		Абстрактная функция сортировки массива
	    @param[in] array - массив значений для сортировки
	    @param[in] size - размер массива значений
	*/
	virtual void Sort(sf::RectangleShape ** array, size_t size) = 0;

	/**
	    @short
		Получить имя алгоритма сортировки
	    @return Имя алгоритма сортировки
	*/
	const std::string & GetName() const { return algName; };

	/**
	    @short
		Получить кол-во сравнений
	    @return Кол-во сравнений
	*/
	const int GetMergeCount() const { return *environment->GetCurrentMergeCount(); }

	/**
	    @short
		Получить кол-во доступов к массиву
	    @return Кол-во доступов к массиву
	*/
	const int GetAccessCount() const { return *environment->GetCurrentAccessCount(); }
    protected:
	// Указатель на окружение приложения
	Sort::AppEnv * environment;
	
	/**
	    @short
		Распечатать итоговую информация по сортировке
		в консоль
	*/
	void PrintFinalInfo();
    private:
	// Имя алгоритма сортировки
        std::string algName;
    };

    /**
	@short
	    Декларация класса сортировки пузырьком
    */
    class BubbleSort : public Algorithm {
    public:
	/**
	    @short
		Конструктор по умолчанию
	*/
	BubbleSort() : Algorithm("Bubble Sort") {};
	
	/**
	    @short
		Конструктор с параметрами
	    @param[in] name - имя алгоритма сортировки
	*/
	BubbleSort(std::string const & name) : Algorithm(name) {};

	/**
	    @short
		Конструктор с параметрами (перегрузка)
	    @param[in] environment - указатель на окружение приложения
	*/
	BubbleSort(Sort::AppEnv * _environment);
	
	/**
	    @short
		Переопределенная функция сортировки массива
	    @param[in] array - указатель на массив значений для сортировки
	    @param[in] size - размер массива значений
	*/
	virtual void Sort(sf::RectangleShape ** array, size_t size) override final;
    };

    /**
	@short
	    Декларация класса алгоритма быстрой сортировки
    */
    class QuickSort : public Algorithm {
    public:
	/**
	    @short
		Конструктор по умолчанию
	*/
	QuickSort() : Algorithm("Bubble Sort") {};

	/**
	    @short
		Конструктор с параметрами
	    @param[in] name - имя алгоритма сортировки
	*/
	QuickSort(std::string const & name) : Algorithm(name) {};

	/**
	    @short
		Конструктор с параметрами (перегрузка)
	    @param[in] _environment - указатель на окружение приложения
	*/
	QuickSort(Sort::AppEnv * _environment);

	/**
	    @short
		Переопределенная функция сортировки массива
	    @param[in] array - указатель на массив значений для сортировки
	    @param[in] size -размер массива значений
	*/
	virtual void Sort(sf::RectangleShape ** array, size_t size) override final;
    private:
	/**
	    @short
		Внутренняя реализация функции сортировки
	    @param[in] array - указатель на массив значений для сортировки
	    @param[in] low - нижняя граница массива значений
	    @param[in] high - верхняя граница массива значений
	*/
	void SortImpl(sf::RectangleShape ** array, size_t low, size_t high);
    };

    /**
	@short
	    Декларация класса алгоритма Shell сортировки
    */
    class ShellSort : public Algorithm {
    public:
	/**
	    @short
		Конструктор по умолчанию
	*/
	ShellSort() : Algorithm("Shell Sort") {};

	/**
	    @short
		Конструктор с параметрами
	    @param[in] name - имя алгоритма сортировки
	*/
	ShellSort(std::string const & name) : Algorithm(name) {};

	/**
	    @short
		Конструктор с параметрами (перегрузка)
	    @param[in] _environment - указатель на окружение приложения
	*/
	ShellSort(Sort::AppEnv * _environment);

	/**
	    @short
		Переопределенная функция сортировки массива
	    @param[in] array - указатель на массив значений для сортировки
	    @param[in] size - размер массива значений
	*/
	virtual void Sort(sf::RectangleShape ** array, size_t size) override final;
    };

    /**
	@short
	    Декларация класса алгоритма Gnome сортировки
    */
    class GnomeSort : public Algorithm {
    public:
	/**
	    @short
		Конструктор по умолчанию
	*/
	GnomeSort() : Algorithm("Gnome Sort") {};

	/**
	    @short
		Конструктор с параметрами
	    @param[in] name - имя алгоритма сортировки
	*/
	GnomeSort(std::string const & name) : Algorithm(name) {};

	/**
	    @short
		Конструктор с параметрами (перезгрузка)
	    @param[in] _environment - указатель на окружение приложения
	*/
	GnomeSort(Sort::AppEnv * _environment);

	/**
	    @short
		Переопределенная функция сортировки массива
	    @param[in] array - указатель на массив значений для сортировки
	    @param[in] size - размер массива значений
	*/
	virtual void Sort(sf::RectangleShape ** array, size_t size) override final;
    };
} // Sort
