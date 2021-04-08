#include <gtest/gtest.h>

#include "kt-serial/details/basic_traits.h"

TEST(BasicTraits, ChecksConstants)
{
    using namespace KtSerial::Traits;

    EXPECT_TRUE(BoolConstant<true>::value);
    EXPECT_FALSE(BoolConstant<false>::value);
    EXPECT_TRUE(BoolConstant<std::true_type::value>::value);
    EXPECT_FALSE(BoolConstant<std::false_type::value>::value);

    EXPECT_EQ(IntConstant<2>::value, 2);
    EXPECT_EQ(IntConstant<-100>::value, -100);
    EXPECT_EQ(IntConstant<std::true_type::value>::value, 1);
    EXPECT_EQ(IntConstant<std::false_type::value>::value, 0);
}

TEST(BasicTraits, LogicalOperations)
{
    using namespace KtSerial::Traits;
    
    const bool conjunction1 = Conjunction<1, 1, 1, 1, 1>::value;
    EXPECT_TRUE(conjunction1);

    const bool conjunction2 = Conjunction<1, 0, 1, 0>::value;
    EXPECT_FALSE(conjunction2);

    const bool conjunction3 = Conjunction<false>::value;
    EXPECT_FALSE(conjunction3);

    const bool conjunction4 = Conjunction<true>::value;
    EXPECT_TRUE(conjunction4);

    const bool disjunction1 = Disjunction<1, 0, 0, 0>::value;
    EXPECT_TRUE(disjunction1);

    const bool disjunction2 = Disjunction<0, 0, 0>::value;
    EXPECT_FALSE(disjunction2);

    const bool disjunction3 = Disjunction<false>::value;
    EXPECT_FALSE(disjunction3);

    const bool disjunction4 = Disjunction<true>::value;
    EXPECT_TRUE(disjunction4);
}

TEST(BasicTraits, PoinerTypes)
{
    using namespace KtSerial::Traits;

    const bool sameType = std::is_same<typename RemovePointer<int>::type, int>::value;
    EXPECT_TRUE(sameType);

    const bool ptrRemoved = std::is_same<typename RemovePointer<int*>::type, int>::value;
    EXPECT_TRUE(ptrRemoved);

    const bool refRemoved = std::is_same<typename RemovePointer<int&>::type, int>::value;
    EXPECT_TRUE(refRemoved);

    const bool refPtrRemoved = std::is_same<typename RemovePointer<int*&>::type, int>::value;
    EXPECT_TRUE(refPtrRemoved);

    const bool constTypePtrRemoved = std::is_same<typename RemovePointer<const int*>::type, const int>::value;
    EXPECT_TRUE(constTypePtrRemoved);

    const bool constPtrRemoved = std::is_same<typename RemovePointer<int* const>::type, int>::value;
    EXPECT_TRUE(constPtrRemoved);

    const bool constPtrConstTypeRemoved = std::is_same<
        typename RemovePointer<const int* const>::type, const int
    >::value;
    EXPECT_TRUE(constPtrConstTypeRemoved);

    const bool constIntToVoid = std::is_same<VoidPointerKeepingConst<const int*>, const void*>::value;
    EXPECT_TRUE(constIntToVoid);

    const bool intToVoid = std::is_same<VoidPointerKeepingConst<int*>, void*>::value;
    EXPECT_TRUE(intToVoid);

    const bool voidToVoid = std::is_same<VoidPointerKeepingConst<void*>, void*>::value;
    EXPECT_TRUE(voidToVoid);
}

