# **Template Method 模式**

**动机（Motivation）** 

- 在软件构建过程中，对于某一项任务，它常常有稳定的整体操作结构，但各个子步骤却有很多改变的需求，或者由于固有的原因 （比如框架与应用之间的关系）而无法和任务的整体结构同时实现。 

- 如何在确定稳定操作结构的前提下，来灵活应对各个子步骤的变化或者晚期实现需求？ 

![微信截图_20200813182718](picture\微信截图_20200813182718.png)

![微信截图_20200813183019](picture\微信截图_20200813183019.png)

![微信截图_20200813183106](picture\微信截图_20200813183106.png)

## **模式定义** 

定义一个操作中的算法的骨架 (稳定)，而将一些步骤延迟(变化)到子类中。Template Method使得子类可以不改变 (复用)一个算法的结构即可重定义(override 重写)该算法的某些特定步骤。 

 																					——《设计模式》GoF

![微信截图_20200813183312](picture\微信截图_20200813183312.png)

## **要点总结** 

- Template Method模式是一种非常基础性的设计模式，在面向对 象系统中有着大量的应用。它用最简洁的机制（虚函数的多态性）为很多应用程序框架提供了灵活的扩展点，是代码复用方面的基本实现结构。 

- 除了可以灵活应对子步骤的变化外，“不要调用我，让我来调用你”的反向控制结构是Template Method的典型应用。 

- 在具体实现方面，被Template Method调用的虚方法可以具有实现，也可以没有任何实现（抽象方法、纯虚方法），但一般推荐将它们设置为protected方法。

## 示例代码

### 不好的示例

`template1_lib.cpp`

```c++
//程序库开发人员
class Library{

public:
	void Step1(){
		//...
	}

    void Step3(){
		//...
    }

    void Step5(){
		//...
    }
};
```

`template1_app.cpp`

```c++
//应用程序开发人员
class Application{
public:
	bool Step2(){
		//...
    }

    void Step4(){
		//...
    }
};

int main()
{
	Library lib();
	Application app();

	lib.Step1();

	if (app.Step2()){
		lib.Step3();
	}

	for (int i = 0; i < 4; i++){
		app.Step4();
	}

	lib.Step5();
}
```

### 优化后的代码

`template2_lib.cpp`

```c++
//程序库开发人员
class Library{
public:
	//稳定 template method
    void Run(){
        
        Step1();

        if (Step2()) { //支持变化 ==> 虚函数的多态调用
            Step3(); 
        }

        for (int i = 0; i < 4; i++){
            Step4(); //支持变化 ==> 虚函数的多态调用
        }

        Step5();

    }
	virtual ~Library(){ }

protected:
	
	void Step1() { //稳定
        //.....
    }
	void Step3() {//稳定
        //.....
    }
	void Step5() { //稳定
		//.....
	}

	virtual bool Step2() = 0;//变化
    virtual void Step4() =0; //变化
};
```

``template1_app.cpp``

```c++
//应用程序开发人员
class Application : public Library {
protected:
	virtual bool Step2(){
		//... 子类重写实现
    }

    virtual void Step4() {
		//... 子类重写实现
    }
};

int main()
	{
	    Library* pLib=new Application();
	    lib->Run();

		delete pLib;
	}
}
```

