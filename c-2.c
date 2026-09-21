#include <stdlib.h>//不能忘
#include <stdio.h>
typedef struct Glimmer {
    int cs;
    struct Glimmer *next;
} g;

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
}//创建新节点函数

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
}//头插函数

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

} //尾插函数

void search(g* head){
    g* p=head;
    while(p !=NULL){
        printf("%d ",p->cs);//加了空格
        p=p->next;
    }
    printf("\n");
   // return  head; 不需要返回值
}//打印所有数据

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
    
   }//查找值的位置函数

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
    return head;//删除节点函数
}

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
}//反转函数

void free_list(g* head) {
    while (head != NULL) {
        g* temp = head;
        head = head->next;
        free(temp);
    }
}

int main(){
    g *head;
    head=(g*)malloc(sizeof(g));
    if(head == NULL)//判断
    {
        return -1;
    }

    head->cs=0;
    head->next=NULL;

    head=headplus(head,1);
    head=tailplus(head,2);
    head=tailplus(head,3);
    search(head);
    lookfor(head,0);
    head=delete(head,2);
    head=reverse(head);
    search(head);


    free_list(head);
     // 释放内存
    return 0;

} 