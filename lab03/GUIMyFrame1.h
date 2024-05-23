#ifndef __GUIMyFrame1__
#define __GUIMyFrame1__

/**
@file
Subclass of MyFrame1, which is generated by wxFormBuilder.
*/

#include "GUI.h"

//// end generated include

/** Implementing MyFrame1 */
class GUIMyFrame1 : public MyFrame1
{
	protected:
		// Handlers for MyFrame1 events.
		void m_panel3OnUpdateUI(wxUpdateUIEvent& event);
		void m_button7OnButtonClick( wxCommandEvent& event );
		void m_checkBox3OnCheckBox( wxCommandEvent& event );
		void m_scrollBar2OnScroll( wxScrollEvent& event );
		void m_button8OnButtonClick( wxCommandEvent& event );
		void m_textCtrl2OnText( wxCommandEvent& event );
		void m_choice1OnChoice( wxCommandEvent& event );
	public:
		/** Constructor */
		GUIMyFrame1( wxWindow* parent );
	//// end generated class members
		void Repaint();
		wxBitmap bitmap;

};

#endif // __GUIMyFrame1__
