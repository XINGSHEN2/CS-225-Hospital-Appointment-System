#pragma once

#ifndef _Fibonacci_H
#define _Fibonacci_H
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Global.h"
// #include "Person.h"
// #include "Queue.h"
// #include "List.h"
using namespace std;

template <class T>
class FibNode {
public:
	int key;                        // �ؼ���(��ֵ)��������T�Ķ����ĳ�����������
	T node;						    // ָ��һ��T�Ķ���
	int degree;						// ����
	FibNode<T>* left;				// ���ֵ�
	FibNode<T>* right;				// ���ֵ�
	FibNode<T>* child;				// ��һ�����ӽڵ�
	FibNode<T>* parent;				// ���ڵ�
	bool marked;					// �Ƿ�ɾ����һ������

    FibNode(T node) 
    {
        key = node->key;
        this->node = node;
        degree = 0;
        marked = false;
        left = this;
        right = this;
        parent = NULL;
        child = NULL;
    }
};

template <class T>
class FibHeap {
private:
	int keyNum;						// ���нڵ������
	int maxDegree;					// ����
	FibNode<T>* min;				// ��С�ڵ�(ĳ����С�ѵĸ��ڵ�)
	FibNode<T>** cons;				// ���ȵ��ڴ�����

public:
	FibHeap();
	~FibHeap();

    // ��ȡ���ڵ�
    T get_min();

	// �½�key��Ӧ�Ľڵ㣬��������뵽쳲���������
	void insert(T node);
	// �Ƴ�쳲��������е���С�ڵ�
	void removeMin();
	// ��other�ϲ�����ǰ����
	void combine(FibHeap<T>* other);
	// ��ȡ쳲�����������С��ֵ�������浽pkey�У��ɹ�����true�����򷵻�false��
	bool minimum(T* pkey);
	// ��쳲��������м�ֵoldkey����Ϊnewkey
	void update(T oldkey, T newkey);
	// ɾ����ֵΪkey�Ľڵ�
	void remove(T key);
	// 쳲����������Ƿ������ֵkey
	bool contains(T key);
	// ��ӡ쳲�������
	void print();
	// ����
	void destroy();

// private:
	// ��node��˫�����Ƴ�
	void removeNode(FibNode<T>* node);
	// ��node�ѽ�����root���֮ǰ(ѭ��������)
	void addNode(FibNode<T>* node, FibNode<T>* root);
	// ��˫������b���ӵ�˫������a�ĺ���
	void catList(FibNode<T>* a, FibNode<T>* b);
	// ���ڵ�node���뵽쳲���������
	void insert(FibNode<T>* node);
	// ��"�ѵ���С���"�Ӹ��������Ƴ���
	FibNode<T>* extractMin();
	// ��node���ӵ�root�����
	void link(FibNode<T>* node, FibNode<T>* root);
	// ����consolidate����ռ�
	void makeCons();
	// �ϲ�쳲������ѵĸ�������������ͬ��������
	void consolidate();
	// �޸Ķ���
	void renewDegree(FibNode<T>* parent, int degree);
	// ��node�Ӹ��ڵ�parent���������а����������ʹnode��Ϊ"�ѵĸ�����"�е�һԱ��
	void cut(FibNode<T>* node, FibNode<T>* parent);
	// �Խڵ�node����"��������"
	void cascadingCut(FibNode<T>* node);
	// ��쳲��������нڵ�node��ֵ����Ϊkey
	void decrease(FibNode<T>* node, T key);
	// ��쳲��������нڵ�node��ֵ����Ϊkey
	void increase(FibNode<T>* node, T key);
	// ����쳲������ѵĽڵ�node�ļ�ֵΪkey
	void update(FibNode<T>* node, T key);
	// ����С��root�в���node
	FibNode<T>* search(FibNode<T>* root, T node);
	// ��쳲��������в���node
	FibNode<T>* search(T node);
	// ɾ�����node
	void remove(FibNode<T>* node);
	// ����쳲�������
	void destroyNode(FibNode<T>* node);
	// ��ӡ"쳲�������"
	void print(FibNode<T>* node, FibNode<T>* prev, int direction);
};

