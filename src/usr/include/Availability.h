/*
 * Copyright (c) 2007-2016 by Apple Inc.. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
 
#ifndef __AVAILABILITY__
#define __AVAILABILITY__
 /*     
    These macros are for use in OS header files. They enable function prototypes
    and Objective-C methods to be tagged with the OS version in which they
    were first available; and, if applicable, the OS version in which they 
    became deprecated.  
     
    The desktop Mac OS X and iOS each have different version numbers.
    The __OSX_AVAILABLE_STARTING() macro allows you to specify both the desktop
    and iOS version numbers.  For instance:
        __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0)
    means the function/method was first available on Mac OS X 10.2 on the desktop
    and first available in iOS 2.0 on the iPhone.
    
    If a function is available on one platform, but not the other a _NA (not
    applicable) parameter is used.  For instance:
            __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA)
    means that the function/method was first available on Mac OS X 10.3, and it
    currently not implemented on the iPhone.

    At some point, a function/method may be deprecated.  That means Apple
    recommends applications stop using the function, either because there is a 
    better replacement or the functionality is being phased out.  Deprecated
    functions/methods can be tagged with a __OSX_AVAILABLE_BUT_DEPRECATED()
    macro which specifies the OS version where the function became available
    as well as the OS version in which it became deprecated.  For instance:
        __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_NA,__IPHONE_NA)
    means that the function/method was introduced in Mac OS X 10.0, then
    became deprecated beginning in Mac OS X 10.5.  On iOS the function 
    has never been available.  
    
    For these macros to function properly, a program must specify the OS version range 
    it is targeting.  The min OS version is specified as an option to the compiler:
    -mmacosx-version-min=10.x when building for Mac OS X, and -miphoneos-version-min=y.z
    when building for the iPhone.  The upper bound for the OS version is rarely needed,
    but it can be set on the command line via: -D__MAC_OS_X_VERSION_MAX_ALLOWED=10x0 for
    Mac OS X and __IPHONE_OS_VERSION_MAX_ALLOWED = y0z00 for iOS.  
    
    Examples:

        A function available in Mac OS X 10.5 and later, but not on the phone:
        
            extern void mymacfunc() __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);


        An Objective-C method in Mac OS X 10.5 and later, but not on the phone:
        
            @interface MyClass : NSObject
            -(void) mymacmethod __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
            @end

        
        An enum available on the phone, but not available on Mac OS X:
        
            #if __IPHONE_OS_VERSION_MIN_REQUIRED
                enum { myEnum = 1 };
            #endif
           Note: this works when targeting the Mac OS X platform because 
           __IPHONE_OS_VERSION_MIN_REQUIRED is undefined which evaluates to zero. 
        

        An enum with values added in different iPhoneOS versions:
		
			enum {
			    myX  = 1,	// Usable on iPhoneOS 2.1 and later
			    myY  = 2,	// Usable on iPhoneOS 3.0 and later
			    myZ  = 3,	// Usable on iPhoneOS 3.0 and later
				...
		      Note: you do not want to use #if with enumeration values
			  when a client needs to see all values at compile time
			  and use runtime logic to only use the viable values.
			  

    It is also possible to use the *_VERSION_MIN_REQUIRED in source code to make one
    source base that can be compiled to target a range of OS versions.  It is best
    to not use the _MAC_* and __IPHONE_* macros for comparisons, but rather their values.
    That is because you might get compiled on an old OS that does not define a later
    OS version macro, and in the C preprocessor undefined values evaluate to zero
    in expresssions, which could cause the #if expression to evaluate in an unexpected
    way.
    
        #ifdef __MAC_OS_X_VERSION_MIN_REQUIRED
            // code only compiled when targeting Mac OS X and not iPhone
            // note use of 1050 instead of __MAC_10_5
            #if __MAC_OS_X_VERSION_MIN_REQUIRED < 1050
                // code in here might run on pre-Leopard OS
            #else
                // code here can assume Leopard or later
            #endif
        #endif


*/

#define __MAC_10_0            1000
#define __MAC_10_1            1010
#define __MAC_10_2            1020
#define __MAC_10_3            1030
#define __MAC_10_4            1040
#define __MAC_10_5            1050
#define __MAC_10_6            1060
#define __MAC_10_7            1070
#define __MAC_10_8            1080
#define __MAC_10_9            1090
#define __MAC_10_10         101000
#define __MAC_10_10_2       101002
#define __MAC_10_10_3       101003
#define __MAC_10_11         101100
#define __MAC_10_11_2       101102
#define __MAC_10_11_3       101103
#define __MAC_10_11_4       101104
#define __MAC_10_12         101200
#define __MAC_10_12_1       101201
#define __MAC_10_12_2       101202
#define __MAC_10_12_4       101204
/* __MAC_NA is not defined to a value but is uses as a token by macros to indicate that the API is unavailable */

