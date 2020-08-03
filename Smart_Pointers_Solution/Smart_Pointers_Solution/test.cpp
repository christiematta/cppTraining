#include "pch.h"
#include "Unique_Pointer.h"
#include "Shared_Pointer.h"
#include <vector>

using namespace smartpointers;

TEST(sharedPointers, counterWorks)
{
	MySharedPointer<int> a(new int(10));
	MySharedPointer<int> b(a);
	MySharedPointer<int> c(a);
	MySharedPointer<int> d(a);
	MySharedPointer<int> e = make_shared<int>(67);
}

TEST(sharedPointers, sharedPointersGlobalTest)
{
	MySharedPointer<int> a0;
	{
		MySharedPointer<int> a = make_shared<int>(10);

		{
			MySharedPointer<int> a2(a);

			EXPECT_EQ(*a2, 10);
			a0 = a2;
			EXPECT_EQ(*a0, 10);
		}

		{
			MySharedPointer<int> a3 = a0;
			EXPECT_EQ(*a3, 10);
		}
	}

	EXPECT_EQ(*a0, 10);
}

TEST(sharedPointers, copyConstructorWorks) {

	//MySharedPointer<int> a(new int(1));
	//a.get();
	//MySharedPointer<int> b(a);
	 

	//ASSERT_EQ(a.get(),b.get());
}

TEST(sharedPointers, destructorWorks) {

	MySharedPointer<int> b(new int(1));

	int* ptr1 = nullptr;
	{
		MySharedPointer<int> ptr = make_shared<int>(3);
		ptr1 = ptr.get();
		ASSERT_EQ(*ptr1, *ptr);
	}

	ASSERT_NE(*ptr1, 3);
}


TEST(sharedPointers, makeUniqueWorksWithExample) {
	MySharedPointer<Child1> child1Default = make_shared<Child1>();
	MySharedPointer<Child1> child1With2Params = make_shared<Child1>(27, "Christie");

	MySharedPointer<Child1> child1With1Params = make_shared<Child1>("Ryan");
	//MyUniquePointer<Child1> child1With1Paramgfgs = make_unique<Child1>("Ryan");

}

TEST(sharedPointers, makeUniqueWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MySharedPointer<std::vector<int>> ptr = make_shared<std::vector<int>>(vec);
}

TEST(sharedPointers, releaseWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MySharedPointer<std::vector<int>> ptr = make_shared(vec);
	std::vector<int>* vec1 = ptr.release();

	ASSERT_EQ(vec1->size(), 4);
	ASSERT_EQ(vec1->at(0), 1);
}

TEST(sharedPointers, resetWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MySharedPointer<std::vector<int>> ptr = make_shared(vec);
	ptr.reset();
	ASSERT_TRUE(!ptr);
}

TEST(sharedPointers, boolOperatorWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MySharedPointer<std::vector<int>> ptr = make_shared(vec);
	ptr.getCounter();
	MySharedPointer<std::vector<int>> ptr2 = std::move(ptr);
	ptr2.getCounter();
	ASSERT_TRUE(ptr2);
	ASSERT_FALSE(ptr);
}

TEST(sharedPointers, negationOperatorWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MySharedPointer<std::vector<int>> ptr = make_shared(vec);
	MySharedPointer<std::vector<int>> ptr2 = std::move(ptr);
	ASSERT_FALSE(!ptr2);
	ASSERT_TRUE(!ptr);
}

TEST(sharedPointers, indirectionOperatorWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MySharedPointer<std::vector<int>> ptr = make_shared(vec);
	MySharedPointer<std::vector<int>> ptr2 = std::move(ptr);
	std::vector<int> vec2 = *ptr2;
	ASSERT_EQ(vec2.size(), 4);
}

TEST(sharedPointers, getWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MySharedPointer<std::vector<int>> ptr = make_shared(vec);
	ASSERT_EQ(ptr->size(), 4);
	MySharedPointer<std::vector<int>> ptr2 = std::move(ptr);
	ASSERT_EQ(ptr.get(), nullptr);
	ASSERT_EQ(ptr2.get()->size(), 4);
}

