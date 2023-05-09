/*Modify reserve to use the vector_base solution ( a RAII example ).
This example also includes iterators.
This version includes an input and an output operator (>> and <<) for
vector.*/

#include<iostream>
#include<algorithm>

using namespace std;

//--------------------------------------------------------------------

namespace v
{ 

// vector_base is used for manage memory.

template<typename T,typename A>
struct vector_base
{
    A alloc;
    T* elem;
    int sz;
    int space;                      // Ammount of allocated space.

    vector_base(const A& a, int n)
        : alloc{a}, elem{alloc.allocate(n)}, sz{n}, space{n} {} 

    ~vector_base() {}
};

//--------------------------------------------------------------------

template<typename T, typename A = allocator<T>>
class vector : private vector_base<T,A>
{
    A alloc;
    int sz;
    T* elem;
    int space;

public:

    using size_type = unsigned long;
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;

    vector() : sz(0), elem{nullptr}, space{0} {}
    explicit vector(int s, T val = T()) : sz{s},
        elem{alloc.allocate(s)}, space{s}, vector_base<T,A>{alloc,s}
    {
        for(int i=0; i<sz; ++i) alloc.construct(&elem[i],val);
    }

    vector(const vector&);                  // Copy constructor.
    vector& operator=(const vector&);       // Copy assignment.
  
    vector(vector&&);                       // Move constructor.
    vector& operator=(vector&&);            // Move assignment.

    ~vector() { delete[] elem; }            // Destructor. 

    T& operator[](int n){ return elem[n]; }
    const T& operator[](int n) const { return elem[n]; }

    int size() const{ return sz; }          // The current size.
    int capacity() const { return space; }

    void reserve(int newalloc);             // Growth.
    void push_back(const T& d);

    // resize is placed here because default arguments cannot be added
    // to an out-of-line definition of a class template member.
    void resize(int newsize, T val = T())
    {
        reserve(newsize);
        for(int i=sz; i<newsize; ++i) alloc.construct(&elem[i],val);
        for(int i = newsize; i < sz; ++i) alloc.destroy(&elem[i]);
        sz = newsize;
    }

    iterator begin() {return elem;}
    const iterator begin() const {return elem;}
    iterator end() { return elem + sz; }
    const iterator end() const { return elem + sz; }
    T* back(){ return elem + (sz-1); }

