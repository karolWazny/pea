#include "gtest/gtest.h"

#include "../structure_templates_lib/linked_list_lib/LinkedList.h"

LinkedList<int> function(){
    auto list = LinkedList<int>();
    list.pushBack(3);
    list.pushBack(1);
    list.pushBack(4);
    list.pushBack(1);
    list.pushBack(5);
    return list;
}

TEST(ListSuite, canReturnListFromFunction){
    auto list = function();
    ASSERT_EQ(list.toString(), "[3, 1, 4, 1, 5]");
}