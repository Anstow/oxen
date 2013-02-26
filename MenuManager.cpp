#include "MenuManager.h"
#include <CEGUIVector.h>

MenuManager::MenuManager(Ogre::RenderTarget &pWnd) {
	// Set up the renderer
	CEGUI::OgreRenderer* renderer = &CEGUI::OgreRenderer::bootstrapSystem(pWnd);

	CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
	
	// Load the scheme
	CEGUI::SchemeManager::getSingletonPtr()->create("TaharezLook.scheme");
	// Create the mouse cursor
	CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");

	// Attach the root menu
	m_pRootWnd = CEGUI::WindowManager::getSingletonPtr()->createWindow("DefaultWindow", "_MasterRoot");
	// Make the root window ignore mouse clicks
	m_pRootWnd->setMousePassThroughEnabled(true);

	CEGUI::System::getSingletonPtr()->setGUISheet(m_pRootWnd);
}

MenuManager::~MenuManager() {
	// TODO: I'm not sure if this is necessary, remove if it isn't
	// CEGUI::WindowManager::getSingletonPtr()->destroyAllWindows();
}

void MenuManager::pushMenu(CEGUI::Window* pMenu) {
	if (pMenu) {
		m_pRootWnd->addChildWindow(pMenu);
	}
}
	
void MenuManager::popMenu(CEGUI::Window* pMenu) {
	m_pRootWnd->removeChildWindow(pMenu);
}

bool MenuManager::InjectOISkeyDown(const OIS::KeyEvent &inKey) {
	CEGUI::System::getSingletonPtr()->injectKeyDown(inKey.key);
	return CEGUI::System::getSingletonPtr()->injectChar(inKey.text);
}

bool MenuManager::InjectOISkeyUp(const OIS::KeyEvent &inKey) {
	return CEGUI::System::getSingletonPtr()->injectKeyUp(inKey.key);
}

bool MenuManager::InjectOISMouseButtonDown(const OIS::MouseEvent &arg, const OIS::MouseButtonID &inButton) {
	bool rtn = false;
	switch (inButton) {
	case OIS::MB_Left:
		rtn = CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);
		break;
	case OIS::MB_Middle:
		rtn = CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MiddleButton);
		break;
	case OIS::MB_Right:
		rtn = CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);
		break;
	case OIS::MB_Button3:
		rtn = CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::X1Button);
		break;
	case OIS::MB_Button4:
		rtn = CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::X2Button);
		break;
	default:	
		break;
	}
	return rtn;
}

bool MenuManager::InjectOISMouseButtonUp(const OIS::MouseEvent &arg, const OIS::MouseButtonID &inButton) {
	bool rtn = false;
	switch (inButton) {
	case OIS::MB_Left:
		rtn = CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);
		break;
	case OIS::MB_Middle:
		rtn = CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MiddleButton);
		break;
	case OIS::MB_Right:
		rtn = CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::RightButton);
		break;
	case OIS::MB_Button3:
		rtn = CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::X1Button);
		break;
	case OIS::MB_Button4:
		rtn = CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::X2Button);
		break;
	default:	
		break;
	}
	return rtn;
}

bool MenuManager::InjectOISMouseMove(const OIS::MouseEvent &arg) {
	CEGUI::System &sys = CEGUI::System::getSingleton();
	sys.injectMousePosition(arg.state.X.abs, arg.state.Y.abs);
	// Scroll wheel.
	if (arg.state.Z.rel) {
		sys.injectMouseWheelChange(arg.state.Z.rel / 120.0f);
	}
	return true;
}

Ogre::Vector2 MenuManager::getMousePos() {
	CEGUI::Point p = CEGUI::MouseCursor::getSingleton().getPosition();
	return Ogre::Vector2(p.d_x, p.d_y);
}

