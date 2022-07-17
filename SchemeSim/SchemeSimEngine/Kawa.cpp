#include <iostream>
#include "SymbolFunction.h"
#include "REPL.h"

using namespace std;


// Start Kawa
int main() {
    cout << "#******************************************#" << endl;
    cout << "            Kawa Interpreter" << endl;	
    cout << "<<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>>" << endl;
    cout << "  Enter \"(exit)\" to EXIT from KAWA" << endl;
    cout << "  Enter \"(file)\" to REPL from File" << endl;
    cout << "  Enter \"(df)\" to REPL from Default File" << endl;
    cout << "<<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>>" << endl << endl;

    SymbolFunction symFn = SymbolFunction();
    REPL::populate_s_fn(&symFn);

    REPL::defineBaseFuncs(&symFn);

    REPL::evalFromTerminal(symFn);

    return 0;
}
