
#include "prime_panel.h"
#include "wx/wx.h"

PrimaryUIPanel::PrimaryUIPanel(wxWindow *parent) : wxPanel(parent)
{
    wxButton *button_1 = new wxButton(this, wxID_ANY, "button", wxPoint(100, 100), wxSize(100, 50), wxBU_LEFT);
}
