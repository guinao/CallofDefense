#include "Shield.h"
#include "BootScene.h"
//#include "pthread/pthread.h"

Shield* Shield::m_shield = NULL;

//pthread_mutex_t mutex;

Shield::Shield()
{
	m_circle = NULL;
}

Shield::~Shield()
{
}

Shield* Shield::getShieldSingleton()
{
	if(NULL == m_shield)
	{
		m_shield = Shield::create();
		if(NULL != m_shield)
		{
			m_shield->autorelease();
		}
	}

	return m_shield;
}

bool Shield::init()
{
	bool bRet = false;

	do{
		CC_BREAK_IF( ! CCLayer::init() );

		initColorStrip();

		texture[0] = CCTextureCache::sharedTextureCache()->addImage("PvZelements/Tallnut_body.png");
		texture[1] = CCTextureCache::sharedTextureCache()->addImage("PvZelements/Tallnut_cracked1.png");
		texture[2] = CCTextureCache::sharedTextureCache()->addImage("PvZelements/Tallnut_cracked2.png");

		m_sprite = CCSprite::createWithTexture(texture[0]);
		m_color = m_sprite->getColor();

		CCRotateBy *action1 = CCRotateBy::create(1, 20, 20);
		CCActionInterval *action2 = action1->reverse();
		CCSequence *action3 = CCSequence::create(
			action1, 
			action2, 
			action2, 
			action1, 
			NULL);

		m_sprite->runAction(CCRepeatForever::create(action3));

		CCSize size = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint position = ccp(size.width/2 , size.height/2);
		m_sprite->setPosition(position);
		m_position = position;
		addChild(m_sprite, 31);

		setTouchEnabled(true);

		//pthread_mutex_init(&mutex,NULL);

		bRet = true;
	}while(0);

	return bRet;
}

void Shield::initColorStrip()
{
	float gradientAlpha = 0.7f;
	m_colorstep = 300;
	ccColor4B color[6];
	color[0].r = 0;
	color[0].g = 0;
	color[0].b = 0;
	color[0].a = 178;

	color[1].r = 64;
	color[1].g = 44;
	color[1].b = 58;
	color[1].a = 178;

	color[2].r = 67;
	color[2].g = 52;
	color[2].b = 89;
	color[2].a = 178;

	color[3].r = 151;
	color[3].g = 122;
	color[3].b = 191;
	color[3].a = 178;

	color[4].r = 144;
	color[4].g = 141;
	color[4].b = 242;
	color[4].a = 178;

	color[5].r = 172;
	color[5].g = 183;
	color[5].b = 242;
	color[5].a = 178;

	for(int i=0; i<5; ++i)
	{
		m_basecolor[i] = ccc4FFromccc4B(color[i+1]);
	}
	for(int i=0; i<5; ++i)
	{
		m_deltacolor[i].r = (m_basecolor[i+1].r - m_basecolor[i].r) / m_colorstep;
		m_deltacolor[i].g = (m_basecolor[i+1].g - m_basecolor[i].g) / m_colorstep;
		m_deltacolor[i].b = (m_basecolor[i+1].b - m_basecolor[i].b) / m_colorstep;
		m_deltacolor[i].b = 1.0f / m_colorstep;
	}
}

void Shield::drawSolidCycle(ccColor4F color, CCPoint center, float radius, int segs)
{
	float coef = 2.0f * (float) (M_PI) /segs;
	float gradientAlpha = 0.7f;
	CCPoint *vertices = new CCPoint[segs+2];

	int nVertices = 0;

	float rads = 0.0f;
	for(int i=0; i<=segs; ++i)
	{
		float x = radius * cosf(rads) + center.x;
		float y = radius * sinf(rads) + center.y;
		vertices[i] = ccp(x, y);
		rads += coef;
	}

	ccDrawSolidPoly(vertices, segs, color);
}

void Shield::drawShieldRegion()
{
	if(m_zombieinshield > 0)
	{
		glLineWidth( 5.0f );
		ccDrawColor4B(255, 0, 0, 255);
		ccDrawCircle(m_sprite->getPosition(), m_radius, 0, 1000, false);
	}

	int nStripes = ((rand() % 4) + 1) * 2;
	nStripes = 5;
	
	float dr = m_radius / nStripes;
	static int cc = 0;
	cc = (cc+1) % m_colorstep;
	for(int i=nStripes; i>0 ;--i)
	{
		ccColor4F color = m_basecolor[i];
		color.r += cc * m_deltacolor[i].r;
		color.g += cc * m_deltacolor[i].g;
		color.b += cc * m_deltacolor[i].b;
		drawSolidCycle(color, m_position, i*dr, 1000);
	}
}

void Shield::draw()
{
	drawShieldRegion();
}

void Shield::update(float delta)
{
	static int cnt = 0;
	if( ++cnt  %30 == 0 ){
		//	this->genBackground();
	}
}

