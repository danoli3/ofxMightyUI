/*
 *  Button.h
 *
 *  yyyy, a button!
 
 void onEvent(const void* pSender, ofTouchEventArgs& arg){
	std::cout << "onEvent: " << arg << std::endl;
 }
 
 or

 void onEvent(ofTouchEventArgs& arg){
	std::cout << "onEvent: " << arg << std::endl;
 }
 
 
 then do button.onPress += Delegate<YourClass,ofTouchEventArgs>( this, %YourClass::yourEventFunc );
 */

#ifndef MUI_TOGGLEBUTTON
#define MUI_TOGGLEBUTTON

#include "MuiCore.h"

namespace mui{
	class Label;
	
	class ToggleButton : public Container{
	public:
		ToggleButton( std::string title_, float x_ = 0, float y_ = 0, float width_ = 200, float height_ = 20 );
		virtual ~ToggleButton();
		Label * label;
		bool pressed;
		bool selected;
		ofColor selectedBg;
		ofColor selectedFg;
		ofEvent<ofTouchEventArgs> onPress;
		ofEvent<ofTouchEventArgs> onContextMenu;
		ofEvent<bool> onChange;
		
		bool checkbox;
		HorizontalAlign checkboxAlign;
		
		virtual void update();
		virtual void draw();
		virtual void drawBackground();
		virtual void fitWidthToLabel(int paddingLR = 5); // deprecated
		virtual void fitWidthToLabel(int paddingL, int paddingR ); // deprecated
		virtual void sizeToFitWidth(int paddingLR = 5);
		virtual void sizeToFitWidth(int paddingL, int paddingR );
		virtual void layout();

		// simulate a click
		virtual void clickAndNotify();
		virtual void clickAndNotify(bool state);
		
		virtual void touchDown( ofTouchEventArgs &touch );
		virtual void touchMoved( ofTouchEventArgs &touch );
		virtual void touchMovedOutside( ofTouchEventArgs &touch );
		virtual void touchUp( ofTouchEventArgs &touch );
		virtual void touchUpOutside( ofTouchEventArgs &touch );
		virtual void touchDoubleTap( ofTouchEventArgs &touch );
		virtual void touchCanceled( ofTouchEventArgs &touch );
		
	private:
		bool isRightClick; 
	};
};

#endif