/*
 * ���캯��
 */
template <class T>
FibHeap<T>::FibHeap()
{
    keyNum = 0;
    maxDegree = 0;
    min = NULL;
    cons = NULL;
}

/*
 * ��������
 */
template <class T>
FibHeap<T>::~FibHeap()
{
}

/*
 * ��node��˫�����Ƴ�
 */
template <class T>
void FibHeap<T>::removeNode(FibNode<T>* node)
{
    node->left->right = node->right;
    node->right->left = node->left;
}

/*
 * ��node�ѽ�����root���֮ǰ(ѭ��������)
 *   a ���� root
 *   a ���� node ���� root
*/
template <class T>
void FibHeap<T>::addNode(FibNode<T>* node, FibNode<T>* root)
{
    node->left = root->left;
    root->left->right = node;
    node->right = root;
    root->left = node;
}

/*
 * ���ڵ�node���뵽쳲���������
 */
template <class T>
void FibHeap<T>::insert(FibNode<T>* node)
{
    if (keyNum == 0)
        min = node;
    else
    {
        addNode(node, min);
        if (node->key < min->key)
            min = node;
    }
    keyNum++;
}

/*
 * �½���ֵΪkey�Ľڵ㣬��������뵽쳲���������
 */
template <class T>
void FibHeap<T>::insert(T node)
{
    FibNode<T>* pnode;

    pnode = new FibNode<T>(node);
    if (pnode == NULL)
        return;

    insert(pnode);
}

/*
 * ��˫������b���ӵ�˫������a�ĺ���
 *
 * ע�⣺ �˴�a��b����˫������
 */
template <class T>
void FibHeap<T>::catList(FibNode<T>* a, FibNode<T>* b)
{
    FibNode<T>* tmp;

    tmp = a->right;
    a->right = b->right;
    b->right->left = a;
    b->right = tmp;
    tmp->left = b;
}


/*
 * ��other�ϲ�����ǰ����
 */
template <class T>
void FibHeap<T>::combine(FibHeap<T>* other)
{
    if (other == NULL)
        return;

    if (other->maxDegree > this->maxDegree)
        swap(*this, *other);

    if ((this->min) == NULL)                // this��"��С�ڵ�"
    {
        this->min = other->min;
        this->keyNum = other->keyNum;
        free(other->cons);
        delete other;
    }
    else if ((other->min) == NULL)           // this��"��С�ڵ�" && other��"��С�ڵ�"
    {
        free(other->cons);
        delete other;
    }                                       // this��"��С�ڵ�" && other��"��С�ڵ�"
    else
    {
        // ��"other�и�����"���ӵ�"this"��
        catList(this->min, other->min);

        if (this->min->key > other->min->key)
            this->min = other->min;
        this->keyNum += other->keyNum;
        free(other->cons);
        delete other;
    }
}

/*
 * ��"�ѵ���С���"�Ӹ��������Ƴ���
 * ����ζ��"����С�ڵ���������"�Ӷ����Ƴ�!
 */
template <class T>
FibNode<T>* FibHeap<T>::extractMin()
{
    FibNode<T>* p = min;

    if (p == p->right)
        min = NULL;
    else
    {
        removeNode(p);
        min = p->right;
    }
    p->left = p->right = p;

    return p;
}

/*
 * ��node���ӵ�root�����
 */
template <class T>
void FibHeap<T>::link(FibNode<T>* node, FibNode<T>* root)
{
    // ��node��˫�������Ƴ�
    removeNode(node);
    // ��node��Ϊroot�ĺ���
    if (root->child == NULL)
        root->child = node;
    else
        addNode(node, root->child);

    node->parent = root;
    root->degree++;
    node->marked = false;
}