void Shield::onEnter()
{
	CCLayer::onEnter();

	m_touched = false;
	m_radius = 200.0f;
	m_state = en_hpHigh;
	m_hp = kHpFull;
	m_zombieinshield = 0;

	NOTIFY->addObserver(
		this,
		callfuncO_selector(Shield::recvZombieOnBoardMessage),
		kZombiesOnBoardMessage,
		NULL);

	NOTIFY->addObserver(
		this,
		callfuncO_selector(Shield::recvZombieLeaveMessage),
		kZombieLeaveMessage,
		NULL);

//	m_background = NULL;
//	genBackground();

	scheduleUpdate();
}

void Shield::onExit()
{
	setTouchEnabled(false);
	m_shield = NULL;
	NOTIFY->removeObserver(this, kZombiesOnBoardMessage);
	NOTIFY->removeObserver(this, kZombieLeaveMessage);
	unscheduleUpdate();
}

void Shield::collideDetect()
{

}

void Shield::onHurt(float losehp)
{
	m_hp -= losehp;

	if(m_hp>kHpLow && m_hp<=kHpMid && m_state!=en_hpMid)
	{
		m_state = en_hpMid;
		m_sprite->setTexture(texture[1]);
		m_color = m_sprite->getColor();
	}
	else if(m_hp<=kHpLow && m_hp>0 && m_state!=en_hpLow)
	{
		m_state = en_hpLow;
		m_sprite->setTexture(texture[2]);
		m_color = m_sprite->getColor();
	}
	else if(m_hp <= 0)
	{
		NOTIFY->postNotification(kLoseMessage, NULL);
//		CCDirector::sharedDirector()->replaceScene(BootScene::scene());
	}
}

void Shield::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	if(1 == pTouches->count())
	{
		CCTouch	*touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
		CCPoint position = touch->getLocationInView();
		position = CCDirector::sharedDirector()->convertToUI(position);

		if( m_sprite->boundingBox().containsPoint(position) )
		{
			m_touched = true;
			m_oldtouchpoint = position;
		}
	}
}

static void printRect(const CCRect rect)
{
	char msg[128];

	sprintf(msg, "minx %f, miny %f, maxx %f, maxy %f", 
		rect.getMinX(), rect.getMinY(), rect.getMaxX(), rect.getMaxY());
	CCLOG(msg);
}

void Shield::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	//CCLOG("Shield::ccTouchesMoved");

	if(m_touched && 1==pTouches->count())
	{
		CCTouch	*touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
		CCPoint temppos = touch->getLocationInView();
		CCPoint position = CCDirector::sharedDirector()->convertToUI(temppos);

		//CCPoint delta = ccp(position.x-m_oldtouchpoint.x, position.y-m_oldtouchpoint.y);
		CCPoint delta = ccpSub(position, m_oldtouchpoint);

		float x = m_sprite->getPositionX() + delta.x;
		float y = m_sprite->getPositionY() + delta.y;
		CCSize size = CCDirector::sharedDirector()->getVisibleSize();
		if(x > size.width)
			x = size.width;
		if(x < 0.0f)
			x = 0.0f;
		if(y > size.height)
			y = size.height;
		if(y < 0.0f)
			y = 0.0f;

		m_position = ccp(x, y);
		m_sprite->setPosition(m_position);
//		m_background->setPosition(m_position);

		m_oldtouchpoint = position;

		CCDictionary *dict = CCDictionary::create();
		dict->setObject(CCFloat::create(m_radius), "r");
		dict->setObject(CCFloat::create(m_sprite->getPositionX()), "x");
		dict->setObject(CCFloat::create(m_sprite->getPositionY()), "y");

		NOTIFY->postNotification(kShieldPostionChangedMessage, dict);
	}
}

void Shield::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	m_touched = false;
}

void Shield::getCenterAndRadius(float &r, float &x, float &y)
{
	r = m_radius;
	x = m_sprite->getPositionX();
	y = m_sprite->getPositionY();
}

void Shield::recvZombieOnBoardMessage(CCObject *)
{
	char msg[128];

	//pthread_mutex_lock(&mutex);
	m_zombieinshield ++;
	//pthread_mutex_unlock(&mutex);
	
	sprintf(msg, "Shield::recvZombieOnBoardMessage %d", m_zombieinshield);
	CCLOG(msg);
}

void Shield::recvZombieLeaveMessage(CCObject *)
{
	char msg[128];

	//pthread_mutex_lock(&mutex);
	m_zombieinshield --;
	//pthread_mutex_unlock(&mutex);

	sprintf(msg, "Shield::recvZombieOnBoardMessage %d", m_zombieinshield);
	CCLOG(msg);
}

void Shield::genBackground()
{
	if (m_background)
	{
		m_background->removeFromParentAndCleanup(true);
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	ccColor4F bgColor = this->randomBrightColor();
	ccColor4F color2 = this->randomBrightColor();
	//m_background = this->spriteWithColor(bgColor, 512, 512);
	int nStripes = ((rand() % 4) + 1) * 2;
	m_background = this->spriteWithColor1(bgColor, color2, 1024, 512, nStripes);

	m_background->setScale(0.5);

	m_background->setPosition(m_position);
	ccTexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
	m_background->getTexture()->setTexParameters(&tp);
	this->addChild(m_background, 1);
}

ccColor4F Shield::randomBrightColor()
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

CCSprite * Shield::spriteWithColor1(ccColor4F c1, ccColor4F c2, float textureWidth, float textureHeight, int nStripes)
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