TEST(sharedPointers, moveWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MySharedPointer<std::vector<int>> ptr = make_shared(vec);
	//MyUniquePointer<std::vector<int>> ptr2(ptr);
	//MyUniquePointer<std::vector<int>> ptr2=ptr;
	ASSERT_EQ(ptr->size(), 4);
	MySharedPointer<std::vector<int>> ptr2 = std::move(ptr);
	ASSERT_EQ(ptr2->size(), 4);

}
////////////////////////////////////////
TEST(pointers, destructorWorks) {

	std::unique_ptr<int> a(new int(1));
	std::unique_ptr<int> a34 =std::make_unique<int>(32);
	MyUniquePointer<int> b(new int(1));

	int* ptr1 = nullptr ;
	{
		MyUniquePointer<int> ptr =  make_unique<int>(3);
		ptr1 = ptr.get();
		ASSERT_EQ(*ptr1, *ptr);
	}

	ASSERT_NE(*ptr1, 3);
}


TEST(pointer, defaultConstructor)
{
	MyUniquePointer<int> myInt;
	EXPECT_EQ(myInt, false);
	EXPECT_EQ(myInt.get(), nullptr);
}

TEST(pointers, makeUniqueWorksWithExample) {
	MyUniquePointer<Child1> child1Default = make_unique<Child1>();
	MyUniquePointer<Child1> child1With2Params = make_unique<Child1>(27, "Christie");

	MyUniquePointer<Child1> child1With1Params = make_unique<Child1>("Ryan");
	//MyUniquePointer<Child1> child1With1Paramgfgs = make_unique<Child1>("Ryan");

}

TEST(pointers, makeUniqueWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MyUniquePointer<std::vector<int>> ptr = make_unique<std::vector<int>>(vec);
}

TEST(pointers, releaseWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MyUniquePointer<std::vector<int>> ptr = make_unique(vec);
	std::vector<int> * vec1 = ptr.release();

	ASSERT_EQ(vec1->size(),4);
	ASSERT_EQ(vec1->at(0), 1);
}

TEST(pointers, resetWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MyUniquePointer<std::vector<int>> ptr = make_unique(vec);
	ptr.reset();
	ASSERT_TRUE(!ptr);
}

TEST(pointers, boolOperatorWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MyUniquePointer<std::vector<int>> ptr = make_unique(vec);
	MyUniquePointer<std::vector<int>> ptr2 = std::move(ptr);
	ASSERT_TRUE(ptr2);
	ASSERT_FALSE(ptr);
}

TEST(pointers, negationOperatorWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MyUniquePointer<std::vector<int>> ptr = make_unique(vec);
	MyUniquePointer<std::vector<int>> ptr2 = std::move(ptr);
	ASSERT_FALSE(!ptr2);
	ASSERT_TRUE(!ptr);
}

TEST(pointers, indirectionOperatorWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MyUniquePointer<std::vector<int>> ptr = make_unique(vec);
	MyUniquePointer<std::vector<int>> ptr2 = std::move(ptr);
	std::vector<int> vec2 = *ptr2;
    ASSERT_EQ(vec2.size(), 4);
}

TEST(pointers, getWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MyUniquePointer<std::vector<int>> ptr = make_unique(vec);
	ASSERT_EQ(ptr->size(), 4);
	MyUniquePointer<std::vector<int>> ptr2 = std::move(ptr);
	ASSERT_EQ(ptr.get(), nullptr);
	ASSERT_EQ(ptr2.get()->size(), 4);
}

TEST(pointers, moveWorks) {
	std::vector<int> vec = { 1,45,6,7 };
	MyUniquePointer<std::vector<int>> ptr = make_unique(vec);
	//MyUniquePointer<std::vector<int>> ptr2(ptr);
	//MyUniquePointer<std::vector<int>> ptr2=ptr;
	ASSERT_EQ(ptr->size(), 4);
	MyUniquePointer<std::vector<int>> ptr2 = std::move(ptr);
	ASSERT_EQ(ptr2->size(),4);
	
}