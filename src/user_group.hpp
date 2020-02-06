/*Author: obendalink@gmail.com*/
#ifndef ENTITY_USERGROUP_HXX
#define ENTITY_USERGROUP_HXX

#include <entities_global.h>
#include <OdbCC.h>

#pragma db object table("bqc_user_groups") 
class EUserGroup{
public:
#pragma db column("usrgp_code") type("INT(10) UNSIGNED") not_null id auto
 dbo::CUint64 code;
#pragma db column("usrgp_name") type("VARCHAR(100)") null
 dbo::CString name;
#pragma db column("usrgp_ref") type("VARCHAR(100)") null
 dbo::CString ref;
#pragma db column("usrgp_email") type("VARCHAR(100)") null
 dbo::CString email;
#pragma db column("usrgp_is_root") type("VARCHAR(1)") null
 dbo::CString is_root;
#pragma db column("usrgp_is_admin") type("VARCHAR(1)") null
 dbo::CString is_admin;
#pragma db column("usrgp_created_on") type("DATETIME") null
 dbo::CDateTime created_on;
#pragma db column("usrgp_created_by") type("VARCHAR(100)") null
 dbo::CString created_by;
#pragma db column("usrgp_modified_on") type("DATETIME") null
 dbo::CDateTime modified_on;
#pragma db column("usrgp_modified_by") type("VARCHAR(100)") null
 dbo::CString modified_by;
//start to_json converter = (EUserGroup) NB: this technic fixes std::bad_cast bug! So never change it
 Json::Value to_json(){  
 Json::Value v;  
  v["code"] = dbo::COdbCC::toJson(code);
  v["name"] = dbo::COdbCC::toJson(name);
  v["ref"] = dbo::COdbCC::toJson(ref);
  v["email"] = dbo::COdbCC::toJson(email);
  v["is_root"] = dbo::COdbCC::toJson(is_root);
  v["is_admin"] = dbo::COdbCC::toJson(is_admin);
  v["created_on"] = dbo::COdbCC::toJson(created_on);
  v["created_by"] = dbo::COdbCC::toJson(created_by);
  v["modified_on"] = dbo::COdbCC::toJson(modified_on);
  v["modified_by"] = dbo::COdbCC::toJson(modified_by);
 return v;}
//end to_json converter = (EUserGroup)
//start to_odb converter = (EUserGroup) NB: this technic fixes std::bad_cast bug! So never change it
 void to_odb(const Json::Value& v){ 
 code = dbo::COdbCC::toUint64(v["code"]);
 name = dbo::COdbCC::toString(v["name"]);
 ref = dbo::COdbCC::toString(v["ref"]);
 email = dbo::COdbCC::toString(v["email"]);
 is_root = dbo::COdbCC::toString(v["is_root"]);
 is_admin = dbo::COdbCC::toString(v["is_admin"]);
 created_on = dbo::COdbCC::toTimeStamp(v["created_on"]);
 created_by = dbo::COdbCC::toString(v["created_by"]);
 modified_on = dbo::COdbCC::toTimeStamp(v["modified_on"]);
 modified_by = dbo::COdbCC::toString(v["modified_by"]);
 }
//end to_odb converter = (EUserGroup)
};
namespace dbo{
}//end dbo

#endif // USERGROUP_HXX