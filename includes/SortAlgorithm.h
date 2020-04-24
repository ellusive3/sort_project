#include <stdafx.h>
#include <Graphics.hpp>
#include <AppEnv.h>

/**
	@file
		���� ��� ���������� ������� ����������
	@author
		Zyukov Alexander Vadimovich (ellusive)
	@date
		2020 April 25
*/

namespace Sort {
    /**
	@short
	    ������� ����� ��� �������� ��������� ����������
    */
    class Algorithm {
    public:
	/**
	    @short
		����������� �� ���������
	*/
        Algorithm();
        
        /**
    	    @short
    		����������� � �����������
    	    @param[in] name - ��� ��������� ����������
        */
        Algorithm(std::string const & name);
        
	/**
	    @short
		����������� ������� ���������� �������
	    @param[in] array - ������ �������� ��� ����������
	    @param[in] size - ������ ������� ��������
	*/
	virtual void Sort(sf::RectangleShape ** array, size_t size) = 0;

	/**
	    @short
		�������� ��� ��������� ����������
	    @return ��� ��������� ����������
	*/
	const std::string & GetName() const { return algName; };

	/**
	    @short
		�������� ���-�� ���������
	    @return ���-�� ���������
	*/
	const int GetMergeCount() const { return *environment->GetCurrentMergeCount(); }

	/**
	    @short
		�������� ���-�� �������� � �������
	    @return ���-�� �������� � �������
	*/
	const int GetAccessCount() const { return *environment->GetCurrentAccessCount(); }
    protected:
	// ��������� �� ��������� ����������
	Sort::AppEnv * environment;
	
	/**
	    @short
		����������� �������� ���������� �� ����������
		� �������
	*/
	void PrintFinalInfo();
    private:
	// ��� ��������� ����������
        std::string algName;
    };

    /**
	@short
	    ���������� ������ ���������� ���������
    */
    class BubbleSort : public Algorithm {
    public:
	/**
	    @short
		����������� �� ���������
	*/
	BubbleSort() : Algorithm("Bubble Sort") {};
	
	/**
	    @short
		����������� � �����������
	    @param[in] name - ��� ��������� ����������
	*/
	BubbleSort(std::string const & name) : Algorithm(name) {};

	/**
	    @short
		����������� � ����������� (����������)
	    @param[in] environment - ��������� �� ��������� ����������
	*/
	BubbleSort(Sort::AppEnv * _environment);
	
	/**
	    @short
		���������������� ������� ���������� �������
	    @param[in] array - ��������� �� ������ �������� ��� ����������
	    @param[in] size - ������ ������� ��������
	*/
	virtual void Sort(sf::RectangleShape ** array, size_t size) override final;
    };

    /**
	@short
	    ���������� ������ ��������� ������� ����������
    */
    class QuickSort : public Algorithm {
    public:
	/**
	    @short
		����������� �� ���������
	*/
	QuickSort() : Algorithm("Bubble Sort") {};

	/**
	    @short
		����������� � �����������
	    @param[in] name - ��� ��������� ����������
	*/
	QuickSort(std::string const & name) : Algorithm(name) {};

	/**
	    @short
		����������� � ����������� (����������)
	    @param[in] _environment - ��������� �� ��������� ����������
	*/
	QuickSort(Sort::AppEnv * _environment);

	/**
	    @short
		���������������� ������� ���������� �������
	    @param[in] array - ��������� �� ������ �������� ��� ����������
	    @param[in] size -������ ������� ��������
	*/
	virtual void Sort(sf::RectangleShape ** array, size_t size) override final;
    private:
	/**
	    @short
		���������� ���������� ������� ����������
	    @param[in] array - ��������� �� ������ �������� ��� ����������
	    @param[in] low - ������ ������� ������� ��������
	    @param[in] high - ������� ������� ������� ��������
	*/
	void SortImpl(sf::RectangleShape ** array, size_t low, size_t high);
    };

    /**
	@short
	    ���������� ������ ��������� Shell ����������
    */
    class ShellSort : public Algorithm {
    public:
	/**
	    @short
		����������� �� ���������
	*/
	ShellSort() : Algorithm("Shell Sort") {};

	/**
	    @short
		����������� � �����������
	    @param[in] name - ��� ��������� ����������
	*/
	ShellSort(std::string const & name) : Algorithm(name) {};

	/**
	    @short
		����������� � ����������� (����������)
	    @param[in] _environment - ��������� �� ��������� ����������
	*/
	ShellSort(Sort::AppEnv * _environment);

	/**
	    @short
		���������������� ������� ���������� �������
	    @param[in] array - ��������� �� ������ �������� ��� ����������
	    @param[in] size - ������ ������� ��������
	*/
	virtual void Sort(sf::RectangleShape ** array, size_t size) override final;
    };

    /**
	@short
	    ���������� ������ ��������� Gnome ����������
    */
    class GnomeSort : public Algorithm {
    public:
	/**
	    @short
		����������� �� ���������
	*/
	GnomeSort() : Algorithm("Gnome Sort") {};

	/**
	    @short
		����������� � �����������
	    @param[in] name - ��� ��������� ����������
	*/
	GnomeSort(std::string const & name) : Algorithm(name) {};

	/**
	    @short
		����������� � ����������� (�����������)
	    @param[in] _environment - ��������� �� ��������� ����������
	*/
	GnomeSort(Sort::AppEnv * _environment);

	/**
	    @short
		���������������� ������� ���������� �������
	    @param[in] array - ��������� �� ������ �������� ��� ����������
	    @param[in] size - ������ ������� ��������
	*/
	virtual void Sort(sf::RectangleShape ** array, size_t size) override final;
    };
} // Sort
