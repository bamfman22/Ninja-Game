#include "Sprite.h"

BaseObject::BaseObject() {
    trans = ofVec3f(0,0,0);
    scale = ofVec3f(1, 1, 1);
    rot = 1;
}

void BaseObject::setPosition(ofVec3f pos) {
    trans = pos;
}

//
// Basic Sprite Object
//
Sprite::Sprite() {
    speed = 0;
    velocity = ofVec3f(0,0, 0) ;
    lifespan = -1;      // lifespan of -1 => immortal
    birthtime = 0;
    bSelected = false;
    haveImage = false;
    name = "UnamedSprite";
    width = 20;
    height = 20;
    
    
    
}

// Return a sprite's age in milliseconds
//
float Sprite::age() {
    return (ofGetElapsedTimeMillis() - birthtime);
}

//  Set an image for the sprite. If you don't set one, a rectangle
//  gets drawn.
//
void Sprite::setImage(ofImage img) {
    image = img;
    haveImage = true;
    width = image.getWidth();
    height = image.getHeight();
}


//  Render the sprite
//
void Sprite::draw() {
    
    ofSetColor(255, 255, 255, 255);
    
    // draw image centered and add in translation amount
    //
    if (haveImage) {
        image.draw(width / 2.0 + trans.x, -height / 2.0 + trans.y);
    }
    else {
        
        ofNoFill();
        ofSetColor(255, 0, 0);
        ofDrawRectangle(-width / 2.0 + trans.x, -height / 2.0 + trans.y, width, height);
    }
}

//  Add a Sprite to the Sprite System
//
void SpriteSystem::add(Sprite s) {
    sprites.push_back(s);
}

//remove sprite whenever it comes into contact with something
bool SpriteSystem::removeNear(ofVec3f point, float dist) {
    vector<Sprite>::iterator s = sprites.begin();
    vector<Sprite>::iterator tmp;
    while (s != sprites.end()) {
        ofVec3f v = s->trans - point;
        if (v.length() < dist) {
            tmp = sprites.erase(s);
            s = tmp;
            return true;
        }
        else s++;
    }
    return false;
}

void SpriteSystem::remove(int i) {
    sprites.erase(sprites.begin() + i);
}

//update method
void SpriteSystem::update() {
    
    if (sprites.size() == 0) return;
    vector<Sprite>::iterator s = sprites.begin();
    vector<Sprite>::iterator tmp;
    
    
    while (s != sprites.end()) {
        if (s->lifespan != -1 && s->age() > s->lifespan) {
           
            tmp = sprites.erase(s);
            s = tmp;
        }
       
        //we can create a new velocity for our sprite so its movements are unpredictable and creates a much more interesting game
        else if(bullet == false){
            s->velocity.x += ofRandom(-50,50);
            s->velocity.y += ofRandom(-50,50);
           
            s++;
        }
        else{
            s++;
        }
    }
    //move sprite
    for (int i = 0; i < sprites.size(); i++) {
        sprites[i].trans += sprites[i].velocity / ofGetFrameRate();
        
        
    }
   
}

//  Render all the sprites
//
void SpriteSystem::draw() {
    for (int i = 0; i < sprites.size(); i++) {
        sprites[i].draw();
    }
    
}

