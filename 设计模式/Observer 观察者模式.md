# **Observer 观察者模式**

## 动机

- 在软件构建过程中，我们需要为某些对象建立一种“通知依赖关系” ——个对象（目标对象）的状态发生改变，所有的依赖对象（观察者对象）都将得到通知。如果这样的依赖关系过于紧密，将使软件不能很好地抵御变化。 

- 使用面向对象技术，可以将这种依赖关系弱化，并形成一种稳定的依赖关系。从而实现软件体系结构的松耦合。 

## **模式定义** 

- 定义对象间的一种一对多（变化）的依赖关系，以便当一个对像(Subject)的状态发生改变时，所有依赖于它的对象都得到通知并自动更新。 

  ​																			——《设计模式》GoF

## **结构（Structure）** 

![微信截图_20200821170626](picture\微信截图_20200821170626.png)

## **要点总结** 

- 使用面向对象的抽象，Observer模式使得我们可以独立地改变目标与观察者，从而使二者之间的依赖关系达致松耦合。 

- 目标发送通知时，无需指定观察者，通知（可以携带通知信息作为参数）会自动传播。 

- 观察者自己决定是否需要订阅通知，目标对象对此一无所知。 

- Observer模式是基于事件的UI框架中非常常用的设计模式，也是MVC模式的一个重要组成部分。 

## 示例代码：

### 问题背景：

- 需要将一个大文件分割成许多的小文件，同时还需要将分割的进度，告知对其感兴趣的程序。

### 不好的设计

`FileSplitter1.cpp`

```c++
class FileSplitter
{
	string m_filePath;
	int m_fileNumber;
	ProgressBar* m_progressBar;

public:
	FileSplitter(const string& filePath, int fileNumber, ProgressBar* progressBar) :
		m_filePath(filePath), 
		m_fileNumber(fileNumber),
		m_progressBar(progressBar){

	}

	void split(){

		//1.读取大文件

		//2.分批次向小文件中写入
		for (int i = 0; i < m_fileNumber; i++){
			//...
			float progressValue = m_fileNumber;
			progressValue = (i + 1) / progressValue;
            //此处仅通知一个观察者，当需要添加多个观察者时则此处需要添加代码。
			m_progressBar->setValue(progressValue);
		}

	}
};
```

`MainForm1.cpp`

```c++
class MainForm : public Form
{
	TextBox* txtFilePath;
	TextBox* txtFileNumber;
	ProgressBar* progressBar;

public:
	void Button1_Click(){

		string filePath = txtFilePath->getText();
		int number = atoi(txtFileNumber->getText().c_str());

		FileSplitter splitter(filePath, number, progressBar);

		splitter.split();

	}
};
```

### 好的设计

`FileSpliter2.cpp`

```c++
//每个观察者都应该继承的接口。
class IProgress{
public:
	virtual void DoProgress(float value)=0;
	virtual ~IProgress(){}
};


class FileSplitter
{
	string m_filePath;
	int m_fileNumber;

	List<IProgress*>  m_iprogressList; // 抽象通知机制，支持多个观察者
	
public:
	FileSplitter(const string& filePath, int fileNumber) :
		m_filePath(filePath), 
		m_fileNumber(fileNumber){

	}


	void split(){

		//1.读取大文件

		//2.分批次向小文件中写入
		for (int i = 0; i < m_fileNumber; i++){
			//...

			float progressValue = m_fileNumber;
			progressValue = (i + 1) / progressValue;
			onProgress(progressValue);//发送通知
		}

	}


	void addIProgress(IProgress* iprogress){
		m_iprogressList.push_back(iprogress);
	}

	void removeIProgress(IProgress* iprogress){
		m_iprogressList.remove(iprogress);
	}


protected:
	virtual void onProgress(float value){
		
		List<IProgress*>::iterator itor=m_iprogressList.begin();

		while (itor != m_iprogressList.end() )
            //此处实现多态调用，只需要将观察者压入链表中就行，就自行进行多态调用。
			(*itor)->DoProgress(value); //更新进度条
			itor++;
		}
	}
};
```

`MainForm2.cpp`

```c++
class MainForm : public Form, public IProgress
{
	TextBox* txtFilePath;
	TextBox* txtFileNumber;

	ProgressBar* progressBar;

public:
	void Button1_Click(){

		string filePath = txtFilePath->getText();
		int number = atoi(txtFileNumber->getText().c_str());

		ConsoleNotifier cn;

		FileSplitter splitter(filePath, number);
//当业务需要添加多一个观察者，只需要在这里添加一行代码就可以。
		splitter.addIProgress(this); //订阅通知
		splitter.addIProgress(&cn)； //订阅通知

		splitter.split();

		splitter.removeIProgress(this); //取消订阅

	}

	virtual void DoProgress(float value){
		progressBar->setValue(value);//观察者通过进度条通知用户
	}
};

class ConsoleNotifier : public IProgress {
public:
	virtual void DoProgress(float value){
		cout << ".";  //观察者通过'.'通知用户
	}
};
```

