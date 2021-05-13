#
# Copyright (c) 2011-2018 Technosoftware GmbH. All rights reserved
# Web: https://technosoftware.com 
# 
# Purpose: 
#
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#

# Set the Technosoftware compiler flags
setTechnosoftwareDaAeHdaClientCompilerFlags()

# Add all source files in this directory.
aux_source_directory(.                      SOURCES_TECHNOSOFTWARE_TechnosoftwareDaAeHdaClient)
aux_source_directory(./Ae              		SOURCES_TECHNOSOFTWARE_TechnosoftwareDaAeHdaClient_AE)
aux_source_directory(./Da              		SOURCES_TECHNOSOFTWARE_TechnosoftwareDaAeHdaClient_DA)
aux_source_directory(./Hda             		SOURCES_TECHNOSOFTWARE_TechnosoftwareDaAeHdaClient_HDA)
aux_source_directory(./system         		SOURCES_TECHNOSOFTWARE_TechnosoftwareDaAeHdaClient_SYSTEM)
aux_source_directory(./License         		SOURCES_TECHNOSOFTWARE_TechnosoftwareDaAeHdaClient_LICENSE)

# Include the client headers from the Core
include_directories(".")
include_directories("${PROJECT_SOURCE_DIR}/../include/DaAeHdaClient")
include_directories("system")
include_directories("License")

link_directories("${PROJECT_SOURCE_DIR}/../lib/Win32")

# Create a shared library consisting of the previously added source files.
add_library(TechnosoftwareDaAeHdaClient SHARED ${SOURCES_TECHNOSOFTWARE_TechnosoftwareDaAeHdaClient}
                             ${SOURCES_TECHNOSOFTWARE_TechnosoftwareDaAeHdaClient_AE}
                             ${SOURCES_TECHNOSOFTWARE_TechnosoftwareDaAeHdaClient_DA}
                             ${SOURCES_TECHNOSOFTWARE_TechnosoftwareDaAeHdaClient_HDA}
                             ${SOURCES_TECHNOSOFTWARE_TechnosoftwareDaAeHdaClient_SYSTEM}
                             ${SOURCES_TECHNOSOFTWARE_TechnosoftwareDaAeHdaClient_LICENSE})

# Link the libraries.
if (WIN32)
    target_link_libraries(
						  TechnosoftwareDaAeHdaClient TechnosoftwareBase
						  oleaut32 ole32 Version ws2_32 rpcrt4 crypt32 PLUSNative
                         )
else (WIN32)
    target_link_libraries(
						  TechnosoftwareDaAeHdaClient TechnosoftwareBase
                          dl rt pthread PLUSNative
                         )
endif (WIN32)

install(TARGETS TechnosoftwareDaAeHdaClient TechnosoftwareDaAeHdaClient TechnosoftwareDaAeHdaClient
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/../bin
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/../bin
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/../lib)
