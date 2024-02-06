/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  while (head_ != NULL) {
    ListNode * temp = head_;
    head_ = head_->next;
    delete temp;
  }
}


/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode->prev = NULL;

  if (head_ != NULL) {
    newNode->next = head_;
    head_->prev = newNode;
    head_ = newNode;
  } else {
    newNode->next = NULL;
    head_ = newNode;
    tail_ = newNode;
  }

  
  
  /*
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
    head_ = newNode;
  }
  
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  */
  
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode->next = NULL;
  if (tail_ != NULL) {
    newNode->prev = tail_;
    tail_->next = newNode;
    tail_ = newNode;
  } else {
    newNode->next = NULL;
    head_ = newNode;
    tail_ = newNode;
  }

  length_++;

}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if (start == NULL || splitPoint == 0) {
    return start;
  } 
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }
  
  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
    if (head_ == NULL || tail_ == NULL) {
      return;
    }
    if (startPoint == endPoint) {
      return;
    }
    ListNode * currentBegin = startPoint;
    ListNode * currentBeginCopy = currentBegin;
    ListNode * start = currentBegin->prev;
    ListNode * temp = currentBegin->next;
    //ListNode * temp = NULL;
    ListNode * copyEnd = endPoint;
    ListNode * copyStart = startPoint;

    currentBegin->next = endPoint->next;
    currentBegin->prev = temp;
    currentBegin = temp;

    while (currentBegin != copyEnd) {
      temp = currentBegin->next;
      currentBegin->next = currentBegin->prev;
      currentBegin->prev = temp;
      currentBegin = temp;
      //std::cout << "hi" << std::endl;
    }
    endPoint->next = endPoint->prev;
    //std::cout << "hi" << std::endl;
    endPoint->prev = start;
    

    
    if (head_ == startPoint) {
      head_ = copyEnd;
    }
    //std::cout << "hi" << std::endl;
    if (tail_ == copyEnd) {
      tail_ = startPoint;
    }
    //std::cout << "hi" << std::endl;
    if (head_ != startPoint) {
      currentBeginCopy = currentBegin; 
      //std::cout << "hi" << std::endl;
    }
    if (tail_ != copyEnd) {
      startPoint->next->prev = startPoint;
    }

//std::cout << "hi" << std::endl;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (length_ > -1 && length_ < 2) {
    return;
  }
  ListNode * start = head_;
  ListNode * end = start;

  while (end != NULL){
    
    



    for (int i = 0; i < n-1; i++) {
      if (end->next == NULL) {
        reverse(start, end);
        return;
      }
      end = end->next;
    }
    reverse(start, end);
    if (end->next != NULL) {
      start = end->next;
      end = start;
    } else {
      return;
    } 
  } 
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first == NULL){
    return second;
  } else if (second == NULL) {
    return first;
  }
  
  ListNode * start = NULL;
  ListNode * end = NULL;

  if (second->data < first->data) {
    start = second; 
    second = second->next;
  } else {
    start = first;
    first = first->next;
  }
  end = start;

  while (second != NULL && first != NULL) {
    if (second->data < first->data) {
      end->next = second;
      end = second;
      second = second->next;
    } else {
      end->next = first;
      end = first;
      first = first->next;
    }
  }

  if (first == NULL) {
    end->next = second;
  } else {
    end->next = first;
  }


  return start;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength > -1 && chainLength < 2) {
    return start;
  }
  int halfLength = chainLength / 2;
  ListNode * temp;
  ListNode * firstHalf;
  ListNode * secondHalf;

  temp = split(start, halfLength);
  firstHalf = mergesort(start, halfLength);
  secondHalf = mergesort(temp, chainLength - halfLength);
  return merge(firstHalf, secondHalf);
}
