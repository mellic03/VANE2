#pragma once


namespace vane::dsa
{
    template <typename T>
    struct LinkedList
    {
    private:
        T *mHead;

    public:
        LinkedList(): mHead(nullptr) {  };

        void insert(T *node)
        {
            node->mNext = mHead;
            mHead = node;
        }

        struct iterator
        {
            T *mNode;
            iterator(T *node): mNode(node) {  }
            iterator(const iterator &I): mNode(I.mNode) {  }
            iterator &operator++() { mNode = mNode->mNext; return *this; };
            iterator operator++(int) { return iterator(mNode->mNext); };
            bool operator==(const iterator &rhs ) { return mNode == rhs.mNode; };
            bool operator!=(const iterator &rhs ) { return mNode != rhs.mNode; };
            T *&operator*() { return mNode; };
        };

        iterator begin() { return iterator(mHead); };
        iterator end()   { return iterator(nullptr); };
    };
}
