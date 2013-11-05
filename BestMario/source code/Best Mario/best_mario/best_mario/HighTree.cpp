#include "HighTree.h"
#include "ListTexture.h"
#include "Define.h"

HighTree::HighTree(void)
{
}

HighTree::HighTree( int left, int top, int iid )
{
	sprite = new Sprite(ListTexture::TT_HIGH_TREE, 
		ListTexture::TT_HIGH_TREE_WIDTH, 
		ListTexture::TT_HIGH_TREE_HEIGHT, 
		ListTexture::TT_HIGH_TREE_COUNT, 
		ListTexture::TT_HIGH_TREE_SPRITEPERROW);

	id = iid;
	UpdateRect(left, top, ListTexture::TT_HIGH_TREE_WIDTH, ListTexture::TT_HIGH_TREE_HEIGHT);
	map_level = 2;
	isKind = HIGHTREE;
	isSolid = false;
}

HighTree::~HighTree(void)
{
}
