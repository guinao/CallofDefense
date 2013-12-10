#include "BootScene.h"
#include <ccTypes.h>
#include "layers_scenes_transitions_nodes\CCLayer.h"
#include "cocoa\CCGeometry.h"
#include "layers_scenes_transitions_nodes\CCScene.h"
#include "misc_nodes\CCRenderTexture.h"
#include "actions\CCActionInterval.h"
#include "actions\CCAction.h"
#include "SpaceAdventureScene.h"

using namespace cocos2d;

BootScene::BootScene()
{
	_background = NULL;
}

CCScene* BootScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        BootScene *layer = BootScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

ccColor4F BootScene::randomBrightColor()
{
	while (true)
	{
		float requiredBrightness = 192;
		ccColor4B randomColor = ccc4(rand() % 255,
			rand() % 255,
			rand() % 255,
			255);
		if (randomColor.r > requiredBrightness || 
			randomColor.g > requiredBrightness ||
			randomColor.b > requiredBrightness)
		{
			return ccc4FFromccc4B(randomColor);
		}
	}
}

void BootScene::genBackground()
{
	if (_background)
	{
		_background->removeFromParentAndCleanup(true);
	}

	ccColor4F bgColor = this->randomBrightColor();
	ccColor4F color2 = this->randomBrightColor();
	//_background = this->spriteWithColor(bgColor, 512, 512);
	int nStripes = ((rand() % 4) + 1) * 2;
	_background = this->spriteWithColor1(bgColor, color2, 1024, 512, nStripes);

//	this->setScale(0.5f);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	ccTexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
	_background->getTexture()->setTexParameters(&tp);
	this->addChild(_background);
}

void BootScene::onEnter()
{
	CCLayer::onEnter();
	this->genBackground();
	this->setTouchEnabled(true);
	this->scheduleUpdate();
}

void BootScene::update(float dt)
{
	static int cnt = 0;
	float PIXELS_PER_SECOND = 100;
	static float offset = 0;
	offset += PIXELS_PER_SECOND * dt;

	CCSize textureSize = _background->getTextureRect().size;
	_background->setTextureRect(CCRectMake(offset, 0, textureSize.width, textureSize.height));
	if( ++cnt  %30 == 0 )
		this->genBackground();
}

void BootScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	this->genBackground();
}

void BootScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if(1 == pTouches->count())
	{
		CCTouch *touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
		CCPoint pos1 = touch->getLocationInView();
		CCPoint	pos2 = CCDirector::sharedDirector()->convertToUI(pos1);

		if( _starticon->boundingBox().containsPoint(pos2) )
		{
			CCDirector::sharedDirector()->replaceScene(
				cocos2d::CCTransitionShrinkGrow::create(
					0.5, SpaceAdventureScene::scene()
				)
			);
		}
	}
}

CCSprite* BootScene::spriteWithColor(ccColor4F bgColor, float textureWidth, float textureHeight)
{
	// 1: Create new CCRenderTexture
	CCRenderTexture *rt = CCRenderTexture::create(textureWidth, textureHeight);

	// 2: Call CCRenderTexture:begin
	rt->beginWithClear(bgColor.r, bgColor.g, bgColor.b, bgColor.a);


	// 2.5
	this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));

	CC_NODE_DRAW_SETUP();

	// 3: Draw into the texture
	float gradientAlpha = 0.7f;
	CCPoint vertices[4];
	ccColor4F colors[4];
	int nVertices = 0;

	vertices[nVertices] = CCPointMake(0, 0);
	colors[nVertices++] = ccc4f(0, 0, 0, 0);
	vertices[nVertices] = CCPointMake(textureWidth, 0);
	colors[nVertices++] = ccc4f(0, 0, 0, 0);
	vertices[nVertices] = CCPointMake(0, textureHeight);
	colors[nVertices++] = ccc4f(0, 0, 0, gradientAlpha);
	vertices[nVertices] = CCPointMake(textureWidth, textureHeight);
	colors[nVertices++] = ccc4f(0, 0, 0, gradientAlpha);

	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, colors);
	glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);
	// 3: Draw into the texture
	// You'll add this later
	CCSprite *noise = CCSprite::create("Noise.png");
	ccBlendFunc blendFunc = {GL_DST_COLOR, GL_ZERO};
	noise->setBlendFunc(blendFunc);
	noise->setPosition(ccp(textureWidth / 2, textureHeight / 2));
	noise->visit();
	// 4: Call CCRenderTexture:end
	rt->end();

	// 5: Create a new Sprite from the texture
	return CCSprite::createWithTexture(rt->getSprite()->getTexture());
}

