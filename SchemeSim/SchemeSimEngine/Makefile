default:
	g++ *.cpp -o a
defOut:
	g++ *.cpp -o a.out
kawa:
	g++ *.cpp -o kawa
kawaOut:
	g++ *.cpp -o kawa.out
snt:
	g++ *.cpp -o a_snt -fsanitize=address -g
sntOut:
	g++ *.cpp -o a_snt.out -fsanitize=address -g
kawa_snt:
	g++ *.cpp -o kawa_snt -fsanitize=address -g
kawa_sntOut:
	g++ *.cpp -o kawa_snt.out -fsanitize=address -g
all:
	g++ *.cpp -o a
	g++ *.cpp -o a.out
	g++ *.cpp -o kawa
	g++ *.cpp -o kawa.out
	g++ *.cpp -o a_snt -fsanitize=address -g
	g++ *.cpp -o a_snt.out -fsanitize=address -g
	g++ *.cpp -o kawa_snt -fsanitize=address -g
	g++ *.cpp -o kawa_snt.out -fsanitize=address -g
clean: 
	rm -f a
	rm -f a.out
	rm -f kawa
	rm -f kawa.out
	rm -f a_snt
	rm -f a_snt.out
	rm -f kawa_snt
	rm -f kawa_snt.out
