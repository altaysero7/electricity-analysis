project: projectWork.o methods.o
	gcc projectWork.o methods.o -o project
projectWork.o: projectWork.c
	gcc projectWork.c -c
methods.o: methods.c
	gcc methods.c -c