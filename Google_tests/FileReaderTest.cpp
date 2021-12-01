#include "gtest/gtest.h"

#include "../program/file/AtspFileHandler.h"

TEST(FileReaderSuite, ReadCorrectFileTest){
    auto reader = AtspFileHandler();
    auto values = reader.fromFile("testfile.atsp");
    size_t correctValues[] = {5,
                              INT32_MAX, 9999, 1, 9999, 9999,
                              9999, INT32_MAX, 9999, 9999, 1,
                              9999, 1, INT32_MAX, 9999, 9999,
                              1, 9999, 9999, INT32_MAX, 9999,
                              9999, 9999, 9999, 1, INT32_MAX};
    for(int i = 0; i < 26; i++){
        ASSERT_EQ(correctValues[i], values[i]);
    }
}
