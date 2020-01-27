#ifndef LINKEDLIST_LIST_H
#define LINKEDLIST_LIST_H

#include <stdexcept>
#include <string>

/**
 * List is a double ended linked list that stores char data.
 * A List object can be traversed in forward and reverse.
 * Methods for inserting, removing, and traversing the list are provided for
 * basic functionality.
 *
 * This class can be additionally be implemented as a queue or stack using the
 * provided prepend/append and popFront/popBack methods as appropriate.
 */
class List {
private: /*Private member inner class declarations*/
    /**
     * Member Node class stores data and the pointers to the next/previous Node.
     * Each Node is initialized as pointing to nowhere and must be added to the
     * list creating it by pointing to the next/previous Node as applicable.
     * If appending, next should remain nullptr.
     * If prepending, prev should remain nullptr.
     * If inserting, next should be set to the Node that is to be next and prev
     * should be set to the Node that the created Node should follow.
     * Nodes can be initialized as empty or with an char argument to store.
     */
    struct Node {
        char data = '\0'; // for storing data
        Node * next = nullptr; // for storing pointer to next node
        Node * prev = nullptr; // for storing pointer to previous node
        Node() = default; // default constructor creates an empty node
        explicit Node(const char data) // constructor with data arg
            : data(data)                       // constructs a node with data
        {}                                     // default points nowhere
    };

private: /*Private member variable declarations*/
    Node * head; // For storing the beginning of the list.
    Node * tail; // For storing the end of the list.

private: /*Class friend declarations*/
    friend class ListTestSuite; // For unit testing.

public: /*Member inner class declarations*/
    /**
     * InvalidPosition exception class.
     * When attempting to use a position that is not valid (i.e. -1 or a position
     * greater than the size of the current list), this exception will be thrown.
     */
    class InvalidPosition : public std::out_of_range {
    public:
        explicit InvalidPosition(int pos);
    };
    /**
     * EmptyList exception class.
     * When attempting to use a function that can only act on a list containing
     * data, this exception will be thrown if the list is empty.
     */
    class EmptyList : public std::invalid_argument {
    public:
        explicit EmptyList();
    };

public: /*Constructors and destructors*/
    List();
    ~List();

public: /*Member function declarations*/
    // insertion operations
    void prepend(const char data);
    void insert(int pos, char data);
    void append(const char data);

    // general maintenance operations
    bool isEmpty();
    int size();

    // deletion operations
    char remove(int pos); // remove specific position
    //remove all nodes with given value, return num nodes removed
    int remove(const char value);

    // delete and return operations
    char popFront(); // remove and return head
    char popBack(); // remove and return tail
};

#endif //LINKEDLIST_LIST_H
