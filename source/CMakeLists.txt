cmake_minimum_required(VERSION 3.20)
project(source)

set(CMAKE_CXX_STANDARD 11)

add_executable(HelloWorld main.cpp)

add_executable(Link "Unit1/Link/link1.cpp" Unit1/Link/link2.cpp)

add_executable(C_Struct0 "Unit1/Struct/struct0.c")
add_executable(C_Struct1 "Unit1/Struct/struct1.c")
add_executable(C_Struct2 "Unit1/Struct/struct2.c")

add_executable(C_Customization "Unit2/Class Flexible Demo/complex_c.c")
add_executable(C_PlusPlus_Customization "Unit2/Class Flexible Demo/complex_cplus.cpp")

add_executable(Demo0 Unit2/Stock/stock0.h Unit2/Stock/stock0.cpp Unit2/Stock/demo0.cpp)
add_executable(Demo1 Unit2/Stock/stock1.h Unit2/Stock/stock1.cpp Unit2/Stock/demo1.cpp)
add_executable(Demo2 Unit2/Stock/stock2.h Unit2/Stock/stock2.cpp Unit2/Stock/demo2.cpp)
add_executable(Demo3 Unit2/Stock/stock2.h Unit2/Stock/stock2.cpp Unit2/Stock/demo3.cpp)
add_executable(Const0 Unit2/Constant/constant.h Unit2/Constant/demo.cpp Unit2/Constant/const_object.h Unit2/Constant/const_object.cpp)

add_executable(Operator1 Unit3/Operator/mytime1.h Unit3/Operator/mytime1.cpp Unit3/Operator/demo1.cpp)
add_executable(Operator2 Unit3/Operator/mytime2.h Unit3/Operator/mytime2.cpp Unit3/Operator/demo2.cpp)
add_executable(Friend Unit3/Operator/myfriend.h Unit3/Operator/myfriend.cpp Unit3/Operator/demo3.cpp)
add_executable(Output Unit3/Practice/output.h Unit3/Practice/output.cpp Unit3/Practice/vector.h Unit3/Practice/vector.cpp Unit3/Practice/demo.cpp)
add_executable(TypeConversion Unit3/TypeConversion/stone.h Unit3/TypeConversion/stone.cpp Unit3/TypeConversion/demo.cpp)

add_executable(DynamicMemory Unit4/StringBad.h Unit4/StringBad.cpp Unit4/String.cpp Unit4/String.h Unit4/demo.cpp)
add_executable(PositionNew Unit4/position_new.cpp)
add_executable(ATMQueue Unit4/client.h Unit4/client.cpp Unit4/atm.cpp Unit8/Theory/main.cpp)

add_executable(Extends Unit5/main.cpp Unit5/person.h Unit5/person.cpp Unit5/Brass.h Unit5/Brass.cpp)

add_executable(CodeReuse Unit6/main.cpp Unit6/Contains.h Unit6/PrivateExtend.h Unit6/MultipleInheritance.h Unit6/ClassTemplate.h)

add_executable(FriendClass Unit7/Friend.h Unit7/Friend.cpp Unit7/main.cpp)

add_executable(NoException Unit8/NoException/error.cpp)
add_executable(Exception Unit8/Exception/Exception.h Unit8/Exception/main.cpp)
add_executable(Theory Unit8/Theory/Demo.h Unit8/Theory/main.cpp)
add_executable(ExceptionSTDClass Unit8/ExceptionSTDClass/main.cpp)

add_executable(RTTI Unit9/RTTI.h Unit9/main.cpp)

add_executable(STL Unit10/smart_ptr.h Unit10/main.cpp)