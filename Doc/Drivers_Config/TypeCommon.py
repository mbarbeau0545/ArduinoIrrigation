"""
#  @file        TypeCommon.py
#  @brief       Template_BriefDescription.
#  @details     TemplateDetailsDescription.\n
#
#  @author      AUDMBA
#  @date        jj/mm/yyyy
#  @version     1.0
"""
#------------------------------------------------------------------------------
#                                       IMPORT
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#                                       DEFINE
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#                                       CLASS
#------------------------------------------------------------------------------
class t_eReturnCode():
        # Errors
        ERROR_POINTOR_NULL = -16,                    """At least one of the pointor is NULL                          """
        ERROR_ALLOC_FAILED = -15,                    """ At least one of alloc memory failed                         """
        ERROR_PARAM_INVALID = -14,                   """ At least one of the parameters is not in the allowed range. """
        ERROR_PARAM_NOT_SUPPORTED = -13,             """ At lest one of the parameters is not supported.             """
        ERROR_WRONG_STATE = -12,                     """ The function cannot succeed in the current state.           """
        ERROR_MODULE_NOT_INITIALIZED = -11,          """ The module must be initialized before calling the function. """
        ERROR_MISSING_CONFIG = -10,                  """ Some configuration is missing.                              """
        ERROR_WRONG_CONFIG = -9,                     """ The configuration is not consistent.                        """
        ERROR_UNDEFINED = -8,                        """ An undefined error has occurred.                            """
        ERROR_NOT_SUPPORTED = -7,                    """ The function is not supported.                              """ 
        ERROR_BUSY = -6,                             """ Process busy, task not accepted.                            """
        ERROR_TIMEOUT = -5,                          """ The operation timed out.                                    """
        ERROR_NOT_ALLOWED = -4,                      """ Not allowed to perform the requested operation.             """
        ERROR_WRONG_RESULT = -3,                     """ The operation has succeeded, but the result is incorrect.   """
        ERROR_LIMIT_REACHED = -2,                    """ The operation cannot be done because a limit has been reached. """
        ERROR_NOT_ENOUGH_MEMORY = -1,                """ The operation cannot be done because there is not enough memory. """

        # OK
        OK = 0,                                      """ Process finished successfully. """

        # Warnings
        WARNING_NO_OPERATION = 1,                    """ No error occurred, but there was no operation to execute. """
        WARNING_BUSY = 2,                            """ The operation is accepted, but the process was already busy"""
        """ which means the previous operation has been stopped. """
        WARNING_ALREADY_CONFIGURED = 3,              """ The operation is accepted, but the user must be aware that """
        """ a previous configuration has been lost. """
        WARNING_WRONG_CONFIG = 4,                    """ The configuration is not consistent. """
        WARNING_MISSING_CONFIG = 5,                  """ Some configuration is missing. """
        WARNING_INIT_PROBLEM = 6,                    """ No initialization done, process performed as default mode. """
        WARNING_PENDING = 7,                         """ Operation accepted and started, but the result is not immediate. """
        WARNING_NOT_ALLOWED = 8,                     """ Not allowed to perform the requested operation. """
        WARNING_LIMIT_REACHED = 9,                   """ The operation cannot be done because a limit has been reached. """
        WARNING_WRONG_RESULT = 10,                    """ The operation has succeeded, but the result is incorrect."""
#------------------------------------------------------------------------------
#                              FUNCTION DECLARATION
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#                             FUNCTION IMPLMENTATION
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#			                MAIN
#------------------------------------------------------------------------------


#------------------------------------------------------------------------------
#		                    END OF FILE
#------------------------------------------------------------------------------
#--------------------------
# Function_name
#--------------------------

"""
    @brief
    @details




    @params[in]
    @params[out]
    @retval
"""

