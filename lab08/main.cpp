#include <wx/wx.h>
#include "GUIMyFrame1.h"

#define FREEIMAGE_LIB

class MyApp : public wxApp {

public:

	virtual bool OnInit();
	virtual int OnExit() { FreeImage_DeInitialise(); return 0; }

};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
	FreeImage_Initialise();
	wxInitAllImageHandlers();

	SetProcessDPIAware();
	GUIMyFrame1* mainFrame = new GUIMyFrame1(NULL);

	mainFrame->Show(true);
	mainFrame->Repaint();
	SetTopWindow(mainFrame);

	return true;
}