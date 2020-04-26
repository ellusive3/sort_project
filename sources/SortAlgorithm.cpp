#include <stdafx.h>
#include <SortAlgorithm.h>

/**
    @file
	Файл реализации алгоритмов сортировки
    @author
	Zyukov Alexander Vadimovich (ellusive)
    @date
	2020 April 25
*/

namespace Sort {

	Algorithm::Algorithm()
	{ 
	    environment->SetCurrentAlgName("none");
	    environment->ResetAccessCount();
	    environment->ResetMergeCount();
	}

	Algorithm::Algorithm(std::string const & name)
	{
	    algName = name;
	}

	void Algorithm::PrintFinalInfo()
	{
	    printf("\n**********\n");
	    printf("Sort algorithm name: %s\n", GetName().c_str());
	    printf("Merges count: %d\n", GetMergeCount());
	    printf("Accesses count: %d\n", GetAccessCount());
	    printf("\n**********\n");
	}

	BubbleSort::BubbleSort(Sort::AppEnv * _environment) :
		Algorithm("Bubble Sort")
	{
	    assert(_environment != nullptr);
	    this->environment = _environment;
	    environment->SetCurrentAlgName("Bubble Sort");
	    environment->ResetAccessCount();
	    environment->ResetMergeCount();
	}

	void BubbleSort::Sort(sf::RectangleShape ** array, size_t size)
	{
		environment->ResetMergeCount();
		environment->ResetAccessCount();
		environment->SetCurrentAlgName(this->GetName());
		for (size_t i = 0; i < size - 1; i++) {
			for (size_t j = 0; j < size - i - 1; j++) {
				environment->IncMergeCount();
				assert(environment->GetLockElementMutex() != nullptr);
				assert(environment->GetLockElement() != nullptr);
				if ((int)array[j]->getSize().y < (int)array[j + 1]->getSize().y) {
					sf::RectangleShape tmp = *array[j];
					{
						std::lock_guard<std::mutex> lock(*environment->GetLockElementMutex());
						*environment->GetLockElement() = array[j]->getPosition().x;
					}
					array[j]->setSize(sf::Vector2f(1, array[j + 1]->getSize().y));
					array[j + 1]->setSize(sf::Vector2f(1, tmp.getSize().y));
					environment->IncAccessCount();
					{
						std::lock_guard<std::mutex> lock(*environment->GetLockElementMutex());
						*environment->GetLockElement() = -1;
					}
				}
				std::this_thread::sleep_for(std::chrono::nanoseconds(100));
			}
		}
		this->PrintFinalInfo();
	}

	QuickSort::QuickSort(Sort::AppEnv * _environment) :
		Algorithm("Quick Sort")
	{
	    assert(_environment != nullptr);
	    this->environment = _environment;
	    environment->SetCurrentAlgName("Quick Sort");
	    environment->ResetAccessCount();
	    environment->ResetMergeCount();
	}

