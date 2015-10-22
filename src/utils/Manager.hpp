/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-10-22
* Description:
* * * * * * * * * * * * * * * */

#ifndef MANAGER_HPP_
#define MANAGER_HPP_ 

#include <vector>
#include "maraton.h"
#include <mutex>

template<class T>
class Manager
{
public:

    virtual void push( T* instance )
    {
        std::unique_lock<std::mutex> lck( mtx );

        this->instance_.push_back( instance );
    }

    virtual void remove( T* instance )
    {
        std::unique_lock<std::mutex> lck( mtx );

        std::vector<T*>::iterator itr = this->instance_.begin();

        while ( itr != this->instance_.end() )
        {

            if ( *itr == instance )
            {
                itr = this->instance_.erase( itr );
                SAFE_DELETE( instance );
                break;
            }
            else
            {
                itr++;
            }
        }

    }

protected:

    std::vector<T*> instances() 
    {
        std::unique_lock<std::mutex> lck( mtx );

        std::vector<T*> vret( this->instance_.begin(), this->instance_.end() );

        return vret;
    }

    std::vector<T*> instance_;

private:

    std::mutex mtx;
};
 
#endif //!MANAGER_HPP_ 