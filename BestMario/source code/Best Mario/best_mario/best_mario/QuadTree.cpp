#include "QuadTree.h"
#include "GlobalHandler.h"

QuadTree::QuadTree(void){
	root = new QuadNode();
	count = 0;
}

QuadTree::QuadTree(int _mapwidth, int _mapheight){
	mapwidth = _mapwidth;
	mapheight = _mapheight;	
	root = new QuadNode(0, 0, mapwidth, mapheight, "");
	count = 0;
}

QuadTree::~QuadTree(void){}

void QuadTree::Release(){
	Release(root);
}

void QuadTree::Release(QuadNode *root){

	if(root->LTNode != NULL)
		Release(root->LTNode);
	if(root->LBNode != NULL)
		Release(root->LBNode);
	if(root->RTNode != NULL)
		Release(root->RTNode);
	if(root->RTNode != NULL)
		Release(root->LTNode);

	root->Release();
	delete root;
}

void QuadTree::Reset(){

	Release(root);
	root = new QuadNode();
	count = 0;
}

void QuadTree::ReadQuadTreeFormFile(int level)
{
	char filePath[50];
	sprintf_s(filePath,"Map\\Map%dQuadTree.txt",level);

	string str;
	ifstream file;

	file.open(filePath);
	
	if(!file.is_open()){
		trace(L"Khong doc duoc file QuadTree cua Map%d", level);
		exit(EXIT_FAILURE);
	}

	while(getline(file, str))
	{
		istringstream ss(str);

		string id;
		string qNode;
		ss >> id;		
		while(ss.good()){
			string text;
			ss >> text;
			qNode += text + " ";
		}
		
		qNode.erase(0, qNode.find_first_not_of(' '));
		qNode.erase(qNode.find_last_not_of(' ')+1);    

		qTreeMap[id] = qNode;

	}
	
}

void QuadTree::Deserialize()
{
	SaveNode(root);
}

void QuadTree::SaveNode(QuadNode *iroot){

	string id_LT = iroot->id + "00";
	string id_LB = iroot->id + "01";
	string id_RT = iroot->id + "10";
	string id_RB = iroot->id + "11";
	
	for (map<string, string>::iterator ii = qTreeMap.begin(); ii != qTreeMap.end(); ++ii)
	{
		if (id_LT.compare(ii->first) == 0)
		{
			GetNodeInfo(ii->second);	
			iroot->LTNode = new QuadNode(rNode.left, rNode.top, rNode.right, rNode.bottom, id_LT);
			iroot->LTNode->GetListObj(list_id);
			list_id = "";
			SaveNode(iroot->LTNode);
		}
		if (id_LB.compare(ii->first) == 0)
		{
			GetNodeInfo(ii->second);
			iroot->LBNode = new QuadNode(rNode.left, rNode.top, rNode.right, rNode.bottom, id_LB);
			iroot->LBNode->GetListObj(list_id);
			list_id = "";
			SaveNode(iroot->LBNode);
		}
		if (id_RT.compare(ii->first) == 0)
		{
			GetNodeInfo(ii->second);
			iroot->RTNode = new QuadNode(rNode.left, rNode.top, rNode.right, rNode.bottom, id_RT);
			iroot->RTNode->GetListObj(list_id);
			list_id = "";
			SaveNode(iroot->RTNode);
		}
		if (id_RB.compare(ii->first) == 0)
		{
			GetNodeInfo(ii->second);
			iroot->RBNode = new QuadNode(rNode.left, rNode.top, rNode.right, rNode.bottom, id_RB);
			iroot->RBNode->GetListObj(list_id);
			list_id = "";
			SaveNode(iroot->RBNode);
		}
	}
}

void QuadTree::GetNodeInfo(string info){
	
	istringstream ss(info);
	int l,t,r,b;
	ss >> l >> t >> r >> b; 
	rNode.left = l;
	rNode.top = t;
	rNode.right = r;
	rNode.bottom = b;
	while(ss.good()){
		string temp;
		ss >> temp;
		list_id += temp + " ";
	}

	list_id.erase(0, list_id.find_first_not_of(' '));
	list_id.erase(list_id.find_last_not_of(' ')+1);
	
	ss.str().clear();
	//trace(L"%d %d %d %d",rNode.left,rNode.top,rNode.right,rNode.bottom);
}

void QuadTree::RemoveObj(StaticObject* obj){
	RemoveObj(root, obj);	
}

void QuadTree::RemoveObj(QuadNode* root, StaticObject* obj){
	
	/*list<StaticObject*>::iterator it;
	for (it = root->listObject.begin(); it != root->listObject.end(); it ++)
	{
		if (obj == (*it))
		{
			root->listObject.remove(obj);
			return;
		}
	}*/
	root->listObject.remove(obj);

	if (root->LTNode != NULL)
		RemoveObj(root->LTNode, obj);
	if (root->RTNode != NULL)
		RemoveObj(root->RTNode, obj);			
	if (root->LBNode != NULL)
		RemoveObj(root->LBNode, obj);		
	if (root->RBNode != NULL)
		RemoveObj(root->RBNode, obj);

	GlobalHandler::listStaticObj.remove(obj);
}

