# 进程与资源管理实验
****
## 一、实验原理
&ensp;&ensp;&ensp;&ensp;利用相应的操作系统的进程创建、删除和调度原理，通过编程语言来实现模拟一个操作系统的进程调度

## 二、实验目的
&ensp;&ensp;&ensp;&ensp;设计和实现进程与资源管理，并完成Test shell的编写，以建立系统的进程管理、调度、资源管理和分配的知识体系，从而加深对操作系统进程调度和资源管理功能的宏观理解和微观实现技术的掌握。

## 三、实验内容
&ensp;&ensp;&ensp;&ensp;在实验室提供的软硬件环境中，设计并实现一个基本的进程与资源管理器。该管理器能够完成进程的控制，如进程创建与撤销、进程的状态转换；能够基于优先级调度算法完成进程的调度，模拟时钟中断，在同优先级进程中采用时间片轮转调度算法进行调度；能够完成资源的分配与释放，并完成进程之间的同步。该管理器同时也能完成从用户终端或者指定文件读取用户命令，通过Test shell模块完成对用户命令的解释，将用户命令转化为对进程与资源控制的具体操作，并将执行结果输出到终端或指定文件中。

## 四、实验环境
- 平台：Windows
- 语言：C++

## 五、实验步骤
### 1.系统功能分析
&ensp;&ensp;&ensp;&ensp;系统应具备以下功能：

- 驱动程序（shell）
    - 从终端或者测试文件读取命令
    - 将用户需求转换成调度内核函数（即调度进程和资源管理器）
    - 在终端或输出文件中显示结果：如当前运行的进程、错误信息等。

- 进程
    - 进程的创建
    - 进程的切换
    - 进程的删除
    - 错误检测
    - 定时器中断

- 资源管理
    - 资源的申请
    - 资源的释放

### 2. 总体架构设计
&ensp;&ensp;&ensp;&ensp;系统的总体架构图如下:

![](./system.png)

&ensp;&ensp;&ensp;&ensp;图中最右边部分为进程与资源管理器，属于操作系统内核的功能。该管理器具有如下功能：完成进程创建、撤销和进程调度；完成多单元 (multi_unit)资源的管理；完成资源的申请和释放；完成错误检测和定时器中断功能。

&ensp;&ensp;&ensp;&ensp;图中间绿色部分为驱动程序 shell, 设计与实现 shell，该 shell将调度所设计的进程与资源管理器来完成测试。

&ensp;&ensp;&ensp;&ensp;图中最左端部分为：通过终端（如键盘输入）或者测试文件来给出相应的用户命令，以及模拟硬件引起的中断

### 3.具体模块设计
&ensp;&ensp;&ensp;&ensp;这里把系统分为三个模块，分别是进程模块、TEST Shell 模块和资源模块，具体的设计细节在下面会有说明，在其中类的说明中类成员没有括号，类方法有括号

&ensp;&ensp;&ensp;&ensp;系统的大体运行流程：最开始我们先通过交互解释模块来解析输入的命令来执行相应的操作，然后便进行进程的管理（进程的创建和删除）和资源的管理（资源的申请和释放），在下面每个具体的模块设计将进行详细的设计介绍。

#### 3.1 Test shell 模块：
&ensp;&ensp;&ensp;&ensp;首先是 shell 模块的设计，此模块主要的功能是解析用户输入的指令，然后执行相应的操作。在代码中我们设计一个类来表示 shell，然后读入用户的输入来执行对应的操作。下面具体类信息和代码流程细节，其中关于进程和资源模块不做详细说明。

##### 3.1.1 模块类：
- 交互界面 shell：
    - 读入用户输入，执行相应的操作：read()

##### 3.1.2 细节说明：
###### 系统启动初始化：Shell()
&ensp;&ensp;&ensp;&ensp;通过 shell 类的构造函数进行系统的初始化，在初始化中，调用 init() 函数创建初始进程（优先级为0的系统进程）：

```c++
Shell::Shell() {
    ProcessManage::init();
    instruck = NULL;
}
```

###### 对用户输入指令进行解析执行：read(std::string input)
&ensp;&ensp;&ensp;&ensp;读入用户的输入，使用字符分割获取指令的各个部分，然后对指令进行判断（是什么指令，指令参数是否符合规范），指令正确时安装相应指令调用相应的函数：

