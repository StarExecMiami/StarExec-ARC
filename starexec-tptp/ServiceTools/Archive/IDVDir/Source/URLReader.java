import java.io.*;
import java.net.*;
import java.util.StringTokenizer;
import java.util.*;

public class URLReader {

  public static final String URL_FILE = "url.dat";
  //public URL AGInT_URL;
  public String AGInT_URL;

  public URLReader () {
    // read from url.dat
    //DataInputStream dis = null;
    BufferedReader bin = null;
    String entry = null;
    FileReader file = null;
    try {
      File f = new File(URL_FILE);
      file = new FileReader(f);
      bin = new BufferedReader(file);
      //FileInputStream fis = new FileInputStream(f);
      //BufferedInputStream bis = new BufferedInputStream(fis);
      //dis = new DataInputStream(bis);

      // read each line
      while ( (entry = bin.readLine()) != null) {
        System.out.println("Current entry: " + entry);
        
        if (entry.equals("")) {
          continue;
        }

        StringTokenizer st = new StringTokenizer(entry, " ");
        
        String name = st.nextToken();
        String url = st.nextToken();

        System.out.println("name: " + name);
        System.out.println("url: " + url);
       
        if (name.equals("AGInT")) {
          System.out.println("AGINT url: " + url);
          //AGInT_URL = new URL(url);
          AGInT_URL = url;
          System.out.println("AGINT url: " + url);
        }

      }
    } catch (IOException e) {
      System.out.println("IO Error: " + e.getMessage());
    } 

    try { file.close(); } catch (Exception e) { }

    System.out.println("Success");
  }


};
