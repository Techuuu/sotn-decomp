# build object file with dosemu
HOME="." dosemu -quiet -dumb -f ./dosemurc -K . -E "GCC.EXE -c -I./ $OPT_FLAGS -m2 -fsigned-char $FILENAME.c -o $FILENAME.o"
