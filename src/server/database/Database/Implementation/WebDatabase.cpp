
#include "WebDatabase.h"
#include "MySQLPreparedStatement.h"

void WebDatabaseConnection::DoPrepareStatements()
{
    if (!m_reconnecting)
        m_stmts.resize(MAX_WEBDATABASE_STATEMENTS);

    PrepareStatement(WEB_SEL_DP, "SELECT dp from account_data WHERE id = ?", CONNECTION_BOTH);
    PrepareStatement(WEB_SEL_VP, "SELECT vp from account_data WHERE id = ?", CONNECTION_BOTH);
    PrepareStatement(WEB_UPD_DP, "UPDATE account_data SET dp = ? WHERE id = ?", CONNECTION_BOTH);
    PrepareStatement(WEB_UPD_VP, "UPDATE account_data SET vp = ? WHERE id = ?", CONNECTION_BOTH);
}

WebDatabaseConnection::WebDatabaseConnection(MySQLConnectionInfo& connInfo) : MySQLConnection(connInfo)
{
}

WebDatabaseConnection::WebDatabaseConnection(ProducerConsumerQueue<SQLOperation*>* q, MySQLConnectionInfo& connInfo) : MySQLConnection(q, connInfo)
{
}

WebDatabaseConnection::~WebDatabaseConnection()
{
}
