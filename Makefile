CC = g++

OBJECTS = `find . -name "*.o"`
LIBS = `pkg-config --libs openscenegraph` -lm ../bullet_lib/libbulletdynamics.a ../bullet_lib/libbulletcollision.a ../bullet_lib/libbulletmath.a

SUBDIR = controller simulator

.PHONY: botsim $(SUBDIR) clean

botsim: $(SUBDIR)
	$(CC) -o botsim $(OBJECTS) $(LIBS)

$(SUBDIR):
	$(MAKE) --directory=$@

clean:
	rm -rf botsim
	$(MAKE) clean --directory=simulator
	$(MAKE) clean --directory=controller
