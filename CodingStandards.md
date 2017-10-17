 # BlueBerry coding standards
by **Dedipyaman Das** | github.com/2DSharp


* Indent code correctly. All code blocks should have two spaces indentation. Example: 

      void someFunction() {
        Serial.println(“Look how this line is indented by two spaces after the function definition”);
      }
* Be careful with variable names. Variables should be named in this fashion:
   * If the variable name (not value) is a single word like “servo”, write it in lowercase. Example: int servo;
   * If the variable name is a compound word (combination of two or more words), capitalize every word after the first word, without spaces. Example: ```ledPinNumber``` (not led-pin-number or LedPinNumber).
   * The variable names should be descriptive and easily readable and understandable by anyone, no matter how big. Avoid ambiguous variable names like “a, b, c, i, j, k, nm, srvo”. Use names like ```motorSpeed``` instead of spd or s.
   * Don't make them too big in the process. Keep them short and descriptive. 
* Function names follow the same conventions. If you have to get the value of something like getting the current servo degree with a function, use names like getServoDegree instead of degree(). Similarly if you have to set the value of something with a function, use names like setServoDegree().
* Filenames should follow **PascalCasing** conventions. Use *BlinkLED.ino* instead of ledblink.ino.
* Class names and object names like ```Serial``` (which is a predefined Arduino class) should always follow PascalCasing. 
* Every code should be in the ```src/``` directory. Put your tests in the Tests/ folder. 
* Keep the code clean. Break down problems. **Use functions**. 
* Document your code, comment everything. **DO NOT** write something that you don't understand. Don't copy paste blindly. 
* Use appropriate spacing. Don't put more spaces or less spaces than necessary. Put spaces between variables and operators(```num = 5``` instead of ```num=5```). Do not make spelling mistakes. 
* Test and commit to the **feature-test** branch. Upload all new tested and finalized code to github. Put useful commit messages describing the recent change in the commit. 
* Each function should have 100 lines of code or less. 
* Each line should be less than 80 characters long.
