#include <stdio.h>
#include <stdlib.h>

#define _new(T,C) ((T*)malloc(C*sizeof(T)))
#define _delete free

template <class T>
struct linked_node {
    linked_node* next;
    T value;
};

template <class T>
class linked_list {
    private:
        linked_node<T>* _head;
        linked_node<T>* _tail;
        linked_node<T>* new_node(int value) {
            linked_node<T>* ret = _new(linked_node<T>, 1);
            ret->value = value;
            ret->next = NULL;
            return ret;
        }
    public:
        // linked_list()
        void init(int with_label) {
            _head = new_node(with_label);
            _tail = _head;
        }
        void push_front(T value) {
            linked_node<T>* n = new_node(value);
            n->next = _head->next;
            _head->next = n;
        }
        void push_back(T value) {
            _tail->next = new_node(value);
            _tail = _tail->next;
        }
        void remove(T value) {
            if (_head->value == value) {
                // removing head.
                void* target = _head;
                _head = _head->next;
                _delete(target);
                return;
            }
            linked_node<T>* pre = _head, *p = _head->next;
            while (p) {
                if (p->value == value) {
                    // perform remove.
                    void* target = p;
                    pre->next = p->next;
                    _delete(target);
                    return;
                }
                pre = pre->next;
                p = p->next;
            }
        }
        linked_node<T>* head() {
            return _head;
        }
};

class hash_table { 
    private:
        linked_list<int>* keys;
        int table_size;
        int (*hash_func)(int);
    public:
        // hash_table()
        void init(int table_size, int (*_hash_func)(int)) {
            this->keys = _new(linked_list<int>, table_size);
            for (int i = 0; i < table_size; i++)
                this->keys[i].init(i);
            this->hash_func = _hash_func;
            this->table_size = table_size;
        }
        // ~hash_table()
        void add(int key) {
            keys[hash_func(key)].push_front(key);
        }
        void del(int key) {
            keys[hash_func(key)].remove(key);
        }
        linked_list<int>* entries() {
            return keys;
        }
};

int main() {
    const int table_size = 10;

    hash_table t;
    t.init(table_size, [](int key) -> int {
        return key % 10;
    });

    int n, value;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        t.add(value);
    }

    int x, y;
    scanf("%d%d", &x, &y);
    t.del(x);
    t.add(y);

    linked_list<int>* keys = t.entries();
    for (int i = 0; i < table_size; i++) {
        linked_node<int>* head = keys[i].head();
        // head label.
        printf("%d", head->value);
        for (
            linked_node<int>* p = head->next;
            p;
            p = p->next) {
            printf("->%d", p->value);
        }
        printf("^\n");
    }

    return 0;
}
