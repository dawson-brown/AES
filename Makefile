testing:
	make -f makefile.test

# debugging:
# 	make -f makefile.debug

# release:
# 	make -f makefile.release

clean-test:
	rm test/*.o

# clean-debug:
# 	rm -rf debug/

# clean-release:
# 	rm -rf release/