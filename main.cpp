#include <iostream>
#include "Manager.h"
#include "png_toolkit.h"

int main( int argc, char *argv[] )
{
    // toolkit filter_name base_pic_name student_tool student_pic_name limitPix limitMSE
    // toolkit near test images!
    try
    {
        if (argc != 4)
            throw "Not enough arguments";

        char* fileConfig = argv[1];
        char* fileIn = argv[2];
        char* fileOut = argv[3];

        /*Manager manager;
        manager.launch(fileConfig, fileIn, fileOut);*/
        png_toolkit stoodTool;
        stoodTool.load(fileIn);
        stoodTool.save(fileOut);

    }
    catch (const char *str)
    {
        std::cout << "Error: " << str << std::endl;
        return 1;
    }

    return 0;
}
