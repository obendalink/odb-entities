/* Author obendalink@gmail.com
 * Entity Helper Generic functions
*/
#ifndef ODB_ENTITY_MANAGER_H
#define ODB_ENTITY_MANAGER_H

#include <bqc_global.h>

#include <type_traits>
#include <odb/traits.hxx>
#include <DbConnector.h> // create_database
#include <entities_global.h>

using namespace std;
using namespace odb::core;

namespace bqc
{
	namespace base
	{ 
	class OdbEntityMgr {
    public:

        OdbEntityMgr(); 
        template<typename T>
		std::vector<T> findAll(); 
        template<typename T>
		bool findAll(std::vector<T>& items); 
		template<typename T>
		bool findBy(std::vector<T>& items,const odb::query<T> &query);
		template<typename T>
		std::vector<T> findBy(const odb::query<T> &query);
		template<typename T>
		bool findOne(T& item,const typename odb::object_traits<T>::id_type& id);
		template<typename T>  
		bool findOne(T& item,const odb::query<T> &query); 
		template<typename T>
		shared_ptr<T> findOne(const typename odb::object_traits<T>::id_type& id); 
		template<typename T>
		shared_ptr<T> findOne(const odb::query<T> &query); 
		template<typename T>
		bool existsById(const typename odb::object_traits<T>::id_type& id); 
        template<typename T>
        bool existsBy(const odb::query<T> &query); 
		template<typename T>
		bool deleteBy(const odb::query<T> &query);
        template<typename T>
        bool deleteOne(T& item);
        template<typename T>
        bool deleteOne(T* item);
        template<typename T>
        bool deleteOne(const typename odb::object_traits<T>::id_type& id);
		template<typename T>
        typename odb::object_traits<T>::id_type insertOne(T& item);
		template<typename T>
        typename odb::object_traits<T>::id_type insertOne(T* item);
		template<typename T>
		bool updateOne(T& item); 
		template<typename T>
		bool updateOne(T* item); 
		template<typename T>
        typename odb::object_traits<T>::id_type saveOne(T& item);
		template<typename T>
        typename odb::object_traits<T>::id_type saveOne(T* item);
		template<typename T>
		bool insertAll(std::vector<T> &items);
		template<typename T>
		bool updateAll(std::vector<T> &items);
		template<typename T>
		bool saveAll(std::vector<T> &items);
		template<typename T>
		Json::Value toJson(std::vector<T> &items);
		template<typename T>
		Json::Value toJson(T &item); 
		template<typename T>
		Json::Value toJson(shared_ptr<T> &item); 
		template<typename T>
		void toOdb(T& p, const Json::Value& v); 
	};
	
    inline OdbEntityMgr::OdbEntityMgr(){

    }

	template<class T>
	inline std::vector<T> OdbEntityMgr::findAll() {
		std::vector<T> items;
		try {
			shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
			{
				transaction t(db->begin());

				t.tracer (stderr_tracer);

				odb::result<T> r(db->query<T>());

				for (typename odb::result<T>::iterator i(r.begin()); i != r.end(); i++) {
					items.push_back((*i));
				}
				t.commit();
			}
		} catch (const odb::exception &e) {
			cerr << "std::vector<T> OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::findAll(): " << e.what() << endl;
		}

		return items;
	}

	template<typename T>
	inline bool OdbEntityMgr::findAll(std::vector<T>& items) {
	  bool success = false;
		try {
			shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
			{
				transaction t(db->begin());

				t.tracer (stderr_tracer);

				odb::result<T> r(db->query<T>());

				for (typename odb::result<T>::iterator i(r.begin()); i != r.end(); i++) {
					items.push_back((*i));
				}
				t.commit();
				success = true;
			}
		} catch (const odb::exception &e) {
			cerr << "bool OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::findAll(std::vector<T>& items): " << e.what() << endl;
		} 

		return success;
	}
	
	template<typename T>
	inline bool OdbEntityMgr::findBy(std::vector<T>& items,const odb::query<T> &query) { 
			bool success = false;
			try {
					shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
					{
						transaction t(db->begin());

						t.tracer (stderr_tracer);
						
						odb::result<T> r(db->query<T>(query));

						for (typename odb::result<T>::iterator i(r.begin()); i != r.end(); i++) {
							items.push_back((*i));
						}
						t.commit();
						success = true;
					}
			} catch (const odb::exception &e) {
				cerr << "bool OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::findBy(std::vector<T>& items,const odb::query<T> &query): " << e.what() << endl;
			} 
			return success;
		}
	
