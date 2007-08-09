/**
 *  @file	FastSharedMutexFactory.h
 *
 *	@brief	Header file for the fast shared mutex factory class.
 *
 *	$Log: $
 */

#if !defined (ACTIV_BASE_FAST_SHARED_MUTEX_FACTORY_H)
#define ACTIV_BASE_FAST_SHARED_MUTEX_FACTORY_H

#include "ActivMiddleware/ActivBase/External.h"
#include "ActivMiddleware/ActivBase/IMutex.h"
#include "ActivMiddleware/ActivBase/Timeout.h"

#include <string>

namespace Activ
{

/**
 *	@brief	Fast shared mutex factory class.
 */
class FastSharedMutexFactory
{
public:
	/**
     *	@brief	Create a mutex.
	 *
	 *	@param	name the mutex name.
	 *	@param	isInitialOwner whether the mutex is initially locked on creation.
	 *
	 *	@return	pointer to an object providing an IMutex interface.
	 *
	 *	@throw	Exception.
     */
	ACTIV_BASE_API IMutex *Create(const std::string &name, const bool isInitialOwner = false);

	/**
     *	@brief	Open an existing mutex.
	 *
	 *	@param	name the mutex name.
	 *	@param	timeout how long to wait for the object to exist, in ms.
	 *
	 *	@return	pointer to an object providing an IMutex interface.
	 *
	 *	@throw	Exception.
     */
	ACTIV_BASE_API IMutex *Open(const std::string &name, Timeout &timeout = Timeout::GetInfinite());

	/**
	 *	@brief	Get the instance of the factory object.
	 */
	ACTIV_BASE_API static FastSharedMutexFactory &GetInstance();

private:
    /**
     *	@brief	Destructor.
     */
	~FastSharedMutexFactory();

	static FastSharedMutexFactory	m_factory;					///< Singleton fast shared mutex factory
};

} // namespace Activ

#endif // !defined (ACTIV_BASE_FAST_SHARED_MUTEX_FACTORY_H)
