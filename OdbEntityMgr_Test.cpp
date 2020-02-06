#include <criterion/criterion.h>  
#include <Entities.h> 
#include <user.hxx>
#include <user-odb.hxx>  
#include <OdbEntityMgr.hpp> 
   
using namespace bqc;

void entitymgr_setup(void)
{  
	base::AllTests::instance()->setup(); 
}

void entitymgr_teardown(void)
{ 
	base::AllTests::instance()->teardown();
}

TestSuite(entitymgr_base , .init = entitymgr_setup, .fini = entitymgr_teardown);

Test(entitymgr_base, find_one) {
      
	  typedef odb::query<EUser> query;
		
	  base::OdbEntityMgr em; 
 
	  std::shared_ptr<EUser> user = em.findOne<EUser>( query::code == 1UL);  
	
	  cr_expect(user.get() != nullptr,"Test em.findBy<EUser>() failed!"); 
}

Test(entitymgr_base, find_by_0) {
      
	  typedef odb::query<EUser> query;
		
	  base::OdbEntityMgr em; 
 
	  std::vector<EUser> users ;
	  
	  em.findBy<EUser>(users, query::org_code == 1UL);
	   
	  int count = users.size();
	
	  std::cout << "user_0 count = "<<count<<std::endl;
	
	  cr_expect_gt(count,0 ,"Test em.findBy<EUser>() failed!"); 
}

Test(entitymgr_base, find_by_1) {
      
	  typedef odb::query<EUser> query;
		
	  base::OdbEntityMgr em;
	  
	  query sql(query::org_code == 1UL);
 
	  std::vector<EUser> users = em.findBy<EUser>(sql);
	   
	  int count = users.size();
	
	  std::cout << "user_1 count = "<<count<<std::endl;
	
	  cr_expect_gt(count,0 ,"Test em.findBy<EUser>() failed!"); 
}