	template<typename T>
	inline std::vector<T> OdbEntityMgr::findBy(const odb::query<T> &query) { 
			std::vector<T> items;
			try {
					shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
					{
						transaction t(db->begin());

						t.tracer (stderr_tracer);
						odb::result<T> r(db->query<T>(query));

						for (typename odb::result<T>::iterator i(r.begin()); i != r.end(); i++) {
							items.push_back((*i));
						}
						t.commit(); 
					}
			} catch (const odb::exception &e) { 
				cerr << "std::vector<T> OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::findBy(const odb::query<T> &query): " << e.what() << endl;
			} 
			return items;
		}

	template<typename T>
	inline bool OdbEntityMgr::findOne(T& item,const typename odb::object_traits<T>::id_type& id) {
		
		std::cout <<"OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::findOne() getting "<<typeid(T).name()<<" by code = ["<<std::to_string(id)<<"] ...."<<std::endl;
		
		bool success = false;		
		
		try {
				shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
				{
					transaction t(db->begin());

					t.tracer (stderr_tracer);
					db->load<T>(id,item);
					t.commit();
					success = true;
				}

		} catch (const odb::exception &e) {
			cerr << "bool OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::findOne(T& item,const typename odb::object_traits<T>::id_type& id): " << e.what() << endl;
		}

		return success;
	}

	template <typename T>
	inline bool OdbEntityMgr::findOne(T& item,const odb::query<T> &query) {
			bool success = false;
			try {
					shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
					{
						transaction t(db->begin());

						t.tracer (stderr_tracer);
						
						success = db->query_one<T>(query,item);

						t.commit(); 
					}

			} catch (const odb::exception &e) { 
				cerr << "bool OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::findOne(T& item,const odb::query<T> &query): " << e.what() << endl;
			}

			return success;
    }

	template<typename T>
	inline shared_ptr<T> OdbEntityMgr::findOne(const typename odb::object_traits<T>::id_type& id) {
		
		std::cout <<"OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::findOne() getting "<<typeid(T).name()<<" by code = ["<<std::to_string(id)<<"] ...."<<std::endl;
		
		shared_ptr<T> item = nullptr;
		
		try {
				shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
				{
					transaction t(db->begin());

					t.tracer (stderr_tracer);
					
					item = shared_ptr<T>(db->load<T>(id));
					t.commit(); 
				}

		} catch (const odb::exception &e) {
			cerr << "shared_ptr<T> OdbEntityMgr::< T = ["<<typeid(T).name()<<"] >::findOne(const typename odb::object_traits<T>::id_type& id): " << e.what() << endl;
		}

		return item;
	}

	template <typename T>
	inline shared_ptr<T> OdbEntityMgr::findOne(const odb::query<T> &query) {
			shared_ptr<T> item = nullptr;
			try {
				shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
				{
					transaction t(db->begin());

					t.tracer (stderr_tracer);

					item = shared_ptr<T>(db->query_one<T>(query));

					t.commit();
				}
			} catch (const odb::exception &e) {
				cerr << "shared_ptr<T> OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::findOne(const odb::query<T> &query): " << e.what() << endl;
			}


			return item;
	}


	template<typename T>
	inline  bool OdbEntityMgr::existsById(const typename odb::object_traits<T>::id_type& id) { 
		
		    std::cout <<"OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::existsById() checking "<<typeid(T).name()<<" by code = ["<<std::to_string(id)<<"] ...."<<std::endl;
		
			bool success = false;
			
			T item;
			try {
					shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
					{
						transaction t(db->begin());

						t.tracer (stderr_tracer);
						success = db->find<T>(id);
						t.commit();
						success = true;
					}
					
			} catch (const odb::exception &e) {
				cerr << "bool OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::existsById(const typename odb::object_traits<T>::id_type& id): " << e.what() << endl;
			}

			return success;
		}
	template<typename T>
	inline bool OdbEntityMgr::existsBy(const odb::query<T> &query) { 
			bool success = false;
			try {
					shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
					{
						transaction t(db->begin());

						t.tracer (stderr_tracer);
						odb::result<T> r(db->query<T>(query));
						success = r.size() > 0;
						t.commit(); 
					}
			} catch (const odb::exception &e) {
				cerr << "bool OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::existsBy(const odb::query<T> &query): " << e.what() << endl;
			}

			return success;
		}

	


