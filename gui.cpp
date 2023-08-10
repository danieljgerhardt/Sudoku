// Start of wxWidgets "Hello World" Program
#include <wx/wx.h>

class Sudoku : public wxApp
{
public:
    bool OnInit() override;
};
 
// This defines the equivalent of main() for the current platform.
wxIMPLEMENT_APP(Sudoku);
