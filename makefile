srcdir = src
objdir = ./

target = permanent.so
setup = setup.py

default : $(target) test

# Compile
$(target): $(srcdir)/* 
	python $(setup) build_ext --inplace 

test : 
	python ./run-tests.py

clean :
	@ rm permanent.so
	@ rm -rf build

tar :
	@ tar czf permanent.tar.gz $(srcdir) $(utils)
