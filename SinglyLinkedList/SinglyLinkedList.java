package SinglyLinkedList;

class SLinkedList <T extends Comparable<T>> {
  public class Node {
    public Node next;
    public T data;
  }

  private Node head;
  private int size;

  public SLinkedList() {
    size = 0;
    head = null;
  }

  public int getSize() {
    return size;
  }

  public Node getHead() {
    return head;
  }

  public void add(int index, T value) {
    if(index < 0 || index > size) throw new IndexOutOfBoundsException();

    if(index == 0) {
      addFirst(value);
      return;
    }
    else if(index == size) {
      addLast(value);
      return;
    }

    Node curNode = head;

    for(int i = 0; i < index - 1; ++i)
      curNode = curNode.next;
    
    Node newNode = new Node();
    newNode.data = value;
    newNode.next = curNode.next;
    curNode.next = newNode;
   
    size++;
  }

  public void addFirst(T value) {
    if(head == null) {
      head = new Node();
      head.data = value;
    }
    else {
      Node newNode = new Node();
      newNode.next = head;
      head = newNode;
      head.data = value;
    }

    size++;
  }

  public void addLast(T value) {
    if(head == null) {
      addFirst(value);
    }
    else {
      Node curNode = head;
      while(curNode.next != null)
        curNode = curNode.next;
      
      curNode.next = new Node();
      curNode.next.data = value;

      size++;
    }
  }

  public boolean remove(T value) {
    Node curNode = head;
    Node prevNode = curNode;

    while(curNode != null) {
      if(curNode.data.equals(value)) {
        if(curNode == head) {
          head = curNode.next;
          curNode = null;

          size--;
          return true;
        }

        Node nodeToRemove = curNode;

        prevNode.next = nodeToRemove.next;
        nodeToRemove = null;

        size--;
        return true;
      }

      prevNode = curNode;
      curNode = curNode.next;
    }

    return false;
  }

  public T removeAt(int index) {
    if(index < 0 || index >= size) throw new IndexOutOfBoundsException();

    Node curNode = head;
    Node prevNode = curNode;
    for(int i = 0; i < index; i++) {
      prevNode = curNode;
      curNode = curNode.next;
    }

    if(curNode == head) {
      head = head.next;
      T value = head.data;
      curNode = null;

      size--;
      return value;
    }
      
    Node nodeToRemove = curNode;
    prevNode.next = curNode.next;

    T value = nodeToRemove.data;
    nodeToRemove = null;

    size--;
    return value;
  }

  public int indexOf(T value) {
    Node curNode = head;
    int index = 0;

    while(curNode != null) {
      if(curNode.data.equals(value)) {
        return index;
      }

      index++;
      curNode = curNode.next;
    }

    return -1;
  }

  public T get(int index) {
    if(index < 0 || index >= size) throw new IndexOutOfBoundsException();

    Node curNode = head;

    for(int i = 0; i < index; i++) 
      curNode = curNode.next;
      
    return curNode.data;
  }

  public void set(int index, T value) {
    if(index < 0 || index >= size) throw new IndexOutOfBoundsException();

    Node curNode = head;

    for(int i = 0; i < index; i++) 
      curNode = curNode.next;
      
    curNode.data = value;
  }

  @Override
  public String toString() {
    Node curNode = head;
    StringBuilder builder = new StringBuilder();

    while(curNode != null) {
      builder.append(curNode.data + " -> ");
      curNode = curNode.next;
    }

    return builder.delete(builder.length() - 4, builder.length()).toString();
  }
}

public class SinglyLinkedList {
  public static void main(String[] args) {
    SLinkedList<Integer> list = new SLinkedList<Integer>();
    list.addLast(1);
    list.addLast(2);
    list.addLast(3);
    list.addLast(4);
    list.addLast(5);
    list.addLast(6);

    list.add(0, 15);
    list.add(7, 100);
    list.add(3, 70);

    System.out.println(list);
    
    list.remove(15);
    System.out.println(list);
    
    System.out.println(list.indexOf(1));
    System.out.println(list.indexOf(70));
    System.out.println(list.indexOf(100));
    System.out.println(list.indexOf(1123));
    
    list.removeAt(0);
    System.out.println(list);
    list.removeAt(6);
    System.out.println(list);
    list.removeAt(3);
    System.out.println(list);
    
    System.out.println(list.get(0));
    System.out.println(list.get(list.getSize() - 1));
    System.out.println(list.get(2));
    
    list.set(0, 99);
    list.set(list.getSize() - 1, 90);
    list.set(2, 50);
    System.out.println(list);
  }
}
