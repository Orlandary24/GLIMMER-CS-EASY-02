# 

# C-EASY-2：指针

## Step 1. 指针与结构体

### 什么是指针？

#### 1.如何在C语言中定义指针变量？指针变量的大小是固定的吗？其大小与什么有关？

通过  类型 * 指针名 的形式定义，其中 * 表示变量是指针。

指针变量的大小是固定的，与类型无关。

指针变量的大小由cpu的位数决定，32位对应4字节，64位对应8字节。

#### 2.写出以下代码的输出结果，并解释原因。

```c
int x = 10;
int* p = &x;  //x的地址给p
*p = 20; //将p地址上对应的值赋值为20，x因此变成了20

int arr[3] = {3, 6, 9};
int *q = arr; //arr的 首元素地址 给q，此时*q为3
int y = ++*arr  +  *++q; /* 查询资料可知 *和++优先
级相同，遵循从右往左。前者可以理解为对 arr的首元素地址 
解引用获得第一个元素的值,再通过++赋值最终第一个元素的值变
成了4；后者可以理解为对q的地址进行加一操作，而q的地址加1就
是arr[1]的地址，对其进行解引用得到了6。y最终为10。 */


printf("%d %d", x, y);
```

根据以上分析最终输出结果为：

20 10

#### 3.什么是野指针？简述其危害。如何避免产生野指针？

野指针就是指向一个非法内存地址的指针，这个存储的地址是无效的。举例：因为指针没有初始化导致存储了随机的地址。

危害：可能造成程序崩溃或者篡改未知的内存，同时因为编译器不会报错也可能导致程序运行正常但是得不到期望结果，增加纠错成本。

避免方法：

1. 初始化时对指针赋值为NULL；

2. 在free完内存后记得NULL一下指针；

3. 小心指针越界，特别注意使用数组时。

#### 4.尝试设计一个真正有效的swap()函数

错误函数如下，现尝试在此基础上修改调试

```c
void swap(int a, int b){
  int temp = a;
  a = b;
  b = temp;
}

int main(){
  int a = 10;
  int b = 20;
  swap(a, b);
}
```

第一次尝试如下：

<img src="file:///C:/Users/Orlandary/AppData/Roaming/marktext/images/2026-09-17-09-56-09-image.png" title="" alt="" width="489">

思考：没有抓住本质，实参的地址才是关键，对函数输入做些改变

更改后如下

![](C:/Users/Orlandary/AppData/Roaming/marktext/images/2026-09-17-10-00-47-image.png)

### 什么是结构体？

#### 1.请你完成一个PerInfo结构体的定义，成员组成如下。了解一下typedef关键字与结构体的一般用法，利用typedef为你刚刚定义的结构体取一个别名。提交最终的结构体定义。

> 1. 个人姓名（字符型数组，长度为10个字节）
> 2. 性别（字符型）
> 3. 年龄（整型）
> 4. 身高（双精度浮点型）

一个完整的结构体应该遵循以下模板：

```c
struct 结构体名 {
    成员类型1 成员名1;
    成员类型2 成员名2;
    // ...更多成员
};  // 注意：分号不能丢！
```

完成PerInfo定义

```c
struct PerInfo{
    char name[10];
    char gender;
    int age;
    double height;

} ;
```

typedef可以给已存在的数据类型起别名。

在这里的作用是可以给已存在的结构体取别名。

```c
struct PerInfo{
    char name[10];
    char gender;
    int age;
    double height;
} ;
typedef struct PerInfo personalinformation;//此时的别名可以单独使用
```

#### 2.了解并说明结构体指针的含义。

通过下面这个列子理解

其中的s是结构体的变量，类似于int 后面定义的东西。

s的大小是sizeof这个结构体。

```c
struct PerInfo s;
struct PerInfo *p = &s; // p是指针，存放s的首地址
```

指针p的类型是 struct PerInfo *,p中存放的是s的起始地址。

与普通指针类似的，该结构体指针本身大小只与系统位数有关（32 位系统 4 字节，64 位系统 8 字节）。

对于访问成员：

