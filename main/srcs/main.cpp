// Start of wxWidgets "Hello World" Program

#include "wx/wx.h"
#include "main.h"
#include "main_frame.h"


bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);
 
