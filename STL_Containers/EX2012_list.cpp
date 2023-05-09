/*Representation of the standard library list. This representation has
the operations we have for vector ( except subscripting ), insert, e-
rase and iterators.*/

#include<iostream>

using namespace std;

//--------------------------------------------------------------------

template<typename Elem>
struct Link
{
    Link* prev;         // Previous link.
    Link* succ;         // Successor (next) link.
    Elem val;

    Link(const Elem& v, Link* p = nullptr, Link* s = nullptr) :
        val{v}, prev{p}, succ{s} {}
};

//--------------------------------------------------------------------

namespace l
{

// list_base is used for manage memory.

template<typename Elem,typename A>
struct list_base
{
    A alloc;
    Link<Elem>* elem;
    int sz;
    int space;                      // Ammount of allocated space.

    list_base(const A& a, int n)
        : alloc{a}, elem{alloc.allocate(n)}, sz{n}, space{n} {} 

    ~list_base() {}
};

//--------------------------------------------------------------------

template<typename Elem, typename A = allocator<Link<Elem>>>
class list : private list_base<Elem,A>
{
    A alloc;
    int sz;
    Link<Elem>* elem;
    int space;
    Link<Elem>* bg;             // Points to the first element.
    Link<Elem>* ed;             // Points to the last element.*/

    Link<Elem>* initial_linker(Link<Elem>* p, Link<Elem>* n);

public:
    
    list() : sz{0}, elem{nullptr}, space{0} {}
    explicit list(int s, Elem val = Elem()) : sz{s},
             elem{alloc.allocate(s)}, space{s},
             list_base<Elem,A>{alloc,s}
    {
        for(int i=0; i<=sz; ++i)
        {
            alloc.construct(&elem[i], Link{++val});
            if(i>0) initial_linker(&elem[i-1], &elem[i]);
        }

        // Initializing both the pointers to the first and last
        // elements.
        bg = elem;
        ed = elem + sz;
    }

    class iterator;                   // Member type: iterator.
    iterator begin() { return bg; }   // It to first element.
    iterator end() { return ed; }   // It to one beyond last element.
    int size() const{ return sz; }       // The current size.
    int capacity() const { return space; }

    // Growth.
    void reserve(int newalloc);
    iterator insert(iterator p, const Elem& v); // Insert v after p.
    void push_back(const Elem& v);          // Insert v at end.
    void push_front(const Elem& v);         // Insert v at front.

    // Removing.
    iterator erase(iterator p);         // Remove p from the list.
    void pop_front() { erase(bg); }     // Remove the first element.
    void pop_back() { erase(--ed); }    // Remove the last element.

    Elem& front() { return *begin(); }     // The first element.
    Elem& back() { return *(--end()); }    // The last element.
    
    ~list(){ alloc.deallocate(elem,space); }
};

//--------------------------------------------------------------------

// Links n after p.

template<typename Elem, typename A>
Link<Elem>* list<Elem,A>::initial_linker(Link<Elem>* p, Link<Elem>* n)
{
    if(n == nullptr) return p;
    if(p == nullptr) return n;

    n->prev = p;
    if(p->succ) p->succ->prev = n;
    n->succ = p->succ;
    p->succ = n;

    return n;
}

//--------------------------------------------------------------------

// Member type: iterator.

template<typename Elem, typename A>
class list<Elem,A>::iterator
{
    Link<Elem>* curr;       // Current link.

public:
    iterator(Link<Elem>* p) : curr{p}{}

    iterator& operator++(){ curr = curr->succ; return *this; }
    iterator& operator--(){ curr = curr->prev; return *this; }
    Elem& operator*(){ return curr->val; } // Get value (dereference.)
    Link<Elem>* previous() {return curr->prev;}
    Link<Elem>* succesor() {return curr->succ;}
    Link<Elem>* current() {return curr;}

