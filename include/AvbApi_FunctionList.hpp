#pragma once

/*
Copyright (c) 2014, Jeff Koftinoff
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "AvbApi_world.hpp"

namespace AvbApi2014
{
typedef uint32_t FunctionId;

class FunctionListBase
{
public:
    FunctionId nextId()
    {
        return m_nextFunctionId++;
    }

    virtual void remove( FunctionId fid ) = 0;

private:
    std::atomic<FunctionId> m_nextFunctionId;
};

template <typename F>
class FunctionList : public FunctionListBase
{
  public:
    using function_type = std::function<F>;
    using item_type = pair<FunctionId, function_type>;

    template <typename... Args>
    void operator()( Args... args ) const
    {
        for ( auto &i : m_functions )
        {
            i.second( args... );
        }
    }

    FunctionId add( function_type f )
    {
        FunctionId fid = nextId();
        m_functions.emplace_back( make_pair( fid, f ) );
        return fid;
    }

    virtual void remove( FunctionId fid )
    {
        m_functions.erase( std::remove_if( m_functions.begin(),
                                           m_functions.end(),
                                           [&]( item_type const &item )
                                           {
                               return item.first == fid;
                           } ),
                           m_functions.end() );
    }

    std::vector<item_type> m_functions;


    class Registrar
    {
      public:
        Registrar( FunctionList &functionList, function_type func )
            : m_functionList(functionList)
            , m_fid( m_functionList.add( func ) )
        {
        }

        ~Registrar()
        {
            m_functionList.remove(m_fid);
        }

        FunctionList &m_functionList;
        FunctionId m_fid;
    };

};

template <typename FunctionListT>
auto registerFunction( FunctionListT &functionList, typename FunctionListT::function_type func ) -> typename FunctionListT::Registrar
{
    return typename FunctionListT::Registrar(functionList,func);
}


}
