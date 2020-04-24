#include <stdafx.h>
/**
	@file
		���� ���������� ������ � ������� ������ ���������.
		����� ��������� ��������� ��� ������� � ���������-������������ ���������� �����
		��������
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
				����������� � �����������
			@param[in] windowWidth - ������ ����
			@param[in] windowHeight - ������ ����
		*/
		AppEnv(const uint32_t windowWidth, const uint32_t windowHeight);

		/**
			@short
				�������� ������� ��� ������� � �������� ������������ ��������
			@return 
				��������� �� ������� ��� ������� � �������� ������������ ��������
		*/
		std::mutex * GetLockElementMutex();

		/**
			@short
				�������� ������� ����������� �������
			@return
				��������� �� ������� ����������� �������
		*/
		int * GetLockElement();

		/**
			@short
				�������� ���� ��� ���������
			@return
				��������� �� ���� ��� ����������
		*/
		sf::RenderWindow * GetWindow();
		
		/**
			@short
				�������� ���� ���������� ������ ���������
			@return
				��������� ����, ����������� �� ������������� ���������� ������ ���������
				����
		*/
		bool * GetCancelled();
		
		/**
			@short
				�������� ������� ������������ ���������
			@return
				������ �� ������������ �������� ��������� ����������
		*/
		std::string & GetCurrentAlgName();
		
		/**
			@short
				�������� ���-�� ���������
			@return
				��������� �� ���-�� ��������� � ������� ��������� ����������
		*/
		int * GetCurrentMergeCount();
		
		/**
			@short
				�������� ���-�� �������� � �������
			@return
				��������� �� ���-�� �������� � ������� � ������� ��������� ����������
		*/
		int * GetCurrentAccessCount();
		
		/**
			@short
				�������� ������� ��� ������� � ���������� � ������� ��������� ����������
			@return
				��������� �� ������� ��� ������� � �������� ��������� ����������
		*/
		std::mutex * GetCurrentAlgMutex();

		/**
			@short
				������ ��� �������� ��������� ����������	
			@param[in] algName - ��� �������� ��������� ����������
		*/		
		void SetCurrentAlgName(std::string const & algName);

		/**
			@short
				���������������� ���-�� �������� � �������
		*/
		void IncAccessCount();

		/**
		@short
			���������������� ���-�� ���������
		*/
		void IncMergeCount();

		/**
		@short
			�������� ���-�� �������� � �������
		*/
		void ResetAccessCount();

		/**
		@short
			�������� ���-�� ���������
		*/
		void ResetMergeCount();

	private:
		// ������ ��� ������� � �������� ������������ ��������
		std::mutex lockElementMutex;
		
		// ������� ����������� �������
		int lockElement;
		
		// ���� ��� ��������� ���������
		sf::RenderWindow window;
		
		// ����, ����������� �� ������������� ���������� ������ ���������� ����
		bool shouldBeCancelled;
		
		// ��� �������� ��������� ����������
		std::string currentAlgName;
		
		// ���-�� ��������� � ������� ��������� ����������
		int currentMergeCount;
		
		// ���-�� �������� � ������� � ������� ��������� ����������
		int currentAccessCount;
		
		// ������� ��� ������� � �������� ��������� ����������
		std::mutex currentAlgMutex;
	};

} // Sort

