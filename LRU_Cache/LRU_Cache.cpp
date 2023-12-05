/* Gen Digital test: LRU Cache.  */

#include <iostream>
#include <list>
#include <map>
#include <type_traits>

using namespace std;

//--------------------------------------------------------------------

template<typename T_key, typename T_val>
class LRU_cache
{
    // Alias declarations.
    using list_iterator = typename list< pair<T_key,T_val> >::iterator;
                                                                     // ** Please skip these comments** Maximum LRU space memory space (Consultar en web para elegir un buen valor).
                                                                     // unsigned const int max_size = 10000;

    // Private attributes.

    unsigned int capacity;                                           // Capacity of the LRU cache.
    int item_counter;                                                // Counts items stored in memory.
    list< pair<T_key,T_val> > value_list;                            // Uses pairs to store both keys and values.
    map<T_key, list_iterator> key_map;                               // Stores the keys and the iterators of each link in the list.
    list_iterator it_value_list;                                     // Allows new items to be added to the list. Iterators are stored in the map to retrieve the list items.


    // Private methods.

    void add_item(T_key,T_val);                                      // Add a new item to the LRU cache.
    void evict_item(T_key, T_val);                                   // Evicts the least recently used key.
    void update_most_recently_used(list_iterator);                   // Update the item most recently used.
    void save_MRU_values(unsigned const int);

public:
  
    LRU_cache(unsigned int sz, T_val default_val = T_val()) : capacity{sz},
    item_counter{0}
    {
        value_list.resize(capacity, make_pair(T_key(), default_val));
        it_value_list = value_list.begin();
                                                                     // ** Please skip these comments** Guaranteed to be less than and equallity comparable. if (función en la documentación T_key == true) through exception;???
                                                                     // Size validations. if (size < 0 || size > max_size) through exception;
    }


    // Public methods.

    int cache_capacity() const { return capacity; }                  // Memory status.
    int item_count() const { return item_counter; }
    bool is_there_capacity() const
        {return capacity-item_counter? true : false;}
    bool key_found(T_key key) const
        {return key_map.find(key) != key_map.end()? true : false;}

    list_iterator put(T_key, T_val);                                 // Adds a new pair to LRU cache memory.
    list_iterator get(T_key);                                        // Returns the iterator of the linked list containing the <key,value> pair.
    list_iterator del(T_key);                                        // Returns iterator pointing to the element that followed the last element erased.
    void resize(unsigned const int);                                 // Changes the capacity of the LRU cache.
    void clear();                                                    // Deletes the content of the LRU cache, i.e., the content of both the map and the linked list is deleted.
    void print() const;                                              // Prints the content of both the list and the map.

    ~LRU_cache(){ clear();}

};

//--------------------------------------------------------------------

// Adds a new pair to LRU cache memory.

template<typename T_key, typename T_val>
typename list< pair<T_key,T_val> >::iterator LRU_cache<T_key,T_val>::put(T_key key, T_val val)
{

    if(key_found(key) || capacity==0)                                // Discards the key and value.
        return value_list.end();                                     // Returns an iterator to end of the linked list.
  
    if(is_there_capacity()) 
        add_item(key,val);
    else
        evict_item(key,val);

    return key_map.at(key);                                          // Returns an iterator to an existing or new element of the linked list.

}

//--------------------------------------------------------------------

// Add a new item to the LRU cache.

template<typename T_key, typename T_val>
void LRU_cache<T_key,T_val>::add_item(T_key key, T_val val)
{
    *it_value_list = pair<T_key, T_val>(key, val);                   // The iterator of the link is updated by introducing a pair. This pair contains the new key and the new value. 
    key_map.insert(pair<T_key, list_iterator>(key, it_value_list));  // Inserts a new pair to the map using the new key and the iterator of the new link.
    ++it_value_list;
    ++item_counter;
}

//--------------------------------------------------------------------

// Evicts the least recently used key.

/* The LRU and the MRU items are stored at the beginning and the end,
 respectively. */

