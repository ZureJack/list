#ifndef __LIST_H__
#define __LIST_H__
#include <stddef.h>
#include <stdbool.h>

struct list {
 struct list *next, *prev;
};


#define offset_of(struct_name, member) ((size_t) &(((struct_name *)0)->member))
#define get_node_addr(ptr, offset) ((void *)(((void *)(ptr)) - offset))


void *list_create_(size_t offset, size_t size);

/**
 * @param list 链表指针
 * @param destroy 函数原型为 void (*destroy)(void *)；的指针，函数destory用来销毁节点对象内申请的堆空间 
*/
bool list_destroy(void *list, void (*destroy)(void *));
/**
 * 
 * @param list 链表指针
 * @return 返回链表长度
*/
size_t list_length(void *list);


//bool list_append(void *node, void *list, void *dest);
/**
 * @public
 * @param node 需要插入的节点
 * @param list 被插入的链表指针
 * @param dest 被插入的节点，当dest == NULL时，node会插入到链表尾部;当dest != NULL时，node会插入到dest后
*/
bool list_insert(void *node, void *list, void *dest);
/**
 * @public
 * @brief 删除链表中的节点
 * @param node 被删除节点指针
 * @param list 链表指针
*/
bool list_delete(void *node, void *list, void (*delete)(void *));
/**
 * @public
 * @param list 链表指针
 * @param condition 函数指针，函数原型：bool condition(void *dest, void *src);
 *                  
 * @param dest 需要查询的对象（链表节点结构对象）,该变量将会传入第二个参数的函数原型中dest
 * @return 返回查询到的节点的地址,如果返回NULL则在该链表中查不到目标节点
*/
void *list_search(void *list, bool (*condition)(void *, void *), void *dest);
/**
 * @public 
 * @param struct_name 链表的节点结构名称
 * @param member 节点结构子对象名称
 * @return 链表指针
*/
#define list_create(struct_name, member) list_create_(offset_of(struct_name, member), sizeof(struct_name))
//debug
#ifdef LIST_DEBUG
//#undef LIST_DEBUG
/**
 * 打印整个链表的数据
 * @param list 链表指针
 * @param print 打印函数指针，使用者可以在该函数内编写需要打印的节点内的信息
*/
void list_print(void *list, void (*print)(void *));
#endif

#endif
