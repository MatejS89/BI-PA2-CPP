CXXFLAGS = -Wall -pedantic -std=c++17

LDLIBS = -lSDL2 -lSDL2_image -lxml2
INCLUDES = -I/usr/include/libxml2 -I/usr/include/SDL2
HEADERS = $(wildcard src/*.h src/*.hpp)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)

.PHONY: all
all: compile doc

.PHONY: run
run: compile
	./sedlam53 $(MODE)

.PHONY: compile
compile: sedlam53

sedlam53: build/main
	cp $< $@

build/main: $(OBJECTS)
	mkdir -p $(@D)
	g++ $^ -o $@ $(LDLIBS)

build/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $(INCLUDES) $< -c -o $@

.PHONY: doc
doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -rf sedlam53 build/ doc/ Makefile.d

CCamera.o: src/CCamera.cpp src/CCamera.h src/CVector2D.h src/CGame.h \
 src/CTextureManager.h src/CInputHandler.h src/SMouseState.h src/CMap.h \
 src/CMapLayer.h src/json.hpp src/CGameLayer.h
CCollider.o: src/CCollider.cpp src/CCollider.h
CCollisionHandler.o: src/CCollisionHandler.cpp src/CCollisionHandler.h \
 src/CTileLayer.h src/CMapLayer.h src/json.hpp src/CTimer.h \
 src/STileSet.h src/EBlockType.h src/CEntity.h src/CGameObject.h \
 src/CGame.h src/CTextureManager.h src/CCamera.h src/CVector2D.h \
 src/CInputHandler.h src/SMouseState.h src/CMap.h src/CGameLayer.h \
 src/CRigidBody.h src/CCollider.h src/EDirection.h src/ERotation.h
CEnemy.o: src/CEnemy.cpp src/CEnemy.h src/CEntity.h src/CGameObject.h \
 src/CGame.h src/CTextureManager.h src/CCamera.h src/CVector2D.h \
 src/CInputHandler.h src/SMouseState.h src/CMap.h src/CMapLayer.h \
 src/json.hpp src/CGameLayer.h src/CRigidBody.h src/CTimer.h \
 src/CCollider.h src/EDirection.h src/ERotation.h src/CCollisionHandler.h \
 src/CTileLayer.h src/STileSet.h src/EBlockType.h
CEntity.o: src/CEntity.cpp src/CEntity.h src/CGameObject.h src/CGame.h \
 src/CTextureManager.h src/CCamera.h src/CVector2D.h src/CInputHandler.h \
 src/SMouseState.h src/CMap.h src/CMapLayer.h src/json.hpp \
 src/CGameLayer.h src/CRigidBody.h src/CTimer.h src/CCollider.h \
 src/EDirection.h src/ERotation.h src/CCollisionHandler.h \
 src/CTileLayer.h src/STileSet.h src/EBlockType.h
CGame.o: src/CGame.cpp src/CGame.h src/CTextureManager.h src/CCamera.h \
 src/CVector2D.h src/CInputHandler.h src/SMouseState.h src/CMap.h \
 src/CMapLayer.h src/json.hpp src/CGameLayer.h src/CMapParser.h \
 src/CTileLayer.h src/CTimer.h src/STileSet.h src/EBlockType.h \
 src/CMapBackgroundLayer.h src/CHudLayer.h src/CGameObject.h \
 src/CGameplayLayer.h src/CGameObjectFactory.h src/CPlayer.h \
 src/CEntity.h src/CRigidBody.h src/CCollider.h src/EDirection.h \
 src/ERotation.h src/CCollisionHandler.h src/CEnemy.h
CGameLayer.o: src/CGameLayer.cpp src/CGameLayer.h src/CMap.h \
 src/CMapLayer.h src/json.hpp
CGameObject.o: src/CGameObject.cpp src/CGameObject.h src/CGame.h \
 src/CTextureManager.h src/CCamera.h src/CVector2D.h src/CInputHandler.h \
 src/SMouseState.h src/CMap.h src/CMapLayer.h src/json.hpp \
 src/CGameLayer.h
CGameObjectFactory.o: src/CGameObjectFactory.cpp src/CGameObjectFactory.h \
 src/CPlayer.h src/CEntity.h src/CGameObject.h src/CGame.h \
 src/CTextureManager.h src/CCamera.h src/CVector2D.h src/CInputHandler.h \
 src/SMouseState.h src/CMap.h src/CMapLayer.h src/json.hpp \
 src/CGameLayer.h src/CRigidBody.h src/CTimer.h src/CCollider.h \
 src/EDirection.h src/ERotation.h src/CCollisionHandler.h \
 src/CTileLayer.h src/STileSet.h src/EBlockType.h src/CEnemy.h
CGameplayLayer.o: src/CGameplayLayer.cpp src/CGameplayLayer.h \
 src/CGameLayer.h src/CMap.h src/CMapLayer.h src/json.hpp src/CHudLayer.h \
 src/CGame.h src/CTextureManager.h src/CCamera.h src/CVector2D.h \
 src/CInputHandler.h src/SMouseState.h src/CGameObject.h \
 src/CGameObjectFactory.h src/CPlayer.h src/CEntity.h src/CRigidBody.h \
 src/CTimer.h src/CCollider.h src/EDirection.h src/ERotation.h \
 src/CCollisionHandler.h src/CTileLayer.h src/STileSet.h src/EBlockType.h \
 src/CEnemy.h src/CMapParser.h src/CMapBackgroundLayer.h
CHudLayer.o: src/CHudLayer.cpp src/CHudLayer.h src/CGameLayer.h \
 src/CMap.h src/CMapLayer.h src/json.hpp src/CGame.h \
 src/CTextureManager.h src/CCamera.h src/CVector2D.h src/CInputHandler.h \
 src/SMouseState.h src/CGameObject.h
CInputHandler.o: src/CInputHandler.cpp src/CInputHandler.h src/CCamera.h \
 src/CVector2D.h src/CGame.h src/CTextureManager.h src/CMap.h \
 src/CMapLayer.h src/json.hpp src/CGameLayer.h src/SMouseState.h
CMapBackgroundLayer.o: src/CMapBackgroundLayer.cpp \
 src/CMapBackgroundLayer.h src/CMapLayer.h src/json.hpp src/CGame.h \
 src/CTextureManager.h src/CCamera.h src/CVector2D.h src/CInputHandler.h \
 src/SMouseState.h src/CMap.h src/CGameLayer.h src/CTimer.h
CMap.o: src/CMap.cpp src/CMap.h src/CMapLayer.h src/json.hpp
CMapLayer.o: src/CMapLayer.cpp src/CMapLayer.h src/json.hpp
CMapParser.o: src/CMapParser.cpp src/CMapParser.h src/CMap.h \
 src/CMapLayer.h src/json.hpp src/CTileLayer.h src/CTimer.h \
 src/STileSet.h src/EBlockType.h src/CMapBackgroundLayer.h src/CGame.h \
 src/CTextureManager.h src/CCamera.h src/CVector2D.h src/CInputHandler.h \
 src/SMouseState.h src/CGameLayer.h
CollisionHandler.test.o: tests/CollisionHandler.test.cpp \
 src/CCollisionHandler.h src/CTileLayer.h src/CMapLayer.h src/json.hpp \
 src/CTimer.h src/STileSet.h src/EBlockType.h src/CEntity.h \
 src/CGameObject.h src/CGame.h src/CTextureManager.h src/CCamera.h \
 src/CVector2D.h src/CInputHandler.h src/SMouseState.h src/CMap.h \
 src/CGameLayer.h src/CRigidBody.h src/CCollider.h src/EDirection.h \
 src/ERotation.h
CPlayer.o: src/CPlayer.cpp src/CPlayer.h src/CEntity.h src/CGameObject.h \
 src/CGame.h src/CTextureManager.h src/CCamera.h src/CVector2D.h \
 src/CInputHandler.h src/SMouseState.h src/CMap.h src/CMapLayer.h \
 src/json.hpp src/CGameLayer.h src/CRigidBody.h src/CTimer.h \
 src/CCollider.h src/EDirection.h src/ERotation.h src/CCollisionHandler.h \
 src/CTileLayer.h src/STileSet.h src/EBlockType.h
CRigidBody.o: src/CRigidBody.cpp src/CRigidBody.h src/CVector2D.h \
 src/CTimer.h
CTextureManager.o: src/CTextureManager.cpp src/CTextureManager.h \
 src/CGame.h src/CInputHandler.h src/CCamera.h src/CVector2D.h \
 src/SMouseState.h src/CMap.h src/CMapLayer.h src/json.hpp \
 src/CGameLayer.h
CTileLayer.o: src/CTileLayer.cpp src/CTileLayer.h src/CMapLayer.h \
 src/json.hpp src/CTimer.h src/STileSet.h src/EBlockType.h \
 src/CTextureManager.h src/CGame.h src/CInputHandler.h src/CCamera.h \
 src/CVector2D.h src/SMouseState.h src/CMap.h src/CGameLayer.h
CTimer.o: src/CTimer.cpp src/CTimer.h
CVector2D.o: src/CVector2D.cpp src/CVector2D.h
main.o: src/main.cpp src/CGame.h src/CTextureManager.h src/CCamera.h \
 src/CVector2D.h src/CInputHandler.h src/SMouseState.h src/CMap.h \
 src/CMapLayer.h src/json.hpp src/CGameLayer.h src/CTimer.h

.PHONY: deps
deps:
	$(CC) -MM $(SOURCES) > Makefile.d