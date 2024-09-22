
#pragma once
#ifndef List_h
#define List_h

#include <algorithm>
using namespace std;

// based on the code from my teacher
template <class T> class List
{
public:
    List(int size = 20);
    T &operator[](int index);
    int getlength(void);
    void setitem(int index, T value);
    T getitem(int index);
    void append(T value);
    void insert(int index, T value);
    void remove(int index);
    void concat(List<T> &list);
    bool member(T value);
    bool equal(List<T> &list);
    bool sublist(List<T> &list);
    void prettyprint(void);
    T select(int k);
    void empty();
    void sort_items(bool (*compare)(T, T));     // sort all items using quick sort
	int search(T item, bool (*equal)(T, T));                         // binary search the index of T item
    int search(T item);                         // binary search the index of T item
    int search(T item, bool (*compare)(T, T), bool (*equal)(T, T));  // search the item with compare function
private:
    int numitems;
    T * data_items;
    int maxsize, minsize;
    void allocate(void);
    void deallocate(void);
};

template<class T> List<T>::List(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    data_items = new T[maxsize];
}

template<class T> T& List<T>::operator[](int index)
{
    return data_items[index];
}

template<class T> int List<T>::getlength(void)
{
    return numitems;
}

template<class T> void List<T>::setitem(int index, T value)
{
    if ((index >= 0) && (index < numitems))
    {
        data_items[index] = value;
        return;
    }
    else
        cout << "Index error: index out or range\n";
}

template<class T> T List<T>::getitem(int index)
{
    if ((index >= 0) && (index < numitems))
    {
        return data_items[index];
    }
    else
    {
        cout << "Index error: index out or range\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void List<T>::append(T value)
{
    if (numitems == maxsize)
        allocate();
    data_items[numitems] = value;
    ++numitems;
    return;
}

template<class T> void List<T>::insert(int index, T value)
{
    if (numitems == maxsize)
        allocate();
    if (index < numitems)
    {
        for (int j = numitems - 1; j >= index; --j)
        {
            data_items[j + 1] = data_items[j];
        }
        data_items[index] = value;
        ++numitems;
        return;
    }
    else
    {
        append(value);
        return;
    }
}

template<class T> void List<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T* newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = data_items[i];
    }
    delete[] data_items;
    data_items = newarray;
    maxsize = newsize;
    return;
}

template<class T> void List<T>::remove(int index)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (index <= numitems)
    {
        for (int j = index; j < numitems; ++j)
        {
            data_items[j - 1] = data_items[j];
        }
        --numitems;
        return;
    }
    else
        cout << "Index error: list index out of range\n";
}

template<class T> void List<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    T* newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = data_items[i];
    }
    delete[] data_items;
    data_items = newarray;
    maxsize = newsize;
    return;
}

template<class T> void List<T>::concat(List<T>& list)
{
    int length = list.getlength();
    for (int i = 1; i <= length; ++i)
    {
        append(list[i]);
    }
    return;
}

template<class T> bool List<T>::member(T value)
{
    bool result = false;
    for (int i = 0; i < numitems; ++i)
    {
        if (data_items[i] == value)
        {
            result = true;
            break;
        }
    }
    return result;
}

template<class T> bool List<T>::equal(List<T>& list)
{
    bool result = true;
    if (numitems == list.getlength())
    {
        for (int i = 0; i < numitems; ++i)
        {
            if (data_items[i] == list[i + 1])
                continue;
            else
            {
                result = false;
                break;
            }
        }
    }
    else
        result = false;
    return result;
}

template<class T> bool List<T>::sublist(List<T>& list)
{
    int length = list.getlength();
    bool result = true;
    for (int i = 0, j = 0; (i < length) && (j < numitems); ++i, ++j)
    {
        if (list[i] == data_items[j])
        {
            if ((j == numitems - 1) && (i < length))
            {
                result = false;
                break;
            }
        }
        else
            if (j == numitems - 1)
            {
                result = false;
                break;
            }
            else
                --i;
    }
    return result;
}

template<class T> void List<T>::prettyprint(void)
{
    data_items[0]->show(true);         // show header
    for (int i = 0; i < numitems; i++)
    {
        data_items[i]->show();
    }
}


template<class T> T List<T>::select(int k)
{
    List<T> less = List<T>();
    List<T> more = List<T>();

    T pivot = data_items[numitems - 1];

    for (int i = 0; i < numitems; i++) {
        if (data_items[i] < pivot) {
            less.append(data_items[i]);
        }
        else if (data_items[i] > pivot) {
            more.append(data_items[i]);
        }
        else {
            continue;
        }
    }

    if (k <= less.getlength() && k > 0) {
        return less.select(k);
    }
    else if (k > less.getlength() && k <= numitems - more.getlength()) {
        return pivot;
    }
    else if (k > numitems - more.getlength() && k <= numitems) {
        return more.select(k - (numitems - more.getlength()));
    }
    else {
        return INT_MAX;
    }
    // this member function needs to be implemented
}


template <class T> void List<T>::empty()
{
    delete[] data_items;
    List();
}

template <class T> void List<T>::sort_items(bool (*compare)(T, T))
{
    // qsort(data_items, numitems, sizeof(T), (_CoreCrtNonSecureSearchSortCompareFunction)compare);
    sort(data_items, data_items + numitems, compare);
}

template <class T> int List<T>::search(T item)
{
    int left = 0, right = numitems - 1;
    while (left <= right)
    {
        int middle = left + ((right - left) / 2);
        if (data_items[middle] > item)
            right = middle - 1;
        else if (data_items[middle] < item)
            left = middle + 1;
        else
            return middle;
    }
    return -1;
};

template <class T> int List<T>::search(T item, bool (*compare)(T, T), bool (*equal)(T, T))
{
    sort_items(compare);
	int left = 0, right = numitems - 1;
	while (!compare(data_items[left], data_items[right]))
	{
		int middle = left + ((right - left) / 2);
		if (compare(data_items[middle], item))
			right = middle - 1;
		else if (equal(data_items[middle], item))
			return middle;
		else
			left = middle + 1;
	}
	return -1;

}

template <class T> int List<T>::search(T item, bool (*equal)(T, T))
{
    for (int i = 0; i < numitems; i++)
    {
        if (equal(data_items[i], item))
            return i;
    }
    return -1;
}


#endif  // List