- s用s.age=  的形式

- 指针p用p->age 的形式

#### 3.了解一下结构体的**内存对齐规则**，据此计算一下你刚刚定义的结构体占用字节的大小（可用sizeof运算符验证计算结果）。提交计算过程。(此外，你还可以尝试更改一下结构体中成员的定义顺序，看看对结构体占用字节数的影响)

对齐规则：

- 对于每一个成员的起始地址，必须是成员自身对齐值的整数倍。

- 结构体的整体大小一定是最大成员大小的整数倍。

- 顺序会影响占用字节，必须严格按照代码书写顺序。

```c
struct PerInfo{
    char name[10];
    char gender;
    int age;
    double height;

} ;
```

计算过程如下：

char 1字节，int 4字节，double 8字节。

char name[10] 占了0到9的地址，char gender占了10的位置；

根据规则第一条，int要在4的倍数12，因此padding在11，int age占12，13，14，15；

此时16恰好为height的两倍，height占到15+8=23；

用第二规则检验一下，一共24，是8的倍数，无需再填充padding。

验证：

```c
#include <stdio.h>
struct PerInfo{
    char name[10];
    char gender;
    int age;
    double height;

};
int main()
{
    printf("%zu\n", sizeof(struct PerInfo));
    return 0;
}
```

![](C:/Users/Orlandary/AppData/Roaming/marktext/images/2026-09-17-20-41-45-image.png)

尝试交换顺序结果如下：

<img src="file:///C:/Users/Orlandary/AppData/Roaming/marktext/images/2026-09-17-20-45-49-image.png" title="" alt="" width="509">

## Step2. 链操作

### 什么是链表？

#### 1.请对比链表和数组的存储，讲讲链表和数组的区别

数组的存储是地址连续的数据，元素类型统一。

链表的存储各个节点的地址并不是一定相邻的，是取决于指针域，该节点的指针域存的是下一个节点的地址，我理解为一个房间里存在的物品和下一个房间的钥匙。

#### 2. 简述单向链表节点的结构特点。定义一个只存储一个整数的单向链表节点。

每个节点由数据域和指针域组成，指针域存放的是下一个节点的地址，用指针<u>next</u>表示。 需要注意的是访问只能通过当前节点的指针向后访问，最后一个节点的指针域置为NULL,表示结束。

定义如下

```c
struct Glimmer {
    int cs;
    struct Glimmer *next;
};
```

### 实现基本的链操作