```c++
/************************************************************************/
/* 读取用户指令进行相应操作：
    input：用户输入的指令*/
/************************************************************************/
bool Shell::read(std::string s) {
    int input = 0;

    //对输入的指令进行分割解析
    instruck = new std::vector<std::string>;
    std::string delim = " ";//分隔符为空格
    Tool::split(s, delim, instruck);

    //获取命令
    std::string command = instruck->at(0);

    //匹配的同时进行指令参数检测（是否符合标准或个数是否匹配）
    //退出系统
    if(command == "q") {
        if(instruck->size() == 1) {
            return false;
        }
    }
    //创建进程
    else if(command == "cr") {
        //判断是否参数为两个，一个进程 ID,一个进程优先级
        if(instruck->size() != 3) {
            std::cout << ">>创建进程需提供进程名和优先级，请检查输入参数" << std::endl;
            std::cout << ">>";
        }
        else {
            std::string name = instruck->at(1);
            int priority = atoi(instruck->at(2).c_str());
            ProcessManage::createProcess(name, priority);
        }
    }
    //删除进程
    else if(command == "de") {
        //判断参数是否为一个，删除进程名
        if(instruck->size() != 2) {
            std::cout << ">>删除进程需提供进程名，请检查输入参数" << std::endl;
            std::cout << ">>";
        }
        else {
            std::string name = instruck->at(1);
            ProcessManage::deleteProcess(name);
        }
    }
    //申请资源
    else if(command == "req") {
        //判断参数是否为两个，资源名和申请资源数量
        if(instruck->size() != 3) {
            std::cout << ">>申请需提供资源名和数量，请检查输入参数" << std::endl;
            std::cout << ">>";
        }
        else {
            std::string name = instruck->at(1);
            int count = atoi(instruck->at(2).c_str());
            ResourceManage::requestResource(name, count);
        }
    }
    //释放资源
    else if(command == "rel") {
        //判断参数是否为一个：资源名
        if(instruck->size() != 2) {
            std::cout << ">>释放需提供资源名，请检查输入参数" << std::endl;
            std::cout << ">>";
        }
        else {
            std::string name = instruck->at(1);
            ResourceManage::releaseResource(name);
        }
    }
    //时钟中断
    else if(command == "to") {
        if(instruck->size() != 1) {
            std::cout << ">>请检查输入，help查看指令输入帮助" << std::endl;
            std::cout << ">>";
        }
        else {
            ProcessManage::timeInt();
        }
    }
    //查看进程信息
    else if(command == "list_p") {
        if(instruck->size() != 1) {
            std::cout << ">>请检查输入，help查看指令输入帮助" << std::endl;
            std::cout << ">>";
        }
        else {
            ProcessManage::listProcess();
        }
    }
    //查看系统资源信息
    else if(command == "list_r") {
        if(instruck->size() != 1) {
            std::cout << ">>请检查输入，help查看指令输入帮助" << std::endl;
            std::cout << ">>";
        }
        else {
            ResourceManage::listResource();
        }
    }
    //输入错误
    else {
        std::cout << ">>请检查输入，help查看指令输入帮助" << std::endl;
        std::cout << ">>";
    }

    //释放相应指针资源
    delete(instruck);

    return true;
}
```

#### 3.2 进程模块：
&ensp;&ensp;&ensp;&ensp;进程模块较为复杂，以下活动有几个要点需要注意：
- 进程初始化：进程初始化时系统会自动创建一个初始进程，其优先级为0，最高优先级，是后面所有进行的父进程
- 进程创建：创建一个新的进程会导致一次进程调度，重新检查进程的优先级，如果当前新建的进程的优先级比正在运行的进程的优先级高，那么当前正在运行的进程停止运行，进入就绪等待队列，新建进程运行
- 删除进程：删除一个进程，也会导致一次进程调度，因为删除一个进程后会释放相应获得的资源，而其他进程可也申请相应的资源而进入就绪队列
- 时钟中断：停止当前运行的进程，让其进入就绪等待队列，再让下一进程进入运行

