#include <cstdint>
#include <string>
#include <tuple>
#include <iostream>

template <class T> class maxHeap
{
    public:
        maxHeap() = default;
        maxHeap(std::vector<std::tuple<T, uint32_t>> arr);
        ~maxHeap();
        std::vector<std::tuple<T, uint32_t>> heapsort();
        void buildMaxHeap();
        uint32_t heapSize();
        T heapMaximum();
        T heapExtractMax();
        void heapIncreaseKey(uint32_t index, std::tuple<T, uint32_t> key); // uint32_t is the priority
        void heapInsert(std::tuple<T, uint32_t> key);
    protected:
        uint32_t parent(uint32_t index);
        uint32_t left(uint32_t index);
        uint32_t right(uint32_t index);
        void exchange(std::tuple<T, uint32_t>& A, std::tuple<T, uint32_t>& B);
        void maxHeapify(std::vector<std::tuple<T, uint32_t>> arr, uint32_t index, uint32_t heapSize);

        std::vector<std::tuple<T, uint32_t>> m_arr;
        uint32_t m_heapSize;
};

template <class T> maxHeap<T>::maxHeap(std::vector<std::tuple<T, uint32_t>> arr)
{
    m_arr = arr;
    buildMaxHeap();
}

template <class T> maxHeap<T>::~maxHeap()
{

}

/**
 * @brief returns the index of parent of the node at the specified index
*/
template <class T> uint32_t maxHeap<T>::parent(uint32_t index)
{
    return index/2;
}

template <class T> uint32_t maxHeap<T>::left(uint32_t index)
{
    return (2*index)-2;
}

template <class T> uint32_t maxHeap<T>::right(uint32_t index)
{
    return (2*index)-1;
}

template <class T> uint32_t maxHeap<T>::heapSize()
{
    return m_heapSize;
}

template <class T> void maxHeap<T>::exchange(std::tuple<T, uint32_t>& A, std::tuple<T, uint32_t>& B)
{
    std::tuple<T, uint32_t> temp;

    temp = A;
    B = A;
    B = temp;
}

template <class T> void maxHeap<T>::maxHeapify(std::vector<std::tuple<T, uint32_t>> arr, uint32_t index, uint32_t heapSize)
{
    uint32_t largest = 0;
    
    if((left(index) <= heapSize) && (std::get<1>(arr.at(left(index))) > std::get<1>(arr.at(index))))
    {
        largest = left(index);
    }
    else
    {
        largest = index;
    }

    if((right(index) <= heapSize) && (std::get<1>(arr.at(right(index))) > std::get<1>(arr.at(largest))))
    {
        largest = right(index);
    }

    if(largest != index)
    {
        exchange(arr.at(index), arr.at(largest));
        maxHeapify(arr, index, heapSize);
    }
}

template <class T> void maxHeap<T>::buildMaxHeap()
{
    m_heapSize = m_arr.size();
    for(uint32_t iIter = (m_arr.size()/2); iIter > 0; iIter--)
    {
        maxHeapify(m_arr, iIter, m_heapSize);
    }
}

// assume we already have a max heap
template <class T> std::vector<std::tuple<T, uint32_t>> maxHeap<T>::heapsort()
{
    // create a copy of the array
    std::vector<std::tuple<T, uint32_t>> sorted = m_arr;
    uint32_t heapSize = m_arr.size();
    for(uint32_t iIter = sorted.size(); iIter > 1; iIter--)
    {
        exchange(sorted.at(0), sorted.at(iIter));
        heapSize--;
        maxHeapify(sorted, 0);
    }

    // return the copy
}

template <class T> T maxHeap<T>::heapMaximum()
{
    return std::get<0>(m_arr.at(0));
}

template <class T> T maxHeap<T>::heapExtractMax()
{
    T max;
    if(heapSize() < 1)
    {
        std::cout<<"heap underflow"<<std::endl;
    }

    max = std::get<0>(m_arr.at(0));
    std::get<0>(m_arr.at(0)) = std::get<0>(m_arr.at(heapSize()));
    m_heapSize--;
    maxHeapify(m_arr, 0, m_heapSize);
    return max;
}

template <class T> void maxHeap<T>::heapIncreaseKey(uint32_t index, std::tuple<T, uint32_t> key)
{
    std::vector<std::tuple<T, uint32_t>> sorted = m_arr;
    if(std::get<1>(key) < std::get<1>(m_arr.at(index)))
    {
        std::cout<<"new key is smaller than current key"<<std::endl;
    }

    m_arr.at(0) = key;
    while((index > 0) && (std::get<0>(m_arr.at(parent(index))) < std::get<0>(m_arr.at(index))))
    {
        exchange(sorted.at(index), sorted.at(parent(index)));
        index = parent(index);
    }
}

template <class T> void maxHeap<T>::heapInsert(std::tuple<T, uint32_t> key)
{
    m_arr.resize(m_arr.size() + 1);
    m_heapSize++;
    std::get<1>(m_arr.at(heapSize())) = 0;
    heapIncreaseKey(heapSize(), key);
}