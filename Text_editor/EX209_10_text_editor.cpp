/*A simple text editor.
6. Write a find-and-replace operation for Documents.
8. Define a function that counts the number of characters in a 
Document.
9. Define a function that counts the number of words in a document. 
provide two versions: 1. Word as "a whitespace-separated sequence of
characters". 2. Word as "a sequence of consecutive alphabetic
characters".
10. Version of the word-counting program where the user can specify
the set of whitespace characters.
*/

#include<iostream>
#include<vector>
#include<list>

using namespace std;
using Line = vector<char>;

//--------------------------------------------------------------------

// Keep track of line and character position within a line.

class Text_iterator
{
    list<Line>::iterator ln;
    Line::iterator pos;

public:
    // Start the iterator at line ll's character position pp:
    Text_iterator(list<Line>::iterator ll, Line::iterator pp)
                 : ln{ll}, pos{pp} {}

    char& operator*(){ return *pos; }
    Text_iterator& operator++();

    bool operator==(const Text_iterator& other) const
        { return ln == other.ln && pos == other.pos; }
    bool operator!=(const Text_iterator& other) const
        { return !(*this == other); }

    list<Line>::iterator line() const { return ln; }
    Line::iterator position() const { return pos; }
};

Text_iterator& Text_iterator::operator++()
{
    ++pos;
    if(pos == (*ln).end())      // vector<char>'s final.
    {
        ++ln;
        pos = (*ln).begin();
    }

    return *this;
}

//--------------------------------------------------------------------

struct Document
{
    list<Line> line;
    Document() { line.push_back(Line{}); }

    // First character of first line.
    Text_iterator begin()
        { return Text_iterator(line.begin(), (*line.begin()).begin());}

    // One beyond the last character of the last line.

    Text_iterator end()
    {
        auto last = line.end();
        --last;
        return Text_iterator(last, (*last).end());
    }
};

/*Text_iterator Document::erase(const Text_iterator& p)
{
    auto ln = line.begin();
    auto pos = (*line.begin()).begin();

    while(Text_iterator{ln,pos} != p && Text_iterator{ln,pos} != end())
        if(*pos == '\n') { ++ln; pos = (*ln).begin(); } 
        else{ ++pos; }

    if(Text_iterator{ln,c} == end()) return p;
    pos = (*ln).erase(pos);

    if(p == end()) return p;
    p.pos = (*p.ln).erase(p.pos);
    return Text_iterator{}
}*/

//--------------------------------------------------------------------

istream& operator>>(istream& is, Document& d)
{
    for(char ch; is.get(ch);)
    {
        d.line.back().push_back(ch);    // Add the character.
        if(ch == '\n')
            d.line.push_back(Line{});
    }
    
    if(d.line.back().size()) d.line.push_back(Line{});

    return is;
}

//--------------------------------------------------------------------

void print(Document& d)
{
    for(auto p : d) cout << p;
}

void erase_line(Document& d, int n)
{
    if(n<0 || d.line.size()-1<=n) return;
    auto p = d.line.begin();
    advance(p,n);
    d.line.erase(p);
}

//--------------------------------------------------------------------

bool match(Text_iterator p, Text_iterator last, const string& s)
{
    for(char c:s)
    {
        if(c != *p || p == last)    return false;
        ++p;
    }
    return true;
}

Text_iterator find_txt(Text_iterator first, Text_iterator last,
                       const string& s)
{
    if(s.size() == 0)   return last;
    char first_char = s[0];

    while(true)
    {
        auto p = find(first, last, first_char);
        if(p == last || match(p,last,s)) return p;
        first = ++p;
    }
}

//--------------------------------------------------------------------

// Find and replace function.

Text_iterator find_replace(Document& d, const string& s_goal,
                           const string& s_rep)
{
    // Searching the string (s_goal).
    Text_iterator first = d.begin();
    Text_iterator last = d.end();
    auto p = find_txt(first, last, s_goal);

    if(p == last) { return p; }

    // Deleting the string (s_goal).
    auto ln = p.line();
    auto pos = p.position();

    for(char c : s_goal)
        if(*pos == '\n') { ++ln; pos = (*ln).begin(); }
        else pos = (*ln).erase(pos);

    // Replacing the string (s_goal changes to s_rep).
    for(int i = s_rep.size()-1; i >= 0; --i)
        if(s_goal[i] == '\n')
            {
                --ln;   // Decreasing a line.
                pos = (*ln).end() -1; // Placing pos on the lasr elem.
                pos = (*ln).insert(pos,s_rep[i]);
            } 
        else
            { 
                pos = (*ln).insert(pos,s_rep[i]);
            }

    return p;
}

//--------------------------------------------------------------------

// Number of characters function.

int char_number(Document& d)
{
    Text_iterator ti = d.begin();
    Text_iterator last = d.end();
    int char_counter{0};

    while(ti != last) { ++char_counter; ++ti; }

    return char_counter;
}

// Word as "a whitespace-separated sequence of characters".

int words_whitespace(Document& d)
{
    Text_iterator ti = d.begin();
    Text_iterator last = d.end();
    int word_counter{0};

    while(ti != last)
    {
        if(isspace(*ti)) ++word_counter;
        ++ti;
    }

    return word_counter;
}

// Word as "a sequence of consecutive alphabetic characters".

int words_alphabetic(Document& d)
{
    Text_iterator ti = d.begin();
    Text_iterator last = d.end();
    int word_counter{0};
   
    // alpha lets to control the word_counter variable.
    bool alpha;
    if(isalpha(*ti)) alpha = true;
    else alpha = false;

    while(ti != last)
    {
        if(alpha)
        {
            while(isalpha(*ti)) ++ti;
            ++word_counter;
            alpha = false;
        }
        
        if(!alpha)
        {
            while(ti != last && !(isalpha(*ti))) ++ti;
            alpha = true;
        }
    }

    return word_counter;
}

// Set of whitespace characters specified by the users.

bool is_whitespace(const char& c, const string& s)
{
    for(char cs : s)
        if( c == cs ) return true;

    return false;
}

int words_users_whitespaces(Document& d, const string& s)
{
    Text_iterator ti = d.begin();
    Text_iterator last = d.end();
    int word_counter{0};

    while(ti != last)
    {
        if(is_whitespace(*ti,s)) ++word_counter;
        ++ti;
    }

    return word_counter;
}

//--------------------------------------------------------------------

int main()
{
    Document d;
    cout << "\nInput the text:\n";
    cin >> d;
    cout << "\n\n";   print(d);

    auto p = find_txt(d.begin(), d.end(), "dro\ncas");
    if(p == d.end())
        cout << "\n\tNot found.\n";
    else
        cout << "\n\tString found.\n";

    //find_replace(d,"dro","test1");
    find_replace(d,"dro\nca","test1%3");
    cout << "\n\n"; print(d);

    cout << "\n\nThe number of characters is: " << char_number(d);

    cout << "\n\nWord as a whitespace-separated sequence " 
         << "of characters: " << words_whitespace(d);

    cout << "\n\nWord as a sequence of consecutive alphabetic"
         <<  " characters: " << words_alphabetic(d);

    cout << "\n\nThe user can specify the set of whitespaces: "
         << words_users_whitespaces(d," %\n") << "\n\n";

    /*erase_line(d,0);
    cout << "\nLine 0 deleted:\n";   print(d);*/

    /*vector<int> tst{1,2,3,4,5,6,7,8,9};
    auto it = tst.begin();
    it = tst.erase(it);
    cout << "\n\n\t" << *it;*/

    return 0;
}

//--------------------------------------------------------------------
