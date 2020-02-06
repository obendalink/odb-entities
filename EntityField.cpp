/*
 * Field DB API
 * Copyright:Doctor Dk.
 * Author:  Obenda Dk obendalink@gmail.com
 * */

#include <EntityField.h>
#include <HelperCC.h>
using namespace std;
using namespace dbo;  
using namespace bqc; 

//Field/Column DEFITIONS

IEntityField::IEntityField()
{ 
	
}

IEntityField::IEntityField(void* data,const string& name, const string& type,int vSz): m(make_shared<IEntityField_Dt>())
{
	m->data=data; m->name=name; m->type=type; m->size=vSz;

}

void IEntityField::setSize(int vSz)
{
    m->size = vSz;
}
void IEntityField::setData(void* data)
{
    m->data = data;
}
void IEntityField::setType(const string& type)
{
    m->name = type;
}
void IEntityField::setName(const string& name)
{
    m->name = name;
}
const string& IEntityField::name()
{
    return m->name;
}

const string& IEntityField::type()
{
    return m->type;
}

void* IEntityField::data()
{
    return m->data;
}
string IEntityField::value(const string& instead)
{
	std::string val = "";  
	if(m->data!=nullptr){
		if(m->type == "int"){
			int tmp = *((int*)m->data);
			val = std::to_string(tmp);
		}else if(m->type == "float"){
			float tmp = *((float*)m->data);
			val = std::to_string(tmp);
		}else if(m->type == "bool"){
			bool tmp = *((bool*)m->data);
			val = std::to_string(tmp);
		}else if(m->type == "double"){
			double tmp = *((double*)m->data);
			val = std::to_string(tmp);
		}else if(m->type == "std::string"){ 
			val = *((std::string*)m->data);
		}else if(m->type == "boost::gregorian::date"){
			boost::gregorian::date tmp = *((boost::gregorian::date*)m->data);
			val =  utils::CDateUtils::instance()->format(tmp,"%Y-%m-%d"); 
		}else if(m->type == "boost::posix_time::ptime"){
			boost::posix_time::ptime tmp =*((boost::posix_time::ptime*)m->data);
			val =  utils::CDateUtils::instance()->format(tmp,"%Y-%m-%d %H:%M:%S");  
		}else if(m->type == "std::vector<char>"){
			std::vector<char> tmp = *((std::vector<char>*)m->data);
			val =  std::string(tmp.begin(), tmp.end());
		} 	
	} 
	if(!val.empty()){
		return val;
	}
    return instead;
}

void IEntityField::setValue(const string& val)
{  
	std::string tmp = base::IHelperCC::trim(val);
	
	if(m->data!=nullptr){
		if(m->type == "int"){
			 *((int*)m->data)=atoi(tmp.c_str()); 
		}else if(m->type == "bool"){
			 *((bool*)m->data)=atoi(tmp.c_str()); 
		}else if(m->type == "float"){
			*((int*)m->data)=atof(tmp.c_str()); 
		}else if(m->type == "double"){
			*((int*)m->data)=atof(tmp.c_str()); 
		}else if(m->type == "std::string"){ 
			*((std::string*)m->data)= tmp;
		}else if(m->type == "boost::gregorian::date"){ 
			*((boost::gregorian::date*)m->data)= boost::gregorian::from_simple_string(tmp);
		}else if(m->type == "boost::posix_time::ptime"){ 
			*((boost::posix_time::ptime*)m->data) = boost::posix_time::time_from_string(tmp); 
		}else if(m->type == "std::vector<char>"){  
			*((std::vector<char>*)m->data) = std::vector<char>(tmp.begin(), tmp.end());
		} 	
	}  
}

size_t IEntityField::size()
{
    return m->size;
}