template<typename T_key, typename T_val>
void LRU_cache<T_key,T_val>::evict_item(T_key key, T_val val)
{
    value_list.push_back(*value_list.begin());                       // Adds a new link at the end using the content of the LRU item.
    list_iterator it_new_link = --value_list.end();                  // This iterator refers to the new link of the list.

    key_map.erase((*it_new_link).first);                             // Erases the pair that contains the key of the LRU item. The iterator of the new link lets to recover this key. 
    key_map.insert(pair<T_key, list_iterator>(key, it_new_link));    // Inserts a new pair to the map using the new key and the iterator of the new link.

    *it_new_link = pair<T_key, T_val>(key, val);                     // MRU item: the iterator of the new link is updated by introducing a pair. This pair contains the new key and the new value. 
    value_list.erase(value_list.begin());                            // Erases the LRU item.
}

//--------------------------------------------------------------------

// Returns the iterator of the linked list containing the <key,value> pair.

template<typename T_key, typename T_val>
typename list< pair<T_key,T_val> >::iterator LRU_cache<T_key,T_val>::get(T_key key)
{
    if(!key_found(key))                                              // If the key doesn't exist, returns an iterator to end of the linked list.
        return value_list.end();
    
    list_iterator it_key_found = key_map.at(key);                    // The next block defines a new MRU element.
    if(!is_there_capacity())                                         // If the memory is full, the found element chages its position to the end of the linked list.
    {
        value_list.push_back(*it_key_found);
        key_map[key] = --value_list.end();
    }
    else                                                             // If the memory isn't full, the found item is placed after the others.
    {
        it_value_list =  value_list.insert(it_value_list, *(it_key_found));
        key_map[key] = it_value_list;
        ++it_value_list;
    }
    value_list.erase(it_key_found);

    return key_map.at(key);
}

//--------------------------------------------------------------------

template<typename T_key, typename T_val>
typename list< pair<T_key,T_val> >::iterator LRU_cache<T_key,T_val>::del(T_key key)
{
    if(!key_found(key))
        return value_list.end();                                     // If the key doesn't exist, returns an iterator to end of the linked list.
    
    value_list.push_back(make_pair(T_key(), T_val()));
    list_iterator it_elem_after_deleted = value_list.erase(key_map.at(key));  // Returns iterator pointing to the element that followed the last element erased.
    key_map.erase(key);                                                       // Deletes the key from the map.
    --item_counter;

    it_value_list = value_list.begin();
    advance(it_value_list, item_counter);                            // The reference iterator is updated.

    return it_elem_after_deleted;
}

//--------------------------------------------------------------------

// Changes the capacity of the LRU cache.

template<typename T_key, typename T_val>
void LRU_cache<T_key,T_val>::resize(unsigned const int new_size)
{
    if(new_size == capacity)    return;

    if(new_size >= item_counter)
    {
        value_list.resize(new_size, make_pair(T_key(),T_val()));
        it_value_list = value_list.begin();
        advance(it_value_list,item_counter);                         // The reference iterator is updated.
    }
    else
    {
        save_MRU_values(new_size);
        key_map.clear();

        item_counter = new_size;
        it_value_list = value_list.begin();
        advance(it_value_list,item_counter);                         // The reference iterator is updated.

        for(auto it = value_list.begin() ; it != it_value_list; ++it) // Map reconstruction
            key_map.insert(make_pair((*it).first,it));
    }

    capacity = new_size;
}

//--------------------------------------------------------------------

template<typename T_key, typename T_val>
void LRU_cache<T_key,T_val>::save_MRU_values(unsigned const int new_size)
{   
    value_list.resize(item_counter); value_list.reverse();
    value_list.resize(new_size);     value_list.reverse();
}

//--------------------------------------------------------------------

template<typename T_key, typename T_val>
void LRU_cache<T_key,T_val>::clear()
{
    resize(0);
    cout << "\n\nClearing.........";
}

//--------------------------------------------------------------------

// Prints the content of both the list and the map.

/* it_map.second: it is an iterator of value_list.
   *(it_map.second): The content of the iterator is dereferenced. It
   contains a pair<Tkey,T_val>. */

template<typename T_key, typename T_val>
void LRU_cache<T_key,T_val>::print() const
{

    cout << "\n\n\n\tList content:";
    for(auto it_list : value_list)
        cout << "\n\tkey: " << it_list.first << "\tvalue: " << it_list.second;

    cout << "\n\n\tMap content:";
    for (auto it_map : key_map)
        cout << "\n\tkey: " << it_map.first 
             << "\tIterator<pair(key,value)>: (" 
             << (*(it_map.second)).first
             << "," << (*(it_map.second)).second << ")";

}

