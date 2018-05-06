CC = gcc
all:
	$(CC) -o parse_xml_bin parse_xml_bin.c

clean:
	-rm -rf parse_xml_bin *.o
	
