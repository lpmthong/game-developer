#include "QuadTree.h"

QuadTree::QuadTree(int w,int h)
{
	MapWidth=w;
	MapHeight=h;
	Root=new QuadNode(0,0,MapWidth,MapHeight);
	Count=0;
}
int QuadTree::CheckRECT(RECT *rootRECT,Object *Ob)
{
	//0_Add binh thg
	//1_LT
	//2_RT
	//3_LB
	//4_RB
	int result=0;//Add binh thuong
	int rw=Ob->Rect->right-Ob->Rect->left,rh=Ob->Rect->bottom-Ob->Rect->top;
	int w=rootRECT->right-rootRECT->left,h=rootRECT->bottom-rootRECT->top;
	int x=(rootRECT->right+rootRECT->left)/2,y=(rootRECT->bottom+rootRECT->top)/2;//2 dg thg chia rootRECT thanh 4 phan bg nhau

	if((rw*rh>w*h/4)//Dien tich hinh add vao lon hon 1/4 dien tich cua root
		||(x>Ob->Rect->left&&x<=Ob->Rect->right)||(y>Ob->Rect->top&&y<=Ob->Rect->bottom))
		result=0;//Add ngay tai do.
	else
	{
		if(Ob->Rect->left>=rootRECT->left&&Ob->Rect->left<x&&Ob->Rect->top>=rootRECT->top&&Ob->Rect->top<y)//Goc LT
			result =1;
		else if(Ob->Rect->left>=x&&Ob->Rect->left<rootRECT->right&&Ob->Rect->top>=rootRECT->top&&Ob->Rect->top<y)//RT
			result =2;
		else if(Ob->Rect->left>=rootRECT->left&&Ob->Rect->left<x&&Ob->Rect->top>=y&&Ob->Rect->top<rootRECT->bottom)//LB
			result=3;
		else//RB
			result=4;
	}
	return result;//Chuyen sang huong khac
}
void QuadTree::Add(QuadNode *root,Object *Ob)
{	
	if(root!=NULL)
	{
		int result=CheckRECT(root->Rect,Ob);
		if(result==0)//Add binh thuong
		{
			root->ArrayList.Add(Ob);
			Count++;
		}
		else
		{
			int w=root->Rect->right-root->Rect->left;
			int h=root->Rect->bottom-root->Rect->top;
			if(w/2>LIM_W_H&&h/2>LIM_W_H)
			{
				int x=(root->Rect->right+root->Rect->left)/2;//duong trung binh x
				int y=(root->Rect->bottom+root->Rect->top)/2;//duong trung binh y
				switch(result)
				{
				case 1://LT
					if(root->LT==NULL)
						root->LT=new QuadNode(root->Rect->left,root->Rect->top,w/2,h/2);
					Add(root->LT,Ob);
					break;
				case 2://RT
					if(root->RT==NULL)
						root->RT=new QuadNode(x,root->Rect->top,w/2,h/2);
					Add(root->RT,Ob);
					break;
				case 3://LB
					if(root->LB==NULL)
						root->LB=new QuadNode(root->Rect->left,y,w/2,h/2);
					Add(root->LB,Ob);
					break;
				case 4://RB
					if(root->RB==NULL)
						root->RB=new QuadNode(x,y,w/2,h/2);
					Add(root->RB,Ob);
					break;
				}
			}
		}
	}
}
void QuadTree::OutPutTree(QuadNode *root)
{
	//Root->LT->RT->LB->RB
	printf("%4ld%4ld%4ld%4ld\n",root->Rect->left,root->Rect->top,root->Rect->right,root->Rect->bottom);
	if(root->ArrayList.Count!=0)
		for(int i=0;i<root->ArrayList.Count;i++)
			printf("Element: %4ld%4ld%4ld%4ld\n",root->ArrayList[i]->Rect->left,root->ArrayList[i]->Rect->top,root->ArrayList[i]->Rect->right,root->ArrayList[i]->Rect->bottom);
	if(root->LT!=NULL)
		OutPutTree(root->LT);
	if(root->RT!=NULL)
		OutPutTree(root->RT);
	if(root->LB!=NULL)
		OutPutTree(root->LB);
	if(root->RB!=NULL)
		OutPutTree(root->RB);
}
//Truoc khi chay ham nay phai ghi "Count" truoc!
void QuadTree::WriteToFile(QuadNode *root,FILE *f)
{
	for(int i=0;i<root->ArrayList.Count;i++)
	{
		root->ArrayList[i]->WriteToFile(f);
	}
	if(root->LT!=NULL)
		WriteToFile(root->LT,f);
	if(root->RT!=NULL)
		WriteToFile(root->RT,f);
	if(root->LB!=NULL)
		WriteToFile(root->LB,f);
	if(root->RB!=NULL)
		WriteToFile(root->RB,f);
}
bool QuadTree::PointInRECT(int x,int y,RECT rect)
{
	if(x>=rect.left&&x<=rect.right&&y>=rect.top&&y<=rect.bottom)
		return true;//Nam trong
	return false;//Khong nam trong
}
bool QuadTree::RECTInRECT(RECT r,RECT rect)
{
	if(PointInRECT(r.left,r.top,rect)
		||PointInRECT(r.right,r.top,rect)
		||PointInRECT(r.left,r.bottom,rect)
		||PointInRECT(r.right,r.bottom,rect)
		||(rect.top<=r.top&&rect.bottom>=r.bottom&&r.left<=rect.left&&r.right>=rect.right))
	{
		return true;//Dc in ra
	}
	return false;
}
void QuadTree::DrawObjects(int VirtualLeft,QuadNode *root,RECT Screen,int layer)
{
	for(int i=0;i<root->ArrayList.Count;i++)
		if(root->ArrayList[i]->ID!=1&&root->ArrayList[i]->Layer==layer&&(RECTInRECT(*root->ArrayList[i]->Rect,Screen)||RECTInRECT(Screen,*root->ArrayList[i]->Rect)))
		{
			if(!root->ArrayList[i]->IsActive)//Active enemies
			{
				root->ArrayList[i]->OnMove->OldTime=GetTickCount();
				root->ArrayList[i]->IsActive=true;
			}
			root->ArrayList[i]->Draw(VirtualLeft,0);
		}
	if(root->LT!=NULL&&(RECTInRECT(*root->LT->Rect,Screen)||RECTInRECT(Screen,*root->LT->Rect)))
		DrawObjects(VirtualLeft,root->LT,Screen,layer);
	if(root->RT!=NULL&&(RECTInRECT(*root->RT->Rect,Screen)||RECTInRECT(Screen,*root->RT->Rect)))
		DrawObjects(VirtualLeft,root->RT,Screen,layer);
	if(root->LB!=NULL&&(RECTInRECT(*root->LB->Rect,Screen)||RECTInRECT(Screen,*root->LB->Rect)))
		DrawObjects(VirtualLeft,root->LB,Screen,layer);
	if(root->RB!=NULL&&(RECTInRECT(*root->RB->Rect,Screen)||RECTInRECT(Screen,*root->RB->Rect)))
		DrawObjects(VirtualLeft,root->RB,Screen,layer);
}
Object* QuadTree::CheckCollision(QuadNode *root,RECT r,int Seq)
{	
	for(int i=0;i<root->ArrayList.Count;i++)
		if(root->ArrayList[i]->ID!=-1//Day la nhung Object chi dung de trang tri
			&&root->ArrayList[i]->Status!=2//Chua chet
			&&root->ArrayList[i]->Sequency!=Seq
			&&(RECTInRECT(*root->ArrayList[i]->Rect,r)||RECTInRECT(r,*root->ArrayList[i]->Rect)))
			return root->ArrayList[i];//Dung do
	if(root->LT!=NULL&&(RECTInRECT(*root->LT->Rect,r)||RECTInRECT(r,*root->LT->Rect)))
	{
		Object *ob=CheckCollision(root->LT,r,Seq);
		if(ob!=NULL)
			return ob;
	}
	if(root->RT!=NULL&&(RECTInRECT(*root->RT->Rect,r)||RECTInRECT(r,*root->RT->Rect)))
	{
		Object *ob=CheckCollision(root->RT,r,Seq);
		if(ob!=NULL)
			return ob;
	}
	if(root->LB!=NULL&&(RECTInRECT(*root->LB->Rect,r)||RECTInRECT(r,*root->LB->Rect)))
	{
		Object *ob=CheckCollision(root->LB,r,Seq);
		if(ob!=NULL)
			return ob;
	}
	if(root->RB!=NULL&&(RECTInRECT(*root->RB->Rect,r)||RECTInRECT(r,*root->RB->Rect)))
	{
		Object *ob=CheckCollision(root->RB,r,Seq);
		if(ob!=NULL)
			return ob;
	}
	return NULL;
}
bool QuadTree::IsOnObject(RECT *rect,int Seq)//duoi chan object la object khac hay la khoang trong
{
	RECT r;
	r.left=rect->left;r.right=rect->right;
	r.top=rect->top+1;r.bottom=rect->bottom+1;
	Object *Ob=CheckCollision(Root,r,Seq);
	if(Ob!=NULL&&Ob->ID==0)
		return true;
	return false;
}
void QuadTree::UpdatePosition(QuadNode *root)
{
	for(int i=0;i<root->ArrayList.Count;i++)
	{
		Object *Ob=root->ArrayList[i];
		if(Ob->ID!=-1&&Ob->ID!=1&&Ob->IsActive)
		{
			if(Ob->Rect->top>SCREEN_HEIGHT
				||(Ob->Sprite->TotalExistTime!=0&&Ob->Status==2&&GetTickCount()-Ob->Sprite->RootTime >=(DWORD)Ob->Sprite->TotalExistTime))
			{
				Ob->Release();
				root->ArrayList.Remove(Ob,true);
				i--;
				break;
			}
			int a=Ob->Move();
			if(a!=0)
			{
				root->ArrayList.Remove(Ob,false);
				i--;
				this->Add(Root,Ob);
			}
		}
		else if(Ob->ID==1&&Ob->JustMove)//mario
		{
			root->ArrayList.Remove(Ob,false);
			i--;
			this->Add(Root,Ob);
			Ob->JustMove=false;
		}
	}
	if(root->LT!=NULL)
		UpdatePosition(root->LT);
	if(root->RT!=NULL)
		UpdatePosition(root->RT);
	if(root->LB!=NULL)
		UpdatePosition(root->LB);
	if(root->RB!=NULL)
		UpdatePosition(root->RB);
}
bool QuadTree::Remove(QuadNode *root,Object *Ob)
{
	for(int i=0;i<root->ArrayList.Count;i++)
	{
		if(root->ArrayList[i]->Sequency==Ob->Sequency&&root->ArrayList[i]->Rect->left==Ob->Rect->left)
		{
			root->ArrayList.Remove(Ob,true);
			return true;
		}
	}
	if(root->LT!=NULL)
	{
		if(Remove(root->LT,Ob))
			return true;
	}
	if(root->RT!=NULL)
	{
		if(Remove(root->RT,Ob))
			return true;
	}
	if(root->LB!=NULL)
	{
		if(Remove(root->LB,Ob))
			return true;
	}
	if(root->RB!=NULL)
	{
		if(Remove(root->RB,Ob))
			return true;
	}
	return false;
}
QuadTree::~QuadTree(void)
{
}
