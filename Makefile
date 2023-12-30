COMPILE = g++-11 -std=c++20 -fmodules-ts -Wall -g
EXEC = age
OFILES = main.o gameengine.o board.o controller.o model.o ncurseskeyinput.o ncursesview.o observer.o subject.o view.o object.o bitmapobject.o basicobject.o rectangleobject.o borderobject.o movement.o straightmovement.o bordermovement.o cyclicmovement.o wasdmovement.o collision.o stopcollision.o onewaydamage.o bounceoffcollision.o endgamecollision.o spawnermovement.o statusline.o gamestatus.o attributestatus.o typecountstatus.o spawnercollision.o winlosecondition.o attributewinlose.o typecountwinlose.o client.o


${EXEC}: ${OFILES}
	${COMPILE} ${OFILES} -o ${EXEC} -lncurses

main.o: main.cc client.h
	${COMPILE} -c main.cc

gameengine.o: gameengine.cc gameengine.h view.h controller.h ncursesview.h ncurseskeyinput.h board.h movement.h wasdmovement.h collision.h stopcollision.h bounceoffcollision.h borderobject.h bordermovement.h endgamecollision.h cyclicmovement.h straightmovement.h bitmapobject.h basicobject.h rectangleobject.h spawnermovement.h statusline.h gamestatus.h attributestatus.h typecountstatus.h spawnercollision.h winlosecondition.h attributewinlose.h typecountwinlose.h
	${COMPILE} -c gameengine.cc

board.o: board.cc board.h model.h view.h object.h ncurseskeyinput.h movement.h wasdmovement.h endgamecollision.h statusline.h spawnermovement.h spawnercollision.h winlosecondition.h
	${COMPILE} -c board.cc

controller.o: controller.cc controller.h subject.h model.h
	${COMPILE} -c controller.cc

model.o: model.cc model.h observer.h subject.h view.h
	${COMPILE} -c model.cc

ncurseskeyinput.o: ncurseskeyinput.cc ncurseskeyinput.h controller.h
	${COMPILE} -c ncurseskeyinput.cc

ncursesview.o: ncursesview.cc ncursesview.h view.h
	${COMPILE} -c ncursesview.cc

observer.o: observer.cc observer.h
	${COMPILE} -c observer.cc

subject.o: subject.cc subject.h observer.h
	${COMPILE} -c subject.cc

view.o: view.cc view.h observer.h
	${COMPILE} -c view.cc

object.o: object.cc object.h drawable.h movement.h collidable.h 
	${COMPILE} -c object.cc

bitmapobject.o: bitmapobject.cc bitmapobject.h object.h
	${COMPILE} -c bitmapobject.cc

basicobject.o: basicobject.cc basicobject.h object.h
	${COMPILE} -c basicobject.cc

rectangleobject.o: rectangleobject.cc rectangleobject.h object.h
	${COMPILE} -c rectangleobject.cc

borderobject.o: borderobject.cc borderobject.h object.h
	${COMPILE} -c borderobject.cc

movement.o: movement.cc movement.h reversible.h
	${COMPILE} -c movement.cc

straightmovement.o: straightmovement.cc straightmovement.h basicobject.h rectangleobject.h bitmapobject.h
	${COMPILE} -c straightmovement.cc

bordermovement.o: bordermovement.cc bordermovement.h basicobject.h rectangleobject.h bitmapobject.h
	${COMPILE} -c bordermovement.cc

cyclicmovement.o: cyclicmovement.cc cyclicmovement.h basicobject.h rectangleobject.h bitmapobject.h
	${COMPILE} -c cyclicmovement.cc

wasdmovement.o: wasdmovement.cc wasdmovement.h basicobject.h rectangleobject.h bitmapobject.h
	${COMPILE} -c wasdmovement.cc

collision.o: collision.cc collision.h object.h
	${COMPILE} -c collision.cc

stopcollision.o: stopcollision.cc stopcollision.h collision.h object.h
	${COMPILE} -c stopcollision.cc

onewaydamage.o: onewaydamage.cc onewaydamage.h collision.h object.h
	${COMPILE} -c onewaydamage.cc

bounceoffcollision.o: bounceoffcollision.cc bounceoffcollision.h collision.h object.h
	${COMPILE} -c bounceoffcollision.cc

endgamecollision.o: endgamecollision.cc endgamecollision.h collision.h object.h
	${COMPILE} -c endgamecollision.cc

spawnermovement.o: spawnermovement.cc spawnermovement.h subject.h board.h object.h movement.h
	${COMPILE} -c spawnermovement.cc

statusline.o: statusline.cc statusline.h
	${COMPILE} -c statusline.cc

gamestatus.o: gamestatus.cc gamestatus.h statusline.h board.h
	${COMPILE} -c gamestatus.cc

attributestatus.o: attributestatus.cc attributestatus.h statusline.h board.h
	${COMPILE} -c attributestatus.cc

typecountstatus.o: typecountstatus.cc typecountstatus.h statusline.h board.h
	${COMPILE} -c typecountstatus.cc

spawnercollision.o: spawnercollision.cc spawnercollision.h collision.h object.h model.h
	${COMPILE} -c spawnercollision.cc

winlosecondition.o: winlosecondition.cc winlosecondition.h 
	${COMPILE} -c winlosecondition.cc

attributewinlose.o: attributewinlose.cc attributewinlose.h board.h
	${COMPILE} -c attributewinlose.cc

typecountwinlose.o: typecountwinlose.cc typecountwinlose.h board.h
	${COMPILE} -c typecountwinlose.cc

client.o: client.cc client.h gameengine.h
	${COMPILE} -c client.cc

.PHONY: clean

clean:
	rm *.o ${EXEC}
