/****************************************************************************
** Service
****************************************************************************/

#include <algorithm>
#include <functional>
#include <iterator>
#include <string.h>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <fstream>
#include <streambuf>
#include <malloc.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <functional>
#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <HelperCC.h>
#include <OdbCC.h> 

using namespace std;  
using namespace dbo;  
using namespace bqc;  

//Meet COdbCC

Json::Value COdbCC::toJson(const std::string& val)
{
    return Json::Value(val);
}

Json::Value COdbCC::toJson(const CBlob& val)
{ 
	std::string s;
    if(val.size()>0) {
		size_t len = val.size();
		uint8_t* uc = const_cast<uint8_t*>(val.data());
		s = std::string( reinterpret_cast<char const*>(uc), len ) ;
    }
    return Json::Value(s);
}
Json::Value COdbCC::toJson(const CUint64& val)
{
    std::string s = boost::lexical_cast<std::string>(val);
    return Json::Value(s);
}

Json::Value COdbCC::toJson(const CDouble& val)
{
    std::string s = boost::lexical_cast<std::string>(val);
    return Json::Value(s);
}
Json::Value COdbCC::toJson(const CBoolean& val)
{
    std::string s = boost::lexical_cast<std::string>(val);
    return Json::Value(s);
}
Json::Value COdbCC::toJson(const CFloat& val)
{
    std::string s = boost::lexical_cast<std::string>(val);
    return Json::Value(s);
}

Json::Value COdbCC::toJson(CDate val,const std::string& format)
{
	std::string date = ""; 
	if(!format.empty())
	{
		const std::locale fmt(std::locale::classic(),new boost::gregorian::date_facet(format.c_str()));
		std::ostringstream os;
		os.imbue(fmt);
		os << val;
		if(os.str() != "not-a-date-time"){
			date = os.str();
		}
	}
	return Json::Value(date);
}

Json::Value COdbCC::toJson(CDateTime val,const std::string& format)
{
	std::string date = ""; 
	if(!format.empty())
	{
		const std::locale fmt = std::locale(std::locale::classic(), new boost::posix_time::time_facet(format.c_str()));//e.g "%Y-%m-%d %H:%M:%S"
		std::ostringstream os;
		os.imbue(fmt);
		os << val;
		if(os.str() != "not-a-date-time"){
			date = os.str();
		}		
	}
	return Json::Value(date);
}
Json::Value COdbCC::toJson(CTime val,const std::string& format)
{
	std::string time = "";
	//[TODO]
	if(!format.empty())
	{
		const std::locale fmt = std::locale(std::locale::classic(), new boost::posix_time::time_facet(format.c_str()));//e.g "%H:%M:%S"
		std::ostringstream os;
		os.imbue(fmt);
		os << val;
		if(os.str() != "not-a-date-time"){
			time = os.str();
		}		
	}
	return Json::Value(time);
}


CUint64 COdbCC::toUint64(const Json::Value& val)
{
	std::string s = val.asString();
	if(!val.empty() && base::IHelperCC::match(s,"^\\d{1,22}$")){
		return std::stoul(s);
	} 
	return 0UL;
}

std::string COdbCC::toString(const Json::Value& val)
{
    return val.asString();
}

CDate COdbCC::toDate(const Json::Value& val)
{
	CDate null(boost::gregorian::not_a_date_time);
    std::string v = val.asString();
    if(!val.empty() && base::IHelperCC::match(v,"^\\d{4}\\-\\d{1,2}\\-\\d{1,2}$"))   //.e.g 2017-07-27
    {
        return boost::gregorian::from_simple_string(v);
    }
    return null;
}
CTime COdbCC::toTime(const Json::Value& val)
{
    CTime null(0,0,0);
    std::string s = val.asString();
    if(!val.empty() && base::IHelperCC::match(s,"^\\d{2}(:\\d{2}){1,2}$"))   //.e.g 9:01 or 9:01:33
    {
        std::vector<string> p = base::IHelperCC::split(":",s);
        int hour = atoi(p[0].c_str());
        int min = atoi(p[1].c_str());
        int sec = p.size() == 3 ? atoi(p[2].c_str()) : 0;
        return boost::posix_time::time_duration(hour,min,sec);
    }
    return null;
}
CDateTime COdbCC::toTimeStamp(const Json::Value& val)
{
	CDateTime null(boost::posix_time::not_a_date_time);
    std::string v = val.asString();
    if(!val.empty() && base::IHelperCC::match(v,"^\\d{4}\\-\\d{1,2}\\-\\d{1,2}\\s\\d{2}\\:\\d{1,2}\\:\\d{1,2}$"))   //.e.g 2017-07-27 00:00:00
    {
        return boost::posix_time::time_from_string(v);
    }
    return null;
}

CBlob COdbCC::toBlob(const Json::Value& val)
{
	if(!val.empty())
	{
		std::string s = val.asString();
		return CBlob(s.begin(), s.end());		
	}
	return CBlob();
}
CDouble COdbCC::toDouble(const Json::Value& val)
{   
	if(!val.empty())
	{
		std::string num = val.asString(); 
        return std::atof(num.c_str());		
	}
	return 0.0d;
}
CFloat COdbCC::toFloat(const Json::Value& val)
{  
    if(!val.empty())
	{
		std::string num = val.asString(); 
        return std::atof(num.c_str());		
	}
	return 0.0f;
} 
CBoolean COdbCC::toBoolean(const Json::Value& val)
{  
    return val.asBool();
}
CEnum COdbCC::toEnum(const Json::Value& val)
{  
    return val.asString();
}
