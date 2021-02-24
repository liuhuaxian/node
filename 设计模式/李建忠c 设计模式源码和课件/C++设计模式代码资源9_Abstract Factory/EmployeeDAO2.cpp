
//数据库访问有关的基类
class IDBConnection{
    
};

class IDBConnectionFactory{
public:
    virtual IDBConnection* CreateDBConnection()=0;
};


class IDBCommand{
    
};

class IDBCommandFactory{
public:
    virtual IDBCommand* CreateDBCommand()=0;
};


class IDataReader{
    
};

class IDataReaderFactory{
public:
    virtual IDataReader* CreateDataReader()=0;
};
/*********************************以上是基类工厂供继承，以提供多态指针。***********************************/

//支持SQL Server
class SqlConnection: public IDBConnection{
    
};
class SqlConnectionFactory:public IDBConnectionFactory{
    IDBConnection* CreateDBConnection(){
		return new SqlConnection();
	}
};


class SqlCommand: public IDBCommand{
    
};
class SqlCommandFactory:public IDBCommandFactory{
		IDBCommand* CreateDBCommand(){
			return new SqlCommand();
		}
};

class SqlDataReader: public IDataReader{
    
};
class SqlDataReaderFactory:public IDataReaderFactory{
		IDataReader* CreateDataReader(){
			return new SqlDataReader();
		}
};

/*****************************以上是sql相关的数据库操作****************************************/


//支持Oracle
class OracleConnection: public IDBConnection{
    
};
class OracleConnectionFactory:public IDBConnectionFactory{
    
};


class OracleCommand: public IDBCommand{
    
};
class OracleCommandFactory:public IDBCommandFactory{
    
};


class OracleDataReader: public IDataReader{
    
};
class OracleDataReaderFactory:public IDataReaderFactory{
    
};

/******************以上是Oracal数据库相关的操作******************************/

//EmployeeDAO变成稳定的部分。
class EmployeeDAO{
    IDBConnectionFactory* dbConnectionFactory;
    IDBCommandFactory* dbCommandFactory;
    IDataReaderFactory* dataReaderFactory;
    
    
public:
    vector<EmployeeDO> GetEmployees(){
        IDBConnection* connection =
            dbConnectionFactory->CreateDBConnection();
        connection->ConnectionString("...");

        IDBCommand* command =
            dbCommandFactory->CreateDBCommand();
        command->CommandText("...");
        command->SetConnection(connection); //关联性

        IDBDataReader* reader = command->ExecuteReader(); //关联性(sql的数据库只能调用sql的指令)，此处为多态调用
        while (reader->Read()){

        }

    }
};
