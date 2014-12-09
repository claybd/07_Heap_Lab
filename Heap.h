/* This program was written by Ben Clay.  It may be used without the author's consent for non-profit puproses only. */

#include "Queue.h"
#include <utility>

//This should be the initial arrSize
#define START_SIZE 10

/*
 * This is a priority queue, which means that as items are removed in order
 * of decreasing priority.
 *
 * 
 */
template<class Pri, class T>
class Heap : public Queue<std::pair<Pri, T> > {
public:
  Heap();
  ~Heap();

  //Add a new item
  virtual void add(std::pair<Pri,T> toAdd);

  //Remove the item with lowest priority, and return it
  //If the queue is empty, throw a string exception
  virtual std::pair<Pri,T> remove();

  //Return the number of items currently in the queue
  virtual unsigned long getNumItems();

private:
  int arrSize;
  int numItems;
  std::pair<Pri, T>* backingArray;

  //Grow the backingArray by making a new array of twice the size,
  // and copying over the data
  void grow();

  //Check the item at index, and make sure it is in the right place.
  // If not, swap it up the "tree" of the heap until you find the right
  // place
  void bubbleUp(unsigned long index);

  //Check the item at index, and make sure it is in the right place.
  // If not, swap it down the "tree" of the heap until you find the right
  // place
  void trickleDown(unsigned long index);
    
  unsigned long left(unsigned long index);
  unsigned long right(unsigned long index);
  unsigned long parent(unsigned long index);
    
};

#include <string>

template<class Pri, class T>
Heap<Pri,T>::Heap()
{
    numItems = 0;
    arrSize = 20;
    backingArray = new std::pair<Pri, T>[arrSize];
}

template<class Pri, class T>
Heap<Pri,T>::~Heap()
{
    numItems = 0;
    arrSize = 0;
    delete[] backingArray;
}

template<class Pri, class T>
unsigned long Heap<Pri,T>::left(unsigned long index)
{
    return 2*index+1;
}

template<class Pri, class T>
unsigned long Heap<Pri,T>::right(unsigned long index)
{
    return 2*index+2;
}

template<class Pri, class T>
unsigned long Heap<Pri,T>::parent(unsigned long index)
{
    return (index-1)/2;
}

template<class Pri, class T>
void Heap<Pri,T>::grow()
{
    arrSize = arrSize*2;
    std::pair<Pri, T> *tempArray = new std::pair<Pri, T>[arrSize];
    
    for (int i=0; i < arrSize/2; i++)
        tempArray[i] = backingArray[i];
    
    backingArray = tempArray;
}

template<class Pri, class T>
void Heap<Pri,T>::add(std::pair<Pri,T> toAdd)
{
    if (numItems+1 > arrSize)
        grow();
    
    backingArray[numItems] = toAdd;
    numItems++;
    bubbleUp(numItems-1);
}

template<class Pri, class T>
void Heap<Pri,T>::bubbleUp(unsigned long index)
{
    unsigned long parentIndex = parent(index);
    
    while (index > 0 && backingArray[index].second < backingArray[parentIndex].second)
    {
        std::pair<Pri,T> holder = backingArray[index];
        backingArray[index] = backingArray[parentIndex];
        backingArray[parentIndex] = holder;
        
        index = parentIndex;
        parentIndex = parent(index);
    }
}

template<class Pri, class T>
void Heap<Pri,T>::trickleDown(unsigned long index)
{
    int i = index;
    
    do {
        int j = -1;
        unsigned long rightIndex = right(index);
        if (rightIndex < numItems && backingArray[rightIndex].first < backingArray[i].first)
        {
            int leftIndex = left(i);
            
            if (backingArray[leftIndex].first < backingArray[rightIndex].first)
                j = leftIndex;
            else
                j = rightIndex;
        }
        else
        {
            int leftIndex = left(i);
            if (leftIndex < numItems && backingArray[leftIndex].first < backingArray[i].first)
                j = leftIndex;
        }
        
        if (j >= 0)
        {
            std::pair<Pri,T> holder = backingArray[index];
            backingArray[index] = backingArray[j];
            backingArray[j] = holder;
        }
        
        i = j;
    } while (i >= 0);
}

template<class Pri, class T>
std::pair<Pri,T> Heap<Pri,T>::remove(){
    std::pair<Pri,T> tmp = backingArray[0];
    backingArray[0] = backingArray[--numItems];
    trickleDown(0);
    
    if (numItems+1 > arrSize)
        grow();

    return tmp;
}

template<class Pri, class T>
unsigned long Heap<Pri,T>::getNumItems(){
    return numItems;
}