	template<typename T>
	inline bool OdbEntityMgr::deleteOne(T& item) { 
				bool success = false;
				try {
						shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
						{
							transaction t(db->begin());

							t.tracer (stderr_tracer);
							db->erase<T>( item.code );
							t.commit();
							success = true;
						}
				} catch (const odb::exception &e) {
					cerr << "bool OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::deleteOne(T& item):  item.code = ["<<item.code<<"]" << e.what() << endl;
				}
				return success;
		}
		
	template<typename T>
	inline bool OdbEntityMgr::deleteOne(T* item) { 
				bool success = false;
				try {
						shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
						{
							transaction t(db->begin());

							t.tracer (stderr_tracer);
							db->erase<T>( item->code );
							t.commit();
							success = true;
						}
				} catch (const odb::exception &e) { 
					cerr << "bool OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::deleteOne(T* item):  item->code = ["<<item.code<<"]" << e.what() << endl;
				}
				return success;
		}

	template<typename T>
	inline bool OdbEntityMgr::deleteOne(const typename odb::object_traits<T>::id_type& id) { 
		
		    std::cout <<"OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::deleteOne() deleting "<<typeid(T).name()<<" by code = ["<<std::to_string(id)<<"] ...."<<std::endl;
		
			  bool success = false;
			  try {
						shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
						{
							transaction t(db->begin());

							t.tracer (stderr_tracer);
							db->erase<T>(id);
							t.commit();
							success = true;
						}
				} catch (const odb::exception &e) {
					cerr << "bool OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::deleteOne(const typename odb::object_traits<T>::id_type& id = ["<<id<<"]): " << e.what() << endl;
				}

				return success;
		}

		template<typename T>
	inline	bool OdbEntityMgr::deleteBy(const odb::query<T> &query) { 
				bool success = false;
				try {
						shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
						{
							transaction t(db->begin());

							t.tracer (stderr_tracer);
							db->erase_query<T>(query);
							t.commit();
							success = true;
						}
				} catch (const odb::exception &e) {

					cerr << "bool OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::deleteOne(const odb::query<T>& query = [sql]): " << e.what() << endl;
				}

				return success;
			}

	template<typename T>
	inline typename odb::object_traits<T>::id_type OdbEntityMgr::insertOne(T& item) { 
		typename odb::object_traits<T>::id_type item_id = 0UL;
		try { 
					shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
					{
						transaction t(db->begin());

						t.tracer (stderr_tracer);
						item_id = db->persist(item);
						t.commit();
					}
		} catch (const odb::exception &e) {
			cerr << "odb::object_traits<T>::id_type OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::insertOne(const T& item): " << e.what() << endl;
		}

		return item_id;
	}
	template<typename T>
	inline typename odb::object_traits<T>::id_type OdbEntityMgr::insertOne(T* item) { 
		typename odb::object_traits<T>::id_type item_id = 0UL;
		try { 
					shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
					{
						transaction t(db->begin());

						t.tracer (stderr_tracer);
						item_id = db->persist(item);
						t.commit();
					}
		} catch (const odb::exception &e) {
			cerr << "odb::object_traits<T>::id_type OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::insertOne(const T& item): " << e.what() << endl;
		}

		return item_id;
	}

	template<typename T>
	inline bool OdbEntityMgr::updateOne(T& item) { 
		bool success = false;
		try {
					shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
					{
						transaction t(db->begin());

						t.tracer (stderr_tracer);
						db->update(item);
						t.commit();
						success = true;
					}
		} catch (const odb::exception &e) {
			cerr << "bool OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::updateOne(const T& item): " << e.what() << endl;
		}

		return success;
	}

