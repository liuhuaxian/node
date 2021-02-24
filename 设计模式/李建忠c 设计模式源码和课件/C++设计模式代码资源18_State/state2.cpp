class NetworkState{

public:
    NetworkState* pNext;
    virtual void Operation1()=0;
    virtual void Operation2()=0;
    virtual void Operation3()=0;

    virtual ~NetworkState(){}
};


class OpenState :public NetworkState{
   
    static NetworkState* m_instance;
public:
    static NetworkState* getInstance(){
        if (m_instance == nullptr) {
            m_instance = new OpenState(); //通过多态指针动态的识别当前的状态。
        }
        return m_instance;
    }

    void Operation1(){
        
        //**********
        pNext = CloseState::getInstance();
    }
    
    void Operation2(){
        
        //..........
        pNext = ConnectState::getInstance(); //指定open成功后的下一个状态为connect状态。
    }
    
    void Operation3(){
        
        //$$$$$$$$$$
        pNext = OpenState::getInstance();
    }
    
    
};

class CloseState:public NetworkState{ }
//...


class NetworkProcessor{
    
    NetworkState* pState;
    
public:
    
    NetworkProcessor(NetworkState* pState){
        
        this->pState = pState;
    }
    
    void Operation1(){
        //...
        pState->Operation1();
        pState = pState->pNext;//多态指针动态的指定下一个状态。
        //...
    }
    
    void Operation2(){
        //...
        pState->Operation2();
        pState = pState->pNext;
        //...
    }
    
    void Operation3(){
        //...
        pState->Operation3();
        pState = pState->pNext;
        //...
    }

};


