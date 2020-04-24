#include <stdafx.h>
#include <Graphics.hpp>
#include <AppEnv.h>

namespace Sort {

    class Algorithm {
    public:
        Algorithm();
        Algorithm(std::string const & name);
		Algorithm(Sort::AppEnv * _environment);
		virtual void Sort(sf::RectangleShape ** array, size_t size) = 0;
		const std::string & GetName() const { return algName; };
		const int GetMergeCount() const { return *environment->GetCurrentMergeCount(); }
		const int GetAccessCount() const { return *environment->GetCurrentAccessCount(); }
	protected:
		Sort::AppEnv * environment;
		void PrintFinalInfo();
    private:
        std::string algName;
    };

	class BubbleSort : public Algorithm {
	public:
		BubbleSort() : Algorithm("Bubble Sort") {};
		BubbleSort(std::string const & name) : Algorithm(name) {};
		BubbleSort(Sort::AppEnv * _environment);
		virtual void Sort(sf::RectangleShape ** array, size_t size) override final;
	};

	class QuickSort : public Algorithm {
	public:
		QuickSort() : Algorithm("Bubble Sort") {};
		QuickSort(std::string const & name) : Algorithm(name) {};
		QuickSort(Sort::AppEnv * _environment);
		virtual void Sort(sf::RectangleShape ** array, size_t size) override final;
	private:
		void SortImpl(sf::RectangleShape ** array, size_t low, size_t high);
	};

	class ShellSort : public Algorithm {
	public:
		ShellSort() : Algorithm("Shell Sort") {};
		ShellSort(std::string const & name) : Algorithm(name) {};
		ShellSort(Sort::AppEnv * _environment);
		virtual void Sort(sf::RectangleShape ** array, size_t size) override final;
	};

	class GnomeSort : public Algorithm {
	public:
		GnomeSort() : Algorithm("Gnome Sort") {};
		GnomeSort(std::string const & name) : Algorithm(name) {};
		GnomeSort(Sort::AppEnv * _environment);
		virtual void Sort(sf::RectangleShape ** array, size_t size) override final;
	};

} // Sort
