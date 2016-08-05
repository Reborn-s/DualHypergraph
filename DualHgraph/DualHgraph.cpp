#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include"DualHgraph.h"

using namespace std;

DualHgraph::DualHgraph()
{
	edgeCnt	= 0;
	nodeCnt	= 0;
	fmt		= 0;
}

DualHgraph::~DualHgraph()
{
}


void DualHgraph::doDual(string hgrPath)
{
	edgeCnt = 0;
	nodeCnt = 0;
	fmt = 0;

	fstream temHgr;
	temHgr.open(hgrPath+"//ordinary_mini.hgr",ios::in);
	if( !temHgr )
	{
		cout<<"error open!";
		exit(0);
	}

	char line[1000];
	string temp="";
	int flag = 0;

	temHgr.getline(line,sizeof(line));
	for(int i=0;line[i]!='\0';i++)
	{
		if(line[i]!=' ')
			temp+=line[i];
		if(line[i]==' '||(line[i]!=' '&&line[i+1]=='\0'))
		{
			if( 0==flag )
				nodeCnt = atoi(temp.c_str());
			if( 1==flag )
				edgeCnt = atoi(temp.c_str());
			if( 2==flag )
				fmt = atoi(temp.c_str());
			temp="";
			flag+=1;
		}
	}

	pAllVertices	=	(Vnode*)malloc(sizeof(struct Vnode)*nodeCnt);
	for(int i=0;i<nodeCnt;i++)
	{
		pAllVertices[i].firstarc = NULL;
		pAllVertices[i].edgeNum = 0;
		pAllVertices[i].Vweight = 0;
		pAllVertices[i].node = -1;
	}
	
	flag = 0;
	int nodeNum = 1;
	temp = "";
	while( nodeNum<=nodeCnt )
	{
		Vnode *newNode = (Vnode*)malloc(sizeof(struct Vnode));
		ArcNodeH *hedge = (ArcNodeH*)malloc(sizeof(struct ArcNodeH));
		
		newNode->node = nodeNum;
		newNode->edgeNum = 0;
		
		temHgr.getline(line,sizeof(line));
		for(int i=0;line[i]!='\0';i++)
		{
			if(line[i]!=' ')
				temp+=line[i];
			if(line[i]==' '||(line[i]!=' '&&line[i+1]=='\0'))
			{
				if( 0==flag )
					newNode->Vweight = atoi(temp.c_str());
				if( 1==flag )
				{
					hedge->hedge = atoi(temp.c_str())-1;		
					newNode->firstarc = hedge;
					newNode->edgeNum+=1;
				}
				if( flag>1 )
				{
					ArcNodeH *nextHedge = (ArcNodeH*)malloc(sizeof(struct ArcNodeH));
					nextHedge->hedge = atoi(temp.c_str())-1;
					nextHedge->nextarc = newNode->firstarc;
					newNode->firstarc = nextHedge;
					newNode->edgeNum+=1;
				}
				flag+=1;
				temp="";
			}
			
		}
		pAllVertices[nodeNum-1] = *newNode;
		nodeNum+=1;
		flag = 0;
		free(newNode);
	}
	int *edgeWgts = new int[edgeCnt];
	for(int e=0;e<edgeCnt;e++)
	{
		temHgr.getline(line,sizeof(line));
		edgeWgts[e] = atoi(line);
	}
	temHgr.close();
	
	
	for(int i=0;i<nodeCnt;i++)
	{
		Vnode newvert = pAllVertices[i];
		ArcNodeH *firstEdge = newvert.firstarc;
		for(int j=0;j<newvert.edgeNum;j++)
		{
			ArcNodeV *temvert = (ArcNodeV*)malloc(sizeof(struct ArcNodeV));
			temvert->node = newvert.node;
			if(allEdges.find(firstEdge->hedge)==allEdges.end())
			{
				HEnode* newedge = (HEnode*)malloc(sizeof(struct HEnode));
				newedge->Enode = firstEdge->hedge;
				newedge->nodeNum = 1;
				newedge->Hweight = edgeWgts[firstEdge->hedge];
				temvert->nextarc = NULL;
				newedge->firstarc = temvert;
				allEdges[firstEdge->hedge] = newedge;

			}
			else
			{
				allEdges[firstEdge->hedge]->nodeNum += 1;
				ArcNodeV *temvert = (ArcNodeV*)malloc(sizeof(struct ArcNodeV));
				temvert->node = newvert.node;
				temvert->nextarc = allEdges[firstEdge->hedge]->firstarc;
				allEdges[firstEdge->hedge]->firstarc = temvert;
			}
			firstEdge = firstEdge->nextarc;
		}
	}

	fstream Hgr;
	Hgr.open(hgrPath+"/Hgraph.hgr",ios::out);
	Hgr<<allEdges.size()<<" "<<nodeCnt<<" "<<fmt<<"\n";

	for(map<int,HEnode*>::iterator iter=allEdges.begin();iter!=allEdges.end();iter++)
	{
		Hgr<<iter->second->Hweight<<" ";
		ArcNodeV* node = iter->second->firstarc;
		for(int i=0;i<iter->second->nodeNum-1;i++)
		{
			Hgr<<node->node<<" ";
			node = node->nextarc;
		}
		Hgr<<node->node<<"\n";
	}
	for(int j=0;j<nodeCnt-1;j++)
	{
		Hgr<<pAllVertices[j].Vweight<<"\n";
	}
	Hgr<<pAllVertices[nodeCnt-1].Vweight;

	Hgr.close();

	free(pAllVertices);
}

	

