CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

CMAKE_POLICY(SET CMP0015 NEW) 

INCLUDE_DIRECTORIES(
	"${CMAKE_SOURCE_DIR}/entities"
	"${CMAKE_SOURCE_DIR}/entities/src"
	"${CMAKE_SOURCE_DIR}/entities/generated"
	"${CMAKE_SOURCE_DIR}/base"
)
	
SET(LINUX_OS OS_UBUNTU)  # enable C++11 standard	

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -fPIC -g -lpthread -DDATABASE_MYSQL -D${LINUX_OS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/include/mysql -I/usr/include/jsoncpp -L/usr/lib/odb") # link to odb and mysql
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--no-undefined -Wl,--start-group") #fix cyclic dependencies 

MACRO(ODB_GENERATE header)
    SET(cxxFile "${CMAKE_SOURCE_DIR}/entities/generated/${header}-odb.cxx")
    SET(hxxFile "${CMAKE_SOURCE_DIR}/entities/generated/${header}-odb.hxx")
    SET(ixxFile "${CMAKE_SOURCE_DIR}/entities/generated/${header}-odb.ixx")
    SET(sqlFile "${CMAKE_SOURCE_DIR}/entities/generated/${header}.sql")

    SET(ODB_GENERATED_FILES ${cxxFile} ${hxxFile} ${ixxFile} ${sqlFile})

    ADD_CUSTOM_COMMAND(
        OUTPUT ${ODB_GENERATED_FILES}
        COMMAND mkdir -p ${CMAKE_SOURCE_DIR}/entities/generated && odb -o ${CMAKE_SOURCE_DIR}/entities/generated/ --std c++11 -I/usr/include/jsoncpp -d mysql  -p boost/date-time -D${LINUX_OS} --generate-query --generate-schema
                --show-sloc ${CMAKE_SOURCE_DIR}/entities/src/${header}.hpp  -I${CMAKE_SOURCE_DIR}/entities -I${CMAKE_SOURCE_DIR}/entities/src -I${CMAKE_SOURCE_DIR}/base
        DEPENDS ${CMAKE_SOURCE_DIR}/entities/src/${header}.hpp
        COMMENT "Generate database support code for ${header}.hpp")

ENDMACRO()

ADD_LIBRARY(entities 
	Entities.cpp
    OdbCC.cpp
	 
	src/user.hpp
	src/user_group.hpp 
	#cxx
    
	generated/user-odb.cxx
	generated/user_group-odb.cxx
	 
 )

TARGET_LINK_LIBRARIES(entities 
      "${CMAKE_BINARY_DIR}/base/libbase.a"
      odb-mysql odb odb-boost boost_regex boost_date_time boost_system boost_filesystem jsoncpp log4cxx
)

 
ODB_GENERATE(user)
ODB_GENERATE(user_group) 