#define __IPHONE_2_0      20000
#define __IPHONE_2_1      20100
#define __IPHONE_2_2      20200
#define __IPHONE_3_0      30000
#define __IPHONE_3_1      30100
#define __IPHONE_3_2      30200
#define __IPHONE_4_0      40000
#define __IPHONE_4_1      40100
#define __IPHONE_4_2      40200
#define __IPHONE_4_3      40300
#define __IPHONE_5_0      50000
#define __IPHONE_5_1      50100
#define __IPHONE_6_0      60000
#define __IPHONE_6_1      60100
#define __IPHONE_7_0      70000
#define __IPHONE_7_1      70100
#define __IPHONE_8_0      80000
#define __IPHONE_8_1      80100
#define __IPHONE_8_2      80200
#define __IPHONE_8_3      80300
#define __IPHONE_8_4      80400
#define __IPHONE_9_0      90000
#define __IPHONE_9_1      90100
#define __IPHONE_9_2      90200
#define __IPHONE_9_3      90300
#define __IPHONE_10_0    100000
#define __IPHONE_10_1    100100
#define __IPHONE_10_2    100200
#define __IPHONE_10_3    100300
/* __IPHONE_NA is not defined to a value but is uses as a token by macros to indicate that the API is unavailable */

#define __TVOS_9_0        90000
#define __TVOS_9_1        90100
#define __TVOS_9_2        90200
#define __TVOS_10_0      100000
#define __TVOS_10_0_1    100001
#define __TVOS_10_1      100100
#define __TVOS_10_2      100200

#define __WATCHOS_1_0     10000
#define __WATCHOS_2_0     20000
#define __WATCHOS_3_0     30000
#define __WATCHOS_3_1     30100
#define __WATCHOS_3_1_1   30101
#define __WATCHOS_3_2     30200

#include <AvailabilityInternal.h>

#ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
    #define __OSX_AVAILABLE_STARTING(_osx, _ios) __AVAILABILITY_INTERNAL##_ios
    #define __OSX_AVAILABLE_BUT_DEPRECATED(_osxIntro, _osxDep, _iosIntro, _iosDep) \
                                                    __AVAILABILITY_INTERNAL##_iosIntro##_DEP##_iosDep
    #define __OSX_AVAILABLE_BUT_DEPRECATED_MSG(_osxIntro, _osxDep, _iosIntro, _iosDep, _msg) \
                                                    __AVAILABILITY_INTERNAL##_iosIntro##_DEP##_iosDep##_MSG(_msg)

#elif defined(__MAC_OS_X_VERSION_MIN_REQUIRED)
    #define __OSX_AVAILABLE_STARTING(_osx, _ios) __AVAILABILITY_INTERNAL##_osx
    #define __OSX_AVAILABLE_BUT_DEPRECATED(_osxIntro, _osxDep, _iosIntro, _iosDep) \
                                                    __AVAILABILITY_INTERNAL##_osxIntro##_DEP##_osxDep
    #define __OSX_AVAILABLE_BUT_DEPRECATED_MSG(_osxIntro, _osxDep, _iosIntro, _iosDep, _msg) \
                                                    __AVAILABILITY_INTERNAL##_osxIntro##_DEP##_osxDep##_MSG(_msg)

#else
    #define __OSX_AVAILABLE_STARTING(_osx, _ios)
    #define __OSX_AVAILABLE_BUT_DEPRECATED(_osxIntro, _osxDep, _iosIntro, _iosDep)
    #define __OSX_AVAILABLE_BUT_DEPRECATED_MSG(_osxIntro, _osxDep, _iosIntro, _iosDep, _msg)
#endif


#if defined(__has_feature)
  #if __has_feature(attribute_availability_with_message)
    #define __OS_AVAILABILITY(_target, _availability)            __attribute__((availability(_target,_availability)))
    #define __OS_AVAILABILITY_MSG(_target, _availability, _msg)  __attribute__((availability(_target,_availability,message=_msg)))
  #elif __has_feature(attribute_availability)
    #define __OS_AVAILABILITY(_target, _availability)            __attribute__((availability(_target,_availability)))
    #define __OS_AVAILABILITY_MSG(_target, _availability, _msg)  __attribute__((availability(_target,_availability)))
  #else
    #define __OS_AVAILABILITY(_target, _availability)
    #define __OS_AVAILABILITY_MSG(_target, _availability, _msg)
  #endif
