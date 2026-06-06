/**
 * @file hello.h
 * @author tinysec
 * @brief Public hello API.
 * @version 0.0.1
 */
#ifndef HELLO_HEADER_FILE
#define HELLO_HEADER_FILE

#if defined(_WIN32) && defined(HELLO_SHARED) && !defined(HELLO_BUILDING_LIBRARY)
    #define HELLO_API __declspec(dllimport)
#else
    #define HELLO_API
#endif

#ifdef __cplusplus
extern "C"
{
#endif


/*!
 * @brief for test
 * @param [in] a
 * @param [in] b
 * @return
 */
HELLO_API int foobar(int a, int b);


#ifdef __cplusplus
}
#endif

#endif /* HELLO_HEADER_FILE */
