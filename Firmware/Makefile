
# Só escrevi esse MAKE := make pq eu estou utilizando o make do mingw64
# e o make do mingw64 é diferente do make do chocollatey, então eu preciso especificar
# o make que eu quero utilizar, nesse caso o do mingw64
# Caso você esteja utilizando o make do chocolatey, pode remover essa linha

MAKE := make

.PHONY:gccall
gccall:
	(cd Applications/$(PROJECT) && $(MAKE) V=$(V) -f Makefile all)

.PHONY:clean_all
clean_all:
ifneq ("$(wildcard Build/)","")
	@$(RM) -r Build/
endif

.PHONY:clean-gccall
clean-gccall:
	(cd Applications/$(PROJECT) && $(MAKE) -f Makefile cleanall)

.PHONY:clean-gcc
clean-gcc:
	(cd Applications/$(PROJECT) && $(MAKE) -f Makefile clean)

.PHONY:size
size:
	(cd Applications/$(PROJECT) && $(MAKE) -f Makefile size)

.PHONY:jflash
jflash:
	(JLink -commanderscript Applications/$(PROJECT)/Launch/jflash)

