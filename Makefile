CXX = g++
CXXFLAGS = -Wall -MMD
OBJECTS = main.o shade.o game.o character.o entity.o player.o npc.o human.o vampire.o dwarf.o util.o potion.o treasure.o drow.o troll.o goblin.o orc.o elf.o dragon.o halfling.o merchant.o
DEPENDS = ${OBJECTS.o=.d}
EXEC = cc3k

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}
