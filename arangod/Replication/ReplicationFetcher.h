////////////////////////////////////////////////////////////////////////////////
/// @brief replication data fetcher
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2004-2013 triAGENS GmbH, Cologne, Germany
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
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Jan Steemann
/// @author Copyright 2013, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_REPLICATION_REPLICATION_FETCHER_H
#define TRIAGENS_REPLICATION_REPLICATION_FETCHER_H 1

#include "Basics/Common.h"

#include "Logger/Logger.h"
#include "VocBase/replication.h"
#include "VocBase/server-id.h"

// -----------------------------------------------------------------------------
// --SECTION--                                              forward declarations
// -----------------------------------------------------------------------------
  
struct TRI_json_s;
struct TRI_transaction_collection_s;
struct TRI_vocbase_s;
struct TRI_vocbase_col_s;

namespace triagens {

  namespace httpclient {
    class GeneralClientConnection;
    class SimpleHttpClient;
    class SimpleHttpResult;
  }
  
  namespace rest {
    class Endpoint;
  }

  namespace arango {

// -----------------------------------------------------------------------------
// --SECTION--                                                ReplicationFetcher
// -----------------------------------------------------------------------------

    class ReplicationFetcher {

// -----------------------------------------------------------------------------
// --SECTION--                                                     private types
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      private:

////////////////////////////////////////////////////////////////////////////////
/// @brief replication apply setup phase
////////////////////////////////////////////////////////////////////////////////

        typedef enum {
          PHASE_DROP,
          PHASE_CREATE,
          PHASE_DATA
        }
        setup_phase_e;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                      constructors and destructors
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      public:

////////////////////////////////////////////////////////////////////////////////
/// @brief constructor
////////////////////////////////////////////////////////////////////////////////

        ReplicationFetcher (struct TRI_vocbase_s*,
                            const std::string&,
                            double);

////////////////////////////////////////////////////////////////////////////////
/// @brief destructor
////////////////////////////////////////////////////////////////////////////////
        
        ~ReplicationFetcher ();

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                    public methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      public:

////////////////////////////////////////////////////////////////////////////////
/// @brief run method
////////////////////////////////////////////////////////////////////////////////

        int run ();

////////////////////////////////////////////////////////////////////////////////
/// @brief comparator to sort collections
/// sort order is by collection type first (vertices before edges), then name 
////////////////////////////////////////////////////////////////////////////////

        static int sortCollections (const void*, const void*);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                   private methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      private:

////////////////////////////////////////////////////////////////////////////////
/// @brief apply the data from a collection dump
////////////////////////////////////////////////////////////////////////////////

        int applyMarker (struct TRI_transaction_collection_s*,
                         char const*,
                         const TRI_voc_key_t,
                         struct TRI_json_s const*,
                         string&);

////////////////////////////////////////////////////////////////////////////////
/// @brief apply the data from a collection dump
////////////////////////////////////////////////////////////////////////////////

        int applyCollectionDump (struct TRI_transaction_collection_s*,
                                 httpclient::SimpleHttpResult*,
                                 string&);

////////////////////////////////////////////////////////////////////////////////
/// @brief get local replication apply state
////////////////////////////////////////////////////////////////////////////////

        int getLocalState (string&);

////////////////////////////////////////////////////////////////////////////////
/// @brief get master state
////////////////////////////////////////////////////////////////////////////////

        int getMasterState (string&);

////////////////////////////////////////////////////////////////////////////////
/// @brief get master inventory
////////////////////////////////////////////////////////////////////////////////

        int getMasterInventory (string&);

////////////////////////////////////////////////////////////////////////////////
/// @brief incrementally fetch data from a collection
////////////////////////////////////////////////////////////////////////////////

        int handleCollectionDump (struct TRI_transaction_collection_s*,
                                  TRI_voc_tick_t,
                                  string&);

////////////////////////////////////////////////////////////////////////////////
/// @brief handle the information about a collection
////////////////////////////////////////////////////////////////////////////////

        int handleCollectionInitial (struct TRI_json_s const*, 
                                     string&, 
                                     setup_phase_e);

////////////////////////////////////////////////////////////////////////////////
/// @brief handle the state response of the master
////////////////////////////////////////////////////////////////////////////////

        int handleStateResponse (struct TRI_json_s const*, 
                                 string&);

////////////////////////////////////////////////////////////////////////////////
/// @brief handle the inventory response of the master
////////////////////////////////////////////////////////////////////////////////

        int handleInventoryResponse (struct TRI_json_s const*, string&);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                 private variables
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      private:
       
        struct TRI_vocbase_s* _vocbase;

        TRI_replication_master_info_t _masterInfo;
  
        TRI_replication_apply_state_t _applyState;

        rest::Endpoint* _endpoint;

        httpclient::GeneralClientConnection* _connection;
        
        httpclient::SimpleHttpClient* _client;

    };

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

  }
}

#endif

// Local Variables:
// mode: outline-minor
// outline-regexp: "/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|/// @page\\|// --SECTION--\\|/// @\\}"
// End:
