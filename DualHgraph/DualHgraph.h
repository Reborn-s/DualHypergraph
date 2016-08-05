#include<string>
#include<map>

using namespace std;

struct ArcNodeH
{
	int hedge;  //指向超边号，从0开始
	ArcNodeH *nextarc; //包含该顶点下一条超边
};

struct Vnode
{
	int  node; //顶点号
	int  Vweight;
	int  edgeNum; //超边数
	ArcNodeH *firstarc; //包含该顶点的第一条超边  
};
struct ArcNodeV
{
	int node; //指向的顶点号
	ArcNodeV *nextarc; //该超边包含的下个顶点
};

struct HEnode
{
	int Enode; //超边号
	int nodeNum; //超边顶点数
	ArcNodeV *firstarc; //该超边包含的第一个顶点
	int Hweight;
};

class DualHgraph
{
public:
	int edgeCnt;
	int nodeCnt;
	int fmt;

	Vnode			*pAllVertices;
	map<int,HEnode*>	allEdges;	//超边号，超边结构体

public:
	DualHgraph();
	~DualHgraph();

	void doDual(string hgrPath);
};