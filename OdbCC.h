/****************************************************************************
**
** Odb Field Conversion Utilities.
****************************************************************************/

#ifndef BQC_ODB_CC_H
#define BQC_ODB_CC_H

#include <entities_global.h>
using namespace std; 

//typedef std::vector< uint8_t > Bytes;

 
namespace dbo
{
    class COdbCC
    {
    public:
        //to Json type
		static Json::Value toJson(const std::string& val);
		static Json::Value toJson(const CBlob& val);
		static Json::Value toJson(const CDouble& val);
		static Json::Value toJson(const CFloat& val);
		static Json::Value toJson(const CBoolean& val);
		static Json::Value toJson(CDate val,const std::string& format="%Y-%m-%d");
		static Json::Value toJson(CDateTime val,const std::string& format="%Y-%m-%d %H:%M:%S"); 
		static Json::Value toJson(CTime val,const std::string& format="%H:%M:%S"); 
		static Json::Value toJson(const CUint64& val);  
		//to others types
		static CString toString(const Json::Value& val);
		static CEnum toEnum(const Json::Value& val);
		static CUint64 toUint64(const Json::Value& val);
		static CDouble toDouble(const Json::Value& val);
		static CFloat toFloat(const Json::Value& val);
		static CBoolean toBoolean(const Json::Value& val);
		static CBlob toBlob(const Json::Value& val);
		static CDate toDate(const Json::Value& val);
		static CTime toTime(const Json::Value& val);
		static CDateTime toTimeStamp(const Json::Value& val); 
    private:
    };
};
#endif
