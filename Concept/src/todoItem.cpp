#include "todoItem.h"
#include <string>
using namespace std;

ToDoListItem::ToDoListItem(int index, string taskname, string location) {
    this->index = index;
    this->taskname = taskname;
    this->location = location;
}

ToDoListItem::~ToDoListItem() {

}

string ToDoListItem::getTaskname() {
    return this->taskname;
}
