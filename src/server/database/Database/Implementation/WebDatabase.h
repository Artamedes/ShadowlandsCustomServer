#pragma once

#include "MySQLConnection.h"

enum WebDatabaseStatements : uint32
{
    WEB_SEL_DP,
    WEB_SEL_VP,
    WEB_UPD_DP,
    WEB_UPD_VP,
    MAX_WEBDATABASE_STATEMENTS
};

class TC_DATABASE_API WebDatabaseConnection : public MySQLConnection
{
public:
    typedef WebDatabaseStatements Statements;

    //- Constructors for sync and async connections
    WebDatabaseConnection(MySQLConnectionInfo& connInfo);
    WebDatabaseConnection(ProducerConsumerQueue<SQLOperation*>* q, MySQLConnectionInfo& connInfo);
    ~WebDatabaseConnection();

    //- Loads database type specific prepared statements
    void DoPrepareStatements() override;
};
