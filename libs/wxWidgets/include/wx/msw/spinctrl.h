////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/spinctrl.h
// Purpose:     wxSpinCtrl class declaration for Win32
// Author:      Vadim Zeitlin
// Modified by:
// Created:     22.07.99
// Copyright:   (c) Vadim Zeitlin
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_MSW_SPINCTRL_H_
#define _WX_MSW_SPINCTRL_H_

#include "wx/spinbutt.h"    // the base class

#if wxUSE_SPINCTRL

#include "wx/dynarray.h"

class WXDLLIMPEXP_FWD_CORE wxSpinCtrl;
WX_DEFINE_EXPORTED_ARRAY_PTR(wxSpinCtrl *, wxArraySpins);

// ----------------------------------------------------------------------------
// Under Win32, wxSpinCtrl is a wxSpinButton with a buddy (as MSDN docs call
// it) text window whose contents is automatically updated when the spin
// control is clicked.
// ----------------------------------------------------------------------------

class WXDLLIMPEXP_CORE wxSpinCtrl : public wxSpinButton
{
public:
    wxSpinCtrl() { Init(); }

    wxSpinCtrl(wxWindow *parent,
               wxWindowID id = wxID_ANY,
               const wxString& value = wxEmptyString,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = wxSP_ARROW_KEYS,
               int min = 0, int max = 100, int initial = 0,
               const wxString& name = wxT("wxSpinCtrl"))
    {
        Init();

        Create(parent, id, value, pos, size, style, min, max, initial, name);
    }

    bool Create(wxWindow *parent,
                wxWindowID id = wxID_ANY,
                const wxString& value = wxEmptyString,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = wxSP_ARROW_KEYS,
                int min = 0, int max = 100, int initial = 0,
                const wxString& name = wxT("wxSpinCtrl"));

    // a wxTextCtrl-like method (but we can't have GetValue returning wxString
    // because the base class already has one returning int!)
    void SetValue(const wxString& text);

    // another wxTextCtrl-like method
    void SetSelection(long from, long to);

    // wxSpinCtrlBase methods
    virtual wxString GetTextValue() const;
    virtual int GetBase() const;
    virtual bool SetBase(int base);

    virtual void Refresh( bool eraseBackground = true,
                          const wxRect *rect = (const wxRect *) NULL ) wxOVERRIDE;

    // implementation only from now on
    // -------------------------------

    virtual ~wxSpinCtrl();

    virtual void SetValue(int val) wxOVERRIDE;
    virtual int  GetValue() const wxOVERRIDE;
    virtual void SetRange(int minVal, int maxVal) wxOVERRIDE;
    virtual bool SetFont(const wxFont &font) wxOVERRIDE;

    virtual bool Enable(bool enable = true) wxOVERRIDE;
    virtual bool Show(bool show = true) wxOVERRIDE;

    virtual bool Reparent(wxWindowBase *newParent) wxOVERRIDE;

    // wxSpinButton doesn't accept focus, but we do
    virtual bool AcceptsFocus() const wxOVERRIDE { return wxWindow::AcceptsFocus(); }

    // we're like wxTextCtrl and not (default) wxButton
    virtual wxVisualAttributes GetDefaultAttributes() const wxOVERRIDE
    {
        return GetClassDefaultAttributes(GetWindowVariant());
    }

    static wxVisualAttributes
    GetClassDefaultAttributes(wxWindowVariant variant = wxWINDOW_VARIANT_NORMAL)
    {
        return GetCompositeControlsDefaultAttributes(variant);
    }

    // for internal use only

    // get the subclassed window proc of the buddy text
    WXWNDPROC GetBuddyWndProc() const { return m_wndProcBuddy; }

    // return the spinctrl object whose buddy is the given window or NULL
    static wxSpinCtrl *GetSpinForTextCtrl(WXHWND hwndBuddy);

    // process a WM_COMMAND generated by the buddy text control
    bool ProcessTextCommand(WXWORD cmd, WXWORD id);

    // recognize buddy window as part of this control at wx level
    virtual bool ContainsHWND(WXHWND hWnd) const wxOVERRIDE { return hWnd == m_hwndBuddy; }

    virtual void SetLayoutDirection(wxLayoutDirection dir) wxOVERRIDE;

    virtual WXHWND MSWGetFocusHWND() const wxOVERRIDE;

protected:
    virtual void DoGetPosition(int *x, int *y) const wxOVERRIDE;
    virtual void DoMoveWindow(int x, int y, int width, int height) wxOVERRIDE;
    virtual wxSize DoGetBestSize() const wxOVERRIDE;
    virtual wxSize DoGetSizeFromTextSize(int xlen, int ylen = -1) const wxOVERRIDE;
    virtual void DoGetSize(int *width, int *height) const wxOVERRIDE;
    virtual void DoGetClientSize(int *x, int *y) const wxOVERRIDE;
    virtual void DoClientToScreen(int *x, int *y) const wxOVERRIDE;
    virtual void DoScreenToClient(int *x, int *y) const wxOVERRIDE;
#if wxUSE_TOOLTIPS
    virtual void DoSetToolTip( wxToolTip *tip ) wxOVERRIDE;
#endif // wxUSE_TOOLTIPS

    virtual bool MSWOnNotify(int idCtrl, WXLPARAM lParam, WXLPARAM *result) wxOVERRIDE;
    virtual bool MSWOnScroll(int orientation, WXWORD wParam,
                             WXWORD pos, WXHWND control) wxOVERRIDE;
    virtual void MSWUpdateFontOnDPIChange(const wxSize& newDPI) wxOVERRIDE;

    // handle processing of special keys
    void OnChar(wxKeyEvent& event);
    void OnSetFocus(wxFocusEvent& event);
    void OnKillFocus(wxFocusEvent& event);

    // returns true for special keys like "Ctrl+C" that should be handled
    // by the text control
    virtual bool MSWShouldPreProcessMessage(WXMSG* msg) wxOVERRIDE;

    // generate spin control update event with the given value
    void SendSpinUpdate(int value);

    // called to ensure that the value is in the correct range
    virtual void NormalizeValue() wxOVERRIDE;

    // the value of the control before the latest change (which might not have
    // changed anything in fact -- this is why we need this field)
    int m_oldValue;

    // the data for the "buddy" text ctrl
    WXHWND     m_hwndBuddy;
    WXWNDPROC  m_wndProcBuddy;

    // Block text update event after SetValue()
    bool m_blockEvent;

private:
    // Common part of all ctors.
    void Init();

    // Adjust the text control style depending on whether we need to enter only
    // digits or may need to enter something else (e.g. "-" sign, "x"
    // hexadecimal prefix, ...) in it.
    void UpdateBuddyStyle();

    // Determine the (horizontal) pixel overlap between the spin button
    // (up-down control) and the text control (buddy window).
    int GetOverlap() const;

    // Calculate the best size for the number with the given number of digits.
    wxSize GetBestSizeFromDigitsCount(int digitsCount) const;

    wxDECLARE_DYNAMIC_CLASS(wxSpinCtrl);
    wxDECLARE_EVENT_TABLE();
    wxDECLARE_NO_COPY_CLASS(wxSpinCtrl);
};

#endif // wxUSE_SPINCTRL

#endif // _WX_MSW_SPINCTRL_H_


