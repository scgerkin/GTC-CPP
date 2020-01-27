#include "List.h"

/**
 * Default constructor.
 * Initializes the pointers for the list as null.
 */
List::List() {
    head = nullptr;
    tail = nullptr;
}

/**
 * Destructor deletes all Nodes and frees the memory used by the list.
 */
List::~List() {
    Node * traveller = this->head;
    Node * keeper = nullptr;

    while (traveller) {
        keeper = traveller->next;
        delete traveller;
        traveller = keeper;
    }
}

/**
 * Adds a new node to the beginning of the list.
 * If the list is empty, this will initialize a new list with the data.
 * @param data The data we wish to put into the list.
 */
void List::prepend(const char data) {
    if (isEmpty()) {
        head = new Node(data);
        tail = head;
    }
    else {
        Node * temp = head;
        head = new Node(data);
        temp->prev = head;
        head->next = temp;
    }
}

/**
 * Inserts data into the list at a specific position in the list.
 * @param pos The position in the list where we want to insert an element.
 * @param data The data we wish to insert.
 * @throws InvalidPosition if the pos argument greater than the total size
 *         of the list or is less than 0.
 */
void List::insert(int pos, const char data) {
    int listSize = size();
    if (pos > listSize || pos < 0) {
        throw InvalidPosition(pos);
    }

    if (pos == listSize) {
        append(data);
        return;
    }

    if (pos == 0) {
        prepend(data);
        return;
    }

    // move to position
    int i = 0;
    Node * temp = nullptr;
    if (pos > size()/2) { // start from tail if closer
        temp = tail;
        while (i >= pos) {
            temp = temp->prev;
            i--;
        }


    }
    else { // start from head if tail is not closer to pos
        temp = head;
        while (i < pos) {
            temp = temp->next;
            i++;
        }
    }
    // insert new element and update pointers
    temp->prev->next = new Node(data);
    temp->prev->next->next = temp;
    temp->prev->next->prev = temp->prev;
    temp->prev = temp->prev->next;
}

/**
 * Appends a new node to the list given the data.
 * If the list is empty, this will initialize a new list by calling prepend().
 * @param data The data we wish to append to the list.
 */
void List::append(const char data) {
    if (isEmpty()) {
        prepend(data);
    }
    else {
        tail->next = new Node(data);// put a new node at the end
        tail->next->prev = tail;// point the new node to the previous node
        tail = tail->next;// move the tail pointer to the new node
    }
}

/**
 * Determines if a list does not contain any Nodes.
 * @return True if there are no Nodes in the list.
 */
bool List::isEmpty() {
    return size() <= 0;
}

/**
 * Determines the number of Nodes in a list.
 * If there are no Nodes, will return 0.
 * @return The number of nodes in a list.
 */
int List::size() {
    if (head == nullptr) {
        return 0;
    }
    else {
        int size = 0;
        Node * temp = head;
        while (temp) {
            size++;
            temp = temp->next;
        }
        return size;
    }
}

/**
 * Removes a Node from the list given a position.
 * Lists are 0 indexed, so removing position 0 would remove the first item of
 * the list.
 * Care should be taken to not attempt to remove outside the range of the size
 * of the list.
 * Because of 0 indexing, attempting to remove position equal to the number of
 * elements (IE remove(4) for size() == 4), will be an error.
 * @param pos The position of the Node we wish to remove.
 * @return The data that was in the removed Node.
 * @throws InvalidPosition if the pos given is out of range of the list size
 *         (IE -1 or 4 if the list only has 4 elements).
 */
char List::remove(int pos) {
    if (pos >= size() || pos < 0) {
        throw InvalidPosition(pos);
    }

    // early returns if beginning or end of list
    if (pos == 0) {
        return popFront();
    }
    if (pos == size()-1) {
        return popBack();
    }


    // otherwise get from within list
    Node * temp = nullptr;
    int i = 0;
    if (pos > size()/2) { // start from tail if closer
        temp = tail;
        while (i > pos) {
            temp = temp->prev;
            i--;
        }
    }
    else { // start from head if tail is not closer to pos
        temp = head;
        while (i < pos) {
            temp = temp->next;
            i++;
        }
    }

    // update pointers to remove node and free memory
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    char result = temp->data;
    delete temp;
    return result;
}

/**
 * Removes all Nodes from a list with a given value.
 * @param value The value we want to remove from the list.
 * @return The number of nodes removed from the list.
 */
int List::remove(const char value) {
    int numRemoved = 0;

    // trim the front of the list of the value until head is no longer the data
    while (head && head->data == value) {
        popFront();
        numRemoved++;
    }
    // trim the back of the list of the value until tail is no longer the data
    while (tail && tail->data == value) {
        popBack();
        numRemoved++;
    }

    Node * traveller = head;

    // this is fairly complex but basically it removes any occurrence of what
    // we are looking for from inside the list that was not removed by trimming
    // the tail and the head of the value
    while (traveller && traveller->next) {
        if (traveller->data == value) {
            Node * temp = traveller;
            if (traveller->next) {
                traveller->next->prev = traveller->prev;
            }
            if (traveller->prev) {
                traveller->prev->next = traveller->next;
            }
            traveller = traveller->next;
            delete temp;
            numRemoved++;
        }
        else {
            traveller = traveller->next;
        }
    }
    return numRemoved;
}

/**
 * Removes the first Node from the list and returns the data held by that node.
 * @return The data in the first Node of the list.
 */
char List::popFront() {
    if (isEmpty()) {
        throw EmptyList();
    }

    char data = head->data;

    Node * temp = head;
    if (head->next) {
        head->next->prev = nullptr;
    }
    head = head->next;
    delete temp;
    return data;
}

/**
 * Removes the last Node from the list and returns the data held by that node.
 * @return The data in the last Node of the list.
 */
char List::popBack() {
    if (isEmpty()) {
        throw EmptyList();
    }
    if (size() == 1) {
        return popFront();
    }
    char data = tail->data;
    Node * temp = tail;
    if (tail->prev) {
        tail->prev->next = nullptr;
    }
    tail = tail->prev;
    delete temp;
    return data;
}

/**
 * Default constructor for InvalidPosition.
 * Holds on to a message with information about the position given.
 * @param pos The position that is out of range.
 */
List::InvalidPosition::InvalidPosition(int pos)
    : std::out_of_range("Position out of range: " + std::to_string(pos))
{}

/**
 * Default constructor for EmptyList.
 * Holds a message with information about the list being empty.
 */
List::EmptyList::EmptyList()
    : std::invalid_argument("List does not contain any elements.")
{}


