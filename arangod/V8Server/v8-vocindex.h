////////////////////////////////////////////////////////////////////////////////
/// @brief V8-vocbase bridge
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2014 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
/// @author Copyright 2014, ArangoDB GmbH, Cologne, Germany
/// @author Copyright 2011-2013, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef ARANGODB_V8SERVER_V8__INDEX_H
#define ARANGODB_V8SERVER_V8__INDEX_H 1

#include "Basics/Common.h"
#include "Utils/CollectionNameResolver.h"
#include "VocBase/index.h"
#include "VocBase/server.h"
#include "V8/v8-globals.h"
#include "V8Server/v8-vocbase.h"

namespace triagens {
  namespace mvcc {
    class Index;
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief looks up a index identifier
////////////////////////////////////////////////////////////////////////////////

triagens::mvcc::Index* TRI_LookupMvccIndexByHandle (v8::Isolate*,
                                                    triagens::arango::CollectionNameResolver const*,
                                                    TRI_vocbase_col_t const*,
                                                    v8::Handle<v8::Value> const);

////////////////////////////////////////////////////////////////////////////////
/// @brief initializer for database index management functions
////////////////////////////////////////////////////////////////////////////////

void TRI_InitV8IndexArangoDB (v8::Isolate*,
                              v8::Handle<v8::ObjectTemplate>);

////////////////////////////////////////////////////////////////////////////////
/// @brief initializer for collection index management functions
////////////////////////////////////////////////////////////////////////////////

void TRI_InitV8IndexCollection (v8::Isolate*,
                                v8::Handle<v8::ObjectTemplate>);

#endif
