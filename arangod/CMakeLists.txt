# -*- mode: CMAKE; -*-

## -----------------------------------------------------------------------------
## --SECTION--                                                   COMMON INCLUDES
## -----------------------------------------------------------------------------

################################################################################
### @brief local directory
################################################################################

include_directories(.)

################################################################################
### @brief library source
################################################################################

include_directories(${PROJECT_SOURCE_DIR}/lib)

## -----------------------------------------------------------------------------
## --SECTION--                                                       EXECUTABLES
## -----------------------------------------------------------------------------

################################################################################
### @brief output directory
################################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

################################################################################
### @brief arangod
################################################################################

if (MSVC)
  SET(ARANGO_MSVC
    RestServer/WindowsServiceUtils.cpp
  )
endif ()


add_executable(
    ${BIN_ARANGOD}
    ${ARANGO_MSVC}
    Actions/actions.cpp
    Actions/RestActionHandler.cpp
    Aql/AqlItemBlock.cpp
    Aql/AqlValue.cpp
    Aql/Ast.cpp
    Aql/AstNode.cpp
    Aql/BindParameters.cpp
    Aql/Collection.cpp
    Aql/CollectionScanner.cpp
    Aql/ExecutionBlock.cpp
    Aql/ExecutionEngine.cpp
    Aql/ExecutionNode.cpp
    Aql/ExecutionPlan.cpp
    Aql/ExecutionStats.cpp
    Aql/Executor.cpp
    Aql/Expression.cpp
    Aql/Function.cpp
    Aql/Functions.cpp
    Aql/grammar.cpp
    Aql/NodeFinder.cpp
    Aql/Optimizer.cpp
    Aql/OptimizerRules.cpp
    Aql/Parser.cpp
    Aql/Query.cpp
    Aql/QueryList.cpp
    Aql/QueryRegistry.cpp
    Aql/RangeInfo.cpp
    Aql/Range.cpp
    Aql/RestAqlHandler.cpp
    Aql/Scopes.cpp
    Aql/tokens.cpp
    Aql/V8Expression.cpp
    Aql/Variable.cpp
    Aql/VariableGenerator.cpp
    Aql/ModificationOptions.cpp
    CapConstraint/cap-constraint.cpp
    Cluster/AgencyComm.cpp
    Cluster/ApplicationCluster.cpp
    Cluster/ClusterComm.cpp
    Cluster/ClusterInfo.cpp
    Cluster/ClusterMethods.cpp
    Cluster/HeartbeatThread.cpp
    Cluster/RestShardHandler.cpp
    Cluster/ServerJob.cpp
    Cluster/ServerState.cpp
    Cluster/v8-cluster.cpp
    FulltextIndex/fulltext-handles.cpp
    FulltextIndex/fulltext-index.cpp
    FulltextIndex/fulltext-list.cpp
    FulltextIndex/fulltext-query.cpp
    FulltextIndex/fulltext-result.cpp
    FulltextIndex/fulltext-wordlist.cpp
    GeoIndex/GeoIndex.cpp
    GeoIndex/geo-index.cpp
    HashIndex/hash-array.cpp
    HashIndex/hash-array-multi.cpp
    HashIndex/hash-index.cpp
    IndexOperators/index-operator.cpp
    Replication/ContinuousSyncer.cpp
    Replication/InitialSyncer.cpp
    Replication/Syncer.cpp
    RestHandler/RestBatchHandler.cpp
    RestHandler/RestCursorHandler.cpp
    RestHandler/RestDocumentHandler.cpp
    RestHandler/RestEdgeHandler.cpp
    RestHandler/RestExportHandler.cpp
    RestHandler/RestImportHandler.cpp
    RestHandler/RestPleaseUpgradeHandler.cpp
    RestHandler/RestQueryHandler.cpp
    RestHandler/RestReplicationHandler.cpp
    RestHandler/RestUploadHandler.cpp
    RestHandler/RestVocbaseBaseHandler.cpp
    RestServer/ArangoServer.cpp
    RestServer/ConsoleThread.cpp
    RestServer/VocbaseContext.cpp
    RestServer/arangod.cpp
    SkipLists/skiplistIndex.cpp
    Utils/CollectionExport.cpp
    Utils/Cursor.cpp
    Utils/CursorRepository.cpp
    Utils/DocumentHelper.cpp
    Utils/StandaloneTransactionContext.cpp
    Utils/Transaction.cpp
    Utils/TransactionContext.cpp
    Utils/V8TransactionContext.cpp
    V8Server/ApplicationV8.cpp
    V8Server/V8DispatcherThread.cpp
    V8Server/V8Job.cpp
    V8Server/V8PeriodicTask.cpp
    V8Server/V8QueueJob.cpp
    V8Server/V8TimerTask.cpp
    V8Server/v8-actions.cpp
    V8Server/v8-collection.cpp
    V8Server/v8-collection-util.cpp
    V8Server/v8-dispatcher.cpp
    V8Server/v8-query.cpp
    V8Server/v8-replication.cpp
    V8Server/v8-user-structures.cpp
    V8Server/v8-util.cpp
    V8Server/v8-vocbase.cpp
    V8Server/v8-voccursor.cpp
    V8Server/v8-vocindex.cpp
    V8Server/v8-wrapshapedjson.cpp
    VocBase/auth.cpp
    VocBase/barrier.cpp
    VocBase/cleanup.cpp
    VocBase/collection.cpp
    VocBase/compactor.cpp
    VocBase/datafile.cpp
    VocBase/document-collection.cpp
    VocBase/edge-collection.cpp
    VocBase/headers.cpp
    VocBase/index.cpp
    VocBase/key-generator.cpp
    VocBase/primary-index.cpp
    VocBase/replication-applier.cpp
    VocBase/replication-common.cpp
    VocBase/replication-dump.cpp
    VocBase/replication-master.cpp
    VocBase/server.cpp
    VocBase/transaction.cpp
    VocBase/voc-shaper.cpp
    VocBase/vocbase.cpp
    VocBase/vocbase-defaults.cpp
    Wal/AllocatorThread.cpp
    Wal/CollectorThread.cpp
    Wal/LogfileManager.cpp
    Wal/Logfile.cpp
    Wal/Marker.cpp
    Wal/RecoverState.cpp
    Wal/RemoverThread.cpp
    Wal/Slot.cpp
    Wal/Slots.cpp
    Wal/SynchroniserThread.cpp
)