CCSprite * BootScene::spriteWithColor1(ccColor4F c1, ccColor4F c2, float textureWidth, float textureHeight, int nStripes)
{
	// 1: Create new CCRenderTexture
	CCRenderTexture *rt = CCRenderTexture::create(textureWidth, textureHeight);

	// 2: Call CCRenderTexture:begin
	rt->beginWithClear(c1.r, c1.g, c1.b, c1.a);

	// 3: Draw into the texture
	this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
	CC_NODE_DRAW_SETUP();

	// Layer 1: Stripes
	CCPoint *vertices = new CCPoint[nStripes * 6];
	ccColor4F *colors = new ccColor4F[nStripes * 6];

	int nVertices = 0;
	float x1 = -textureHeight;
	float x2;
	float y1 = textureHeight;
	float y2 = 0;
	float dx = textureWidth / nStripes * 2;
	float stripeWidth = dx / 2;
	for (int i = 0; i < nStripes; ++i)
	{
		x2  = x1 + textureHeight;

		vertices[nVertices] = ccp(x1, y1);
		colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);

		vertices[nVertices] = ccp(x1 + stripeWidth, y1);
		colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);

		vertices[nVertices] = ccp(x2, y2);
		colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);

		vertices[nVertices] = vertices[nVertices - 2];
		colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);

		vertices[nVertices] = vertices[nVertices - 2];
		colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);

		vertices[nVertices] = ccp(x2 + stripeWidth, y2);
		colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);
		x1 += dx;
	}

	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_TRUE, 0, colors);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)nVertices);
	// Layer 2: gradient
	float gradientAlpha = 0.7f;
	nVertices = 0;

	vertices[nVertices] = ccp(0, 0);
	colors[nVertices++] = ccc4f(0, 0, 0, 0);

	vertices[nVertices] = ccp(textureWidth, 0);
	colors[nVertices++] = ccc4f(0, 0, 0, 0);

	vertices[nVertices] = ccp(0, textureHeight);
	colors[nVertices++] = ccc4f(0, 0, 0, gradientAlpha);

	vertices[nVertices] = ccp(textureWidth, textureHeight);
	colors[nVertices++] = ccc4f(0, 0, 0, gradientAlpha);

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_TRUE, 0, colors);
	glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);

	// Layer 3: top highlight
	float borderHeight = textureHeight / 16;
	float borderAlpha = 0.3f;
	nVertices = 0;

	vertices[nVertices] = ccp(0, 0);
	colors[nVertices++] = ccc4f(1, 1, 1, borderAlpha);

	vertices[nVertices] = ccp(textureWidth, 0);
	colors[nVertices++] = ccc4f(1, 1, 1, borderAlpha);

	vertices[nVertices] = ccp(0, borderHeight);
	colors[nVertices++] = ccc4f(0, 0, 0, 0);

	vertices[nVertices] = ccp(textureWidth, borderHeight);
	colors[nVertices++] = ccc4f(0, 0, 0, 0);

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_TRUE, 0, colors);
	glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);


	CC_SAFE_DELETE_ARRAY(vertices);
	CC_SAFE_DELETE_ARRAY(colors);

	// Layer 4: Noise
	CCSprite *noise = CCSprite::create("Noise.png");
	ccBlendFunc blendFunc = {GL_DST_COLOR, GL_ZERO};
	noise->setBlendFunc(blendFunc);
	noise->setPosition(ccp(textureWidth / 2, textureHeight / 2));
	noise->visit();

	// 4: Call CCRenderTexture:end
	rt->end();

	// 5: Create a new Sprite from the texture
	return CCSprite::createWithTexture(rt->getSprite()->getTexture());
}

