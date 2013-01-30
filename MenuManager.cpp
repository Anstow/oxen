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

	CEGUI::System::getSingletonPtr()->setGUISheet(m_pRootWnd);
}

MenuManager::~MenuManager() {
	// Clears the menu pointers
	while(!m_Menus.empty()) {
		m_Menus.pop_back();
	}

	// TODO: I'm not sure if this is necessary, remove if it isn't
	//CEGUI::WindowManager::getSingletonPtr()->destroyAllWindows();
}

void MenuManager::pushMenu(CEGUI::Window* pMenu) {
	if (pMenu) {
		m_pRootWnd->addChildWindow(pMenu);
		m_Menus.push_back(pMenu);
	}
}
	
void MenuManager::popMenu() {
	if (!m_Menus.empty()) {
		m_pRootWnd->removeChildWindow(m_Menus.back());
		m_Menus.pop_back();
	}
}

void MenuManager::popAllMenus() {
	while (!m_Menus.empty()) {
		m_pRootWnd->removeChildWindow(m_Menus.back());
		m_Menus.pop_back();
	}
}

bool MenuManager::InjectOISkeyDown(const OIS::KeyEvent &inKey) {
	CEGUI::System::getSingletonPtr()->injectKeyDown(inKey.key);
	CEGUI::System::getSingletonPtr()->injectChar(inKey.text);
	return true;
}

bool MenuManager::InjectOISkeyUp(const OIS::KeyEvent &inKey) {
	CEGUI::System::getSingletonPtr()->injectKeyUp(inKey.key);
	return true;
}

bool MenuManager::InjectOISMouseButtonDown(const OIS::MouseEvent &arg, const OIS::MouseButtonID &inButton) {
	switch (inButton) {
	case OIS::MB_Left:
		CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);
		break;
	case OIS::MB_Middle:
		CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MiddleButton);
		break;
	case OIS::MB_Right:
		CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);
		break;
	case OIS::MB_Button3:
		CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::X1Button);
		break;
	case OIS::MB_Button4:
		CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::X2Button);
		break;
	default:	
		break;
	}
	// TODO: This is a little hacked it depends on the absolute position of the
	// mouse. We should invesitgate if we can do this using the return from the
	// inject statements.
	return m_pRootWnd->getChildAtPosition(CEGUI::Vector2(arg.state.X.abs, arg.state.Y.abs));
}

bool MenuManager::InjectOISMouseButtonUp(const OIS::MouseEvent &arg, const OIS::MouseButtonID &inButton) {
	switch (inButton) {
	case OIS::MB_Left:
		CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);
		break;
	case OIS::MB_Middle:
		CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MiddleButton);
		break;
	case OIS::MB_Right:
		CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::RightButton);
		break;
	case OIS::MB_Button3:
		CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::X1Button);
		break;
	case OIS::MB_Button4:
		CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::X2Button);
		break;
	default:	
		break;
	}
	// TODO: This is a little hacked it depends on the absolute position of the
	// mouse. We should invesitgate if we can do this using the return from the
	// inject statements.
	return m_pRootWnd->getChildAtPosition(CEGUI::Vector2(arg.state.X.abs, arg.state.Y.abs));
}

bool MenuManager::InjectOISMouseMove(const OIS::MouseEvent &arg) {
	CEGUI::System &sys = CEGUI::System::getSingleton();
	sys.injectMousePosition(arg.state.X.abs, arg.state.Y.abs);
	// Scroll wheel.
	if (arg.state.Z.rel) {
		sys.injectMouseWheelChange(arg.state.Z.rel / 120.0f);
	}
	// TODO: This is a little hacked it depends on the absolute position of the
	// mouse. We should invesitgate if we can do this using the return from the
	// inject statements.
	return m_pRootWnd->getChildAtPosition(CEGUI::Vector2(arg.state.X.abs, arg.state.Y.abs));
}

bool MenuManager::InjectOISMousePosition(float xPos, float yPos) {
	CEGUI::System::getSingleton().injectMousePosition(xPos, yPos);
	return true;
}