/*
 * ����consolidate����ռ�
 */
template <class T>
void FibHeap<T>::makeCons()
{
    int old = maxDegree;

    // ����log2(keyNum)��"+1"��ζ������ȡ����
    // ex. log2(13) = 3������ȡ��Ϊ3+1=4��
    maxDegree = (log(keyNum) / log(2.0)) + 1;
    if (old >= maxDegree)
        return;

    // ��Ϊ��ΪmaxDegree���ܱ��ϲ�������ҪmaxDegree+1
    cons = (FibNode<T> **)realloc(cons,
        sizeof(FibHeap<T> *) * (maxDegree + 1));
}

/*
 * �ϲ�쳲������ѵĸ�������������ͬ��������
 */
template <class T>
void FibHeap<T>::consolidate()
{
    int i, d, D;
    FibNode<T>* x, * y, * tmp;

    makeCons();//���ٹ�ϣ���ÿռ�
    D = maxDegree + 1;

    for (i = 0; i < D; i++)
        cons[i] = NULL;

    // �ϲ���ͬ�ȵĸ��ڵ㣬ʹÿ����������Ψһ
    while (min != NULL)
    {
        x = extractMin();                // ȡ�����е���С��(��С�ڵ����ڵ���)
        d = x->degree;                    // ��ȡ��С���Ķ���
        // cons[d] != NULL����ζ����������(x��y)��"����"��ͬ��
        while (cons[d] != NULL)
        {
            y = cons[d];                // y��"��x�Ķ�����ͬ����"
            if (x->key > y->key)        // ��֤x�ļ�ֵ��yС
                swap(x, y);

            link(y, x);    // ��y���ӵ�x��
            cons[d] = NULL;
            d++;
        }
        cons[d] = x;
    }
    min = NULL;

    // ��cons�еĽ�����¼ӵ�������
    for (i = 0; i < D; i++)
    {
        if (cons[i] != NULL)
        {
            if (min == NULL)
                min = cons[i];
            else
            {
                addNode(cons[i], min);
                if ((cons[i])->key < min->key)
                    min = cons[i];
            }
        }
    }
}

/*
 * �Ƴ���С�ڵ�
 */
template <class T>
void FibHeap<T>::removeMin()
{
    if (min == NULL)
        return;

    FibNode<T>* child = NULL;
    FibNode<T>* m = min;
    // ��minÿһ������(���ӺͶ��ӵ��ֵ�)�����ӵ�"쳲������ѵĸ�����"��
    while (m->child != NULL)
    {
        child = m->child;
        removeNode(child);
        if (child->right == child)
            m->child = NULL;
        else
            m->child = child->right;

        addNode(child, min);
        child->parent = NULL;
    }

    // ��m�Ӹ��������Ƴ�
    removeNode(m);
    // ��m�Ƕ���Ψһ�ڵ㣬�����öѵ���С�ڵ�ΪNULL��
    // �������öѵ���С�ڵ�Ϊһ���ǿսڵ�(m->right)��Ȼ���ٽ��е��ڡ�
    if (m->right == m)
        min = NULL;
    else
    {
        min = m->right;
        consolidate();
    }
    keyNum--;

    delete m;
}

/*
 * ��ȡ쳲�����������С��ֵ�������浽pkey�У��ɹ�����true�����򷵻�false��
 */
template <class T>
bool FibHeap<T>::minimum(T* pkey)
{
    if (min == NULL || pkey == NULL)
        return false;

    *pkey = min->key;
    return true;
}

/*
 * �޸Ķ���
 */
template <class T>
void FibHeap<T>::renewDegree(FibNode<T>* parent, int degree)
{
    parent->degree -= degree;
    if (parent->parent != NULL)
        renewDegree(parent->parent, degree);
}

/*
 * ��node�Ӹ��ڵ�parent���������а��������
 * ��ʹnode��Ϊ"�ѵĸ�����"�е�һԱ��
 */
