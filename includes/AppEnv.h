#include <stdafx.h>
/**
	@file
		Файл декларации членов и функций класса окружения.
		Класс окружения необходим для доступа к совместно-используемой информации между
		потоками
	@author
		Zyukov Alexander Vadimovich (ellusive)
	@date
		2020 April 24
*/


namespace Sort {

	class AppEnv {
	public:
		/**
			@short
				Конструктор с параметрами
			@param[in] windowWidth - ширина окна
			@param[in] windowHeight - высота окна
		*/
		AppEnv(const uint32_t windowWidth, const uint32_t windowHeight);

		/**
			@short
				Получить мьютекс для доступа к текущему сортируемому элементу
			@return 
				Указатель на мьютекс для доступа к текущему сортируемому элементу
		*/
		std::mutex * GetLockElementMutex();

		/**
			@short
				Получить текущий сортируемый элемент
			@return
				Указатель на текущий сортируемый элемент
		*/
		int * GetLockElement();

		/**
			@short
				Получить окно для отрисовки
			@return
				Указатель на окно для сортировки
		*/
		sf::RenderWindow * GetWindow();
		
		/**
			@short
				Получить флаг завершения потока отрисовки
			@return
				Указатель флаг, указывающий на необходимость завершения потока отрисовки
				окна
		*/
		bool * GetCancelled();
		
		/**
			@short
				Получить текущее наименование алгоритма
			@return
				Ссылка на наименование текущего алгоритма сортировки
		*/
		std::string & GetCurrentAlgName();
		
		/**
			@short
				Получить кол-во сравнений
			@return
				Указатель на кол-во сравнений в текущем алгоритме сортировки
		*/
		int * GetCurrentMergeCount();
		
		/**
			@short
				Получить кол-во доступов к массиву
			@return
				Указатель на кол-во доступов к массиву в текущем алгоритме сортировки
		*/
		int * GetCurrentAccessCount();
		
		/**
			@short
				Получить мьютекс для доступа к информации о текущем алгоритме сортировки
			@return
				Указатель на мьютекс для доступа к текущему алгоритму сортировки
		*/
		std::mutex * GetCurrentAlgMutex();

		/**
			@short
				Задать имя текущего алгоритма сортировки	
			@param[in] algName - имя текущего алгоритма сортировки
		*/		
		void SetCurrentAlgName(std::string const & algName);

		/**
			@short
				Инкрементировать кол-во доступов к массиву
		*/
		void IncAccessCount();

		/**
		@short
			Инкрементировать кол-во сравнений
		*/
		void IncMergeCount();

		/**
		@short
			Обнулить кол-во доступов к массиву
		*/
		void ResetAccessCount();

		/**
		@short
			Обнулить кол-во сравнений
		*/
		void ResetMergeCount();

	private:
		// Мютекс для доступа к текущему сортируемому элементу
		std::mutex lockElementMutex;
		
		// Текущий сортируемый элемент
		int lockElement;
		
		// Окно для отрисовки изменений
		sf::RenderWindow window;
		
		// Флаг, указывающий на необходимость завершения потока обновления окна
		bool shouldBeCancelled;
		
		// Имя текущего алгоритма сортировки
		std::string currentAlgName;
		
		// Кол-во сравнений в текущем алгоритме сортировки
		int currentMergeCount;
		
		// Кол-во доступов к массиву в текущем алгоритме сортировки
		int currentAccessCount;
		
		// Мьютекс для доступа к текущему алгоритму сортировки
		std::mutex currentAlgMutex;
	};

} // Sort

