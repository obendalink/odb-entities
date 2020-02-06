/*Author obendalink@gmail.com
 @copyright bunilab.com
*/
#ifndef ODB_REPOSITORY_H
#define ODB_REPOSITORY_H

#include <bqc_global.h>

#include <type_traits>
#include <typeinfo>

#include <DbConnector.h> // create_database
#include <entities_global.h>
#include <OdbEntityMgr.hpp>

using namespace std;
using namespace odb::core;
using namespace log4cxx;
using namespace log4cxx::helpers;
namespace bqc
{
	namespace base
	{ 
		typedef struct{
			LoggerPtr 	log; 
		}OdbRepository_Dt;
		
		template<class T>
		class OdbRepository;

		template<class T>
		class OdbRepository {

		private:
			std::vector<T> elems;    // elements
		protected:
			shared_ptr<OdbRepository_Dt> m;
			OdbEntityMgr em;
		public:
			OdbRepository();

			void deleteAllInBatch();//Deletes all entities in a batch call.
			void deleteInBatch(const std::vector<long> entities);//Deletes the given entities in a batch which means it will create a single Query.
			std::vector<T> findAll(); 
			bool findAll(std::vector<T>& items);
			std::vector<T> findBy(const odb::query<T> &query); 
			bool findBy(std::vector<T>& ,const odb::query<T> &query); 
			std::vector<T> findAllById(const std::vector<long> &ids = std::vector<long>()); 
			void flush();//Flushes all pending changes to the database.
			bool findOne(T& item,const typename odb::object_traits<T>::id_type& id); //!if return value is false it means it was not found! 
			bool findOne(T& item,const odb::query<T> &query); //!if return value is false it means it was not found!  
			shared_ptr<T> findOne(const typename odb::object_traits<T>::id_type& id);//Returns a [shared_ptr<T>] reference to the entity with the given identifier. if pointer value is nullptr it means it was not found!
			shared_ptr<T> findOne(const odb::query<T> &query);//Returns a [shared_ptr<T>] reference to the entity with the given identifier. . if pointer value is nullptr it means it was not found!
			bool insertAll(std::vector<T> &items); 
			bool updateAll(std::vector<T> &items); 
			bool saveAll(std::vector<T> &items); 
			int count(); 
			bool deleteAll(); 
			bool deleteOne(const typename odb::object_traits<T>::id_type id); 
			bool deleteBy(const odb::query<T> &query); 
			bool existsById(const typename odb::object_traits<T>::id_type id); 
			bool existsBy(const odb::query<T> &query); 
			typename odb::object_traits<T>::id_type insertOne(T &item); //[T &item)] is preferred to [shared_ptr<T>] during saving to make sure you don't save nullptr 
			bool updateOne(T &item); //[T &item)] is preferred to [shared_ptr<T>] during saving to make sure you don't save nullptr 
			typename odb::object_traits<T>::id_type saveOne(T &item);//[T &item)] is preferred to [shared_ptr<T>] during saving to make sure you don't save nullptr
		 
		};


		template<class T>
		OdbRepository<T>::OdbRepository() {
		}
		template<class T>
		bool OdbRepository<T>::findOne(T& item,const typename odb::object_traits<T>::id_type& id) {
			return em.findOne<T>(item,id);
		}
		
		template<class T>
		bool OdbRepository<T>::findOne(T& item,const odb::query<T> &query) {
			return em.findOne<T>(item,query);
		}
		
		template<class T>
		shared_ptr<T> OdbRepository<T>::findOne(const typename odb::object_traits<T>::id_type& id) { 
			return em.findOne<T>(id);
		}

		template<class T>
		shared_ptr<T> OdbRepository<T>::findOne(const odb::query<T> &query) {
			return em.findOne<T>(query);
		}

		template<class T>
		bool OdbRepository<T>::existsById(const typename odb::object_traits<T>::id_type id) {
			return em.existsById<T>(id);
		}

		template<class T>
		bool OdbRepository<T>::existsBy(const odb::query<T> &query) {
			return em.existsBy<T>(query);
		}

		template<class T>
		std::vector<T> OdbRepository<T>::findAll() {
			return em.findAll<T>();
		}
		
		template<class T>
		bool OdbRepository<T>::findAll(std::vector<T>& items) {
			return em.findAll<T>(items);
		}

		template<class T>
		std::vector<T> OdbRepository<T>::findBy(const odb::query<T> &query) {
			return em.findBy<T>(query);
		}
		template<class T>
		bool OdbRepository<T>::findBy(std::vector<T>& items,const odb::query<T> &query) {
			return em.findBy<T>(items,query);
		}

		template<class T>
		bool OdbRepository<T>::deleteOne(const typename odb::object_traits<T>::id_type id) {
			return em.deleteOne<T>(id);
		}

		template<class T>
		bool OdbRepository<T>::deleteBy(const odb::query<T> &query) {
			return em.deleteBy<T>(query);;
		}

		template<class T>
		typename odb::object_traits<T>::id_type OdbRepository<T>::insertOne(T &item) {
			return em.insertOne<T>(item);
		}

		template<class T>
		bool OdbRepository<T>::updateOne(T &item) {
			return em.updateOne<T>(item);
		}
 
		template<class T>
		typename odb::object_traits<T>::id_type OdbRepository<T>::saveOne(T &item) {
			return em.saveOne<T>(item);
		}

		template<class T>
		bool OdbRepository<T>::insertAll(std::vector<T> &items) {
			return em.insertAll<T>(items);
		}

		template<class T>
		bool OdbRepository<T>::updateAll(std::vector<T> &items) {
			return em.updateAll<T>(items);
		}

		template<class T>
		bool OdbRepository<T>::saveAll(std::vector<T> &items) {
			return em.saveAll<T>(items);
		}

};//end base
};//end bqc

#endif