&ensp;&ensp;&ensp;&ensp;进程优先级有三级，依次下降，0级只有初始化进程：0级、1级、2级

&ensp;&ensp;&ensp;&ensp;进程的状态有三种：阻塞（-1）、就绪（0）、运行（1）。阻塞是因资源无法获取；就绪是资源获取后在队列中排队等待；运行是进行正在运行，系统在同一时间只能运行一个进程

&ensp;&ensp;&ensp;&ensp;新建进程是资源获取数量为随机生成

##### 3.2.1 模块类：
- 进程管理 ProgressManage：
    - 系统进程初始化：init()
    - 创建进程：createProcess()
    - 删除进程：deleteProcess（）
    - 查看进程信息：listProcess（）
    - 时钟中断：timeInt（）

- 进程 Progress：
    - 进程名：name
    - 所需资源：resource1, resuouce2
    - 优先级：priority
    - 进程状态：state
    
- 进程控制块结构 PCB：
    - 进程：pProgress
    - 父进程：pFather
    - 子进程：pSon
    - 队列中的上一个进程：fore
    - 队列中的下一个进程：next
    - 资源状态：sourceState

##### 3.2.2 实现细节：
###### 进程创建：
&ensp;&ensp;&ensp;&ensp;创建进程如下：首先要确定新建的进程为重名，然后新建进程，打印相应信息；新建的进程首先进入就绪队列，如果优先级较高，可强占运行时间

```c++
/************************************************************************/
/* 创建进程：
    name：新建进程名
    priority：新建进程优先级*/
/************************************************************************/
bool ProcessManage::createProcess(std::string name, int priority) {
    //首先检查是否重复创建相同名称的进程
    PCB* isRepeat = NULL;
    isRepeat = find(name);
    if(isRepeat != NULL) {
        std::cout << ">>当前进程名已存在，请重新命名进程名" << std::endl;
        return false;
    }

    int rA = -1;
    int rB = -1;

    MyProcess* process = new MyProcess(name, priority);
    process->getResourceNeed(rA, rB);
    PCB* pcb = new PCB(process);

    std::cout << ">>进程： " << name << " 创建成功，优先级为：" << priority 
        << " 资源A、B需求量为:" << rA << "、" << rB  << std::endl;

    //父子关系建立
    //如果当前有运行进程，则此新建进程为此运行进程的子进程，如果没有，则是初始进程的子进程
    if(runningProcess == NULL) {
        initProcess->setSon(pcb);
        pcb->setFather(initProcess);
    }
    else {
        runningProcess->setSon(pcb);
        pcb->setFather(runningProcess);
    }

    //新建进程后将其添加入就绪队列
    addReadyQueue(pcb);

    return true;
}
```

###### 删除进程：
&ensp;&ensp;&ensp;&ensp;删除进程时首先判断系统中是否存在这个进程，并且释放其占用的资源，然后销毁此进程和他的子进程，如果进行一次系统调度