	template<typename T>
	inline bool OdbEntityMgr::updateOne(T* item) { 
		bool success = false;
		try {
					shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
					{
						transaction t(db->begin());

						t.tracer (stderr_tracer);
						db->update(item);
						t.commit();
						success = true;
					}
		} catch (const odb::exception &e) {
			cerr << "bool OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::updateOne(const T& item): " << e.what() << endl;
		}

		return success;
	}

	template<typename T>
	inline typename odb::object_traits<T>::id_type OdbEntityMgr::saveOne(T& item) { 
		typename odb::object_traits<T>::id_type item_id = 0UL;
		try {
				shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
					{
						transaction t(db->begin());

						t.tracer (stderr_tracer);
						item_id = item.code;
						if (!item_id) {
							item_id = db->persist(item);
						} else {
							db->update(item);
						}
						t.commit();
					}

		} catch (const odb::exception &e) {
			cerr << "odb::object_traits<T>::id_type OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::saveOne(const T& item): " << e.what() << endl;
		}

		return item_id;
	}
	template<typename T>
	inline typename odb::object_traits<T>::id_type OdbEntityMgr::saveOne(T* item) { 
		typename odb::object_traits<T>::id_type item_id = 0UL;
		try {
				shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
					{
						transaction t(db->begin());

						t.tracer (stderr_tracer);
						item_id = item->code;
						if (!item_id) {
							item_id = db->persist(item);
						} else {
							db->update(item);
						}
						t.commit();
					}

		} catch (const odb::exception &e) {
			cerr << "odb::object_traits<T>::id_type OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::saveOne(const T*item): " << e.what() << endl;
		}

		return item_id;
	}

	template<typename T>
	inline bool OdbEntityMgr::insertAll(std::vector<T> &items) { 
		bool success = false;
		try { 
				shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
					{
						transaction t(db->begin()); 
						t.tracer (stderr_tracer);
						for (T &item: items) {
							db->persist(item);
						}
						t.commit();
						success = true;
					}
		} catch (const odb::exception &e) {
			cerr << "bool OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::saveAll(std::vector<T>& items): " << e.what() << endl;
		}

		return success;
	}

	template<typename T>
	inline bool OdbEntityMgr::updateAll(std::vector<T> &items) { 
		bool success = false;
		try { 
				shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
					{
						transaction t(db->begin());

						t.tracer (stderr_tracer);
						for (T &item: items) {
							db->update(item);
						}
						t.commit();
						success = true;
					}

		} catch (const odb::exception &e) {
			cerr << "bool OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::saveAll(std::vector<T>& items): " << e.what() << endl;
		}

		return success;
	}

	template<typename T>
	inline bool OdbEntityMgr::saveAll(std::vector<T> &items) { 
		bool success = false;
		try {
				shared_ptr<database> db = bqc::base::dbConnector()->getConnection();
				{
					transaction t(db->begin());

					t.tracer (stderr_tracer);
					for (T &item: items) {
						typename odb::object_traits<T>::id_type item_id = item.code;
						if (!item_id) {
							item_id = db->persist(item);
						} else {
							db->update(item);
						}
					}
					t.commit();
					success = true;
				}
		} catch (const odb::exception &e) {
			cerr << "bool OdbEntityMgr< T = ["<<typeid(T).name()<<"] >::saveAll(std::vector<T>& items): " << e.what() << endl;
		}

		return success;
	}

    template<typename T> //! type and thread safe
    inline Json::Value OdbEntityMgr::toJson(std::vector<T> &items) {
    Json::Value vals = Json::Value(Json::arrayValue);
		for (int i = 0; i < items.size(); i++) { 
            vals[i] = items[i].to_json();
		}
		return vals;
    }
    
    template<typename T> //! type and thread safe
    inline Json::Value OdbEntityMgr::toJson(T &item) {
        return item.to_json();
    } 
    
    template<typename T> //! type and thread safe
    inline Json::Value OdbEntityMgr::toJson(shared_ptr<T> &item) {
        Json::Value val;
        if(item != nullptr){ 
           return item->to_json();
        }
        return val;
    }
     
    template<typename T> //! type and thread safe
    inline void OdbEntityMgr::toOdb(T& p, const Json::Value& v){
        if(!v.isNull()){ 
			p.to_odb(v);
		}
    }
}
}
#endif
