# HashTable


A relational database is a collection of "tables" that are sets of tuples sharing the same attributes. For example, a college database includes the table "Student" which is a set of tuples in the form of: (StudentID, FirstName, LastName, etc.). Every student in the college has one record in the student table which is a row (tuple) in the table. Data fields create the columns of the table and every row of the table is uniquely identified by a set of data fields that make the "primary key" of the table. For example, the field "StudenID" in the "Student" table is the primary key of the table because no two students have the same value for this field. The primary keys of tables are used to access and retrieve the records stored in a table. 
Implement the type "RelationalTable" including the members specified below.


Attributes:

vector<string> fieldNames;
This attribute stores the field names of the table, e.g., "StudentID", "FirstName", etc. The first string in this object is the primary key's field name. For the sake of simplicity, it is assumed that the primary keys include one field only.
vector<pair<string, vector<string>> rows;
This attribute is a hash table including pairs that map a primary key to a vector including the rest of the tuple. This hash table uses the STL hash functor to generate hash codes and uses the quadratic probing algorithm to handle collisions.
int capacity;
This attribute identifies the maximum capacity of the table; i.e. the maximum size of the vector "rows". 
const double loadThreshold;
This attribute identifies the load threshold of the hash table for rehashing. If the load factor exceeds this value, the table is rehashed into a table of double size. The default load threshold is 0.5, but this value can be set at the instantiation time.
    
    
Methods:
    
RelationalTable(double loadThreshold = 0.5);
The no-arg constructor creates an empty table, including no data.Use 97 as the size of the table.
RelationalTable(const string attNames[], int size, double loadThreshold = 0.5);
A parameterized constructor accepts an array including the field names of the table as an input parameter and creates an empty table including the field names listed in "attNames". The name of the primary key is in the first cell of the array. Note that the size of the attribute "fieldNames" is always equal to the size of the vectors included in the pairs in the vector "rows".
void addRow(const string values[], int size);
This method adds a row of values to the table or updates the existing row. The size of the array must match the size of the attribute names of the table or the method throws an exception. It is assumed that the primary key is in the first cell of the array. If a row with the specified primary key does not exist in the table, the row will be added to the table, otherwise, the existing row will be updated. The load factor of the table is checked after adding a new row and if required rehashing takes place. The size of the table doubles when rehashing.
vector<string> removeRow(const string& pkValue); 
This method accesses removes the row associated with the key passed in "pkValue". If the key does not exist in the table, an empty vector is returned, otherwise, the vector corresponding to the input key is returned.
void setValue(const string& pkValue, const string& fieldName, const string& fieldValue);
This method accesses the record associated with the key "pkValue" and sets the value of the field identified by the name "fieldName" to "fieldValue".  If the record or the field name does not exist, the method throws an exception.
string getValue(const string& pkValue, const string& fieldName);
This method accesses the record associated with the key "pkValue" and returns the value of the field identified by the name "fieldName". If the record or the field name does not exist, the method throws an exception.
void addField(const string& fieldName);
This method adds a new field called "fieldName" to the table. If the name exists in the table's list of fields, an exception is thrown, otherwise, the name is added and its value is set to a null string in all the existing rows in the table.
void removeField(const string& fieldName);
This method removes the field called "fieldName" from the table. If the name does not exist in the table's list of fields, an exception is thrown, otherwise, the name and its values in all the table's rows are removed from the table. 
int getSize();
This method returns the number of rows in the table.