    bool operator==(const iterator& b){ return curr == b.curr; }
    bool operator!=(const iterator& b){ return curr != b.curr; }
};

//--------------------------------------------------------------------

// erase() and insert() functons using iterators.

template<typename Elem, typename A>
typename list<Elem,A>::iterator list<Elem,A>::erase(iterator p)
{
   if(p == end()) return p;

   // Removing the beginning if necessary.
   if(p == begin())
   {
       bg = p.succesor();               // The begin is updated.
       p.succesor()->prev = nullptr;
       p.current()->succ = nullptr;
       alloc.destroy(p.current());
       return ++p;
   }
    
   // Verifying if the element is in the list.
   iterator it = begin();
   while(it != p)
   {
       ++it;
       if(it == end())
       {
            cout << "\n\n\tThe element was not found.\n\t";
            return p;
       }
   }

   // Removing the element from the list.
   if(p.succesor()) { p.succesor()->prev = p.previous(); }
   if(p.previous()) { p.previous()->succ = p.succesor(); } 
   alloc.destroy(p.current());

   return ++p;
}

//--------------------------------------------------------------------

// Growth.

template<typename Elem, typename A>
void list<Elem,A>::reserve(int newalloc)
{
    if(newalloc <= capacity()) return;
    list_base<Elem,A> b{this->alloc,newalloc};
    uninitialized_copy(this->elem,this->elem+size(),b.elem);

    // Linking the new elements of the list.
    for(int i=0; i<=sz; ++i)
        if(i>0) initial_linker(&b.elem[i-1],&b.elem[i]);

    // Destroying the old elements.
    for(int i=0; i <= size(); ++i)
        this->alloc.destroy(&this->elem[i]);

    // Deallocating the current memory.
    this->alloc.deallocate(elem,space);

    // Updating the members.
    bg = elem = b.elem;
    ed = elem + size();
    space = b.space;

    b.elem = nullptr;
    b.space = b.sz = 0;
}

template<typename Elem, typename A>
void list<Elem,A>::push_back(const Elem& v)
{
    if(space == 0) reserve(8);
    else if(sz == space) reserve(2*space);

    // Adding the new value in end().
    this->elem[sz].val = v;
    
    // Constructing a new element for end().
    ++sz;
    this->alloc.construct(&this->elem[sz],Link{v});
    initial_linker(&this->elem[sz-1],&this->elem[sz]);

    ed = this->elem + sz;
}

template<typename Elem, typename A>
void list<Elem,A>::push_front(const Elem& v)
{
    if(space == 0) reserve(8);
    else if(sz == space) reserve(2*space);

    // Constructing a new element for end().
    ++sz;
    this->alloc.construct(&this->elem[sz],Link{v});

    // Reservando un espacio en el frente de la lista.
    // Los valores se mueven a otras posiciones de la memoria.
    list_base<Elem,A> b{this->alloc,space};
    uninitialized_copy(this->elem,this->elem+size(),b.elem + 1);
    
    // Destroying the old elements.
    for(int i=0; i <= size(); ++i)
        this->alloc.destroy(&this->elem[i]);

    // Deallocating the current memory.
    this->alloc.deallocate(elem,space);
    
    // Updating pointers both at the beginning and at the ending.
    bg = elem = b.elem;
    ed = elem + size();

    // Creating the element in the front.
    this->alloc.construct(&this->elem[0],Link{v});
    for(int i=0; i<=sz; ++i)
        if(i>0) initial_linker(&elem[i-1], &elem[i]); 

    b.elem = nullptr;
    b.space = b.sz = 0;
}

}   // End of namespace l.

//--------------------------------------------------------------------

int main()
{
    l::list<int> lt{10,0};

    cout << "\n\n\tList content: \n\t"; 
    for(auto it = lt.begin(); it != lt.end(); ++it) 
        cout << *it << ' ';

    lt.pop_back();
    cout << "\n\n\tList content: \n\t"; 
    for(auto it = lt.begin(); it != lt.end(); ++it) 
        cout << *it << ' ';

    // Testing pop_front(), pop_back(), front(), and back().
    lt.pop_back();
    lt.pop_front();

    cout << "\n\n\tThe first element is: " << lt.front()
         << "\n\tThe last element is: " << lt.back() << "\n\t";

    cout << "\n\n\tList content: \n\t"; 
    for(auto it = lt.begin(); it != lt.end(); ++it) 
        cout << *it << ' ';

    // Testing push_back() and push_front() functions.
    cout << "\n\n\tTesting push_back()\n\t";
    lt.push_back(23);
    auto it = lt.begin();
    for(; it != lt.end(); ++it) 
        cout << *it << ' ';
    
    cout << "\n\n\tTesting push_front()\n\t";
    lt.push_front(437);
    it = lt.begin();
    for(; it != lt.end(); ++it) 
        cout << *it << ' ';
    
    cout << "\n\n\n\tWarning: When the list is copied to a new space"
         << "\n\tof memory, it is necessary to delete the elements "
         << "\n\tpreviously erased by either erase(), pop_back"
         << "\n\tor pop_front().";

    return 0;
}

//--------------------------------------------------------------------