    iterator insert(iterator p, const T& val);
    iterator erase(iterator p);
};

//--------------------------------------------------------------------

// Copy constructor.

template<typename T, typename A>
vector<T,A>::vector(const vector& arg) : sz{arg.sz}
             ,elem{alloc.allocate(arg.sz)}, space{arg.sz}
             , vector_base<T,A>{alloc,arg.capacity()}
{
    for(int i=0; i<sz; ++i) alloc.construct(&elem[i],arg[i]);
}

// Copy assignment.

template<typename T, typename A>
vector<T,A>& vector<T,A>::operator=(const vector& a)
{
    if(this == &a) return *this;    // Self-assignment, no work needed.

    if(a.sz <= space)                  // No need for new allocation.
    {
        for(int i=0; i<a.sz; ++i) alloc.construct(&elem[i],a[i]);
        for(int i=a.sz; i<space; ++i) alloc.destroy(&elem[i]);
        sz = a.sz;
        return *this;
    }

    T* p = alloc.allocate(a.sz);
    for(int i=0; i<a.sz; ++i) alloc.construct(&p[i],a[i]);
    for(int i=0; i<space; ++i) alloc.destroy(&elem[i]);
    alloc.deallocate(elem,space);
    space = sz = a.sz;
    elem = p;

    return *this;
}


//--------------------------------------------------------------------

// Move constructor.

template<typename T, typename A>
vector<T,A>::vector(vector&& a) : sz{a.sz}, elem{a.elem}
             , space{a.space}, vector_base<T,A>{alloc,a.space}
{
    a.space = a.sz = 0;
    a.elem = nullptr;
}

// Move assignment.

template<typename T, typename A>
vector<T,A>& vector<T,A>::operator=(vector&& a)
{
    for(int i=0; i<space; ++i) alloc.destroy(&elem[i]);
    alloc.deallocate(elem,space);
    elem = a.elem;
    sz = a.sz;
    space = a.space;
    
    a.elem = nullptr;
    a.space = a.sz = 0;

    return *this;
}

//--------------------------------------------------------------------

// Growth.

template<typename T, typename A>
void vector<T,A>::reserve(int newalloc)
{
    if(newalloc <= capacity()) return;
    vector_base<T,A> b{this->alloc,newalloc};
    uninitialized_copy(this->elem,this->elem+size(),b.elem);
    for(int i=0; i<size(); ++i)
        this->alloc.destroy(&this->elem[i]);

    elem = b.elem;
    space = b.space;
    
    b.elem = nullptr;
    b.space = b.sz = 0;
}

template<typename T, typename A>
void vector<T,A>::push_back(const T& val)
{
    if(space == 0) reserve(8);
    else if(sz == space) reserve(2*space);
    this->alloc.construct(&this->elem[sz],val);
    ++sz;
}

//--------------------------------------------------------------------

// delete() and insert() functons using iterators.

template<typename T, typename A>
typename vector<T,A>::iterator vector<T,A>::erase(iterator p)
{
   if(p == end()) return p;
   for(auto pos = p+1; p!=end(); ++p)  *(pos-1) = *pos;
   alloc.destroy(&elem[sz-1]);

   --sz;
   return p;
}

template<typename T, typename A>
typename vector<T,A>::iterator vector<T,A>::insert(iterator p, const T& val)
{
   int index = p-begin();
   if(size() == capacity()) 
      reserve(size()==0 ? 8 : 2*size());

   // First copy last element into uninitialized space:
   alloc.construct(elem+sz, *back());

   ++sz;
   iterator pp = begin()+index;
   for(auto pos = end()-1; pos!=pp; --pos)
      *pos = *(pos-1);

   *pp = val;
   return pp;
}

//--------------------------------------------------------------------

} // Close namespace "v".

//--------------------------------------------------------------------

// Input (>>) and output (<<) operations.

template<typename T, typename A>
ostream& operator<<(ostream& os, const v::vector<T,A>& v)
{
    for(T x : v) os << x << ' ';
    return os;
}

template<typename T, typename A>
istream& operator>>(istream& is, v::vector<T,A>& v)
{
    T val;
    int sz;
    char ch1, ch2, ch3;
    is >> ch1 >> sz >> ch2 >> val >> ch3;
    if(!is) return is;

    if(ch1!='{' || ch2!=',' || ch3!='}')
    {
        is.clear(ios_base::failbit);
        return is;
    }

    v = v::vector<T,A>{sz,val};
    return is;
}

//--------------------------------------------------------------------

// This function checks the Move function.

template<typename T, typename A>
v::vector<T,A> test(int n)
{
    v::vector<int> t{n,n};
    return t;
}

//--------------------------------------------------------------------

int main()
{
    // Checking copy and push_back.

    v::vector<int> t1{10,15};                   
    t1.push_back(300);
    cout << "\n\n\tChecking copy and push_back.\n\t" << t1 
         << "\n\n\tInput the vector again {sz,val}: ";

    cin >> t1;
    t1.erase(t1.end()-1);
    cout << "\n\n\tPrinting and Deleting the last element.\n\t" << t1
         << "\n\n\t";

    v::vector<int> t2{5,7};
    t2.push_back(100);
    cout << "Checking copy and push_back.\n\t" << t2 << "\n\n\t";
    t2.insert(t2.begin() +3, 14);

    cout << "Inserting the number 14.\n\t" << t2 << "\t";
    
    return 0;
}    

//--------------------------------------------------------------------
