#include <stdafx.h>
#include <SortAlgorithm.h>

namespace Sort {

	Algorithm::Algorithm() :
		algName("none"),
		mergeCount(0),
		accessCount(0)
	{ }

	Algorithm::Algorithm(std::string const & name) :
		algName(name),
		mergeCount(0),
		accessCount(0)
	{ }

	void Algorithm::PrintFinalInfo()
	{
		printf("\n**********\n");
		printf("Sort algorithm name: %s\n", GetName().c_str());
		printf("Merges count: %d\n", GetMergeCount());
		printf("Accesses count: %d\n", GetAccessCount());
		printf("\n**********\n");
	}

	BubbleSort::BubbleSort(std::mutex * _lock, int * _lockElement) :
		Algorithm("Bubble Sort")
	{
		this->lock = _lock;
		this->lockElement = _lockElement;
	}

	void BubbleSort::Sort(sf::RectangleShape ** array, size_t size)
	{
		for (size_t i = 0; i < size - 1; i++) {
			for (size_t j = 0; j < size - i - 1; j++) {
				mergeCount++;
				assert(lock != nullptr);
				assert(lockElement != nullptr);
				if ((int)array[j]->getSize().y < (int)array[j + 1]->getSize().y) {
					sf::RectangleShape tmp = *array[j];
					{
						std::lock_guard<std::mutex> lock(*this->lock);
						*this->lockElement = array[j]->getPosition().x;
					}
					array[j]->setSize(sf::Vector2f(1, array[j + 1]->getSize().y));
					array[j + 1]->setSize(sf::Vector2f(1, tmp.getSize().y));
					accessCount++;
					{
						std::lock_guard<std::mutex> lock(*this->lock);
						*this->lockElement = -1;
					}
				}
				std::this_thread::sleep_for(std::chrono::nanoseconds(100));
			}
		}
		this->PrintFinalInfo();
	}

	QuickSort::QuickSort(std::mutex * _lock, int * _lockElement) :
		Algorithm("Quick Sort")
	{
		this->lock = _lock;
		this->lockElement = _lockElement;
	}

	void QuickSort::Sort(sf::RectangleShape ** array, size_t size)
	{
		SortImpl(array, 0, size - 1);
		this->PrintFinalInfo();
	}

	void QuickSort::SortImpl(sf::RectangleShape ** array, size_t low, size_t high)
	{
		int i = low;
		int j = high;
		int partition = (int)array[(i + j) / 2]->getSize().y;
		while (i <= j) {
			while ((int)array[i]->getSize().y > partition)
				i++;
			while ((int)array[j]->getSize().y < partition)
				j--;

			mergeCount++;
			if (i <= j) {
				{
					std::lock_guard<std::mutex> lock(*this->lock);
					*this->lockElement = array[j]->getPosition().x;
				}
				sf::RectangleShape tmp = *array[i];
				array[i]->setSize(sf::Vector2f(1, array[j]->getSize().y));
				array[j]->setSize(sf::Vector2f(1, tmp.getSize().y));
				i++;
				j--;
				accessCount++;
				{
					std::lock_guard<std::mutex> lock(*this->lock);
					*this->lockElement = -1;
				}
			}
			std::this_thread::sleep_for(std::chrono::nanoseconds(50));
			if (j > low)
				SortImpl(array, low, j);
			if (i < high)
				SortImpl(array, i, high);
		}
	}

	ShellSort::ShellSort(std::mutex * _lock, int * _lockElement) :
		Algorithm("Shell Sort")
	{
		this->lock = _lock;
		this->lockElement = _lockElement;
	}

	void ShellSort::Sort(sf::RectangleShape ** array, size_t size)
	{
		// Start with a big gap, then reduce the gap 
		for (int gap = size / 2; gap > 0; gap /= 2)
		{
			// Do a gapped insertion sort for this gap size. 
			// The first gap elements a[0..gap-1] are already in gapped order 
			// keep adding one more element until the entire array is 
			// gap sorted  
			for (int i = gap; i < size; i++)
			{
				// add a[i] to the elements that have been gap sorted 
				// save a[i] in temp and make a hole at position i 
				sf::RectangleShape temp = *array[i];

				// shift earlier gap-sorted elements up until the correct  
				// location for a[i] is found 
				int j;
				for (j = i; j >= gap && array[j - gap]->getSize().y < temp.getSize().y; j -= gap) {
					mergeCount++;
					{
						std::lock_guard<std::mutex> lock(*this->lock);
						*this->lockElement = array[j]->getPosition().x;
					}
					accessCount++;
					array[j]->setSize(sf::Vector2f(array[j]->getSize().x, array[j - gap]->getSize().y));
					std::this_thread::sleep_for(std::chrono::nanoseconds(1000000));
					{
						std::lock_guard<std::mutex> lock(*this->lock);
						*this->lockElement = -1;
					}
				}

				//  put temp (the original a[i]) in its correct location 
				array[j]->setSize(sf::Vector2f(array[j]->getSize().x, temp.getSize().y));
			}
		}
		this->PrintFinalInfo();
	}

	GnomeSort::GnomeSort(std::mutex * _lock, int * _lockElement) :
		Algorithm("Gnome Sort")
	{
		this->lock = _lock;
		this->lockElement = _lockElement;
	}

	void GnomeSort::Sort(sf::RectangleShape ** array, size_t size)
	{
		int index = 0;

		while (index < size) {
			if (index == 0)
				index++;
			mergeCount++;
			if (array[index]->getSize().y <= array[index - 1]->getSize().y)
				index++;
			else {
				accessCount++;
				sf::RectangleShape tmp = *array[index];
				{
					std::lock_guard<std::mutex> lock(*this->lock);
					*this->lockElement = array[index]->getPosition().x;
				}
				array[index]->setSize(sf::Vector2f(1, array[index - 1]->getSize().y));
				array[index - 1]->setSize(sf::Vector2f(1, tmp.getSize().y));
				accessCount++;
				{
					std::lock_guard<std::mutex> lock(*this->lock);
					*this->lockElement = -1;
				}

				index--;
				std::this_thread::sleep_for(std::chrono::nanoseconds(100000));
			}
		}
		this->PrintFinalInfo();
	}

} // Sort
