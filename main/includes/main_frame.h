#ifndef __MAIN_FRAME_H__
#define __MAIN_FRAME_H__

#include "wx/wx.h"


class MyFrame : public wxFrame
{
public:
    MyFrame();
 
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

#endif // __MAIN_FRAME_H__
