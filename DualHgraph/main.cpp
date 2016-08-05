// DualHgraph.cpp : 定义控制台应用程序的入口点。
//对超图做对偶
//原超图第一行需是超图规定的格式：超边数 顶点数 fmt

#include "stdafx.h"
#include"DualHgraph.h"

int main()
{
	DualHgraph *transfer = new DualHgraph();
	transfer->doDual("../testcase");
	return 0;
}
