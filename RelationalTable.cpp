//fieldname = {"id" , "fname" , "lname"}
//rows      = {"123" , "hazel" , "phyu"}
//consider using the first cell/element of the array and use hash function to get the index

#include "RelationalTable.hpp"
#include <vector>
#include <functional>
#include <math.h>
using namespace std;

//creating an empty table with the name of each column first
RelationalTable::RelationalTable(const string attNames[] , int size , double threshold = 0.5):loadThreshold(threshold),capacity(97)
{
    for(int i = 0 ; i < size ; i++)
    {
        fieldName.push_back(attNames[i]);
    }
}

void RelationalTable::addRow(const string values[] , int size)
{
    if(size != fieldName.size())
        throw runtime_error("Size have to match the size of fieldname");
    
    size_t index = hash<string>{}(values[0]) % 97;
    vector<string> str;
    for(int i = 1 ; i < size ; i++)
    {
        str.push_back(values[i]);
    }
    pair<int,vector<string>> element(index , str);
    double load_factor = num_of_insertion / 97;
    
    if(isEmpty(rows[index]))
    {
        rows[index] = element;
        num_of_insertion++;
    }
    else if(load_factor >= loadThreshold)
    {
        //rehashing
        rehash();
    }
    else
    {
        for(int i = 1 ; i < capacity ; i++) //quadratic probing//
        {
            int power = pow(i , 2);
            int new_index = power % 97;
            rows[new_index] = element;
        }
    }
}

bool RelationalTable::isEmpty(pair<int, vector<string>>cell)
{
    return cell.first == 0;
}
void RelationalTable::rehash()
{
    int new_size = capacity* 2;
    vector<pair<string , vector<string>>> new_table(new_size);
    
    for(int i = 0 ; i < rows.size() ; i++)
    {
        size_t new_index = hash<string>{}(rows[i].first) % new_size;
        rows[i] = new_table[new_index];
    }
    rows = new_table;
    
}

//vector<string> RelationalTable::removeRow(const string& pkValue)//removes the row associated with the key passed in "pkValue"
//{
//    if(!rows[pkValue])
//    {
//        return vector<string> empty; //suppose to return empty vector but not done YET!
//    }
//    else
//    {
//        vector<string> row = rows[pkValue]->second;
//        auto it = begin(row);
//        for (; it < row.size(); it++)
//        {
//
//        }
//    }
//}

//int RelationalTable::getSize() const //returns the number of rowa in the table
//{
//    return rows.size();
//}
//
//void RelationalTable::setValue(const string& pkValue, const string& fieldName, const string& fieldValue)//accesses the record associated with the key "pkValue" and sets the value of the field identified by the name "fieldName" to "fieldValue"
//{
//
//// check if student id and field name exist
//    int hi =hash(pkValue);
//    int k = hi;
//    int j = 1;
//    // if record is not at the hashcode , quadratically probe until found, else throw exception
//    while((isEmpty(k) == false && getValue(k, fieldNames[1]) != pkValue) || isEmpty(k) == true){
//
//      k=(k + j^2) % capacity;
//        j++;
//
//        if (k == hi) {
//            throw runtime_error "does not exist in table";
//        }
//        else if (getValue(k, fieldNames[1]) == pkValue)
//            hi = k;
//    }
//
//    // now we have to check if the field name itself exists, but ion got no time
//
//
//
//}
