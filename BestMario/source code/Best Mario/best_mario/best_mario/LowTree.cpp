#include "LowTree.h"
#include "Define.h"
#include "ListTexture.h"

LowTree::LowTree(void)
{
}

LowTree::LowTree( int left, int top )
{
	sprite = new Sprite(ListTexture::TT_LOW_TREE, 
						ListTexture::TT_LOW_TREE_WIDTH, 
						ListTexture::TT_LOW_TREE_HEIGHT, 
						ListTexture::TT_LOW_TREE_COUNT, 
						ListTexture::TT_LOW_TREE_SPRITEPERROW);


	UpdateRect(left, top, ListTexture::TT_LOW_TREE_WIDTH, ListTexture::TT_LOW_TREE_HEIGHT);
	map_level = 2;
	isKind = LOWTREE;
	isSolid = false;
}

LowTree::~LowTree(void)
{
}
