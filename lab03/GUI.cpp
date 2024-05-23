///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.1.0-0-g733bf3d)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/colordlg.h>
#include <wx/wxprec.h>
#include <wx/bitmap.h>
#include <wx/image.h>

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints(wxSize(600, 400), wxDefaultSize);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel3->SetBackgroundColour(wxColour(255, 255, 255));

	bSizer6->Add( m_panel3, 1, wxEXPAND | wxALL, 5 );


	bSizer4->Add( bSizer6, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_button7 = new wxButton( this, wxID_ANY, wxT("Zapis do pliku"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_button7, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

	m_checkBox3 = new wxCheckBox( this, wxID_ANY, wxT("banan"), wxPoint( -1,-1 ), wxDefaultSize, 0 );
	bSizer5->Add( m_checkBox3, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

	m_scrollBar2 = new wxScrollBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	m_scrollBar2->Enable(false);
	m_scrollBar2->SetScrollbar(0, 5, 100, 5);
	m_scrollBar2->SetMinSize( wxSize( 175,-1 ) );

	bSizer5->Add( m_scrollBar2, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

	m_gauge2 = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_gauge2->SetValue( 0 );
	m_gauge2->SetMaxSize( wxSize( 175,-1 ) );

	bSizer5->Add( m_gauge2, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

	m_button8 = new wxButton( this, wxID_ANY, wxT("kolor gwiazdki"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_button8, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

	m_textCtrl2 = new wxTextCtrl( this, wxID_ANY, wxT("tekst"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer5->Add( m_textCtrl2, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

	wxArrayString m_choice1Choices = {"gwiazdka", "ksiezyc", "slonko"};
	m_choice1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1Choices, 0 );
	m_choice1->SetSelection( 0 );
	bSizer5->Add( m_choice1, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );


	bSizer4->Add( bSizer5, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer4 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_panel3->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::m_panel3OnUpdateUI), NULL, this);
	m_button7->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button7OnButtonClick ), NULL, this );
	m_checkBox3->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBox3OnCheckBox ), NULL, this );
	m_scrollBar2->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::m_scrollBar2OnScroll ), NULL, this );
	m_scrollBar2->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::m_scrollBar2OnScroll ), NULL, this );
	m_scrollBar2->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::m_scrollBar2OnScroll ), NULL, this );
	m_scrollBar2->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::m_scrollBar2OnScroll ), NULL, this );
	m_scrollBar2->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::m_scrollBar2OnScroll ), NULL, this );
	m_scrollBar2->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::m_scrollBar2OnScroll ), NULL, this );
	m_scrollBar2->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::m_scrollBar2OnScroll ), NULL, this );
	m_scrollBar2->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::m_scrollBar2OnScroll ), NULL, this );
	m_scrollBar2->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::m_scrollBar2OnScroll ), NULL, this );
	m_button8->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button8OnButtonClick ), NULL, this );
	m_textCtrl2->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MyFrame1::m_textCtrl2OnText ), NULL, this );
	m_choice1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyFrame1::m_choice1OnChoice ), NULL, this );

	wxInitAllImageHandlers();

	wxImage imagebanan;
	imagebanan.LoadFile("banan.png", wxBITMAP_TYPE_PNG);
	bananbitmap = wxBitmap(imagebanan);
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_panel3->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::m_panel3OnUpdateUI), NULL, this);
	m_button7->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button7OnButtonClick ), NULL, this );
	m_checkBox3->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBox3OnCheckBox ), NULL, this );
	m_scrollBar2->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::m_scrollBar2OnScroll ), NULL, this );
	m_scrollBar2->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::m_scrollBar2OnScroll ), NULL, this );
	m_scrollBar2->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::m_scrollBar2OnScroll ), NULL, this );
	m_scrollBar2->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::m_scrollBar2OnScroll ), NULL, this );
	m_scrollBar2->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::m_scrollBar2OnScroll ), NULL, this );
	m_scrollBar2->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::m_scrollBar2OnScroll ), NULL, this );
	m_scrollBar2->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::m_scrollBar2OnScroll ), NULL, this );
	m_scrollBar2->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::m_scrollBar2OnScroll ), NULL, this );
	m_scrollBar2->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::m_scrollBar2OnScroll ), NULL, this );
	m_button8->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button8OnButtonClick ), NULL, this );
	m_textCtrl2->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MyFrame1::m_textCtrl2OnText ), NULL, this );
	m_choice1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyFrame1::m_choice1OnChoice ), NULL, this );

}
