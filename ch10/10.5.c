#include "apue.h"
#include <time.h>
#include <stdbool.h>

typedef void Timerfunc(void);

typedef struct my_timer
{
    int rest_time;    // 到期时间
    Timerfunc *func;  // 定时器处理函数

    struct my_timer *next;
} my_timer_t;

static my_timer_t head; /* 头节点，不使用 */
static time_t last_time; /* 上次更新链表时间的时间 */

static void pr_list()
{
    my_timer_t *p = head.next;
    printf("Rest time:");
    while (p != NULL) {
        printf("%d ",p->rest_time);
        p = p->next;
    }
    printf("\n");
}

// 更新各个节点的到期时间
static void update_timer()
{
    time_t now = time(NULL);
    time_t offset = now-last_time;  /* 计算时间间隔 */
    last_time = now;                /* 更新过去时间 */

    my_timer_t *p = head.next;
    while(p != NULL) {
        p->rest_time -= offset;   /* 减去间隔的时间 */
        p = p->next;
    }
}

// 信号处理函数
static void my_sigalrm(int no)
{
    my_timer_t *p;

    update_timer();

    // 以第二个节点的时间设置为下次的超时时间
    p = head.next->next;
    if(p != NULL) {
        alarm(p->rest_time);
    }

    // 头部节点到期
    p = head.next;
    p->func();    /*执行对应的任务*/
    head.next = p->next;    /* 删去超时节点 */
}

// 插入到链表适当位置
static int insert_timer(my_timer_t *timer)
{
    my_timer_t *p, *prev;
    unsigned int rtime;
    // 未插入节点
    if(head.next == NULL) {
        head.next = timer;
        // 无节点说明alarm未工作，启用alarm
        alarm(timer->rest_time);
        last_time = time(NULL);
        return 0;
    }

    update_timer(); /* 更新链表中各个定时器的剩余时间 */
                    /* 此时肯定没有定时器到期 */

    // 向链表插入节点
    p = head.next;
    prev = &head;
    while(p != NULL) {
        // 比当前节点的值大，向后查询
        if(timer->rest_time > p->rest_time) {
            prev = p;
            p = p->next;
            if(p == NULL) { /* 已经到链表尾部 */
                prev->next = timer; /* 放在链表尾部，不需要更新alarm */
                return 0;
            }
        }
        else { /* 比当前节点小，插入在前节点后面 */
            // 如果插入的是链表头部，说明需要更新alarm
            if(prev == &head) {
                // 更新alarm
                alarm(timer->rest_time);
            }
            timer->next = p;
            prev->next = timer;
            // 插入完成
            return 0;
        }
    }
    return -1;   /* 应该不会到这 */
}

int my_timer_set(int time, Timerfunc *func)
{
    // 申请空间
    my_timer_t *timer = (my_timer_t *)malloc(sizeof(my_timer_t));
    if(timer == NULL)
        return -1;

    // 设定参数
    timer->rest_time = time;
    timer->func = func;
    timer->next = NULL;

    // 插入链表中
    int ret = insert_timer(timer);
    pr_list();
    return ret;
}

void my_timer_init()
{
    // 设置信号处理函数
    signal(SIGALRM, my_sigalrm);
}

void ti_1()
{
    printf("timer1:%ld\n",time(NULL));
}
void ti_2()
{
    printf("timer2:%ld\n",time(NULL));
}
void ti_3()
{
    printf("timer3:%ld\n",time(NULL));
}

int main()
{
    my_timer_init();

    my_timer_set(4, ti_1);
    my_timer_set(2, ti_2);
    my_timer_set(6, ti_3);

    while(1)
    {
        ;
    }
    exit(0);
}