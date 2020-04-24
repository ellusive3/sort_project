#include <stdafx.h>
#include <Graphics.hpp>

namespace Sort {

    class Algorithm {
    public:
        Algorithm();
        Algorithm(std::string const & name);
		virtual void Sort(sf::RectangleShape ** array, size_t size) = 0;
		const std::string & GetName() const { return algName; };
		const int GetMergeCount() const { return mergeCount; }
		const int GetAccessCount() const { return accessCount; }
	protected:
        int mergeCount;
        int accessCount;
		std::mutex * lock;
		int * lockElement;
		void PrintFinalInfo();
    private:
        std::string algName;
    };

	class BubbleSort : public Algorithm {
	public:
		BubbleSort() : Algorithm("Bubble Sort") {};
		BubbleSort(std::string const & name) : Algorithm(name) {};
		BubbleSort(std::mutex * _lock, int * _lockElement);
		virtual void Sort(sf::RectangleShape ** array, size_t size) override final;
	};

	class QuickSort : public Algorithm {
	public:
		QuickSort() : Algorithm("Bubble Sort") {};
		QuickSort(std::string const & name) : Algorithm(name) {};
		QuickSort(std::mutex * _lock, int * _lockElement);
		virtual void Sort(sf::RectangleShape ** array, size_t size) override final;
	private:
		void SortImpl(sf::RectangleShape ** array, size_t low, size_t high);
	};

	class ShellSort : public Algorithm {
	public:
		ShellSort() : Algorithm("Shell Sort") {};
		ShellSort(std::string const & name) : Algorithm(name) {};
		ShellSort(std::mutex * _lock, int * _lockElement);
		virtual void Sort(sf::RectangleShape ** array, size_t size) override final;
	};

	class GnomeSort : public Algorithm {
	public:
		GnomeSort() : Algorithm("Gnome Sort") {};
		GnomeSort(std::string const & name) : Algorithm(name) {};
		GnomeSort(std::mutex * _lock, int * _lockElement);
		virtual void Sort(sf::RectangleShape ** array, size_t size) override final;
	};

} // Sort