template <class T>
void FibHeap<T>::cut(FibNode<T>* node, FibNode<T>* parent)
{
    removeNode(node);
    renewDegree(parent, node->degree);
    // nodeû���ֵ�
    if (node == node->right)
        parent->child = NULL;
    else
        parent->child = node->right;

    node->parent = NULL;
    node->left = node->right = node;
    node->marked = false;
    // ��"node������"���ӵ�"������"��
    addNode(node, min);
}

/*
 * �Խڵ�node����"��������"
 *
 * �������У������С��Ľ���ƻ�����С�����ʣ�
 *     �����������(��������˫��������ɾ��������
 *     ����뵽����С�����ڵ��γɵ�˫��������)��
 *     Ȼ���ٴ�"���нڵ�ĸ��ڵ�"�����������ڵ�ݹ�ִ�м�����֦
 */
template <class T>
void FibHeap<T>::cascadingCut(FibNode<T>* node)
{
    FibNode<T>* parent = node->parent;
    if (parent != NULL)
    {
        if (node->marked == false)
            node->marked = true;
        else
        {
            cut(node, parent);
            cascadingCut(parent);
        }
    }
}

/*
 * ��쳲��������нڵ�node��ֵ����Ϊkey
 */
template <class T>
void FibHeap<T>::decrease(FibNode<T>* node, T key)
{
    FibNode<T>* parent;

    if (min == NULL || node == NULL)
        return;

    if (key >= node->key)
    {
        cout << "decrease failed: the new key(" << key << ") "
            << "is no smaller than current key(" << node->key << ")" << endl;
        return;
    }

    node->key = key;
    parent = node->parent;
    if (parent != NULL && node->key < parent->key)
    {
        // ��node�Ӹ��ڵ�parent�а������������node���ӵ���������
        cut(node, parent);
        cascadingCut(parent);
    }

    // ������С�ڵ�
    if (node->key < min->key)
        min = node;
}

/*
 * ��쳲��������нڵ�node��ֵ����Ϊkey
 */
template <class T>
void FibHeap<T>::increase(FibNode<T>* node, T key)
{
    FibNode<T>* child, * parent, * right;

    if (min == NULL || node == NULL)
        return;

    if (key <= node->key)
    {
        cout << "increase failed: the new key(" << key << ") "
            << "is no greater than current key(" << node->key << ")" << endl;
        return;
    }

    // ��nodeÿһ������(����������,����,...)�����ӵ�"쳲������ѵĸ�����"��
    while (node->child != NULL)
    {
        child = node->child;
        removeNode(child);               // ��child��node����������ɾ��
        if (child->right == child)
            node->child = NULL;
        else
            node->child = child->right;

        addNode(child, min);       // ��child���ӵ���������
        child->parent = NULL;
    }
    node->degree = 0;
    node->key = key;

    // ���node���ڸ������У�
    //     ��node�Ӹ��ڵ�parent���������а��������
    //     ��ʹnode��Ϊ"�ѵĸ�����"�е�һԱ��
    //     Ȼ�����"��������"
    // �������ж��Ƿ���Ҫ���¶ѵ���С�ڵ�
    parent = node->parent;
    if (parent != NULL)
    {
        cut(node, parent);
        cascadingCut(parent);
    }
    else if (min == node)
    {
        right = node->right;
        while (right != node)
        {
            if (node->key > right->key)
                min = right;
            right = right->right;
        }
    }
}

/*
 * ����쳲������ѵĽڵ�node�ļ�ֵΪkey
 */
template <class T>
void FibHeap<T>::update(FibNode<T>* node, T key)
{
    if (key < node->key)
        decrease(node, key);
    else if (key > node->key)
        increase(node, key);
    else
        cout << "No need to update!!!" << endl;
}