#else
    #define __OS_AVAILABILITY(_target, _availability)
    #define __OS_AVAILABILITY_MSG(_target, _availability, _msg)
#endif


/* for use to document app extension usage */
#if defined(__has_feature)
  #if __has_feature(attribute_availability_app_extension)
    #define __OSX_EXTENSION_UNAVAILABLE(_msg)  __OS_AVAILABILITY_MSG(macosx_app_extension,unavailable,_msg)
    #define __IOS_EXTENSION_UNAVAILABLE(_msg)  __OS_AVAILABILITY_MSG(ios_app_extension,unavailable,_msg)
  #else
    #define __OSX_EXTENSION_UNAVAILABLE(_msg)
    #define __IOS_EXTENSION_UNAVAILABLE(_msg)
  #endif
#else
    #define __OSX_EXTENSION_UNAVAILABLE(_msg)
    #define __IOS_EXTENSION_UNAVAILABLE(_msg)
#endif

#define __OS_EXTENSION_UNAVAILABLE(_msg)  __OSX_EXTENSION_UNAVAILABLE(_msg) __IOS_EXTENSION_UNAVAILABLE(_msg)



/* for use marking APIs available info for Mac OSX */
#if defined(__has_attribute)
  #if __has_attribute(availability)
    #define __OSX_UNAVAILABLE                    __OS_AVAILABILITY(macosx,unavailable)
    #define __OSX_AVAILABLE(_vers)               __OS_AVAILABILITY(macosx,introduced=_vers)
    #define __OSX_DEPRECATED(_start, _dep, _msg) __OSX_AVAILABLE(_start) __OS_AVAILABILITY_MSG(macosx,deprecated=_dep,_msg)
  #endif
#endif

#ifndef __OSX_UNAVAILABLE
  #define __OSX_UNAVAILABLE
#endif

#ifndef __OSX_AVAILABLE
  #define __OSX_AVAILABLE(_vers)
#endif

#ifndef __OSX_DEPRECATED
  #define __OSX_DEPRECATED(_start, _dep, _msg)
#endif


/* for use marking APIs available info for iOS */
#if defined(__has_attribute)
  #if __has_attribute(availability)
    #define __IOS_UNAVAILABLE                    __OS_AVAILABILITY(ios,unavailable)
    #define __IOS_PROHIBITED                     __OS_AVAILABILITY(ios,unavailable)
    #define __IOS_AVAILABLE(_vers)               __OS_AVAILABILITY(ios,introduced=_vers)
    #define __IOS_DEPRECATED(_start, _dep, _msg) __IOS_AVAILABLE(_start) __OS_AVAILABILITY_MSG(ios,deprecated=_dep,_msg)
  #endif
#endif

#ifndef __IOS_UNAVAILABLE
  #define __IOS_UNAVAILABLE
#endif

#ifndef __IOS_PROHIBITED
  #define __IOS_PROHIBITED
#endif

#ifndef __IOS_AVAILABLE
  #define __IOS_AVAILABLE(_vers)
#endif

#ifndef __IOS_DEPRECATED
  #define __IOS_DEPRECATED(_start, _dep, _msg)
#endif


/* for use marking APIs available info for tvOS */
#if defined(__has_feature)
  #if __has_feature(attribute_availability_tvos)
    #define __TVOS_UNAVAILABLE                    __OS_AVAILABILITY(tvos,unavailable)
    #define __TVOS_PROHIBITED                     __OS_AVAILABILITY(tvos,unavailable)
    #define __TVOS_AVAILABLE(_vers)               __OS_AVAILABILITY(tvos,introduced=_vers)
    #define __TVOS_DEPRECATED(_start, _dep, _msg) __TVOS_AVAILABLE(_start) __OS_AVAILABILITY_MSG(tvos,deprecated=_dep,_msg)
  #endif
#endif

#ifndef __TVOS_UNAVAILABLE
  #define __TVOS_UNAVAILABLE
#endif

#ifndef __TVOS_PROHIBITED
  #define __TVOS_PROHIBITED
#endif

#ifndef __TVOS_AVAILABLE
  #define __TVOS_AVAILABLE(_vers)
#endif

#ifndef __TVOS_DEPRECATED
  #define __TVOS_DEPRECATED(_start, _dep, _msg)
