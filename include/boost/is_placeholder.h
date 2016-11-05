/**
 * @file is_placeholder.h
 * @brief
 * @version 1.0
 * @date 11/02/2016 10:11:30 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#ifndef  __IS_PLACEHOLDER_H__
#define  __IS_PLACEHOLDER_H__

namespace myboost {

template <typename T>
struct is_placeholder {
    enum {value = 0};
};

}
#endif