```c++
/************************************************************************/
/* 删除进程：
    name：删除的进程名*/
/************************************************************************/
bool ProcessManage::deleteProcess(std::string name) {
    //查看是否存在这个进程
    PCB* destroyProcess = find(name);
    if(destroyProcess == NULL) {
        std::cout << ">>系统中无此进程，请检查输入" << std::endl;

        return true;
    }
    else {
        destroy(destroyProcess);
        schedule();
    }

    return true;
}

/************************************************************************/
/* 销毁进程，连同其子进程：
    pcb：销毁的进程*/
/************************************************************************/
bool ProcessManage::destroy(PCB* pcb) {
    //首先查看此进程是否有子进程，如果有子进程，先销毁子进程
    if(pcb->getSon() != NULL) {
        destroy(pcb->getSon());
    }

    //释放删除进程的资源
    ResourceManage::releaseResource(pcb);

    //销毁当前进程
    //去除相应的父子关系
    PCB* father = pcb->getFather();
    PCB* son = pcb->getSon();
    if(father != NULL && son == NULL) {
        father->setSon(NULL);
    }

    //去除队列信息
    std::string name = pcb->getProcess()->getName();
    //就绪队列寻找
    PCB* current = readyQueue;
    while(current != NULL) {
        if(current->getProcess()->getName() == name) {
            PCB* fore = current->getFore();
            PCB* next = current->getNext();
            //如果当前进程位于队首，并且不止一个进程
            if(fore == NULL && next != NULL) {
                readyQueue = next;
                next->setFore(fore);
                runningProcess = NULL;

                delete(pcb);
                std::cout << ">>进程： " << name << " 删除成功";
                std::cout << " 正在运行的进程被删除" << std::endl;
                return true;
            }
            //如果当前进程位于队首，并且只有一个进程
            else if(fore == NULL && next == NULL) {
                readyQueue = NULL;
                runningProcess = NULL;

                delete(pcb);
                std::cout << ">>进程： " << name << " 删除成功";
                std::cout << " 正在运行的进程被删除" << std::endl;
                return true;
            }
            //如果当前进程位于队尾
            else if(fore != NULL && next == NULL) {
                fore->setSon(NULL);

                delete(pcb);
                std::cout << ">>进程： " << name << " 删除成功" << std::endl;
                return true;
            }
            //进程位于中间
            else if(fore != NULL && next != NULL) {
                fore->setNext(next);
                next->setFore(fore);

                delete(pcb);
                std::cout << ">>进程： " << name << " 删除成功" << std::endl;
                return true;
            }
        }

        current = current->getNext();
    }

    //阻塞队列寻找
    current = blockQueue;
    while(current != NULL && pcb != NULL) {
        if(current->getProcess()->getName() == name) {
            PCB* fore = current->getFore();
            PCB* next = current->getNext();
            //如果当前进程位于队首，并且不止一个进程
            if(fore == NULL && next != NULL) {
                blockQueue = next;
                next->setFore(fore);

                delete(pcb);
                std::cout << ">>进程： " << name << " 删除成功" << std::endl;
                return true;
            }
            //如果当前进程位于队首，并且只有一个进程
            else if(fore == NULL && next == NULL) {
                blockQueue = NULL;

                delete(pcb);
                std::cout << ">>进程： " << name << " 删除成功" << std::endl;
                return true;
            }
            //如果当前进程位于队尾
            else if(fore != NULL && next == NULL) {
                fore->setSon(NULL);

                delete(pcb);
                std::cout << ">>进程： " << name << " 删除成功" << std::endl;
                return true;
            }
            //进程位于中间
            else if(fore != NULL && next != NULL) {
                fore->setNext(next);
                next->setFore(fore);

                delete(pcb);
                std::cout << ">>进程： " << name << " 删除成功" << std::endl;
                return true;
            }
        }

        current = current->getNext();
    }

    return false;
}
```

###### 进程调度：
&ensp;&ensp;&ensp;&ensp;在进程调度中，首先查找阻塞队列，看是否有足够的空闲资源，如果有空闲的充足资源，则把相应的进程激活，加入就绪队列

