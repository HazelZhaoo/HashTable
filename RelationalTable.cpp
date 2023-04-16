#include "RelationalTable.hpp"
#include <vector>
#include <functional>
#include <math.h>
#include <algorithm>
using namespace std;

//creating an empty table with the name of each column first
RelationalTable::RelationalTable(const string attNames[] , int size , double threshold = 0.5):loadThreshold(threshold),capacity(97)
{
    vector<pair<string, vector<string>>> new_row(capacity, make_pair("", vector<string>()));
    rows = new_row;

    for(int i = 0 ; i < size ; i++)
    {
        fieldName.push_back(attNames[i]);
    }
}

void RelationalTable::addRow(const string values[] , int size)
{
    if(size != fieldName.size()) //handle the exception for the size
        throw runtime_error("Size have to match the size of fieldname");
    
    size_t index = hash<string>{}(values[0]) % 97; //convert into a hash key
    vector<string> str; //a vector to put the remainings
    
    for(int i = 1 ; i < size ; i++)
    {
        str.push_back(values[i]);
    }
    pair<int,vector<string>> element(index , str); //put them in a pair
    
    double load_factor = num_of_insertion / 97; //keep track of the load factor
    
    if(isEmpty(rows[index]))
    {
        rows[index] = element;
        num_of_insertion++;
    }
    else if(load_factor >= loadThreshold)
    {
        rehash();
    }
    else
    {
        for(int i = 1 ; i < capacity ; i++) //quadratic probing//
        {
            int power = pow(i , 2);
            int new_index = power % 97;
            rows[new_index] = element;
            num_of_insertion++;
        }
    }
}

bool RelationalTable::isEmpty(pair<string,vector<string>>cell)
{
    return cell.first.empty();
}

void RelationalTable::rehash()
{
    int new_size = capacity* 2;
    vector<pair<string , vector<string>>> new_table(new_size);
    
    for(int i = 0 ; i < rows.size() ; i++)
    {
        size_t new_index = hash<string>{}(rows[i].first) % new_size;
        new_table[new_index] = rows[i] ;
    }
    capacity = new_size;
    rows = new_table;
    
}

vector<string> RelationalTable::getFieldNames() const
{
    return fieldName;
}

string RelationalTable::getValue(const string& pkValue , const string& field)
{
    pair<string , vector<string>> return_str;
    
    //use a lambda expression to find the key
    auto it = find_if(rows.begin() , rows.end() ,[pkValue](const auto& rows){return rows.first == pkValue;});
    
    //if the key exist in the rows vector , assign it//
    if(it != rows.end())
        return_str = *it;
 
 
    int index = 0; //find the index of the fieldname to return the right value
    for(auto it = fieldName.begin() ; it != fieldName.end(); it++)
    {
        index++;
        if(*it == field)
            break;
    }
    return return_str.second[index];
}

vector<string> RelationalTable:: removeRow(const string& pkValue)
{
     vector<string> remove_value;
    auto it = find_if(rows.begin() , rows.end() ,
                      [pkValue](const auto& rows){return rows.first == pkValue;});
    
    if(it != rows.end())
        remove_value = it-> second;
    
    rows.erase(it);
    return remove_value;
}

void RelationalTable::setValue(const string& pkValue , const string& fieldName , const string& fieldValue)
{
    auto cell = getValue(pkValue, fieldName);
    for(auto it : rows)
    {
        if(it.first == cell)
        {
            it.second.push_back(fieldValue);
        }
    }
}

void RelationalTable::addField(const string& fieldName)
{
    for(auto it : this->fieldName)
    {
        if(it == fieldName)
            throw runtime_error("The name already exist");
    }
    this->fieldName.push_back(fieldName);
}

void RelationalTable::removeField(const string& fieldName)
{
    
    int index = 0;
    for(auto it : this->fieldName)
    {
        index++;
        if(it == fieldName)
            break;
    }
    for(auto it = rows.begin() ; it != rows.end(); it++)
    {
       it->second.erase(it->second.begin() + index -1);
    }
    
    this->fieldName.erase(this->fieldName.begin() + index -1);
}

int RelationalTable::getSize() const
{
    return static_cast<int>(rows.size());
}

//overload ostream iterator to print the hash table//

 
