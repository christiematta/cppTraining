#include "pch.h"
#include "Unique_Pointer.h"
#include <vector>

using namespace smartpointers;

TEST(pointers, releaseWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MyUniquePointer<std::vector<int>> ptr(vec);
	MyUniquePointer<std::vector<int>> ptr2 = std::move(ptr);
	std::vector<int>  vec1 = ptr2.release();
	int a = vec1.size();
	ASSERT_EQ(vec.size(),4);
	ASSERT_EQ(vec.at(0), 1);
}

TEST(pointers, resetWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MyUniquePointer<std::vector<int>> ptr(vec);
	MyUniquePointer<std::vector<int>> ptr2 = std::move(ptr);
	ptr.reset();
	ASSERT_TRUE(!ptr);
	ptr2.reset();
	ASSERT_TRUE(!ptr2);
}

TEST(pointers, boolOperatorWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MyUniquePointer<std::vector<int>> ptr(vec);
	MyUniquePointer<std::vector<int>> ptr2 = std::move(ptr);
	ASSERT_TRUE(ptr2);
	ASSERT_FALSE(ptr);
}

TEST(pointers, negationOperatorWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MyUniquePointer<std::vector<int>> ptr(vec);
	MyUniquePointer<std::vector<int>> ptr2 = std::move(ptr);
	ASSERT_FALSE(!ptr2);
	ASSERT_TRUE(!ptr);
}

TEST(pointers, indirectionOperatorWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MyUniquePointer<std::vector<int>> ptr(vec);
	MyUniquePointer<std::vector<int>> ptr2 = std::move(ptr);
	std::vector<int> vec2 = *ptr2;
    ASSERT_EQ(vec2.size(), 4);
}

TEST(pointers, getWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MyUniquePointer<std::vector<int>> ptr(vec);
	ASSERT_EQ(ptr->size(), 4);
	MyUniquePointer<std::vector<int>> ptr2 = std::move(ptr);
	ASSERT_EQ(ptr.get(), nullptr);
	ASSERT_EQ(ptr2.get()->size(), 4);
}

TEST(pointers, moveWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MyUniquePointer<std::vector<int>> ptr(vec);
	//MyUniquePointer<std::vector<int>> ptr2(ptr);
	//MyUniquePointer<std::vector<int>> ptr2=ptr;
	ASSERT_EQ(ptr->size(), 4);
	MyUniquePointer<std::vector<int>> ptr2 = std::move(ptr);
	ASSERT_EQ(ptr2->size(),4);
	
}