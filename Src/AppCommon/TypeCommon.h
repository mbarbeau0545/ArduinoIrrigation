/*****************************************************************************
 * @file        TypeCommon.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
#ifndef TYPECOMMON_H_INCLUDED
#define TYPECOMMON_H_INCLUDED
    typedef enum

    {

        // Errors
        RC_ERROR_COPY_FAILED = -16,                      /**< The copy between two variable failed*/
        RC_ERROR_PTR_NULL = -15,                         /**< At least one of the pointer is null*/
        RC_ERROR_PARAM_INVALID = -14,                   /**< At least one of the parameters is not in the allowed range. */
        RC_ERROR_PARAM_NOT_SUPPORTED = -13,             /**< At lest one of the parameters is not supported. */
        RC_ERROR_WRONG_STATE = -12,                     /**< The function cannot succeed in the current state. */
        RC_ERROR_MODULE_NOT_INITIALIZED = -11,          /**< The module must be initialized before calling the function. */
        RC_ERROR_MISSING_CONFIG = -10,                  /**< Some configuration is missing. */
        RC_ERROR_WRONG_CONFIG = -9,                     /**< The configuration is not consistent. */
        RC_ERROR_UNDEFINED = -8,                        /**< An undefined error has occurred. */
        RC_ERROR_NOT_SUPPORTED = -7,                    /**< The function is not supported. */ 
        RC_ERROR_BUSY = -6,                             /**< Process busy, task not accepted. */
        RC_ERROR_TIMEOUT = -5,                          /**< The operation timed out. */
        RC_ERROR_NOT_ALLOWED = -4,                      /**< Not allowed to perform the requested operation. */
        RC_ERROR_WRONG_RESULT = -3,                     /**< The operation has succeeded, but the result is incorrect. */
        RC_ERROR_LIMIT_REACHED = -2,                    /**< The operation cannot be done because a limit has been reached. */
        RC_ERROR_NOT_ENOUGH_MEMORY = -1,                /**< The operation cannot be done because there is not enough memory. */

        // OK
        RC_OK = 0,                                      /**< Process finished successfully. */

        // Warnings
        RC_WARNING_NO_OPERATION = 1,                    /**< No error occurred, but there was no operation to execute. */
        RC_WARNING_BUSY = 2,                            /**< The operation is accepted, but the process was already busy, */
                                                        /**< which means the previous operation has been stopped. */
        RC_WARNING_ALREADY_CONFIGURED = 3,              /**< The operation is accepted, but the user must be aware that */
                                                        /**< a previous configuration has been lost. */
        RC_WARNING_WRONG_CONFIG = 4,                     /**< The configuration is not consistent. */
        RC_WARNING_MISSING_CONFIG = 5,                  /**< Some configuration is missing. */
        RC_WARNING_INIT_PROBLEM = 6,                    /**< No initialization done, process performed as default mode. */
        RC_WARNING_PENDING = 7,                         /**< Operation accepted and started, but the result is not immediate. */
        RC_WARNING_NOT_ALLOWED = 8,                     /**< Not allowed to perform the requested operation. */
        RC_WARNING_LIMIT_REACHED = 9,                   /**< The operation cannot be done because a limit has been reached. */
        RC_WARNING_WRONG_RESULT = 10                    /**< The operation has succeeded, but the result is incorrect. */

    } t_eReturnCode;

typedef unsigned char t_bool;               /**< Boolean type. */
typedef unsigned char t_uint8;              /**< Unsigned 8-bit type. */
typedef signed char t_sint8;                /**< Signed 8-bit type. */
typedef unsigned short t_uint16;            /**< Unsigned 16-bit type. */
typedef signed short t_sint16;              /**< Signed 16-bit type. */
typedef unsigned long t_uint32;             /**< Unsigned 32-bit type. */
typedef signed long t_sint32;               /**< Signed 32-bit type. */
typedef float t_float32;                    /**< 32-bit float type. */
//typedef unsigned long long t_uint64;        /**< Unsigned 64-bit type. */
//typedef signed long long t_sint64;          /**< Signed 64-bit type. */
typedef char t_char;
#endif //TYPECOMMON_H_INCLUDED