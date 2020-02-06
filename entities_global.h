#ifndef BQC_ENTITIES_GLOBAL_H
#define BQC_ENTITIES_GLOBAL_H 1

/*c++-libs*/
#include <iostream>
#include <list>
#include <iterator>
#include <cassert> // for assert()
#include <memory>
#include <cstdlib> 
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
#include <iterator>
#include <cassert>

#include <json/json.h> //fedora
#include <mysql/mysql.h>  
#include <boost/algorithm/string.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time.hpp>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include <odb/core.hxx>
#include <odb/nullable.hxx>
#include <odb/lazy-ptr.hxx>
#include <odb/boost/lazy-ptr.hxx>
//#include <odb/tr1/memory.hxx>

#if defined BUILD_MODELS
//#define BQC_API Q_DECL_EXPORT
#else
//#define BQC_API Q_DECL_IMPORT
#endif
using namespace std;

//Foward Declarations
namespace dbo
{
	class IEntity;
	class IEntityField;
	class IHelperCC;
	//type mapping per type basis
	typedef std::vector<uint8_t> CBlob; 
	typedef uint64_t  CUint64;
	typedef uint64_t  CUint32;
	typedef bool  CBoolean;
	typedef std::string  CString; 
	typedef std::string  CEnum; 
	typedef boost::gregorian::date  CDate; 
	typedef boost::posix_time::ptime  CDateTime; 
	typedef boost::posix_time::time_duration  CTime; 
	typedef double  CDouble; 
	typedef float  CFloat; 
};

#endif