	void QuickSort::Sort(sf::RectangleShape ** array, size_t size)
	{
	    environment->ResetMergeCount();
	    environment->ResetAccessCount();
	    environment->SetCurrentAlgName(this->GetName());
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

			environment->IncMergeCount();
			if (i <= j) {
				{
					std::lock_guard<std::mutex> lock(*environment->GetLockElementMutex());
					*environment->GetLockElement() = array[j]->getPosition().x;
				}
				sf::RectangleShape tmp = *array[i];
				array[i]->setSize(sf::Vector2f(1, array[j]->getSize().y));
				array[j]->setSize(sf::Vector2f(1, tmp.getSize().y));
				i++;
				j--;
				environment->IncAccessCount();
				{
					std::lock_guard<std::mutex> lock(*environment->GetLockElementMutex());
					*environment->GetLockElement() = -1;
				}
			}
			std::this_thread::sleep_for(std::chrono::nanoseconds(50));
			if (j > low)
				SortImpl(array, low, j);
			if (i < high)
				SortImpl(array, i, high);
		}
	}

	ShellSort::ShellSort(Sort::AppEnv * _environment) :
		Algorithm("Shell Sort")
	{
	    assert(_environment != nullptr);
	    this->environment = _environment;
	    environment->SetCurrentAlgName("Shell Sort");
	    environment->ResetAccessCount();
	    environment->ResetMergeCount();
	}

	void ShellSort::Sort(sf::RectangleShape ** array, size_t size)
	{
		environment->ResetMergeCount();
		environment->ResetAccessCount();
		environment->SetCurrentAlgName(this->GetName());
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
					environment->IncMergeCount();
					{
						std::lock_guard<std::mutex> lock(*environment->GetLockElementMutex());
						*environment->GetLockElement() = array[j]->getPosition().x;
					}
					environment->IncAccessCount();
					array[j]->setSize(sf::Vector2f(array[j]->getSize().x, array[j - gap]->getSize().y));
					std::this_thread::sleep_for(std::chrono::nanoseconds(1000000));
					{
						std::lock_guard<std::mutex> lock(*environment->GetLockElementMutex());
						*environment->GetLockElement() = -1;
					}
				}

				//  put temp (the original a[i]) in its correct location 
				array[j]->setSize(sf::Vector2f(array[j]->getSize().x, temp.getSize().y));
			}
		}
		this->PrintFinalInfo();
	}

	GnomeSort::GnomeSort(Sort::AppEnv * _environment) :
		Algorithm("Gnome Sort")
	{
	    assert(_environment != nullptr);
	    this->environment = _environment;
	    environment->SetCurrentAlgName("Gnome Sort");
	    environment->ResetAccessCount();
	    environment->ResetMergeCount();
	}

	void GnomeSort::Sort(sf::RectangleShape ** array, size_t size)
	{
		environment->ResetMergeCount();
		environment->ResetAccessCount();
		environment->SetCurrentAlgName(this->GetName());
		int index = 0;

		while (index < size) {
			if (index == 0)
				index++;
			environment->IncMergeCount();
			if (array[index]->getSize().y <= array[index - 1]->getSize().y)
				index++;
			else {
				environment->IncAccessCount();
				sf::RectangleShape tmp = *array[index];
				{
					std::lock_guard<std::mutex> lock(*environment->GetLockElementMutex());
					*environment->GetLockElement() = array[index]->getPosition().x;
				}
				array[index]->setSize(sf::Vector2f(1, array[index - 1]->getSize().y));
				array[index - 1]->setSize(sf::Vector2f(1, tmp.getSize().y));
				environment->IncAccessCount();
				{
					std::lock_guard<std::mutex> lock(*environment->GetLockElementMutex());
					*environment->GetLockElement() = -1;
				}

				index--;
				std::this_thread::sleep_for(std::chrono::nanoseconds(100000));
			}
		}
		this->PrintFinalInfo();
	}
	
	InsertionSort::InsertionSort(Sort::AppEnv * _environment) :
	    Algorithm("Insertion Sort")
	{
	    assert(_environment != nullptr);
	    this->environment = _environment;
	    environment->SetCurrentAlgName("Insertion Sort");
	    environment->ResetMergeCount();
	    environment->ResetAccessCount();
	}
	
	void InsertionSort::Sort(sf::RectangleShape ** array, size_t size)
	{
	    environment->SetCurrentAlgName(this->GetName());
	    environment->ResetMergeCount();
	    environment->ResetAccessCount();
	    int key, j;
	    for (int i = 1; i < size; i++) {
		environment->IncAccessCount();
		key = array[i]->getSize().y;
		j = i - 1;
		environment->IncAccessCount();
		environment->IncMergeCount();
		while (j >= 0 && array[j]->getSize().y < key) {
		    environment->IncAccessCount();
		    array[j + 1]->setSize(sf::Vector2f(array[j + 1]->getSize().x, array[j]->getSize().y));
		    j--;
		}
		environment->IncAccessCount();
		array[j + 1]->setSize(sf::Vector2f(array[j + 1]->getSize().x, key));
		std::this_thread::sleep_for(std::chrono::nanoseconds(10000));
	    }
	    this->PrintFinalInfo();
	}

} // Sort
