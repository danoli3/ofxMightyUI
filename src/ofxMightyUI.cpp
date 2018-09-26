/*
 *  ofxMightyUI.cpp
 *  ofxMightyUI
 *
 *  Created by hansi on 28.01.11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxMightyUI.h"
#include <Poco/Util/Application.h>


#if TARGET_OS_IPHONE
	#include "ofAppiOSWindow.h"
	#include <CoreFoundation/CoreFoundation.h>
#elif TARGET_OS_MAC
	#include "ofAppGLFWWindow.h"
#elif _WIN32
	#include <windows.h>
	#include "ofAppGLFWWindow.h"
#endif

void mui_init(){
	#if TARGET_OS_IPHONE
	if( mui::MuiConfig::detectRetina ){
		ofAppiOSWindow * w = ofAppiOSWindow::getInstance();
		if( w->isRetinaEnabled() ){
			mui::MuiConfig::scaleFactor = 2;
			mui::MuiConfig::useRetinaAssets = true;
		}
	}
	#endif

	Poco::Path appPath;
	#if TARGET_OS_IPHONE
		// http://www.cocoabuilder.com/archive/cocoa/193451-finding-out-executable-location-from-c-program.html
		CFBundleRef bundle = CFBundleGetMainBundle();
		CFURLRef    url  = CFBundleCopyExecutableURL(bundle); // CFBundleCopyResourcesDirectoryURL(bundle);
		CFURLRef absolute = CFURLCopyAbsoluteURL(url);
		CFStringRef path  = CFURLCopyFileSystemPath(url, kCFURLPOSIXPathStyle);
		CFIndex    maxLength = CFStringGetMaximumSizeOfFileSystemRepresentation(path);
		char        *result = (char*)malloc(maxLength);
		
		if(result) {
			if(!CFStringGetFileSystemRepresentation(path,result, maxLength)) {
				free(result);
				result = NULL;
			}
		}
		
		CFRelease(path);
		CFRelease(url);
		CFRelease(absolute);
		appPath = Poco::Path(result);
		appPath = appPath.parent();
	#elif TARGET_OS_MAC
		// http://www.cocoabuilder.com/archive/cocoa/193451-finding-out-executable-location-from-c-program.html
		CFBundleRef bundle = CFBundleGetMainBundle();
		CFURLRef    url  = CFBundleCopyExecutableURL(bundle); // CFBundleCopyResourcesDirectoryURL(bundle);
		CFURLRef absolute = CFURLCopyAbsoluteURL(url);
		CFStringRef path  = CFURLCopyFileSystemPath(url, kCFURLPOSIXPathStyle);
		CFIndex    maxLength = CFStringGetMaximumSizeOfFileSystemRepresentation(path);
		char        *result = (char*)malloc(maxLength);
		
		if(result) {
			if(!CFStringGetFileSystemRepresentation(path,result, maxLength)) {
				free(result);
				result = NULL;
			}
		}
		
		CFRelease(path);
		CFRelease(url);
		CFRelease(absolute);
		appPath = Poco::Path(result);
		if(result != NULL ) free(result); 
		appPath = appPath.parent().parent().pushDirectory("Resources");
	
		if( mui::MuiConfig::detectRetina ){
			ofAppGLFWWindow * window = dynamic_cast<ofAppGLFWWindow*>(ofGetWindowPtr());
			if( window != NULL ){
				mui::MuiConfig::scaleFactor = window->getPixelScreenCoordScale();
			}
		}
	#elif _WIN32
		if (mui::MuiConfig::detectRetina) {
			SetProcessDPIAware(); //true
			HDC screen = GetDC(NULL);
			double hPixelsPerInch = GetDeviceCaps(screen, LOGPIXELSX);
			double vPixelsPerInch = GetDeviceCaps(screen, LOGPIXELSY);
			ReleaseDC(NULL, screen);
			float dpi = (hPixelsPerInch + vPixelsPerInch) * 0.5/96.0;
			mui::MuiConfig::scaleFactor = dpi;
			cout << "scale factor = " << dpi << endl;
		}
		appPath = Poco::Path(ofToDataPath("./", true));
	#else
		appPath = Poco::Path(ofToDataPath("./", true));
	#endif
	
	mui::MuiConfig::dataPath = appPath.absolute();
	mui::Helpers::getFontStash().setup(mui::MuiConfig::fontAtlasSize );
	mui::Helpers::getFontStash().pixelDensity = mui::MuiConfig::scaleFactor;
	mui::Helpers::getFontStash().fontScale = 1.3;
}

float muiGetDefaultDisplayScaling(){
#if TARGET_OS_IPHONE
	if( mui::MuiConfig::detectRetina ){
		ofAppiOSWindow * w = ofAppiOSWindow::getInstance();
		return w->isRetinaEnabled()?2:1;
	}
#elif TARGET_OS_MAC
	ofAppGLFWWindow * window = dynamic_cast<ofAppGLFWWindow*>(ofGetWindowPtr());
	if( window != NULL ){
		return window->getPixelScreenCoordScale();
	}
	else{
		return 1;
	}
#elif _WIN32
	SetProcessDPIAware(); //true
	HDC screen = GetDC(NULL);
	double hPixelsPerInch = GetDeviceCaps(screen, LOGPIXELSX);
	double vPixelsPerInch = GetDeviceCaps(screen, LOGPIXELSY);
	ReleaseDC(NULL, screen);
	float dpi = (hPixelsPerInch + vPixelsPerInch) * 0.5/96.0;
	return dpi;
#else
	return 1;
#endif
}


ofVec2f muiGetMousePos(){
	return ofVec2f(ofGetMouseX(),ofGetMouseY())/mui::MuiConfig::scaleFactor;
}

int muiGetMouseX(){
	return ofGetMouseX()/mui::MuiConfig::scaleFactor;
}

int muiGetMouseY(){
	return ofGetMouseY()/mui::MuiConfig::scaleFactor;
}

float muiGetWidth(){
	return ofGetWidth()/mui::MuiConfig::scaleFactor;
}

float muiGetHeight(){
	return ofGetHeight()/mui::MuiConfig::scaleFactor;
}

string muiToDataPath( string path, bool abs ){
	return mui::Helpers::muiPath(path);
}