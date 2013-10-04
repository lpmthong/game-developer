#include "QuadNode.h"

QuadNode::QuadNode(void){
	LTNode = LBNode = RTNode = RBNode = NULL;
}

QuadNode::QuadNode(int left, int top, int width, int height){
	rect.left = left;
	rect.top = top;
	rect.right = left + width;
	rect.bottom = top + height;

	a = 0;
	LTNode = LBNode = RTNode = RBNode = NULL;
}

QuadNode::~QuadNode(void){}

void QuadNode::Release(){

	StaticObject *temp;
	while(!listObject.empty()){
		list<StaticObject*>::iterator it = listObject.begin();
		temp = (*it);
		listObject.pop_front();
		delete temp;
	}

}

void QuadNode::Render(){
	
	list<StaticObject*>::iterator it;
	for(it = listObject.begin(); it != listObject.end(); ++it ){
		(*it)->Render();
	}

}

void QuadNode::Render(int map_level){
	
	list<StaticObject*>::iterator it;
	for(it = listObject.begin(); it != listObject.end(); ++it ){
		if ((*it)->map_level == map_level)
			(*it)->Render();
	}

}

void QuadNode::Update(){

	list<StaticObject*>::iterator it;
	for(it = listObject.begin(); it != listObject.end(); ++it ){
		(*it)->Update();
	}

}