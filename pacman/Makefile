CXX = g++
CXX_FLAGS = -Wall -pedantic -Wextra -std=c++14
DIR = build
LOGIN = kousaja1

compile: $(DIR)/CApplication.o $(DIR)/CCharacter.o $(DIR)/CConfig.o $(DIR)/CCoord.o $(DIR)/CGame.o $(DIR)/CGameState.o $(DIR)/CInterface.o $(DIR)/CMap.o $(DIR)/CMode.o $(DIR)/CObject.o $(DIR)/CObjectCanal.o $(DIR)/CObjectCherry.o $(DIR)/CObjectDiamond.o $(DIR)/CObjectGold.o $(DIR)/CPlayer.o $(DIR)/CRobot.o $(DIR)/CRobotA.o $(DIR)/CRobotB.o $(DIR)/CRobotX.o $(DIR)/SRandom.o $(DIR)/main.o
	$(CXX) $(CXX_FLAGS) $^ -o $(LOGIN)

$(DIR)/%.o: src/%.cpp
	mkdir -p $(DIR)
	$(CXX) $(CXX_FLAGS) $< -c -o $@

run:
	./$(LOGIN)

.PHONY: clean doc all testmaps testconfigs
clean:
		rm -rf $(DIR)/ 2>/dev/null
		rm $(LOGIN) 2>/dev/null
		rm -rf doc/ 2>/dev/null
doc:
	rm -rf doc/ 2>/dev/null
	doxygen

all: compile doc

testmaps: compile
	./examples/tests/testmaps.sh
testconfigs: compile
	./examples/tests/testconfigs.sh

# Dependencies - generated by g++ -MM
$(DIR)/CApplication.o: src/CApplication.cpp src/CApplication.h src/CInterface.h \
 src/EDirection.h src/CMap.h src/CObject.h src/CGameState.h src/CPlayer.h \
 src/CCharacter.h src/CCoord.h src/CMode.h src/CConfig.h \
 src/EDifficulty.h src/ECharacter.h src/ECommand.h src/EColors.h \
 src/CGame.h src/CRobot.h src/SRandom.h
$(DIR)/CCharacter.o: src/CCharacter.cpp src/CCharacter.h src/CCoord.h \
 src/EDirection.h
$(DIR)/CConfig.o: src/CConfig.cpp src/CConfig.h src/EDifficulty.h
$(DIR)/CCoord.o: src/CCoord.cpp src/CCoord.h src/EDirection.h
$(DIR)/CGame.o: src/CGame.cpp src/CGame.h src/CMap.h src/CObject.h \
 src/CGameState.h src/CPlayer.h src/CCharacter.h src/CCoord.h \
 src/EDirection.h src/CMode.h src/CConfig.h src/EDifficulty.h \
 src/ECharacter.h src/CInterface.h src/ECommand.h src/EColors.h \
 src/CRobot.h src/SRandom.h src/CRobotA.h src/CRobotB.h src/CRobotX.h \
 src/game_exit.h
$(DIR)/CGameState.o: src/CGameState.cpp src/CGameState.h src/CPlayer.h \
 src/CCharacter.h src/CCoord.h src/EDirection.h src/CMode.h src/CConfig.h \
 src/EDifficulty.h
$(DIR)/CInterface.o: src/CInterface.cpp src/CInterface.h src/EDirection.h \
 src/CMap.h src/CObject.h src/CGameState.h src/CPlayer.h src/CCharacter.h \
 src/CCoord.h src/CMode.h src/CConfig.h src/EDifficulty.h \
 src/ECharacter.h src/ECommand.h src/EColors.h src/game_exit.h
$(DIR)/CMap.o: src/CMap.cpp src/CMap.h src/CObject.h src/CGameState.h \
 src/CPlayer.h src/CCharacter.h src/CCoord.h src/EDirection.h src/CMode.h \
 src/CConfig.h src/EDifficulty.h src/ECharacter.h src/CObjectCherry.h \
 src/CObjectCanal.h src/CObjectGold.h src/CObjectDiamond.h src/SRandom.h