target_link_libraries(
    ${BIN_ARANGOD}
    ${LIB_ARANGO_FE}
    ${LIB_ARANGO_V8}
    ${LIB_ARANGO}
    ${LIBEV_LIBS}
    ${V8_LIBS} # need this for rest::Version
    ${ICU_LIBS}
    ${BT_LIBS}
    ${ZLIB_LIBS}
    ${READLINE_LIBS}
    ${OPENSSL_LIBS}
    ${CMAKE_THREAD_LIBS_INIT}
    ${MSVC_LIBS}
)

################################################################################
### @brief install arangod binary
################################################################################

install(
  TARGETS ${BIN_ARANGOD}
  RUNTIME DESTINATION ${TRI_SBINDIR_INSTALL})

################################################################################
### @brief install arangod config
################################################################################

install_config(arangod)

################################################################################
### @brief install arango-dfdb binary
################################################################################

install_command_alias(${BIN_ARANGOD} ${TRI_SBINDIR_INSTALL} arango-dfdb)

################################################################################
### @brief install arango-dfdb config
################################################################################

install_config(arango-dfdb)

################################################################################
### @brief install server-side JavaScript files
################################################################################

install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/js/common ${PROJECT_SOURCE_DIR}/js/server ${PROJECT_SOURCE_DIR}/js/actions
  DESTINATION share/arangodb/js
  FILES_MATCHING PATTERN "*.js" PATTERN "*.tmpl"
  REGEX "^.*/common/test-data$" EXCLUDE
  REGEX "^.*/common/tests$" EXCLUDE
  REGEX "^.*/server/tests$" EXCLUDE)

install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/js/node 
  DESTINATION share/arangodb/js
  REGEX ".travis.yml" EXCLUDE
  REGEX ".npmignore" EXCLUDE
  PATTERN "_db" EXCLUDE)

install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/js/apps/system/_admin
  DESTINATION share/arangodb/js/apps/system
  REGEX "/node_modules/" EXCLUDE
  REGEX "/test/" EXCLUDE
  REGEX "/test_data/" EXCLUDE
  REGEX "/coverage/" EXCLUDE
  PATTERN "_db" EXCLUDE)

install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/js/apps/system/_api ${PROJECT_SOURCE_DIR}/js/apps/system/_system
  DESTINATION share/arangodb/js/apps/system
  REGEX "/test/" EXCLUDE
  REGEX "/test_data/" EXCLUDE
  PATTERN "_db" EXCLUDE)

################################################################################
### @brief install log directory
################################################################################

install(
  DIRECTORY ${PROJECT_BINARY_DIR}/var/log/arangodb
  DESTINATION ${VARDIR_INSTALL}/log)

################################################################################
### @brief install database directory
################################################################################

install(
  DIRECTORY ${PROJECT_BINARY_DIR}/var/lib/arangodb
  DESTINATION ${VARDIR_INSTALL}/lib)

################################################################################
### @brief install apps directory
################################################################################

install(
  DIRECTORY ${PROJECT_BINARY_DIR}/var/lib/arangodb-apps
  DESTINATION ${VARDIR_INSTALL}/lib)

## -----------------------------------------------------------------------------
## --SECTION--                                                       END-OF-FILE
## -----------------------------------------------------------------------------

## Local Variables:
## mode: outline-minor
## outline-regexp: "### @brief\\|## --SECTION--\\|# -\\*- "
## End:
