//
//  RelationalTable.hpp
//  Assignment4
//
//  Created by Hazel Zhao on 2023-04-03.
//
#include <iostream>
using namespace std;
#include <vector>


#ifndef RelationalTable_hpp
#define RelationalTable_hpp

 
class RelationalTable
{
private:
    vector<string> fieldName;
    vector<pair<string,vector<string>>>rows;
    int capacity;
    const double loadThreshold;
    int num_of_insertion;
    
public:
    RelationalTable(double loadThreshold = 0.5);
    RelationalTable(const string attNames[] , int size , double loadThreshold );
    void addRow(const string values[] , int size);
    vector<string> removeRow(const string& pkValue);
    void setValue(const string& pkValue , const string& fieldName , const string& fieldValue);
    string getValue(const string& pkValue , const string& field);
    void addField(const string& fieldName);//done debugging
    void removeField(const string& fieldName);
    int getSize() const;
    bool isEmpty(pair<string , vector<string>>cell);
    void rehash();
    vector<string>getFieldNames() const;
     
    
};

#endif /* RelationalTable_hpp */
