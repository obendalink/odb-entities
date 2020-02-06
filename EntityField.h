/*
 * [TODO] CHANGE THIS OBJECT TO BE A TEMPLATE AND YOU ARE GOOD TO GO
 * Mysql DB API
 * Copyright:Doctor Dk.
 * Author:  kavagi: obendalink@gmail.com
 *  Nice One. Doesnt know the database below is a mysql,sqlite,access etc.
    How Cool. A good Library for a Project Team.
 * */
#ifndef OBJECT_FIELD_H
#define OBJECT_FIELD_H 1
#include <entities_global.h>

#define sz_field 256
using namespace std;
namespace bqc
{
/*Database IEntityField*/
//column prototype
/*!
 * FormField struct Data
 */
 typedef struct {
	std::string name;//keys of IEntityField will be pointing to this field.
    std::string type;//type
    size_t size;
    void* data;
}IEntityField_Dt;


class  IEntityField
{

public:
    IEntityField();
    IEntityField(void* data,const string& name,const string& type,int sz = 0);
    const string& name();
    const string& type();
    size_t size();
    void* data();
    string value(const string& val);
    void setValue(const string& val);
    void setSize(int sz);
    void setData(void* data);
    void setType(const string& type);
    void setName(const string& name);
private:
shared_ptr<IEntityField_Dt> 	m;

};
typedef shared_ptr<IEntityField> IEntityField_Spt;
typedef vector<IEntityField_Spt>::iterator IEntityField_It;
};
#endif
