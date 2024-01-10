//#include "windows.h"
#include "schedulecreator.h"
#include "mainio.h"
#include <iostream>

#pragma execution_character_set( "utf-8" )

int main()
{
    MainIO procedure ("1. Generuj plan\n2. Zapisz plan dla pracownika\n3. Zapisz plan dla zarzadu\n4. Wylacz system\nWprowadz zadanie: ");
    while(true){
        procedure.printPrefix();
        string tmp = procedure.getCommand();
        if(tmp == "1"){
            // GeneratePlan
        }
        else if(tmp == "2"){
            // FileWrite() GeneratePlan for worker
        }
        else if(tmp == "3"){
            // FileWrite() GeneratePlan for all
        }
        else if(tmp == "4"){
            break;
        }
    }
    return 0;
}
