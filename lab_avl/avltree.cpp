/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */



using namespace std;

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * temp = t->right;
    t->right = temp->left;
    temp->left = t;
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = temp;
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * temp = t->left;
    t->left = temp->right;
    temp->right = t;
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = temp;
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == NULL) {
        return;
    }
    int balanceValue = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if (balanceValue == 2) {
        int balanceValueRight = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if (balanceValueRight > 0) {
            rotateLeft(subtree);
        } else {
            rotateRightLeft(subtree);
        }
    } else if (balanceValue == -2) {
        int balanceValueLeft = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if (balanceValueLeft > 0) {
            rotateLeftRight(subtree);
        } else {
            rotateRight(subtree);
        }
    }
    subtree->height = 1 + max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left));
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        Node * temp = new Node(key, value);
        subtree = temp;
    } else if (key > subtree->key) {
        insert(subtree->right, key, value);
        rebalance(subtree);
    } else if (key <= subtree->key) {
        insert(subtree->left, key, value);
        rebalance(subtree);
    }
    //subtree->height = 1 + max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left));
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * replacement = subtree->left;
            while (replacement->right != NULL) {
                replacement = replacement->right;
            }
            
            swap(subtree, replacement);
            remove(subtree->left, replacement->key);
            

        } else {
            /* one-child remove */
            // your code here
            Node * tempRight = subtree->right;
            Node * tempLeft = subtree->left;

            if (tempRight != NULL) {
                delete subtree;
                subtree = tempRight;
                
            } else if (tempLeft != NULL) {
                delete subtree;
                subtree = tempLeft;
              
            }
        }
        // your code here
        //subtree->height = 1 + max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left));
        rebalance(subtree);
    }
    rebalance(subtree);
}