#endif


/* for use marking APIs available info for Watch OS */
#if defined(__has_feature)
  #if __has_feature(attribute_availability_watchos)
    #define __WATCHOS_UNAVAILABLE                    __OS_AVAILABILITY(watchos,unavailable)
    #define __WATCHOS_PROHIBITED                     __OS_AVAILABILITY(watchos,unavailable)
    #define __WATCHOS_AVAILABLE(_vers)               __OS_AVAILABILITY(watchos,introduced=_vers)
    #define __WATCHOS_DEPRECATED(_start, _dep, _msg) __WATCHOS_AVAILABLE(_start) __OS_AVAILABILITY_MSG(watchos,deprecated=_dep,_msg)
  #endif
#endif

#ifndef __WATCHOS_UNAVAILABLE
  #define __WATCHOS_UNAVAILABLE
#endif

#ifndef __WATCHOS_PROHIBITED
  #define __WATCHOS_PROHIBITED
#endif

#ifndef __WATCHOS_AVAILABLE
  #define __WATCHOS_AVAILABLE(_vers)
#endif

#ifndef __WATCHOS_DEPRECATED
  #define __WATCHOS_DEPRECATED(_start, _dep, _msg)
#endif


/* for use marking APIs unavailable for swift */
#if defined(__has_feature)
  #if __has_feature(attribute_availability_swift)
    #define __SWIFT_UNAVAILABLE                   __OS_AVAILABILITY(swift,unavailable)
    #define __SWIFT_UNAVAILABLE_MSG(_msg)         __OS_AVAILABILITY_MSG(swift,unavailable,_msg)
  #endif
#endif

#ifndef __SWIFT_UNAVAILABLE
  #define __SWIFT_UNAVAILABLE
#endif

#ifndef __SWIFT_UNAVAILABLE_MSG
  #define __SWIFT_UNAVAILABLE_MSG(_msg)
#endif

#if __has_include(<AvailabilityProhibitedInternal.h>)
  #include <AvailabilityProhibitedInternal.h>
#endif

/*
 Macros for defining which versions/platform a given symbol can be used.
 
 @see http://clang.llvm.org/docs/AttributeReference.html#availability
 */

/*
 * API Introductions
 *
 * Use to specify the release that a particular API became available.
 *
 * Platform names:
 *   macos, ios, tvos, watchos
 *
 * Examples:
 *    __API_AVAILABLE(macos(10.10))
 *    __API_AVAILABLE(macos(10.9), ios(10.0))
 *    __API_AVAILABLE(macos(10.4), ios(8.0), watchos(2.0), tvos(10.0))
 */
#define __API_AVAILABLE(...)


/*
 * API Deprecations
 *
 * Use to specify the release that a particular API became unavailable.
 *
 * Platform names:
 *   macos, ios, tvos, watchos
 *
 * Examples:
 *
 *    __API_DEPRECATED("No longer supported", macos(10.4, 10.8))
 *    __API_DEPRECATED("No longer supported", macos(10.4, 10.8), ios(2.0, 3.0), watchos(2.0, 3.0), tvos(9.0, 10.0))
 *
 *    __API_DEPRECATED_WITH_REPLACEMENT("-setName:", tvos(10.0, 10.4), ios(9.0, 10.0))
 *    __API_DEPRECATED_WITH_REPLACEMENT("SomeClassName", macos(10.4, 10.6), watchos(2.0, 3.0))
 */
#define __API_DEPRECATED(...) __API_DEPRECATED_MSG_GET_MACRO(__VA_ARGS__,__API_DEPRECATED_MSG5,__API_DEPRECATED_MSG4,__API_DEPRECATED_MSG3,__API_DEPRECATED_MSG2,__API_DEPRECATED_MSG1)(__VA_ARGS__)
#define __API_DEPRECATED_WITH_REPLACEMENT(...) __API_DEPRECATED_REP_GET_MACRO(__VA_ARGS__,__API_DEPRECATED_REP5,__API_DEPRECATED_REP4,__API_DEPRECATED_REP3,__API_DEPRECATED_REP2,__API_DEPRECATED_REP1)(__VA_ARGS__)

/*
 * API Unavailability
 * Use to specify that an API is unavailable for a particular platform.
 *
 * Example:
 *    __API_UNAVAILABLE(macos)
 *    __API_UNAVAILABLE(watchos, tvos)
 */
#define __API_UNAVAILABLE(...)

#endif /* __AVAILABILITY__ */
