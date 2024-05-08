namespace SparkInternal::Utils {

	/*
	* This class is a simple vector that will not delete its data when it goes out of scope.
	* Used in model loading.
	*/
	template <typename T>
	class WeakVector {
	private:
		T* data;
		size_t size;
		size_t capacity;

		void resize(size_t newCapacity) {
			T* newData = new T[newCapacity];
			for (size_t i = 0; i < size; ++i) {
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
			capacity = newCapacity;
		}

		public:
			WeakVector() : data(nullptr), size(0), capacity(0) {
				resize(10);
			}

			T* get_data() {
				return data;
			}

			const size_t get_size() const {
				return size;
			}

			void push_back(const T& value) {
				if (size >= capacity) {
					resize(capacity * 2);
				}
				data[size++] = value;
			}

			void shrink_to_fit() {
				resize(size);
			}
	};
}