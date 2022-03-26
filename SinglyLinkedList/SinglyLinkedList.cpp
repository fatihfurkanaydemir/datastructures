#include <iostream>

template <typename T>
struct Node {
    Node<T>* next;
    T data;
};

template <typename T>
class SLinkedList {
  private: 
    Node<T>* head;
    int size;

  public:
    SLinkedList() : size{}, head{nullptr} {}

    ~SLinkedList() {
      if(size == 0) return;

      Node<T>* curNode = head;
      Node<T>* nextNode = curNode->next;

      while(curNode != nullptr) {
        delete curNode;
        curNode = nextNode;
        nextNode = curNode->next;
      }
    }

    int getSize() const {
      return size;
    }

    Node<T>* getHead() const {
      return head;
    }

    void add(int index, T value) {
      if(index < 0 || index > size) throw std::runtime_error("Index out of bounds");

      if(index == 0) {
        addFirst(value);
        return;
      }
      else if(index == size) {
        addLast(value);
        return;
      }

      Node<T>* curNode = head;

      for(int i = 0; i < index - 1; ++i)
        curNode = curNode->next;

      Node<T>* newNode = new Node<T>();
      newNode->data = value;
      newNode->next = curNode->next;
      curNode->next = newNode;

      size++;
    }

    void addFirst(T value) {
      if(head == nullptr) {
        head = new Node<T>();
        head->data = value;
      }
      else {
        Node<T>* newNode = new Node<T>();
        newNode->next = head;
        head = newNode;
        head->data = value;
      }

      size++;
    }

    void addLast(T value) {
      if(head == nullptr) {
        addFirst(value);
      }
      else {
        Node<T>* curNode = head;
        while(curNode->next != nullptr)
          curNode = curNode->next;

        curNode->next = new Node<T>();
        curNode->next->data = value;

        size++;
      }
    }

    bool remove(T value) {
      Node<T>* curNode = head;
      Node<T>* prevNode = curNode;

      while(curNode != nullptr) {
        if(curNode->data == value) {
          if(curNode == head) {
            head = curNode->next;
            delete curNode;

            size--;
            return true;
          }

          Node<T>* nodeToRemove = curNode;

          prevNode->next = nodeToRemove->next;
          delete nodeToRemove;

          size--;
          return true;
        }

        prevNode = curNode;
        curNode = curNode->next;
      }

      return false;
    }

    T removeAt(int index) {
      if(index < 0 || index >= size) throw std::runtime_error("Index out of bounds");

      Node<T>* curNode = head;
      Node<T>* prevNode = curNode;

      for(int i = 0; i < index; i++) {
        prevNode = curNode;
        curNode = curNode->next;
      }

      if(curNode == head) {
        head = head->next;
        T value = head->data;
        delete curNode;

        size--;
        return value;
      }

      Node<T>* nodeToRemove = curNode;
      prevNode->next = curNode->next;

      T value = nodeToRemove->data;
      delete nodeToRemove;

      size--;
      return value;
    }

    int indexOf(T value) const {
      Node<T>* curNode = head;
      int index = 0;

      while(curNode != nullptr) {
        if(curNode->data == value) {
          return index;
        }

        index++;
        curNode = curNode->next;
      }

      return -1;
    }

    T get(int index) const {
      if(index < 0 || index >= size) throw std::runtime_error("Index out of bounds");

      Node<T>* curNode = head;

      for(int i = 0; i < index; i++) 
        curNode = curNode->next;

      return curNode->data;
    }

    void set(int index, T value) {
      if(index < 0 || index >= size) throw std::runtime_error("Index out of bounds");

      Node<T>* curNode = head;

      for(int i = 0; i < index; i++) 
        curNode = curNode->next;

      curNode->data = value;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const SLinkedList<T>& list) {
  Node<T>* curNode = list.getHead();
  while(curNode != nullptr) {
    os << curNode->data << " -> ";
    curNode = curNode->next;
  }
  os << "null";

  return os;
}

int main(int argc, char** argv) {
  SLinkedList<int> list;

  list.addLast(1);
  list.addLast(2);
  list.addLast(3);
  list.addLast(4);
  list.addLast(5);
  list.addLast(6);

  list.add(0, 15);
  list.add(7, 100);
  list.add(3, 70);

  std::cout << list << std::endl;
    
  list.remove(15);
  std::cout << list << std::endl;
    
  std::cout << list.indexOf(1) << std::endl;
  std::cout << list.indexOf(70) << std::endl;
  std::cout << list.indexOf(100) << std::endl;
  std::cout << list.indexOf(1123) << std::endl;
    
  list.removeAt(0);
  std::cout << list << std::endl;
  list.removeAt(6);
  std::cout << list << std::endl;
  list.removeAt(3);
  std::cout << list << std::endl;
    
  std::cout << list.get(0) << std::endl;
  std::cout << list.get(list.getSize() - 1) << std::endl;
  std::cout << list.get(2) << std::endl;
    
  list.set(0, 99);
  list.set(list.getSize() - 1, 90);
  list.set(2, 50);
  std::cout << list << std::endl;
  return 0;
}