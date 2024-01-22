#ifndef TODOITEM_H
#define TODOITEM_H

#include <string>
using namespace std;

class ToDoListItem {

private:
    int index;
    string taskname;
    string location;

public:
    ToDoListItem(int index, string taskname, string location);
    ~ToDoListItem();
    string getTaskname();

};

#endif // TODOITEM_H
