/****************************************************************************
 * [TODO] CHANGE THIS OBJECT TO BE A TEMPLATE AND YOU ARE GOOD TO GO
** Capture Params Post Style
**
****************************************************************************/

#ifndef MODEL_OBJECT_H
#define MODEL_OBJECT_H

#include <entities_global.h>
#include <EntityField.h>

using namespace std; 
namespace bqc
{
typedef struct {
		vector<IEntityField*>    		  fields;
}IEntity_St;

class IEntity
{
	 
public:
		IEntity(const std::string& body="");
		IEntity& operator = (const std::string& body);
		void 							setValue(const string& key,const string& data);
		void 							setValue(int col,const string& data);
		string 							value(const string& key,const string& instead="");
		string 							value(int col,const string& instead);
		int 							index(const string& col);
	//data accessors key
	bool  						getBoolean(const std::string& key,bool instead = false);
    int    					    getInt(const std::string& key,int instead = 0); 
    float    					getFloat(const std::string& key,float instead = 0.0); 
    double    					getDouble(const std::string& key,double instead = 0.0); 
    boost::gregorian::date		getDate(const std::string& key,boost::gregorian::date instead = boost::gregorian::date(boost::gregorian::not_a_date_time));
    boost::posix_time::ptime	getTimeStamp(const std::string& key,boost::posix_time::ptime instead = boost::posix_time::ptime(boost::posix_time::not_a_date_time));
    std::string    				getString(const std::string& key,const string& instead="");
    //data manipulators
	void  						setBoolean(const std::string&  key,bool  val);	
    void    					setInt(const std::string&  key,int  val);
    void    					setString(const std::string&  key,const std::string&  val);
    void    					setFloat(const std::string&  key,float  val);
    void    					setDouble(const std::string&  key,double  val);
    void    					setDate(const std::string&  key,boost::gregorian::date  val);
    void    					setTimeStamp(const std::string&  key,boost::posix_time::ptime  val);
    //
	void						parse(const std::string& body);
	vector<string> 				keys();
	vector<IEntityField*>*  	fields();
	//Json::Value 				toJson(); 
	std::string 				data();
private:
	std::shared_ptr<IEntity_St>         m;
};
};
#endif
