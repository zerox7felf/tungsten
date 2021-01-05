#pragma once
// Anonymous functions using GCC's nested functions
// ...this does mean that the code only compiles with gcc.
// TODO: remove if unused
#define val(...) __VA_ARGS__
#define L(_func_ret_type, _func_args, _func_body)\
    ({\
        _func_ret_type _func_name _func_args\
        _func_body\
        &_func_name;\
    })

