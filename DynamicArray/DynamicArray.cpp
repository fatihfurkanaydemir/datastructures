#include <iostream>

template<typename T>
class DArray {
  private:
    static const int INITIAL_SIZE = 16;
    static const int RESIZE_FACTOR = 2;

    int size, capacity;
    T* data;

  public:
    DArray() : DArray(INITIAL_SIZE) { }

    DArray(int capacity) : size{0} {
      this->capacity = capacity > 0 ? capacity : INITIAL_SIZE;
      data = new T[capacity];
    }

    DArray(const DArray<T>& other) {
      capacity = other.capacity;
      size = other.size;
      data = new T[capacity];

      for(int i = 0; i < size; ++i) 
        data[i] = other.data[i];
    }

    DArray(const DArray<T>&& other) {      
      capacity = other.capacity;
      size = other.size;
      data = other.data;

      other.data = nullptr;
    }

    DArray<T>& operator=(const DArray<T>& other) {
      if(*this == other) return *this;

      capacity = other.capacity;
      size = other.size;

      delete[] data;
      data = new T[capacity];

      for(int i = 0; i < size; ++i) 
        data[i] = other.data[i];

      return *this;
    }

    DArray<T>& operator=(const DArray<T>&& other) {
      if(*this == other) return *this;

      capacity = other.capacity;
      size = other.size;
      data = other.data;

      other.data = nullptr;
    }

    ~DArray() {
      delete[] data;
    }

    int getSize() const {
      return size;
    }

    int getCapacity() const {
      return capacity;
    }

    void add(T value) {
      // Resize
      if(size + 1 == capacity) {
        capacity *= RESIZE_FACTOR;
        T* newData = new T[capacity];

        for(int i = 0; i < size; ++i) 
          newData[i] = data[i];

        delete[] data;

        data = newData;
        data[size++] = value;
      }
      else {
        data[size++] = value;
      }
    }

    T remove(int index) {
      if(index < 0 || index >= size) throw std::runtime_error("Index out of bounds");

      T value = data[index];

      for(int i = index + 1; i < size; ++i) {
        data[i - 1] = data[i];
      }

      data[--size] = 0;

      return value;
    }

    T get(int index) const {
      if(index < 0 || index >= size) throw std::runtime_error("Index out of bounds");

      return data[index];
    }

    int indexOf(T value) const {
      for(int i = 0; i < size; ++i) {
        if(data[i] == value)
          return i;
      }

      return -1;
    }

    bool contains(T value) const {
      return indexOf(value) != -1;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const DArray<T>& arr) {
  os << "[";

  for(int i = 0; i < arr.getSize(); ++i) 
    os << arr.get(i) << " ";

  os << "]";

  return os;
}


int main(int argc, char** argv) {
  DArray<int> arr(2);

  arr.add(5);
  arr.add(3);
  arr.add(7);
  arr.add(512);
  arr.add(55);
  arr.add(124);

  std::cout << arr << std::endl;
  std::cout << arr.indexOf(512) << std::endl;

  arr.remove(arr.indexOf(512));

  std::cout << arr << std::endl;
  std::cout << arr.contains(124) << std::endl;
  std::cout << arr.getCapacity() << std::endl;
  std::cout << arr.getSize() << std::endl;
  std::cout << "------------" << std::endl;

  DArray<int> arr2 = arr;
  arr2.add(1024);
  std::cout << arr << std::endl;
  std::cout << arr2 << std::endl;
}