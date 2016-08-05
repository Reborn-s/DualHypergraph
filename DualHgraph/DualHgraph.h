#include<string>
#include<map>

using namespace std;

struct ArcNodeH
{
	int hedge;  //ָ�򳬱ߺţ���0��ʼ
	ArcNodeH *nextarc; //�����ö�����һ������
};

struct Vnode
{
	int  node; //�����
	int  Vweight;
	int  edgeNum; //������
	ArcNodeH *firstarc; //�����ö���ĵ�һ������  
};
struct ArcNodeV
{
	int node; //ָ��Ķ����
	ArcNodeV *nextarc; //�ó��߰������¸�����
};

struct HEnode
{
	int Enode; //���ߺ�
	int nodeNum; //���߶�����
	ArcNodeV *firstarc; //�ó��߰����ĵ�һ������
	int Hweight;
};

class DualHgraph
{
public:
	int edgeCnt;
	int nodeCnt;
	int fmt;

	Vnode			*pAllVertices;
	map<int,HEnode*>	allEdges;	//���ߺţ����߽ṹ��

public:
	DualHgraph();
	~DualHgraph();

	void doDual(string hgrPath);
};