```c++
************************************************************************/
/* 进程调度：*/
/************************************************************************/
void ProcessManage::schedule() {
    //首先检查阻塞队列是否可以获得资源而激活
    PCB* current = blockQueue;
    while(current != NULL) {
        //如果资源充足，进程进入就绪队列
        if(current->applyForResource(false)) {
            //从阻塞队列中移除
            std::string name = current->getProcess()->getName();
            PCB* fore = current->getFore();
            PCB* next = current->getNext();
            //如果当前进程位于队首，并且不止一个进程
            if(fore == NULL && next != NULL) {
                blockQueue = next;
                next->setFore(fore);

                std::cout << ">>进程： " << name << "进入就绪队列" << std::endl;
                addReadyQueue(current);
                return;
            }
            //如果当前进程位于队首，并且只有一个进程
            else if(fore == NULL && next == NULL) {
                blockQueue = NULL;

                std::cout << ">>进程： " << name << "进入就绪队列" << std::endl;
                addReadyQueue(current);
                return;
            }
            //如果当前进程位于队尾
            else if(fore != NULL && next == NULL) {
                fore->setSon(NULL);

                std::cout << ">>进程： " << name << "进入就绪队列" << std::endl;
                addReadyQueue(current);
                return;
            }
            //进程位于中间
            else if(fore != NULL && next != NULL) {
                fore->setNext(next);
                next->setFore(fore);

                std::cout << ">>进程： " << name << "进入就绪队列" << std::endl;
                addReadyQueue(current);
                return;
            }
        }

        current = current->getNext();
    }

    //检查就绪队列，如果有进程存在，但无运行进程则申请资源
    if(readyQueue == NULL) {
        std::cout << ">>无就绪进程，无进程可调度运行" << std::endl;
    }
    if(readyQueue != NULL && runningProcess == NULL) {
        //对队首进程进行检测，如果成功则运行，失败进入阻塞队列
        std::string name = readyQueue->getProcess()->getName();
        //如果资源不足则进入阻塞队列
        if(!readyQueue->getState() && !readyQueue->applyForResource(false)) {
            //首先从就绪独立移除
            PCB* current = readyQueue;
            current->setNext(NULL);
            readyQueue = current->getNext();
            if(readyQueue == NULL) {
                runningProcess = NULL;
                readyLast = NULL;
            }
            else {
                readyQueue->setFore(NULL);
            }
            //加入阻塞队列
            addBlockQueue(current);
            std::string name = readyQueue->getProcess()->getName();
            std::cout << ">>进程： " << name << "进入阻塞队列" << std::endl;

            //无运行进程，再调度进程调度，查看就绪队列下一个进程
            schedule();
        }
        else {
            readyQueue->getProcess()->setState(1);
            runningProcess = readyQueue;
            //如果是第一次申请资源成功，则设置成功占用资源
            if(!readyQueue->getState()) {
                readyQueue->setState(true);
            }
            std::cout << ">>进程： " << name << "资源申请成功，进入运行状态" << std::endl;
            return;
        }
    }
}
```

###### 时钟中断：
&ensp;&ensp;&ensp;&ensp;时钟中断时暂停当前运行的进程，并将当前运行的进程加入到就绪队列的尾部，但不释放其占有的资源。然后进行进程调度

```c++
/************************************************************************/
/* 时钟中断：*/
/************************************************************************/
bool ProcessManage::timeInt() {
    if(runningProcess == NULL) {
        std::cout << ">>当前无运行进程，不需时钟中断" << std::endl;
        return false;
    }

    std::cout << ">>进程：" << runningProcess->getProcess()->getName() << " 时钟中断" << std::endl;
    //如果就绪进程就只有一个，只设置不是运行状态就可
    if(readyQueue->getNext() == NULL) {
        runningProcess->getProcess()->setState(0);
    }
    //否则将运行进程停止，并插入就绪队列最后方
    else {
        //设置状态
        runningProcess->getProcess()->setState(0);
        //从队列中移除
        readyQueue = runningProcess->getNext();
        runningProcess->getNext()->setFore(NULL);
        //插入队尾
        PCB* current = runningProcess;
        readyLast->setNext(current);
        current->setFore(readyLast);
        current->setNext(NULL);
        readyLast = current;
    }

    runningProcess = NULL;
    schedule();

    return true;
}
```

###### 查看进程信息：
&ensp;&ensp;&ensp;&ensp;打印出现系统的相关进程信息

```c++
/************************************************************************/
/* 查看进程列表：*/
/************************************************************************/
bool ProcessManage::listProcess() {
    std::cout << ">>进程列表如下：" << std::endl;

    if(runningProcess == NULL) {
        std::cout << ">>当前无运行进程" << std::endl;
    }
    else {
        std::cout << ">>当前运行进程为：" << runningProcess->getProcess()->getName() << std::endl;
    }

    PCB* current = readyQueue;
    if(current == NULL) {
        std::cout << ">>就绪队列为空，没有就绪进程" << std::endl;
    }
    else {
        std::cout << ">>就绪队列有如下进程：";
        while(current != NULL) {
            std::cout << current->getProcess()->getName() << " ";
            current = current->getNext();
        }
        std::cout << std::endl;
    }

    current = blockQueue;
    if(current == NULL) {
        std::cout << ">>阻塞队列为空，没有阻塞进程" << std::endl;
    }
    else {
        std::cout << ">>阻塞队列有如下进程：";
        while(current != NULL) {
            std::cout << current->getProcess()->getName() << " ";
            current = current->getNext();
        }
        std::cout << std::endl;
    }

    return true;
}
```

