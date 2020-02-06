#include <criterion/criterion.h>
#include <exception>
#include <new>
#include <array>
#include <stdio.h>
#include <HelperCC.h>
#include <OdbFieldCC.h>
#include <DbConnector.h> 
#include <AllTests.h>  

using namespace bqc;  

void odbfieldcc_setup(void)
{  
	base::AllTests::instance()->setup(); 
}

void odbfieldcc_teardown(void)
{ 
	base::AllTests::instance()->teardown();
}

TestSuite(odbfieldcc_main , .init = odbfieldcc_setup, .fini = odbfieldcc_teardown);

Test(odbfieldcc_main, to_json_string) {

    Json::Value val = dbo::IOdbFieldCC::toJson("ok");
     
	cr_expect(val == "ok","Test  CUtility::loadFile() failed!!");

}

Test(odbfieldcc_main, to_json_blob) {

    std::string test ="{\"code\":\"1\",\"created_by\":\"SYSTEM\",\"created_on\":\"2018-04-19 09:14:32\",\"message\":\"Bunilab Technologies, P.O.Box 40101 Luthuli Street , \r\nNairobi, Kenya.\",\"modified_by\":\"\",\"modified_on\":\"2018-06-11 20:48:58\",\"name\":\"ADDRESS\",\"subject\":\"Bunilab Address\",\"title\":\"Address\",\"type\":\"SMS\"}";
    
    cout<<"StringValue: "<<test<<endl;
    
    Json::Value v = dbo::IOdbFieldCC::toJson(test);

	cout<<"JsonValue: "<<v<<endl;
     
	cr_expect(!v.empty(),"Test  CUtility::toJson() failed empty!");
	
	std::string val = v["created_on"].asString();
	
	cr_expect(val == "2018-04-19 09:14:32" ,"Test  CUtility::toJson() failed unable to extract value!");
	

}