//--------------------------------------------------------------------

int main()
{
  
    // Testing put(key,val), get(key), del(key), clear(), resize(size).

    cout << "\n\nInitializing LRU cache:";
    LRU_cache<int,string> lru_cache(8,"");
    lru_cache.print();

    cout << "\n\n\n\n\nFilling the LRU cache using put(key,value):";
    lru_cache.put(1,"Camilo");      lru_cache.print();
    lru_cache.put(9,"Víctor");      lru_cache.print();
    lru_cache.put(6,"Magda");       lru_cache.print();
    lru_cache.put(4,"Córdula");     lru_cache.print();
    lru_cache.put(5,"Caroline");    lru_cache.print();
    lru_cache.put(-1,"Natalina");   lru_cache.print();
    lru_cache.put(0,"Jorge");       lru_cache.print();

    
    cout << "\n\n\n\nget(9): the linked list is updated.";
    lru_cache.get(9);               lru_cache.print();

    cout << "\n\n\n\nget(9) again: no changes";
    lru_cache.get(9);               lru_cache.print();

    cout << "\n\n\n\nput(6,\"Magda\") again: no changes";
    lru_cache.put(6,"Magda");       lru_cache.print();
    
    cout << "\n\n\n\nget(1): the linked list is updated.";
    lru_cache.get(1);               lru_cache.print();

    cout << "\n\n\n\ndel(9): deletes (9,Víctor) and the linked list is updated.";
    lru_cache.del(9);               lru_cache.print();



    cout << "\n\n\n\nclear(): deletes all elements, capacity = 0.";
    lru_cache.clear();              lru_cache.print();



    cout << "\n\n\n\nput(4,\"Córdula\") again: no space";
    lru_cache.put(4,"Córdula");     lru_cache.print();
    
    cout << "\n\n\n\nget(1): no space.";
    lru_cache.get(1);               lru_cache.print();


    cout << "\n\n\n\ndel(9): no space.";
    lru_cache.del(5);               lru_cache.print();



    cout << "\n\n\n\nresize(6): pairs(0,\"\"), capcity = 6.";
    lru_cache.resize(6);            lru_cache.print();



    cout << "\n\n\n\nput(20,\"Luis\").";
    lru_cache.put(20,"Luis");       lru_cache.print();
    
    cout << "\n\n\n\nput(14,\"Johan\").";
    lru_cache.put(14,"Johan");      lru_cache.print();
    

    cout << "\n\n\n\nget(4): the linked list is updated.";
    lru_cache.get(4);               lru_cache.print();

    cout << "\n\n\n\ndel(20): deletes (20,Luis) and the linked list is updated.";
    lru_cache.del(20);
    lru_cache.print();

    cout << "\n\n\n\nput(5,\"Caroline\").";
    lru_cache.put(5,"Caroline");    lru_cache.print();

    
    cout << "\n\n\n\nresize(2): keeps the MRUs.";
    lru_cache.resize(2);            lru_cache.print();


    cout << "\n\n\n\nget(5) again: no changes";
    lru_cache.get(5);               lru_cache.print();

    cout << "\n\n\n\ndel(5): deletes (5,Caroline) and the linked list is updated.";
    lru_cache.del(5);               lru_cache.print();

    cout << "\n\n\n\nput(11,\"Guillermo\").";
    lru_cache.put(11,"Guillermo");  lru_cache.print();


    cout << "\n\n\n\nput(12,\"Alfredo\").";
    lru_cache.put(12,"Alfredo");    lru_cache.print();

    cout << "\n\n\n\nput(13,\"Fermín\").";
    lru_cache.put(13,"Fermín");     lru_cache.print();

    cout << "\n\n\n\ndel(12): deletes (12,Alfredo) and the linked list is updated.";
    lru_cache.del(12);              lru_cache.print();

    cout << "\n\n\n\nput(12,\"Alfredo\") again.";
    lru_cache.put(12,"Alfredo");    lru_cache.print();

    cout << "\n\n\tItem count: " << lru_cache.item_count();
    cout << "\n\n\tCapacity: " << lru_cache.cache_capacity();


    //------------------------------------

    cout << "\n\n\n\n\n------------------------------------------------";
    cout << "\n\n\n\n\nUsing pairs<char,float>(key,value):";
    LRU_cache<char,float> lru_cache_2(3);
    lru_cache_2.print();

    cout << "\n\n\n\n\nFilling the LRU cache using put(key,value):";
    lru_cache_2.put('a',1.7);       lru_cache_2.print();
    lru_cache_2.put('z',8.6);       lru_cache_2.print();
    lru_cache_2.put('t',23.2);      lru_cache_2.print();

    cout << "\n\n\n\nget(\'z\'): the linked list is updated.";
    lru_cache_2.get('z');           lru_cache_2.print();

    cout << "\n\n\n\nput(\'g\',100).";
    lru_cache_2.put('g',100.4);     lru_cache_2.print();

    cout << "\n\n\n\ndel(\'t\'): deletes (\'t\',23) and the linked list is updated.";
    lru_cache_2.del('t');           lru_cache_2.print();


    //------------------------------------

    cout << "\n\n\n\n\n------------------------------------------------";
    cout << "\n\n\n\n\nUsing pairs<string,float>(key,value):";
    LRU_cache<string,float> lru_cache_3(3);
    lru_cache_3.print();

    cout << "\n\n\n\n\nFilling the LRU cache using put(key,value):";
    lru_cache_3.put("England",5.9);   lru_cache_3.print();
    lru_cache_3.put("Colombia",7.8);  lru_cache_3.print();
    lru_cache_3.put("France",2.6);    lru_cache_3.print();

    cout << "\n\n\n\nget(\"England\"): the linked list is updated.";
    lru_cache_3.get("England");     lru_cache_3.print();

    cout << "\n\n\n\nput(\"Germany\",100).";
    lru_cache_3.put("Germany",8.6);   lru_cache_3.print();

    cout << "\n\n\n\ndel(\"France\"): deletes (\"France\",2) and the linked list is updated.";
    lru_cache_3.del("France");           lru_cache_3.print();


    //------------------------------------

    cout << "\n\n\n\n\n------------------------------------------------";
    cout << "\n\n\n\n\nUsing pairs<string,char>(key,value):";
    LRU_cache<string,char> lru_cache_4(3,'z');
    lru_cache_4.print();

    cout << "\n\n\n\n\nFilling the LRU cache using put(key,value):";
    lru_cache_4.put("England",'E');   lru_cache_4.print();
    lru_cache_4.put("Colombia",'C');  lru_cache_4.print();
    lru_cache_4.put("France",'F');    lru_cache_4.print();

    cout << "\n\n\n\nget(\"England\"): the linked list is updated.";
    lru_cache_4.get("England");     lru_cache_4.print();

    cout << "\n\n\n\nput(\"Germany\",\'G\').";
    lru_cache_4.put("Germany",'G');   lru_cache_4.print();

    cout << "\n\n\n\ndel(\"France\"): deletes (\"France\",\'F\') and the linked list is updated.";
    lru_cache_4.del("France");           lru_cache_4.print();

    //------------------------------------

    cout << "\n\n\n\n\n------------------------------------------------";
    cout << "\n\n\n\n\nUsing pairs<char,bool>(key,value):";
    LRU_cache<char,bool> lru_cache_5(3,true);
    lru_cache_5.print();

    cout << "\n\n\n\n\nFilling the LRU cache using put(key,value):";
    lru_cache_5.put('a',false);     lru_cache_5.print();
    lru_cache_5.put('z',true);      lru_cache_5.print();
    lru_cache_5.put('t',false);     lru_cache_5.print();

    cout << "\n\n\n\nget(\'z\'): the linked list is updated.";
    lru_cache_5.get('z');           lru_cache_5.print();

    cout << "\n\n\n\nput(\'g\',false).";
    lru_cache_5.put('g',false);     lru_cache_5.print();

    cout << "\n\n\n\ndel(\'t\'): deletes (\'t\',false) and the linked list is updated.";
    lru_cache_5.del('t');           lru_cache_5.print();

    //------------------------------------

  return 0;
}

//--------------------------------------------------------------------