#### 3.3 资源模块：
##### 3.3.1 模块类：
- 资源管理类 ResourceManage：
    - 资源A：resourceA
    - 资源B：resourceB
    - 资源A的剩余数量：remainA
    - 资源B的剩余数量：remainB
    - 资源申请：requestResource（）
    - 具体进程资源申请：apply（）
    - 资源释放：releaseResource（）
    - 资源情况查看：listResource（）

- 资源类 Resource：基类
    - 资源总数量：amount

- 资源A ResourceA：继承资源类

- 资源B ResourceB：基础资源类

##### 3.3.2 实现细节：
###### 资源申请：
&ensp;&ensp;&ensp;&ensp;根据系统的进程的资源要求进行资源的申请，资源申请有两种形式，一个是只查看系统中是否有相应的充足的资源，资源的数量不做相应的变化；另一种是判断是否有相应的资源，并获取，相应的资源数量做相应的变化

```c++
/************************************************************************/
/* 申请系统资源：
/************************************************************************/
bool ResourceManage::requestResource() {
    //std::cout << ">>申请资源：" << name << std::endl;
    ProcessManage::schedule();

    return true;
}

/************************************************************************/
/* 进程资源申请，申请成功则资源数量进行相应的变化:
    countA:资源A的申请数量
    countB:资源B的申请数量
    isGet:是否是资源数量进行相应的变化*/
/************************************************************************/
bool ResourceManage::apply(const int& countA, const int& countB, bool isGet) {
    if(countA <= remainA && countB <= remainB) {
        if(isGet) {
            remainA -= countA;
            remainB -= countB;
        }
        return true;
    }

    return false;
}
```

###### 释放资源：
&ensp;&ensp;&ensp;&ensp;释放资源有两种调用形式，一种是无参数调用，此调用默认释放当前运行进程的资源（视此进程已运行完成）；另一种是指定相应的进程并释放其占有的资源

```c++
/************************************************************************/
/* 释放对应资源：
/************************************************************************/
bool ResourceManage::releaseResource() {
    //获取当前运行进程的资源数目,并释放
    int runA = -1;
    int runB = -1;
    ProcessManage::getRunningResource(runA, runB);
    remainA += runA;
    remainB += runB;

    //重新调度进程
    ProcessManage::schedule();

    return true;
}

/************************************************************************/
/* 释放对应资源：
    pcb:要释放资源的进程*/
/************************************************************************/
bool ResourceManage::releaseResource(PCB* pcb) {
    //检测此进程是否有占用资源,没有资源占用直接返回
    if(!pcb->getState()) {
        return false;
    }

    //获取当前运行进程的资源数目,并释放
    int runA = -1;
    int runB = -1;
    pcb->getProcess()->getResourceNeed(runA, runB);
    remainA += runA;
    remainB += runB;

    std::cout << ">>进程 " << pcb->getProcess()->getName() << " 资源释放成功" << std::endl;

    return true;
}
```

###### 查看资源信息：
&ensp;&ensp;&ensp;&ensp;打印显示系统中相关的资源信息：

```c++
/************************************************************************/
/* 查看系统资源信息：*/
/************************************************************************/
bool ResourceManage::listResource() {
    std::cout << ">>系统资源信息如下：" << std::endl;
    std::cout << "ResourceA:amount=" << resourceA->getAmount() << " remain=" << remainA << std::endl;
    std::cout << "ResourceB:amount=" << resourceB->getAmount() << " remain=" << remainB << std::endl;

    return true;
}
```

### 4.测试
#### 4.1 测试输入如下：
- cr firstProcess 2
- list_r
- cr secondProcess 1
- list_r
- list_p
- de firstProcess
- list_p
- list_r
- cr firstProcess 2
- cr secondProcess 1
- list_r
- list_p
- to
- list_r
- list_p
- cr P3 2
- cr P4 2
- list_r
- list_p
- rel
- list_r
- list_p
- cr P5 1
- cr P6 1
- list_r
- list_p

#### 4.1 测试结果如下：

![](./result1.jpg)

![](./result2.jpg)

![](./result3.jpg)

## 六、实验总结