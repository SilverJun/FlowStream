#pragma once

#include <memory>
#include <mutex>

template <typename T>
class CSingleton
{
public:
	static T* GetInstance()
	{
		call_once(m_onceFlag, [] 
			{
				m_pInstance.reset(new T);
			}
		);
		return m_pInstance.get();
	}

private:
	static std::shared_ptr<T> CSingleton<T>::m_pInstance;
	static std::once_flag m_onceFlag;
};

template <typename T> std::shared_ptr<T> CSingleton<T>::m_pInstance = nullptr;

template <typename T> std::once_flag CSingleton<T>::m_onceFlag;
