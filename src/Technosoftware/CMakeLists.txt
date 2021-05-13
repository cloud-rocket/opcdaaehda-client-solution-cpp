#
# Copyright (c) 2011-2018 Technosoftware GmbH. All rights reserved
# Web: https://technosoftware.com 
# 
# Purpose: 
#
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#

add_subdirectory(${PROJECT_SOURCE_DIR}/Technosoftware/Base)
add_subdirectory(${PROJECT_SOURCE_DIR}/Technosoftware/Core)
add_subdirectory(${PROJECT_SOURCE_DIR}/Technosoftware/Client)
if (WIN32)
 	add_subdirectory(${PROJECT_SOURCE_DIR}/Technosoftware/DaAeHdaClient)
endif (WIN32)