void QuadTree::RenderScreen(){
	RenderScreen(root, 0);
	RenderScreen(root, 1);
	RenderScreen(root, 2);
}

void QuadTree::RenderScreen(QuadNode *root, int map_level){
	root->Render(map_level);

	if ((root->LTNode != NULL) && (GlobalHandler::CheckRectInRect(GlobalHandler::screen, root->LTNode->rect)))
		RenderScreen(root->LTNode, map_level);
	if ((root->RTNode != NULL) && (GlobalHandler::CheckRectInRect(GlobalHandler::screen, root->RTNode->rect)))
		RenderScreen(root->RTNode, map_level);
	if ((root->LBNode != NULL) && (GlobalHandler::CheckRectInRect(GlobalHandler::screen, root->LBNode->rect)))
		RenderScreen(root->LBNode, map_level);
	if ((root->RBNode != NULL) && (GlobalHandler::CheckRectInRect(GlobalHandler::screen, root->RBNode->rect)))
		RenderScreen(root->RBNode, map_level);
}

void QuadTree::RenderObj(){
	RenderObj(0);
	RenderObj(1);
	RenderObj(2);
}

void QuadTree::RenderObj(int map_level){

	list<StaticObject*>::iterator it;
	for(it = GlobalHandler::listStaticObjRender.begin(); it != GlobalHandler::listStaticObjRender.end(); ++it ){
		if ((*it)->map_level == map_level )
			(*it)->Render();
	}

}

void QuadTree::UpdateScreen()
{
	GlobalHandler::listStaticObjRender.clear();
	UpdateScreen(root);
}

void QuadTree::UpdateScreen( QuadNode* root )
{
	root->Update();

	if ((root->LTNode != NULL) && (GlobalHandler::CheckRectInRect(GlobalHandler::screen, root->LTNode->rect)))
		UpdateScreen(root->LTNode);
	if ((root->RTNode != NULL) && (GlobalHandler::CheckRectInRect(GlobalHandler::screen, root->RTNode->rect)))
		UpdateScreen(root->RTNode);
	if ((root->LBNode != NULL) && (GlobalHandler::CheckRectInRect(GlobalHandler::screen, root->LBNode->rect)))
		UpdateScreen(root->LBNode);
	if ((root->RBNode != NULL) && (GlobalHandler::CheckRectInRect(GlobalHandler::screen, root->RBNode->rect)))
		UpdateScreen(root->RBNode);

}

void QuadTree::GetListObjCanCollide(RECT rectObj){
	GlobalHandler::listStaticObjCanCollide.clear();
	GetListObjCanCollide(rectObj, root);
}

void QuadTree::GetListObjCanCollide(RECT rectObj, QuadNode *root){
	root->GetListObjCanCollide();

	if ((root->LTNode != NULL) && (GlobalHandler::CheckRectInRect(root->LTNode->rect, rectObj)))
		GetListObjCanCollide(rectObj, root->LTNode);
	if ((root->RTNode != NULL) && (GlobalHandler::CheckRectInRect(root->RTNode->rect, rectObj)))
		GetListObjCanCollide(rectObj, root->RTNode);
	if ((root->LBNode != NULL) && (GlobalHandler::CheckRectInRect(root->LBNode->rect, rectObj)))
		GetListObjCanCollide(rectObj, root->LBNode);
	if ((root->RBNode != NULL) && (GlobalHandler::CheckRectInRect(root->RBNode->rect, rectObj)))
		GetListObjCanCollide(rectObj, root->RBNode);
}

void QuadTree::Save(){
	GlobalHandler::save->SetFile("Map\\Map0QuadTree.txt");
	GlobalHandler::save->ClearSaveFile();
	Save(root);
}

void QuadTree::Save(QuadNode *root){

	if (!root->id.empty())
	{				
		GlobalHandler::save->SaveString(root->id);		
		GlobalHandler::save->SaveText(L" %d %d %d %d", root->rect.left, root->rect.top, root->rect.right, root->rect.bottom);
		if (root->listObject.empty())
			GlobalHandler::save->SaveText(L" %d", 0);
		else
		{
			list<StaticObject*>::iterator it;
			for(it = root->listObject.begin(); it != root->listObject.end(); ++it ){
				GlobalHandler::save->SaveText(L" %d", (*it)->id);
			}
		}
		GlobalHandler::save->SaveText(L"\n");
	}
	
	if (root->LTNode != NULL)
		Save(root->LTNode);
	if (root->LBNode != NULL)
		Save(root->LBNode);
	if (root->RTNode != NULL)
		Save(root->RTNode);
	if (root->RBNode != NULL)
		Save(root->RBNode);

}