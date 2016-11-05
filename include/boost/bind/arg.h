/**
 * @file arg.h
 * @brief
 * @version 1.0
 * @date 11/02/2016 07:10:42 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#ifndef  __ARG_H__
#define  __ARG_H__

#include "boost/is_placeholder.h"

namespace myboost {

template <int I>
struct arg {
    /**
     * @brief 
     */
    arg() {}
     
    /**
     * @brief 
     * @param[in]
     */
    template<typename T> arg(const T &) {
        typedef char T_must_be_placeholder[I == is_placeholder<T>::value ? 1 : -1];
    }
};

/**
 * @brief 
 * @param[in]
 * @param[in]
 * @return
 */
template <int T> bool operator == (const arg<T> &, const arg<T> &) {
    return true;
} 

template <int I>
struct is_placeholder<arg<I> > {
    enum {value = I};
};

template <int I>
struct is_placeholder<arg<I> (*)() > {
    enum {value = I};
};

}
#endif

