#all:
#	javac -source 1.4 -target 1.4 *.java
#	cp *.class ~/public_html/test/IDV/
#	cp html/*.html ~/public_html/test/IDV/
#	cp files/*.tptp ~/public_html/test/IDV/files/

#java -classpath .:./parser/antlr-2.7.5.jar:./parser/TptpParser.jar TestParser

JAVA = 	./AboutBox.java \
	./BezierChain.java \
	./BezierCurve.java \
	./Edge.java \
	./Formula.java \
	./GMSlider.java \
	./Graph.java \
	./GraphManTools.java \
	./GraphPanel.java \
	./GravityForce.java \
	./IDGraph.java \
	./IDNode.java \
	./IDVApplet.java \
	./IDV.java \
	./Intersection.java \
	./Node.java \
	./NodePair.java \
	./SensitivePolygon.java \
	./SpringEmbedder.java \
	./TestParser.java \
	./TPTPReader.java \
	./URLReader.java

PARSER_DIR = ./parser
PARSER_JAR = $(PARSER_DIR)/TptpParser.jar
ANTLR_JAR = $(PARSER_DIR)/antlr-2.7.5.jar
HTTP_JAR = ClientHttpRequest/ClientHttpRequest.jar
NETSCAPE_JAR = ./netscape.jar
all: public


#%.class: %.java
#	javac -classpath .:$(ANTLR_JAR):$(PARSER_JAR) $<
#	cd parser; make default; cp *.class ../
#	javac -classpath .:$(ANTLR_JAR) $<

private: 
#	javac -source 1.4 -target 1.4 -classpath ./parser/TPTPParser.jar -classpath.:$(ANTLR_JAR) *.java	
#	jar cf IDV.jar *.class images/*.* ./parser/TPTPParser.jar
#	javac -source 1.4 -target 1.4 *.java	
	jar cf IDV.jar $(PARSER_JAR) $(ANTLR_JAR) $(HTTP_JAR) *.class images/*.* 
	cp IDV.jar ~/private_html/test/IDV/
	cp html/*.html ~/private_html/test/IDV/
	cp files/*.tptp ~/private_html/test/IDV/files/

public: 
#	javac -source 1.4 -target 1.4 -classpath ./parser/TPTPParser.jar *.java	
#	jar cf IDV.jar *.class images/*.* ./parser/TPTPParser.jar
#	javac -source 1.4 -target 1.4 *.java	
	cd parser; make default
	cd ClientHttpRequest; make default
#	javac -source 1.4 -target 1.4 -classpath .:$(ANTLR_JAR):$(PARSER_JAR) *.java
#	javac -classpath .:$(ANTLR_JAR):$(PARSER_JAR):$(NETSCAPE_JAR) *.java
	javac -source 1.5 -target 1.5 -classpath .:$(ANTLR_JAR):$(PARSER_JAR):$(NETSCAPE_JAR):$(HTTP_JAR) *.java
	jar cfm IDV.jar Manifest.txt *.class images/*.* 
#	cp IDV.jar ~/public_html/test/IDV/
#	cp $(PARSER_JAR) ~/public_html/test/IDV/
#	cp $(HTTP_JAR) ~/public_html/test/IDV/
#	cp $(ANTLR_JAR) ~/public_html/test/IDV/
#	cp html/*.html ~/public_html/test/IDV/
#	cp files/* ~/public_html/test/IDV/files/

test:
	cp html/*.html ~/public_html/test/IDV/
	cp files/*.tptp ~/public_html/test/IDV/files/

clean:
	rm *.class *~ core.* IDV.jar
