#ifndef SHARED_POINTER_H
#define SHARED_POINTER_H

namespace smartpointers {

template<typename T>
class MySharedPointer
{
public:
	MySharedPointer(T* t)
		: m_pointer(t),
		m_counter(new int(1))
	{
	}

	MySharedPointer()
		: m_pointer(nullptr),
		m_counter(nullptr)
	{
	}

	MySharedPointer(const MySharedPointer& t)
		:m_pointer(t.m_pointer),
		m_counter(t.m_counter)
	{
		if (m_counter != nullptr)
		{
			(*m_counter)++;
			
		}
		
		
	}

	~MySharedPointer()
	{
		if (m_counter!=nullptr && *m_counter == 1)
		{
			delete m_pointer;
			(*m_counter)--;
		}
	}

	MySharedPointer<T>& operator=(MySharedPointer<T>&& ptr);

	MySharedPointer(MySharedPointer<T>&& ptr);

	T* operator->() const;

	T& operator*() const;

	T* get() const;

	void reset();

	T* release();

	operator bool() const;

	MySharedPointer<T>& operator=(const MySharedPointer<T>& ptr);

	void getCounter() const;

private:
	T* m_pointer;
	int* m_counter;

};

template<typename T>
inline T* MySharedPointer<T>::operator->() const
{
	return m_pointer;
}

template<typename T>
inline T& MySharedPointer<T>::operator*() const
{
	return *m_pointer;
}


template<typename T>
inline T* MySharedPointer<T>::get() const
{
	return m_pointer;
}

template<typename T>
inline void MySharedPointer<T>::reset()
{
	delete m_pointer;
	m_pointer = nullptr;
}

template<typename T>
inline T* MySharedPointer<T>::release()
{
	T* res = m_pointer;
	m_pointer = nullptr;
	return res;
}

template<typename T>
inline MySharedPointer<T>::operator bool() const
{
	return(m_pointer != nullptr);
}

template<typename T>
inline MySharedPointer<T>& MySharedPointer<T>::operator=(const MySharedPointer<T>& ptr)
{
	m_pointer = ptr.m_pointer;
	return *this;
}

template<typename T>
inline void MySharedPointer<T>::getCounter() const
{
	std::cout << " Le counter est :" << *(m_counter) << std::endl;
}


template<typename T>
inline MySharedPointer<T>& MySharedPointer<T>::operator=(MySharedPointer<T>&& ptr)
{
	this->m_pointer = ptr.m_pointer;
	this->m_counter = ptr.m_counter;
	ptr.m_pointer = nullptr;
	return *this;
}

template<typename T>
inline MySharedPointer<T>::MySharedPointer(MySharedPointer<T>&& ptr)
{
	*this = std::move(ptr);
}

template<typename T>
MySharedPointer<T> make_shared(T& obj)
{
	return MySharedPointer<T>(new T(obj));
}


template<typename T, class... Args>
MySharedPointer<T> make_shared(Args&& ... args)
{
	return MySharedPointer<T>(new T(std::forward<Args>(args) ...));
}

}

#endif