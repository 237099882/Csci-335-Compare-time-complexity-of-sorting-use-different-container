// myAVLtree.hpp
#ifndef MYAVLTREE_HPP
#define MYAVLTREE_HPP

#include <iostream>
#include <vector>
#include <algorithm>

//implenment of AVLtree from textbook and with modify of hanle with integer and duplicate, and add helper funtions getSize()
class AvlTree
{
  public:
    AvlTree( ) : root{ nullptr }
      { }
    
    AvlTree( const AvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    AvlTree( AvlTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    AvlTree & operator=( AvlTree && rhs )
    {
        std::swap( root, rhs.root );
        
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     * return -2 if empty.
     */
    const int & findMin( ) const
    {
        if( isEmpty( ) )
            return -2;
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * return -2 if empty.
     */
    const int & findMax( ) const
    {
        if( isEmpty( ) )
            return -2;
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const int & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            std::cout << "Empty tree" << std::endl;
        else
            printTree( root );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const int & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree
     */
    void insert( int && x )
    {
        insert( std::move( x ), root );
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const int & x )
    {
        remove( x, root );
    }
    //Get the number of count of tree.
    int getSize() const
    {
        return getSize(root);
    }

  private:
    struct AvlNode
    {
        int element;
        AvlNode *left;
        AvlNode *right;
        int height;
        //use count to record duplicant and defult is 1
        int count;
        AvlNode( const int & ele, AvlNode *lt, AvlNode *rt, int h = 0, int c = 1 )
          : element{ ele }, left{ lt }, right{ rt }, height{ h }, count { c }{ }
        
        AvlNode( int && ele, AvlNode *lt, AvlNode *rt, int h = 0 , int c = 1)
          : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h }, count { c } { }
    };

    AvlNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const int & x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else if( x == t->element)
            t->count++;
        balance( t );
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( int && x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else if( x == t->element)
            t->count++;
        balance( t );
    }
     
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const int & x, AvlNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            if(t->count>1)
            {
                t->count--;
            }
            else{
                t->element = findMin( t->right )->element;
                remove( t->element, t->right );
            }
        }
        else
        {
            if(t->count>1)
            {
                t->count--;
            }
            else
            {
                AvlNode *oldNode = t;
                t = ( t->left != nullptr ) ? t->left : t->right;
                delete oldNode;
            }
        }
        
        balance( t );
    }
    
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        else
        if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
                
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const int & x, AvlNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left );
            std::cout << t->element << std::endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
    //Use recurise call to find total counts of avl tree
    int getSize(AvlNode *t) const
    {
        if(t == nullptr)
        {
            return 0;
        }
        return t->count + getSize(t->left) + getSize(t->right);
    }
};

//insert and pop median from instructions
void treeMedian (const std::vector<int> * instructions);
//balance two AvlTree
void resize(AvlTree &small, AvlTree &large);
#endif 