template <class T>
void FibHeap<T>::update(T oldkey, T newkey)
{
    FibNode<T>* node;

    node = search(oldkey);
    if (node != NULL)
        update(node, newkey);
}

/*
 * ����С��root�в��Ҽ�ֵΪkey�Ľڵ�
 */
template <class T>
FibNode<T>* FibHeap<T>::search(FibNode<T>* root, T node)
{
    FibNode<T>* t = root;    // ��ʱ�ڵ�
    FibNode<T>* p = NULL;    // Ҫ���ҵĽڵ�

    if (root == NULL)
        return root;

    do
    {
        // if (t->key == key)
        if (t->node==node)
        {
            p = t;
            break;
        }
        else
        {
            if ((p = search(t->child, node)) != NULL)
                break;
        }
        t = t->right;
    } while (t != root);

    return p;
}

/*
 * ��쳲��������в��Ҽ�ֵΪkey�Ľڵ�
 */
template <class T>
FibNode<T>* FibHeap<T>::search(T key)
{
    if (min == NULL)
        return NULL;

    return search(min, key);
}

/*
 * ��쳲����������Ƿ���ڼ�ֵΪkey�Ľڵ㡣
 * ���ڷ���true�����򷵻�false��
 */
template <class T>
bool FibHeap<T>::contains(T key)
{
    return search(key) != NULL ? true : false;
}

/*
 * ɾ�����node
 */
template <class T>
void FibHeap<T>::remove(FibNode<T>* node)
{
    T m = min->key - 1;
    decrease(node, m - 1);
    removeMin();
}

template <class T>
void FibHeap<T>::remove(T key)
{
    FibNode<T>* node;

    if (min == NULL)
        return;

    node = search(key);
    if (node == NULL)
        return;

    remove(node);
}

/*
 * ����쳲�������
 */
template <class T>
void FibHeap<T>::destroyNode(FibNode<T>* node)
{
    FibNode<T>* start = node;

    if (node == NULL)
        return;

    do {
        destroyNode(node->child);
        // ����node������nodeָ����һ��
        node = node->right;
        delete node->left;
    } while (node != start);
}

template <class T>
void FibHeap<T>::destroy()
{
    destroyNode(min);
    free(cons);
}

/*
 * ��ӡ"쳲�������"
 *
 * ����˵����
 *     node       -- ��ǰ�ڵ�
 *     prev       -- ��ǰ�ڵ��ǰһ���ڵ�(���ڵ�or�ֵܽڵ�)
 *     direction  --  1����ʾ��ǰ�ڵ���һ������;
 *                    2����ʾ��ǰ�ڵ���һ���ֵܽڵ㡣
 */
template <class T>
void FibHeap<T>::print(FibNode<T>* node, FibNode<T>* prev, int direction)
{
    FibNode<T>* start = node;

    if (node == NULL)
        return;
    do
    {
        if (direction == 1)
            cout << setw(8) << node->key << "(" << node->degree << ") is " << setw(2) << prev->key << "'s child" << endl;
        else
            cout << setw(8) << node->key << "(" << node->degree << ") is " << setw(2) << prev->key << "'s next" << endl;

        if (node->child != NULL)
            print(node->child, node, 1);

        // �ֵܽڵ�
        prev = node;
        node = node->right;
        direction = 2;
    } while (node != start);
}

template <class T>
void FibHeap<T>::print()
{
    int i = 0;
    FibNode<T>* p;

    if (min == NULL)
        return;

    cout << "== 쳲������ѵ���ϸ��Ϣ: ==" << endl;
    p = min;
    do {
        i++;
        cout << setw(2) << i << ". " << setw(4) << p->key << "(" << p->degree << ") is root" << endl;
        p->node->show();
        print(p->child, p, 1);
        p = p->right;
    } while (p != min);
    cout << endl;
}

template <class T>
T FibHeap<T>::get_min()
{
    if (min == NULL)
        return NULL;
    return min->node;
}
#endif