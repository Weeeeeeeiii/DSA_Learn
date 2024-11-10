#ifndef BST_H
#define BST_H

#include "dsexceptions.h"
#include <algorithm>

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree() : root{nullptr}
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{clone(rhs.root)} {}

    /**
     * Move constructor
     */
    BinarySearchTree(BinarySearchTree &&rhs) noexcept : root{rhs.root}
    {
        rhs.root = nullptr;
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree()
    {
        makeEmpty();
    }

    /**
     * Copy assignment
     */
    BinarySearchTree &operator=(const BinarySearchTree &rhs)
    {
        if (this != &rhs)
        {
            BinarySearchTree temp(rhs);
            std::swap(root, temp.root);
        }
        return *this;
    }

    /**
     * Move assignment
     */
    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept
    {
        std::swap(root, rhs.root);
        return *this;
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMin() const
    {
        if (isEmpty())
            throw UnderflowException{};
        return findMin(root)->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMax() const
    {
        if (isEmpty())
            throw UnderflowException{};
        return findMax(root)->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x) const
    {
        return contains(x, root);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree(std::ostream &out = std::cout) const
    {
        if (isEmpty())
            out << "Empty tree" << std::endl;
        else
            printTree(root, out);
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x)
    {
        insert(x, root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(Comparable &&x)
    {
        insert(std::move(x), root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable &x)
    {
        remove(x, root);
    }

  protected:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        int height = 1;

        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
            : element{theElement}, left{lt}, right{rt} {}

        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
            : element{std::move(theElement)}, left{lt}, right{rt} {}
    };

    BinaryNode *root;

    /**
     * Get heigiht of node.
     * t is the pointer of the node.
     */
    int getHeight(BinaryNode *t)
    {
        if (t == nullptr)
            return 0;
        return t->height;
    }
    /**
     * Internal method to get the balence factor of node.
     * Balance factor = left node height - right node height.
     * t is the pointer of the node.
     */
    int getBalance(BinaryNode *t)
    {
        if (t == nullptr)
            return 0;
        return getHeight(t->left) - getHeight(t->right);
    }

    /**
     * Right rotate a tree.
     * t points root of subtree.
     */
    void rightRotate(BinaryNode *&t)
    {
        // Remenber child node
        BinaryNode * const tmp = t->left;

        // Let root point to child's right child
        t->left = tmp->right;

        // Let ordinary child node points to its root
        tmp->right = t;

        // Let root be the ordianry child node
        t = tmp;

        // Update heights
        t->right->height = 1 + std::max(getHeight(t->right->left), getHeight(t->right->right));

        t->height = 1 + std::max(getHeight(t->left), getHeight(t->right));
    }

    /**
     * Left rotate a tree.
     * Symetric to upside.
     */
    void leftRotate(BinaryNode *&t)
    {
        BinaryNode * const tmp = t->right;
        t->right = tmp->left;
        tmp->left = t;
        t = tmp;

        t->left->height = 1 + std::max(getHeight(t->left->left), getHeight(t->left->right));
        t->height = 1 + std::max(getHeight(t->left), getHeight(t->right));
    }

    /**
     * Rotate the node after insert.
     * t is the node pointer from its parent node.
     */
    void rotate(const Comparable &x, BinaryNode *&t)
    {
        // Get balance factor
        int balance = getBalance(t);

        if (balance > 1 && x < t->left->element)
        {
            rightRotate(t);
        }
        else if (balance > 1 && x > t->left->element)
        {
            leftRotate(t->left);
            rightRotate(t);
        }
        else if (balance < -1 && x > t->right->element)
        {
            leftRotate(t);
        }
        else if (balance < -1 && x < t->right->element)
        {
            rightRotate(t->right);
            leftRotate(t);
        }
        else
            ;
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Comparable &x, BinaryNode *&t)
    {
        if (t == nullptr)
        {
            t = new BinaryNode{x, nullptr, nullptr};
            return;
        }
        else if (x < t->element)
        {
            insert(x, t->left);
            if (t->height == t->left->height)
                ++(t->height);
        }
        else if (t->element < x)
        {
            insert(x, t->right);
            if (t->height == t->right->height)
                ++(t->height);
        }
        else
            return; // Duplicate; do nothing

        rotate(x, t);
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(Comparable &&x, BinaryNode *&t)
    {
        if (t == nullptr)
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        else if (x < t->element)
        {
            insert(std::move(x), t->left);
            if (t->height == t->left->height)
                ++(t->height);
        }
        else if (t->element < x)
        {
            insert(std::move(x), t->right);
            if (t->height == t->right->height)
                ++(t->height);
        }
        else
            ; // Duplicate; do nothing

        rotate(x, t);
    }

    /**
     * Find and delete the minimul node, return its pointer
     */
    BinaryNode* detachMin(BinaryNode *node, BinaryNode *& minNode)
    {
        if (!node->left)
        {
            minNode = node;
            return node->right;
        }
        node->left = detachMin(node->left, minNode);
        return node;
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const Comparable &x, BinaryNode *&t)
    {
        if (t == nullptr)
            return; // Item not found; do nothing
        if (x < t->element)
            remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) // Two children
        {
            BinaryNode *minNode = nullptr;
            BinaryNode *oldNode = t;
            detachMin(t->right, minNode);
            t = minNode;
            t->left = oldNode->left;
            t->right = oldNode->right;
            delete oldNode;
            return;
        }
        else
        {
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode *findMin(BinaryNode *t) const
    {
        if (t != nullptr)
            while (t->left != nullptr)
                t = t->left;
        return t;
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode *findMax(BinaryNode *t) const
    {
        if (t != nullptr)
            while (t->right != nullptr)
                t = t->right;
        return t;
    }

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }

    /******************* Recursive method *********************
        bool contains(const Comparable &x, BinaryNode *t) const
        {
            if (t == nullptr)
                return false;
            else if (x < t->element)
                return contains(x, t->left);
            else if (t->element < x)
                return contains(x, t->right);
            else
                return true; // Match
        }
    ***********************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(BinaryNode *&t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullptr;
        }
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree(BinaryNode *t, std::ostream &out) const
    {
        if (t != nullptr)
        {
            printTree(t->left, out);
            out << t->element << std::endl;
            printTree(t->right, out);
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode *clone(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        else
            return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }
};

#endif