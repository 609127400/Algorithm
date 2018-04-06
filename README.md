## 简介

自己写的一些算法，关于树、图。由于是在windows系统上进行编码的，因此在查看是可能会出现中文字符乱码的问题，请转换字符编码为GBK。每种算法都集中在单独的一个文件中，可直接进行gcc编译。

## 目录文件

* Graphics - 图
    * graphics_connected.c - 图的连通性问题
    * graphics_dag.c - 有向无环图
    * graphics_maximumflow.c - 最大流问题
    * graphics_minimumshortpath.c - 最短路径问题
    * graphics_search.c - 有向图、无向图以十字链表、邻接多重表的表示方法进行深度优先和广度优先的遍历
* Tree - 树
    * avl_tree.c - 平衡树
    * b_tree.c - B树
    * red_black_tree.c - 红黑树
    * splay_tree.c - 伸展树
* Config.h - 公共配置文件，是否输出日志，是否是在windows下编译
* dancing_links.c - （空，未写）
* hash.c - 哈希算法（散列表）
* huffman.c - 霍夫曼算法（霍夫曼树）
* mergesort.c - 归并排序 - 分而治之的思想
* methodology.c - 动态规划中的典型问题：钢条分割问题
* priority_queue.c - 优先队列
* PublicForAlgorithms.h - 定义一些各个算法公用的宏，常量，打印函数等
* queue.c - 利用队列实现一棵树的广度优先遍历。
* README.md - 说明文档

## Config.h配置说明

#### Debug输出

* 打开Debug输出：定义_DEBUG_OPEN_宏且不存在_DEBUG_CLOSE_宏
* 关闭Debug输出：定义_DEBUG_CLOSE_宏

#### 编译环境

若在windows下使用mingw编译，则保留`#define _WINDOWS_`宏定义，若在linux下编译，则删除此宏定义。
