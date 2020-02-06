/****************************************************************************
** Capture Params Post Style
****************************************************************************/

#include <HelperCC.h>
#include <EntityField.h>
#include <Entity.h>
//Meet IEntity
using namespace dbo;  
using namespace bqc; 
using namespace std;
IEntity::IEntity(const std::string& body)
    : m(make_shared<IEntity_St>())
{
   //parse(body);
}

IEntity& IEntity::operator = (const std::string& body){
     //parse(body);
     return (*this);
}
/*
Json::Value IEntity::toJson(){
 Json::Value v; 
	 for(std::vector<bqc::IEntityField*>::iterator  i = m->fields.begin();i!=m->fields.end();i++){
			void* data = (*i)->data();
			if(data!=nullptr){
				if((*i)->type()=="int"){
					v[(*i)->name()] = *((int*)data);
				}else if((*i)->type()=="float"){
					v[(*i)->name()] = *((float*)data);
				}else if((*i)->type()=="double"){
					v[(*i)->name()] = *((double*)data);
				}else if((*i)->type()=="bool"){
					v[(*i)->name()] = *((bool*)data);
				}else if((*i)->type()=="std::string"){
					v[(*i)->name()] = *((std::string*)data);
				}else if((*i)->type()=="boost::gregorian::date"){
					boost::gregorian::date tmp = *((boost::gregorian::date*)data);
					v[(*i)->name()] =  utils::CDateUtils::instance()->format(tmp,"%Y-%m-%d"); 
				}else if((*i)->type()=="boost::posix_time::ptime"){
					boost::posix_time::ptime tmp =*((boost::posix_time::ptime*)data);
					v[(*i)->name()] =  utils::CDateUtils::instance()->format(tmp,"%Y-%m-%d");  
				}else if((*i)->type()=="std::vector<char>"){
					std::vector<char> tmp = *((std::vector<char>*)data);
					v[(*i)->name()] =  std::string(tmp.begin(), tmp.end());
				} 	
			} 
	 }
	 return v;
 }*/

void IEntity::parse(const std::string& body)
{ 
	/*if(!body.empty()){
		Json::Value json = base::IHelperCC::toJson(body); 
		if(!json.empty()){ 
		   if(json.isObject()) {
				vector<string> keys = json.getMemberNames();
				for (size_t i=0; i<keys.size(); i++){
					const string& key = keys[i];
					Json::Value param = json[key]; 
					string val = ""; 
					if(param.isObject() || param.isArray()){
						val = base::IHelperCC::toString(param);
					}else{
						val = base::IHelperCC::trim(param.asString());
					}  
					val = (val!="null" && val != "undefined")? val : ""; 
					setValue(key, val ) ; 
				}
			}
		} 
	}*/
}



int IEntity::index(const string& col)
{
     for(int i = 0;i<m->fields.size();i++){
		if( m->fields[i]->name()==col )
		  return i;
	}
    return -1;
}
string IEntity::value(const string& key,const string& instead)
{
    int col = index(key);
    return value(col,instead);
}
string IEntity::value(int col,const string& instead)
{ 
	if(col>=0 && col<m->fields.size()){
		std::string val = m->fields[col]->value(instead); 
		if(!val.empty()){
			return val;
		}
	}  
    return instead;
}
void IEntity::setValue(int col,const string& data)
{
    if(col>=0 && col<m->fields.size()){
		m->fields[col]->setValue(data);   
	} 
}
void IEntity::setValue(const string& key,const string& data)
{
    int col = index(key);
    if(col>=0 && col<m->fields.size()){
		m->fields[col]->setValue(data);   
	}  
}


void IEntity::setString(const string& key,const string& data)
{
    setValue(key,data);
}
string IEntity::getString(const string& key,const string& instead)
{
    return value( key,instead);
}
bool  IEntity::getBoolean(const std::string& key,bool instead)
{
	 std::string val = getString(key,std::to_string(instead));
	 return val == "true";
}
int  IEntity::getInt(const std::string& key,int instead)
{
	 std::string val = getString(key,std::to_string(instead));
	 return atoi(val.c_str());
}

float  IEntity::getFloat(const std::string& key,float instead)
{
	 std::string val = getString(key,std::to_string(instead));
	 return atof(val.c_str());
}
double  IEntity::getDouble(const std::string& key,double instead)
{
	 std::string val = getString(key,std::to_string(instead));
	 return atof(val.c_str());
}
boost::gregorian::date	IEntity::getDate(const std::string& key,boost::gregorian::date instead)
{
	std::string val = getString(key);
	boost::gregorian::date null(boost::gregorian::not_a_date_time);
    if(!val.empty() && base::IHelperCC::match(val,"^\\d{1,2}\\-\\d{1,2}\\-\\d{4}$"))   //.e.g
    {
        return boost::gregorian::from_uk_string(val);
    }
    return null;
}
boost::posix_time::ptime IEntity::getTimeStamp(const std::string& key,boost::posix_time::ptime instead)
{
	std::string val = getString(key);
	boost::posix_time::ptime null(boost::posix_time::not_a_date_time);
    if(!val.empty() && base::IHelperCC::match(val,"^\\d{4}\\-\\d{1,2}\\-\\d{1,2}\\s\\d{2}\\:\\d{1,2}\\:\\d{1,2}$"))   //.e.g 2017-07-27 00:00:00
    {
        return boost::posix_time::time_from_string(val);//"2016/2/19 9:01:33.10"
    }
    return null;
}
void  IEntity::setBoolean(const std::string&  key,bool val)
{
    setString(key,std::to_string(val));
}
void  IEntity::setInt(const std::string&  key,int  val)
{
    setString(key,std::to_string(val));
}
void  IEntity::setFloat(const std::string&  key,float  val)
{
    setString(key,std::to_string(val));
}
void  IEntity::setDouble(const std::string&  key,double  val)
{
    setString(key,std::to_string(val));
}
void  IEntity::setDate(const std::string&  key,boost::gregorian::date  val)
{
	const std::locale fmt(std::locale::classic(),new boost::gregorian::date_facet("%Y-%m-%d"));
	std::ostringstream os;
	os.imbue(fmt);
	os << val;
	std::string date = os.str();
    setString(key,date);
}

void  IEntity::setTimeStamp(const std::string&  key,boost::posix_time::ptime  val)
{
	const std::locale fmt = std::locale(std::locale::classic(), new boost::posix_time::time_facet("%Y-%m-%d %H:%M:%S"));
	std::ostringstream os;
	os.imbue(fmt);
	os << val;
	std::string date = os.str();
    setString(key,date);
}

vector<IEntityField*>* IEntity::fields()
{
    return &m->fields;
}
vector<string> IEntity::keys()
{
    std::vector<string> k; 
	std::vector<IEntityField*>::iterator i;
    for(i = fields()->begin(); i!=fields()->end(); i++)
    {
        k.push_back( (*i)->name() );
    }
    return k;
}

/*Test Code
 *
 *  IEntity p = new IEntity();
 *  p->parse("{\"email\": \"admin@store.com\", \"password\": \"Test12345$\"}");
    cout<<"email: "<<p->value("email")<<endl;
    cout<<"password: "<<p->value("password")<<endl;
 **/

