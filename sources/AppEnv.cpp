#include <AppEnv.h>

/**
	@file
		Файл для реализации функций класса окружения
	@author
		Zyukov Alexander Vadimovich (ellusive)
	@date
		2020 April 24
*/

namespace Sort {

	AppEnv::AppEnv(const uint32_t windowWidth, const uint32_t windowHeight) :
		window(sf::VideoMode(windowWidth, windowHeight), "Sort window", sf::Style::Close)
	{
		lockElement = -1;
		shouldBeCancelled = false;
		currentAccessCount = 0;
		currentMergeCount = 0;
		currentAlgName = "";
	}

	std::mutex * AppEnv::GetLockElementMutex()
	{ return &lockElementMutex; }

	int * AppEnv::GetLockElement()
	{ return &lockElement; }

	sf::RenderWindow * AppEnv::GetWindow()
	{ return &window; }

	bool * AppEnv::GetCancelled()
	{ return &shouldBeCancelled; }

	std::string & AppEnv::GetCurrentAlgName()
	{ return currentAlgName; }

	int * AppEnv::GetCurrentMergeCount()
	{ return &currentMergeCount; }

	int * AppEnv::GetCurrentAccessCount()
	{ return &currentAccessCount; }

	std::mutex * AppEnv::GetCurrentAlgMutex()
	{ return &currentAlgMutex; }

	void AppEnv::SetCurrentAlgName(std::string const & algName)
	{ 
		std::lock_guard< std::mutex > lock(currentAlgMutex);
		currentAlgName = algName;
	}

	void AppEnv::IncAccessCount()
	{
		std::lock_guard< std::mutex > lock(currentAlgMutex);
		currentAccessCount++;
	}

	void AppEnv::IncMergeCount()
	{
		std::lock_guard< std::mutex > lock(currentAlgMutex);
		currentMergeCount++;
	}

	void AppEnv::ResetAccessCount()
	{
		std::lock_guard< std::mutex > lock(currentAlgMutex);
		currentAccessCount = 0;
	}

	void AppEnv::ResetMergeCount()
	{
		std::lock_guard< std::mutex > lock(currentAlgMutex);
		currentMergeCount = 0;
	}

} // Sort