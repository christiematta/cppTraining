#ifndef UNIQUE_POINTER_H
#define UNIQUE_POINTER_H

namespace smartpointers{

template<typename T>
class MyUniquePointer
{
public:
	MyUniquePointer(T& t)
	{
		m_pointer = new T(t);
	}

	~MyUniquePointer()
	{
		delete m_pointer;
	}

	MyUniquePointer<T>& operator=(MyUniquePointer<T>&& ptr);

	MyUniquePointer(MyUniquePointer<T>&& ptr);

	T * operator->() const;

	T& operator*() const;

	bool operator!() const;

	T* get() const;

	void reset();

	T & release();
	
	operator bool() const;

private:
	T* m_pointer;
	MyUniquePointer(MyUniquePointer<T>& ptr)=delete;
	MyUniquePointer<T>& operator=(const MyUniquePointer<T>& ptr)=delete;
};

template<typename T>
MyUniquePointer<T> make_unique(T & obj)
{
	return MyUniquePointer<T>(obj);
}


template<typename T, class... Args>
MyUniquePointer<T> make_unique(Args&& ... args)
{
	return MyUniquePointer<T>(T(std::forward<Args>(args) ...));
}

template<typename T>
inline MyUniquePointer<T>& MyUniquePointer<T>::operator=(MyUniquePointer<T>&& ptr)
{
	this->m_pointer = ptr.m_pointer;
	ptr.m_pointer = nullptr;
	return *this;
}

template<typename T>
inline MyUniquePointer<T>::MyUniquePointer(MyUniquePointer<T>&& ptr)
{
	*this = std::move(ptr);
}

template<typename T>
inline T * MyUniquePointer<T>::operator->() const
{
	return m_pointer;
}
template<typename T>
inline T& MyUniquePointer<T>::operator*() const
{
	return *m_pointer;
}
template<typename T>
inline bool MyUniquePointer<T>::operator!() const
{
	return(m_pointer == nullptr);
}

template<typename T>
inline T* MyUniquePointer<T>::get() const
{
	return m_pointer;
}

template<typename T>
inline void MyUniquePointer<T>::reset()
{
	m_pointer = nullptr;
}

template<typename T>
inline T & MyUniquePointer<T>::release()
{	
	T& res = *m_pointer;
	reset();
	return res;
}

template<typename T>
inline MyUniquePointer<T>::operator bool() const
{
	return(!(!(*this)));
}


class Parent
{
public:
	explicit Parent(int x)
		: m_x(x)
	{}
private:
	int m_x;
};



class Child1 : public Parent
{
public:
	Child1()
		: Parent(0)
		, m_s("Default")
	{}

	Child1(const std::string& s)
		: Parent(0)
		, m_s(s)
	{}

	Child1(int x, const std::string& s)
		: Parent(x)
		, m_s(s)
	{}



private:
	std::string m_s;
};



}
#endif