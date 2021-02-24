# **Abstract Factory 抽象工厂**

## **动机（Motivation）** 

- 软件系统中，经常面临着“一系列相互依赖的对象”的创建工作；同时，由于需求的变化，往往存在更多系列对象的创建工作。 

- 如何应对这种变化？如何绕过常规的对象创建方法(new)，提供一种“封装机制”来避免客户程序和这种“多系列具体对象创建工作” 的紧耦合？

## **模式定义** 

提供一个接口，让该接口负责创建一系列“相关或者相互依赖的对象”，无需指定它们具体的类。 

​																						 ——《设计模式》GoF 

## **结构（Structure）** 

![微信截图_20200825141403](picture\微信截图_20200825141403.png)

## **要点总结** 

- 如果没有应对“多系列对象构建”的需求变化，则没有必要使用Abstract Factory模式，这时候使用简单的工厂完全可以。 

- “系列对象”指的是在某一特定系列下的对象之间有相互依赖、 或作用的关系。不同系列的对象之间不能相互依赖。 

- Abstract Factory模式主要在于应对“新系列”的需求变动。其缺点在于难以应对“新对象”的需求变动。

## 示例代码

### 不好的代码

`EmpolyeeDA01.cpp`

```c++

//此类需要根据业务需要进行变化，此时只支持sql的数据库
class EmployeeDAO{
    
public:
    vector<EmployeeDO> GetEmployees(){
        SqlConnection* connection =
            new SqlConnection();
        connection->ConnectionString = "...";

        SqlCommand* command =
            new SqlCommand();
        command->CommandText="...";
        command->SetConnection(connection);

        SqlDataReader* reader = command->ExecuteReader();
        while (reader->Read()){

        }

    }
};
```

### 好的代码

`EmployeeDA02.cpp`

```c++

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
```

### 更加好的代码

`EmployeeDA03.cpp`

```c++

//数据库访问有关的基类
class IDBConnection{
    
};

class IDBCommand{
    
};

class IDataReader{
    
};


class IDBFactory{
public:
    virtual IDBConnection* CreateDBConnection()=0;
    virtual IDBCommand* CreateDBCommand()=0;
    virtual IDataReader* CreateDataReader()=0;
    
};


//支持SQL Server
class SqlConnection: public IDBConnection{
    
};
class SqlCommand: public IDBCommand{
    
};
class SqlDataReader: public IDataReader{
    
};


class SqlDBFactory:public IDBFactory{
public:
    virtual IDBConnection* CreateDBConnection{
		return new SqlConnection();
	}
    virtual IDBCommand* CreateDBCommand{
		return new SqlCommand();
	}
    virtual IDataReader* CreateDataReader{
		return new SqlDataReader();
	}
};

//支持Oracle
class OracleConnection: public IDBConnection{
    
};

class OracleCommand: public IDBCommand{
    
};

class OracleDataReader: public IDataReader{
    
};
//这样设计的工厂可以防止，各个工厂生成出来的部件，没有正确的组合在一起。
class OracleDBFactory:public IDBFactory{
public:
    virtual IDBConnection* CreateDBConnection{
		return new OracleConnection();
	}
    virtual IDBCommand* CreateDBCommand{
		return new OracleCommand();
	}
    virtual IDataReader* CreateDataReader{
		return new OracleDataReader();
	}
 
};

//EmployeeDAO变成稳定的部分。
class EmployeeDAO{
    IDBFactory* dbFactory;
    
public:
    vector<EmployeeDO> GetEmployees(){
        IDBConnection* connection =
            dbFactory->CreateDBConnection();
        connection->ConnectionString("...");

        IDBCommand* command =
            dbFactory->CreateDBCommand();
        command->CommandText("...");
        command->SetConnection(connection); //关联性

        IDBDataReader* reader = command->ExecuteReader(); //关联性
        while (reader->Read()){

        }

    }
};
```

