
package javaimglib;

import java.awt.image.BufferedImage;
import java.awt.image.DataBufferInt;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import static javaimglib.JavaImgLib.COLOR_FORMAT_RGB888;
import static javaimglib.JavaImgLib.convertColorFormat;
import static javaimglib.JavaImgLib.convertImageSize;
import javax.imageio.ImageIO;

public class ARFont {
    
    private static final String[] font = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O",
    "P","Q","R","S","T","U","V","W","X","Y","Z","0","1","2","3","4","5","6","7","8","9",".",",","'",
    "!","?"};
    
    public static void initFont(String directory)throws FileNotFoundException, IOException{
        for(int i = 0; i < font.length; i++){
            if(font[i].equals(".")){
                ARFontToArr("./"+directory+"/"+font[i]+".png","LETTER_PERIOD_H",COLOR_FORMAT_RGB888);
            }
            else if(font[i].equals(",")){
                ARFontToArr("./"+directory+"/"+font[i]+".png","LETTER_COMMA_H",COLOR_FORMAT_RGB888);
            }
            else if(font[i].equals("'")){
                ARFontToArr("./"+directory+"/"+font[i]+".png","LETTER_APOSTROPHE_H",COLOR_FORMAT_RGB888);
            }
            else if(font[i].equals("!")){
                ARFontToArr("./"+directory+"/"+font[i]+".png","LETTER_EXCLAMATION_H",COLOR_FORMAT_RGB888);
            }
            else if(font[i].equals("?")){
                ARFontToArr("./"+directory+"/"+font[i]+".png","LETTER_QUESTION_H",COLOR_FORMAT_RGB888);
            }
            else{
                ARFontToArr("./"+directory+"/"+font[i]+".png","LETTER_"+font[i]+"_H",COLOR_FORMAT_RGB888);
            }
        }
    }
    
    public static void ARFontToArr(String fileName, String headerName, int colorFormat)throws FileNotFoundException, IOException{
        
        int count = 0;
        
        File file = new File(fileName);
        
        if(file.exists()){
            BufferedImage img = ImageIO.read(file);
            
            int width = img.getWidth();
            int height = img.getHeight();
            
            convertColorFormat(img, colorFormat);
            
            int[] clut = ((DataBufferInt)img.getRaster().getDataBuffer()).getData();
            
            PrintWriter pw = new PrintWriter(fileName+".h");
            
            pw.println("#ifndef"+" "+headerName+"_H");
            pw.println("#define"+" "+headerName+"_H");
            pw.println();
            pw.print("int clut["+String.valueOf(width)+"*"+String.valueOf(height)+"] = {");
            
            for(int i = 0; i < clut.length; i++){
                
                pw.printf("%s",Integer.toHexString(clut[i]));
                
                if(count % 40 == 0){
                    pw.println();
                }
                
                count++;
            }
            
            pw.println("};");
            pw.print("#endif");
        }
    }
    
    public static int[] imgToCArr(String fileName, int newWidth, int newHeight, int colorFormat)throws FileNotFoundException, IOException{
        
        File file = new File(fileName);
        
        if(file.exists()){
            
            BufferedImage img = ImageIO.read(file);
            convertColorFormat(img,colorFormat);
            convertImageSize(img, newWidth, newHeight);
            
            int[] clut = ((DataBufferInt)img.getRaster().getDataBuffer()).getData();
            
            return clut;
        }
        else return new int[]{0};
    }
}