// on "init" you need to initialize your instance
bool BootScene::init()
{
//	CCSprite::createWithTexture();
    bool bRet = false;
    do {
    
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        bRet = true;
		// G::
		CCSprite* G = CCSprite::create("G.png");
		G->setPosition(ccp(winSize.width / 8 * 1, winSize.height * 3 / 4));
		this->addChild(G, 10);
		CCActionInterval *GAction1 = CCFadeTo::create(0.37, 100);
		CCActionInterval *GAction2 = CCFadeTo::create(0.37, 200);
		CCFiniteTimeAction *GAction3 = CCRotateBy::create(0.25,5);
		CCFiniteTimeAction *GAction4 = CCRotateBy::create(0.25,-10);
		CCFiniteTimeAction *GAction5 = CCRotateBy::create(0.25,5);
		G->setScale(1);
		CCFiniteTimeAction *GAction6 = CCScaleTo::create(0.25, 1.25);
		CCFiniteTimeAction *GAction7 = CCScaleTo::create(0.25, 0.8);
		CCFiniteTimeAction *GAction8 = CCScaleTo::create(0.25, 1);

		CCActionInterval *GAct1 = CCSequence::create(GAction1, GAction2, NULL);
		CCActionInterval *GAct2 = CCSequence::create(GAction3, GAction4, GAction5, NULL);
		CCActionInterval *GAct3 = CCSequence::create(GAction6, GAction7, GAction8, NULL);
		CCActionInterval *GAct =  CCSpawn::create(GAct1, GAct2, GAct3, NULL);
		G->runAction(CCRepeatForever::create(GAct));

		// R::
		CCSprite* R = CCSprite::create("R.png");
		R->setPosition(ccp(winSize.width / 8 * 2, winSize.height * 3 / 4));
		this->addChild(R, 10);
		CCActionInterval *RAction1 = CCFadeTo::create(0.37, 100);
		CCActionInterval *RAction2 = CCFadeTo::create(0.37, 200);
		CCFiniteTimeAction *RAction3 = CCRotateBy::create(0.25,5);
		CCFiniteTimeAction *RAction4 = CCRotateBy::create(0.25,-10);
		CCFiniteTimeAction *RAction5 = CCRotateBy::create(0.25,5);
		R->setScale(1);
		CCFiniteTimeAction *RAction6 = CCScaleTo::create(0.25, 1.25);
		CCFiniteTimeAction *RAction7 = CCScaleTo::create(0.25, 0.8);
		CCFiniteTimeAction *RAction8 = CCScaleTo::create(0.25, 1);

		CCActionInterval *RAct1 = CCSequence::create(RAction1, RAction2, NULL);
		CCActionInterval *RAct2 = CCSequence::create(RAction3, RAction4, RAction5, NULL);
		CCActionInterval *RAct3 = CCSequence::create(RAction6, RAction7, RAction8, NULL);
		CCActionInterval *RAct =  CCSpawn::create(RAct1, RAct2, RAct3, NULL);
		R->runAction(CCRepeatForever::create(RAct));

		// A::
		CCSprite* A = CCSprite::create("A.png");
		A->setPosition(ccp(winSize.width / 8 * 3, winSize.height * 3 / 4));
		this->addChild(A, 10);
		CCActionInterval *AAction1 = CCFadeTo::create(0.37, 100);
		CCActionInterval *AAction2 = CCFadeTo::create(0.37, 200);
		CCFiniteTimeAction *AAction3 = CCRotateBy::create(0.25,5);
		CCFiniteTimeAction *AAction4 = CCRotateBy::create(0.25,-10);
		CCFiniteTimeAction *AAction5 = CCRotateBy::create(0.25,5);
		A->setScale(1);
		CCFiniteTimeAction *AAction6 = CCScaleTo::create(0.25, 1.25);
		CCFiniteTimeAction *AAction7 = CCScaleTo::create(0.25, 0.8);
		CCFiniteTimeAction *AAction8 = CCScaleTo::create(0.25, 1);

		CCActionInterval *AAct1 = CCSequence::create(AAction1, AAction2, NULL);
		CCActionInterval *AAct2 = CCSequence::create(AAction3, AAction4, AAction5, NULL);
		CCActionInterval *AAct3 = CCSequence::create(AAction6, AAction7, AAction8, NULL);
		CCActionInterval *AAct =  CCSpawn::create(AAct1, AAct2, AAct3, NULL);
		A->runAction(CCRepeatForever::create(AAct));

		// V::
		CCSprite* V = CCSprite::create("V.png");
		V->setPosition(ccp(winSize.width / 8 * 4, winSize.height * 3 / 4));
		this->addChild(V, 10);
		CCActionInterval *VAction1 = CCFadeTo::create(0.37, 100);
		CCActionInterval *VAction2 = CCFadeTo::create(0.37, 200);
		CCFiniteTimeAction *VAction3 = CCRotateBy::create(0.25,5);
		CCFiniteTimeAction *VAction4 = CCRotateBy::create(0.25,-10);
		CCFiniteTimeAction *VAction5 = CCRotateBy::create(0.25,5);
		V->setScale(1);
		CCFiniteTimeAction *VAction6 = CCScaleTo::create(0.25, 1.25);
		CCFiniteTimeAction *VAction7 = CCScaleTo::create(0.25, 0.8);
		CCFiniteTimeAction *VAction8 = CCScaleTo::create(0.25, 1);

		CCActionInterval *VAct1 = CCSequence::create(VAction1, VAction2, NULL);
		CCActionInterval *VAct2 = CCSequence::create(VAction3, VAction4, VAction5, NULL);
		CCActionInterval *VAct3 = CCSequence::create(VAction6, VAction7, VAction8, NULL);
		CCActionInterval *VAct =  CCSpawn::create(VAct1, VAct2, VAct3, NULL);
		V->runAction(CCRepeatForever::create(VAct));

		// I::
		CCSprite* I = CCSprite::create("I.png");
		I->setPosition(ccp(winSize.width / 8 * 5, winSize.height * 3 / 4));
		this->addChild(I, 10);
		CCActionInterval *IAction1 = CCFadeTo::create(0.37, 100);
		CCActionInterval *IAction2 = CCFadeTo::create(0.37, 200);
		CCFiniteTimeAction *IAction3 = CCRotateBy::create(0.25,5);
		CCFiniteTimeAction *IAction4 = CCRotateBy::create(0.25,-10);
		CCFiniteTimeAction *IAction5 = CCRotateBy::create(0.25,5);
		I->setScale(1);
		CCFiniteTimeAction *IAction6 = CCScaleTo::create(0.25, 1.25);
		CCFiniteTimeAction *IAction7 = CCScaleTo::create(0.25, 0.8);
		CCFiniteTimeAction *IAction8 = CCScaleTo::create(0.25, 1);

		CCActionInterval *IAct1 = CCSequence::create(IAction1, IAction2, NULL);
		CCActionInterval *IAct2 = CCSequence::create(IAction3, IAction4, IAction5, NULL);
		CCActionInterval *IAct3 = CCSequence::create(IAction6, IAction7, IAction8, NULL);
		CCActionInterval *IAct =  CCSpawn::create(IAct1, IAct2, IAct3, NULL);
		I->runAction(CCRepeatForever::create(IAct));

		// T::
		CCSprite* T = CCSprite::create("T.png");
		T->setPosition(ccp(winSize.width / 8 * 6, winSize.height * 3 / 4));
		this->addChild(T, 10);
		CCActionInterval *TAction1 = CCFadeTo::create(0.37, 100);
		CCActionInterval *TAction2 = CCFadeTo::create(0.37, 200);
		CCFiniteTimeAction *TAction3 = CCRotateBy::create(0.25,5);
		CCFiniteTimeAction *TAction4 = CCRotateBy::create(0.25,-10);
		CCFiniteTimeAction *TAction5 = CCRotateBy::create(0.25,5);
		T->setScale(1);
		CCFiniteTimeAction *TAction6 = CCScaleTo::create(0.25, 1.25);
		CCFiniteTimeAction *TAction7 = CCScaleTo::create(0.25, 0.8);
		CCFiniteTimeAction *TAction8 = CCScaleTo::create(0.25, 1);

		CCActionInterval *TAct1 = CCSequence::create(TAction1, TAction2, NULL);
		CCActionInterval *TAct2 = CCSequence::create(TAction3, TAction4, TAction5, NULL);
		CCActionInterval *TAct3 = CCSequence::create(TAction6, TAction7, TAction8, NULL);
		CCActionInterval *TAct =  CCSpawn::create(TAct1, TAct2, TAct3, NULL);
		T->runAction(CCRepeatForever::create(TAct));

		// Y::
		CCSprite* Y = CCSprite::create("Y.png");
		Y->setPosition(ccp(winSize.width / 8 * 7, winSize.height * 3 / 4));
		this->addChild(Y, 10);
		CCActionInterval *YAction1 = CCFadeTo::create(0.37, 100);
		CCActionInterval *YAction2 = CCFadeTo::create(0.37, 200);
		CCFiniteTimeAction *YAction3 = CCRotateBy::create(0.25,5);
		CCFiniteTimeAction *YAction4 = CCRotateBy::create(0.25,-10);
		CCFiniteTimeAction *YAction5 = CCRotateBy::create(0.25,5);
		Y->setScale(1);
		CCFiniteTimeAction *YAction6 = CCScaleTo::create(0.25, 1.25);
		CCFiniteTimeAction *YAction7 = CCScaleTo::create(0.25, 0.8);
		CCFiniteTimeAction *YAction8 = CCScaleTo::create(0.25, 1);

		CCActionInterval *YAct1 = CCSequence::create(YAction1, YAction2, NULL);
		CCActionInterval *YAct2 = CCSequence::create(YAction3, YAction4, YAction5, NULL);
		CCActionInterval *YAct3 = CCSequence::create(YAction6, YAction7, YAction8, NULL);
		CCActionInterval *YAct =  CCSpawn::create(YAct1, YAct2, YAct3, NULL);
		Y->runAction(CCRepeatForever::create(YAct));

		// Icon
		_starticon = CCSprite::create("voyage.png");
		_starticon->setScale(0.2);
		_starticon->setPosition(ccp(winSize.width / 2, winSize.height * 3 / 10));
		this->addChild(_starticon, 10);
		CCActionInterval *iconAction1 = CCFadeTo::create(0.37, 150);
		CCActionInterval *iconAction2 = CCFadeTo::create(0.37, 200);
		CCFiniteTimeAction *iconAction3 = CCRotateBy::create(1.5, 360);
		CCFiniteTimeAction *iconAction4 = CCScaleTo::create(0.25, 0.25);
		CCFiniteTimeAction *iconAction5 = CCScaleTo::create(0.25, 0.16);
		CCFiniteTimeAction *iconAction6 = CCScaleTo::create(0.25, 0.2);

		CCActionInterval *iconAct1 = CCSequence::create(iconAction1, iconAction2, iconAction1, iconAction2, NULL);
		CCActionInterval *iconAct2 = CCSequence::create(iconAction4, iconAction5, iconAction6, iconAction4, iconAction5, iconAction6,  NULL);
		CCActionInterval *iconAct =  CCSpawn::create(iconAct1, iconAct2, iconAction3, NULL);
		_starticon->runAction(CCRepeatForever::create(iconAct));

    } while (0);

    return bRet;
}

void BootScene::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