$(DIR)/CMode.o: src/CMode.cpp src/CMode.h src/CConfig.h src/EDifficulty.h
$(DIR)/CObject.o: src/CObject.cpp src/CObject.h src/CGameState.h src/CPlayer.h \
 src/CCharacter.h src/CCoord.h src/EDirection.h src/CMode.h src/CConfig.h \
 src/EDifficulty.h
$(DIR)/CObjectCanal.o: src/CObjectCanal.cpp src/CObjectCanal.h src/CObject.h \
 src/CGameState.h src/CPlayer.h src/CCharacter.h src/CCoord.h \
 src/EDirection.h src/CMode.h src/CConfig.h src/EDifficulty.h
$(DIR)/CObjectCherry.o: src/CObjectCherry.cpp src/CObjectCherry.h src/CObject.h \
 src/CGameState.h src/CPlayer.h src/CCharacter.h src/CCoord.h \
 src/EDirection.h src/CMode.h src/CConfig.h src/EDifficulty.h
$(DIR)/CObjectDiamond.o: src/CObjectDiamond.cpp src/CObjectDiamond.h \
 src/CObject.h src/CGameState.h src/CPlayer.h src/CCharacter.h \
 src/CCoord.h src/EDirection.h src/CMode.h src/CConfig.h \
 src/EDifficulty.h
$(DIR)/CObjectGold.o: src/CObjectGold.cpp src/CObjectGold.h src/CObject.h \
 src/CGameState.h src/CPlayer.h src/CCharacter.h src/CCoord.h \
 src/EDirection.h src/CMode.h src/CConfig.h src/EDifficulty.h
$(DIR)/CPlayer.o: src/CPlayer.cpp src/CPlayer.h src/CCharacter.h src/CCoord.h \
 src/EDirection.h
$(DIR)/CRobot.o: src/CRobot.cpp src/CRobot.h src/CCharacter.h src/CCoord.h \
 src/EDirection.h src/CMode.h src/CConfig.h src/EDifficulty.h src/CMap.h \
 src/CObject.h src/CGameState.h src/CPlayer.h src/ECharacter.h \
 src/SRandom.h
$(DIR)/CRobotA.o: src/CRobotA.cpp src/CRobotA.h src/CRobot.h src/CCharacter.h \
 src/CCoord.h src/EDirection.h src/CMode.h src/CConfig.h \
 src/EDifficulty.h src/CMap.h src/CObject.h src/CGameState.h \
 src/CPlayer.h src/ECharacter.h src/SRandom.h
$(DIR)/CRobotB.o: src/CRobotB.cpp src/CRobotB.h src/CRobot.h src/CCharacter.h \
 src/CCoord.h src/EDirection.h src/CMode.h src/CConfig.h \
 src/EDifficulty.h src/CMap.h src/CObject.h src/CGameState.h \
 src/CPlayer.h src/ECharacter.h src/SRandom.h
$(DIR)/CRobotX.o: src/CRobotX.cpp src/CRobotX.h src/CRobot.h src/CCharacter.h \
 src/CCoord.h src/EDirection.h src/CMode.h src/CConfig.h \
 src/EDifficulty.h src/CMap.h src/CObject.h src/CGameState.h \
 src/CPlayer.h src/ECharacter.h src/SRandom.h
$(DIR)/SRandom.o: src/SRandom.cpp src/SRandom.h src/EDirection.h src/CCoord.h
$(DIR)/main.o: src/main.cpp src/CInterface.h src/EDirection.h src/CMap.h \
 src/CObject.h src/CGameState.h src/CPlayer.h src/CCharacter.h \
 src/CCoord.h src/CMode.h src/CConfig.h src/EDifficulty.h \
 src/ECharacter.h src/ECommand.h src/EColors.h src/CApplication.h \
 src/CGame.h src/CRobot.h src/SRandom.h