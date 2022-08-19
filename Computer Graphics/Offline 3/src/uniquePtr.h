#ifndef C8F61A1C_0821_4B5B_A0EE_B305B0CBB547
#define C8F61A1C_0821_4B5B_A0EE_B305B0CBB547


template<typename T>
class UniquePtr
{
	T * ptr;
	void __cleanup__()
	{
		if (ptr != nullptr){
			delete ptr;
		}
		ptr=nullptr;
	}
public:
	UniquePtr() = delete;
	UniquePtr(const UniquePtr & ) = delete;
	UniquePtr(T * ptr):ptr(ptr)
	{
	}
	UniquePtr(UniquePtr && dyingObj) // move constructor
	{
		// Transfer ownership of the memory pointed by dyingObj to this object
		this->ptr = dyingObj.ptr;
		dyingObj.ptr = nullptr; 
	}
	void operator=(UniquePtr && dyingObj) // move assignment
	{
		__cleanup__(); // cleanup any existing data

		// Transfer ownership of the memory pointed by dyingObj to this object
		this->ptr = dyingObj.ptr;
		dyingObj.ptr = nullptr;
	}

	T * get() const
	{
		return ptr;
	}
	~UniquePtr()
	{
		__cleanup__();
	}
	UniquePtr & operator=(const UniquePtr & ) = delete;
	T* operator->() const // obtaining pointer using arrow operator
	{
		return this->ptr;
	}
	T& operator*() const // dereferencing underlying pointer
	{
		return *(this->ptr);
	}
};

#endif /* C8F61A1C_0821_4B5B_A0EE_B305B0CBB547 */
