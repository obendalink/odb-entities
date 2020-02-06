/*Author: obendalink@gmail.com*/
#ifndef ENTITY_USER_HXX
#define ENTITY_USER_HXX

#include <entities_global.h>
#include <OdbCC.h>

#pragma db object table("bqc_users") 
class EUser{
public:
#pragma db column("usr_code") type("BIGINT(20)") not_null id auto
 dbo::CUint64 code;
#pragma db column("usr_name") type("VARCHAR(200)") null
 dbo::CString name;
#pragma db column("usr_full_name") type("VARCHAR(100)") null
 dbo::CString full_name;
#pragma db column("usr_user_no") type("VARCHAR(80)") not_null
 dbo::CString user_no;
#pragma db column("usr_email") type("VARCHAR(100)") null
 dbo::CString email;
#pragma db column("usr_sms_no") type("VARCHAR(30)") null
 dbo::CString sms_no;
#pragma db column("usr_pin_no") type("VARCHAR(20)") null
 dbo::CString pin_no;
#pragma db column("usr_physical_addrs") type("VARCHAR(200)") null
 dbo::CString physical_addrs;
#pragma db column("usr_postal_addrs") type("VARCHAR(200)") null
 dbo::CString postal_addrs;
#pragma db column("usr_wef") type("DATE") null
 dbo::CDate wef;
#pragma db column("usr_wet") type("DATE") null
 dbo::CDate wet;
#pragma db column("usr_pwd") type("VARCHAR(100)") null
 dbo::CString pwd;
#pragma db column("usr_status") type("ENUM('A','I')") null
 dbo::CEnum status;
#pragma db column("usr_group_code") type("BIGINT(20)") null
 dbo::CUint64 group_code;
#pragma db column("usr_photo") type("BLOB") null
 dbo::CBlob photo;
#pragma db column("usr_params") type("TEXT") null
 dbo::CString params;
#pragma db column("usr_reset_count") type("INT(11)") null
 dbo::CUint64 reset_count;
#pragma db column("usr_remarks") type("TEXT") null
 dbo::CString remarks;
#pragma db column("usr_is_admin") type("ENUM('N','Y')") null
 dbo::CEnum is_admin;
#pragma db column("usr_is_root") type("ENUM('N','Y')") not_null
 dbo::CEnum is_root;
#pragma db column("usr_rank") type("VARCHAR(45)") null
 dbo::CString rank;
#pragma db column("usr_pwd_changed") type("DATETIME") null
 dbo::CDateTime pwd_changed;
#pragma db column("usr_pwd_reset") type("VARCHAR(1)") null
 dbo::CString pwd_reset;
#pragma db column("usr_activate") type("VARCHAR(1)") null
 dbo::CString activate;
#pragma db column("usr_login_attempts") type("INT(11)") null
 dbo::CUint64 login_attempts;
#pragma db column("usr_login_time") type("DATETIME") not_null default("CURRENT_TIMESTAMP")
 dbo::CDateTime login_time;
#pragma db column("usr_logout_time") type("DATETIME") null
 dbo::CDateTime logout_time;
#pragma db column("usr_title") type("VARCHAR(20)") null
 dbo::CString title;
#pragma db column("usr_gender") type("VARCHAR(1)") null
 dbo::CString gender;
#pragma db column("usr_dob") type("DATE") null
 dbo::CDate dob;
#pragma db column("usr_org_code") type("INT(11)") null
 dbo::CUint64 org_code;
#pragma db column("usr_role_code") type("INT(11)") null
 dbo::CUint64 role_code;
#pragma db column("usr_post_code") type("BIGINT(20)") not_null default(0)
 dbo::CUint64 post_code;
#pragma db column("usr_country_code") type("INT(11)") null
 dbo::CUint64 country_code;
#pragma db column("usr_state_code") type("INT(11)") null
 dbo::CUint64 state_code;
#pragma db column("usr_town_code") type("INT(11)") null
 dbo::CUint64 town_code;
#pragma db column("usr_type") type("VARCHAR(1)") null
 dbo::CString type;
#pragma db column("usr_token") type("VARCHAR(100)") null
 dbo::CString token;
#pragma db column("usr_token_tstamp") type("DATETIME") null
 dbo::CDateTime token_tstamp;
#pragma db column("usr_session_id") type("VARCHAR(120)") null
 dbo::CString session_id;
#pragma db column("usr_created_on") type("DATETIME") null
 dbo::CDateTime created_on;
#pragma db column("usr_created_by") type("VARCHAR(100)") null
 dbo::CString created_by;
#pragma db column("usr_modified_on") type("DATETIME") null
 dbo::CDateTime modified_on;
#pragma db column("usr_modified_by") type("VARCHAR(100)") null
 dbo::CString modified_by;
#pragma db column("usr_approved") type("VARCHAR(1)") null
 dbo::CString approved;
#pragma db column("usr_approved_on") type("DATETIME") null
 dbo::CDateTime approved_on;
#pragma db column("usr_approved_by") type("VARCHAR(100)") null
 dbo::CString approved_by;
//start to_json converter = (EUser) NB: this technic fixes std::bad_cast bug! So never change it
 Json::Value to_json(){  
 Json::Value v;  
  v["code"] = dbo::COdbCC::toJson(code);
  v["name"] = dbo::COdbCC::toJson(name);
  v["full_name"] = dbo::COdbCC::toJson(full_name);
  v["user_no"] = dbo::COdbCC::toJson(user_no);
  v["email"] = dbo::COdbCC::toJson(email);
  v["sms_no"] = dbo::COdbCC::toJson(sms_no);
  v["pin_no"] = dbo::COdbCC::toJson(pin_no);
  v["physical_addrs"] = dbo::COdbCC::toJson(physical_addrs);
  v["postal_addrs"] = dbo::COdbCC::toJson(postal_addrs);
  v["wef"] = dbo::COdbCC::toJson(wef);
  v["wet"] = dbo::COdbCC::toJson(wet);
  v["pwd"] = dbo::COdbCC::toJson(pwd);
  v["status"] = dbo::COdbCC::toJson(status);
  v["group_code"] = dbo::COdbCC::toJson(group_code);
  v["photo"] = dbo::COdbCC::toJson(photo);
  v["params"] = dbo::COdbCC::toJson(params);
  v["reset_count"] = dbo::COdbCC::toJson(reset_count);
  v["remarks"] = dbo::COdbCC::toJson(remarks);
  v["is_admin"] = dbo::COdbCC::toJson(is_admin);
  v["is_root"] = dbo::COdbCC::toJson(is_root);
  v["rank"] = dbo::COdbCC::toJson(rank);
  v["pwd_changed"] = dbo::COdbCC::toJson(pwd_changed);
  v["pwd_reset"] = dbo::COdbCC::toJson(pwd_reset);
  v["activate"] = dbo::COdbCC::toJson(activate);
  v["login_attempts"] = dbo::COdbCC::toJson(login_attempts);
  v["login_time"] = dbo::COdbCC::toJson(login_time);
  v["logout_time"] = dbo::COdbCC::toJson(logout_time);
  v["title"] = dbo::COdbCC::toJson(title);
  v["gender"] = dbo::COdbCC::toJson(gender);
  v["dob"] = dbo::COdbCC::toJson(dob);
  v["org_code"] = dbo::COdbCC::toJson(org_code);
  v["role_code"] = dbo::COdbCC::toJson(role_code);
  v["post_code"] = dbo::COdbCC::toJson(post_code);
  v["country_code"] = dbo::COdbCC::toJson(country_code);
  v["state_code"] = dbo::COdbCC::toJson(state_code);
  v["town_code"] = dbo::COdbCC::toJson(town_code);
  v["type"] = dbo::COdbCC::toJson(type);
  v["token"] = dbo::COdbCC::toJson(token);
  v["token_tstamp"] = dbo::COdbCC::toJson(token_tstamp);
  v["session_id"] = dbo::COdbCC::toJson(session_id);
  v["created_on"] = dbo::COdbCC::toJson(created_on);
  v["created_by"] = dbo::COdbCC::toJson(created_by);
  v["modified_on"] = dbo::COdbCC::toJson(modified_on);
  v["modified_by"] = dbo::COdbCC::toJson(modified_by);
  v["approved"] = dbo::COdbCC::toJson(approved);
  v["approved_on"] = dbo::COdbCC::toJson(approved_on);
  v["approved_by"] = dbo::COdbCC::toJson(approved_by);
 return v;}
//end to_json converter = (EUser)
//start to_odb converter = (EUser) NB: this technic fixes std::bad_cast bug! So never change it
 void to_odb(const Json::Value& v){ 
 code = dbo::COdbCC::toUint64(v["code"]);
 name = dbo::COdbCC::toString(v["name"]);
 full_name = dbo::COdbCC::toString(v["full_name"]);
 user_no = dbo::COdbCC::toString(v["user_no"]);
 email = dbo::COdbCC::toString(v["email"]);
 sms_no = dbo::COdbCC::toString(v["sms_no"]);
 pin_no = dbo::COdbCC::toString(v["pin_no"]);
 physical_addrs = dbo::COdbCC::toString(v["physical_addrs"]);
 postal_addrs = dbo::COdbCC::toString(v["postal_addrs"]);
 wef = dbo::COdbCC::toDate(v["wef"]);
 wet = dbo::COdbCC::toDate(v["wet"]);
 pwd = dbo::COdbCC::toString(v["pwd"]);
 status = dbo::COdbCC::toString(v["status"]);
 group_code = dbo::COdbCC::toUint64(v["group_code"]);
 photo = dbo::COdbCC::toBlob(v["photo"]);
 params = dbo::COdbCC::toString(v["params"]);
 reset_count = dbo::COdbCC::toUint64(v["reset_count"]);
 remarks = dbo::COdbCC::toString(v["remarks"]);
 is_admin = dbo::COdbCC::toString(v["is_admin"]);
 is_root = dbo::COdbCC::toString(v["is_root"]);
 rank = dbo::COdbCC::toString(v["rank"]);
 pwd_changed = dbo::COdbCC::toTimeStamp(v["pwd_changed"]);
 pwd_reset = dbo::COdbCC::toString(v["pwd_reset"]);
 activate = dbo::COdbCC::toString(v["activate"]);
 login_attempts = dbo::COdbCC::toUint64(v["login_attempts"]);
 login_time = dbo::COdbCC::toTimeStamp(v["login_time"]);
 logout_time = dbo::COdbCC::toTimeStamp(v["logout_time"]);
 title = dbo::COdbCC::toString(v["title"]);
 gender = dbo::COdbCC::toString(v["gender"]);
 dob = dbo::COdbCC::toDate(v["dob"]);
 org_code = dbo::COdbCC::toUint64(v["org_code"]);
 role_code = dbo::COdbCC::toUint64(v["role_code"]);
 post_code = dbo::COdbCC::toUint64(v["post_code"]);
 country_code = dbo::COdbCC::toUint64(v["country_code"]);
 state_code = dbo::COdbCC::toUint64(v["state_code"]);
 town_code = dbo::COdbCC::toUint64(v["town_code"]);
 type = dbo::COdbCC::toString(v["type"]);
 token = dbo::COdbCC::toString(v["token"]);
 token_tstamp = dbo::COdbCC::toTimeStamp(v["token_tstamp"]);
 session_id = dbo::COdbCC::toString(v["session_id"]);
 created_on = dbo::COdbCC::toTimeStamp(v["created_on"]);
 created_by = dbo::COdbCC::toString(v["created_by"]);
 modified_on = dbo::COdbCC::toTimeStamp(v["modified_on"]);
 modified_by = dbo::COdbCC::toString(v["modified_by"]);
 approved = dbo::COdbCC::toString(v["approved"]);
 approved_on = dbo::COdbCC::toTimeStamp(v["approved_on"]);
 approved_by = dbo::COdbCC::toString(v["approved_by"]);
 }
//end to_odb converter = (EUser)
};
namespace dbo{
}//end dbo

#endif // USER_HXX