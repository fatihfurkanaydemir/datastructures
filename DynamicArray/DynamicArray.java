package DynamicArray;

class DArray <T extends Comparable<T>> {
  private static final int INITIAL_SIZE = 16;
  private static final int RESIZE_FACTOR = 2;

  private int size, capacity;
  private T[] data;

  public DArray() {
    this(INITIAL_SIZE);
  }
  
  public DArray(int capacity) {
    size = 0;
    this.capacity = capacity > 0 ? capacity : INITIAL_SIZE;
    data = (T[])new Comparable[capacity];
  }

  public int getSize() {
    return size;
  }

  public int getCapacity() {
    return capacity;
  }

  public void add(T value) {
    // Resize
    if(size + 1 == capacity) {
      capacity *= RESIZE_FACTOR;
      T[] newData = (T[])new Comparable[capacity];

      for(int i = 0; i < size; ++i) 
        newData[i] = data[i];

      data = newData;
      data[size++] = value;

      newData = null;
    }
    else {
      data[size++] = value;
    }
  }

  public T remove(int index) {
    if(index < 0 || index >= size) throw new IndexOutOfBoundsException();

    T value = data[index];

    for(int i = index + 1; i < size; ++i) {
      data[i - 1] = data[i];
    }

    data[--size] = null;

    return value;
  }

  public T get(int index) {
    if(index < 0 || index >= size) throw new IndexOutOfBoundsException();
    
    return data[index];
  }

  public int indexOf(T value) {
    for(int i = 0; i < size; ++i) {
      if(data[i].equals(value))
        return i;
    }

    return -1;
  }

  public boolean contains(T value) {
    return indexOf(value) != -1;
  }

  @Override
  public String toString() {
    StringBuilder builder = new StringBuilder();
    builder.append("[");
    for(int i = 0; i < size; ++i) 
      builder.append(data[i]).append(" ");
    builder.delete(builder.length() - 1, builder.length()).append("]");

    return builder.toString();
  }
}

public class DynamicArray {
  public static void main(String[] args) {
    DArray<Integer> arr = new DArray<Integer>(2);
    arr.add(5);
    arr.add(3);
    arr.add(7);
    arr.add(512);
    arr.add(55);
    arr.add(124);

    System.out.println(arr);

    System.out.println(arr.indexOf(512));
    arr.remove(arr.indexOf(512));
    System.out.println(arr);
    System.out.println(arr.contains(124));
    System.out.println(arr.getCapacity());
    System.out.println(arr.getSize());
    System.out.println(arr.get(2));
  }
}