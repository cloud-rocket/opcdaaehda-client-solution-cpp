#
# Copyright (c) 2011-2018 Technosoftware GmbH. All rights reserved
# Web: https://technosoftware.com 
# 
# Purpose: 
#
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#

# declare the targets
set(  TECHNOSOFTWARE_CLIENT_EXAMPLES
      DaConsole
      DaBrowserConsole
      HdaConsole
   )

foreach(TECHNOSOFTWARE_CLIENT_EXAMPLE ${TECHNOSOFTWARE_CLIENT_EXAMPLES})

    # Add an executable for the example
    add_executable(${TECHNOSOFTWARE_CLIENT_EXAMPLE} ${TECHNOSOFTWARE_CLIENT_EXAMPLE}.cpp)
    
    # Link the executable.
    if(WIN32)
        target_link_libraries(
							  ${TECHNOSOFTWARE_CLIENT_EXAMPLE} 
                              TechnosoftwareClient TechnosoftwareBase TechnosoftwareCore TechnosoftwareDaAeHdaClient
							  oleaut32 ole32 Version ws2_32 rpcrt4 crypt32
							 )
    else(WIN32)
        target_link_libraries(
							  ${TECHNOSOFTWARE_CLIENT_EXAMPLE} 
                              TechnosoftwareClient TechnosoftwareBase TechnosoftwareCore TechnosoftwareDaAeHdaClient
                              dl rt pthread                   
							 )
    endif(WIN32)
    
    # Set the output directory for the C++ test to the previously defined output directory
    set_target_properties(${TECHNOSOFTWARE_CLIENT_EXAMPLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY         "${EXAMPLES_TECHNOSOFTWARE_BIN_DIR}")
    set_target_properties(${TECHNOSOFTWARE_CLIENT_EXAMPLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${EXAMPLES_TECHNOSOFTWARE_BIN_DIR}")
    set_target_properties(${TECHNOSOFTWARE_CLIENT_EXAMPLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${EXAMPLES_TECHNOSOFTWARE_BIN_DIR}")
    
endforeach(TECHNOSOFTWARE_CLIENT_EXAMPLE)
