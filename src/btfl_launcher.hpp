#ifndef _BTFLLAUNCHER_HPP_
#define _BTFLLAUNCHER_HPP_

#include <wx/app.h>

#include "frames/frame.app_main.hpp"

class BTFLLauncher : public wxApp {
private:
    Frame::AppMain* pAppFrame;

public:
    virtual bool OnInit() override;
    virtual int OnExit() override;

private:
    void SetupManagers();
};

wxDECLARE_APP(BTFLLauncher);

#endif  // _BTFLLAUNCHER_HPP_
