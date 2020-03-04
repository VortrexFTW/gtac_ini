# gtac_ini

INI module for GTA Connected

Originally created by Lucx. Updated by Vortrex to support the new module SDK

Script example:
 ```
 	ini = module.ini.create();

 	ini.loadFile("abc.txt")

 	ini.setStringValue("Section", "Test", "Hello world!", "Comment example", true);

 	ini.saveFile("abc.txt")

 	ini.close();
 ```

Functions available:
 ```
 * ptr.errno(int errid)
 * ptr.reset();
 * ptr.delete(string szSection, string szKey, bool bRemoveEmpty = true);
 * ptr.isEmpty();
 * ptr.isMultiKey();
 * ptr.isMultiLine();
 * ptr.isUnicode();
 * ptr.isUsingSpaces()
 * ptr.setUnicode(bool bUnicode)
 * ptr.loadFile(string szFile)
 * ptr.saveFile(string szFile, bool bSign)
 * ptr.getBoolValue(string szSection, string szKey, bool bDefaultValue = false)
 * ptr.getIntValue(string szSection, string szKey, bool iDefaultValue = 0)
 * ptr.getFloatValue(string szSection, string szKey, bool fDefaultValue = 0.0)
 * ptr.getStringValue(string szSection, string szKey, string szDefaultValue = "")
 * ptr.setBoolValue(string szSection, string szKey, bool bValue, string szComment, bool bForceReplace)
 * ptr.setIntValue(string szSection, string szKey, int iValue, string szComment, bool bUseHex, bool bForceReplace)
 * ptr.setFloatValue(string szSection, string szKey, float fValue, string szComment, bool bReplace)
 * ptr.setStringValue(string szSection, string szKey, string szValue, string szComment, bool bForceReplace)
 ```