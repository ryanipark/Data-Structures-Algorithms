#include "htable.h"
#include "entry.h"

#define N1 10  // num of decimal digits
#define N2 26  // num of upper-case letters

// Hash function, you may NOT modify this function
int HT::hash(const string &s) {
  int n = (N2 * N1) * (s[0] - 'A') + N1 * (s[1] - 'A') + (s[2] - '0');

  return n % hsize;
}
// You will complete the code below ...
//---------------------------------------------
/*
 Ryan Park z1940877
 Assignment 10
 CSCI 340, Section 3

 I certify that this is my own work and where appropriate an
 extension of the starter code provided for the assignment.
*/
//---------------------------------------------
/* Constructor
 *
 *@param refrence to const unsigned hs
 *@return none
 */
HT::HT(const unsigned &hs) 
{
  // construct HT according to size
  hsize = hs;
  hTable.resize(hs);
}
/* Destructor
 *
 *@param none
 *@return none
 */
HT::~HT() 
{
  // Free memory in list container
  while(!hTable.empty())
  {
    hTable.pop_back();
  }
  // Then delete each index of vector entry
  for(unsigned i = 0; i < pTable.size(); i++)
  {
    delete pTable[i];
  }

}
/*
 * Utility struct for checking
 *  and comparing keys using find_if
 */
struct check
{
  string compare;
  // conversion constructor accepting std::string
  check(const string& x) : compare(x) {}
  // operator() to return in find_if on case
  bool operator()(const Entry& e)
  {
    return compare == e.key;
  }
};
/* insert entry into Hash Table
 *
 *@param refrence to const Entry e
 *@return none
 */
void HT::insert(const Entry &e) 
{
  // First hash function the entry
  int entry = hash(e.key);
  list<Entry> &l = hTable[entry];

  // If entry e.key matches in the list l duplicate and exit
  if(find_if(l.begin(), l.end(),check(e.key)) != l.cend())
  {
      cout << " not inserted - duplicate key!!!\n";
      return;
  }
  // Otherwise you insert it, then push that list into ptable
  else
  {
      l.push_front(e);
      Entry *temp = new Entry(e.key,e.desc,e.num);
      pTable.push_back(temp);
      cout << " entry =  " << std::left << setw(3) <<  entry << endl;
  }

}
/* search for a key in the table
 *
 *@param refrence to const string s
 *@return none
 */
void HT::search(const string &s)
{
  // Hash function the search
  int searchFor = hash(s);
  list<Entry> &l = hTable[searchFor];
  
  // Set an iterator equal to find_if, searching for s == find.key
  auto i = find_if(l.begin(), l.end(),
  [s](Entry find){return s == find.key;}  );

  // If i points to the end it was not found
  if(i == l.cend())
  {
    cout << " not in table!!\n";
  }
  // Otherwise derefrence and print the find
  else
  {
    cout << " ==> number:"<< setw(5) << i->num << " - item:" << i->desc << endl;
  }

}
/* Print contents of the has table accordingly
 *
 *@param none
 *@return none
 */
void HT::hTable_print() 
{
  cout << endl;
  // Loop through has table
  for(size_t i = 0; i < hTable.size(); i++)
  {
    // Loop through each list in the hash table.
    list<Entry>& l = hTable[i];

    for(auto j = l.begin();j != l.end(); j++)
    {
       cout << std::left << setw(4) << i << ":"
       << setw(7) << j->key << "- "
       << setw(7) << j->num << "-  "
       << j->desc << endl;
    }
  }
}
/* Print contents of the has table accordingly from A-Z
 *
 *@param none
 *@return none
 */
void HT::pTable_print() 
{
  // Sort ptable
  sort(pTable.begin(), pTable.end(), [](Entry*p, Entry*q)
  {
    return p->key < q->key;
  });

  for(auto i = pTable.begin();i != pTable.end(); i++)
  {
    // Output with refout formatting
    cout << std::right << setw(6) << (*i)->key << "  - " 
    << setw(5) << (*i)->num << "  -  "
    << setw(2) << (*i)->desc << endl;
  }
}