基础必备步骤(先通过typedef别名成g）

```c
g *head;   // 定义头指针

head = (g*)malloc(sizeof(g));
// 1. 申请节点空间 其中(g*)作用是强制转换成节点指针类型，查阅资料知这里可以省略

head->cs = 0;// 2. 设置数据域 细节指针使用->的符号

head->next = NULL;// 3. 只有这一个节点，没有下一个节点，next为null
```

典型错误

```c
typedef struct Glimmer {
    int cs;
    struct Glimmer *next;
} g;

int main(){
    g *head;
    head=（g*）malloc(sizeof(g));
    head->cs=0;
    head->next=NULL;

}
```

![](C:/Users/Orlandary/AppData/Roaming/marktext/images/2026-09-17-22-09-26-image.png)

修改后完成基础操作

```c
#include <stdlib.h>//头文件
typedef struct Glimmer {
    int cs;
    struct Glimmer *next;
} g;

int main(){
    g *head;
    head=（g*）malloc(sizeof(g));
    if(head == NULL)//判断
    {
        return -1;
    }
    head->cs=0;
    head->next=NULL;


    free(head); // 释放内存
    head=NULL;
    return 0;

} 
```

#### 添加元素:

##### 请你设计一个函数，传入一个数据（int即可），返回一个存储这个数据的节点。

模仿头指针的创建过程，另外注意加上数据域

尝试结果如下：

```c
g* newnode(int num){
    g* s;
    s=(g*)malloc(sizeof(g));
    if(s == NULL)
    {
        return -1;
    }
    s->cs=num;


    return s;

}
```

检查错误修改

1.返回值不能是-1. 2.加一条next为NULL，防止垃圾值

![](C:/Users/Orlandary/AppData/Roaming/marktext/images/2026-09-18-17-35-36-image.png)

```c
g* newnode(int num){
    g* s;
    s=(g*)malloc(sizeof(g));
    if(s == NULL)
    {
        return NULL;
    }
    s->cs=num;
    s->next=NULL;
    return s;
}
```

##### 请你实现头插函数。函数传入主链表的头指针head和一个数据n

按照提示初步尝试：

关键点：定义新A;A指向头节点；头指针指向A。

```c
g* headplus(g* head,int n){
    g* A;
    A=(g*)malloc(sizeof(g));
    if(A==NULL)
    {
        return NULL;
    }
    A->cs=n;
    A->next=head ;


}
```

经过ai纠错  

1. 重点错误，还是没有理解提示和头插的逻辑，没有返回值，应该末尾返回新的头节点，相当于创造一个新的head，把老的head和n结合成新节点

2. 可以提升的点：return NULL改成 return head。这样即使错误也能保全外部的head。

```c
g* headplus(g* head,int n){
    g* A;
    A=(g*)malloc(sizeof(g));
    if(A==NULL)
    {
        return head;
    }
    A->cs=n;
    A->next=head ;

    return A;
}
```

调用的格式应该是：

```c
head = headplus(head, n);
```

##### 请你自己设计尾插函数，并用代码将其实现。（提示：不要直接用头指针，定义一个新的指针将其赋值为头指针）

```c
g* tailplus(g* head,int n){
    g* A;
    A=(g*)malloc(sizeof(g));
    if(A==NULL)
    {
        return head;
    }
    A->cs=n;
    A->next=NULL ;

     g* find=head;


    return A;
}
```

到这基本思路卡壳，无法理解和使用这个定义的新指针的作用也想不出应该怎么return。

借助ai完善理解：

```c
g* tailplus(g* head, int n) {
    g* A = (g*)malloc(sizeof(g));
    if (A == NULL) {
        return head;   
    }

    A->cs = n;
    A->next = NULL;  

    if (head == NULL) {
        return A;
    }//若为空，可以直接用头插函数的做法，这是必要的

    g* p = head;
    while (p->next != NULL) {
        p = p->next;
    }//理解：找到当p->next是NULL的节点
    p->next = A;// 把新节点接到刚刚找到的节点尾部

    return head;
    /*头节点没有变，返回原来的 head，所以这个函数实际
    上应该不需要返回什么东西*/

}
```

调用的格式

```c
head = tailplus(head, n);
```

#### 查找元素：

##### 通过遍历思想，我们可以打印链表每个节点的数据。请你实现这个打印链表函数，传入链表头指针。且打印后不要改变头指针的指向。

初步想法： 1.通过NULL判断结束。2.按照上面的思路，引入一个可以随便乱造的p。3.现学现用上面p->next的写法按顺序遍历。

尝试如下：

```c
g* search(g* head){
    g* p=head;
    while(p->next!=NULL){
        printf("%d",p->cs);
        p=p->next;
    }
    printf("%d",p->cs);

    return  head;
}
```

该代码的问题：

1.空链表的p->next会出错。

2.循环结构可以简化。

3.小问题 打印格式优化。

4.不需要返回值。

```c
void search(g* head){
    g* p=head;
    while(p !=NULL){
        printf("%d ",p->cs);//加了空格
        p=p->next;
    }
    printf("\n");
   // return  head; 不需要返回值
}
```

直接调用就行

初步整合后验证如下

![](C:/Users/Orlandary/AppData/Roaming/marktext/images/2026-09-20-10-54-56-image.png)

##### 请你实现这个查找函数。传入头节点head和要查找的数据n，输出这个节点距头节点的距离（统计这是第几个节点）。如果有多个数据为n的节点只返回第一个，如果没有查找到则返回false。

1.大体框架依旧沿用之前的遍历框架；2.加入ok判断false；3.使用break防止找到第二个数据为n的节点。

尝试如下：

```c
void search(g* head,int n){
    g* p=head;
    int i=1;
    int ok=0;
    while(p !=NULL){
        if(p->cs==n){
        printf("%d ",i);
        ok=1;
        break;         
        }
        i++;
        p=p->next;
    }
    if(ok==0){
        printf("false");
    }

   }
```

通过ai纠错

1.函数名忘记改了。2.通过直接return可以不用ok判断，精简代码。

修改后如下

```c
void lookfor(g* head,int n){
    g* p=head;
    int i=1;
    int ok=0;
    while(p !=NULL){
        if(p->cs==n){
        printf("%d ",i);
        ok=1;
        break;         
        }
        i++;
        p=p->next;
    }
    if(ok==0){
        printf("false");
    }

   }
```

验证结果如下

![](C:/Users/Orlandary/AppData/Roaming/marktext/images/2026-09-20-11-34-32-image.png)

#### 删除和更改：

##### 请你实现删除第n个节点的函数。只传入头指针和n，如果链表节点数少于n返回false，反之返回true。

1.按照这个要求我们无法提前知道链表节点数，但是如果结束没有实现删除功能可以直接false，这次试一下return.2.引入第二个指针q。

```c
void delete(g* head,int n){
    g* p=head;
    g* q=head->next;
    int i=1;
    while(p !=NULL){
        if(i==n-1){
        p->next=q->next;
        free(q);
        printf("true");
        return ;    
        }
        p=p->next;
        q=q->next;
        i++;
    }
        printf("false");
    }

   }
```

ai修改再重新理解

![](C:/Users/Orlandary/AppData/Roaming/marktext/images/2026-09-20-15-31-55-image.png)

```c
g* delete(g* head, int n) {
    // 非法情况
    if (head == NULL || n <= 0) {
        printf("false\n");
        return head;
    }//此时没有节点或者n无意义

    // 特殊情况：删除第 1 个节点
    if (n == 1) {
        g* temp = head;//temp的作用类似于我写的q的作用
        head = head->next;
        free(temp);
        printf("true\n");
        return head;//直接跳出去修改head
    }

    g* p = head;          // p 指向第 n-1 个节点
    g* q = head->next;    // q 指向第 n 个节点
    int i = 1;

    // 当 q 不为空时继续查找，这里修改成q不为空，巧妙避免最大i=n-1的问题
    while (q != NULL) {
        if (i == n - 1) {
            p->next = q->next;  
            free(q);         
            printf("true\n");
            return head;
        }
        p = p->next;
        q = q->next;
        i++;
    }

    // 链表长度小于 n
    printf("false\n");
    return head;
}
```

#### 反转函数：

##### 请根据上面双指针的思想，设计一个函数，传入头指针，然后将链表倒置，头指针指向新链表的第一个节点。

对于指针q和上一个指针p，q->next应该等于p，但是这样无法继续操作因为q-> next已经发生变化了。这里需要再引入一个新的指针。运用prev，curr，next三个指针实现这个过程。这道题我的卡住的点是当q->next的存储值改变就无法处理了，引入一个新指针next可以完美解决。

```c
g* reverse(g* head){
    g* prev=NULL;
    g* curr=head;
    g* next;

    while(curr!=NULL){
        next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }


    return prev;//注意注意，此时的curr是NULL，prev是最后一个节点。
}
```

调用：

```c
head = reverse(head);
```

最终整合所有函数并测试：

<img src="file:///C:/Users/Orlandary/AppData/Roaming/marktext/images/2026-09-20-17-25-45-image.png" title="" alt="" width="439">

其他学习知识：循环释放节点的函数

只freehead并没有完全free所有内存。

```c
void free_list(g* head) {
    while (head != NULL) {
        g* temp = head;
        head = head->next;
        free(temp);
    }
}
```

吐槽一下我现在使用的唐氏豆包

![](C:/Users/Orlandary/AppData/Roaming/marktext/images/2026-09-17-20-36-14-image.png)

![](C:/Users/Orlandary/AppData/Roaming/marktext/images/2026-09-17-20-35-36-image.png)
