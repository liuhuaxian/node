# Flyweight享元模式

## 动机

- 在软件系统采用纯粹对象方案的问题在于大量细粒度的对象会很快充斥在系统中，从而带来很高的运行时代价----主要指内存需要方面的代价。
- 如何在避免大量细粒度对象问题的同时，让外部客户程序仍然能够透明的使用面向对象的方式来进行操作？

## 模式定义

运用共享技术有效地支持大量细粒度的对象

​																				----《设计模式》

## 结构

![微信截图_20200825163248](picture\微信截图_20200825163248.png)

## 要点总结

- 面向对象很好的解决了抽象性的问题，但是作为一个运行在机器中的程序实体，我们需要考虑对象的代价问题。Flyweight主要解决面向对象的代价问题，一般不触及面向对象的抽象性问题。
- Flyweight采用对象的共享的做法来降低系统中对象的个数，从而降低细粒度对象给系统带来的内存压力。在具体实现方面，要注意对象状态的处理(一般是只读属性)。
- 对象的数量太大从而导致对象内存开销加大-----什么样的数量才算大？这需要我们仔细的根据具体应用情况进行评估，而不能凭空臆断。
- 类比活字印刷术，共享每个汉字，由每个汉字组合成一个模板。

## 示例代码

`FlyWeight.cpp`

```c++

class Font {
private:

    //unique object key
    string key;
    
    //object state
    //....
    
public:
    Font(const string& key){
        //...
    }
};
ß

class FontFactory{
private:
    map<string,Font* > fontPool;
    
public:
    Font* GetFont(const string& key){

        map<string,Font*>::iterator item=fontPool.find(key); 
        //同一个key只保存一份对象。没有则创建并放入fontpool中
        
        if(item!=footPool.end()){
            return fontPool[key];
        }
        else{
            Font* font = new Font(key);
            fontPool[key]= font;
            return font;
        }

    }
    
    void clear(){
        //...
    }
};
```

