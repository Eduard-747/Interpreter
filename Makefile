CONTROLER	= ./src/typeControler.cpp
UTIL		= ./src/Util.cpp
COLCUL		= ./src/Calculate.cpp
ENGIN		= ./src/Engin.cpp 
TYPE		= ./src/Type.cpp 
MAIN_JS		= ./src/jsmain.cpp 
MAIN_NODE	= ./src/main.cpp 
JS 		= ./bin/JS 
GET_NAME 	= -o 
NODE		= ./bin/NODE 
FOR_GDB		= -g
CC		= g++ -std=c++17

all :
	sudo ${CC}  ${MAIN_NODE} ${CONTROLER} ${UTIL} ${COLCUL} ${ENGIN} ${TYPE} ${GET_NAME} ${JS} ${FOR_GDB}
	sudo ${CC}  ${MAIN_JS} ${CONTROLER} ${UTIL} ${COLCUL} ${ENGIN} ${TYPE} ${GET_NAME} ${NODE} ${FOR_GDB}
