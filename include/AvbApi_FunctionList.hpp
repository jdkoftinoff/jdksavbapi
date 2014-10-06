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
typedef uint64_t FunctionId;

class FunctionListCounter
{
  protected:
    static std::atomic_uint_least64_t nextFunctionId;
};

template <typename F>
class FunctionList : private FunctionListCounter
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
        FunctionId fid = nextFunctionId++;
        m_functions.emplace_back( make_pair( fid, f ) );
        return fid;
    }

    void remove( FunctionId fid )
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
};

class ScopedRegisterFunction
{
    struct ScopedRegisterFunctionHelper
    {
        FunctionId m_fid;
    };

    template <typename FunctionListT>
    struct ScopedRegisterFunctionHelperSpecial : ScopedRegisterFunctionHelper
    {
        ScopedRegisterFunctionHelperSpecial( FunctionId fid, FunctionListT &functionList )
            : ScopedRegisterFunctionHelper{fid}, m_functionList{functionList}
        {
        }

        ~ScopedRegisterFunctionHelperSpecial() { m_functionList.remove( m_fid ); }

        FunctionListT m_functionList;
    };

  public:
    template <typename FunctionListT>
    ScopedRegisterFunction( FunctionListT &functionList, typename FunctionListT::function_type func )
        : m_helper( new ScopedRegisterFunctionHelperSpecial<FunctionListT>( functionList.add( func ), functionList ) )
    {
    }

    ~ScopedRegisterFunction() {}

    unique_ptr<ScopedRegisterFunctionHelper> m_helper;
};
}
