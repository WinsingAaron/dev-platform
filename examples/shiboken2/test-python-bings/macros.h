//
// Created by Jsiyong on 2020-06-07.
//

#ifndef MACROS_H
#define MACROS_H

#if defined _WIN32 || defined __CYGWIN__
    // Export symbols when creating .dll and .lib, and import them when using .lib.
    #if BINDINGS_BUILD
        #define BINDINGS_API __declspec(dllexport)
    #else
        #define BINDINGS_API __declspec(dllimport)
    #endif
    // Disable warnings about exporting STL types being a bad idea. Don't use this in production
    // code.
    #pragma warning( disable : 4251 )
#else
     #define BINDINGS_API
#endif

#endif // MACROS_H
