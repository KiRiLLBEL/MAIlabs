namespace NMystd {
    
	template<class T>
	void FillN(T* object, size_t size, T value) {
		for (size_t i = 0; i < size; ++i) {
			object[i] = value;
		}
	}

	template<class T>
	class TVector {
	public:

		TVector();

		TVector(size_t size);

		TVector(size_t size, T value);

		TVector(const TVector& arg);

		TVector<T>& operator=(const TVector<T>& arg);

		T& operator [](size_t  index);

		const T& operator [](size_t index) const;

		inline size_t Size() const;

		void Reserve(size_t newmem);

		void Resize(size_t newsize);

		void PushBack(const T& arg);

		~TVector();
	
	private:
		T* arr;

		size_t size;

		size_t mem;

	};

	template<class T>
	TVector<T>::TVector() : size(0), mem(0), arr(nullptr) {

	}

	template<class T>
	TVector<T>::TVector(size_t size) : size(size), mem(size)  {
		arr = new T[size];
	}

	template<class T>
	TVector<T>::TVector(size_t size, T value) {
		this->size = size;
		this->mem = size;
		this->arr = new T[size];
		FillN(arr, size, value);
	}

	template<class T>
	const T& TVector<T>::operator [](size_t index) const {
		return this->arr[index];
	}
	
	template<class T>
	T& TVector<T>::operator [](size_t index) {
		return this->arr[index];
	}

	template<class T>
	size_t TVector<T>::Size() const {
		return this->size;
	}

	template<class T>
	void TVector<T>::Reserve(size_t newmem) {
		if(newmem < this->mem) {
			return;
		}
		
		T* newarr = new T[newmem];
		for(int i = 0; i < this->Size(); ++i) {
			newarr[i] = this->arr[i];
		}
		delete[] arr;
		this->arr = newarr;
		this->mem = newmem;
	}

	template<class T>
	void TVector<T>::Resize(size_t newsize) {
		Reserve(newsize);
		for(int i = this->size; i < newsize; ++i) {
			this->arr = T();
		}

		this->size = newsize;
	}

	template<class T>
	void TVector<T>::PushBack(const T& arg) {
		if(this->mem == 0) {
			this->Reserve(10);
		}
		else if(this->size == this->mem) {
			this->Reserve(this->size * 2);
		}

		this->arr[this->size] = arg;
		++this->size;
	}

	template<class T>
	TVector<T>::~TVector() {
		delete[] arr;
	}

	template<class T>
	TVector<T>::TVector(const TVector& vec) : 
		size(vec.Size()), mem(vec.Size()), arr(new T(vec.Size())) 
	{
		for(int i = 0; i < vec.Size(); ++i) {
			this->arr[i] = vec[i];
		}
	}

	template<class T>
	TVector<T>& TVector<T>::operator=(const TVector<T>& rhs) {
		if(this == &rhs) {
			return *this;
		}

		if(rhs.Size() <= this->Size()) {
			for(int i = 0; i < rhs.Size(); ++i) {
				arr[i] = rhs[i];
			}
			this->size = rhs.Size();
			return *this;
		}

		T* narr = new T(rhs.Size());

		for(int i = 0; i < rhs.Size(); ++i) {
			arr[i] = rhs[i];
		}

		delete[] this->arr;

		this->size = rhs.Size();
		this->mem = rhs.Size();
		this->arr = narr;
		return *this;
	}
}